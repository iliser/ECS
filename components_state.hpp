#pragma once

#include <typeindex>
#include <memory>
#include <cassert>

#include "component_container.hpp"

struct Entity;
template<class T> struct ComTag{};

#define DataComponent(ComName,DataType) struct ComName##Component{DataType data;};\
ComTag<ComName##Component> ComName;

class ComponentsState
{
    using cc_ptr = std::unique_ptr<IComponentContainer>;
    std::unordered_map<std::type_index,cc_ptr> data;
    size_t id = 0;
public:
    template<class Com> ComponentContainer<Com> & get()
    {
        auto &f = data[typeid(Com)];
        if(f)
        {
            auto ptr = f.get();
            auto c_ptr = dynamic_cast<ComponentContainer<Com>*>(ptr);
            assert(c_ptr != nullptr 
                && "ComponentsState -> ComponentContainerPtr contain not valid pointer");
            return *c_ptr;
        }
        f = std::make_unique<ComponentContainer<Com>>();
        return get<Com>();
    }

    template<class Com> auto & operator [](ComTag<Com>)
    {
        return get<Com>();
    }

    template<class ...Args> Entity createEntity(ComTag<Args> ...);
};