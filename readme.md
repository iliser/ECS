ECS
===

A simple ECS base implementation

Usage:
```c++
//define component type
DataComponent(Velocity,glm::vec3);
DataComponent(Position,glm::vec3);

//create state
GameState gs;

//create entity
Entity e = gs.createEntity(Position,Velocity);

//set component data
e[Position].data = glm::vec3{12,3,0};
e[Velocity].data = glm::vec3{-1,2,0};


//Define system
void MoveSystem(GameState & gs)
{
    for(auto &[k,v]:gs[Velocity])
    {
        auto & p = gs[Position][k];
        p.data += v.data;
    }
}

//call system
MoveSystem(gs);
```