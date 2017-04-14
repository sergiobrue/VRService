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
    : config_ok_(false)
{
    const char* const CONFIG_FILE_PATH = "/etc/vrs.conf";

    std::ifstream input_file(CONFIG_FILE_PATH);

    if (!input_file.is_open())
    {
        VRS_LOG_DEBUG("Error: Opening config file [%s]", CONFIG_FILE_PATH);
        return;
    }

    nlohmann::json json_obj;

    try
    {
        VRS_LOG_DEBUG("+---- Loading Config");
        input_file >> json_obj;
        VRS_LOG_DEBUG("| Getting Acquirer Name");
        resource_acquirer_name_ = json_obj["acquirer"];
        VRS_LOG_DEBUG("| Getting User");
        resource_acquirer_user_ = json_obj["user"];
        VRS_LOG_DEBUG("| Getting Password");
        resource_acquirer_password_ = json_obj["password"];
        VRS_LOG_DEBUG("| Getting DB");
        resource_acquirer_db_ = json_obj["db"];
        VRS_LOG_DEBUG("| Getting Host");
        resource_acquirer_host_ = json_obj["host"];
        VRS_LOG_DEBUG("| Getting Port");
        resource_acquirer_port_ = json_obj["port"];
        VRS_LOG_DEBUG("| Getting RequireSSL");
        resource_acquirer_require_ssl_ = json_obj["requiressl"];
        VRS_LOG_DEBUG("| Getting SSL Chain File");
        ssl_chain_file_path_ = json_obj["chain_file"];
        VRS_LOG_DEBUG("| Getting SSL Cert File");
        ssl_cert_file_path_ = json_obj["cert_file"];
        VRS_LOG_DEBUG("| Getting SSL PrivKey File");
        ssl_private_key_file_path_ = json_obj["priv_key_file"];
    }
    catch (std::exception& e)
    {
        VRS_LOG_DEBUG("Error: Parsing config file [%s] : %s", CONFIG_FILE_PATH, e.what());
        return;
    }

    config_ok_ = true;

}

Config::~Config()
{
}

const std::string Config::GetConnectionString() const
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
