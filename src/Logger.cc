#include "Logger.h"

namespace vrs {

LogLevel_t Logger::log_level_ = LOG_ERR;


Logger::Logger()
    : print_to_stdout_(false)
{
}


Logger::~Logger()
{
}


void Logger::log(decltype(LOG_INFO) log_level, const char* msg, ...)
{
    va_list args;
    va_start(args, msg);

    syslog(log_level_, msg, args);

    if (log_level <= log_level_ && print_to_stdout_)
    {
        static char fmt_msg[4098];
        vsnprintf(fmt_msg, sizeof(fmt_msg), msg, args);
        std::lock_guard<std::mutex> lock_(write_mutex_);
        printf("%s\n", fmt_msg);
    }
    va_end(args);
}


void Logger::EnableStdout()
{
    print_to_stdout_ = true;
}


void Logger::DisableStdout()
{
    print_to_stdout_ = false;
}


void Logger::SetLevel(const LogLevel_t level)
{
    log_level_ = level;
}


}
