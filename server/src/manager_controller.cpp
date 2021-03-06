#include "manager_controller.h"
#include "Registration/RegisterManager.h"
#include "Registration/RegisterSendKeyManager.h"
#include "Auth/LoginManager.h"
#include "Auth/LoginSendKeyManager.h"
#include "Message/MessageManager.h"
#include "Message/UserInfoManager.h"
#include "Message/ChatsInfoManager.h"
#include "Message/MessagesInfoManager.h"

namespace m2
{
namespace server
{


ManagerController::ManagerController(Database *database, Session *session)
    : db(database), session_(session)
{
    managerProcessor = {
        {"/user/register/sendKey", new RegisterSendKeyManager(this)},
        {"/user/register", new RegisterManager(this)},
        {"/user/auth/sendUuid", new LoginSendKeyManager(this)},
        {"/user/auth", new LoginManager(this)},
        {"/dialog/send_message", new MessageManager(this)},
        {"/user/info", new UserInfoManager(this)},
        {"/dialog/list", new ChatsinfoManager(this)},
        {"/dialog/messages", new MessagesInfoManager(this)}
    };
}

responsePtr ManagerController::doProcess(requestPtr request)
{
    responsePtr answer = std::make_shared<HttpResponse>();

    std::string uri = request->getHeader().uri_;
    std::string data = request->getData();
    std::string response;
    HttpResponse::Code code = HttpResponse::Code::OK;

    if (managerProcessor.count(uri) > 0) {
        code = managerProcessor.at(uri)->doAction(data, response);
    }
    else {
        code = HttpResponse::Code::NOT_FOUND;
        response = Manager::createError("Something wrong");
    }

    std::cout << "RESPONSE: " << response << std::endl;

    answer->setData(response, code);

    return answer;
}

ManagerController::~ManagerController()
{
    db->DeleteSession(userUid);
}

}
} // m2::server
