#ifndef _VRS_RESOURCE_ACQUIRER_H_
#define _VRS_RESOURCE_ACQUIRER_H_

#include "User.h"
#include "Group.h"
#include "ResourceFolder.h"

#include <unordered_map>

namespace vrs {

class ResourceAcquirer {
public:
    enum ResourceAcquirer_t {
        PSQL
    };

    virtual bool Connect() = 0;
    virtual bool GetUsers(std::unordered_map<uint64_t, User*>& users) const = 0;
    virtual bool GetGroups(std::vector<Group*>& groups) const = 0;

    virtual ResourceAcquirer_t type() const  = 0;

    virtual ~ResourceAcquirer() {}

    // virtual bool GetFolders(std::vector<ResourceFolder*> folders) = 0;
    // virtual bool GetFiles(std::vector<ResourceFolder*> folders) = 0;
    // virtual bool GetViews(std::vector<ResourceView*> folders) = 0;
};

} // vrs

#endif /* _VRS_RESOURCE_ACQUIRER_H_ */
