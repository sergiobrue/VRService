#ifndef _VRS_RESOURCE_FOLDER_H_
#define _VRS_RESOURCE_FOLDER_H_

#include "Resource.h"
#include <vector>

namespace vrs {

class ResourceFolder : public Resource
{
public:
    ResourceFolder(const User* owner,
                   const Group* group,
                   const Permissions permissions,
                   const uint64_t id_,
                   const std::string& name_,
                   const std::string& description_,
                   const std::string& uri_thumbnail_,
                   const std::string& uri_scene_,
                   const std::vector<Resource*>& childs);

    virtual ~ResourceFolder() final;

    void UpdateChilds(const std::vector<Resource*>& childs);

private:
    virtual void Update_json() const final;

    const uint64_t    id_;
    const std::string name_;
    const std::string description_;
    const std::string uri_thumbnail_;
    const std::string uri_scene_;

    std::vector<Resource*> childs_;
};

}

#endif /* _VRS_RESOURCE_FOLDER_H_ */
