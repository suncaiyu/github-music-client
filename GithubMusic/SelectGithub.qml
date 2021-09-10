import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
Window {
    signal addNameUrl(var name, var url)
    id : root
    width:300
    height:90
    ColumnLayout{
        anchors.fill: parent
        TextField {
            Layout.fillWidth: true
            id : tfName
            placeholderText: "请输入歌单名称"
            onAccepted: {
                if(tf.text.length == 0) {
                    return
                }

                urlText(tf.text)
                root.hide()
            }
        }
        TextField {
            id : tfUrl
            Layout.fillWidth: true
            placeholderText: "请输入api地址"
        }
        Button {
            id : sure
            Layout.fillWidth: true
            text: "Sure"
            onClicked: {
                if (tfName.text.length == 0 || tfUrl.text.length == 0) {
                    return
                }
                addNameUrl(tfName.text, tfUrl.text)
            }
        }
    }
}
