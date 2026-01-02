# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/19 08:54:24 by amezoe            #+#    #+#              #
#    Updated: 2026/01/02 10:35:43 by amezoe           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXECDIR		=	src/execution
PARSEDIR	=	src/parse
SRCSDIR		=	src


EXEC		=	$(EXECDIR)/meth.c $(EXECDIR)/mover.c $(EXECDIR)/textures.c $(EXECDIR)/inits.c $(EXECDIR)/normi_dump.c $(EXECDIR)/mlx_draw.c

PARSE		=	$(PARSEDIR)/basic.c $(PARSEDIR)/init.c $(PARSEDIR)/parse.c \
				$(PARSEDIR)/utils.c $(PARSEDIR)/parse_map.c $(PARSEDIR)/validate.c \
				$(PARSEDIR)/tabs_spaces.c $(PARSEDIR)/free.c $(PARSEDIR)/fake_floodfill.c\

SRCS		=	$(SRCSDIR)/main.c $(EXEC) $(PARSE) \

LIBFTDIR	=	inc/libft
GNLDIR		=	inc/get_next_line
MLXDIR		=	inc/minilibx-linux

LIBS		=	$(GNLDIR)/gnl.a $(LIBFTDIR)/libft.a $(MLXDIR)/libmlx.a

OBJS		=	$(SRCS:.c=.o)

CC			=	@cc
RM			=	@rm -f
CCFLAGS		=	-Wall -Werror -Wextra -Iinclude/mlx -g
MLXFLAGS	=	-L/usr/X11/lib -lX11 -lXext -Llibs/mlx_linux -lm

NAME		=	cub3d

%.o:		%.c
			$(CC) $(CCFLAGS) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS)
			@make -sC $(LIBFTDIR)
			@make -sC $(GNLDIR)
			@make --no-print-directory -sC $(MLXDIR)
			@$(CC) $(CCFLAGS) $(OBJS) $(LIBS) $(MLXFLAGS) -o $(NAME)
			$(SUCCESS)

clean:
			$(RM) $(OBJS)
			@make --no-print-directory -sC $(LIBFTDIR) clean
			@make --no-print-directory -sC $(GNLDIR) clean
			@make --no-print-directory -sC $(MLXDIR) clean
			$(S_OBJS)

fclean:		clean
			$(RM) $(NAME)
			@make --no-print-directory -sC $(LIBFTDIR) fclean
			@make --no-print-directory -sC $(GNLDIR) fclean
			$(RM) $(MLXDIR)/libmlx.a
			$(S_NAME)

re:			fclean all

.PHONY:		all clean fclean re