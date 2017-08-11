#ifndef M2_SERVER_CHATSINFOMANAGER_H
#define M2_SERVER_CHATSINFOMANAGER_H

#include "Manager.h"

namespace m2     {
namespace server {

    class ChatsinfoManager : public Manager
    {
    private:
        using ChatUid    = uuids::uuid;
        using MessageUid = uuids::uuid;

    public:



    public:
        ChatsinfoManager(ManagerController* controller);

        HttpResponse::Code
        doAction(const std::string &data, std::string &response) final;

    private:

        std::string
        CreateResponse(const std::map<ChatUid,MessageUid>& Data);

        uuids::uuid User;
    };



}}

#endif //M2_SERVER_CHATSINFOMANAGER_H
