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
                           const std::string uri_file,
                           const uint16_t parent_folder)
: Resource(owner, group, permissions, id, name)
    , type_(type)
    , description_(description)
    , uri_thumbnail_(uri_thumbnail)
    , uri_file_(uri_file)
    , parent_folder_(parent_folder)
{
}

ResourceFile::~ResourceFile()
{
}

const json ResourceFile::as_json(const User* user) const
{
    json json_out;
    json_out["id"] = id();
    json_out["type"] = FileTypes_Str[type_];
    json_out["name"] = name();
    json_out["description"] = description_;
    json_out["uri_thumbnail"] = uri_thumbnail_;
    json_out["uri_file"] = uri_file_;
    return json_out;
}


const char* ResourceFile::c_str() const
{
    static char str[4098] = {0};
    snprintf(str, sizeof(str), "(id⁼%ju, name=\"%s\", description=\"%s\", uri_thumbnail=\"%s\", uri_scene=\"%s\", parent=%ju, owner=%s, group=%s, perms=%s)",
             uintmax_t(id()), name().c_str(), description_.c_str(), uri_thumbnail_.c_str(), uri_file_.c_str(), uintmax_t(parent_folder_),
             owner()->c_str(), group()->c_str(), permissions().c_str());

    return str;
}


}
