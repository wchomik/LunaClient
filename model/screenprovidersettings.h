#ifndef SCREENPROVIDERSETTINGS_H
#define SCREENPROVIDERSETTINGS_H

#include "providersettings.h"

#include "../luna/screenprovider.h"

namespace model {
    class ScreenProviderSettings : public ProviderSettings
    {
        Q_OBJECT
        Q_PROPERTY(qreal top READ top WRITE setTop NOTIFY topChanged)
        Q_PROPERTY(qreal bottom READ bottom WRITE setBottom NOTIFY bottomChanged)
        Q_PROPERTY(qreal left READ left WRITE setLeft NOTIFY leftChanged)
        Q_PROPERTY(qreal right READ right WRITE setRight NOTIFY rightChanged)
        Q_PROPERTY(qreal depth READ depth WRITE setDepth NOTIFY depthChanged)
    public:
        ScreenProviderSettings(QObject * parent = nullptr);
        ~ScreenProviderSettings();
        void setProvider(luna::Provider *provider) override;
        void setSettings(QSettings *settings) override;

        qreal top() const { return mTop; }
        qreal bottom() const { return mBottom; }
        qreal left() const { return mLeft; }
        qreal right() const { return mRight; }
        qreal depth() const { return mDepth; }

        void setTop(const qreal value);
        void setBottom(const qreal value);
        void setLeft(const qreal value);
        void setRight(const qreal value);
        void setDepth(const qreal value);

    signals:
        void topChanged();
        void bottomChanged();
        void leftChanged();
        void rightChanged();
        void depthChanged();
    private:
        void applyBounds();
        void applyDepth();

        qreal mTop;
        qreal mBottom;
        qreal mLeft;
        qreal mRight;
        qreal mDepth;

        luna::ScreenProvider * mProvider;
    };
}

#endif // SCREENPROVIDERSETTINGS_H
