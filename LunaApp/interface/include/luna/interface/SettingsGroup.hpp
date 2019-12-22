#pragma once

#include <QSettings>

namespace luna::interface
{
    struct SettingsGroup
    {
        explicit SettingsGroup(QSettings* settings, QString name) :
            mSettings(settings)
        {
            mSettings->beginGroup(name);
        }

        ~SettingsGroup()
        {
            mSettings->endGroup();
        }
    private:
        QSettings* mSettings;
    };
}
