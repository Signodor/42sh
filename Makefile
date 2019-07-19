##
## EPITECH PROJECT, 2018
## Makefile infinadd
## File description:
## Make File for infinite add project
##

#	CONFIGURATIONS

NAME		=		42sh

MAIN		=		main.c

ROOT		=		.

SRC_DIR		=		$(ROOT)/src

TESTS_DIR	=		$(ROOT)/tests

LIB_DIR		=		$(ROOT)/libraries

BUILD_DIR	=		$(ROOT)/builds

INCLUDE_DIR	=		$(ROOT)/include

HEADERS		:=		$(shell find $(INCLUDE_DIR)/ -type f -name '*.h')

SRC			:=		$(shell find $(SRC_DIR)/ -type f -name '*.c')

SRC_TESTS	:=		$(shell find $(SRC_DIR) $(TESTS_DIR) -type f -name '*.c' -not -path $(SRC_DIR)/$(MAIN) 2> /dev/null)

LIBRARIES	:=		$(shell find $(LIB_DIR) -type d -maxdepth 1 -not -path "$(LIB_DIR)" 2> /dev/null)

OBJ			=		$(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

OBJ_TESTS	=		$(SRC_TESTS:$(ROOT)/%.c=$(BUILD_DIR)/%.o)

WARN		=		-W -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -Wunreachable-code

CFLAGS		=		-D _GNU_SOURCE -I $(INCLUDE_DIR) -g

LDFLAGS		=		-L$(LIB_DIR) $(addprefix -l,$(notdir $(LIBRARIES))) -l ncurses

DEB			=		$(WARN) -g3 

CC			=		gcc

V			=		@

#	COLORS

GREEN		=		\e[1;32m

WHITE		=		\e[0m

ORANGE		=		\e[1;38;5;208m

RED			=		\e[1;38;5;196m

BLUE		=		\e[1;34m

PINK		=		\e[1;38;5;198m

#	PERCENTAGE

THIS		=		$(firstword $(MAKEFILE_LIST))	

ifndef ECHO
T			:=		$(shell $(MAKE) $(MAKECMDGOALS) --no-print-directory \
      				-nrRf $(THIS) \
      				ECHO="COUNTTHIS" | grep -c "COUNTTHIS")
N			:=		x
C			=		$(words $N)$(eval N := x $N)
ECHO		=		echo -e "\r$(PINK)[`printf "%3s" \`expr $C '*' 100 / $T\``%]"
endif

debug:	CFLAGS += $(DEB)

all:	compile_lib	$(NAME)

compile_lib:	$(LIBRARIES)

$(NAME):	$(OBJ)
	$(V)$(ECHO) "$(ORANGE) Linking \t$(RED)$(notdir $@)$(WHITE)"
	$(V)$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

$(BUILD_DIR)/%.o:	$(SRC_DIR)/%.c	$(HEADERS)
	$(V)mkdir -p $(dir $@)
	@$(ECHO) "$(BLUE) Compiling\t$(GREEN)$(notdir $<)$(WHITE)"
	$(V)$(CC) $(CFLAGS) -o $@ -c $<

$(LIBRARIES):
	$(V)make --no-print-directory -C $@

$(BUILD_DIR)/%.o:	$(ROOT)/%.c	$(HEADERS)
	$(V)mkdir -p $(dir $@)
	$(V)printf "$(BLUE)Compiling (test) [ $(GREEN)$(notdir $<)$(BLUE) -> $(ORANGE)$(notdir $@)$(BLUE) ]\n$(WHITE)"
	$(V)$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

tests_run:	compile_lib	$(OBJ_TESTS)
	$(V)printf "$(BLUE)Compile sources and tests : $(GREEN)success$(WHITE)\n"
	$(V)$(CC) $(CFLAGS) $(OBJ_TESTS) $(LIB) -o unit_test -Iinclude -lcriterion --coverage $(LDFLAGS)
	$(V)printf "$(BLUE)Linking obj and Libraries : $(GREEN)success$(WHITE)\n"
	$(V)printf "$(BLUE)Launching tests...$(WHITE)\n"
	$(V)./unit_test
	$(V)gcovr --branches --exclude tests
	$(V)rm -f unit_test

clean:
	$(RM) -r $(BUILD_DIR)
	find $(ROOT) -name '*.gcda' -type f -delete
	find $(ROOT) -name '*.gcno' -type f -delete

fclean:	clean
	find $(ROOT) -name '*.a' -type f -delete
	rm -f $(NAME)

run:
	$(V)./$(NAME)

re:
	$(V)$(MAKE) --no-print-directory -s $(THIS) fclean
	$(V)$(MAKE) --no-print-directory -s $(THIS) all

.PHONY:	all	fclean	clean	run	re	tests_run	$(LIBRARIES)	debug
