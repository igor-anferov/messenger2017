
#include "Data/Dialog/UserDialogs.h"

using namespace m2::data::dialog;

AUserDialogs::AUserDialogs(const std::string& Root, uuids::uuid Uid)
    : TDialogSystem(Root, "Index", 256, Uid)
{}

/****************************|  |****************************/

std::shared_ptr<ADialog>
AUserDialogs::Get(const uuids::uuid& Uid) {

    // from cash
    if (index[Uid]){
        auto ptr = cash(Uid);
        ifR(ptr) ptr;
    } else create_dialog(Uid);

    // from disk
    return cash.Add(root  + Uid.str() + "/", Uid);
}

const std::shared_ptr<ADialog>
AUserDialogs::Get(const uuids::uuid& Uid) const {
    checkR(index[Uid]) nullptr;

    // from cash
    auto ptr = cash(Uid);
    ifR(ptr) ptr;

    //from disk
    return cash.Add(root + Uid.str() + "/", Uid);
}

/****************************|  |****************************/

std::shared_ptr<ADialog>
AUserDialogs::create_dialog(uuids::uuid Uid) {
          index.Add(Uid);
    return cash.Add(root  + Uid.str() + "/", Uid);
}



