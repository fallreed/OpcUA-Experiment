#ifndef UIMODEL_H
#define UIMODEL_H

#include <QObject>

class UIModel : public QObject
{
  Q_OBJECT
public:
  explicit UIModel(QObject *parent = nullptr) : QObject(parent) {}

  Q_PROPERTY(bool connected READ isConnected NOTIFY connectionStatusChanged)
  Q_PROPERTY(QString statusBarMessage READ statusBarMessage NOTIFY statusBarMessageChanged)
  Q_PROPERTY(qint32 circleGaugeValue READ valueA NOTIFY valueAChanged)
  Q_PROPERTY(bool indicatorBValue READ indicatorBValue NOTIFY indicatorBValueChanged)
  Q_PROPERTY(bool indicatorCValue READ indicatorCValue NOTIFY indicatorCValueChanged)
  Q_PROPERTY(bool indicatorDValue READ indicatorDValue NOTIFY indicatorDValueChanged)
  Q_PROPERTY(qint32 numValue READ valueE NOTIFY valueEChanged)

  virtual bool isConnected() const = 0;
  virtual QString statusBarMessage() const = 0;
  virtual qint32 valueA() const = 0;
  virtual bool indicatorBValue() const = 0;
  virtual bool indicatorCValue() const = 0;
  virtual bool indicatorDValue() const = 0;
  virtual qint32 valueE() const = 0;

signals:
  void connectionStatusChanged(const bool connected);
  void statusBarMessageChanged(const QString& msg);
  void valueAChanged(const qint32 value);
  void indicatorBValueChanged(const bool value);
  void indicatorCValueChanged(const bool value);
  void indicatorDValueChanged(const bool value);
  void valueEChanged(const qint32 value);

public slots:
  virtual void handleButtonConnect_Clicked(const QString& opcurl) = 0;
  virtual void handleButtonB_Clicked() = 0;
  virtual void handleButtonC_Clicked() = 0;
  virtual void handleButtonD_Clicked() = 0;
  virtual void handleClientConnectionStatus(const bool state) = 0;
  virtual void handleClientConnectionStatusMsg(const QString& str) = 0;
  virtual void handleClientAValueChanged(const qint32 val) = 0;
  virtual void handleClientBValueChanged(const bool val) = 0;
  virtual void handleClientCValueChanged(const bool val) = 0;
  virtual void handleClientDValueChanged(const bool val) = 0;
  virtual void handleClientEValueChanged(const qint32 val) = 0;

protected:
  bool m_clientConnected {false};
  bool m_indicatorBValue {false};
  bool m_indicatorCValue {false};
  bool m_indicatorDValue {false};
  qint32 m_cirGaugeValue {0};
  qint32 m_numValue {0};
  QString m_statusBarMsg {"Ready to connect"};

};

#endif // UIMODEL_H
