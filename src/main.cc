#include "HTTPServer.h"
#include "Logger.h"
#include "ResourceMapper.h"


#include <iostream>

int main(int argc, char *argv[])
{
#if 1
    vrs::Logger::instance().EnableStdout();
    vrs::Logger::instance().SetLevel(LOG_DEBUG);
#endif

    try
    {
        vrs::ResourceMapper::instance();
        vrs::HTTPServer http_server("0.0.0.0", "31337");
        LOGD("\nRunning Server...\n");
        http_server.Run();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    return 0;
}
