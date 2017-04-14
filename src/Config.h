#ifndef _VRS_CONFIG_H_
#define _VRS_CONFIG_H_

#include "ResourceAcquirer.h"

#include <string>
#include <stdint.h>


namespace vrs {

class Config
{
public:
    const std::string GetConnectionString() const;

    const std::string& ssl_chain_file_path() const { return ssl_chain_file_path_; }
    const std::string& ssl_cert_file_path() const { return ssl_cert_file_path_; }
    const std::string& ssl_private_key_file_path() const { return ssl_private_key_file_path_; }

    static Config& instance()
    {
        static Config instance_;
        return instance_;
    }

    bool is_OK() const { return config_ok_; }

private:
    Config();
    ~Config();


    std::string resource_acquirer_name_;
    std::string resource_acquirer_user_;
    std::string resource_acquirer_password_;
    std::string resource_acquirer_db_;
    std::string resource_acquirer_host_;
    uint16_t    resource_acquirer_port_;
    bool        resource_acquirer_require_ssl_;

    std::string ssl_chain_file_path_;
    std::string ssl_cert_file_path_;
    std::string ssl_private_key_file_path_;

    bool config_ok_;
};


} //vrs


#endif /* _VRS_CONFIG_H_ */
