#include "ResourceFile.h"
#include "ResourceFolder.h"
#include "PostgresSQLResourceAdquirer.h"

#include <iostream>

int main(int argc, char *argv[])
{
    // TODO - Use CPPUNIT or some other unit testing framework

    vrs::Group test_group(0, "Test Group");
    vrs::User test_user(0, "Test User", "View0", {&test_group});
    vrs::Permissions test_permissions;

    vrs::ResourceFile resource_file(&test_user, &test_group, test_permissions, 0, vrs::ResourceFile::VIDEO, "Test File", "Test File Description",
                                    "https://example.com/thumbnail.jpg", "https://example.com/stream.mp4");

    vrs::ResourceFolder resource_folder(&test_user, &test_group, test_permissions, 0, "Test Folder", "Test Folder Description",
                                        "https://example.com/thumbnail_folder.jpg", "https://example.com/scene.jpg", {});

    json final_json;

    final_json["folders"].push_back(resource_folder.as_json());
    final_json["files"].push_back(resource_file.as_json());

    std::cout << final_json << std::endl;

    vrs::PostgresSQLResourceAdquirer psra("dbname=postgres user=vr password=vr hostaddr=192.168.1.200 port=5432 requiressl=1");

    std::cout << "DB Open: " << psra.Connect() << std::endl;

    return 0;
}
