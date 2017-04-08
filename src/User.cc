#include "User.h"

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

}
