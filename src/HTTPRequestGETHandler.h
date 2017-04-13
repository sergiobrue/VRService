#ifndef _HTTP_REQUEST_GET_HANDLER_H_
#define _HTTP_REQUEST_GET_HANDLER_H_

#include "HTTPRequestMethodHandler.h"

#include "Logger.h"
#include "ResourceMapper.h"
#include "TimeMeasurer.h"

namespace vrs {

class HTTPRequestGETHandler
{
public:
    virtual void ProcessRequest(http_server::request const& request,
                                http_server::connection_ptr connection,
                                std::string& msg) final
    {
        const ResourceFolder* folder = ResourceMapper::instance().FindFolderFromURI(request.destination);

        if (folder)
        {
            msg = folder->as_json(nullptr).dump();
            connection->set_status(http_server::connection::ok);
            VRS_LOG_DEBUG("Found: [%s]", folder->c_str());
        }
        else
        {
            VRS_LOG_DEBUG("Request [%s] Not found", request.destination.c_str());
            connection->set_status(http_server::connection::not_found);
            msg = "404 Not found\n";
        }

    }

    virtual ~HTTPRequestGETHandler() {}
};

} // vrs


#endif /* _HTTP_REQUEST_GET_HANDLER_H_ */
