import QtQuick
import QtQuick.Controls

Item {
    id: root
    width: 100
    height: 30
    property string btnLabel

    Button {
        id: button
        text: root.btnLabel
        background: Rectangle {
            color: button.down ? "#d6d6d6" : "#f6f6f6"
            border.color: "#26282a"
            border.width: 1
            radius: 4
        }
    }
}