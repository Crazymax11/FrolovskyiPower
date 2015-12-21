import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Коммивояжерим")
    id: root
    signal start(string name, variant data)
    signal result(string time, real res)

    property var methodColors: {
        "Перебор": "blue",
        "Муравьи": "purple",
        "Ветви и границы": "green"
    }
    property var buttonColors: {
        "Перебор": {"hovered": "#59ABE3", "unhovered": "#4183D7"},
        "Муравьи": {"hovered": "#BF55EC", "unhovered": "#9A12B3"},
        "Ветви и границы": {"hovered": "#2ECC71", "unhovered": "#26A65B"}
    }

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
                    color = methodColors[name]
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
        Rectangle{
            Layout.preferredWidth: parent.width * 0.2
            Layout.fillHeight: true
            border.width: 2
            border.color: "grey"
            color: "transparent"
            Column{
                anchors.fill: parent
                anchors.margins: 5
                id: controlColumn
                Button{
                    id: bruteForceBtn
                    objectName: "bruteForceBtn"
                    width: controlColumn.width
                    text: "Перебор"
                    style: ButtonStyle{
                        background: Rectangle{
                            radius: 10
                            width: control.width
                            height: control.height
                            color: {
                                var isHovered = control.hovered? "hovered": "unhovered"
                                buttonColors[control.text][isHovered]
                            }
                        }
                    }

                    onClicked:{
                        root.start(text, map.serialize())
                    }
                    onHoveredChanged: {
                        console.log(hovered)
                        for(var i in map.lines){
                            var lines = map.lines[i]
                            console.log(lines["name"])
                            console.log(text)
                            if (lines["name"] != text)
                                for(var ind in lines["lines"])
                                    lines["lines"][ind].visible = !hovered
                        }
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
                    style: ButtonStyle{
                        background: Rectangle{
                            radius: 10
                            width: control.width
                            height: control.height
                            color: {
                                var isHovered = control.hovered? "hovered": "unhovered"
                                buttonColors[control.text][isHovered]
                            }
                        }
                    }
                    onHoveredChanged: {
                        console.log(hovered)
                        for(var i in map.lines){
                            var lines = map.lines[i]
                            console.log(lines["name"])
                            if (lines["name"] != text)
                                for(var ind in lines["lines"])
                                    lines["lines"][ind].visible = !hovered
                        }
                    }
                }
                Button{
                    width: controlColumn.width
                    id: antBtn
                    objectName: "antBtn"
                    text: "Муравьи"
                    style: ButtonStyle{
                        background: Rectangle{
                            radius: 10
                            width: control.width
                            height: control.height
                            color: {
                                var isHovered = control.hovered? "hovered": "unhovered"
                                buttonColors[control.text][isHovered]
                            }
                        }
                    }
                    onClicked:{
                        root.start(text, map.serialize())
                    }
                    onHoveredChanged: {
                        console.log(hovered)
                        for(var i in map.lines){
                            var lines = map.lines[i]
                            console.log(lines["name"])
                            if (lines["name"] != text)
                                for(var ind in lines["lines"])
                                    lines["lines"][ind].visible = !hovered
                        }
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
                    width: parent.width
                    property var dict: {"Земля":"qrc:/images/world.jpg",
                    "Европа":"qrc:/images/europe.jpg",
                    "Россия":"qrc:/images/russia.jpg"}
                    onCurrentIndexChanged: mapImage.source =dict[model[currentIndex]]
                }
                Text{
                    text:"результаты"
                }
                Text{
                    text:"время"
                }
                Text{
                    id: bruteForceResult
                    objectName: "bruteForceResult"
                    wrapMode: Text.WordWrap
                    width: parent.width
                    color: methodColors["Перебор"]
                }
                Text{
                    id: branchedResult
                    objectName: "branchedResult"
                    wrapMode: Text.WordWrap
                    width: parent.width
                    color: methodColors["Ветви и границы"]
                }
                Text{
                    id: antColonyResult
                    objectName: "antColonyResult"
                    wrapMode: Text.WordWrap
                    width: parent.width
                    color: methodColors["Муравьи"]
                }
                Text{
                    text:"длина пути"
                }
                Text{
                    id: bruteForceResultLength
                    objectName: "bruteForceResultLength"
                    wrapMode: Text.WordWrap
                    width: parent.width
                    color: methodColors["Перебор"]
                }
                Text{
                    id: branchedResultLength
                    objectName: "branchedResultLength"
                    wrapMode: Text.WordWrap
                    width: parent.width
                    color: methodColors["Ветви и границы"]
                }
                Text{
                    id: antColonyResultLength
                    objectName: "antColonyResultLength"
                    wrapMode: Text.WordWrap
                    width: parent.width
                    color: methodColors["Муравьи"]
                }
                Text{
                    text: "маршрут"
                }

                Text{
                    id: bruteForceResultRoute
                    objectName: "bruteForceResultRoute"
                    wrapMode: Text.WordWrap
                    width: parent.width
                    color: methodColors["Перебор"]
                }
                Text{
                    id: branchedResultRoute
                    objectName: "branchedResultRoute"
                    wrapMode: Text.WordWrap
                    width: parent.width
                    color: methodColors["Ветви и границы"]
                }
                Text{
                    id: antColonyResultRoute
                    objectName: "antColonyResultRoute"
                    wrapMode: Text.WordWrap
                    width: parent.width
                    color: methodColors["Муравьи"]
                }
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
}

