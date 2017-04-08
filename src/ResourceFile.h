#ifndef _VRS_RESOURCE_FILE_H_
#define _VRS_RESOURCE_FILE_H_


#include "Resource.h"

namespace vrs {

class ResourceFile : public Resource {
public:
    enum FileType_t {
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
                 const std::string uri_file);

    virtual ~ResourceFile() final;

private:
    static const std::string FileTypes_Str[MAX_FILETYPE];

    virtual void Update_json() const final;

    const uint64_t    id_;
    const FileType_t  type_;
    const std::string name_;
    const std::string description_;
    const std::string uri_thumbnail_;
    const std::string uri_file_;
};

}

#endif /* _VRS_RESOURCE_FILE_H_ */
