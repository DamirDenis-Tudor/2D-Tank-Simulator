# Description

# 1. Map
- Loaded from AssetsStorage . 

# 2. MapDestructibleObject
- Inherited from SpriteComponent, this class also adds health and a respawn timer.

# 3. Barrel
- Inherited from MapDestructibleObject, this class also adds an explosion animation and damage in its area.

# 4. Tank
- 3 parts : tracks , body , cannon .
- multple TextComponets .
- multimple timers .
- multiple abilities : lauching bullets/mines and to activate special abilities.  

# 5. Bullet 
- Inherited from SpriteComponent .
- It belongs to a tank.

# 6. Mine
- Inherited from AnimationComponent .
- It belongs to a tank.