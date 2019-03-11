IDIR=./include
CC=g++
CFLAGS=-Wall -g

ODIR=./src/obj
BDIR=./bin

LIBS=-lsfml-graphics -lsfml-window -lsfml-system

MKDIR_P=mkdir -p

all: directories game

# Directories that need to exist (that are not in the repository) are created here
directories: $(ODIR) $(LDIR) $(BDIR)

$(ODIR):
	$(MKDIR_P) $(ODIR)

$(BDIR):
	$(MKDIR_P) $(BDIR)
# End directories

# All header files that need to be compiled go here
_DEPS= car.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

# All object files (which correspond to compiled .cpp files, duh) go here
_OBJ= main.o car.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o:./src/%.cpp $(DEPS)
	$(CC) -std=c++11 -c -o $@ $< $(CFLAGS)

game: $(OBJ)
	$(CC) -o ./bin/$@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean directories

clean:
	rm -f $(ODIR)/*.o

