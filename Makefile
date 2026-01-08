# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/19 08:54:24 by amezoe            #+#    #+#              #
#    Updated: 2026/01/08 13:37:22 by amezoe           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXECDIR		 =	src/execution
BONUSEXECDIR =	src_bonus/exec
BONUSPARSEDIR = src_bonus/parse
PARSEDIR	 =	src/parse
SRCSDIR		 =	src


EXEC		=	$(EXECDIR)/meth.c $(EXECDIR)/mover.c $(EXECDIR)/textures.c $(EXECDIR)/inits.c $(EXECDIR)/normi_dump.c $(EXECDIR)/mlx_draw.c

BONUS_EXEC	=	$(EXECDIR)/meth.c $(BONUSEXECDIR)/mover_bonus.c $(BONUSEXECDIR)/textures_bonus.c $(BONUSEXECDIR)/normi_dump_bonus.c $(BONUSEXECDIR)/inits_bonus.c $(BONUSEXECDIR)/mlx_draw_bonus.c $(BONUSEXECDIR)/minimap_bonus.c $(BONUSEXECDIR)/rotator_bonus.c $(BONUSEXECDIR)/animated_bonus.c


BONUS_PARSE =	$(BONUSPARSEDIR)/basic_bonus.c $(BONUSPARSEDIR)/init_bonus.c $(BONUSPARSEDIR)/parse_bonus.c \
				$(BONUSPARSEDIR)/utils_bonus.c $(BONUSPARSEDIR)/parse_map_bonus.c $(BONUSPARSEDIR)/validate_bonus.c \
				$(BONUSPARSEDIR)/tabs_spaces_bonus.c $(BONUSPARSEDIR)/free_bonus.c $(BONUSPARSEDIR)/fake_floodfill_bonus.c\
				$(BONUSPARSEDIR)/doors_bonus.c

PARSE		=	$(PARSEDIR)/basic.c $(PARSEDIR)/init.c $(PARSEDIR)/parse.c \
				$(PARSEDIR)/utils.c $(PARSEDIR)/parse_map.c $(PARSEDIR)/validate.c \
				$(PARSEDIR)/tabs_spaces.c $(PARSEDIR)/free.c $(PARSEDIR)/fake_floodfill.c\


SRCS		=	$(SRCSDIR)/main.c $(EXEC) $(PARSE)
SRCS_BONUS	=	$(BONUSEXECDIR)/main_bonus.c $(BONUS_EXEC) $(BONUS_PARSE)
				
				


LIBFTDIR	=	inc/libft
GNLDIR		=	inc/get_next_line
MLXDIR		=	inc/minilibx-linux

LIBS		=	$(GNLDIR)/gnl.a $(LIBFTDIR)/libft.a $(MLXDIR)/libmlx.a

OBJS		=	$(SRCS:.c=.o)

OBJS_BONUS	=	$(SRCS_BONUS:.c=.o)

CC			=	@cc
RM			=	@rm -f
CCFLAGS		=	-Wall -Werror -Wextra -Iinclude/mlx -g
MLXFLAGS	=	-L/usr/X11/lib -lX11 -lXext -Llibs/mlx_linux -lm

NAME		=	cub3d
BONUS		=	cub3d_bonus

%.o:		%.c
			$(CC) $(CCFLAGS) -c $< -o $@

all:		$(NAME)

bonus:		$(BONUS)

$(NAME):	$(OBJS)
			@make -sC $(LIBFTDIR)
			@make -sC $(GNLDIR)
			@make --no-print-directory -sC $(MLXDIR)
			@$(CC) $(CCFLAGS) $(OBJS) $(LIBS) $(MLXFLAGS) -o $(NAME)
			$(SUCCESS)

$(BONUS):	$(OBJS_BONUS)
			@make -sC $(LIBFTDIR)
			@make -sC $(GNLDIR)
			@make --no-print-directory -sC $(MLXDIR)
			@$(CC) $(CCFLAGS) $(OBJS_BONUS) $(LIBS) $(MLXFLAGS) -o $(BONUS)
			$(SUCCESS)
			
clean:
			$(RM) $(OBJS) $(OBJS_BONUS)
			@make --no-print-directory -sC $(LIBFTDIR) clean
			@make --no-print-directory -sC $(GNLDIR) clean
			@make --no-print-directory -sC $(MLXDIR) clean
			$(S_OBJS)

fclean:		clean
			$(RM) $(NAME) $(BONUS)
			@make --no-print-directory -sC $(LIBFTDIR) fclean
			@make --no-print-directory -sC $(GNLDIR) fclean
			$(RM) $(MLXDIR)/libmlx.a
			$(S_NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus