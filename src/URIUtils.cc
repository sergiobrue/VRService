#include "URIUtils.h"

#include <string.h>
#include <stdio.h>

namespace vrs {

void URIUtils::URIToFolders(const std::string& uri, std::vector<std::string>& folders)
{
    char* in = const_cast<char*>(uri.c_str());
    char* token;
    const char* sep="/";

    token = strtok(in, sep);

    while (token != nullptr)
    {
        folders.push_back(token);
        token = strtok(nullptr, sep);
    }
}


} // vrs
