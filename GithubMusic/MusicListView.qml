import QtQuick 2.0
import Furrain.HttpManager 1.0
Item {
    id : root
    property alias mModel: listView.model
    property alias mLv: listView
    signal doubleclicked(var index)
    ListView {
        id : listView
        height:root.height
        width: root.width
        delegate: dele
        highlight: Rectangle{
            color:Qt.rgba(203 / 255, 236 / 255, 234 / 255, 255 / 255);
        }
        highlightMoveDuration: 500
    }

    Component {
        id : dele
        Item{
            id : root_item
            x:0;
            y:0
            width:listView.width
            height:30
            Row{
                id : row
                x: 10
                height : parent.height
                y : 0
                width : parent.width - 10
                spacing: 10
                Text {
                    height:parent.height
                    width : 20
                    font.family: "FontAwesome"
                    font.pixelSize: 20
                    verticalAlignment: Text.AlignVCenter//垂直居中
                    text: "\uf001"
                }
                Text {
                    width : parent.width - 30
                    height : parent.height
                    verticalAlignment: Text.AlignVCenter//垂直居中
                    text: modelData
                }
            }

            MouseArea{
                anchors.fill:parent
                onClicked: {
                    listView.currentIndex = index
                }
                onDoubleClicked: {
                    doubleclicked(index)
                    HttpManager.downLoad(HttpManager.processJson.urlList[index], HttpManager.processJson.nameList[index])
                }
            }
        }
    }
}
