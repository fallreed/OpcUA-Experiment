import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4

Frame {
    Layout.fillHeight: true
    Layout.fillWidth: true

    FontLoader {
      id: digital7Font
      source: "assets/fonts/digital-7.ttf"
    }

    GridLayout {
        columns: 2
        rows: 2
        anchors.fill: parent

        CircularGauge {
            id: cirGaugeValue
            value: uiModel.circleGaugeValue
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.rowSpan: 2
        }

        Text {
            id: numValue
            text: uiModel.numValue
            color: "white"
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            font.family: digital7Font.name
            font.pointSize: 50
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            IndicatorButton {
              buttonText: "B"
              status: uiModel.indicatorBValue
              onClicked: {
                uiModel.handleButtonB_Clicked()
              }
            }

            IndicatorButton {
              buttonText: "C"
              status: uiModel.indicatorCValue
              onClicked: {
                uiModel.handleButtonC_Clicked()
              }
            }

            IndicatorButton {
              buttonText: "D"
              status: uiModel.indicatorDValue
              onClicked: {
                uiModel.handleButtonD_Clicked()
              }
            }
        }

    }
}
