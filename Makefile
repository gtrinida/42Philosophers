CC = gcc
RM = rm -f
INC = includes
INCLUDES = philosophers.h
CFLAGS = -Wall -Wextra -Werror -pthread -I$(INC)

NAME = philo

SRCS = srcs/main.c \
		srcs/atoi.c \
		srcs/init.c \
		srcs/philosophers.c \
		srcs/philo_utils.c

OBJS = $(SRCS:%.c=%.o)

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
	@echo "Building: \033[0;34m$<\033[0m"

$(NAME):  $(INC)/$(INCLUDES) $(OBJS)
	@echo "Building: \033[0;34m$>$(LIBFT_ARCHIVE)\033[0m"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Binary \033[0;32m$(NAME)\033[0m successfully linked!"

all: $(NAME)

clean:
	@$(RM) $(OBJS)
	@echo "Cleanup: \033[0;34mobject files\033[0m"

fclean: clean
	@$(RM) $(NAME)
	@echo "Cleanup: \033[0;34mlinked files\033[0m"

re: clean all
