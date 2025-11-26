import QtQuick
import QtQuick.Layouts

Item {
    id: debugTab
    anchors.fill: parent

    Rectangle {
        anchors.fill: parent 

        RowLayout {
            Text {
                text: "this is debug tab"
            }
        }
    }
}
