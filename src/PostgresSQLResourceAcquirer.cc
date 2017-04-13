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
    LOGD("Connecting to PostgresSQL [%s]", connection_string_.c_str());

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

    LOGD("+---- Getting Users");

    try
    {
        pqxx::nontransaction nt(*connection_);
        pqxx::result res(nt.exec("SELECT * from users"));

        for (auto it = res.begin(); it != res.end(); ++it)
        {
            User* user = new User(it[0].as<int>(), it[1].as<std::string>(), it[2].as<std::string>());
            users.emplace(user->id(), user);
            LOGD("| Adding User: %s", user->c_str());
        }
    }
    catch (const std::exception& e)
    {
        LOGD("Error getting users:\n%s", e.what());
        return false;
    }

    return true;
}

bool PostgresSQLResourceAcquirer::GetGroups(std::unordered_map<uint64_t, Group*>&  groups) const
{
    if (!connection_) return false;

    LOGD("+---- Getting Groups");

    try
    {
        pqxx::nontransaction nt(*connection_);
        pqxx::result res(nt.exec("SELECT * from groups"));

        for (auto it = res.begin(); it != res.end(); ++it)
        {
            Group* group = new Group(it[0].as<int>(), it[1].as<std::string>());
            groups.emplace(group->id(), group);
            LOGD("| Adding group: %s", group->c_str());
        }
    }
    catch (const std::exception& e)
    {
        LOGD("Error getting users:\n%s", e.what());
        return false;
    }

    return true;
}

bool PostgresSQLResourceAcquirer::GetFolders(std::unordered_map<uint64_t, ResourceFolder*>& folders,
                                             const std::unordered_map<uint64_t, User*>& users,
                                             const std::unordered_map<uint64_t, Group*>&  groups)
{
    if (!connection_) return false;

    LOGD("+---- Getting Folders");

    try
    {
        pqxx::nontransaction nt(*connection_);
        pqxx::result res(nt.exec("SELECT * from folders"));

        for (auto it = res.begin(); it != res.end(); ++it)
        {
            auto it_u = users.find(it[6].as<uint64_t>());
            if (it_u==users.end())
            {
                LOGD("* User with id: %ju not found. Skipping entry.", it[6].as<uint64_t>());
                continue;
            }
            auto it_g = groups.find(it[7].as<uint64_t>());
            if (it_g==groups.end())
            {
                LOGD("* Group with id: %ju not found. Skipping entry.", it[7].as<uint64_t>());
                continue;
            }

            Permissions perm(it[8].as<uint16_t>());

            ResourceFolder* folder = new ResourceFolder(it_u->second, it_g->second, perm,
                                                        it[0].as<uint64_t>(), it[1].as<std::string>(),
                                                        it[2].as<std::string>(), it[3].as<std::string>(),
                                                        it[4].as<std::string>(), it[5].as<uint64_t>());
            folders.emplace(folder->id(), folder);
            LOGD("| Adding folder: %s", folder->c_str());
        }
    }
    catch (const std::exception& e)
    {
        LOGD("Error getting users:\n%s", e.what());
        return false;
    }

    return true;
}

bool PostgresSQLResourceAcquirer::GetFiles(std::unordered_map<uint64_t, ResourceFile*>& files,
                                           const std::unordered_map<uint64_t, User*>& users,
                                           const std::unordered_map<uint64_t, Group*>&  groups)
{
    if (!connection_) return false;

    LOGD("+---- Getting Files");

    try
    {
        pqxx::nontransaction nt(*connection_);
        pqxx::result res(nt.exec("SELECT * from files"));

        for (auto it = res.begin(); it != res.end(); ++it)
        {
            auto it_u = users.find(it[7].as<uint64_t>());
            if (it_u==users.end())
            {
                LOGD("* User with id: %ju not found. Skipping entry.", it[6].as<uint64_t>());
                continue;
            }
            auto it_g = groups.find(it[8].as<uint64_t>());
            if (it_g==groups.end())
            {
                LOGD("* Group with id: %ju not found. Skipping entry.", it[7].as<uint64_t>());
                continue;
            }

            Permissions perm(it[9].as<uint16_t>());

            ResourceFile* file = new ResourceFile(it_u->second, it_g->second, perm,
                                                  it[0].as<uint64_t>(), ResourceFile::FileType_t(it[1].as<uint64_t>()),
                                                  it[2].as<std::string>(), it[3].as<std::string>(),
                                                  it[4].as<std::string>(), it[5].as<std::string>(),
                                                  it[6].as<uint64_t>());

            files.emplace(file->id(), file);
            LOGD("| Adding File: %s", file->c_str());
        }
    }
    catch (const std::exception& e)
    {
        LOGD("Error getting users:\n%s", e.what());
        return false;
    }

    return true;
}

bool PostgresSQLResourceAcquirer::GetViews(std::unordered_map<uint64_t, ResourceView*>& views)
{
    return true;
}


ResourceAcquirer::ResourceAcquirer_t PostgresSQLResourceAcquirer::type() const
{
    return ResourceAcquirer::PSQL;
}


} //vrs
