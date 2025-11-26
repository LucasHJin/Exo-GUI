import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: panel2

    TabBar {
        id: panel2Tabbar
        TabButton {
            text: qsTr("Debug")
        }
        TabButton {
            text: qsTr("Plot")
        }
        onCurrentIndexChanged: panel2Stack.currentIndex = currentIndex
    }

    StackLayout {
        id: panel2Stack
        anchors.top: panel2Tabbar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        DebugTab {}
        PlotTab {}
    }
}
