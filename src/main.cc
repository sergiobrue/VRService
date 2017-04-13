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
    int  log_level = LOG_ERR;
    bool to_stdout = false;

    int c;
    while ((c = getopt(argc, argv, "sl:")) != -1)
    {
        if (c=='s') to_stdout = true;
        else if (c=='l') log_level= atoi(optarg);
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
        VRS_LOG_ERROR(e.what());
        return -1;
    }
    catch (...)
    {
        VRS_LOG_ERROR("Unkown Exception");
        return -2;
    }

    return 0;
}
