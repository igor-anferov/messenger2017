#include <boost/uuid/string_generator.hpp>
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
        preparedData = deserialize (data);
    }
    catch (const pt::ptree_error &e) {
        std::cout << e.what () << std::endl;
        response = createError ("Dialog not found or invalid UDID format");
        return HttpResponse::Code::FORBIDEN;
    }
    userInfo info;
    response = createResponse(preparedData);

    if (info.status != response_result::ok) {
        return HttpResponse::Code::FORBIDEN;
    }
    //  auto generator =  boost::uuids::string_generator()(info.fingerprint);
    db->CreateUser (uuids::to_uuid(info.fingerprint), info.clientPublicKey);

    return HttpResponse::Code::OK;
}
MessagePair MessageManager::deserialize(const std::string &data)
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
std::string MessageManager::createResponse(const MessagePair &pair)
{
    std::string uuidString = pair.udid; //ВОЗМОЖНО, тут будет base64
    std::cout << uuidString << "__UUID__" << std::endl;
    boost::uuids::uuid temp = boost::uuids::string_generator()(uuidString);
    controller->getDB()->StoreMessage(controller->getUuid(), uuids::to_uuid(temp), pair.message);
    return std::string();
}
