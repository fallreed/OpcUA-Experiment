#ifndef MACHINEA_UIMODEL_H
#define MACHINEA_UIMODEL_H

#include "UIModel.h"

class MachineA;

class UIMachineA : public UIModel
{
  Q_OBJECT
public:
  explicit UIMachineA(MachineA& machine, QObject *parent = nullptr);

  bool isConnected() const override;
  QString statusBarMessage() const override;
  qint32 valueA() const override;
  bool indicatorBValue() const override;
  bool indicatorCValue() const override;
  bool indicatorDValue() const override;
  qint32 valueE() const override;

public slots:
  void handleButtonConnect_Clicked(const QString& opcurl) override;
  void handleButtonB_Clicked() override;
  void handleButtonC_Clicked() override;
  void handleButtonD_Clicked() override;
  void handleClientConnectionStatus(const bool state) override;
  void handleClientConnectionStatusMsg(const QString& str) override;
  void handleClientAValueChanged(const qint32 val) override;
  void handleClientBValueChanged(const bool val) override;
  void handleClientCValueChanged(const bool val) override;
  void handleClientDValueChanged(const bool val) override;
  void handleClientEValueChanged(const qint32 val) override;

private:
  MachineA& m_machineA;

  void connectDeviceClientSignals();
};

#endif // MACHINEA_UIMODEL_H
