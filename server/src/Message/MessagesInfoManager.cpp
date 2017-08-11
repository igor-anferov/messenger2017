#include <server/include/manager_controller.h>
#include <server/include/Message/MessagesInfoManager.h>
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
using namespace m2::server;

MessagesInfoManager::MessagesInfoManager(ManagerController *controller)
    : Manager(controller)
{

}
HttpResponse::Code m2::server::MessagesInfoManager::doAction(const std::string &data, std::string &response)
{
    MessagePair preparedData;
    try {
        preparedData = deserialize(data);
    }
    catch (const pt::ptree_error &e) {
        std::cout << e.what() << std::endl;
        response = createError("Dialog not found or invalid UDID format");
        return HttpResponse::Code::FORBIDEN;
    }

    bool isDialogExists = true;
    response = createResponse(preparedData, isDialogExists);
    if (!isDialogExists) {
        response = createError("Can't find dialog");
        return HttpResponse::Code::FORBIDEN;
    }
    return HttpResponse::Code::OK;
}
MessagesInfoManager::MessagePair MessagesInfoManager::deserialize(const std::string &data)
{
    pt::ptree request;
    MessagePair result;
    std::string publicKey;
    std::stringstream stream;
    stream << data;
    boost::property_tree::read_json(stream, request);
    result.umid = request.get<std::string>("umid");
    result.udid = request.get<std::string>("udid");

    return result;
}
std::string MessagesInfoManager::createResponse(const m2::server::MessagesInfoManager::MessagePair &pair,
                                               bool &isDialogExists)
{
    std::string uuidString = pair.udid; //ВОЗМОЖНО, тут будет base64
    boost::uuids::uuid temp = boost::uuids::string_generator()(uuidString);
    uuids::uuid dialogUuid = uuids::to_uuid(temp);
    auto dialog = db->GetDialog(controller->getUuid(), dialogUuid);
    if (dialog == nullptr) {
        isDialogExists = false;
        return std::string();
    }
    std::vector<ResponseMessage> messages;

    std::string umidString = pair.umid; //ВОЗМОЖНО, тут будет base64
    boost::uuids::uuid temp2 = boost::uuids::string_generator()(uuidString);
    uuids::uuid dialogUmid = uuids::to_uuid(temp);
    std::shared_ptr<m2::data::AMessage> message = dialog->Get(dialogUmid);
    pt::ptree tree;
    std::stringstream stream;
    while (message != nullptr) {
//        ResponseMessage response;
//        response.umid = dialogUmid;
//        response.body = message->Text();

        messages.emplace_back(dialogUmid.str(), message->Text());
        dialogUmid++;
        tree.add("messages", message->Text());

        message = dialog->Get(dialogUmid);

    }
    boost::property_tree::write_json(stream, tree);

    return stream.str();
}
MessagesInfoManager::ResponseMessage::ResponseMessage(const std::string &umid, const std::string &body)
    : umid(umid), body(body)
{}
