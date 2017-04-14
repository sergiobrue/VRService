#include "HTTPServer.h"
#include "Config.h"

namespace vrs {

HTTPServer::HTTPServer(const std::string address, const std::string port)
    : options_(requestHandler_)
    , ctx_(std::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::tlsv12_server))
{

    ctx_->set_options(boost::asio::ssl::context::default_workarounds
                      | boost::asio::ssl::context::no_sslv2
                      | boost::asio::ssl::context::no_sslv3
                      | boost::asio::ssl::context::no_tlsv1 );

    options_.address(address).port(port);

    try
    {
        // ctx.set_password_callback(password_callback);
        ctx_->use_certificate_chain_file(Config::instance().ssl_chain_file_path());
        ctx_->use_certificate_file(Config::instance().ssl_cert_file_path(), boost::asio::ssl::context::pem);
        ctx_->use_private_key_file(Config::instance().ssl_private_key_file_path(), boost::asio::ssl::context::pem);
        // ctx.use_tmp_dh_file("dh512.pem");
        options_.context(ctx_);
    }
    catch(std::exception& e)
    {
        VRS_LOG_ERROR("SSL Certs Error: %s - Not using SSL", e.what());
    }

    server_ = std::make_shared<http_server>(options_);
}

void HTTPServer::Run()
{
    // TODO - Async multithread
    server_->run();
}

}
