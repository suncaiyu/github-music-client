import QtQuick 2.0
import Qt.labs.platform 1.1
Item {
    SystemTrayIcon {
        visible: true
        icon.source: "qrc:/font/res/Music.png"
        onActivated: {
            if (reason === SystemTrayIcon.Trigger) {
                ww.show()
                ww.raise()
                ww.requestActivate()
            }
        }
        menu: Menu {
            MenuItem {
                text: qsTr("Quit")
                onTriggered: Qt.quit()
            }
        }
    }
}
