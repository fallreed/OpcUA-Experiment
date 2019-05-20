import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Extras 1.4

Column {
    id: indicatorBtn
    spacing: 20

    property alias buttonText: roundBtn.text
    property alias status: indicator.active
    signal clicked()

    StatusIndicator {
        id: indicator
        anchors.horizontalCenter: parent.horizontalCenter
        color: "green"
    }

    RoundButton {
        id: roundBtn
        anchors.horizontalCenter: parent.horizontalCenter

        onClicked: {
            indicatorBtn.clicked()
        }
    }

}
