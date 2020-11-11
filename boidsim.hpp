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

class Boid {
    public:
        Vector2f p;
        Vector2f v;
        Vector2f a;

        // weights indicating how much effect each behaviour contributes to overall behaviour
        static constexpr float sepWeight = 1.2f;
        static constexpr float aliWeight = 0.4f;
        static constexpr float cohWeight = 0.12f;

        static constexpr float visionRad = 150.0f;
        static constexpr float visionAngle = 2.8f;

        Boid();

        void move();
        Vector2f separation(Boid[], int);
        Vector2f allignment(Vector2f);
        Vector2f cmcohesion(Vector2f);

        Vector2f calculatev(Boid[], int);

        float angleBetween(Boid);
        bool isInVision(Boid);

        float rotation();
};

extern void updateBoidVelocities(Boid boidArray[]);
extern void moveBoids(Boid boidArray[]);


// vector calculations
extern float dist(Vector2f v1, Vector2f v2);
extern float magnitude(Vector2f v);
extern Vector2f normalize(Vector2f v, float unit);

extern float dot(Vector2f v1, Vector2f v2);
extern float angle(Vector2f v1, Vector2f v2);

// utility functions
extern float min(float a, float b);
extern float max(float a, float b);