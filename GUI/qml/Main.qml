import QtQuick
import QtQuick.Layouts
import gui

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
            anchors.margins: 10
            width: 600
            Layout.fillHeight: true
            spacing: 10

            ColumnLayout {
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

                MyButton {
                    id: inputBtn
                    btnLabel: "Update"
                }
            }
            
            ColumnLayout {
                Text {
                    text: "Motor Config"
                    font.bold: true
                }
                MyTextInput {
                    labelText: "kP"
                }
                MyTextInput {
                    labelText: "kI"
                }
                MyTextInput {
                    labelText: "kD"
                }

                MyButton {
                    id: pidBtn
                    btnLabel: "Update"
                }
            }

            
        }

        //right panel
        Panel2 {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
