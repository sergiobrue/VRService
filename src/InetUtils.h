#ifndef _VRS_INET_UTILS_H_
#define _VRS_INET_UTILS_H_

#include <string>

namespace vrs {

class InetUtils {
public:
    static bool GetIPAddressFromHost(const std::string& hostname, std::string& ip);
};

} // vrs

#endif /* _VRS_INET_UTILS_H_ */
