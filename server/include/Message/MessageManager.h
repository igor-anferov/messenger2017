#ifndef M2_SERVER_MESSAGEMANAGER_H
#define M2_SERVER_MESSAGEMANAGER_H

#include "Manager.h"

namespace m2
{
namespace server
{

class MessageManager: public Manager
{
    struct MessagePair{
        std::string udid;
        std::string message;
    };
public:
    MessageManager(ManagerController* controller);

    virtual HttpResponse::Code doAction(const std::string &data, std::string &response) final;


private:
    MessagePair deserialize(const std::string &data);


    std::string createResponse(const MessagePair &pair, bool &isDialogExists);
};
}
}

#endif //M2_SERVER_MESSAGEMANAGER_H
