#include "PostgresSQLResourceAcquirer.h"
#include "Logger.h"

namespace vrs {

PostgresSQLResourceAcquirer::PostgresSQLResourceAcquirer(const std::string& connection_string)
    : connection_(nullptr)
    , connection_string_(connection_string)
{
}

PostgresSQLResourceAcquirer::~PostgresSQLResourceAcquirer()
{
    delete connection_;
}

bool PostgresSQLResourceAcquirer::Connect()
{
    try {
    connection_ = new pqxx::connection(connection_string_);
    }
    catch (const std::exception& e)
    {
        LOGD(e.what());
        return false;
    }
    return true;
}

bool PostgresSQLResourceAcquirer::GetUsers(std::unordered_map<uint64_t, User*>& users) const
{
    if (!connection_) return false;

    try
    {
        pqxx::nontransaction nt(*connection_);
        pqxx::result res(nt.exec("SELECT * from users"));

        for (auto it = res.begin(); it != res.end(); ++it)
        {
            User* user = new User(it[0].as<int>(), it[1].as<std::string>(), it[2].as<std::string>());
            users.emplace(user->id(), user);
            LOGD("Adding User: %s", user->c_str());
        }
    }
    catch (const std::exception& e)
    {
        LOGD("Error getting users:\n%s", e.what());
        return false;
    }

    return true;
}

bool PostgresSQLResourceAcquirer::GetGroups(std::vector<Group*>& groups) const
{
    return true;
}

ResourceAcquirer::ResourceAcquirer_t PostgresSQLResourceAcquirer::type() const
{
    return ResourceAcquirer::PSQL;
}


} //vrs
