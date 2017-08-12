#include "include/models/messages_model.h"

#include <QDebug>
using namespace ModelsElements;


MessagesModel::MessagesModel(QObject *parent) : QAbstractListModel(parent)
{
    itemList.append(MessageData(
                            "1","0",
                            "Eba?",
                            "10:00"
                            ));

        itemList.append(MessageData(
                            "0","0",
                            "Eba",
                            "10:10"
                            ));

        itemList.append(MessageData(
                            "1", "0",
                            "Eba?1",
                            "11:00"
                            ));

       qDebug()<<"create MessagesModel";
}


MessagesModel::~MessagesModel()
{
    qDebug()<<"delete MessagesModel";
}


void MessagesModel::addMessage(const MessageData &mess)
{
    itemList.append(mess);
}


void MessagesModel::loadMessageHistory()
{
    // добавляем в модель новые данные
}


void MessagesModel::cleanChat()
{
    itemList.clear();
}


int MessagesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return itemList.size();
}


QVariant MessagesModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid())
    {
        switch (role) {
        case MessageDataRole::FromUuid:
            return itemList[index.row()].fromUuid;
        case MessageDataRole::ChatUuid:
            return itemList[index.row()].chatUuid;
        case MessageDataRole::MessText:
            return itemList[index.row()].messText;
        case MessageDataRole::MessTime:
            return itemList[index.row()].messTime;
        }
    }
    return QVariant();
}


bool MessagesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid())
    {
        switch (role)
        {
            case MessageDataRole::FromUuid:
            {
                itemList[index.row()].fromUuid = value;
                break;
            }
            case MessageDataRole::ChatUuid:
            {
                itemList[index.row()].chatUuid = value;
                break;
            }
            case MessageDataRole::MessText:
            {
                itemList[index.row()].messText = value;
                break;
            }
            case MessageDataRole::MessTime:
            {
                itemList[index.row()].messTime = value;
                break;
            }

            default:
                return false;
        }
    }
    return true;
}


QHash<int, QByteArray> MessagesModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();

    roles[FromUuid] = "FromUuid";
    roles[ChatUuid] = "ChatUuid";
    roles[MessText] = "MessText";
    roles[MessTime] = "MessTime";

    return roles;
}
