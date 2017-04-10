#ifndef _VRS_RESOURCE_ACQUIRER_H_
#define _VRS_RESOURCE_ACQUIRER_H_

#include "User.h"
#include "Group.h"
#include "ResourceFolder.h"
#include "ResourceFile.h"
#include "ResourceView.h"

#include <unordered_map>

namespace vrs {

class ResourceAcquirer {
public:
    enum ResourceAcquirer_t {
        PSQL
    };

    virtual bool Connect() = 0;
    virtual bool GetUsers(std::unordered_map<uint64_t, User*>& users) const = 0;
    virtual bool GetGroups(std::unordered_map<uint64_t, Group*>&  groups) const = 0;

    virtual bool GetFolders(std::unordered_map<uint64_t, ResourceFolder*>& folders,
                            const std::unordered_map<uint64_t, User*>& users,
                            const std::unordered_map<uint64_t, Group*>&  groups) = 0;

    virtual bool GetFiles(std::unordered_map<uint64_t, ResourceFile*>& files,
                            const std::unordered_map<uint64_t, User*>& users,
                            const std::unordered_map<uint64_t, Group*>&  groups) = 0;

    virtual bool GetViews(std::unordered_map<uint64_t, ResourceView*>& views) = 0;


    virtual ResourceAcquirer_t type() const  = 0;

    virtual ~ResourceAcquirer() {}

};

} // vrs

#endif /* _VRS_RESOURCE_ACQUIRER_H_ */
