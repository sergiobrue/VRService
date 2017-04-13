#include "ResourceFile.h"
#include "ResourceFolder.h"
#include "PostgresSQLResourceAcquirer.h"
#include "Logger.h"
#include "Config.h"
#include "User.h"
#include "URIUtils.h"

#include <iostream>

int main(int argc, char *argv[])
{
    // TODO - Use CPPUNIT or some other unit testing framework

    vrs::Logger::instance().SetLevel(LOG_DEBUG);
    vrs::Logger::instance().EnableStdout();

    vrs::Group test_group(0, "Test Group");
    vrs::User test_user(0, "Test User", "View0", {&test_group});
    vrs::Permissions test_permissions(0777);

    vrs::ResourceFile resource_file(&test_user, &test_group, test_permissions, 0, vrs::ResourceFile::VIDEO, "Test File", "Test File Description",
                                    "https://example.com/thumbnail.jpg", "https://example.com/stream.mp4", 0);

    vrs::ResourceFolder resource_folder(&test_user, &test_group, test_permissions, 0, "Test Folder", "Test Folder Description",
                                        "https://example.com/thumbnail_folder.jpg", "https://example.com/scene.jpg", 0);

    json final_json;

    final_json["folders"].push_back(resource_folder.as_json(nullptr));
    final_json["files"].push_back(resource_file.as_json(nullptr));

    std::cout << final_json << std::endl;

    try
    {
        vrs::Config config;
        std::cout << config.GetConnectionString() << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    vrs::PostgresSQLResourceAcquirer psra("dbname=vrdb user=vr password=vr hostaddr=192.168.1.200 port=5432 requiressl=1");

    std::cout << "DB Open: " << psra.Connect() << std::endl;

    std::unordered_map<uint64_t, vrs::User*> users;
    std::cout << "GetUsers: " <<  psra.GetUsers(users) << std::endl;

    std::unordered_map<uint64_t, vrs::Group*> groups;
    std::cout << "GetGroups: " <<  psra.GetGroups(groups) << std::endl;

    std::unordered_map<uint64_t, vrs::ResourceFolder*> folders;
    std::cout << "GetFolders: " <<  psra.GetFolders(folders, users, groups) << std::endl;

    std::unordered_map<uint64_t, vrs::ResourceFile*> files;
    std::cout << "GetFiles: " <<  psra.GetFiles(files, users, groups) << std::endl;

    std::vector<std::string> folders_str;
    vrs::URIUtils::URIToFolders("/videos/urbazo/ciudad%20real/", folders_str);

    std::cout << "URIToFolders:" << std::endl;

    for (auto& s : folders_str) std::cout << s << std::endl;

    return 0;
}
