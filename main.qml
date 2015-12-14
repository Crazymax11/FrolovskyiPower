import QtQuick 2.4
import QtQuick.Controls 1.3

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    id: root
    signal start(string name, string data)

    signal result(string time, real res)
    onResult: resText.text = time + " " + res
    Rectangle{
        id: map
        width: parent.height * 0.8
        height: width
        color: "pink"

        property var points: []
        MouseArea {
            anchors.fill: parent
            onClicked: {
                var component = Qt.createComponent("City.qml");
                var object = component.createObject(map);
                object.x = mouse.x - 10
                object.y = mouse.y - 10
                map.points.push(object)
            }
        }
    }

    ComboBox{
        id: functionList
        anchors.top : parent.top
        anchors.left: map.right
        width: 100
        height: 30
        model: ["Метод прямого исчерпывающего перебора вариантов","Метод ветвей и границ","Метод динамического программирования","Генетические алгоритмы","Метод системы муравьев и муравьиных колоний"]
    }
    Rectangle{
        id: startBtn
        anchors.left: functionList.right
        anchors.top: parent.top
        width: 100
        height: 30
        Text{
            anchors.fill: parent
            text: "start"
            font.pointSize: 50
            fontSizeMode: Text.VerticalFit
            horizontalAlignment: Text.AlignHCenter
        }

        MouseArea{
            id: startBtnMouseArea
            anchors.fill: parent
            onClicked: {
                var methodName = functionList.currentText
                var data = ""
                for(var i=0;i<map.points.length;i++){
                    data+=(map.points[i].x+10)/map.width + "!" +(map.points[i].y+10)/map.height + ";"
                }
                root.start(methodName, data)
            }
        }
    }
    Rectangle{
        id: resRect
        anchors.left: map.right
        anchors.top: functionList.bottom
        width: 100
        height: 30
        color: "gray"
        Text{
            id: resText
            anchors.fill: parent
            font.pointSize: 50
            fontSizeMode: Text.VerticalFit
            horizontalAlignment: Text.AlignHCenter
        }
    }
}

