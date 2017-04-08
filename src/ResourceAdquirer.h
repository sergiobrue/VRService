#ifndef _VRS_RESOURCE_ADQUIRER_H_
#define _VRS_RESOURCE_ADQUIRER_H_

#include "User.h"
#include "Group.h"
#include "ResourceFolder.h"

namespace vrs {

class ResourceAdquirer {
public:
    virtual bool Connect() = 0;
    virtual bool GetUsers(std::vector<User*>& users) const = 0;
    virtual bool GetGroups(std::vector<Group*>& groups) const = 0;

    virtual ~ResourceAdquirer() {}

    // virtual bool GetFolders(std::vector<ResourceFolder*> folders) = 0;
    // virtual bool GetFiles(std::vector<ResourceFolder*> folders) = 0;
    // virtual bool GetViews(std::vector<ResourceView*> folders) = 0;
};

} // vrs

#endif /* _VRS_RESOURCE_ADQUIRER_H_ */
