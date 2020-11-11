#ifndef BOID
#define BOID
    #include "Boid.hpp"
#endif

extern int maxBoidsPerQuadrant;

class Quadtree {
    public:
        Vector2i p;             // position of top-left corner of quad tree
        Vector2i dim;           // (width, height) of the quadrant

        Quadtree *children[4];
        // Boid *members = (Boid *) malloc(sizeof(Boid)*maxBoidsPerQuadrant);

        vector<Boid> members;

        Quadtree(Boid[]);
        Quadtree(Vector2i, Vector2i, vector<Boid>);

        bool containsBoid(Boid);
        void addMembers();
        void createChildren();

        vector<Boid> searchBoids(Boid);
};