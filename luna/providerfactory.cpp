#include "providerfactory.h"

#include "illuminationprovider.h"
#include "audioprovider.h"
#include "screenprovider.h"

namespace luna {
    template<typename T>
    std::unique_ptr<Provider> createProvider(QObject * parent){
        return std::make_unique<T>(parent);
    }

    template<>
    std::unique_ptr<Provider> createProvider<Provider>(QObject * parent){
        return std::unique_ptr<Provider>();
    }


    ProviderFactory::ProviderFactory()
    {
        mCreators[ProviderType::none] = createProvider<Provider>;
        mCreators[ProviderType::illumination] = createProvider<IlluminationProvider>;
        mCreators[ProviderType::audio] = createProvider<AudioProvider>;
        mCreators[ProviderType::screen] = createProvider<ScreenProvider>;
    }

    std::unique_ptr<Provider> ProviderFactory::make(ProviderType type, QObject *parent)
    {
        return mCreators[type](parent);
    }

}
