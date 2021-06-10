#ifndef ZAKAROUF_Z_IMP__SYS_H
#define ZAKAROUF_Z_IMP__SYS_H


/* System */
long z__sys_getRamUsage(void);


/* Log */
void z__logfile_basic(void * fileStream ,const char *format, ...)
    __attribute__ ((format (printf, 2, 3)));;

#define z__logfile_verbose(file_ptr , format, ...)\
    z__logfile_basic(file_ptr, "%s:%u @ %s(): " format, __FILE__, __LINE__, __func__, __VA_ARGS__)


#define z__logfile_cl256(file_ptr , color, format, ...)\
    z__logfile_basic(file_ptr, "\x1b[38;5;%dm" format "\x1b[0m", color, ##__VA_ARGS__ )

#define z__logfile_cl256_full(file_ptr , colorb, colorf, format, ...)\
    z__logfile_cl256(file_ptr, colorf, "\x1b[48;5;%dm" format, colorb, ##__VA_ARGS__)

#define z__logfile_cl256_verbose(file_ptr , color, format, ...)\
    z__logfile_cl256(file_ptr, color, "%s:%u @ %s(): " format, __FILE__, __LINE__, __func__, ##__VA_ARGS__)

#define z__logfile_cl256_full_verbose(file_ptr , colorb, colorf, format, ...)\
    z__logfile_cl256_full(file_ptr, colorb, colorf, "%s:%u @ %s(): " format "\x1b[0m", __FILE__, __LINE__, __func__, ##__VA_ARGS__)


#define z__logfile_clrgb(file_ptr, r, g, b, format, ...)\
    z__logfile_basic(file_ptr, "\x1b[38;2;%u;%u;%um" format "\x1b[0m", r, g, b, ##__VA_ARGS__)

#define z__logfile_clrgb_verbose(file_ptr, r, g, b, format, ...)\
    z__logfile_clrgb(file_ptr, r, g, b, "%s:%u @ %s(): " format "\x1b[0m", __FILE__, __LINE__, __func__, ##__VA_ARGS__)

#define z__logfile_clrgb_full(file_ptr, br, bg, bb, fr, fg, fb, format, ...)\
    z__logfile_clrgb(file_ptr, fr, fg, fb, "\x1b[48;2;%u;%u;%um" format "\x1b[0m", br, bg, bb, ##__VA_ARGS__)

#define z__logfile_clrgb_full_verbose(file_ptr, br, bg, bb, fr, fg, fb, format, ...)\
    z__logfile_clrgb_full(file_ptr, br, bg, bb, fr, fg, fb, "%s:%u @ %s(): " format "\x1b[0m", __FILE__, __LINE__, __func__, ##__VA_ARGS__)    


#define z__log_basic(format, ...)\
    z__logfile_basic(stdout, format, __VA_ARGS__)

#define z__log_verbose(format, ...)\
    z__logfile_verbose(stdout, format, __VA_ARGS__)

#define z__log_cl256(color, format, ...)\
    z__logfile_basic(stdout, color, format, __VA_ARGS__ )

#define z__log_cl256_full(colorb, colorf, format, ...)\
    z__logfile_cl256_full(stdout, colorb, colorf, format, __VA_ARGS__ )

#define z__log_cl256_verbose(color, format, ...)\
    z__logfile_cl256_verbose(stdout, color, format, __VA_ARGS__)

#define z__log_cl256_full_verbose(colorb, colorf, format, ...)\
    z__logfile_cl256_full_verbose(stdout, colorb, colorf, format, __VA_ARGS__)

#define z__log_clrgb(r, g, b, format, ...)\
    z__logfile_clrgb(stdout, r, g, b, format, __VA_ARGS__)

#define z__log_clrgb_verbose(r, g, b, format, ...)\
    z__logfile_clrgb_verbose(stdout, r, g, b, format, ##__VA_ARGS__)


#define z__log_clrgb_full(r, g, b, fr, fg, fb, format, ...)\
    z__logfile_clrgb_full(stdout, r, g, b, fr, fg, fb, format, __VA_ARGS__)

#define z__log_clrgb_full_verbose(r, g, b, fr, fg, fb, format, ...)\
    z__logfile_clrgb_full_verbose(stdout, r, g, b, fr, fg, fb, format, __VA_ARGS__)    


#endif
