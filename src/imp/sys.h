#ifndef ZAKAROUF_Z_IMP__SYS_H
#define ZAKAROUF_Z_IMP__SYS_H


/* System */
long z__sys_getRamUsage(void);


/* Log */
void z__log_basic(void * fileStream ,const char *format, ...);

#define z__log_color(color, format, ...)\
    z__log_basic(stdout, "\x1b[38;5;%dm" format "\x1b[0m", color, ##__VA_ARGS__ )

#define z__log_verbose(format, ...)\
    z__log_basic(stdout, "%s:%u @ %s(): " format, __FILE__, __LINE__, __func__, __VA_ARGS__)

#define z__log_color_verbose(color, format, ...)\
    z__log_basic(stdout, "\x1b[38;5;%dm" "%s:%u @ %s(): " format "\x1b[0m", color, __FILE__, __LINE__, __func__, ##__VA_ARGS__)

#endif