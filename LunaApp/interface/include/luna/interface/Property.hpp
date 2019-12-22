#pragma once

#include <QSettings>

namespace luna::interface {
    template <typename T>
    struct Property {
        explicit Property(QSettings * settings, QString name, T defaultValue) :
            mSettings(settings),
            mName(std::move(name)),
            mValue(defaultValue)
        {
            auto const variant = mSettings->value(mName);
            if (!variant.isNull() && variant.canConvert<T>()) {
                mValue = variant.value<T>();
            }
        }

        operator T() const noexcept
        {
            return mValue;
        }

        T get() const noexcept
        {
            return *this;
        }

        void operator=(T value)
        {
            mValue = value;
            mSettings->setValue(mName, QVariant::fromValue(value));
        }

        void set(T value)
        {
            *this = value;
        }
    private:
        QSettings * mSettings;
        QString const mName;
        T mValue;
    };
}
