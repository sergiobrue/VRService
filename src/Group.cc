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

}
