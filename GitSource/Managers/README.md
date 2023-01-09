Description : 
---------
**Almost all classes implement the Component interface.**

1. **AnimationHandler**
> - It has a static method that allows it to take over an animation at any moment of the game.
> - It can be stored in **Engine** componets.

2. **AssetsStorage**
> - Load from xml files using the tinyXML library assets such as:
> > - tanks
> > - map & minimap tiles
> > - effects
> > - abilities

3. **CameraManager**
>**Implement 2 modes:**
> - spectator mode : offers the opportunity to observe the gameplay .
> - focus mode : offers the possibility to track any object on the map .

4. **ColisionManager**
>**It offers a series of collisions such as:**
>```cpp
> - static void mapCollision(...);
> - static bool circleRectagleCollision(...);
> - static bool pointMapCollision(...);
> - static bool pointRectagleCollision(...);
>```

5. **InfoManager**
> - It has a static method that allows it to take over a text at any moment of the game.
> - It can be stored in **Engine** componets.

6.**InputManager**
> - Handle the input . 

8.**Mediator**
> - Manages the interaction between objects.
> - Group objects according to certain characteristics.
> - It stores certain information related to objects.
> - It recognizes objects by an id.

> **Usage example** : 
> ```cpp
>/*
>* Tank.cpp
>*/
>Mediator::notifyTeam(_id, _teamColor);
>Mediator::registerTank(_position, _id, Health);
>
>/*
>* Behavior.cpp
>*/
>for (auto& i : Mediator::recieveTanksPositions(_id))
>{
>	CollisionManager::circleRectagleCollision(potentialPos, i, rectDim);
>}
>```



	

	
