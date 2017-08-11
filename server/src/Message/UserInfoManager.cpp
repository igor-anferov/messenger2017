#include "Message/UserInfoManager.h"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/string_generator.hpp>


using namespace m2::server;

HttpResponse::Code UserInfoManager::doAction(const std::string &data, std::string &response)
{
    std::string preparedData;
    try {
        preparedData = deserialize(data);
        response = createResponse(preparedData);
    }
    catch (const pt::ptree_error &e) {
        std::cout << e.what() << std::endl;
        response = createError("uuid deserialize");
        return HttpResponse::Code::FORBIDEN;
    }


    return HttpResponse::Code::OK;
}

std::string UserInfoManager::deserialize(const std::string &data)
{
    std::string uuid;
    pt::ptree request;
    std::stringstream stream;
    stream << data;

    boost::property_tree::read_json(stream, request);
    uuid = request.get<std::string>("uuid");

    return uuid;
}

std::string UserInfoManager::createResponse(const std::string &uuid)
{

    boost::uuids::uuid temp = boost::uuids::string_generator()(uuid);
    uuids::uuid oppnentUuid = uuids::to_uuid(temp);

    std::string piblicKey = db->getUserPublicKey(oppnentUuid);

    pt::ptree tree;
    std::stringstream stream;
    tree.put("public_key", piblicKey.c_str());
    boost::property_tree::write_json(stream, tree);

    return stream.str();
}

UserInfoManager::UserInfoManager(ManagerController* controller)
    : Manager(controller)
{

}
