# Builder
- An abstract class that provides a blueprint for a general builder could be called an "Abstract Builder" class
```cpp
/*
*Builder.h
*/
Component* _result = nullptr;
virtual void build() = 0;
void setAtrributes(string type, string color);
```
# TankBuilder
- Implements Builder interface. 
- This is the base class for PlayerTank and AiTank, which also has a virtual function `virtual void setBehavior() = 0;`

# Director
- Receives a builder, gives him some instructions and provides the client with the result.



# Usage example: 
```cpp
/*
*Engine.cpp
*/
Director::setBuilder(new PlayerTank);
Director::setBuilderAttributes(playerType, playerTeam);
_components.push_back(Director::getResult());
```


# Note
Please <a href="https://www.google.com/](https://refactoring.guru/design-patterns/builder/cpp/example#:~:text=Builder%20in%20C%2B%2B,using%20the%20same%20construction%20process" target="_blank">visit</a>  to see how Builder Pattern Works
