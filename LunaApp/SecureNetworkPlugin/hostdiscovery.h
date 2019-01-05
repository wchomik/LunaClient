#ifndef HOSTDISCOVERY_H
#define HOSTDISCOVERY_H

#include <QObject>
#include <QTimer>
#include <QUdpSocket>
#include <QHostAddress>

#include <luna/proto/Discovery.hpp>

class HostDiscovery : public QObject
{
    Q_OBJECT
public:
    HostDiscovery();

signals:
    void hostDiscovered(QHostAddress hostAddress, luna::proto::Discovery const * properties);

private slots:
    void discover();
    void handleResponse();

private:
    QTimer mDiscoveryTimer;
    QUdpSocket mSocket;
};

#endif // HOSTDISCOVERY_H
