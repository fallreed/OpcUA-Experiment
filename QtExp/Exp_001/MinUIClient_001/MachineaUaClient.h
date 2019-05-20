#ifndef MACHINEAUACLIENT_H
#define MACHINEAUACLIENT_H

#include "MachineA.h"

class MachineAUAClient final : public MachineA
{
  Q_OBJECT
public:
  explicit MachineAUAClient(QObject *parent = nullptr);
  ~MachineAUAClient() override;

  bool isConnected() const override;
  void connectToEndPoint(const QString& url) override;
  void disconnectFromEndPoint() override;
  void toggleBValue() override;
  void toggleCValue() override;
  void toggleDValue() override;

public slots:
  void handleClientState(const QOpcUaClient::ClientState state);
  void handle_VariableA_Update(const QOpcUa::NodeAttribute attr, const QVariant& value);
  void handle_VariableB_Update(const QOpcUa::NodeAttribute attr, const QVariant& value);
  void handle_VariableC_Update(const QOpcUa::NodeAttribute attr, const QVariant& value);
  void handle_VariableD_Update(const QOpcUa::NodeAttribute attr, const QVariant& value);
  void handle_VariableE_Update(const QOpcUa::NodeAttribute attr, const QVariant& value);

private:
  QScopedPointer<QOpcUaClient> m_client;
  QScopedPointer<QOpcUaNode> m_myDeviceNode;
  QScopedPointer<QOpcUaNode> m_variableANode;
  QScopedPointer<QOpcUaNode> m_variableBNode;
  QScopedPointer<QOpcUaNode> m_variableCNode;
  QScopedPointer<QOpcUaNode> m_variableDNode;
  QScopedPointer<QOpcUaNode> m_variableENode;

  bool m_connected {false};
  QString m_uabackend {"open62541"};
  qint32 m_varA_Value {0};
  bool m_varB_Value {false} ;
  bool m_varC_Value {false};
  bool m_varD_Value {false};
  qint32 m_varE_Value {0};

  void createNodeObjects();
  void connectNodeObjectsSignals();
  void subscribeToDataChanges();

};

#endif // MACHINEAUACLIENT_H
