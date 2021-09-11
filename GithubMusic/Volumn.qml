import QtQuick 2.0
import QtQuick.Controls 2.14

Popup {
    property alias nowValue: control.value
    id: popup
    x: 100
    y: 100
    width: 40
    height: 150
    modal: true
    focus: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside | Popup.CloseOnReleaseOutside
    Slider{ // qml 2.0 的slider
        id : control
        orientation: Qt.Vertical
        anchors.fill: parent
        value: 1
        handle: Rectangle{
            x:control.leftPadding + control.availableWidth / 2 - width / 2
            y:control.bottomPadding + control.visualPosition * (control.availableHeight - height)
            implicitWidth: 20
            implicitHeight: 20
            radius: 10
            color: control.pressed ? "#f0f0f0" : "#f6f6f6"
            border.color: "#bdbebf"
        }
        background: Rectangle{
            x:control.leftPadding + control.availableWidth / 2 - width / 2
            y:control.bottomPadding
            width : 6
            height : control.availableHeight
            color: "lightgray"
            radius: 3
            Rectangle{
                y : control.visualPosition * parent.height
                width : parent.width
                height: parent.height - control.visualPosition * parent.height
                radius: 3
                gradient: Gradient{
                    GradientStop{
                        position: 0
                        color : "red"
                    }
                    GradientStop{
                        position: 1
                        color:"blue"
                    }
                }
            }
        }
    }

    background: Rectangle{
        border.width: 1
        border.color: "lightgray"
        radius: 20
    }

    Overlay.modal: Rectangle{
        color : "transparent"
    }
}
