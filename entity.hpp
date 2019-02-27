#pragma once

#include "components_state.hpp"

struct ComponentAccessException{};

class Entity
{
    size_t oid;
    ComponentsState * gs;

    Entity(size_t oid,ComponentsState *gs):oid(oid),gs(gs){}
    friend ComponentsState;
public:
    template<class Com> Com & get()
    {
        auto ptr = gs->get<Com>().get(oid);
        if(ptr==nullptr)throw ComponentAccessException();
        //assert(ptr!=nullptr && "Entity does't have this component");
        return *ptr;
    }

    template<class Com> Com & operator[](ComTag<Com>)
    {
        return get<Com>();
    }
};

template<class ...Args> Entity ComponentsState::createEntity(ComTag<Args> ...ct)
{
    Entity e{++id,this};
    (get<Args>().add(id),...);
    return e;
}