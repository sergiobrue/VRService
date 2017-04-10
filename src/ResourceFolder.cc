#include "ResourceFolder.h"
#include "ResourceFile.h"

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
    : Resource(owner, group, permissions, name)
    , id_(id)
    , description_(description)
    , uri_thumbnail_(uri_thumbnail)
    , uri_scene_(uri_scene)
    , parent_(parent)
{
}

ResourceFolder::~ResourceFolder()
{
}

void ResourceFolder::Update_json() const
{
    json_["id"] = id_;
    json_["name"] = name();
    json_["description"] = description_;
    json_["uri_thumbnail"] = uri_thumbnail_;
    json_["uri_scene"] = uri_scene_;

    json folders_json;

    for_each(child_folders_.begin(), child_folders_.end(),
             [&folders_json](auto it)
             {
                 json tuple;
                 tuple["id"] = it->id();
                 tuple["name"] = it->name();
                 tuple["uri_thumbmail"] = it->uri_thumbnail();
                 folders_json.push_back(tuple);
             }
        );

    json_["folders"] = folders_json;

    json files_json;

    for_each(child_files_.begin(), child_files_.end(),
             [&files_json](auto it)
             {
                 files_json.push_back(it->as_json());
             }
        );

    json_["files"] = folders_json;

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
             uintmax_t(id_), name().c_str(), description_.c_str(), uri_thumbnail_.c_str(), uri_scene_.c_str(), uintmax_t(parent_),
             owner()->c_str(), group()->c_str(), permissions().c_str());

    return str;
}


}
