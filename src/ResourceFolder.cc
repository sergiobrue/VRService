#include "ResourceFolder.h"

namespace vrs {

ResourceFolder::ResourceFolder(const User* owner,
                               const Group* group,
                               const Permissions permissions,
                               const uint64_t id,
                               const std::string& name,
                               const std::string& description,
                               const std::string& uri_thumbnail,
                               const std::string& uri_scene,
                               const std::vector<Resource*>& childs)
    : Resource(owner, group, permissions)
    , id_(id)
    , name_(name)
    , description_(description)
    , uri_thumbnail_(uri_thumbnail)
    , uri_scene_(uri_scene)
    , childs_(childs)
{
}

ResourceFolder::~ResourceFolder()
{
}

void ResourceFolder::Update_json() const
{
    json_["id"] = id_;
    json_["name"] = name_;
    json_["description"] = description_;
    json_["uri_thumbnail"] = uri_thumbnail_;
    json_["uri_scene"] = uri_scene_;
}

void ResourceFolder::UpdateChilds(const std::vector<Resource*>& childs)
{
    childs_ = childs;
}


}
