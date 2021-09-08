import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtMultimedia 5.9
import Furrain.HttpManager 1.0
import Furrain.ProcessJson 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ListView {
        id : listView
        anchors.fill:parent
        delegate: Item{
            id : root_item
            x:0;
            y:0
            width:listView.width
            height:45
            Text {
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter//垂直居中
                text: modelData
            }
            Text {
                id : play
                x:parent.width - parent.height +8
                y : 0
                width:parent.height-8
                height : parent.height
                font.family: "FontAwesome"
                font.pixelSize: 30
                verticalAlignment: Text.AlignVCenter//垂直居中
                text: "\uf04b"
            }
            MouseArea{
                anchors.fill:parent
                onClicked: {
                    if (mouseX < root_item.width - root_item.height) {
                        listView.currentIndex = index
                    } else {
                        HttpManager.downLoad(processJson.urlList[index], processJson.nameList[index])
                    }
                }
                onDoubleClicked: {
                    console.log(processJson.urlList[index])
                    HttpManager.downLoad(processJson.urlList[index], processJson.nameList[index])
                }
            }
        }
        highlight: Rectangle{
            color:"hotpink";
        }
        highlightMoveDuration: 500
    }

    ProcessJson {
        id : processJson
    }

    //    MouseArea {
    //        anchors.fill: parent
    //        onClicked: {
    //            HttpManager.getNetworkInfo("https://api.github.com/repos/music-repo-chi/chi-music/contents/%E9%99%88%E5%A5%95%E8%BF%85");
    //        }
    //    }
    Connections {
        target: HttpManager
        onUrlGetInfo:{
            processJson.process(info)
            var l1 = processJson.nameList;
            listView.model = l1
        }
        onReadyOk:{
            console.log("file:/" + name)
            player.source =  "file:/" + name
            player.volume = 0.8
            player.play();
        }
    }
    Item {
        id: root
        focus: true
        anchors.fill: parent
        Keys.onPressed: {
            if(event.modifiers === Qt.ControlModifier && event.key === Qt.Key_O) {
                iii.show()
            }
        }
    }
    SelectGithub {
        id : iii
        visible: false
        //        "https://api.github.com/repos/music-repo-chi/chi-music/contents/%E9%99%88%E5%A5%95%E8%BF%85"
        onUrlText: {
            //            player.source =  "file:/" + "D:/QtProject/build-GithubMusic-Desktop_Qt_5_14_0_MinGW_32_bit-Debug/Music/1874-陈奕迅.mp3"
            //            player.volume = 0.8
            //            player.play();
            HttpManager.getNetworkInfo(str);
        }
    }
    MediaPlayer{
        id:player
    }
}
