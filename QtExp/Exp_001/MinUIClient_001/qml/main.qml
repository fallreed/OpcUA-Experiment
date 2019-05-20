import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Layouts 1.3

Window {
    visible: true
    width: 600
    height: 450
    minimumWidth: 600
    minimumHeight: 450

    color: "black"

    title: qsTr("Simple UA client")

    ColumnLayout {
        anchors.margins: 10
        anchors.fill: parent
        spacing: 10

        ConnectPanel {}

        MainPanel {}

        StatusBar {}

    }

}
