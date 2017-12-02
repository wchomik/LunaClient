#include "screentab.h"

#include "screenprovider.h"

ScreenTab::ScreenTab() :
    mModel(std::make_unique<ScreenModel>())
{
}

void ScreenTab::activate(luna::Manager * manager) {
    auto ret = std::make_shared<ScreenProvider>();
    mModel->provider(ret);
    manager->setProvider(ret);
}

void ScreenTab::deactivate(luna::Manager * manager) {

}

QString ScreenTab::displayName() const {
    return "Screen";
}

QObject * ScreenTab::model() {
    return mModel.get();
}

int ScreenTab::displayOrder() const {
    return 50;
}

QUrl ScreenTab::itemUrl() const {
    return QUrl("qrc:/ScreenPlugin.qml");
}
