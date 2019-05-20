#include "UIMachineA.h"
#include "MachineaUaClient.h"

UIMachineA::UIMachineA(MachineA& machine, QObject *parent)
  : UIModel(parent),
    m_machineA(machine)
{
  connectDeviceClientSignals();
}

bool UIMachineA::isConnected() const
{
  return m_machineA.isConnected();
}

QString UIMachineA::statusBarMessage() const
{
  return m_statusBarMsg;
}

qint32 UIMachineA::valueA() const
{
  return m_cirGaugeValue;
}

bool UIMachineA::indicatorBValue() const
{
  return m_indicatorBValue;
}

bool UIMachineA::indicatorCValue() const
{
  return m_indicatorCValue;
}

bool UIMachineA::indicatorDValue() const
{
  return m_indicatorDValue;
}

qint32 UIMachineA::valueE() const
{
  return m_numValue;
}

void UIMachineA::connectDeviceClientSignals()
{
  connect(&m_machineA, &MachineAUAClient::connectionStatusChanged,
          this, &UIMachineA::handleClientConnectionStatus);

  connect(&m_machineA, &MachineAUAClient::connectionStatusMessage,
          this, &UIMachineA::handleClientConnectionStatusMsg);

  connect(&m_machineA, &MachineAUAClient::variableAChanged,
          this, &UIMachineA::handleClientAValueChanged);

  connect(&m_machineA, &MachineAUAClient::variableBChanged,
          this, &UIMachineA::handleClientBValueChanged);

  connect(&m_machineA, &MachineAUAClient::variableCChanged,
          this, &UIMachineA::handleClientCValueChanged);

  connect(&m_machineA, &MachineAUAClient::variableDChanged,
          this, &UIMachineA::handleClientDValueChanged);

  connect(&m_machineA, &MachineAUAClient::variableEChanged,
          this, &UIMachineA::handleClientEValueChanged);
}

void UIMachineA::handleButtonConnect_Clicked(const QString& opcurl)
{
  qDebug() << "Handle button connect";
  if (!m_machineA.isConnected())
  {
    qDebug() << "connect to " << opcurl;
    m_machineA.connectToEndPoint(opcurl);
  }
  else
  {
    qDebug() << "disconnect from " << opcurl;
    m_machineA.disconnectFromEndPoint();
  }
}

void UIMachineA::handleButtonB_Clicked()
{
  if (m_machineA.isConnected())
  {
    m_machineA.toggleBValue();
  }
}

void UIMachineA::handleButtonC_Clicked()
{
  if (m_machineA.isConnected())
  {
    m_machineA.toggleCValue();
  }
}

void UIMachineA::handleButtonD_Clicked()
{
  if (m_machineA.isConnected())
  {
    m_machineA.toggleDValue();
  }
}

void UIMachineA::handleClientConnectionStatus(const bool state)
{
  if (m_clientConnected != state)
  {
    m_clientConnected = state;
    emit connectionStatusChanged(m_clientConnected);
  }
}

void UIMachineA::handleClientConnectionStatusMsg(const QString& str)
{
  if (m_statusBarMsg != str)
  {
    m_statusBarMsg = str;
    emit statusBarMessageChanged(m_statusBarMsg);
  }
}

void UIMachineA::handleClientAValueChanged(const qint32 val)
{
  if (m_cirGaugeValue != val)
  {
    m_cirGaugeValue = val;
    emit valueAChanged(m_cirGaugeValue);
  }
}

void UIMachineA::handleClientBValueChanged(const bool val)
{
  if (m_indicatorBValue != val)
  {
    m_indicatorBValue = val;
    emit indicatorBValueChanged(m_indicatorBValue);
  }
}

void UIMachineA::handleClientCValueChanged(const bool val)
{
  if (m_indicatorCValue != val)
  {
    m_indicatorCValue = val;
    emit indicatorCValueChanged(m_indicatorCValue);
  }
}

void UIMachineA::handleClientDValueChanged(const bool val)
{
  if (m_indicatorDValue != val)
  {
    m_indicatorDValue = val;
    emit indicatorDValueChanged(m_indicatorDValue);
  }
}

void UIMachineA::handleClientEValueChanged(const qint32 val)
{
  if (m_numValue != val)
  {
    m_numValue = val;
    emit valueEChanged(m_numValue);
  }
}

