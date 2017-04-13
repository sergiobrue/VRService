#ifndef _VRS_REQUEST_HANDLER_H_
#define _VRS_REQUEST_HANDLER_H_

#include "Logger.h"
#include "ResourceMapper.h"
#include "TimeMeasurer.h"

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

        LOGI("Request: [%s][%s]", request.method.c_str(), request.destination.c_str());

        TimeMeasurer time_measurer;

        std::map<std::string, std::string> headers = { {"Content-Type", "text/plain"} };

        std::string msg;

        if (request.method.c_str()[0]=='G')
        {
            // TODO - Method Handler.
            // GET method
            const ResourceFolder* folder = ResourceMapper::instance().FindFolderFromURI(request.destination);

            if (folder)
            {
                msg = folder->as_json().dump();

                connection->set_status(http_server::connection::ok);

                LOGD("Found: [%s]", folder->c_str());
            }
            else
            {
                LOGD("Request [%s] Not found", request.destination.c_str());
                connection->set_status(http_server::connection::not_found);
                msg = "404 Not found\n";
            }
        }

        connection->set_headers(headers);
        connection->write(msg);

        LOGD("Request took %f seconds",
             time_measurer.diff_with_last_call_seconds());
    }

    void log(http_server::string_type const& info)
    {
        std::cerr << "ERROR: " << info << '\n';
    }
};




}

#endif /* _VRS_REQUEST_HANDLER_H_ */
