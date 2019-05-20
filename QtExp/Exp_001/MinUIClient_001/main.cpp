#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <memory>
#include "UIMachineA.h"
#include "MachineaUaClient.h"

int main(int argc, char *argv[])
{
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  qSetMessagePattern("[%{time}][%{file}:%{line}][%{type}] - %{message}");

  QGuiApplication app(argc, argv);

  MachineAUAClient machineA;
  std::unique_ptr<UIModel> UiModel = std::make_unique<UIMachineA>(machineA);

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("uiModel", UiModel.get());
  engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

  if (engine.rootObjects().isEmpty()) {
    return -1;
  }

  return app.exec();
}
