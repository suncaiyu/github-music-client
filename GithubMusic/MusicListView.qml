import QtQuick 2.0
import Furrain.HttpManager 1.0
import QtQuick.Controls 2.14


Item {
    id : root
    property alias mModel: listView.model
    property alias mLv: listView
    signal doubleclicked(var index)
    property var sindex : 0
    Column {
        anchors.fill: parent
        Rectangle {
            height:30
            width: parent.width
            Row {
                anchors.fill: parent
                TextField {
                    id : stext
                    height: parent.height
                    width:parent.width - 80
                    placeholderText: "Search Text Input"
                }
                Button{
                    height: parent.height
                    width: 80
                    text: "Search"
                    onClicked: {
                        for (var i = sindex; i < mModel.length; ++i) {
                            var name = mModel[i]
                            if (name.indexOf(stext.text) != -1) {
                                sindex = i + 1;
                                listView.currentIndex = i;
                                return;
                            }
                        }
                        sindex = 0
                    }
                }
            }
        }

        ListView {
            id : listView
            height:parent.height - 30
            width: parent.width
            delegate: dele
            highlight: Rectangle{
                color:Qt.rgba(203 / 255, 236 / 255, 234 / 255, 255 / 255);
            }

            ScrollBar.vertical: ScrollBar {
                id: scrollBar
            }
            highlightMoveDuration: 500
            clip: true
        }
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
