#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "Message/MessageManager.h"
using namespace m2::server;
MessageManager::MessageManager(ManagerController *controller)
    : Manager(controller)
{

}
HttpResponse::Code MessageManager::doAction(const std::string &data, std::string &response)
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
    if(!isDialogExists){
        response = createError("Can't find dialog");
        return HttpResponse::Code::FORBIDEN;
    }
    return HttpResponse::Code::OK;
}
MessageManager::MessagePair MessageManager::deserialize(const std::string &data)
{
    pt::ptree request;
    MessagePair result;
    std::string publicKey;
    std::stringstream stream;
    stream << data;
    boost::property_tree::read_json(stream, request);
    result.message = request.get<std::string>("msg");
    result.udid = request.get<std::string>("udid");

    return result;
}
std::string MessageManager::createResponse(const MessagePair &pair, bool &isDialogExists)
{
    std::string uuidString = pair.udid; //ВОЗМОЖНО, тут будет base64
    std::cout << uuidString << "__UUID__" << std::endl;
    boost::uuids::uuid temp = boost::uuids::string_generator()(uuidString);
    uuids::uuid dialogUuid = uuids::to_uuid(temp);
    auto isUserExists = db->GetDialog(controller->getUuid(), dialogUuid);
    if (isUserExists == nullptr) {
        isDialogExists = false;
        return std::string();
    }
    const uuids::uuid& messageUuid = db->StoreMessage(controller->getUuid(), dialogUuid, pair.message);
    pt::ptree tree;
    std::stringstream stream;
    tree.put("uuid", messageUuid.str());
    boost::property_tree::write_json(stream, tree);
    return stream.str();
}

