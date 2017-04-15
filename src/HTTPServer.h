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
    void shut_down(const boost::system::error_code& error, int signal,
                   std::shared_ptr<http_server> p_server_instance);

    HTTPRequestHandler   requestHandler_;
    http_server::options options_;
    std::shared_ptr<http_server>  server_;

    std::shared_ptr<boost::asio::io_service> io_service_;

    // SSL
    std::shared_ptr<boost::asio::ssl::context> ctx_;
};

}

#endif /* _VRS_HTTP_SERVER_H_ */
