import QtQuick 2.0

Item {
    signal getMusicList(var url)
    signal showAddWindow()
    property alias panemodel: listmodel
    id : root
    clip: true
    Rectangle{
        anchors.fill: parent
        border.width: 1
        border.color: "lightgray"
        Column{
            width : root.width
            Rectangle{
                height: 50
                width : root.width - 1
                Text {
                    id: title
                    text: "Github Music"
                    font.pixelSize: 20
                    anchors.centerIn: parent
                }
            }
            Row {
                id : row
                height: 25
                width:root.width - 1
                Rectangle {
                    width: parent.width
                    height:parent.height
                    color : Qt.rgba(87/255, 135/255, 146/255, 255/ 255)
                    Text {
                        width : 100
                        height : 25
                        text: qsTr("收藏的歌单")
                        color : "white"
                        verticalAlignment: Text.AlignVCenter//垂直居中
                    }
                    Text {
                        x: parent.width - 20
                        y : 0
                        width:20
                        height:parent.height
                        font.family: "FontAwesome"
                        font.pixelSize: 18
                        verticalAlignment: Text.AlignVCenter//垂直居中
                        text: "\uf0fe"
                        color : "white"
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                showAddWindow()
                            }
                        }
                    }
                }
            }

            ListView{
                width: root.width - 1
                height : root.height - 50
                id: lv
                delegate:del
                model: listmodel
                highlight: hightlight
            }
        }
    }



    ListModel {
        id : listmodel
        ListElement {
            singername: "陈奕迅";
            musicurl : "https://api.github.com/repos/music-repo-chi/chi-music/contents/%E9%99%88%E5%A5%95%E8%BF%85";
        }
        ListElement {
            singername: "周杰伦";
            musicurl : "https://api.github.com/repos/music-repo-chi/chi-music/contents/%E5%91%A8%E6%9D%B0%E4%BC%A6";
        }
        ListElement {
            singername: "丁旭的歌单";
            musicurl : "https://api.github.com/repos/onedx1943/music/contents";
        }
        ListElement {
            singername: "徐杰的歌单";
            musicurl : "https://api.github.com/repos/xujie-1994/music/contents";
        }
        ListElement {
            singername: "李家辉的歌单";
            musicurl : "https://api.github.com/repos/ljh3675/relax/contents";
        }
        ListElement {
            singername: "五月天";
            musicurl : "https://api.github.com/repos/jay1song/mayday/contents";
        }
        ListElement {
            singername: "林俊杰";
            musicurl : "https://api.github.com/repos/jay1song/forjj/contents";
        }
    }

    Component{
        id:del
        Item {
            width:parent.width
            height:30
            Text {
                x: 10
                y : 0
                width: 20
                height:parent.height
                font.family: "FontAwesome"
                font.pixelSize: 18
                verticalAlignment: Text.AlignVCenter//垂直居中
                text: "\uf006"
            }
            Text {
                x: 40
                y : 0
                width: parent.width - 40
                height:parent.height
                //                horizontalAlignment: Text.AlignHCenter//水平居中
                verticalAlignment: Text.AlignVCenter//垂直居中
                text:singername
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    lv.currentIndex = index;
                }
                onDoubleClicked: {
                    getMusicList(musicurl)
                }
            }
        }
    }
    Component {
        id : hightlight
        Rectangle{
            color: Qt.rgba(156 / 255,190/255,207/255,255/255);
        }
    }
}
