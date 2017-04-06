#include "HTTPServer.h"

namespace VRS {

HTTPServer::HTTPServer(const std::string address, const std::string port)
    : options_(requestHandler_)
    , server_(options_.address(address).port(port))
{
}

void HTTPServer::Run()
{
    server_.run();
}

}
