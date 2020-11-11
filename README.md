# Boids
A C++/SFML implementation of boids.

Tested on Ubuntu (WSL2 Windows 10)

## Installing Dependencies and Building The Project
Currently I have pretty poor support for Windows and OSX.
This is my first proper use of C++ and I can't get SFML to install correctly on Windows.
Apologies for the lack of support, and if anyone has some resources where I can learn about this it would be well appreciated.

### Installing the SFML library:
In order to install the C++ SFML library:
  bash: `sudo apt-get install sfml`
        

### Building the project and the Makefile
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


## What's Coming?
### Refactoring File Structure
I'm going to give each class its own header file and put the class definitions in their proper place

### Performance Overhaul
Once the boid 'vision' works as intended and the variables are cleaned up I will work on performance. Currently my algorithms for iterating through boids are O(n^2). For each boid I'm iterating through every other boid. I'm hoping to implement some sort of spatial partitioning scheme to make this run much smoothly for high numbers of boids.

The optimisation I have in mind will be a quadtree which is an O(log n) lookup, making my algorithm O(n log n) overall (if my maths doesn't fail me).

### Make Boid Movement Frame Independent
Once the quadtree is implemented I will make a clock object so that the boids movement isn't tied to the framerate of the window. This means that a lower framerate won't slow boids down and a higher framerate won't lead to erratic behaviour. The downside of this though is that the simulation will be 'less accurate' as the timesteps are not perfectly uniform (as they would be in a pre-rendered simulation) but as this is a realtime application and the framerate should be rather high after optimisation I don't think that this will lead to a visible difference.

### Tweaking The Weights
The weights need to be tweaked to make the simulation look more natural, but this is a fairly trivial and length process: I'll leave it till the end.

### Fullscreen
I am working on gettings the SFML Fullscreen mode to better integrate with the simulation.
Fullscreen is not planned in the near future as it hinders testing and I have no real incentive to.

It is however going to come at some point down the line when the program is more refined.
