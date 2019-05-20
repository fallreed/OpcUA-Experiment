import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

RowLayout {
    TextField {
        id: uaUrl
        Layout.fillWidth: true

        background: Rectangle {
            color: "black"
            border.color: "white"
            implicitHeight: 40
        }

        text: "opc.tcp://127.0.0.1:4840"
        color: "white"
    }

    Button {
        text: uiModel.connected ? "Disconnect" : "Connect"
        onClicked: {
            uiModel.handleButtonConnect_Clicked(uaUrl.text)
        }
    }
}
