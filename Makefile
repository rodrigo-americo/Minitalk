SERVER  := server
CLIENT  := client
SERVER_BONUS := server_bonus
CLIENT_BONUS := client_bonus
CC          := cc
CFLAGS      := -Wall -Wextra -Werror

OBJ_DIR     := obj

# Fontes
SRCS_SERVER := server.c
SRCS_CLIENT := client.c
SRCS_SERVER_BONUS := server_bonus.c
SRCS_CLIENT_BONUS := client_bonus.c
# Objetos correspondentes
OBJS_SERVER := $(addprefix $(OBJ_DIR)/,$(SRCS_SERVER:.c=.o))
OBJS_CLIENT := $(addprefix $(OBJ_DIR)/,$(SRCS_CLIENT:.c=.o))

OBJS_SERVER_BONUS := $(addprefix $(OBJ_DIR)/,$(SRCS_SERVER_BONUS:.c=.o))
OBJS_CLIENT_BONUS := $(addprefix $(OBJ_DIR)/,$(SRCS_CLIENT_BONUS:.c=.o))
# Regra principal
all: $(SERVER) $(CLIENT)

# Regra para compilar o servidor
$(SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAGS) $(OBJS_SERVER) -o $(SERVER)

# Regra para compilar o cliente
$(CLIENT): $(OBJS_CLIENT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) -o $(CLIENT)

bonus: $(SERVER_BONUS) $(CLIENT_BONUS)

# Regra para compilar o servidor
$(SERVER_BONUS): $(OBJS_SERVER_BONUS)
	$(CC) $(CFLAGS) $(OBJS_SERVER_BONUS) -o $(SERVER_BONUS)

# Regra para compilar o cliente
$(CLIENT_BONUS): $(OBJS_CLIENT_BONUS)
	$(CC) $(CFLAGS) $(OBJS_CLIENT_BONUS) -o $(CLIENT_BONUS)

# Regra genérica para compilar .c em .o
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
# Regras de limpeza
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(SERVER) $(CLIENT) $(SERVER_BONUS) $(CLIENT_BONUS)

re: fclean all

.PHONY: all clean fclean re