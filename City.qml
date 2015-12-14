import QtQuick 2.0

Rectangle{
    id: _root
    width: 20
    height: 20
    radius: width/2
    color: "blue"
    MouseArea{
        anchors.fill: parent
        onClicked: {
            for(var i=0;i<_root.parent.points.length;i++){
                if (_root.parent.points[i] ==_root)
                    _root.parent.points.splice(i,1)
            }
            _root.destroy()
        }
    }
}

