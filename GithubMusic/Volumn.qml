import QtQuick 2.0
import QtQuick.Controls 2.14

Popup {
    property alias nowValue: control.value
    id: popup
    x: 100
    y: 100
    width: 50
    height: 150
    modal: true
    focus: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside | Popup.CloseOnReleaseOutside
    Slider{
        id : control
        orientation: Qt.Vertical
        anchors.fill: parent
        value: 1
    }

    background: Rectangle{
        border.width: 1
        border.color: "lightgray"
        radius: 15
    }

    Overlay.modal: Rectangle{
        color : "transparent"
    }
}
