#pragma once

#include <QObject>

#include <luna/interface/Plugin.hpp>

class LightPlugin : public QObject, public luna::interface::Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.luna.light")
    Q_INTERFACES(luna::interface::Plugin)
public:
    std::string name() const override;
    void initialize(luna::interface::Application * application) override;
    void finalize(luna::interface::Application * application) override;
};
