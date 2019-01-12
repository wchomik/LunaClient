#pragma once

#include <luna/interface/Plugin.hpp>

#include <QObject>

class ScreenPlugin : public QObject, public luna::interface::Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.luna.screen")
    Q_INTERFACES(luna::interface::Plugin)
public:
    std::string name() const override;
    void initialize(luna::interface::Application * application) override;
    void finalize(luna::interface::Application * application) override;
};
