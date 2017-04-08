#ifndef _VRS_RESOURCE_H_
#define _VRS_RESOURCE_H_

#include "json.hpp"
#include <stdint.h>

#include "User.h"
#include "Group.h"


using json = nlohmann::json;

namespace vrs {

struct Permissions
{
    bool user_read   : 1;
    bool user_write  : 1;
    bool user_show   : 1;
    bool group_read  : 1;
    bool group_write : 1;
    bool group_show  : 1;
};

class Resource
{
public:
    Resource(const User* owner,
             const Group* group,
             const Permissions permissions)
        : owner_(owner)
        , group_(group)
        , permissions_(permissions)
        , json_updated_(false)
    {}

    virtual ~Resource() {}

    virtual const json& as_json() const final
    {
        if (!json_updated_)
        {
            Update_json();
            json_updated_ = true;
        }
        return json_;
    }

    const User* owner() const { return owner_; }
    const Group* group() const { return group_; }
    const Permissions permissions() const { return permissions_; }

protected:
    virtual void Update_json() const = 0;
private:
    const User*  owner_;
    const Group* group_;
    const Permissions permissions_;
protected:
    mutable json json_;
private:
    mutable bool json_updated_;
};


}


#endif /* _VRS_RESOURCE_H_ */
