bin_PROGRAMS=mankind
mankind_SOURCES=\
	main.cpp\
	Renderer.cpp\
	Game.cpp\
	InputSystem.cpp\
	MainInputManager.cpp\
	Texture.cpp\
	Shader.cpp

AM_LDFLAGS=-lSDL2 -lSDL2_image -lGL
AM_CPPFLAGS=--std=c++14 -g

mv-local:
	@ $(MV) $(bin_PROGRAMS) ..

