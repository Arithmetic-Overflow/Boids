#ifndef BOID
#define BOID
    #include "Boid.hpp"
#endif


int numBoids = 50;//00;
float ms = 2.0f;
float maxA = 0.1f;

unsigned int canvasWidth;
unsigned int canvasHeight;


Boid::Boid() {
    float angle = (float(rand())/float((RAND_MAX)) * 2.0f * M_PI);

    float vx = ms*cos(angle);
    float vy = ms*sin(angle);

    int xRange = (int) floor(canvasWidth  - 2 * boidSize);
    int yRange = (int) floor(canvasHeight - 2 * boidSize);

    float xPos = (float) ((rand()%xRange));
    float yPos = (float) ((rand()%yRange));

    this->v = Vector2f(vx, vy);
    this->p = Vector2f(xPos, yPos);
}


void Boid::move() {
    this->p += this->v;

    if(this->p.x < 0) {
        this->p.x += canvasWidth;
    }

    if(this->p.y < 0) {
        this->p.y += canvasHeight;
    }

    this->p.x = fmod(this->p.x, canvasWidth);
    this->p.y = fmod(this->p.y, canvasHeight);

    return;
}


Vector2f Boid::separation(Boid boidArray[], int selfIndex) {
    Vector2f separationVec(0.0f ,0.0f);

    for(int i = 0; i < numBoids; i++) {
        Boid thisBoid = boidArray[i];
        
        if(i != selfIndex && isInVision(thisBoid)) {
            separationVec += (this->p - thisBoid.p) / (dist(this->p, thisBoid.p));
        }
    }

    separationVec *= sepWeight;

    return separationVec;
}


Vector2f Boid::allignment(Vector2f avVel) {
    Vector2f targetVel = avVel - this->v;
     targetVel *= aliWeight;
     return targetVel;
}


Vector2f Boid::cmcohesion(Vector2f avPos) {
    Vector2f targetVel = avPos - this->p;
    targetVel *= cohWeight;
    targetVel -= this->v;

    return targetVel;
}


Vector2f Boid::calculatev(Boid boidArray[], int selfIndex) {
    Vector2f newA(0.0f, 0.0f);

    Vector2f averagePos(0.0f, 0.0f);
    Vector2f averageVel(0.0f, 0.0f);

    int boidsInView = 0;

    for(int i = 0; i < numBoids; i++) {
        Boid thisBoid = boidArray[i];

        if(i != selfIndex && isInVision(thisBoid)) {
            averagePos += thisBoid.p;
            averageVel += thisBoid.v;

            boidsInView++;
        }
    }

    if(boidsInView > 0) {
        averagePos /= (float) boidsInView;
        averageVel /= (float) boidsInView;

        newA += separation(boidArray, selfIndex);
        newA += cmcohesion(averagePos);
        newA += allignment(averageVel);
    }

    newA = normalize(newA, min(maxA, magnitude(newA)));

    Vector2f newV = normalize(this->v + newA, ms);

    return newV;
}


float Boid::angleBetween(Boid target) {
    Vector2f deltaP = target.p - this->p;
    float a = angle(this->v, deltaP);

    // cout << a << endl;

    return a;
}

bool Boid::isInVision(Boid target) {
    bool inVision = dist(this->p, target.p) < visionRad;
    inVision &= this->angleBetween(target) < visionAngle;

    return inVision;
}


float Boid::rotation() {
    float radians = atan2(this->v.y, this->v.x);
    return 180.0f * radians / M_PI;
}