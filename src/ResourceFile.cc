#include "ResourceFile.h"

namespace vrs {

const std::string ResourceFile::FileTypes_Str[MAX_FILETYPE] =
{
    "video"
};

ResourceFile::ResourceFile(const User* owner,
                           const Group* group,
                           const Permissions permissions,
                           const uint64_t id,
                           const FileType_t type,
                           const std::string name,
                           const std::string description,
                           const std::string uri_thumbnail,
                           const std::string uri_file)
    : Resource(owner, group, permissions)
    , id_(id)
    , type_(type)
    , name_(name)
    , description_(description)
    , uri_thumbnail_(uri_thumbnail)
    , uri_file_(uri_file)
{
}

ResourceFile::~ResourceFile()
{
}

void ResourceFile::Update_json() const
{
    json_["id"] = id_;
    json_["type"] = FileTypes_Str[type_];
    json_["name"] = name_;
    json_["description"] = description_;
    json_["uri_thumbnail"] = uri_thumbnail_;
    json_["uri_file"] = uri_file_;
}

}
