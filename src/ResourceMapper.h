#ifndef _RESOURCE_MAPPER_H_
#define _RESOURCE_MAPPER_H_

#include "Config.h"

namespace vrs {

class ResourceMapper
{
public:
    static ResourceMapper& instance()
    {
        static ResourceMapper instance_;
        return instance_;
    }

    const std::unordered_map<uint64_t, User*>& users() const { return users_; }
    const std::unordered_map<uint64_t, Group*>& groups() const { return groups_; }
    const std::unordered_map<uint64_t, ResourceFolder*>& folders() const { return folders_; }
    const std::unordered_map<uint64_t, ResourceFile*>& files() const { return files_; }

    const ResourceFolder* FindFolderFromURI(const std::string uri) const;

private:
    ResourceMapper();
    ~ResourceMapper();

    Config config_;

    std::unordered_map<uint64_t, User*> users_;
    std::unordered_map<uint64_t, Group*> groups_;
    std::unordered_map<uint64_t, ResourceFolder*> folders_;
    std::unordered_map<uint64_t, ResourceFile*> files_;
};


} // vrs


#endif /* _RESOURCE_MAPPER_H_ */
