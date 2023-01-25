CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror #-g -fsanitize=address

NAME	=	cub3D

LIBFT	=	libft/libft.a

SRCS	=	main.c \
			srcs/get_next_line/get_next_line.c \
			srcs/parsing/cub3d_utils.c \
			srcs/parsing/get_data.c \
			srcs/parsing/parsing.c \
			srcs/parsing/parsing_utils.c \
			srcs/parsing/parsing_utils1.c \
			srcs/parsing/floor_and_ceil.c \
			srcs/parsing/map_tools.c \
			srcs/raycasting/raycasting.c \
			srcs/raycasting/horizontal_ray.c \
			srcs/raycasting/vertical_ray.c \
			srcs/dependencies/game_rendring.c \
			srcs/dependencies/count_distance.c \
			srcs/dependencies/game_setup.c \
			srcs/dependencies/game_utils.c \
			srcs/event_handling/event_handling.c \
			srcs/3d_projection/render_3d.c \

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