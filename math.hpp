#ifndef BOIDSIM
#define BOIDSIM
    #include "boidsim.hpp"
#endif


// vector calculations
extern float dist(Vector2f v1, Vector2f v2);
extern float magnitude(Vector2f v);
extern Vector2f normalize(Vector2f v, float unit);

extern float dot(Vector2f v1, Vector2f v2);
extern float angle(Vector2f v1, Vector2f v2);

// utility functions
extern float min(float a, float b);
extern float max(float a, float b);