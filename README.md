# Modelling and Simulating the Solar system in C with SDL2
![Interface](/view.png)

This is a 2D simulation of the Solar System, including the Sun and the 8 planets. You can choose at compile time between a scale to fit the screen and a "real" scale : 
```
make # Screen size
make ONSCALE=1 # True scale
```
At run time you can choose the kinematics version or the dynamics one : 
```
./solarsystem # Kinematics
./solarsystem dynamics # Dynamics
```
You can pause by holding the space bar and quit by hitting Escape. It will begin with the current real position and indicate the date at the top left.

The acceleration_factor is around 3,942,000 (1 year in 10 s).

Next steps :
+ In dynamics mode --> integrate with Runge-Kutta 4
+ Improve Compatibility
