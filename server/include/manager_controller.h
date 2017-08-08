#pragma once

#include "http_request.h"
#include "http_response.h"


namespace m2     {
namespace server {

    class Database;

    class ManagerController
    {
    public:
        ManagerController(Database* database);

        responsePtr doProcess(requestPtr request);

    private:
        Database* db;

    };


}} // m2::server
