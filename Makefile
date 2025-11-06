NAME    = malloc_T-T
C	    = cc
CFLAG   = -Wall -Werror -Wextra
LFLAG 	= -fsanitize=address -g3
RM      = rm -rf
OBJDIR  = obj
SOURCES = main.c \
		  srcs/malloc/malloc.c srcs/malloc/init.c srcs/malloc/alloc.c \
		  srcs/free/free.c srcs/realloc/realloc.c

OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(C) $(LFLAG) $(CFLAG) -c $< -o $@

$(NAME): $(OBJECTS)
	@$(C) $(LFLAG) $(OBJECTS) -o $(NAME)
	@echo "Compiled V"
	@echo "\nExecute the program with : ./malloc_T-T"

clean : 
	@$(RM) -r $(OBJDIR)  > /dev/null 2>&1

fclean : clean
	@$(RM) -r $(OBJDIR)  > /dev/null 2>&1
	@$(RM) $(NAME)


all : $(NAME)

re: fclean all

.PHONY: clean all re fclean% 