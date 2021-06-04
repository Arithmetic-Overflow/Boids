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

#define FPSCAP 62


float boidSize = 20;
float dt;

void updateBoidVelocities(Boid boidArray[]) {
    Vector2f newVelocities[numBoids];

    Boid *thisBoid = boidArray;
    Quadtree qtree(boidArray);
    
    for(int i = 0; i < numBoids; i++) {
        vector<Boid> nearby = qtree.nearbyBoids(*thisBoid);
        newVelocities[i] = thisBoid->calculatev(nearby);
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

    RenderWindow canvas(VideoMode(canvasWidth, canvasHeight), "sfmltest", Style::Close | Style::Titlebar | Style::Fullscreen);
    canvas.setFramerateLimit(FPSCAP);

    Texture boidTexture;
    boidTexture.loadFromFile("./sprites/Arrow20.png");

    Sprite boidSprite;
    boidSprite.setTexture(boidTexture);

    Boid boidArray[numBoids];
    for(int i = 0; i < numBoids; i++) {
        boidArray[i] = Boid();
    }


    Clock clock;
    Event event;

    while(canvas.isOpen()) {
        dt = clock.restart().asSeconds();

        if(Keyboard::isKeyPressed(Keyboard::Escape)) {
            canvas.close();
        }

        updateBoidVelocities(boidArray);
        moveBoids(boidArray);

        canvas.clear();

        for(int i = 0; i < numBoids; i++) {
            Boid thisBoid = boidArray[i];

            boidSprite.setPosition(thisBoid.p);
            boidSprite.setRotation(thisBoid.rotation());
            
            canvas.draw(boidSprite);
        }

        canvas.display();
    }

    return 0;
}