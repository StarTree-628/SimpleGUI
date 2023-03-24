#include "console_log.h"
#include <stdarg.h>
#include <sys/timeb.h>
#include <time.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

void simulator_console_log(const char* format, ...)
{
    va_list     args;
    va_start(args, format);
    {
        struct timeb st_timeb;
        time_t      st_time = ::time(nullptr);
        struct tm*  pst_local_time = localtime(&st_time);
        ftime(&st_timeb);
        printf("[%04d-%02d-%02d %02d:%02d:%02d.%03d]", 1900+pst_local_time->tm_year, pst_local_time->tm_mon, pst_local_time->tm_mday,
               pst_local_time->tm_hour, pst_local_time->tm_min, pst_local_time->tm_sec, st_timeb.millitm);
        (void)vprintf(format, args);
    }
    va_end(args);
}

#ifdef __cplusplus
}
#endif // __cplusplus
