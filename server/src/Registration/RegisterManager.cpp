#include "Registration/RegisterManager.h"
#include "../Data/User/Users.h"


using namespace m2::server;


RegisterManager::StringsPair RegisterManager::deserialize(const std::string &data) {
  pt::ptree request;
  StringsPair info;
  std::stringstream stream;
  stream << data;

  boost::property_tree::read_json(stream, request);
  info.serverString = request.get<std::string>("server_string");
  info.clientString = request.get<std::string>("client_string");

  return info;
}

HttpResponse::Code RegisterManager::doAction(const std::string &data, std::string &response) {
  StringsPair info;
  try {
    info = deserialize(data);

    response = createResponse();
  } catch (const pt::ptree_error &e) {
    std::cout << e.what() << std::endl;
    response = createError("client_string and decrypted server_string");
    return HttpResponse::Code::FORBIDEN;
  }
  response = createResponse();
  //тут должен быть fingerprint
  //m2::data::user::AUsers::instance().CreateUser(id, "public_key"); //тут должен быть public_key

  //TODO save
  return HttpResponse::Code::OK;
}
std::string RegisterManager::createResponse() {
  pt::ptree tree;
  std::stringstream stream;
  boost::property_tree::write_json(stream, tree); //empty tree
  return stream.str();
}
void RegisterManager::save(const std::string &data) {}
