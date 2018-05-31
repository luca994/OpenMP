NAME = soccer_mpi_project
CC = g++
CFLAGS = -O3 -fopenmp -std=c++14 -I $(INCDIR)
LDFLAGS = -lm
SRCDIR = ./src
INCDIR = ./include
BINDIR = /usr/local/bin
SOURCES = $(SRCDIR)/main.cpp $(SRCDIR)/sensor.cpp $(SRCDIR)/ball.cpp $(SRCDIR)/field.cpp $(SRCDIR)/match.cpp $(SRCDIR)/player.cpp $(SRCDIR)/position.cpp $(SRCDIR)/referee.cpp $(SRCDIR)/timeinterval.cpp $(SRCDIR)/event.cpp $(SRCDIR)/parser.cpp
OBJECTS = $(SOURCES:.c=.o)

all:$(NAME)

$(NAME): $(OBJECTS)
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)

$(SRCDIR)/%.o: %.c
	$(CC) $^ -c $< $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(NAME)
	rm -f $(SRCDIR)/*.o