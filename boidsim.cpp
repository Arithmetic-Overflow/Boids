#ifndef BOIDSIM
#define BOIDSIM
    #include "boidsim.hpp"
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

    canvasWidth = 500;
    canvasHeight = 500;

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

Ubuntu:

cd /mnt/c/projects/games/c++/boids
export DISPLAY=:0

g++ -I/mnt/c/SFML/include -c main.cpp -o main.o
g++ -L/mnt/c/SFML/lib -o pogoboi.exe -o main.o -lsfml-graphics -lsfml-window -lsfml-system
./pogoboi



Windows:

g++ -IC:\SFML\include -c pogoboi.cpp -o pogo.o
g++ -LC:\SFML\lib -o pogoXD.exe -o pogo.o -lsfml-graphics -lsfml-window -lsfml-system

C:\SFML-2.5.1-windows-vc14-64-bit\SFML-2.5.1

*/