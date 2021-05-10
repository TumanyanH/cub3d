NAME = cub3d
CC = gcc
AR = ar csr
CP = cp
SRCS = main.c \
		utils/cub3d_utils.c \
		utils/parser.c \
		gnl/get_next_line.c \
		utils/get_sprite.c \
		utils/get_pixel.c \
		utils/error.c \
		utils/sprite.c
OBJS = ${SRCS:.c=.o}
COMPILE_FLAGS = -Wall -Wextra -Werror
MLX_FALGS = -Llibs/minilibx_mms -lmlx -framework OpenGL -framework AppKit
MLX_PATH = libs/minilibx_mms/
MLX = libmlx.dylib
LIBFT_PATH = libs/libft/
LIBFT = libft.a
LIBFT_FLAGS = -Llibs/libft -lft

# %.o: %.c
#     $(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

$(NAME) : 	${OBJS}
			${clft} ${cmlx}
			${CC} ${SRCS} ${MLX_FALGS} ${LIBFT_FLAGS} -o ${NAME}
			./cub3d

all : ${NAME}

clean :
	${RM} ${OBJS}

fclean : clean
	${RM} ${NAME}

re : fclean all

clft : 
		@cd $(LIBFT_PATH) && $(MAKE) $(FCLEAN) $(ALL)
		@mv $(MLX) ../../

cmlx : 
		@cd $(MLX_PATH) $(MAKE) $(RE)
		@mv $(LIBFT) ../../


.PHONY: all clean fclean re .c.o
