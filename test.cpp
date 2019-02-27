#include "ecs.hpp"

#include <iostream>

DataComponent(Velocity,glm::vec3);
DataComponent(Position,glm::vec3);

template<class T> class E;
void PositionLogSystem(GameState & gs)
{
    for(auto &[k,p]:gs[Position])std::cout<<p.data.x<<' '<<p.data.y<<'\n';
}

void MoveSystem(GameState & gs)
{
    for(auto &[k,v]:gs[Velocity])
    {
        auto & p = gs[Position][k];
        p.data += v.data;
    }
}


int main()
{
    GameState gs;
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