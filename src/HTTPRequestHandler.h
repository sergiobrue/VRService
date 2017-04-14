#ifndef _VRS_REQUEST_HANDLER_H_
#define _VRS_REQUEST_HANDLER_H_

#include "Logger.h"
#include "HTTPRequestGETHandler.h"

#include <boost/network/protocol/http/server.hpp>
#include <iostream>


namespace vrs {

class HTTPRequestHandler
{
public:
    void operator() (http_server::request const& request,
                     http_server::connection_ptr connection)
    {

        VRS_LOG_INFO("Request: [%s][%s]",
                     request.method.c_str(), request.destination.c_str());

        TimeMeasurer time_measurer;

        const std::map<std::string, std::string> headers =
            {{"Content-Type", "text/plain"}};

        std::string returned_msg;

        switch (request.method.c_str()[0])
        {
            case 'G': // GET
            {
                HTTPRequestGETHandler GET_handler;
                GET_handler.ProcessRequest(request, connection, returned_msg);
                break;
            }
            case 'P': // POST, PUT, PATCH
            {
                switch (request.method.c_str()[1])
                {
                    case 'O': // POST
                        break;
                    case 'U': // PUT
                        break;
                    case 'A': // PATCH
                        break;
                }
            }
            case 'D': // DELETE
            {
                break;
            }
        }

        connection->set_headers(headers);
        connection->write(returned_msg);

        VRS_LOG_INFO("Request took %f seconds",
                     time_measurer.diff_with_last_call_seconds());
    }

    void log(http_server::string_type const& info)
    {
        VRS_LOG_DEBUG(info.c_str());
    }
};




}

#endif /* _VRS_REQUEST_HANDLER_H_ */
