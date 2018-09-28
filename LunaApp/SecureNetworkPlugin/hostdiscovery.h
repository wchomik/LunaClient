#ifndef HOSTDISCOVERY_H
#define HOSTDISCOVERY_H

#include <QObject>
#include <QNetworkInterface>
#include <QTimer>
#include <QUdpSocket>
#include <QHostAddress>

#include <cstdint>
#include <list>

class HostDiscovery : public QObject
{
    Q_OBJECT
public:
    HostDiscovery();
signals:
    void hostDiscovered(QHostAddress hostAddress);
    void hostLost();
private slots:
    void discover();
    void handleResponse();
private:
    struct Host {
        QHostAddress address;
    };

    std::list<Host> mKnownHosts;
    QTimer mDiscoveryTimer;
    QUdpSocket mSocket;
};

#endif // HOSTDISCOVERY_H
