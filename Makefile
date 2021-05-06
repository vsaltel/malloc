CC		=	gcc
CFLAGS	+=	-Wall -Wextra #-Werror

ifdef DEBUG
	CFLAGS += -g3 -fsanitize=address
endif

ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

SHELL	=	bash

VALGRIND_ARGS = --leak-check=full --show-leak-kinds=all

NAME 	=	libft_malloc_$(HOSTTYPE).so
LIBNAME	=	libft_malloc.so
SRCDIR	=	srcs
INCDIR	=	includes
OBJDIR	=	objs

FILES	=	malloc.c			\
			calloc.c			\
			realloc.c			\
			reallocf.c			\
			area.c				\
			memory.c			\
			free.c				\
			print.c				\
			utils.c				\
			show_alloc_mem.c	\
			show_alloc_mem_ex.c


SRCS	=	$(addprefix $(SRCDIR)/, $(FILES))
OBJS	=	$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJSD	=	$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.d)

##### Colors #####
_END=\x1b[0m
_BOLD=\x1b[1m
_UNDER=\x1b[4m
_REV=\x1b[7m
_GREY=\x1b[30m
_RED=\x1b[31m
_GREEN=\x1b[32m
_YELLOW=\x1b[33m
_BLUE=\x1b[34m
_PURPLE=\x1b[35m
_CYAN=\x1b[36m
_WHITE=\x1b[37m

.PHONY: all clean fclean re norm tests

.SILENT:

all: $(NAME)

$(NAME): $(OBJS)
	@echo -e -n "\n${_BLUE}${_BOLD}[Create Shared Library] $(NAME)${_END}"
	@$(CC) $(CFLAGS) -shared -o $(NAME) $(OBJS)
	@ln -sf $(NAME) $(LIBNAME)
	@echo -e "\n${_GREEN}${_BOLD}$(NAME) done.${_END}"

$(OBJDIR)/%.o: $(SRCDIR)/%.c Makefile
	@mkdir -p $(@D)
	@echo -n -e "\r\033[K${_PURPLE}${BOLD}[${NAME}] Compiling $<${_END}"
	@$(CC) $(CFLAGS) -I $(INCDIR) -MMD -fPIC -o $@ -c $<

clean:
	@echo -e "${_RED}${_BOLD}Cleaning obj files...${_END}"
	@rm -f $(OBJS)
	@rm -f $(OBJSD)
	@rm -f test[0-9]*
	@rm -f mytest
	@rm -Rf $(OBJDIR)

fclean: clean
	@echo -e "${_RED}${_BOLD}Cleaning project...${_END}"
	@rm -f $(LIBNAME)
	@rm -f $(NAME)
	@rm -rf $(NAME).dSYM

re: fclean
	@$(MAKE)

-include $(OBJSD)
