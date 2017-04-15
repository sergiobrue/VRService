#ifndef _VRS_HTTP_REQUEST_METHOD_HANDLER_H_
#define _VRS_HTTP_REQUEST_METHOD_HANDLER_H_

#include <boost/network/include/http/server.hpp>

#include <iostream>

namespace vrs {

class HTTPRequestHandler;

using http_server = boost::network::http::server<HTTPRequestHandler>;


class HTTPRequestMethodHandler
{
public:
    virtual void ProcessRequest (http_server::request const& request,
                                 http_server::connection_ptr connection,
                                 std::string& msg) = 0;

protected:
    HTTPRequestMethodHandler();
    virtual ~HTTPRequestMethodHandler();
};


} // vrs

#endif /* _VRS_HTTP_REQUEST_METHOD_HANDLER_H_ */
