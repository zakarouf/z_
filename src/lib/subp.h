/**
    z_, Core Language Module with datatypes, memory tracker, and beyond.
    Copyright (C) 2025  Zakarouf

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ZAKAROUF_Z_IMP__SUB_H
#define ZAKAROUF_Z_IMP__SUB_H

/**
 * Get Enviorment Variable
 */
char** z__subp_getenv(void);

/**
 * Use fork() to create a child process
 */
int z__subp_fork(char const *cmd);

/**
 * Use posix_spawn() to create a child process
 */
int z__subp_spawn(char * const cmd);

/**
 * Use posix_spawn() to execute a binary, must provide absolute path of the binary
 */
int z__subp_exec_raw(char const *absolute_exec_path, char * const *argv);

/**
 * Same as z__sub_exec_raw(), but does not wait for child process to exit.
 */
int z__subp_exec_nowait_raw(int *pid, char const *absolute_exec_path, char * const *argv);

/**
 * Macro wrapper around z__sub_exec_nowait_raw()
 */
#define z__subp_exec_nowait(p, exec, ...)\
  z__subp_exec_nowait_raw(p, exec, (char *const[]){__VA_ARGS__, NULL})

/**
 * Macro wrapper around z__sub_exec_raw()
 */
#define z__subp_exec(exec_path, ...)\
    z__subp_exec_raw(exec_path, (char *const []){__VA_ARGS__, NULL})


#ifdef Z__IMPLEMENTATION
#include <stdlib.h>
#include <spawn.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

extern char **environ;

char** z__subp_getenv(void) { return environ; }

int z__subp_fork(const char *command)
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

    } else if (!child) {
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

    } else if (WIFEXITED(status)) {
        /* Child process exited with WEXITSTATUS(status) status.
         * A status of 0 (or EXIT_SUCCESS) means success,
         * no errors occurred. Nonzero usually means an error,
         * but codes vary from binary to binary.
        */

    } else if (WIFSIGNALED(status)) {
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

int z__subp_exec_nowait_raw(int *pid, char const *exec_path, char * const *argv)
{
    int status = posix_spawn(pid, exec_path, NULL, NULL, argv, environ);
    return status;
}

int z__subp_exec_raw(char const *exec_path, char * const *argv)
{
    pid_t pid;
    int status = posix_spawn(&pid, exec_path, NULL, NULL, argv, environ);
    if (status == 0) {
        do {
            if (waitpid(pid, &status, 0) == -1) {
                exit(1);
            }
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

int z__subp_spawn(char * const cmd)
{
    return z__subp_exec("/bin/sh", "sh", "-c", cmd);
}

#endif //Z__IMPLEMENTATION

#endif

