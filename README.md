# T1Engine
Basic 3D Fixed-Rendering Pipeline Engine built in C++ using OpenGL and Glut from scratch. Doesn't use shaders but still servers as a nice baseline for fixed-rendering and 3D Graphics with OpenGL.

- Includes custom working OBJ Loader with working illumination/normals, texturing and proper sub-object grouping
- Complete scene management implemented - basic state management
- Simple 3D Collisions (sphere-sphere)
- Efficent in terms of memory and processing power
- Skyboxes & Skyspheres
- Built in 3 weeks as a final project (excl. OBJ loader)
- Basic DEM terrain system implemented with polygon normals

Comes with a custom 3D OBJ Loader also built from scratch. Loads triangle and quad face meshes quickly and efficiently. As  this was done as a final project for a 3D Graphics Course external libraries besides Glut wasn't allowed - hence creating a custom OBJ Loader and simple collision system. NOTE: It would obviously be better to use an already existing solution for collison - such as Bullet physics, and like-wise for loading 3D models, but both my custom solutions work fine in hindsight and the 3D loader in particular, is quite feature complete.

Additionally, this engine while built as a project to explore 3D Graphics, its foundations, and the fixed-rendering pipeline of OpenGL - it was also built to server as  a possible baseline for a game engine.

## Contents
* [Todos](#todo)
* [Prerequisites](#prerequisites)
* [How to Use](#how-to-use)
* [Structure](#structure)
* [Examples](#examples)
	* [Video](#video)
	* [Screenshots](#screenshots)
* [References](#references)

## TODO:
- [X] Update Documentation
- [X] Refactor ActorDisplay.cpp and ActorDisplay.h
- [ ] Finalize Last (Unused) Scene

## Prerequisites:

Visual Studio 2015/2017, OpenGL Capable Graphics Card.
(Glut libraries come with project source)

## How to Use

Simply compile in Visual Studio. Currently working on other ways to reuse codebase (besides taking what you want, etc.)

## Structure

The structure of the T1 Engine is open, meaning that while certain things are set in stone customizability and future expandability was kept in mind during construction. Although there are base classes, e.g. the Actor Class, the split of logic is up to the developer - i.e. Where is collision calculated, what involvement do scenes have in controlling loading and initalization.

The included Actor classes and scenes just act as an example - they were also built in regards to steep time deadlines, and so certain corners were cut (e.g. the ActorPlayer class is not really feature complete and movement is handled elsewhere) but the functionality exists to do these properly, and can handle any type of fixed-rendering game.

Following structure constrains are listed here:
* Every movable object (exl. Camera) in the world is derived from Actor base class
	* Every Actor has a transform which contains position, rotation and scale
	* Every Actor implements an update method called every frame and,
	* Every Actor implements a render method called every time the screen is drawn
* Each Scene/Level is built and derived from the GlutScene base class
	* Scene/Level Management is handled by SceneManager and its wrapper functions
* Objects, Textures & Terrains area loaded via utility ResourceManage class
* Camera is considered separate entity
	* Movable by calling relevant methods
	* Refresh method that is called every frame to update renderer, etc.
* Skyboxes are separate objects and not inherently attached to a scene



## Examples

Below are some screenshots of basic scenes built to showcase the engine as well as a video showing the engine running.

### Video

Coming soon

### Screenshots

(All screenshots of scenes are running at 60+ FPS)

First Scene: (Multiple Models & Multi-textured/Subgrouped Models)

![t1enginess1](https://user-images.githubusercontent.com/11038569/33595674-14e5c954-d9ed-11e7-8790-2088a0ae823b.png)

First Scene 2: (Multiple Models & Multi-textured/Subgrouped Models)

![t1enginess2](https://user-images.githubusercontent.com/11038569/33595699-287af7aa-d9ed-11e7-90ef-6590fd6c1cdc.png)

Second Scene: (Staged Scene)

![t1enginess3](https://user-images.githubusercontent.com/11038569/33595725-443fabfc-d9ed-11e7-8235-03be452b1430.png)

Second Scene 2: (Staged Scene)

![t1enginess5](https://user-images.githubusercontent.com/11038569/33595837-b740ad22-d9ed-11e7-91b2-a36a09a4c16d.png)

Third Scene: (Basic Terrain System)

![t1enginess4](https://user-images.githubusercontent.com/11038569/33595734-507ee766-d9ed-11e7-9924-39c01ff9050c.png)

## References
All relevant references included in source code classes.
