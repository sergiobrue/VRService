#ifndef _VRS_URI_UTILS_H_
#define _VRS_URI_UTILS_H_

#include <vector>
#include <string>

namespace vrs {

class URIUtils
{
public:
    URIUtils() = delete;
    ~URIUtils() = delete;

    static void URIToFolders(const std::string& uri, std::vector<std::string>& folders);
};

} //vrs


#endif /* _VRS_URI_UTILS_H_ */
