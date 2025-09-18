# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/13 23:08:55 by gifanell          #+#    #+#              #
#    Updated: 2025/09/18 20:42:24 by gifanell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread

RM = rm -f

#sorgenti
SRCS = main.c \
		init.c \
		routine.c \
		time.c \
		action.c \
		parsing.c \
		monitoring.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	$(MAKE) message

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(OBJS)

re: fclean all

message:

	@echo "(   _   )           \ \                                                           "
	@echo " | | | |  _ __   _   \ \     ___    ____   ___   ______  _ __   ___   ___    ____ "
	@echo " | | | | | '_ \ | |   > \   / _ \  /  ._) / _ \ (  __  )| '_ \ / __) / _ \  /  ._)"
	@echo " | | | | | | | || |  / ^ \ ( (_) )( () ) ( (_) ) | || | | | | |> _) | |_) )( () ) "
	@echo " |_| |_| |_| | | \_)/_/ \_\ \___/  \__/   \___/  |_||_| |_| | |\___)|  __/  \__/  "
	@echo "             | |                                            | |     | |           "
	@echo "             |_|                                            |_|     |_|         \n"
	@echo "È sapiente solo chi sa di non sapere, non chi s'illude di sapere e ignora così    "
	@echo "perfino la sua stessa ignoranza - SOCRATE\n\n                                     "

.PHONY: all clean fclean re
