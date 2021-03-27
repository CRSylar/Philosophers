# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cromalde <cromalde@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/27 19:37:16 by cromalde          #+#    #+#              #
#    Updated: 2021/03/27 19:54:04 by cromalde         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#		-*-		Makefile	-*-

PHI_O	=	philo_one
PHI_TW	=	philo_two
PHI_TR	=	philo_three

CC 		=	gcc
CFLAG	=	-Wall -Wextra -Werror -pthread
RM		=	rm -rf


.PHONY:		all clean fclean re

%.o = %.c:

all:	$(PHI_O) #$(PHI_TW) $(PHI_TR)

clean:
	$(RM) 

fclean: clean
	$(RM)

re: fclean all
