import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: plotTab
    anchors.fill: parent

    Rectangle {
        anchors.fill: parent
        color: "black"

        ColumnLayout {
            anchors.fill: parent

            RowLayout {
                anchors.top: parent.top
                anchors.left: parent.left
                Button {
                    id: plotPauseBtn 
                    text: "Pause"
                    background: Rectangle {
                        color: plotPauseBtn.down ? "#63C5DA" : "#48AAAD"
                        radius: 4
                    }
                }
                Button {
                    id: plotResetZoomBtn 
                    text: "Reset Zoom"
                    background: Rectangle {
                        color: plotResetZoomBtn.down ? "#63C5DA" : "#48AAAD"
                        radius: 4
                    }
                }
                Button {
                    id: plotClearBtn 
                    text: "Clear Plot"
                    background: Rectangle {
                        color: plotClearBtn.down ? "#63C5DA" : "#48AAAD"
                        radius: 4
                    }
                }
            }

        }
    }
}
