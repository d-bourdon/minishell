#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: dbourdon <dbourdon@student.42.fr>          +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2016/06/15 14:15:13 by dbourdon          #+#    #+#             *#
#*   Updated: 2016/06/15 14:15:21 by dbourdon         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME = minishell

SRC = 	cd.c\
		cd2.c\
		dec_commande.c\
		env.c\
		env2.c\
		env3.c\
		ft_erreur.c\
		ft_exit.c\
		ft_islink.c\
		ft_lstaddend.c\
		main.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

.PHONY: clean fclean re libft norme

all: $(NAME)

$(NAME) : libft $(OBG)
	@clang $(FLAGS) $(SRC) -g -o $(NAME) -L./libft/ -lft
	@echo "Compilation"

libft:
	@make -C libft/

clean: 
	@make -C libft/ clean
	@rm -f $(OBJ) *.gch
	@echo "Supression"

fclean: clean
	@rm -f $(NAME)
	@make -C libft/ fclean
	@echo "totale..."

re: fclean all
	@make re -C libft/

norme:
	@norminette *.[ch] ./libft/*.[ch]
