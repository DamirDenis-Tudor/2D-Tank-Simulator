 # Overview
 </br></br>

> ## Behavior :
- An abstract class that characterizes the behavior of a tank. 
  - `void move(...);`
  - `void rotationB(...);`
  - `void rotationC(...);`
- It has a struct of moves : `up , down , right , left , shooting , release mine`
- Additionally, it has `virtual void movement(...) = 0;` that serves as a placeholder for how the behavior is enacted.
 
 </br></br>

> ## PlayerBehavior 

- It implements `virtual void movement(...) = 0;` through Input. 

 </br></br>

> ## AIBehavior 

- It implements `virtual void movement(...) = 0;` through Ai Algorithm. 
