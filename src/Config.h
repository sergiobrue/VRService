#ifndef _VRS_CONFIG_H_
#define _VRS_CONFIG_H_

#include "ResourceAcquirer.h"

#include <string>
#include <stdint.h>


namespace vrs {

class Config
{
public:
    Config();
    ~Config();

    std::string GetConnectionString() const;

private:
    std::string resource_acquirer_name_;
    std::string resource_acquirer_user_;
    std::string resource_acquirer_password_;
    std::string resource_acquirer_db_;

    uint16_t resource_acquirer_port_;
    bool resource_acquirer_require_ssl_;
};


} //vrs


#endif /* _VRS_CONFIG_H_ */
