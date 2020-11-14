#ifndef BOIDSIM
#define BOIDSIM
    #include "boidsim.hpp"
#endif

#ifndef BOID
#define BOID
    #include "Boid.hpp"
#endif

#ifndef QUADTREE
#define QUADTREE
    #include "Quadtree.hpp"
#endif


// void drawQuad(Quadtree q, RenderWindow canvas) {

// }


float boidSize = 20;

void updateBoidVelocities(Boid boidArray[]) {
    Vector2f newVelocities[numBoids];

    Boid *thisBoid = boidArray;
    
    for(int i = 0; i < numBoids; i++) {
        newVelocities[i] = thisBoid->calculatev(boidArray, i);
        thisBoid++;
    }

    thisBoid = boidArray;

    for(int i = 0; i < numBoids; i++) {
        thisBoid->v = newVelocities[i];
        thisBoid++;
    }
}


void moveBoids(Boid boidArray[]) {
    for(int i = 0; i < numBoids; i++) {
        boidArray[i].move();
    }
}


int main(int argc, char *argv[]) {
    srand((unsigned int) time(NULL));

    canvasWidth = 900;
    canvasHeight = 900;

    VideoMode desktopDetails = VideoMode::getDesktopMode();
    canvasWidth = desktopDetails.width;
    canvasHeight = desktopDetails.height;

    RenderWindow canvas(VideoMode(canvasWidth, canvasHeight), "sfmltest", Style::Close | Style::Titlebar);//Style::Fullscreen);

    Texture boidTexture;
    boidTexture.loadFromFile("./sprites/Arrow20.png");

    Sprite boidSprite;
    boidSprite.setTexture(boidTexture);

    Boid boidArray[numBoids];
    for(int i = 0; i < numBoids; i++) {
        boidArray[i] = Boid();
    }

    Event event;
    while(canvas.isOpen()) {
        // while (canvas.pollEvent(event)) {
        //     switch(event.type) {
        //         case Event::Closed:
        //             canvas.close();
        //             break;

        //         case Event::Resized:
        //             break;
        //     }
        // }

        if(Keyboard::isKeyPressed(Keyboard::Escape)) {
            canvas.close();
        }

        updateBoidVelocities(boidArray);
        moveBoids(boidArray);

        canvas.clear();

        Quadtree qtree = Quadtree(boidArray);

        vector<Boid> n = qtree.nearbyBoids(boidArray[0]);
        // cout << n.size() << endl;;

        // for(Boid b : n) {
        //     cout << b.p.x << ", " << b.p.y << endl;
        // }

        for(RectangleShape r : qtree.getRect()) {
            canvas.draw(r);
        }
    
        // drawQuad(qtree, canvas);

        // delete &qtree;

        // RectangleShape bounds(Vector2f(500, 300));
        // bounds.move(400, 400);
        CircleShape bounds(boidArray[0].visionRad);
        bounds.move(boidArray[0].p - Vector2f(boidArray[0].visionRad+boidSize/2, boidArray[0].visionRad+boidSize/2));
        bounds.setFillColor(Color::Transparent);
        bounds.setOutlineThickness(5);
        bounds.setOutlineColor(Color(200,200,0));
        canvas.draw(bounds);

        for(int i = 0; i < numBoids; i++) {
            Boid thisBoid = boidArray[i];

            boidSprite.setPosition(thisBoid.p);
            boidSprite.setRotation(thisBoid.rotation());
            
            if(i == 0) {
                // boidSprite.setColor(Color(255,255,255));
                // canvas.draw(boidSprite);
            }

            // else {
                boidSprite.setColor(Color(140,0,0));
            // }

            canvas.draw(boidSprite);
        }

        for(Boid thisBoid : n) {
            if(!boidArray[0].isInVision(thisBoid)) { continue; }
            boidSprite.setPosition(thisBoid.p);
            boidSprite.setRotation(thisBoid.rotation());
            boidSprite.setColor(Color(255,0,0));
            canvas.draw(boidSprite);
        }

        canvas.display();
    }

    cout << canvasWidth << endl << canvasHeight << endl;

    return 0;
}


/*
Personal comment

Ubuntu WSL:
cd /mnt/c/users/aryag/onedrive/documents/github/boids
*/