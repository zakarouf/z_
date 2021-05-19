#ifndef ZAKAROUF_Z_IMP__SYS_H
#define ZAKAROUF_Z_IMP__SYS_H


/* System */
long z__sys_getRamUsage(void);


/* Log */
void z__log_basic(void * fileStream ,const char *format, ...);


#define z__log_verbose(format, ...)\
    z__log_basic(stdout, "%s:%u @ %s(): " format, __FILE__, __LINE__, __func__, __VA_ARGS__)

#define z__log_cl256(color, format, ...)\
    z__log_basic(stdout, "\x1b[38;5;%dm" format "\x1b[0m", color, ##__VA_ARGS__ )

#define z__log_cl256_full(colorb, colorf, format, ...)\
    z__log_basic(stdout, "\x1b[38;5;%dm" "\x1b[48;5;%dm" format "\x1b[0m", colorb, colorf, ##__VA_ARGS__ )

#define z__log_cl256_verbose(color, format, ...)\
    z__log_basic(stdout, "\x1b[38;5;%dm" "%s:%u @ %s(): " format "\x1b[0m", color, __FILE__, __LINE__, __func__, ##__VA_ARGS__)

#define z__log_cl256_full_verbose(colorb, colorf, format, ...)\
    z__log_basic(stdout, "\x1b[38;5;%dm" "\x1b[48;5;%dm" "%s:%u @ %s(): " format "\x1b[0m", colorb, colorf, __FILE__, __LINE__, __func__, ##__VA_ARGS__)

#define z__log_clrgb(r, g, b, format, ...)\
    z__log_basic(stdout, "\x1b[38;2;%u;%u;%um" format "\x1b[0m", r, g, b, ##__VA_ARGS__)

#define z__log_clrgb_verbose(r, g, b, format, ...)\
    z__log_basic(stdout, "\x1b[38;2;%u;%u;%um" "%s:%u @ %s(): " format "\x1b[0m", r, g, b, __FILE__, __LINE__, __func__, ##__VA_ARGS__)


#define z__log_clrgb_full(r, g, b, fr, fg, fb, format, ...)\
    z__log_basic(stdout, "\x1b[38;2;%u;%u;%um" "\x1b[48;2;%u;%u;%um" format "\x1b[0m", r, g, b, fr, fg, fb, ##__VA_ARGS__)

#define z__log_clrgb_full_verbose(r, g, b, fr, fg, fb, format, ...)\
    z__log_basic(stdout, "\x1b[38;2;%u;%u;%um" "\x1b[48;2;%u;%u;%um" "%s:%u @ %s(): " format "\x1b[0m", r, g, b, fr, fg, fb, __FILE__, __LINE__, __func__, ##__VA_ARGS__)    

#endif