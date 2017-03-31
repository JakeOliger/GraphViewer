CXX = g++ -std=gnu++14
DEBUG = -g
OBJS = main.o window.o
LFLAGS = -Wall $(DEBUG) `sdl2-config --cflags --libs` -lSDL2_image
CFLAGS = -Wall -c $(DEBUG) `sdl2-config --cflags`
PROFILE = -pg
OUT = compute

$(OUT): $(OBJS)
	$(CXX) $(OBJS) $(LFLAGS) -o $(OUT)

main.o:
	$(CXX) $(CFLAGS) src/main.cpp

window.o: src/window.h
	$(CXX) $(CFLAGS) src/window.cpp

clean:
	\rm *.o $(OUT)

prof:
	$(CXX) $(OBJS) $(LFLAGS) -o $(OUT) $(PROFILE)