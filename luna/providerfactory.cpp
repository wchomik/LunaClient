#include "providerfactory.h"

#include "illuminationprovider.h"
#include "audioprovider.h"
#include "screenprovider.h"

namespace luna {
    template<typename T>
    std::unique_ptr<Provider> createProvider(){
        return std::make_unique<T>();
    }

    template<>
    std::unique_ptr<Provider> createProvider<Provider>(){
        return std::unique_ptr<Provider>();
    }


    ProviderFactory::ProviderFactory()
    {
        mCreators[ProviderType::none] = createProvider<Provider>;
        mCreators[ProviderType::illumination] = createProvider<IlluminationProvider>;
        mCreators[ProviderType::audio] = createProvider<AudioProvider>;
        mCreators[ProviderType::screen] = createProvider<ScreenProvider>;
    }

    std::unique_ptr<Provider> ProviderFactory::make(ProviderType type)
    {
        return mCreators[type]();
    }

}
