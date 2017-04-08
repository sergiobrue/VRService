#ifndef _VRS_REQUEST_HANDLER_H_
#define _VRS_REQUEST_HANDLER_H_

#include "Logger.h"

#include <boost/network/protocol/http/server.hpp>
#include <iostream>

namespace vrs {

class HTTPRequestHandler;

typedef boost::network::http::server<HTTPRequestHandler> http_server;

class HTTPRequestHandler
{
public:
    void operator() (http_server::request const& request,
                     http_server::connection_ptr connection)
    {
        std::map<std::string, std::string> headers = {
            {"Content-Type", "text/plain"},
        };

        std::string msg("Destination (\""+request.destination+"\")\n");

        LOGD(msg.c_str());

        connection->set_status(http_server::connection::ok);
        connection->set_headers(headers);
        connection->write(msg);
    }

    void log(http_server::string_type const& info)
    {
        std::cerr << "ERROR: " << info << '\n';
    }
};




}

#endif /* _VRS_REQUEST_HANDLER_H_ */

