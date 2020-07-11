# SnowTerrainDeformation

 OpenGL implementation of Jesper Persson master thesis : __Volume-Preserving Deformation of Terrain in Real-Time__.

Link to paper : http://www.diva-portal.org/smash/get/diva2:1333403/FULLTEXT01.pdf

## Requirement

- Visual Studio 2019
- OpenGL 4.5

I used my little engine for this implementation, I hope the code is explicit enough to be easily moved to another framework.

## Build

Open the solution __Snow.sln__, set the Project property __Debugging/Working Directory__ to *$(OutDir)* and everything should be ready to go.

## Controls

When the viewport is focused (just click inside the viewport window) you can rotate the camera by holding the __shift__ key and draging the mouse with the __left button__ down.

You can zoom by holding the __shift__ key and draging verticaly the mouse with the __right button__ down. You can also use the __mouse wheel__ to zoom.

You can change the orbit center of the camera by selecting an object in the __Outliner__ list and pressing the __F__ key.

## Settings

The majority of the settings are in the __Snow__ panel of the editor.

If you wish to tweak the blurs or the bloom, you can select the corresponding resource (*Normal Map Blur* for example) in the __Resources__ list, their properties will be appear in the __Details__ window.

For the drag float boxes, you can hold the __alt__ key to change the values slower.

## Scene

The scene should be composed of several objects :

- Animated boots
- Spot the cow
- Fences
- Lantern
- Ball

![Expected result of the scene.](/Data/SampleScene.png)

## Implementation details

You can find the detailed explanation [here](http://www.remimaigne.com/volume-preserving-deformation-of-terrain-in-real-time/).
