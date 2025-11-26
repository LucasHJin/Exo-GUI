import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root
    width: 250
    height: 26
    property string labelText: "Label Text"
    property string inputValue: ""
    property color backgroundColor: "#f0f0f0"
    property color borderColor: "gray"
    property int borderRadius: 3
    property int fontSize: 10
    property var inputValidator: DoubleValidator {}

    RowLayout {
        anchors.fill: parent
        spacing: 10
        Layout.alignment: Qt.AlignVCenter
        Layout.preferredHeight: labelItem.height

        Text {
            id: labelItem
            text: root.labelText
            Layout.preferredWidth: parent.width * 0.4
            Layout.fillHeight: true
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.Wrap           // allow wrapping
            maximumLineCount: 2           // optional: limit lines
        }

        Rectangle {
            width: root.width * 0.6       // remaining width
            height: root.height
            Layout.alignment: Qt.AlignVCenter
            color: root.backgroundColor
            radius: root.borderRadius

            Rectangle {  // Bottom border
                height: 2
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                color: root.borderColor
            }

            TextInput {
                id: inputField
                anchors.fill: parent
                anchors.margins: 0
                verticalAlignment: TextInput.AlignVCenter
                anchors.leftMargin: 5
                font.pointSize: root.fontSize
                color: "black"
                validator: root.inputValidator
                inputMethodHints: Qt.ImhDigitsOnly | Qt.ImhFormattedNumbersOnly
                cursorVisible: true

                // Bind TextInput text to root.inputValue dynamically
                text: root.inputValue
                onTextChanged: root.inputValue = text
            }
        }
    }
}
