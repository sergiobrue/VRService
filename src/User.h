#ifndef _VRS_USER_H_
#define _VRS_USER_H_


#include <string>
#include <stdint.h>
#include <vector>

namespace vrs {

class Group;

class User {
public:
    User(const uint64_t id,
         const std::string& name,
         const std::string& home_view,
         const std::vector<Group*> groups);

    ~User();
private:
    const uint64_t    id_;
    const std::string name_;
    const std::string home_view_;
    std::vector<Group*> groups_;

    // TODO Cache home view pointer ?
    // ResourcesView* cachedView_;
};

}


#endif /* _VRS_USER_H_ */
