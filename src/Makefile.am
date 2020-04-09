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
	Terrain.cpp\
	Font.cpp\
	Mesh.cpp\
	TerrainGenerator.cpp\
	TileManager.cpp\
	PhysicsSystem.cpp\
	DirectionalLight.cpp\
	BaseGUIElement.cpp\
	GUILabel.cpp\
	HighlightMesh.cpp\
	QuadMesh.cpp\
	Camera.cpp\
	GraphicsSystem.cpp\
	GraphXManager.cpp

mankind_CPPFLAGS = @DEPS_CPPFLAGS@ --std=c++14 -g
mankind_LDFLAGS  = @DEPS_LDFLAGS@
mankind_LDADD    = @DEPS_LDADD@

mv-local:
	@ $(MV) $(bin_PROGRAMS) ..

