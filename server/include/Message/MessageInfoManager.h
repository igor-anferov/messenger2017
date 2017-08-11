#ifndef M2_SERVER_MESSAGEINFOMANAGER_H
#define M2_SERVER_MESSAGEINFOMANAGER_H
#include "Manager.h"
namespace m2
{
namespace server
{

class MessageInfoManager: public Manager
{
    struct MessagePair
    {
        std::string udid;
        std::string umid;
    };
    struct ResponseMessage{
        ResponseMessage(const std::string &umid, const std::string &body);
        std::string umid;
        std::string body;
    };
public:
    MessageInfoManager(ManagerController *controller);

    virtual HttpResponse::Code doAction(const std::string &data, std::string &response) final;


private:
    MessagePair deserialize(const std::string &data);

    std::string createResponse(const MessagePair &pair, bool &isDialogExists);
};
}
}
#endif //M2_SERVER_MESSAGEINFOMANAGER_H
