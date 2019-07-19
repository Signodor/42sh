##
## EPITECH PROJECT, 2018
## make
## File description:
## file
##

NAME		=		libmy.a

SRC			=		$(shell find . -type f -name '*.c')

OBJ			=		$(SRC:.c=.o)

CC			=		@gcc

CFLAGS		+=		-I.

#COLOR

GREEN		=		\e[1;32m

WHITE		=		\e[0m

ORANGE		=		\e[38;5;208m

RED			=		\e[38;5;196m

BLUE		=		\e[1;34m

all:	$(NAME)

$(NAME):	$(OBJ)
	@ar rc ../$(NAME) $(OBJ)

%.o:	%.c
	@printf "$(BLUE)Compiling [ $(GREEN)$(notdir $<)$(BLUE) -> $(ORANGE)$(notdir $@)$(BLUE) ]\n$(WHITE)"
	@$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

clean:
	@rm -f $(OBJ)
	@printf "$(ORANGE)Removing object files.$(WHITE)\n"

fclean:	clean
	@rm -f ../$(NAME)
	@printf "$(ORANGE)Removing Library file.$(WHITE)\n"

re:	fclean	all

auteur:
	echo $(USER) > auteur

.PHONY: all libmy.a	clean	fclean	re
