#ifndef M2_SERVER_AMESSAGE_H
#define M2_SERVER_AMESSAGE_H

#include <chrono> // how to explain time?

#include "../stdafx.h"



namespace m2      {
namespace data    {
namespace message {

    /**
     * A message is a class,
     * wrapping a file on a disk
     *
     * file name looks like: time^author
     */
    class AMessage
    {
    public: /***************| Construction |***************/
        // new message
        AMessage(std::istream& is);
        AMessage( const std::string& Dir
                , const std::string& Author
                , const std::string& Time
                , const std::string& Text);

        // open existing message
        AMessage(const std::string&  FileName);
        AMessage( const std::string& Dir
                , const std::string& Author
                , const std::string& Time);

        ~AMessage();

    public: /***************| Interface |***************/

        AMessage& Serialize(std::ostream& os);

        void Storage();

        void Remove();

    protected: /************| Members |***************/

        bool bChanged;

        std::string dir;
        std::string author;
        std::string time;
        std::string text;

    public:

        const std::string& Author() const { return author; }
        const std::string& Time()   const { return time;   }
        const std::string& Text()   const { return text;   }

    public:

        void SetAuthor(const std::string& New);
        void SetTime  (const std::string& New);
        void SetText  (const std::string& New);

        void SetAuthor(std::string&& New);
        void SetTime  (std::string&& New);
        void SetText  (std::string&& New);

    protected:

        void init_meta(const std::string& FileName);
        void load_text(const std::string& FileName);
        void on_meta_change();
        void on_text_chande();

        std::string path();

    public: /***************| operators |***************/

        std::ostream& operator<<(std::ostream& os);

        bool operator==(const AMessage& rs) const;
    };


}}}


#endif //M2_SERVER_AMESSAGE_H
