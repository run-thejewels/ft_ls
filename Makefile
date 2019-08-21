NAME = ft_ls

INC_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./obj

LIB_DIR = ./lib/libft
LIB_NAME = $(LIB_DIR)/libft.a
LIB_INC_DIR = ./lib/libft/include

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(LIBS) $(OBJ_DIR) $(OBJS)
	@make -C $(LIB_DIR)
	@gcc $(OBJS) $(LIB_NAME) -o $(NAME)


$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@gcc -Wall -Wextra -Werror -I $(INC_DIR) -I $(LIB_INC_DIR) -o $@ -c $<

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean $(NAME)

libfclean:
	@make -C $(LIB_DIR) fclean

libre:
	@make -C $(LIB_DIR) re

