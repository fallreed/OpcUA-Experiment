import QtQuick 2.11
import QtQuick.Layouts 1.3

RowLayout {
    Text {
        Layout.fillWidth: true
        font.pointSize: 10
        color: "white"
        text: uiModel.statusBarMessage
    }
}
