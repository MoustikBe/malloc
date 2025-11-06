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
		  srcs/free/free.c srcs/realloc/realloc.c
OBJECTS	= $(SOURCES:%.c=$(OBJDIR)/%.o)

all: $(NAME) link

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled $<"

$(NAME): $(OBJECTS)
	@$(CC) $(LFLAGS) $(OBJECTS) -o $(NAME)
	@echo "✅ Created $(NAME)"

link:
	@ln -sf $(NAME) $(LINK)
	@echo "🔗 Created symbolic link: $(LINK) -> $(NAME)"

clean:
	@$(RM) $(OBJDIR)
	@echo "🧹 Object files removed"

fclean: clean
	@$(RM) $(NAME) $(LINK)
	@echo "🗑️  Removed binary and link"

re: fclean all

.PHONY: all clean fclean re link
