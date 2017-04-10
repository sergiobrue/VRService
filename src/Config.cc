#include "Config.h"
#include "Logger.h"
#include "json.hpp"

#include <fstream>
#include <sstream>

namespace vrs {

class ConfigFileOpenException : public std::exception
{
    const char* what() { return "Error opening config file"; }
};

class ConfigFileParsingException : public std::exception
{
    const char* what() { return "Error parsing config file"; }
};


Config::Config()
{
    const char* const CONFIG_FILE_PATH = "/etc/vrs.conf";

    std::ifstream input_file(CONFIG_FILE_PATH);

    if (!input_file.is_open())
    {
        LOGD("Error: Opening config file [%s]", CONFIG_FILE_PATH);
        throw ConfigFileOpenException();
    }

    nlohmann::json json_obj;

    try
    {
        input_file >> json_obj;
        LOGD("Getting Acquirer Name");
        resource_acquirer_name_ = json_obj["acquirer"];
        LOGD("Getting User");
        resource_acquirer_user_ = json_obj["user"];
        LOGD("Getting Password");
        resource_acquirer_password_ = json_obj["password"];
        LOGD("Getting DB");
        resource_acquirer_db_ = json_obj["db"];
        LOGD("Getting Host");
        resource_acquirer_host_ = json_obj["host"];
        LOGD("Getting Port");
        resource_acquirer_port_ = json_obj["port"];
        LOGD("Getting RequireSSL");
        resource_acquirer_require_ssl_ = json_obj["requiressl"];
    }

    catch (std::exception& e)
    {
        LOGD("Error: Parsing config file [%s] - %s", CONFIG_FILE_PATH, e.what());
        throw ConfigFileParsingException();
    }


}

Config::~Config()
{
}

std::string Config::GetConnectionString() const
{
    if (resource_acquirer_name_ == "psql")
    {
        std::stringstream ss_port;
        ss_port << resource_acquirer_port_;
        std::stringstream ss_ssl;
        ss_ssl << resource_acquirer_require_ssl_;

        return "dbname=" + resource_acquirer_db_
            + " user=" + resource_acquirer_user_
            + " password=" + resource_acquirer_password_
            + " hostaddr=" + resource_acquirer_host_
            + " port=" + ss_port.str()
            + " requiressl=" + ss_ssl.str();

    }

    return "NOT_SUPPORTED_ACQUIRER";
}


}
