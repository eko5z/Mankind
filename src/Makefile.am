bin_PROGRAMS=mankind
mankind_SOURCES=\
	main.cpp\
	Renderer.cpp\
	Game.cpp\
	InputSystem.cpp\
	MainInputManager.cpp\
	Texture.cpp\
	Shader.cpp\
	ChunkMesh.cpp\
	Program.cpp\
	Chunk.cpp\
	World.cpp\
	Font.cpp\
	TextRenderer.cpp\
	Mesh.cpp

AM_LDFLAGS=`pkg-config --libs sdl2`\
		   `pkg-config --libs SDL2_image`\
		   `pkg-config --libs SDL2_ttf`\
		   `pkg-config --libs gl`\
		   `pkg-config --libs glew`

AM_CPPFLAGS=--std=c++14 -g\
			`pkg-config --cflags sdl2`\
			`pkg-config --cflags SDL2_image`\
		    `pkg-config --cflags SDL2_ttf`\
			`pkg-config --cflags gl`\
			`pkg-config --cflags glew`

mv-local:
	@ $(MV) $(bin_PROGRAMS) ..

