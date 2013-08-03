CC = g++
CFLAGS  = -ggdb -c -O3 -Wall -std=c++11
LDFLAGS =

EXECUTABLE = xiangqi

SOURCEDIR = src
BUILDDIR = build
SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS = $(patsubst $(SOURCEDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

all: dir $(EXECUTABLE)

dir:
	mkdir -p $(BUILDDIR)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ $(LDFLAGS) -o $@

$(BUILDDIR)/%.o : $(SOURCEDIR)/%.cpp
	$(CC) $(CFLAGS) $< -o $@
	
.PHONY: clean

clean:
	rm $(BUILDDIR)/*o
	rmdir $(BUILDDIR)
	rm $(EXECUTABLE)

