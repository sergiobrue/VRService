#include "HTTPServer.h"
#include <iostream>

int main(int argc, char *argv[])
{
    try
    {
        VRS::HTTPServer http_server("0.0.0.0", "31337");
        http_server.Run();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    return 0;
}
