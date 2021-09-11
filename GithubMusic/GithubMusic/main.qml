import QtQuick 2.12
import QtQuick.Window 2.3
import QtQuick.Controls 2.14
import QtMultimedia 5.9
import Furrain.HttpManager 1.0
import Furrain.ProcessJson 1.0
import Qt.labs.platform 1.1
import QtQuick.Dialogs 1.3
import QtQuick.Particles 2.14
Window {
    // 逻辑 当双击后先变为false，此时会把上一首歌的停掉，不自动播放下一首，当播放时，变为true，此时播放结束后会自动播放下一首
    // 点击停止按钮后变为false，不自动播放下一首
    property bool playnext: true
    property var playintIndex: 0
    visible: true
    width: 640
    height: 480
    title: qsTr("Furrain Music")
    id : ww;
    onClosing:{
        close.accepted = false;
        ww.hide();
    }

    Column {
        Row{
            id : mainrow
            width : ww.width
            height : ww.height - 100;
            MainPane{
                id : pane
                width:150
                height:mainrow.height
                onGetMusicList: {
                    HttpManager.getNetworkInfo(url);
                }
                onShowAddWindow: {
                    iii.show()
                }
            }
            MusicListView {
                id : listview
                height:mainrow.height
                width: mainrow.width - pane.width
                onDoubleclicked: {
                    playintIndex = index
                    player.pause()
                    playnext = false;
                }
            }
        }


        ControlBar {
            id : control
            height : 100
            width:mainrow.width
            onTimeChanged: {
                if (Math.abs(time - player.position) >1000 ) {
                    player.seek(time)
                }
            }
            onPauseMusic: {
                player.pause()
            }
            onPlayMusic: {
                playnext = true
                player.play()
            }
            onStopMusic: {
                control.musicSlider.value = 0
                playnext = false;
                player.stop()
            }
            onNowValueChanged: {
                player.volume = nowValue
            }
        }
    }

    Connections {
        target: HttpManager
        onReadyOk:{
            console.log("file:/" + name)
            player.source =  "file:/" + name
            player.volume = control.nowValue
            control.musicSlider.value = 0
            control.now = 0
            player.play();
        }
        onUpdateList:{
            listview.mModel = HttpManager.processJson.nameList;
            playintIndex = -1;
        }
        onErrorMessageSignal:{
            calendar.text = msg
            dataDialog.open();
        }
        onDownLoadProcessSignal:{
            console.log(all, current)
            control.musicSlider.maximumValue = all;
            control.musicSlider.value = current;
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
        onAddNameUrl: {
            pane.panemodel.append({singername : name, musicurl : url})
        }
    }
    MediaPlayer{
        id:player
        notifyInterval: 1000
        onDurationChanged: {
            control.musicSlider.maximumValue = duration
            control.total = duration
        }
        onPlaybackStateChanged: {
            switch(playbackState) {
            case MediaPlayer.PlayingState :
                playnext = true
                control.changePlay()
                updateSlider.start();
                control.total = player.duration
                break;
            case MediaPlayer.StoppedState:
                control.changePause();
                updateSlider.stop();
                control.total = 0
                control.now = 0
                // 播放下一个
                if (playnext) {
                    if (playintIndex == listview.mLv.model.length - 1) {
                        playintIndex = 0
                        listview.mLv.currentIndex = 0
                    } else {
                        listview.mLv.currentIndex = playintIndex + 1
                        playintIndex = listview.mLv.currentIndex;
                    }
                    console.log(listview.mLv.currentIndex)
                    HttpManager.downLoad(HttpManager.processJson.urlList[listview.mLv.currentIndex], HttpManager.processJson.nameList[listview.mLv.currentIndex])
                }
                break;
            case MediaPlayer.PausedState:
                updateSlider.stop()
                control.changePause();
                break;
            }
        }
        onErrorStringChanged: {
            updateSlider.stop();
            console.log(errorString)
            calendar.text = errorString;
            dataDialog.open()
        }
    }

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

    Dialog {
        id: dataDialog
        visible: false
        title: "Error"
        standardButtons: Dialog.Ok

        Text {
            id: calendar
            text: "???"
        }
    }

    Timer{
        id : updateSlider;
        interval: 500
        repeat: true
        onTriggered: {
            control.musicSlider.value = player.position;
            control.now = player.position
        }
    }

    ParticleSystem{

           id: sys

       }

       ImageParticle{
            color : "green"
           system: sys
           source: "qrc:/font/res/star.png"
           colorVariation: 0.8
           rotation: 15
           rotationVariation: 5
           rotationVelocity: 45
           rotationVelocityVariation: 15
           entryEffect: ImageParticle.Scale
       }

       Emitter{

           id: startField
           system: sys

           emitRate: 60
           lifeSpan: 3500
           lifeSpanVariation: 3500

           width: ww.width
           height: ww.height

           //acceleration: PointDirection { xVariation: 200; yVariation: 200; }

           size: 0
           endSize: 40
           sizeVariation: 5
           velocity: AngleDirection{
               angle: 0
               angleVariation: 15
               magnitude: 100
               magnitudeVariation: 50
           }
       }

}
