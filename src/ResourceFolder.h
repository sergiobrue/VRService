#ifndef _VRS_RESOURCE_FOLDER_H_
#define _VRS_RESOURCE_FOLDER_H_

#include "Resource.h"
#include <vector>

namespace vrs {

class ResourceFile;

class ResourceFolder : public Resource
{
public:
    ResourceFolder(const User* owner,
                   const Group* group,
                   const Permissions permissions,
                   const uint64_t id_,
                   const std::string& name_,
                   const std::string& description,
                   const std::string& uri_thumbnail,
                   const std::string& uri_scene,
                   const uint64_t parent);

    virtual ~ResourceFolder() final;

    const std::string& description() const { return description_; }
    const std::string& uri_thumbnail() const { return uri_thumbnail_; }
    const std::string& uri_scene() const { return uri_scene_; }
    uint64_t parent() const { return parent_; }


    void PushFile(const ResourceFile* file);
    void PushFolder(const ResourceFolder* folder);

    const std::vector<const ResourceFolder*>& child_folders() const { return child_folders_; }
    const std::vector<const ResourceFile*>& child_files() const { return child_files_; }

    const char* c_str() const;

    virtual const json as_json(const User* user) const final;

private:
    const std::string description_;
    const std::string uri_thumbnail_;
    const std::string uri_scene_;
    const uint64_t    parent_;

    std::vector<const ResourceFolder*> child_folders_;
    std::vector<const ResourceFile*> child_files_;
};

}

#endif /* _VRS_RESOURCE_FOLDER_H_ */
