CC = g++
CFLAGS  = -g -c -O3 -Wall
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
	$(CC) $^ -o $@

$(BUILDDIR)/%.o : $(SOURCEDIR)/%.cpp
	$(CC) $(CFLAGS) $< -o $@
	
.PHONY: clean

clean:
	rm $(BUILDDIR)/*o
	rmdir $(BUILDDIR)
	rm $(EXECUTABLE)

