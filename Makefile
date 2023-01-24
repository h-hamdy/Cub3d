CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -g -fsanitize=address

NAME	=	cub3D

LIBFT	=	libft/libft.a

SRCS	=	main.c \
			get_next_line/get_next_line.c \
			parsing/cub3d_utils.c \
			parsing/get_data.c \
			parsing/parsing.c \
			parsing/parsing_utils.c \
			parsing/parsing_utils1.c \
			parsing/floor_and_ceil.c \
			parsing/map_tools.c \
			raycasting/raycasting.c \
			raycasting/horizontal_ray.c \
			raycasting/vertical_ray.c \
			dependencies/game_rendring.c \
			dependencies/count_distance.c \
			dependencies/game_setup.c \
			dependencies/game_utils.c \
			event_handling/event_handling.c \
			3d_projection/render_3d.c \

MINILIBX = minilibx/libmlx.a

all:	$(NAME)

$(NAME):	$(LIBFT) $(SRCS) $(MINILIBX)
	@ $(CC) $(CFLAGS) $(SRCS) -o $(NAME) $(LIBFT) $(MINILIBX) -L /usr/local/lib -I minilibx -lmlx -framework OpenGl -framework Appkit
	@ echo "\n\033[1;32mCub3D has been compiled!\033[0m\n"

$(MINILIBX):
	make -c minilibx &> /dev/null

$(LIBFT):
	@ make -C libft > /dev/null
	@ make -C minilibx > /dev/null
	@ make bonus -C libft > /dev/null

clean:
	@make clean -C libft

fclean:	clean
	@rm -rf libft/libft.a
	@rm -rf $(NAME)

re: fclean all

.PHONY:	all clean fclean re§