# Overview 

 </br></br>

> ## 1. Component  
- An abstract class that has a specific ID.
- The ability to enable and disable.
- Pure virtual functions : 
```cpp 
virtual void draw() = 0 ; 
virtual void update() = 0 ;
```

 </br></br>

> ## 2. SpriteComponent
 - Implements the **Component** interface. 
 - Has a series of statuses such as : 
   - **followed** : set the camera focus on him .
   - **drawble** : enable or disable on-screen drawing.
   - **spawneble** : specifies whether an object can be temporarily disabled.
   - **isBordered** : specifies if it has a rectangle drawn around it.
   - **isMapObject** : speciefies if it is part of the map.
 - Gives the option to create a sprite from a given path and also to copy an existing sprite.

- This is how a sprite copy is made: 
```cpp
SpriteComponent::SpriteComponent(SpriteComponent*& sprite)
{
	_src = sprite->_src;

	_dest = new SDL_Rect;
	*_dest = *sprite->_dest;

	_texture = sprite->_texture;
}
```
- When a copy sprite is deleted, this function must be called first (we don't want to delete this sprite permanently):
 ```cpp
void setSrcTextNullPtr() 
{
	_src = nullptr;
	_texture = nullptr;
}
```

 </br></br>

> ## 3. TextComponent  
- Inherits from the SpriteComponent class.
- Adds additional font, color, and size options.

 </br></br>

> ## 4. AbilityComponent  
- Inherits from the SpriteComponent class.
- Has a type specifier.
- Implements the collectible status. 

 </br></br>

> ## 5. AnimationComponent 
 - Implements the **Component** interface. 
 - Based on a specifier makes a copy of an animation from **AssetsStorage** class . 
 - It has a continuity specifier .
