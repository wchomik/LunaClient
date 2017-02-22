#include "lunaproviderfactory.h"

#include "lunailluminationprovider.h"
#include "lunaaudioprovider.h"
#include "lunascreenprovider.h"

namespace luna {
    template<typename T>
    std::unique_ptr<LunaProvider> createProvider(QObject * parent){
        return std::make_unique<T>(parent);
    }

    template<>
    std::unique_ptr<LunaProvider> createProvider<LunaProvider>(QObject * parent){
        return std::unique_ptr<LunaProvider>();
    }


    LunaProviderFactory::LunaProviderFactory()
    {
        mCreators[LunaProviderType::none] = createProvider<LunaProvider>;
        mCreators[LunaProviderType::illumination] = createProvider<LunaIlluminationProvider>;
        mCreators[LunaProviderType::audio] = createProvider<LunaAudioProvider>;
        mCreators[LunaProviderType::screen] = createProvider<LunaScreenProvider>;
    }

    std::unique_ptr<LunaProvider> LunaProviderFactory::make(LunaProviderType type, QObject *parent)
    {
        return mCreators[type](parent);
    }

}
