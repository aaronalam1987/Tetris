LIBS = -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lopengl32 -lfreetype -lgdi32 -lsfml-main -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg -lws2_32 -lsfml-system-s -lwinmm

# Optional Libs / -static-libgcc -static-libstdc++

OBJS = main.o inputMonitor.o pieces.o audio.o graphics.o pieceManager.o # List of object files

# -mwindows << reinclude this on non-debug.
all: compile link clean run

compile: $(OBJS)

# Compile both main.cpp and inputMonitor.cpp
%.o: %.cpp
	g++ -c $< -o $@ -I"C:\SFML-2.5.1\include" -DSFML_STATIC

link: $(OBJS)
	g++ $(OBJS) -o main -L"C:\SFML-2.5.1\lib" $(LIBS)

clean:
	rm -f *.o

run:
	./main.exe
