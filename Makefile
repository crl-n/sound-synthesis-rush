NAME = minisynth

SRC = main.c wavefunctions.c parser.c mixing.c

CFLAGS = -Wall -Werror -Wextra
CFLAGS += $(shell sdl2-config --cflags)

LIB = $(shell sdl2-config --libs)

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(LIB) $(SRC) -o $(NAME)

debug: $(SRC)
	$(CC) $(CFLAGS) -g $(LIB) $(SRC) -o $(NAME)

clean:

fclean: clean
	/bin/rm $(NAME)

re: fclean all

