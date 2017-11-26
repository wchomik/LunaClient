#ifndef PROVIDERSETTINGS_H
#define PROVIDERSETTINGS_H

#include <QObject>
#include <QSettings>

namespace luna {
    class Provider;
}

namespace model {
    class ProviderSettings : public QObject{
        Q_OBJECT
    public:
        explicit ProviderSettings(QObject * parent) : QObject(parent) {}
        virtual ~ProviderSettings(){}
        virtual void setProvider(luna::Provider * provider) = 0;
        virtual void setSettings(QSettings * settings){ mSettings = settings; }
    protected:
        QSettings * mSettings;
    };
}

#endif // PROVIDERSETTINGS_H
