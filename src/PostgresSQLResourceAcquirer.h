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
    bool GetGroups(std::unordered_map<uint64_t, Group*>&  groups) const final;
    bool GetFolders(std::unordered_map<uint64_t, ResourceFolder*>& folders,
                    const std::unordered_map<uint64_t, User*>& users,
                    const std::unordered_map<uint64_t, Group*>&  groups) final;

    bool GetFiles(std::unordered_map<uint64_t, ResourceFile*>& files,
                  const std::unordered_map<uint64_t, User*>& users,
                  const std::unordered_map<uint64_t, Group*>&  groups) final;

    bool GetViews(std::unordered_map<uint64_t, ResourceView*>& views) final;

    ResourceAcquirer::ResourceAcquirer_t type() const final;

private:
    pqxx::connection* connection_;
    const std::string connection_string_;
};


} // vrs


#endif /* _POSTGRES_SQL_RESOURCE_ACQUIRER_H_ */
