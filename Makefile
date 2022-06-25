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
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):  $(INC)/$(INCLUDES) $(OBJS)

	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: clean all
