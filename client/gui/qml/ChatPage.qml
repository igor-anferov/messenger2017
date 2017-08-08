import QtQuick 2.5
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4


Page{
    id: chatPage
    anchors.fill: parent

    header: ToolBar {
        background: Rectangle {
                    color: "#efefef"
                }

        RowLayout {
            id: topLayout
            anchors.fill: parent

            Image{
                id: chatAvatar

                Layout.fillWidth: true
                Layout.margins: 5
                Layout.minimumHeight: 50
                Layout.minimumWidth: 50
                Layout.maximumWidth: 50
                Layout.maximumHeight: 50

                fillMode: Image.PreserveAspectFit

                //заглушка
                source: "/demo/asd.jpg"
            }


            Text{
                id: chatName

                Layout.fillWidth: true
                Layout.margins: 5
                Layout.minimumHeight: 50
                Layout.minimumWidth: 50
                Layout.maximumWidth: -1
                Layout.maximumHeight: 50

                text: "Eba"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft

                renderType: Text.NativeRendering
                font.pixelSize: 14
            }


            Button{
                id: chatToolsButton

                Layout.fillWidth: true
                Layout.margins: 5
                Layout.minimumHeight: 50
                Layout.minimumWidth: 50
                Layout.maximumWidth: 50
                Layout.maximumHeight: 50

                text: "..."
                font.pixelSize: 22
                font.bold: true
            }
        }
    }


    //////////////////////////////////////////////////////////////////////



        ChatListView{
            id: listView
            anchors.fill: parent
            model: ChatMessagesModel{id: messages}
        }



    //////////////////////////////////////////////////////////////////////


    footer: ToolBar{
        RowLayout {
            id: bottomLayout
            anchors.fill: parent

            Button{
                id: chatAddContent

                Layout.fillWidth: true
                Layout.margins: 5
                Layout.minimumHeight: 50
                Layout.minimumWidth: 50
                Layout.maximumWidth: 50
                Layout.maximumHeight: 50

                background: Rectangle {
                    radius: 10

                    color: parent.hovered ? "#a0dea0" : "#efefef" //"white"
                }

                contentItem: Image {
                    id: affiximg
                    source: "/img/affix.png"
                }
            }


            ScrollView{
                Layout.fillWidth: true
                Layout.topMargin: 5
                Layout.bottomMargin: 5
                Layout.minimumHeight: 50
                Layout.minimumWidth: 50
                Layout.maximumWidth: -1
                Layout.maximumHeight: (chatPage.height - chatPage.header.height)/3


                TextArea {
                    id: chatMessageField
                    selectByMouse: true

                    wrapMode: TextEdit.Wrap
                    renderType: Text.NativeRendering
                    textMargin: 3

                    background: Rectangle{
                        color:"white"
                    }
                }
            }


            Button{
                id: chatSend

                Layout.fillWidth: true
                Layout.margins: 5
                Layout.minimumHeight: 50
                Layout.minimumWidth: 50
                Layout.maximumWidth: 50
                Layout.maximumHeight: 50

                background: Rectangle {
                    radius: 10

                    color: parent.hovered ? "#a0dea0" : "#efefef" //"white"
                }

                contentItem: Image {
                    id: sendimg
                    source: "/img/send.png"
                }

                onClicked: {
                    messages.append({"guid": 1, "messText":chatMessageField.text, "messTime": "18:00"})
                    listView.positionViewAtEnd()
                    chatMessageField.clear()
                }
            }
        }
    }
}
