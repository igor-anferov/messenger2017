#ifndef M2_SERVER_INDEXMANAGER_H
#define M2_SERVER_INDEXMANAGER_H

#include <unordered_set>
#include <boost/unordered_set.hpp>
#include <list>
#include "../stdafx.h"

namespace indices {

    /**
     * 5        - count of positions
     * UID1
     * UID2
     * UID3
     * UID4
     * UID5
     *
     *************************
     *
     */
    template<typename _Tp = uuids::uuid>
    class TIndexManager
    //        : boost::noncopyable
    {
    public:

        typedef boost::unordered_set<_Tp> LUids;

    public: /***************| Construction |***************/

        TIndexManager(const std::string& Path)
            : root(separate_root(Path))
            , path(Path)
        { LoadFromDisk(); }

        TIndexManager(std::string&& Path)
                : root(separate_root(Path))
                , path(std::move(Path))
        { LoadFromDisk(); }

        ~TIndexManager()
        { StoreOnDisk(); }

    public: /***************| Interface |***************/

        void LoadFromDisk() {
            std::ifstream in(path);
            checkR(in.is_open())
                StoreOnDisk();

            int size; //TODO:: check count
            in >> size;

            uuids::uuid Uid;
            for(; in >> Uid; Uid = 0)
                uids.emplace(Uid);
        }

        void StoreOnDisk () const {
            MakeDir(root);
            std::ofstream os(path);
            checkR(os.is_open());
            // send error

            os << uids.size();
            os << "\n";

            for (auto& i : uids) {
                os << i;
                os << "\n";
            }
        }

        void Add       (const _Tp& Uid)
        { uids.insert(Uid); }

        void Remove    (const _Tp& Uid)
        { uids.erase (Uid); }

        bool IsContains(const _Tp& Uid) const
        { return uids.find(Uid) != uids.end(); }

    protected: /************| Members |***************/

        std::string root;
        std::string path;

        LUids uids;

    public:

        std::string  Path() const { return path; }
        const LUids& Uids() const { return uids; }

    protected:

        std::string separate_root(const std::string& p)
        { return p.substr(0, p.find_last_of('/')); }

    public: /***************| operators |***************/

        bool operator[](const _Tp& Uid) const
        { return IsContains(Uid); }

    };

    using AIndexManager = TIndexManager<>;
}

#endif //M2_SERVER_INDEXMANAGER_H
