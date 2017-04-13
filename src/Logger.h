#ifndef _VRS_LOGGER_H_
#define _VRS_LOGGER_H_

#include <stdio.h>
#include <syslog.h>
#include <stdarg.h>

#include "CompilerHints.h"

namespace vrs {

using LogLevel_t =  decltype(LOG_INFO);

#define VRS_LOG(LOG_LEVEL, ...)                                 \
    if (unlikely(vrs::Logger::log_level() >= LOG_LEVEL))        \
    {                                                           \
        vrs::Logger::instance().log(LOG_LEVEL, __VA_ARGS__);    \
    }

#define VRS_LOG_DEBUG(...) VRS_LOG(LOG_DEBUG, __VA_ARGS__)
#define VRS_LOG_INFO(...) VRS_LOG(LOG_INFO, __VA_ARGS__)
#define VRS_LOG_ERROR(...) VRS_LOG(LOG_ERROR, __VA_ARGS__)

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
};


}

#endif /* _VRS_LOGGER_H_ */
