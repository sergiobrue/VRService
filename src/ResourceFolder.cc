#include "ResourceFolder.h"
#include "ResourceFile.h"
#include "Logger.h"

namespace vrs {

ResourceFolder::ResourceFolder(const User* owner,
                               const Group* group,
                               const Permissions permissions,
                               const uint64_t id,
                               const std::string& name,
                               const std::string& description,
                               const std::string& uri_thumbnail,
                               const std::string& uri_scene,
                               const uint64_t parent)
    : Resource(owner, group, permissions, id, name)
    , description_(description)
    , uri_thumbnail_(uri_thumbnail)
    , uri_scene_(uri_scene)
    , parent_(parent)
{
}

ResourceFolder::~ResourceFolder()
{
}

const json ResourceFolder::as_json(const User* user) const
{
    VRS_LOG_DEBUG("Updating JSON for folder [%s] ", name().c_str());

    json json_out;

    json_out["id"] = id();
    json_out["name"] = name();
    json_out["description"] = description_;
    json_out["uri_thumbnail"] = uri_thumbnail_;
    json_out["uri_scene"] = uri_scene_;

    for_each(child_folders_.begin(), child_folders_.end(),
             [&json_out, this](auto it)
             {
                 if (it->id() != this->id())
                     json_out["folders"].push_back(it->as_json(nullptr));
             }
        );

    for_each(child_files_.begin(), child_files_.end(),
             [&json_out, this](auto it)
             {
                 json_out["files"].push_back(it->as_json(nullptr));
             }
        );
    return json_out;
}

void ResourceFolder::PushFile(const ResourceFile* file)
{
    child_files_.push_back(file);
}

void ResourceFolder::PushFolder(const ResourceFolder* folder)
{
    child_folders_.push_back(folder);
}

const char* ResourceFolder::c_str() const
{
    static char str[4098] = {0};
    snprintf(str, sizeof(str), "(id⁼%ju, name=\"%s\", description=\"%s\", uri_thumbnail=\"%s\", uri_scene=\"%s\", parent=%ju, owner=%s, group=%s, perms=%s)",
             uintmax_t(id()), name().c_str(), description_.c_str(), uri_thumbnail_.c_str(), uri_scene_.c_str(), uintmax_t(parent_),
             owner()->c_str(), group()->c_str(), permissions().c_str());

    return str;
}


}
