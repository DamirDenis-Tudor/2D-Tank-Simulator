# Overview

</br>

## 1. Behavior :
- An abstract class that characterizes the behavior of a tank. 
  - `void move(...);`
  - `void rotationB(...);`
  - `void rotationC(...);`
It has a series of possible moves: `up`, `down`, `right`, `left`, `shooting`, `deploy mine`.
- Additionally, it has `virtual void movement(...) = 0;` that serves as a placeholder for how the behavior is enacted.

## 2. PlayerBehavior 

- It implements `virtual void movement(...) = 0;` through Input. 

## 3. AIBehavior 

- It implements `virtual void movement(...) = 0;` through Ai Algorithm. 
