#ifndef _POSTGRES_SQL_RESOURCE_ACQUIRER_H_
#define _POSTGRES_SQL_RESOURCE_ACQUIRER_H_

#include "ResourceAcquirer.h"

#include <pqxx/pqxx>
#include <string>

namespace vrs {

class PostgresSQLResourceAcquirer : public ResourceAcquirer
{
public:
    PostgresSQLResourceAcquirer(const std::string& connection_string);
    ~PostgresSQLResourceAcquirer();

    bool Connect() final;
    bool GetUsers(std::unordered_map<uint64_t, User*>& users) const final;
    bool GetGroups(std::vector<Group*>& groups) const final;

    ResourceAcquirer::ResourceAcquirer_t type() const final;

private:
    pqxx::connection* connection_;
    const std::string connection_string_;
};


} // vrs


#endif /* _POSTGRES_SQL_RESOURCE_ACQUIRER_H_ */
