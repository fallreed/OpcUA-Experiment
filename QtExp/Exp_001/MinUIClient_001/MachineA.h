#ifndef MACHINEA_H
#define MACHINEA_H

#include <QObject>
#include <QtOpcUa>

class MachineA : public QObject
{
  Q_OBJECT
public:
  explicit MachineA(QObject *parent = nullptr) : QObject(parent) {}

  virtual bool isConnected() const = 0;
  virtual void connectToEndPoint(const QString& url) = 0;
  virtual void disconnectFromEndPoint() = 0;
  virtual void toggleBValue() = 0;
  virtual void toggleCValue() = 0;
  virtual void toggleDValue() = 0;

signals:
  void connectionStatusChanged(const bool status);
  void connectionStatusMessage(const QString& str);
  void variableAChanged(const qint32 value);
  void variableBChanged(const bool value);
  void variableCChanged(const bool value);
  void variableDChanged(const bool value);
  void variableEChanged(const qint32 value);

};

#endif // MACHINEA_H
