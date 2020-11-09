#include <SFML/Graphics.hpp>
#include <iostream>
#include <unistd.h>

#include <random>
#include <time.h>
#include <cmath>

#define _USE_MATH_DEFINES

using namespace std;
using namespace sf;

extern unsigned int canvasWidth;
extern unsigned int canvasHeight;

extern int numBoids;
extern float boidSize;
extern float ms;
extern float maxA;
extern float ts;

class Boid {
    public:
        Vector2f p;
        Vector2f v;
        Vector2f a;

        static constexpr float sepWeight = 0.8f;
        static constexpr float aliWeight = 0.3f;
        static constexpr float cohWeight = 0.15f;

        static constexpr float visionRad = 80.0f;

        Boid();

        void move();
        Vector2f separation(Boid[], int);
        Vector2f allignment(Vector2f);
        Vector2f cmcohesion(Vector2f);

        Vector2f calculatev(Boid[], int);

        float rotation();
};

extern void updateBoidVelocities(Boid boidArray[]);
extern void moveBoids(Boid boidArray[]);

extern float dist(Vector2f v1, Vector2f v2);
extern float magnitude(Vector2f v);
extern Vector2f normalize(Vector2f v, float unit);

extern float dot(Vector2f v1, Vector2f v2);
extern float angle(Vector2f v1, Vector2f v2);

extern float min(float a, float b);
extern float max(float a, float b);