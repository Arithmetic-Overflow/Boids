#include <SFML/Graphics.hpp>

#include <iostream>
#include <unistd.h>
#include <stdlib.h>

#include <random>
#include <time.h>
#include <cmath>

#define _USE_MATH_DEFINES

using namespace std;
using namespace sf;

extern unsigned int canvasWidth;
extern unsigned int canvasHeight;

extern int numBoids;        // number of boids in the simulation
extern float boidSize;      // will be used in the future to scale sprite size
extern float ms;            // max movespeed of the boids
extern float maxA;          // max acceleration of the boids