#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include <string.h>
#include <z_/types/hashhoyt.h>
#include <z_/types/mem.h>
#include <z_/types/string.h>
#include <z_/types/fnptr.h>

#include <z_/imp/sub.h>
#include <z_/imp/fio.h>
#include <z_/imp/sys.h>

#include <readline/readline.h>
#include <readline/history.h>

#include <dirent.h>

#define PROMT_L ""

typedef struct chs_State chs_State;
typedef void (* BuiltinFn)(chs_State *, void **);
typedef z__HashHoyt(BuiltinFn) Functions;

typedef struct chs_State {
    char *cmd;
    char *args;

    int cmd_len;
    int arg_len;
    
    z__String dir;
    Functions fn;
} chs_State;

void die(int _code)
{
    exit(_code);
}

static void _cd_back(chs_State *c)
{
    if(c->dir.lenUsed > 1) {
        int i = c->dir.lenUsed-2;
        while(i > 1 && c->dir.data[i] != '/') i--;
        c->dir.lenUsed = i;
        c->dir.data[i] = 0;
    }
    return;
}

static void _cd(chs_State *c, void **m)
{
    const char *args = c->args;
    if(args[0] == 0) z__String_replace(&c->dir, "/");
    if(args[0] == '.' && args[1] == '.') _cd_back(c);

    if(args[0] == '/') {
        if(z__fio_directoryExist(args)) {
            z__String_replace(&c->dir, "%s", args);
        } else {
            z__log_cl256(1, "Folder %s Does not exist!\n", args);
        }
        return;
    }

    z__String_append(&c->dir, 0, '0', "%s/", args);
    if (z__fio_directoryExist(c->dir.data)) {
    } else {
        z__log_cl256(1, "Folder %s Does not exist!\n", c->dir.data);
        _cd_back(c);
    }
}

static void _ls(chs_State *c, void **m)
{
    if(c->args[0] == 0) c->args = "./";
    const char *args = c->args;

    z__String tmp = z__String_newCopy(c->dir);
    _cd(c, 0);

    DIR *drip = opendir(c->dir.data); 
    if(drip == NULL) goto _L_return;

    struct dirent *d;
    int items = 0;
    while((d = readdir(drip)) != NULL) {
        printf("%s\n", d->d_name);
    }
    closedir(drip);
    
    _L_return:
    z__String_delete(&c->dir);
    c->dir = tmp;
}

void chs_State_addfn(chs_State *c, const char *name, BuiltinFn fn)
{
    z__HashHoyt_set(&c->fn, name, fn);
}

chs_State *chs_State_new(void)
{
    chs_State *c = z__New(*c, 1);
    c->cmd = "";
    c->args = "";

    c->dir = z__String_new(128);
    z__String_replace(&c->dir, "/");

    z__HashHoyt_new(&c->fn); 
    chs_State_addfn(c, "cd", _cd);
    chs_State_addfn(c, "ls", _ls);
    return c;
}

void chs_State_delete(chs_State *c)
{
    z__String_delete(&c->dir);
    z__HashHoyt_delete(&c->fn);
}

void* chs_State_tryrunfn(chs_State *c)
{
    BuiltinFn *f;
    z__HashHoyt_getreff(&c->fn, c->cmd, f);
    z__fnptr_call(f, 0, c, NULL);
    return f;
}

#define chs_readline(c, promt)\
    {\
        (c)->cmd = readline(promt);\
        add_history((c)->cmd);\
        (c)->cmd_len = strlen((c)->cmd);\
        (c)->args = (char *)z__str_skipget_ws((c)->cmd, (c)->cmd_len);\
        (c)->arg_len = ((c)->args - (c)->cmd);\
        (c)->cmd_len = (c)->cmd_len - (c)->arg_len;\
        *(c)->args = 0;\
        (c)->args += 1;\
    }

#define chs_linefree(c)\
{ z__FREE((c)->cmd); (c)->cmd = ""; (c)->args = ""; }

static void chs_run(void)
{
    chs_State *c = chs_State_new();
    int quit = 0;
    while(!quit) {
        printf("%s >>> ", c->dir.data);
        chs_readline(c, PROMT_L);
        if(chs_State_tryrunfn(c) == NULL) {
            c->args[-1] = ' ';
            z__sub_spawn(c->cmd);
        }
        chs_linefree(c);
    }
}

int main(int argc, char const *argv[])
{
    signal(SIGINT, die);
    chs_run();
    return 0;
}
