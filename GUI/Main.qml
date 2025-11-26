import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Exo GUI")

    RowLayout {
        anchors.fill: parent

        //left sidebar
        ColumnLayout {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.margins: 4
            Layout.preferredWidth: parent.width * 0.4
            Layout.fillHeight: true
            spacing: 4

            Text {
                text: "Motor Input"
                font.bold: true
            }

            MyTextInput {
                labelText: "Target Position"
            }
            MyTextInput {
                labelText: "Target Velocity"
            }
            MyTextInput {
                labelText: "Target Torque"
            }

            Button {
                id: button
                text: "Submit"
                background: Rectangle {
                    implicitWidth: 100
                    implicitHeight: 30
                    color: button.down ? "#d6d6d6" : "#f6f6f6"
                    border.color: "#26282a"
                    border.width: 1
                    radius: 4
                }
            }
        }

        //right panel
        Rectangle {
            color: "black"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
