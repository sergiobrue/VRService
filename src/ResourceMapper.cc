#include "ResourceMapper.h"
#include "PostgresSQLResourceAcquirer.h"
#include "URIUtils.h"
#include "Logger.h"
#include "Config.h"
#include "User.h"
#include "Group.h"
#include "ResourceFile.h"
#include "ResourceFolder.h"


namespace vrs {

class MappingException : public std::exception {
public:
    const char* what() { return "Cannot map the database"; }
};

ResourceMapper::ResourceMapper()
{
    VRS_LOG_DEBUG("+---- Resource Mapper");

    PostgresSQLResourceAcquirer psra(Config::instance().GetConnectionString());

    if (!psra.Connect()
        || !psra.GetUsers(users_)
        || !psra.GetGroups(groups_)
        || !psra.GetFolders(folders_, users_, groups_)
        || !psra.GetFiles(files_, users_, groups_))
    {
        throw MappingException();
    }


    for_each(folders_.begin(), folders_.end(),
             [this](auto it)
             {
                 ResourceFolder* folder = it.second;
                 folders_[folder->parent()]->PushFolder(folder);
             });

    for_each(files_.begin(), files_.end(),
             [this](auto it)
             {
                 ResourceFile* rfile = it.second;
                 folders_[rfile->parent_folder()]->PushFile(rfile);
             });

}

ResourceMapper::~ResourceMapper()
{
}

const ResourceFolder* ResourceMapper::FindFolderFromURI(const std::string uri) const
{
    std::vector<std::string> folders_str;
    URIUtils::URIToFolders(uri, folders_str);

    auto it = folders_.find(0);

    if (it==folders_.end()) return nullptr; // Root Folder not found

    const ResourceFolder* current_folder = it->second;

    if (folders_str.size()==0) return current_folder;

    for (auto& folder_name : folders_str)
    {
        // TODO - Force unique name inside a folder
        auto it = find_if(current_folder->child_folders().begin(),
                          current_folder->child_folders().end(),
                          [&folder_name](auto itf) -> bool { return itf->name()==folder_name; }
            );
        if (it==current_folder->child_folders().end())
        {
            return nullptr;
        }
        current_folder = *it;
    }
    return current_folder;
}


} // vrs
