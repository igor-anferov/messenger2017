#pragma once
#include "Manager.h"

namespace m2
{
namespace server
{
class UserInfoManager: public Manager
{
public:
    UserInfoManager(ManagerController* controller);
    virtual HttpResponse::Code doAction(const std::string &data, std::string &response) final;

private:
    std::string deserialize(const std::string &data);

    std::string createResponse(const std::string &uuid);
};
}
}

