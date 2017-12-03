#include "legacyudpplugin.h"

#include <luna.h>

#include "connectorudplegacy.h"

void LegacyUdpPlugin::initialize(luna::Luna * luna) {
    luna->addManager(std::make_shared<ConnectorUdpLegacy>());
}

void LegacyUdpPlugin::finalize(luna::Luna * luna) {

}
