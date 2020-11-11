#ifndef BOIDSIM
#define BOIDSIM
    #include "boidsim.hpp"
#endif

#ifndef BOID
#define BOID
    #include "Boid.hpp"
#endif


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

        for(int i = 0; i < numBoids; i++) {
            Boid thisBoid = boidArray[i];

            boidSprite.setPosition(thisBoid.p);
            boidSprite.setRotation(thisBoid.rotation());
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