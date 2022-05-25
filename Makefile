NAME = minisynth

SRC = main.c

CFLAGS = -Wall -Werror -Wextra
CFLAGS += -I${HOME}/.brew/include/SDL2 -D_THREAD_SAFE

LIB = -L${HOME}/.brew/lib -lSDL2

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(LIB) $(SRC) -o $(NAME)

clean:

fclean: clean
	/bin/rm $(NAME)

re: fclean all
