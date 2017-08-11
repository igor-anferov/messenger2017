
#include "Message/ChatsInfoManager.h"

using namespace m2::server;


ChatsinfoManager::ChatsinfoManager(ManagerController* controller)
        : Manager(controller)
        , User()
{
    if (!controller)
        return;
    User = controller->getUuid();
}

HttpResponse::Code
ChatsinfoManager::doAction(const std::string& data, std::string& response)
{
    // if data is broken
    if (!db) {
        response = "";
        return HttpResponse::Code::FORBIDEN;
    }

    // if
    auto UserDialogs = db->GetUserDialog(User);
    if (!UserDialogs) {
        response = "";
        return HttpResponse::Code::FORBIDEN;
    }

    // Fill in @Chats
    std::map<ChatUid, MessageUid> Chats;
    for (ChatUid Uid : UserDialogs->Index())
    {
        // Current dialog manager
        auto Dialog = UserDialogs->Get(Uid);
        if (!Dialog) // Is it a right behavior?
            continue;
        Chats.emplace(Uid,
            Dialog->GetLastMessageUid());
    }

    response = CreateResponse(Chats);
    return HttpResponse::Code::OK;
}

std::string
ChatsinfoManager::CreateResponse(const std::map<ChatUid,MessageUid>& Data)
{
    pt::ptree ResultTree;
    pt::ptree ArrayTree;

    for (auto& pair : Data) {
        // in array data
        pt::ptree element;
        element.put("udid",      pair.first.str());
        element.put("last_umid", pair.second.str());
        // add the data into array
        ArrayTree.push_back(std::make_pair("", element));
    }
    std::stringstream stream;
    ResultTree.add_child("dialogues", ArrayTree);
    pt::write_json(stream, ResultTree);
    return stream.str();
}
