#ifndef M2_SERVER_DATABASE_H
#define M2_SERVER_DATABASE_H

#include "Data.hpp"
#include "session.h"

namespace m2     {
namespace server {


    class Database
    {
    public:

        Database(const std::string& rootDir);

    public:

        bool CreateUser(uuids::uuid Uid, const std::string&  PublicKey);
        bool CreateUser(uuids::uuid Uid,       std::string&& PublicKey);

        bool IsClienExists(uuids::uuid Uid);

    public:

        std::string getUserPublicKey(uuids::uuid Uid);

        std::string getPublicServerKey();
        std::string getPrivateServerKey();

    public:

        sessionPtr

    protected:

        data::AUsers   Users;
        data::ADialogs Dialogs;

        //std::unordered_map<uuids::

    };


}}


#endif //M2_SERVER_DATABASE_H
