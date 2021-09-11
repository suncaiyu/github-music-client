import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

Item {
    property alias musicSlider: timeSlider
    property alias nowValue: v.nowValue
    property var total: 0
    property var now: 0
    signal pauseMusic()
    signal playMusic()
    signal stopMusic()
    signal timeChanged(var time)
    property bool isPlay: false
    id : root

    onTotalChanged: {
        var r = getString(total)
        musictime.text = musictime.text.substring(0, 5) + "/" + r[0] + ":" + r[1]
    }

    onNowChanged: {
        var r = getString(now)
        musictime.text = r[0] + ":" + r[1] + musictime.text.substring(5, 11)
    }

    Rectangle{
        id : base
        anchors.fill: parent
        border.width: 1
        border.color: "gray"

        Column {
            anchors.fill: parent
            Slider{
                x: 5
                id : timeSlider
                height : 50
                width : root.width - 10
                value: 0.5
                onValueChanged: {
                    timeChanged(value)
                }
            }
            RowLayout {
                width:parent.width
                Rectangle {
                    id : showtime
                    width : 100
                    Layout.fillHeight: true
                    Layout.alignment: Qt.AlignLeft
                    Layout.leftMargin: 5
                    Text {
                        id: musictime
                        anchors.fill: parent
                        verticalAlignment: Text.AlignVCenter//垂直居中
                        font.pixelSize: 18
                        text: qsTr("00:00/00:00")
                    }
                }
                RowLayout {
                    id : buttonGroup
                    spacing: 20
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Text {
                        font.family: "FontAwesome"
                        font.pixelSize: 30
                        verticalAlignment: Text.AlignVCenter//垂直居中
                        text: "\uf048"
                    }
                    Text {
                        id : playorpause
                        font.family: "FontAwesome"
                        font.pixelSize: 30
                        verticalAlignment: Text.AlignVCenter//垂直居中
                        // \uf04c
                        text: "\uf04b"
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                if (isPlay) {
                                    pauseMusic()
                                } else {
                                    playMusic()
                                }
                            }
                        }
                    }
                    Text {
                        id : stop
                        font.family: "FontAwesome"
                        font.pixelSize: 30
                        verticalAlignment: Text.AlignVCenter//垂直居中
                        text: "\uf04d"
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                stopMusic()
                            }
                        }
                    }
                    Text {
                        id: next
                        font.family: "FontAwesome"
                        font.pixelSize: 30
                        verticalAlignment: Text.AlignVCenter//垂直居中
                        text: "\uf051"
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {

                            }
                        }
                    }
                }
                Rectangle {
                    id : volumnicon
                    width : 100
                    height : buttonGroup.height
//                    Layout.fillHeight: true
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                    Layout.rightMargin: 10
                    Text {
                        id : volume
                         anchors.centerIn: parent
                        font.family: "FontAwesome"
                        font.pixelSize: 20
                        verticalAlignment: Text.AlignVCenter//垂直居中
                        text: "\uf028"
                        MouseArea{
                            anchors.fill: parent
                            hoverEnabled: true
                            onClicked:  {
                                var yyy = mapToItem(root, x, y)
                                v.x = yyy.x - 15
                                v.y = yyy.y - v.height
                                v.open()
                            }
                        }
                    }
                }
            }
        }
    }

    function changePlay() {
        playorpause.text = "\uf04c"
        isPlay = true
    }

    function changePause() {
        playorpause.text = "\uf04b"
        isPlay = false
    }

    function getString(t) {
        var time = t / 1000
        var m = parseInt(time / 60)
        var s = parseInt(time - m * 60)
        var ss =  s.toString()
        if (ss.length === 1) {
            ss = "0" + ss;
        }
        var sm = m.toString()
        if (sm.length === 1) {
            sm = "0" + sm;
        }
        return[sm, ss]
    }

    Volumn {
        id : v
        x: 10
        y : -20
    }
}
