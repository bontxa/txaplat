NAME = txaplat
SRC_DIR = src
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/cleanUtils.c $(SRC_DIR)/gameUtils.c $(SRC_DIR)/handleBackground.c \
	$(SRC_DIR)/handleCamera.c $(SRC_DIR)/handlePlayer.c $(SRC_DIR)/handleCoins.c $(SRC_DIR)/handleEnemies.c \
	$(SRC_DIR)/handlePlatforms.c $(SRC_DIR)/handlePows.c $(SRC_DIR)/splashPages.c $(SRC_DIR)/getScreenResolution.c
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(SRC_DIR)/%.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(SRC_DIR)/include
RAYLIBFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(RAYLIBFLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME)

.PHONY: all clean fclean re run
