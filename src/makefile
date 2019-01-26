CC = g++

CFLAGS = -Wall -std=c++11 -I $(IDIR)
LFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

IDIR = ../include
ODIR = obj

_DEPS = Texture.hpp RenderData.hpp Game.hpp Defines.hpp Direction.hpp
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))

_OBJS = main.cpp Texture.cpp RenderData.cpp Game.cpp
OBJS = $(patsubst %.cpp, $(ODIR)/%.o, $(_OBJS))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJS)
	$(CC) -o $@ $^ $(LFLAGS) $(CFLAGS)
