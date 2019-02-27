#pragma once

#include "game_state.hpp"

struct ComponentAccessException{};

class Entity
{
    size_t oid;
    GameState * gs;

    Entity(size_t oid,GameState *gs):oid(oid),gs(gs){}
    friend GameState;
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

template<class ...Args> Entity GameState::createEntity(ComTag<Args> ...ct)
{
    Entity e{++id,this};
    (get<Args>().add(id),...);
    return e;
}