##
## EPITECH PROJECT, 2018
## make
## File description:
## file
##

NAME		=		libvector.a

SRC			=		$(shell find . -type f -name '*.c')
OBJ			=		$(SRC:.c=.o)

CC			=		gcc -g3

CFLAGS		+=		-I.

all:	$(NAME)

$(NAME):	$(OBJ)
	@ar rc ../$(NAME) $(OBJ)

%.o:	%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

clean:
	@rm -f $(OBJ)

fclean:	clean
	@rm -f ../$(NAME)

re:	fclean	all

.PHONY: all	clean	fclean	re
