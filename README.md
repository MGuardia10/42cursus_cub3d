# 42cursus_cub3d
A recreation of the world-famous Wolfenstein 3D game, widely recognized as one of the first first-person shooters (FPS). The main objective of this project is to develop a dynamic and subjective view, simulating the character's perspective, within a realistically represented 3D maze. The project explores the technique of ray-casting. Project Details:
- Dynamic View: The view adjusts in real-time according to the player's movements, providing an immersive experience. This adaptation is essential to simulate the visual perception of the character as they move through the maze.
  
- Subjective View: The player sees the world from the character's point of view, meaning the camera is positioned at the character's eye level, offering a first-person perspective.
  
- Realistic 3D Maze: The project aims to create a realistic-looking 3D maze, allowing the player to navigate and find their way through it.
  

![C](https://img.shields.io/badge/C-a?style=for-the-badge&logo=C&color=grey)
![Makefile](https://img.shields.io/badge/Makefile-a?style=for-the-badge&logo=monster&logoColor=orange&color=grey)

You can see the subject [**HERE.**](https://github.com/MGuardia10/42cursus/blob/main/subjects/en/cub3d_subject_en.pdf)

## Preview
https://github.com/user-attachments/assets/5bb36ff5-6551-4443-92a5-fda23db69242

## Installing and running the project:

> ℹ️ This project is done using [Codam MLX library](https://github.com/codam-coding-college/MLX42). If something MLX related is not working on your computer, make sure to check their documentation.

1- Clone this repository
	
	git clone https://github.com/MGuardia10/42cursus_cub3d.git
2- Navigate to the new directory and run `make`
	
	cd 42cursus_cub3d
   	make
3- Execute cub3D binary with a map of your choice, for example:

	./cub3d maps/valid/map6.cub

## Compiling the Program
The cub3D program comes with a Makefile that includes the following rules:

- `all`: compiles the program.
- `re`: recompiles the program.
- `clean`: removes obj directory with objects files.
- `fclean`: removes obj directory with objects files and cub3D binary.
- `test`: executes a script to check parsing status of all maps in `maps/invalid` folder.

## Disclaimer
> At [42School](https://en.wikipedia.org/wiki/42_(school)), almost every project must be written in accordance to the [Norm](https://github.com/MGuardia10/42cursus/blob/main/subjects/en/norm_en.pdf), the school's coding standard. As a result, the implementation of certain parts may appear strange and for sure had room for improvement.
