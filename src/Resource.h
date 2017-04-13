#ifndef _VRS_RESOURCE_H_
#define _VRS_RESOURCE_H_

#include "json.hpp"
#include <stdint.h>

#include "User.h"
#include "Group.h"
#include "Permissions.h"

using json = nlohmann::json;

namespace vrs {


class Resource
{
public:
    Resource(const User* owner,
             const Group* group,
             const Permissions permissions,
             const uint64_t id,
             const std::string& name)
        : owner_(owner)
        , group_(group)
        , permissions_(permissions)
        , id_(id)
        , name_(name)
    {}

    virtual ~Resource() {}

    virtual const json as_json(const User* user) const = 0;

    const User* owner() const { return owner_; }
    const Group* group() const { return group_; }
    const Permissions permissions() const { return permissions_; }
    uint64_t id() const { return id_; }
    const std::string& name() const { return name_; }

private:
    const User*  owner_;
    const Group* group_;
    const Permissions permissions_;
    const uint64_t id_;
    const std::string name_;
};


}


#endif /* _VRS_RESOURCE_H_ */
