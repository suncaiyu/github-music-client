import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4

Window {
    signal urlText(var str)
    id : root
    width:300
    height:60
    TextField {
        id : tf
        anchors.fill: parent
        placeholderText: "请输入api地址"
        onAccepted: {
            if(tf.text.length == 0) {
                return
            }

            urlText(tf.text)
            root.hide()
        }
    }
}
