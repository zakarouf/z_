#ifndef ZAKAROUF_Z_IMP__SUB_H
#define ZAKAROUF_Z_IMP__SUB_H

/**
 * Get Enviorment Variable
 */
char** z__sub_getenv(void);

/**
 * Use fork() to create a child process
 */
int z__sub_fork(char const *cmd);

/**
 * Use posix_spawn() to create a child process
 */
int z__sub_spawn(char * const cmd);

/**
 * Use posix_spawn() to execute a binary, must provide absolute path of the binary
 */
int z__sub_exec_raw(char const *exec_path, char * const *argv);

/**
 * Same as z__sub_exec_raw(), but does not wait for child process to exit.
 */
int z__sub_exec_nowait_raw(int *pid, char const *exec_path, char * const *argv);

/**
 * Macro wrapper around z__sub_exec_nowait_raw()
 */
#define z__sub_exec_nowait(p, exec, ...)\
  z__sub_exec_nowait_raw(p, exec, (char *const[]){__VA_ARGS__, NULL})

/**
 * Macro wrapper around z__sub_exec_raw()
 */
#define z__sub_exec(exec_path, ...)\
    z__sub_exec_raw(exec_path, (char *const []){__VA_ARGS__, NULL})

#endif

