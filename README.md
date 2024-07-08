## Storm rotation

## Introduction
a program designed to rotate a rainfall event (storm) by a certain angle. 

## Algorithm

### Rotation
Given a line segment in a Cartesian coordinate system, with the two ends $A$ ($x_1$, $y_1$), and $B$ ($x_2$, $y_2$), rotate the line segment $\alpha$ degrees with $A$ as the center, the coordinate of the new end $B^r$ ($x_2^r$, $y_2^r$) is calculated as:

$$
x_2^r = x_1 + (x_2 - x_1) \cos{\alpha} + (y_2-y_1) \sin{\alpha}
$$


$$
y_2^r = y_1 - (x_2-x_1) \sin{\alpha} + (y_2 - y_1) \cos{\alpha}
$$


### Storm rotation


