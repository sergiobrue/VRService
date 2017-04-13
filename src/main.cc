#include "HTTPServer.h"
#include "Logger.h"
#include "ResourceMapper.h"


#include <iostream>

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int  log_level = 0;
    bool to_stdout = false;

    int c;

    opterr = 0;

    while ((c = getopt(argc, argv, "sl:")) != -1)
    {
        switch (c)
        {
            case 's':
                to_stdout = true;
                break;
            case 'l':
                log_level= atoi(optarg);
                if (log_level > 8 || log_level < 0)
                    log_level = 0;
                break;
            default:
                break;
        }
    }

    if (to_stdout) vrs::Logger::instance().EnableStdout();
    vrs::Logger::instance().SetLevel(log_level);

    try
    {
        vrs::ResourceMapper::instance();
        vrs::HTTPServer http_server("0.0.0.0", "31337");
        VRS_LOG_DEBUG("\nRunning Server...\n");
        http_server.Run();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    return 0;
}
