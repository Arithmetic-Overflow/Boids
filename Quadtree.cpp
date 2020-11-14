#ifndef QUADTREE
#define QUADTREE
    #include "Quadtree.hpp"
#endif


int maxMembersPerQuadrant = 1;

Quadtree::Quadtree(Boid boidArray[]) {
    this->p = Vector2i(0, 0);
    this->dim = Vector2i(canvasWidth, canvasHeight);

    this->members = vector<Boid>(numBoids);

    // cout << 1 << endl;

    for(int i = 0; i < numBoids; i++) {
        this->members[i] = boidArray[i];
    }

    // cout << 2 << endl;

    this->limitMembers();
}


Quadtree::Quadtree(Vector2i p, Vector2i dim, vector<Boid> boidsInParent) {
    this-> p = p;
    this->dim = dim;
    this->members = boidsInParent;

    this->limitMembers();
}


bool Quadtree::containsPoint(Vector2f point) {
    return
        point.x >= this->p.x                 &&
        point.x < this->p.x + this->dim.x    &&
        point.y >= this->p.y                 &&
        point.y < this->p.y + this->dim.y;
}


bool Quadtree::containsPoint(Vector2i point) {
    return
        point.x >= this->p.x                 &&
        point.x < this->p.x + this->dim.x    &&
        point.y >= this->p.y                 &&
        point.y < this->p.y + this->dim.y;
}


// inclusive for lower bounds, exclusive for upper bounds
bool Quadtree::containsBoid(Boid boid) {
    // int bx = (int) boid.p.x;
    // int by = (int) boid.p.y;

    // these calculations being done multiple times is a reundancy
    // in the future I will factor them out
    
    return this->containsPoint(boid.p);
}


void Quadtree::limitMembers() {
    for(int i = 0; i < members.size(); i++) {
        Boid boid = this->members[i];
        if(!this->containsBoid(boid)) {
            members.erase(members.begin() + i);
            i--;
        }
    }

    if(members.size() > maxMembersPerQuadrant) {
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


vector<Boid> Quadtree::searchBoids(Boid boid) {
    vector<Boid> boidsInVision;
    for(Quadtree *child : children) {
        if(child == NULL) {
            break;
        }

        vector<Boid> newBoids = child->searchBoids(boid);
        
        for(Boid b : newBoids) {
            if(boid.isInVision(b)) {
                boidsInVision.push_back(b);
            }
        }
    }

    return boidsInVision;
}


bool Quadtree::intersectsRect(Vector2i vertices[]) {
    // bool intersects = false;
    // for(int i = 0; i < 4; i++) {
    //     intersects |= this->containsPoint(vertices[i]);
    // }

    bool spansQuad = true;
    
    int leftCount  = 0;
    int rightCount = 0;
    int aboveCount = 0;
    int belowCount = 0;

    for(int i = 0; i < 4; i++) {
        Vector2i vertex = vertices[i];
        if(vertex.x <= this->p.x) {
            leftCount++;
        }

        else if(vertex.x >= this->p.x + this->dim.x) {
            rightCount++;
        }

        if(vertex.y <= this->p.y) {
            aboveCount++;
        }

        else if(vertex.y >= this->p.y + this->dim.y) {
            belowCount++;
        }
    }

    spansQuad = (leftCount < 3 && aboveCount < 3 && rightCount <3 && belowCount < 3);
    return spansQuad;
}


vector<Boid> Quadtree::closeBoidsInNode(Vector2i vertices[4]) {
    vector<Boid> nearby;

    if(!this->intersectsRect(vertices)) {
        return nearby;
    }

    if(this->children[0] != NULL) {
        for(Quadtree *child : this->children) {
            for(Boid boid : child->closeBoidsInNode(vertices)) {
                nearby.push_back(boid);
            }
        }
    }

    else {
        for(Boid boid : this->members) {
            nearby.push_back(boid);
        }
    }

    return nearby;
}


vector<Boid> Quadtree::nearbyBoids(Boid boid) {
    Vector2i searchSquare[4] = {
        Vector2i(boid.p.x - boid.visionRad, boid.p.y - boid.visionRad),
        Vector2i(boid.p.x - boid.visionRad, boid.p.y + boid.visionRad),
        Vector2i(boid.p.x + boid.visionRad, boid.p.y + boid.visionRad),
        Vector2i(boid.p.x + boid.visionRad, boid.p.y - boid.visionRad)
    };

    // Vector2i searchSquare[4] = {
        // Vector2i(400, 400),
        // Vector2i(900, 400),
        // Vector2i(900, 700),
        // Vector2i(400, 700)
    // };

    vector<Boid> nearby = this->closeBoidsInNode(searchSquare);

    // for(int i = 0; i < nearby.size(); i++) {
    //     // cout << nearby[i].p.x << endl;
    //     if(boid.p == nearby[i].p) {
    //         nearby.erase(nearby.begin() + i);
    //         break;
    //     } 
    // }
    // cout << endl;

    for(int i = 0; i < nearby.size(); i++) {
        if(nearby[i].p == boid.p) {
            nearby.erase(nearby.begin() + i);
            break;
        }
    }

    return nearby;
}


vector<RectangleShape> Quadtree::getRect(void) {
    vector<RectangleShape> rects;

    RectangleShape rect = RectangleShape((Vector2f) this->dim);
    rect.setFillColor(Color::Transparent);
    rect.setOutlineColor(Color(255,255,255));
    rect.setOutlineThickness(2);
    rect.move((Vector2f) this->p);

    rects.push_back(rect);

    // cout << 1 << endl;

    if(children[0] == NULL) {
        return rects;
    }

    for(Quadtree *child : children) {
        

        vector<RectangleShape> childRects = child->getRect();

        for(RectangleShape r : childRects) {
            rects.push_back(r);
        }
    }

    return rects;
}