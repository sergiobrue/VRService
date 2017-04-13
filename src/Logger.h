#ifndef _VRS_LOGGER_H_
#define _VRS_LOGGER_H_

#include <stdio.h>
#include <syslog.h>
#include <stdarg.h>

#include <mutex>

#include "CompilerHints.h"

// LOG_EMERG    0    /* system is unusable */
// LOG_ALERT    1    /* action must be taken immediately */
// LOG_CRIT     2    /* critical conditions */
// LOG_ERR      3    /* error conditions */
// LOG_WARNING  4    /* warning conditions */
// LOG_NOTICE   5    /* normal but significant condition */
// LOG_INFO     6    /* informational */
// LOG_DEBUG    7    /* debug-level messages */

namespace vrs {

using LogLevel_t =  decltype(LOG_INFO);

#define VRS_LOG(LOG_LEVEL, ...)                                 \
    if (unlikely(vrs::Logger::log_level() >= LOG_LEVEL))        \
    {                                                           \
        vrs::Logger::instance().log(LOG_LEVEL, __VA_ARGS__);    \
    }

#define VRS_LOG_DEBUG(...) VRS_LOG(LOG_DEBUG, __VA_ARGS__)
#define VRS_LOG_INFO(...) VRS_LOG(LOG_INFO, __VA_ARGS__)
#define VRS_LOG_ERROR(...) VRS_LOG(LOG_ERR, __VA_ARGS__)

class Logger {
public:
    static Logger& instance()
    {
        static Logger instance_;
        return instance_;
    }

    void log(decltype(LOG_INFO) log_level, const char* msg, ...);

    void EnableStdout();
    void DisableStdout();

    void SetLevel(const LogLevel_t level);
    static LogLevel_t log_level() { return log_level_; };

private:

    Logger();
    ~Logger();

    static LogLevel_t log_level_;
    bool print_to_stdout_;

    // Only used for printf - syslog call is mutex already
    std::mutex write_mutex_;
};


}

#endif /* _VRS_LOGGER_H_ */
