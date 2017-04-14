#include "InetUtils.h"

#include <netdb.h>
 #include <arpa/inet.h>

namespace vrs {


bool InetUtils::GetIPAddressFromHost(const std::string& hostname, std::string& ip)
{
    const hostent* he = gethostbyname(hostname.c_str());

    if (he == nullptr) return false;

    ip = inet_ntoa(*((struct in_addr**) he->h_addr_list)[0]);

    return true;
}


} // vrs
