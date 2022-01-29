#include <stdlib.h>

#include <spawn.h>
#include <unistd.h>

#include <errno.h>

extern char **environ;

#include "sub.h"

int z__sub_runf(const char *command)
{
    pid_t child, p;
    int   status;

    /*
     * Prepare pipes et cetera first.
    */

    /* Fork to create the subprocess. */
    child = fork();
    if (child == (pid_t)-1) {
        /* Cannot fork(); usually out of resources (user limits).
         * see errno for details. With <string.h>, you can use
         * strerror(errno) to obtain the error string itself. */
        return 0;

    } else
    if (!child) {
        /* This is the child process itself.
         * Do whatever cleanup is necessary, then
         * execute the subprocess command. */
        execl("/bin/sh", "sh", "-c", command, NULL);

        /* This is only reached if the exec failed;
         * again, see errno for reason.
         * Always have the child process exit! */
        return 0;
    }

    /* This is only run by the parent process
     * (because the child always exits within the
     *  else if body above).
     *
     * The subprocess PID is 'child'.
    */

    /* Wait for the child process to exit. */
    do {
        status = 0;
        p = waitpid(child, &status, 0);
        if (p == (pid_t)-1 && errno != EINTR)
            break; /* Error */
    } while (p != child);

    if (p != child) {
        /* Child process was lost.
         * If (p == (pid_t)-1), errno describes the error.
        */

    } else
    if (WIFEXITED(status)) {
        /* Child process exited with WEXITSTATUS(status) status.
         * A status of 0 (or EXIT_SUCCESS) means success,
         * no errors occurred. Nonzero usually means an error,
         * but codes vary from binary to binary.
        */

    } else
    if (WIFSIGNALED(status)) {
        /* Child process died from WTERMSIG(status) signal.
         * If you include <string.h>, you can use
         *     strsignal(WTERMSIG(status))
         * to obtain the name (string) of the terminating signal.
        */

    } else {
        /* Child process died from unknown causes.
        */

    }

    /* All done. */
    return 1;
}

int z__sub_runp(char const *cmd)
{
    pid_t pid;
    char *argv[] = {"sh", "-c", (char*)cmd, NULL};
    int status;
    status = posix_spawn(&pid, "/bin/sh", NULL, NULL, argv, environ);
    if (status == 0) {
        do {
          if (waitpid(pid, &status, 0) == -1) {
            exit(1);
          }
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

