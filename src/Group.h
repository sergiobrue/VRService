#ifndef _VRS_GROUP_H_
#define _VRS_GROUP_H_

#include <string>
#include <stdint.h>

namespace vrs {

class Group
{
public:
    Group(const uint64_t id,
          const std::string name);

    ~Group();
private:
    const uint64_t id_;
    const std::string name_;
};


}


#endif /* _VRS_GROUP_H_ */
