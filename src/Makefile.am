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
	Mesh.cpp\
	WorldGenerator.cpp\
	TileManager.cpp\
	PhysicsSystem.cpp\
	DirectionalLight.cpp\
	Sky.cpp\
	BaseGUIElement.cpp\
	GUILabel.cpp\
	HighlightMesh.cpp\
	QuadMesh.cpp

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

