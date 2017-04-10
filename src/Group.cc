#include "Group.h"

namespace vrs {


Group::Group(const uint64_t id,
             const std::string name)
    : id_(id)
    , name_(name)
{
}

Group::~Group()
{
}

const char* Group::c_str() const
{
    static char str[4098] = {0};
    snprintf(str, sizeof(str), "(id⁼%ju, name=\"%s\")",
             uintmax_t(id_), name_.c_str());

    return str;
}


}
