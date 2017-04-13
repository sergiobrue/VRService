#ifndef _VRS_RESOURCE_FILE_H_
#define _VRS_RESOURCE_FILE_H_


#include "Resource.h"

namespace vrs {

class ResourceFile : public Resource {
public:
    enum FileType_t : uint64_t {
        VIDEO,
        // -- Add above this --
        MAX_FILETYPE
    };

    ResourceFile(const User* owner,
                 const Group* group,
                 const Permissions permissions,
                 const uint64_t id,
                 const FileType_t type,
                 const std::string name,
                 const std::string description,
                 const std::string uri_thumbnail,
                 const std::string uri_file,
                 const uint16_t parent_folder);

    virtual ~ResourceFile() final;

    FileType_t  type() const { return type_; }
    const std::string& description() const { return description_; }
    const std::string& uri_thumbnail() const { return uri_thumbnail_; }
    const std::string& uri_file() const { return uri_file_; }

    uint64_t parent_folder() const { return parent_folder_; }

    const char* c_str() const;

    virtual const json as_json(const User* user) const final;

private:
    static const std::string FileTypes_Str[MAX_FILETYPE];

    const FileType_t  type_;
    const std::string description_;
    const std::string uri_thumbnail_;
    const std::string uri_file_;
    const uint16_t parent_folder_;
};

}

#endif /* _VRS_RESOURCE_FILE_H_ */
