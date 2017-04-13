#ifndef _VRS_LOGGER_H_
#define _VRS_LOGGER_H_

#include <stdio.h>
#include <syslog.h>
#include <stdarg.h>

namespace vrs {

using LogLevel_t =  decltype(LOG_INFO);

#define LOGD(...) vrs::Logger::instance().log(LOG_DEBUG, __VA_ARGS__);
#define LOGI(...) vrs::Logger::instance().log(LOG_INFO, __VA_ARGS__);

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

private:

    Logger();
    ~Logger();

    LogLevel_t log_level_;
    bool print_to_stdout_;
};


}

#endif /* _VRS_LOGGER_H_ */
