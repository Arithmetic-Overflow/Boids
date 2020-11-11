#ifndef QUADTREE
#define QUADTREE
    #include "Quadtree.hpp"
#endif


int maxBoidsPerQuadrant = 1;

Quadtree::Quadtree(Boid boidArray[]) {
    this->p = Vector2i(0, 0);
    this->dim = Vector2i(canvasWidth, canvasHeight);

    members = vector<Boid>(numBoids);

    for(int i = 0; i < numBoids; i++) {
        members[i] = boidArray[i];
    }
}


Quadtree::Quadtree(Vector2i p, Vector2i dim, vector<Boid> boidsInParent) {
    this-> p = p;
    this->dim = dim;
    this->members = boidsInParent;
}


// inclusive for lower bounds, exclusive for upper bounds
bool Quadtree::containsBoid(Boid boid) {
    int bx = (int) boid.p.x;
    int by = (int) boid.p.y;

    // these calculations being done multiple times is a reundancy
    // in the future I will factor them out
    bool isContained =
        bx >= this->p.x                 &&
        bx < this->p.x + this->dim.x    &&
        by >= this->p.y                 &&
        by < this->p.y + this->dim.y;

    return isContained;
}


void Quadtree::addMembers() {
    for(Boid boid : this->members) {
        if(this->containsBoid(boid)) {
            members.push_back(boid);
        }
    }

    if(members.size() > maxBoidsPerQuadrant) {
        this->createChildren();
    }
}

void Quadtree::createChildren() {
    Vector2i childDim = this->dim / 2;
    Vector2i childPos[4] = {
        this->p,
        this->p + Vector2i(childDim.x, 0),
        this->p + Vector2i(0, childDim.y),
        this->p + childDim
    };

    for(int i = 0; i < 4; i++) {
        this->children[i] = new Quadtree(childPos[i], childDim, this->members);
    }

    this->members = vector<Boid>(0);
}


// vector<Boid> Quadtree::searchBoids(Boid boid) {
//     vector<Boid> boidsInVision;
//     // if(this->children[0]) {
//         for(Quadtree child : children) {
//             // if(child.members) {
//                 vector<Boid> newBoids = child.searchBoids(boid);
//                 // if(newBoids != NULL) {
//                     for(Boid b : newBoids) {
//                         if(boid.isInVision(b)) {
//                             boidsInVision.push_back(b);
//                         }
//                     }
//                 // }
//             // }
//         }
//     // }

//     return boidsInVision;
// }