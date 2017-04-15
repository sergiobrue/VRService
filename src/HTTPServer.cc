#include "HTTPServer.h"
#include "Config.h"

#include <signal.h>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/network/utils/thread_group.hpp>

namespace vrs {

HTTPServer::HTTPServer(const std::string address, const std::string port)
    : options_(requestHandler_)
    , io_service_(std::make_shared<boost::asio::io_service>())
    , ctx_(std::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::sslv23))
{
    ctx_->set_options(boost::asio::ssl::context::default_workarounds |
                      boost::asio::ssl::context::no_sslv2);

    const unsigned n_cores = std::thread::hardware_concurrency();
    VRS_LOG_DEBUG("Number of cores/threads: %u", n_cores);

    options_.address(address)
        .port(port)
        .io_service(io_service_)
        .reuse_address(true)
        .thread_pool(std::make_shared<boost::network::utils::thread_pool>(n_cores));

    try
    {
        ctx_->use_certificate_chain_file(Config::instance().ssl_chain_file_path());
        ctx_->use_certificate_file(Config::instance().ssl_cert_file_path(), boost::asio::ssl::context::pem);
        ctx_->use_private_key_file(Config::instance().ssl_private_key_file_path(), boost::asio::ssl::context::pem);
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
    boost::asio::signal_set signals(*io_service_, SIGINT, SIGTERM);

    signals.async_wait([=] (boost::system::error_code const &ec, int signal)
                       {
                           shut_down(ec, signal, server_);
                       });
    server_->run();
}


void HTTPServer::shut_down(const boost::system::error_code& error, int signal,
                           std::shared_ptr<http_server> p_server_instance)
{
    VRS_LOG_DEBUG("Signal captured... Stopping Server");
    if (!error) server_->stop();
}

}
