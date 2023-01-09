# Builder :
- An abstract class that characterizes the behavior of a tank. 
  - `void move(...);`
  - `void rotationB(...);`
  - `void rotationC(...);`
- It has a struct of moves : 

`struct Moves`</br>
`{`</br>
	`bool _up = false;`</br>
	`bool _down = false;`</br>
	`bool _right = false;`</br>
	`bool _left = false;`</br>
	`bool _shoting = false;`</br>
	`bool _releaseMine = false;`</br>
`};`</br>
- Additionally, it has `virtual void movement(...) = 0;` that serves as a placeholder for how the behavior is enacted.

# PlayerBuhavior 

- It implements `virtual void movement(...) = 0;` through Input. 

# AIBehavior 

- It implements `virtual void movement(...) = 0;` through Ai Algorithm. 
