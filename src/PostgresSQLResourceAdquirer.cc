#include "PostgresSQLResourceAdquirer.h"
#include "Logger.h"

namespace vrs {

PostgresSQLResourceAdquirer::PostgresSQLResourceAdquirer(const std::string& connection_string)
    : connection_(nullptr)
    , connection_string_(connection_string)
{
}

PostgresSQLResourceAdquirer::~PostgresSQLResourceAdquirer()
{
    delete connection_;
}

bool PostgresSQLResourceAdquirer::Connect()
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

bool PostgresSQLResourceAdquirer::GetUsers(std::vector<User*>& users) const
{
    return true;
}

bool PostgresSQLResourceAdquirer::GetGroups(std::vector<Group*>& groups) const
{
    return true;
}


} //vrs
