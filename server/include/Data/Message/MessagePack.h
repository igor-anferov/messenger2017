#ifndef M2_SERVER_MESSAGEPACK_H
#define M2_SERVER_MESSAGEPACK_H

#include <vector>
#include <memory>
#include <iostream>


namespace m2      {
namespace data    {
namespace message {

    class AMessage;

    /**
     *
     */
    class AMessagePack
    {
    public:

        using MessagePtr  = std::shared_ptr<AMessage>;
        using MessagePull = std::vector<MessagePtr>;

    public: /***************| Construction |***************/

        AMessagePack() = default;

    public: /***************| Interface |***************/

        void AddMessage(MessagePtr Message);

        void Deserialize(std::istream& in);

    protected: /************| Members |***************/

        MessagePull messages;

    };

}}}


#endif //M2_SERVER_MESSAGEPACK_H
