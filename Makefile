# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cromalde <cromalde@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/27 19:37:16 by cromalde          #+#    #+#              #
#    Updated: 2021/04/05 16:42:32 by cromalde         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#		-*-		Makefile	-*-

PHI_O	=	philo_one
PHI_TW	=	philo_two
PHI_TR	=	philo_three

PO_SRCS	=	ph_one_srcs/ph_one.c ph_one_srcs/utils_one.c
PW_SRCS	=	ph_one_srcs/ph_two.c ph_one_srcs/utils_two.c
PT_SRCS	=	ph_one_srcs/ph_three.c ph_one_srcs/utils_three.c

PO_OBJ	= $(PO_SRCS:.c=.o)
PW_OBJ = $(PW_SRCS:.c=.o)
PT_OBJ = $(PT_SRCS:.c=.o)

O_INC	= includes/philo_one.h
W_INC	= includes/philo_two.h
T_INC	= includes/philo_three.h
CC 		=	gcc
CFLAG	=	-Wall -Wextra -Werror -pthread -g
RM		=	rm -rf

.PHONY:		all clean fclean re

all:	$(PHI_O) $(PHI_TW) $(PHI_TR)

%.o:%.c
		@$(CC) -c $(CFLAG) $^ -o $@

$(PHI_O):	$(PO_OBJ)
		@$(CC) -o $(PHI_O) $(CFLAG) $(PO_OBJ)
		@echo "\033[0;32mCreating        $(PHI_O)\033[0;0m"

$(PHI_TW):	$(PW_OBJ)
		@$(CC) -o $(PHI_TW) $(CFLAG) $(PW_OBJ)
		@echo "\033[0;32mCreating        $(PHI_TW)\033[0;0m"

$(PHI_TR):	$(PT_OBJ)
		@$(CC) -o $(PHI_TR) $(CFLAG) $(PT_OBJ)
		@echo "\033[0;32mCreating        $(PHI_TR)\033[0;0m"

clean:
	@$(RM) $(PO_OBJ) $(PW_OBJ) $(PT_OBJ)
	@echo "\033[0;31mCleaning        objs\033[0;0m"

fclean: clean
	@$(RM) $(PHI_O) $(PHI_TW) $(PHI_TR)
	@echo "\033[0;31mRemoving          binaries\033[0;0m"

re: fclean all
