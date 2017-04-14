#include "HTTPServer.h"
#include "Config.h"

namespace vrs {

HTTPServer::HTTPServer(const std::string address, const std::string port)
    : options_(requestHandler_)
    , server_(options_.address(address).port(port))
    , ctx_(boost::asio::ssl::context::sslv23)
{
    ctx_.set_options(boost::asio::ssl::context::default_workarounds |
                     boost::asio::ssl::context::no_sslv2 |
                     boost::asio::ssl::context::single_dh_use);

    try
    {
        // ctx.set_password_callback(password_callback);
        ctx_.use_certificate_chain_file(Config::instance().ssl_chain_file_path());
        ctx_.use_certificate_file(Config::instance().ssl_cert_file_path(), boost::asio::ssl::context::pem);
        ctx_.use_private_key_file(Config::instance().ssl_private_key_file_path(), boost::asio::ssl::context::pem);
        // ctx.use_tmp_dh_file("dh512.pem");
    }
    catch(std::exception& e)
    {
        VRS_LOG_ERROR("SSL Certs Error: %s", e.what());
    }
}

void HTTPServer::Run()
{
    // TODO - Async multithread
    server_.run();
}

}

