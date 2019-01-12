#include "SecureNetworkPlugin.hpp"

#include <luna/interface/Application.hpp>

#include "SecureNetworkConnectorPlugin.hpp"

void SecureNetworkPlugin::initialize(luna::interface::Application * application)
{
    application->addConnector(std::make_unique<SecureNetworkConnectorPlugin>());
}

void SecureNetworkPlugin::finalize(luna::interface::Application * application)
{
}

std::string SecureNetworkPlugin::name() const
{
    return "Secure Network";
}
