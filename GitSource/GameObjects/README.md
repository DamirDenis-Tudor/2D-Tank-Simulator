# Overview

 </br></br>

> # 1. Map
- Loaded from AssetsStorage . 

 </br></br>

> # 2. MapDestructibleObject
- Inherited from SpriteComponent, this class also adds health and a respawn timer.

 </br></br>

> # 3. Barrel
- Inherited from MapDestructibleObject, this class also adds an explosion animation and damage in its area.

 </br></br>

> # 4. Tank
- 3 parts : tracks , body , cannon .
- multple TextComponets .
- multimple timers .
- multiple abilities : lauching bullets/mines and to activate special abilities.  

 </br></br>

> # 5. Bullet 
- Inherited from SpriteComponent .
- It belongs to a tank.

 </br></br>

> # 6. Mine
- Inherited from AnimationComponent .
- It belongs to a tank.
