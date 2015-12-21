import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    id: root
    signal start(string name, variant data)
    signal result(string time, real res)

    onResult: resText.text = time + " " + res
    RowLayout{
        anchors.fill: parent
        Item{
            Layout.fillWidth: true
            Layout.fillHeight: true
            id: map
            objectName: "map"
            width: parent.height * 0.8
            height: width
            property var lines: []
            property var lineComp
            property var colors: ["yellow", "blue", "green", "purple"]
            Component.onCompleted: lineComp = Qt.createComponent("Line.qml");
            function serialize(){
                var result = []
                for(var i=0;i<map.points.length;i++){
                    result.push({"x": map.points[i].cityX,
                                  "y": map.points[i].cityY,
                                  "name": map.points[i].cityName})
                }
                return result
            }
            // путь -> список названий городов
            function show(path, name){
                //find line
                var curLines = "undefined"
                var color
                for(var i=0;i<lines.length;i++)
                    if (lines[i]["name"] == name){
                        curLines = lines[i]["lines"]
                        color = lines[i]["color"]
                    }
                if (curLines == "undefined"){
                    curLines = []
                    color = colors.pop()
                    lines.push({"name" : name,
                               "color": color,
                               "lines": curLines})

                }

                console.log(path.length)
                for(var k=0;k<path.length;k++)
                    console.log(path[k])
                while (curLines.length < path.length)
                    curLines.push(lineComp.createObject(map))
                var i=0
                var coordPath = []
                for(i=0;i<path.length;i++)
                    for(var j=0;j<points.length;j++)
                        if (path[i]==points[j].cityName)
                            coordPath.push({"x":points[j].cityX,
                                              "y":points[j].cityY})
                for(i=0;i<coordPath.length;i++){
                    curLines[i].x1 = coordPath[i]["x"]
                    curLines[i].y1 = coordPath[i]["y"]
                    curLines[i].x2 = coordPath[(i+1)%coordPath.length]["x"]
                    curLines[i].y2 = coordPath[(i+1)%coordPath.length]["y"]
                    curLines[i].color = color
                }
            }

            Image{
                id: mapImage
                anchors.fill: parent
                source: "qrc:/images/world.jpg"
            }

            property var points: []
            MouseArea {
                anchors.fill: parent
                property int counter: 1
                property var comp
                Component.onCompleted: comp = Qt.createComponent("City.qml");
                onClicked: {
                    var object = comp.createObject(map);
                    object.x = mouse.x - 10
                    object.y = mouse.y - 10
                    object.cityX = mouse.x
                    object.cityY = mouse.y
                    object.cityName = "" + counter
                    counter++
                    map.points.push(object)
                }
            }
        }
        Column{
            Layout.preferredWidth: parent.width * 0.2
            Layout.fillHeight: true
            id: controlColumn
            Button{
                id: bruteForceBtn
                objectName: "bruteForceBtn"
                width: controlColumn.width
                text: "Перебор"
                onClicked:{
                    root.start(text, map.serialize())
                }
            }
            Button{
                width: controlColumn.width
                id: branchBtn
                objectName: "branchBtn"
                text: "Ветви и границы"
                onClicked:{
                    root.start(text, map.serialize())
                }
            }
            Button{
                width: controlColumn.width
                id: antBtn
                objectName: "antBtn"
                text: "Муравьи"
                onClicked:{
                    root.start(text, map.serialize())
                }
            }
            Text{
                text: "Итерации " + antIterations.value
            }
            Slider{
                id: antIterations
                objectName: "antIterations"
                maximumValue: 10000
                minimumValue: 0
                stepSize: 1
                value: 500
                width: controlColumn.width
            }
            Text{
                text: "Жадность " + Math.round(antGreedy.value*100)/100
            }
            Slider{
                id: antGreedy
                objectName: "antGreedy"
                maximumValue: 1
                minimumValue: 0
                stepSize: 0.05
                value: 0.9
                width: controlColumn.width
            }
            Text{
                text: "Стадность " + Math.round(antHerdy.value*100)/100
            }
            Slider{
                id: antHerdy
                objectName: "antHerdy"
                maximumValue: 1
                minimumValue: 0
                stepSize: 0.05
                value: 0.1
                width: controlColumn.width
            }
            Text{
                text: "Испарение " + Math.round(antVaporization.value*100)/100
            }
            Slider{
                id: antVaporization
                objectName: "antVaporization"
                maximumValue: 1
                minimumValue: 0
                stepSize: 0.05
                value: 0.5
                width: controlColumn.width
            }
            Text{
                text: "карта"
            }

            ComboBox{
                id: mapEditor
                model: ["Земля", "Европа", "Россия"]
                currentIndex: 0
                property var dict: {"Земля":"qrc:/images/world.jpg",
                "Европа":"qrc:/images/europe.jpg",
                "Россия":"qrc:/images/russia.jpg"}
                onCurrentIndexChanged: mapImage.source =dict[model[currentIndex]]
            }
            Text{
                text:"результаты"
            }
            Text{
                id: bruteForceResult
                objectName: "bruteForceResult"
                wrapMode: Text.WordWrap
            }
            Text{
                id: branchedResult
                objectName: "branchedResult"
                wrapMode: Text.WordWrap
            }
            Text{
                id: antColonyResult
                objectName: "antColonyResult"
                wrapMode: Text.WordWrap
            }
        }
    }


    Line{
        visible: false
        id: line
        x1:0
        y1:0
        x2:20
        y2:20
        Behavior on x1 {
            NumberAnimation {
                //This specifies how long the animation takes
                duration: 600
                //This selects an easing curve to interpolate with, the default is Easing.Linear
            }
        }
        Behavior on y1 {
            NumberAnimation {
                //This specifies how long the animation takes
                duration: 600
                //This selects an easing curve to interpolate with, the default is Easing.Linear
            }
        }
        Behavior on x2 {
            NumberAnimation {
                //This specifies how long the animation takes
                duration: 600
                //This selects an easing curve to interpolate with, the default is Easing.Linear
            }
        }
        Behavior on y2 {
            NumberAnimation {
                //This specifies how long the animation takes
                duration: 600
                //This selects an easing curve to interpolate with, the default is Easing.Linear
            }
        }

    }

//    ComboBox{
//        id: functionList
//        anchors.top : parent.top
//        anchors.left: map.right
//        width: 100
//        height: 30
//        model: ["Метод ветвей и границ","Метод динамического программирования","Генетические алгоритмы","Метод системы муравьев и муравьиных колоний"]
//    }
//    Rectangle{
//        id: startBtn
//        anchors.left: functionList.right
//        anchors.top: parent.top
//        width: 100
//        height: 30
//        Text{
//            anchors.fill: parent
//            text: "start"
//            font.pointSize: 50
//            fontSizeMode: Text.VerticalFit
//            horizontalAlignment: Text.AlignHCenter
//        }

//        MouseArea{
//            id: startBtnMouseArea
//            anchors.fill: parent
//            onClicked: {
//                var methodName = functionList.currentText

//            }
//        }
//    }
//    Rectangle{
//        id: resRect
//        anchors.left: map.right
//        anchors.top: functionList.bottom
//        width: 100
//        height: 30
//        color: "gray"
//        Text{
//            id: resText
//            anchors.fill: parent
//            font.pointSize: 50
//            fontSizeMode: Text.VerticalFit
//            horizontalAlignment: Text.AlignHCenter
//        }
//    }
}

