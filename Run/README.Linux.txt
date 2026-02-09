AsteroidsWarfield - Linux Installation Guide
=============================================

To run the game on Linux, certain system libraries are required.
Here is how to install them on the most common distributions.

1. Required Dependencies:
-------------------------
The game uses the following libraries:
- FLTK 1.3 (GUI Toolkit)
- OpenGL & GLU (3D Rendering)
- OpenAL (3D Sound)
- libsndfile (Audio file loading)

2. Installation Commands:
--------------------------

On Ubuntu, Debian, Linux Mint and derivatives:
   Run in a terminal:
   sudo apt update
   sudo apt install libfltk1.3 libopenal1 libsndfile1 libglu1-mesa libgl1-mesa-glx

On Fedora:
   sudo dnf install fltk freealut openal-soft libsndfile mesa-libGLU mesa-libGL

On Arch Linux:
   sudo pacman -S fltk openal libsndfile glu mesa

3. Running the Game:
--------------------
Once dependencies are installed, you can run the game from this directory:
   ./AWF

Or use the launch script if present:
   ./AWF.sh
