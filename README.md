[25 Nov, 2025]
November, 2025 embarked on a journey to create a Halo Clone Game Engine from scratch, documenting design patterns via documentation and videos. 
Will hopefully upload to youtube as well, upon completion.

The goal is to create a mini, but satisfying Halo clone video game, implemented with OpenGL and Vulkan, that can run on all major 'desktop' operating systems.

However, currently the project only has entities and methods for windowing and handling inputs from kbm and the gamepad (PS4 tested) (Arch Linux i3wm).
For the heck of it I use SDL3 and GLFW window/input apis.

Hopefully development will be smooth.

[7 Dec, 2025]
I somehow implemented methods for wrapping a scene described in a json file to a scene class instance.
The scene class requests the meshlibrary to store mesh data. mesh data is extracted using tinygltf and meshlibray prevents mesh instance duplicates.
Alot of spegheti, and copies from chatbot.
