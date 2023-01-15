# Overview

</br>

## 1.TextButton 
- This class is inherited from `TextComponent`. 
- It has specific properties such as `hovered` , `pressed` and `order`.
- Class intantiation example: 
```cpp
/*
* ButtonText.H
*/
TextButton(string name, SDL_Color, int size, int pos, bool hover = false,  int active = true); 
/*
*example
*/
text = new TextButton("CONTINUE" , WHITE , 64 , 7 , false , false) ;
```

## 2.MenuScene
- Implements the `Component` interface.
- It has a vector of Button classes and it has a variable that keeps track of the last button pressed.
- Also it has a name.
- Class intantiation example : 
```cpp
/*
* Menu.cpp
*/
/*
* scena main
*/
_scenes.push_back(new MenuScene("Main",
{
new TextButton("2D TANK" , WHITE , 92 , 1) , 
new TextButton("SIMULATOR" , WHITE , 92 , 2) ,
new TextButton("" , WHITE , 64 , 6 , false , false) , // folosit pe poste de delimitare dintre butoane si titlu
new TextButton("CONTINUE" , WHITE , 64 , 7 , false , false) , //initial dezactivat
new TextButton("NEW GAME" , WHITE , 64 , 8 , true) ,
new TextButton("QUIT GAME" , WHITE , 64 , 9) }));
```

## 3.Menu
- Implemets the `Component` interface .
- This class is responsible for loading scenes, particularly with regard to behavioral aspects.
