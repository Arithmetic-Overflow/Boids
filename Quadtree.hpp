#ifndef BOID
#define BOID
    #include "Boid.hpp"
#endif

extern int maxMembersPerQuadrant;

class Quadtree {
    public:
        Vector2i p;             // position of top-left corner of quad tree
        Vector2i dim;           // (width, height) of the quadrant

        Quadtree *children[4] = {NULL, NULL, NULL, NULL};
        // Boid *members = (Boid *) malloc(sizeof(Boid)*maxMembersPerQuadrant);

        vector<Boid> members;

        Quadtree(Boid[]);
        Quadtree(Vector2i, Vector2i, vector<Boid>);

        bool containsPoint(Vector2f);
        bool containsPoint(Vector2i);
        bool containsBoid(Boid);

        void limitMembers();
        void createChildren();

        vector<Boid> closeBoidsInNode(Vector2i[]);
        bool intersectsRect(Vector2i[]);

        vector<Boid> searchBoids(Boid);
        vector<Boid> nearbyBoids(Boid);

        vector<RectangleShape> getRect(void);
};

extern void drawQuad(Quadtree);