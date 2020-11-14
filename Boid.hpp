#ifndef BOIDSIM
#define BOIDSIM
    #include "boidsim.hpp"
#endif

#ifndef MATH
#define MATH
    #include "math.hpp"
#endif


class Boid {
    public:
        Vector2f p;
        Vector2f v;
        Vector2f a;

        // weights indicating how much effect each behaviour contributes to overall behaviour
        static constexpr float sepWeight = 10.0f;
        static constexpr float aliWeight = 6.0f;
        static constexpr float cohWeight = 3.0f;

        static constexpr float visionRad = 120.0f;
        static constexpr float visionAngle = 3.0f;

        Boid();

        void move();
        Vector2f separation(vector<Boid>);
        Vector2f allignment(Vector2f);
        Vector2f cmcohesion(Vector2f);

        Vector2f calculatev(vector<Boid>);

        float angleBetween(Boid);
        bool isInVision(Boid);

        float rotation();
};

extern void updateBoidVelocities(Boid boidArray[]);
extern void moveBoids(Boid boidArray[]);