import QtQuick 2.4
import QtQuick.Window 2.2
import videoitem 1.5

Window {
    visible: true
    height: 300;
    width:500;
    VideoItem {
        id:v
        anchors.fill: parent;
        Component.onCompleted: {
            v.setSource("e:/test/1.flv");
            v.play();
        }
    }

}
