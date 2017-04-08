#ifndef _POSTGRES_SQL_RESOURCE_ADQUIRER_H_
#define _POSTGRES_SQL_RESOURCE_ADQUIRER_H_

#include "ResourceAdquirer.h"

#include <pqxx/pqxx>
#include <string>

namespace vrs {

class PostgresSQLResourceAdquirer : public ResourceAdquirer
{
public:
    PostgresSQLResourceAdquirer(const std::string& connection_string);
    ~PostgresSQLResourceAdquirer();

    bool Connect() final;
    bool GetUsers(std::vector<User*>& users) const;
    bool GetGroups(std::vector<Group*>& groups) const;

private:
    pqxx::connection* connection_;
    const std::string connection_string_;
};


} // vrs


#endif /* _POSTGRES_SQL_RESOURCE_ADQUIRER_H_ */
