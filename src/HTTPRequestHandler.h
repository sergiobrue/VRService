#ifndef _VRS_HTTP_REQUEST_HANDLER_H_
#define _VRS_HTTP_REQUEST_HANDLER_H_


#include <boost/network/include/http/server.hpp>
#include <boost/network/utils/thread_pool.hpp>

namespace VRS {

class HTTPRequestHandler;

typedef boost::network::http::server<HTTPRequestHandler> http_server;

class HTTPRequestHandler
{
};


}

#endif /* _VRS_HTTP_REQUEST_HANDLER_H_ */

