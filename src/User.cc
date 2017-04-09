#include "User.h"

#include <cstdio>

namespace vrs {

User::User(const uint64_t id,
           const std::string& name,
           const std::string& home_view,
           const std::vector<Group*> groups)
    : id_(id)
    , name_(name)
    , home_view_(home_view)
    , groups_(groups)
{
}

User::~User()
{
}

const char* User::c_str() const
{
    static char str[4098] = {0};
    snprintf(str, sizeof(str), "(id⁼%ju, name=\"%s\", home_view=\"%s\")",
             uintmax_t(id_), name_.c_str(), home_view_.c_str());

    return str;
}


}
