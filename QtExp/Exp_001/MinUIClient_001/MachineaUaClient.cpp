#include "MachineaUaClient.h"

MachineAUAClient::MachineAUAClient(QObject *parent)
  : MachineA (parent)
{
}

MachineAUAClient::~MachineAUAClient()
{
  if (m_client)
  {
    m_client->disconnectFromEndpoint();
  }
}

bool MachineAUAClient::isConnected() const
{
  return m_connected;
}

void MachineAUAClient::connectToEndPoint(const QString& url)
{
  if (m_connected) {
    return;
  }

  QStringList backends = QOpcUaProvider::availableBackends();

  if ( !m_client && backends.contains(m_uabackend) )
  {
    QOpcUaProvider provider;
    m_client.reset(provider.createClient(m_uabackend));
    if (m_client)
    {
      QObject::connect(m_client.data(), &QOpcUaClient::stateChanged,
                       this, &MachineAUAClient::handleClientState);
    }
  }

  if (!m_client)
  {
    qWarning() << "Could not create client";
    return;
  }

  m_client->connectToEndpoint(QUrl(url));
}

void MachineAUAClient::disconnectFromEndPoint()
{
  if (m_connected)
  {
    m_client->disconnectFromEndpoint();
  }
}

void MachineAUAClient::toggleBValue()
{
  m_myDeviceNode->callMethod("ns=0;i=20008", {});
}

void MachineAUAClient::toggleCValue()
{
  m_myDeviceNode->callMethod("ns=0;i=20009");
}

void MachineAUAClient::toggleDValue()
{
  m_myDeviceNode->callMethod("ns=0;i=20010");
}

void MachineAUAClient::handleClientState(const QOpcUaClient::ClientState state)
{
  m_connected = (state == QOpcUaClient::ClientState::Connected);
  emit connectionStatusChanged(m_connected);

  if (state == QOpcUaClient::ClientState::Connected)
  {
    qDebug() << "Connected";
    emit connectionStatusMessage(QStringLiteral("Connected"));
    createNodeObjects();
    connectNodeObjectsSignals();
    subscribeToDataChanges();
  }

  if (state == QOpcUaClient::ClientState::Connecting)
  {
    qDebug() << "Connecting";
    emit connectionStatusMessage(QStringLiteral("Connecting"));
  }

  if (state == QOpcUaClient::ClientState::Disconnected)
  {
    qDebug() << "Disconnected";
    emit connectionStatusMessage(QString("Disconnected: %1").arg(QMetaEnum::fromType<QOpcUaClient::ClientError>().valueToKey(static_cast<int>(m_client->error()))));
  }

}

void MachineAUAClient::handle_VariableA_Update(const QOpcUa::NodeAttribute attr, const QVariant& value)
{
  Q_UNUSED(attr);
  qint32 val = value.toInt();
  if (m_varA_Value != val)
  {
    m_varA_Value = val;
    qDebug() << "Variable A updated " << m_varA_Value ;
    emit variableAChanged(m_varA_Value);
  }
}

void MachineAUAClient::handle_VariableB_Update(const QOpcUa::NodeAttribute attr, const QVariant& value)
{
  Q_UNUSED(attr);
  bool val = value.toBool();
  if (m_varB_Value != val)
  {
    m_varB_Value = val;
    emit variableBChanged(m_varB_Value);
  }
}

void MachineAUAClient::handle_VariableC_Update(const QOpcUa::NodeAttribute attr, const QVariant& value)
{
  Q_UNUSED(attr);
  bool val = value.toBool();
  if (m_varC_Value != val)
  {
    m_varC_Value = val;
    emit variableCChanged(m_varC_Value);
  }
}

void MachineAUAClient::handle_VariableD_Update(const QOpcUa::NodeAttribute attr, const QVariant& value)
{
  Q_UNUSED(attr);
  bool val = value.toBool();
  if (m_varD_Value != val)
  {
    m_varD_Value = val;
    emit variableDChanged(m_varD_Value);
  }
}

void MachineAUAClient::handle_VariableE_Update(const QOpcUa::NodeAttribute attr, const QVariant& value)
{
  Q_UNUSED(attr);
  qint32 val = value.toInt();
  if (m_varE_Value != val)
  {
    m_varE_Value = val;
    emit variableEChanged(m_varE_Value);
  }
}

void MachineAUAClient::createNodeObjects()
{
  m_myDeviceNode.reset(m_client->node("ns=0;i=20001"));
  m_variableANode.reset(m_client->node("ns=0;i=20003"));
  m_variableBNode.reset(m_client->node("ns=0;i=20004"));
  m_variableCNode.reset(m_client->node("ns=0;i=20005"));
  m_variableDNode.reset(m_client->node("ns=0;i=20006"));
  m_variableENode.reset(m_client->node("ns=0;i=20007"));
}

void MachineAUAClient::connectNodeObjectsSignals()
{
  connect(m_variableANode.data(), &QOpcUaNode::attributeUpdated, this, &MachineAUAClient::handle_VariableA_Update);
  connect(m_variableBNode.data(), &QOpcUaNode::attributeUpdated, this, &MachineAUAClient::handle_VariableB_Update);
  connect(m_variableCNode.data(), &QOpcUaNode::attributeUpdated, this, &MachineAUAClient::handle_VariableC_Update);
  connect(m_variableDNode.data(), &QOpcUaNode::attributeUpdated, this, &MachineAUAClient::handle_VariableD_Update);
  connect(m_variableENode.data(), &QOpcUaNode::attributeUpdated, this, &MachineAUAClient::handle_VariableE_Update);
}

void MachineAUAClient::subscribeToDataChanges()
{
  m_variableANode->enableMonitoring(QOpcUa::NodeAttribute::Value, QOpcUaMonitoringParameters(100));
  m_variableBNode->enableMonitoring(QOpcUa::NodeAttribute::Value, QOpcUaMonitoringParameters(100));
  m_variableCNode->enableMonitoring(QOpcUa::NodeAttribute::Value, QOpcUaMonitoringParameters(100));
  m_variableDNode->enableMonitoring(QOpcUa::NodeAttribute::Value, QOpcUaMonitoringParameters(100));
  m_variableENode->enableMonitoring(QOpcUa::NodeAttribute::Value, QOpcUaMonitoringParameters(100));
}

