#ifndef _INCLUDE_LOG_H_
#define _INCLUDE_LOG_H_

#include <stdio.h>
#include <pthread.h>

#ifdef LOG_WITH_THREAD_ID
#define INF_LOG(fmt, ...)       simulator_console_log("[T:%-4d]" fmt "\r\n", pthread_self(), ##__VA_ARGS__);
#define DBG_LOG(fmt, ...)       simulator_console_log("[T:%-4d]" fmt "\r\n", pthread_self(), ##__VA_ARGS__);
#define WRN_LOG(fmt, ...)       simulator_console_log("[T:%-4d]" fmt "\r\n", pthread_self(), ##__VA_ARGS__);
#define ERR_LOG(fmt, ...)       simulator_console_log("[T:%-4d]" fmt "\r\n", pthread_self(), ##__VA_ARGS__);
#define TRC_LOG(fmt, ...)       simulator_console_log("[T:%-4d]" fmt "\r\n", pthread_self(), ##__VA_ARGS__);
#else
#define INF_LOG(fmt, ...)       simulator_console_log(fmt"\r\n", ##__VA_ARGS__);
#define DBG_LOG(fmt, ...)       simulator_console_log(fmt"\r\n", ##__VA_ARGS__);
#define WRN_LOG(fmt, ...)       simulator_console_log(fmt"\r\n", ##__VA_ARGS__);
#define ERR_LOG(fmt, ...)       simulator_console_log(fmt"\r\n", ##__VA_ARGS__);
#define TRC_LOG(fmt, ...)       simulator_console_log(fmt"\r\n", ##__VA_ARGS__);
#endif

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

void simulator_console_log(const char* format, ...);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _INCLUDE_LOG_H_
