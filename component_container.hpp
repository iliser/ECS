#pragma once

#include <unordered_map>

class IComponentContainer
{
public:
    virtual ~IComponentContainer(){}
};

//using Velocity = Component<VelocityData>;
template<class Com> class ComponentContainer:public IComponentContainer
{
    std::unordered_map<size_t,Com> data;
public:
    Com & add(size_t key)
    {
        return data[key];
    }
    void del(size_t key)
    {
        data.erase(key);
    }
    Com * get(size_t key)
    {
        if(auto it = data.find(key);it!=data.end())return &it->second;
        return nullptr;
    }
    Com & operator[](size_t key)
    {
        auto * ptr = get(key);
        if(ptr)return *ptr;
        return add(key);
    }

    auto begin()
    {
        return data.begin();
    }
    auto end()
    {
        return data.end();
    }

    virtual ~ComponentContainer(){}
};