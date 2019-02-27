#include "ecs.hpp"

#include <iostream>
#include <glm/vec3.hpp>
DataComponent(Velocity,glm::vec3);
DataComponent(Position,glm::vec3);

template<class T> class E;
void PositionLogSystem(ComponentsState & gs)
{
    for(auto &[k,p]:gs[Position])std::cout<<p.data.x<<' '<<p.data.y<<'\n';
}

void MoveSystem(ComponentsState & gs)
{
    for(auto &[k,v]:gs[Velocity])
    {
        auto & p = gs[Position][k];
        p.data += v.data;
    }
}


int main()
{
    ComponentsState gs;
    auto e = gs.createEntity(Position,Velocity);
    e[Position].data = glm::vec3{12,3,0};
    e[Velocity].data = glm::vec3{-1,2,0};

    PositionLogSystem(gs);
    MoveSystem(gs);

    PositionLogSystem(gs);
    MoveSystem(gs);

    PositionLogSystem(gs);
    MoveSystem(gs);

    auto e2 = gs.createEntity(Position);
    e2[Velocity];
    return 0;
}