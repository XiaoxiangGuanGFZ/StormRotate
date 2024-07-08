## Storm rotation

## Introduction
a program designed to rotate a rainfall event (storm) by a certain angle. 

![Rotation illustration](/doc/rotate_illustation.jpg)

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

set a rotation center and rotation angle (clockwise) to rotate the rainfall storm. The rotation center can be the geographic center of a domain. 

## How-to-use

the program is designed and coded in C language. Take the following steps to build and implement: navigate to the `scr` folder, create directory `build` and navigate to it. call `cmake` and `make` to build the software. 


```console
$ cd ./StormRotate/scr/
$ mkdir build
$ cd build
$ cmake ..
$ make
```

A configure file `gp.txt` is required to provide parameters controlling the behavior, an example is:

```
# field-value pairs, separated by comma
# only values can be changed
ROTATE_ANGLE,190            # degrees
ROTATE_RADIUS,12000         # rotation radius: same unit as RASTER ASCII data
ROTATE_CENTER_X,603987      # coordinates of the rotation center
ROTATE_CENTER_Y,5792746

FP_data,D:/StormDirection/data/rr_hly/          # directory where rainstorm ASCII raster data is stored
# Raster files in FP_data directory should be ASCII, with extension of .asc
FP_out,D:/StormDirection/data/rotate/Angle_190/ # directory to store the rotated rain storm
```

```console
./StormRotate.exe /path/to/gp.txt
```
or
```console
./StormRotate /path/to/gp.txt
```

depending your OS.


## Contact

[Xiaoxiang Guan](https://www.gfz-potsdam.de/staff/guan.xiaoxiang/sec44)
