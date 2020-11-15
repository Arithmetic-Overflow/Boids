# Boids
A 2D C++/SFML implementation of boids.

Tested on Ubuntu (WSL2 Windows 10)

## What Are Boids?
Boids are ["bird-oid/bird-like objects"](https://en.wikipedia.org/wiki/Boids) that exhibit a flocking behaviour. This is done so through the use of 3 simple rules:
1. Separation
2. Alignment
3. Cohesion

Each rule is only applied to those boids that are in vision of the current boid. Each boid has a maximum distance that it can see and a maximum angle that its vision spans (for the purposes of this implementation at least).

### Separation
Each boid will try to avoid crashing into other nearby boids (by exhibiting a steering force away from the position of nearby boids). For my implementation I have decided that the closer the boids are, the greater the steering is. I have specifically used the function 1/distance to scale the steering force.

### Alignment
Each boid will try to match the same velocity as nearby boids. Boids in vicinity of each other will try to steer to be heading the same direction as each other.

### Cohesion
Each boid will try to steer towards the average position of nearby boids. Boids in vicinity will try to cluster to the same location, along with separation this creates an equilibrium where the boids can form a (normally circular or spherical) flying formation

### More Rules
None of the following rules are explicitly specified when writing an implementation of boids but they are either based off the behaviours and limitations of real bird, or are sensible guidelines for your own implementation.

**Blind-spots:** The inability for boids to see behind them is not necessary for boid behaviour, but I felt it was fitting as birds don't have vision that spans all 360 degrees, so I added a blind-spot to each boid.

**Constant speed:** If a bird is slower than a minimum threshold value it will begin to lose altitude. And birds can also (obviously) not accelerate indefinately. In order to try and capture this I have set a certain speed that each boid must always fly at.

**Maximum acceleration:** Birds can only turn so fast, and so are boids have a maximum acceleration. The (magnitude of) acceleration of a boid can be any value between 0 and the maximum acceleration threshold. Acceleration in this context doesn't determine how quickly their *speed* changes but how quickly their *velocity* changes. The velocity of a boid is not only the speed but the direction in which it is facing. A higher acceleration means a quicker turn and a smaller turn radius.


## Installing Dependencies and Building The Project
Okay, so you want to build and run the project.
Currently I have little support for Windows and OSX. But in all fairness the Linux and OSX (and WSL/WSL2) builds for the project should be near identical.

I have provided the instructions for going from a fresh install of a Ubuntu WSL to a working executable of this project.

### Installing the g++ compiler
In order to install the g++ compiler:
  bash: `sudo apt-get install g++`

The g++ compiler will turn the C++ source code into executable machine code.
If you wish to use Clang instead of g++ then you will need to edit the makefile.
(Simply find and replace all instanced of 'g++' with 'clang')


### Installing the SFML library:
In order to install the C++ SFML library:
  bash: `sudo apt-get install sfml`
        

### The makefile and building the project
Once installed download the project and put it in all under the same directoy.
Make sure to maintain the directory structure of the Sprites folder (don't change anything).
Once all contents have been placed under the same directory compile using make:
  bash: `make`

a clean command and an exportDisplay command are built into the makefile.
clean is used to remove the executable and object files constructed in the build.
exportDisplay is used to set the display environment if you're on WSL2.

### WSL2 XServer
If using Windows 10 WSL: set up an XServer first.
[Here is an online resource that will guide you through step by step.](https://virtualizationreview.com/articles/2017/02/08/graphical-programs-on-windows-subsystem-on-linux.aspx)

If using an XServer on WSL2 make sure to remember to run `make exportDisplay` every time you run the program.
Failure to do so will stop the program from being able to run.


## Running The Program
So you have successfully installed SFML and built the project: what now?
The only thing left to do is run it!

Making sure you are in the same directory as before, use the following command:
  bash: `./boidsim`
  
Once you run the command a display window will pop up containing the simulation.
Feel free to draw it to wherever on your screen you need to: it's moveable but not resizable.

The window will be the exact width and height of your display. If you wish for it to be smaller then find the lines where I have assigned canvasWidth and canvasHeight values. Then proceed to subtract a few hundred pixels from them.

Have fun messing around with it!


## Future Updates:

### Performance Increase
Currently the quadtree has no insert method and instead 'inserts' the whole array into it at once. This might hinder performance (I can't analyse the complexity but I susepct it's O(n^2) to insert all boids when it should only be O(n log n)).

An insert method needs to be added and used.
