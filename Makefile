NAME	=	philo
CC		=	@cc
CFLAGS	=	-Wall -Wextra -Werror -pthread -MMD -MP #-g

SRC_DIR	=	src/
INC_DIR	=	inc/
OBJ_DIR	=	obj/
DEP_DIR	=	dep/

SRC 	=	main.c \
			extra.c \
			extra2.c \
			monitor.c \
			philo_extra.c \
			philo.c 
OBJS	=	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))
DEPS	=	$(addprefix $(DEP_DIR), $(SRC:.c=.d))

RESET	= \033[0m
BOLD	= \033[1m
RED		= \033[31m
GREEN	= \033[32m
YELLOW	= \033[33m

all: $(NAME)

INCS := ${addprefix -I,${INC_DIR}}

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) $(DEP_DIR)
	@echo "$(BOLD)$(YELLOW)Creating objs and deps$(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) ${INCS} -c $< -o $@ -MF $(DEP_DIR)$*.d || { echo "$(RED)Failed to create obj/dep$(RESET)"; exit 1; }

$(NAME): $(OBJS)
	@echo "$(BOLD)$(GREEN)DONE$(RESET)"
	@echo "$(BOLD)$(YELLOW)Compiling program$(RESET)"	
	$(CC) $(CFLAGS) ${INCS} $(OBJS) -o $@ || { echo "$(RED)Failed to compile program$(RESET)"; exit 1; }
	@echo "$(BOLD)$(GREEN)Program compiled succesfully$(RESET)"
clean:
	@echo "$(BOLD)$(YELLOW)Deleting objs and deps$(RESET)"
	@rm -rf $(OBJ_DIR) $(DEP_DIR)
	@echo "$(BOLD)$(GREEN)Clean complete$(RESET)"

fclean: clean
	@echo "$(BOLD)$(YELLOW)Deleting all files$(RESET)"	
	@rm -rf $(NAME)
	@echo "$(BOLD)$(GREEN)Full clean complete$(RESET)"

re: fclean all

.PHONY: all re clean fclean

-include ${DEPS}
