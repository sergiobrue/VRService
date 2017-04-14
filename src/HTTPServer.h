#ifndef _VRS_HTTP_SERVER_H_
#define _VRS_HTTP_SERVER_H_

#include "HTTPRequestHandler.h"

#include <boost/asio/ssl.hpp>

namespace vrs {

class HTTPServer {
public:
    HTTPServer(const std::string address, const std::string port);

    void Run();

private:
    HTTPRequestHandler   requestHandler_;
    http_server::options options_;
    http_server          server_;


    // SSL
    boost::asio::ssl::context ctx_;
};

}

#endif /* _VRS_HTTP_SERVER_H_ */
