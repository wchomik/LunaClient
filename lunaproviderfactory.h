#ifndef LUNAPROVIDERFACTORY_H
#define LUNAPROVIDERFACTORY_H

#include <memory>

#include "lunaprovider.h"

namespace luna {
    enum class LunaProviderType {
        none,
        illumination,
        audio,
        screen,
        //fire,
        //plasma,
        COUNT,
    };

    class LunaProviderFactory
    {
    public:
        LunaProviderFactory();

        std::unique_ptr<LunaProvider> make(LunaProviderType type, class QObject * parent);
    private:
        typedef std::unique_ptr<LunaProvider>(* creator_t)(class QObject *);
        template<typename ElemT, typename IndexT, IndexT count>
        class EnumArray {
        public:
            ElemT & operator[](IndexT index){
                return mData[static_cast<size_t>(index)];
            }

        private:
            ElemT mData[static_cast<size_t>(count)];
        };

        EnumArray<creator_t, LunaProviderType, LunaProviderType::COUNT> mCreators;
    };
}

#endif // LUNAPROVIDERFACTORY_H
