# Overview
</br>

## 1.Builder
- An abstract class that provides a blueprint for a general builder could be called an "Abstract Builder" class
```cpp
/*
*Builder.h
*/
Component* _result = nullptr;
virtual void build() = 0;
void setAtrributes(string type, string color);
```
## 2. TankBuilder
- Implements Builder interface. 
- This is the base class for PlayerTank and AiTank, which also has a virtual function `virtual void setBehavior() = 0;`

## 3. Director
- Receives a builder, gives him some instructions and provides the client with the result.

## 4. Usage example: 
```cpp
/*
*Engine.cpp
*/
Director::setBuilder(new PlayerTank);
Director::setBuilderAttributes(playerType, playerTeam);
_components.push_back(Director::getResult());
```


## Note
Please <a href="https://en.wikipedia.org/wiki/Builder_pattern#/media/File:Builder_UML_class_diagram.svg" target="_blank">visit</a>  to see how Builder Pattern Works
