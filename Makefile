ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME	= libft_malloc_$(HOSTTYPE).so
LINK	= libft_malloc.so

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -fPIC
LFLAGS	= -shared -g3
RM		= rm -rf

OBJDIR	= obj
SOURCES	= srcs/malloc/malloc.c srcs/malloc/init.c srcs/malloc/alloc.c \
		  srcs/free/free.c srcs/realloc/realloc.c srcs/show_alloc_mem.c
OBJECTS	= $(SOURCES:%.c=$(OBJDIR)/%.o)

RED=\033[0;31m
GREEN=\033[0;32m

all: $(NAME) link

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled $<"

$(NAME): $(OBJECTS)
	@cd libft && make
	@$(CC) $(LFLAGS) $(OBJECTS) libft/libft.a -o $(NAME)
	@echo "Created $(NAME)"

link:
	@ln -sf $(NAME) $(LINK)
	@echo "Created symbolic link: $(LINK) -> $(NAME)"

clean:
	@cd libft && make clean
	@$(RM) $(OBJDIR)
	@echo "Object files removed"

fclean: clean
	@cd libft && make fclean
	@$(RM) $(NAME) $(LINK)
	@echo " Removed binary and link"

test:
	@set -e ; \
	cc main.c libft/libft.a -o prog || { echo "$(RED)[ERROR] Compilation failed$(RESET)"; exit 1; } ; \
	LD_PRELOAD=./libft_malloc.so ./prog || { echo "$(RED)[ERROR] ./prog$(RESET)"; exit 1; } ; \
	LD_PRELOAD=./libft_malloc.so ls || { echo "$(RED)[ERROR] ls$(RESET)"; exit 1; } ; \
	LD_PRELOAD=./libft_malloc.so echo HelloWorld || { echo "$(RED)[ERROR] echo HelloWorld$(RESET)"; exit 1; } ; \
	LD_PRELOAD=./libft_malloc.so cat main.c || { echo "$(RED)[ERROR] cat main.c$(RESET)"; exit 1; } ; \
	rm -rf prog
	@echo "\n\n$(GREEN)[OK]"

re: fclean all

.PHONY: all clean fclean re link test
