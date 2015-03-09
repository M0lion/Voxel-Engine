LIBS = -lglfw3 -lGLEW -lGL -lGLU -lX11 -lXxf86vm -lXrandr -lpthread -lXi -lm -lXinerama -lXcursor -lm
CFLAGS = -g -c -std=c++11 -fpermissive -O0

all: main

main: main.o ShaderUtils.o Camera.o Mesh.o Shader.o Transform.o Block.o Chunk.o Game.o GamepadManager.o Types.o 
	g++ -o main main.o ShaderUtils.o Camera.o Mesh.o Shader.o Transform.o Block.o Chunk.o Game.o GamepadManager.o Types.o  $(LIBS)

main.o: main.cpp
	g++ $(CFLAGS) main.cpp

ShaderUtils.o: ShaderUtils.cpp ShaderUtils.h 
	g++ $(CFLAGS) ShaderUtils.cpp ShaderUtils.h

Camera.o: Camera.cpp Camera.h 
	g++ $(CFLAGS) Camera.cpp Camera.h

Mesh.o: Mesh.cpp Mesh.h 
	g++ $(CFLAGS) Mesh.cpp Mesh.h

Shader.o: Shader.cpp Shader.h 
	g++ $(CFLAGS) Shader.cpp Shader.h

Transform.o: Transform.cpp Transform.h 
	g++ $(CFLAGS) Transform.cpp Transform.h

Block.o: Block.cpp Block.h 
	g++ $(CFLAGS) Block.cpp Block.h

Chunk.o: Chunk.cpp Chunk.h 
	g++ $(CFLAGS) Chunk.cpp Chunk.h

Game.o: Game.cpp Game.h 
	g++ $(CFLAGS) Game.cpp Game.h

GamepadManager.o: GamepadManager.cpp GamepadManager.h 
	g++ $(CFLAGS) GamepadManager.cpp GamepadManager.h

Types.o: Types.cpp Types.h 
	g++ $(CFLAGS) Types.cpp Types.h

clean:
	rm *.o