##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## build a binary
##

SRC	=	open_window.c	\
		build_map.c	\
		write_score.c	\
		best_score.c	\
		play_music.c	\
		my_strlen.c

OBJ	=	$(SRC:.c=.o)

NAME	=	parallaxe

CSFML   =       -lcsfml-graphics -lcsfml-system -lcsfml-window -lcsfml-audio

all:
	gcc -o $(NAME) $(SRC) $(CSFML) -lm -g3

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f *~
	rm -f *#

re:	fclean all
