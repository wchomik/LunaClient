#include "securenetworkplugin.h"

#include <lunaplugin/luna.h>

#include "securenetworkconnectorplugin.h"


QString SecureNetworkPlugin::name() const
{
    return QString("Secure Network");
}

void SecureNetworkPlugin::initialize(luna::Luna *luna)
{
    luna->addConnector(std::make_unique<SecureNetworkConnectorPlugin>());
}

void SecureNetworkPlugin::finalize(luna::Luna *luna)
{

}
