# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cromalde <cromalde@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/27 19:37:16 by cromalde          #+#    #+#              #
#    Updated: 2021/04/03 15:08:05 by cromalde         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#		-*-		Makefile	-*-

PHI_O	=	philo_one
PHI_TW	=	philo_two
PHI_TR	=	philo_three

PO_SRCS	=	ph_one_srcs/ph_one.c \
						ph_one_srcs/utils.c
PO_OBJ	= $(PO_SRCS:.c = .o)
CC 		=	gcc
CFLAG	=	-Wall -Wextra -Werror -pthread
RM		=	rm -rf


.PHONY:		all clean fclean re

%.o = %.c:
		@$(CC) $(CFLAG) -c  $^ -o $@

all:	$(PHI_O) #$(PHI_TW) $(PHI_TR)

$(PHI_O):	$(PO_OBJ)
		@$(CC) $(CFLAG) -o $(PHI_O) $(PO_OBJ) includes/philo_one.h
		@echo "\033[0;32mCreating        $(PHI_O)\033[0;0m"

clean:
	@$(RM) $(PO_OBJ)
	@echo "\033[0;31mCleaning        objs\033[0;0m"

fclean: clean
	@$(RM) $(PHI_O)
	@echo "\033[0;31mRemoving          binaries\033[0;0m"

re: fclean all
