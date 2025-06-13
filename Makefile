NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./includes -I./libft
LDFLAGS = -L/usr/lib/x86_64-linux-gnu
CPPFLAGS = -I/usr/include/readline

# Préfixes des dossiers
SRCS_DIR = src/
OBJS_DIR = .objets/src/
PARSING_PREFIX = parsing/
BUILTINS_PREFIX = builtins/
INIT_PREFIX = init/
UTILS_PREFIX = utils/
EXECUTOR_PREFIX = executor/
AST_PREFIX = ast/
ENV_PREFIX = env/


# Configuration du garbage collector
GC_DIR = includes/gc/
GC_OBJS_DIR = $(OBJS_DIR)$(GC_DIR)
GC = gc_memory gc_strdup gc_add gc_clean gc_strjoin gc_substr gc_init gc_redir

# Sources avec préfixes
MAIN = main
PARSING = $(addprefix $(PARSING_PREFIX), parser_main parse_utils token_utils tokenizer expansion expansion_utils quotes token_list variable_expansion token_errors)
BUILTINS = $(addprefix $(BUILTINS_PREFIX), cd echo env exit export export_handle export_utils pwd unset)
INIT = $(addprefix $(INIT_PREFIX), init_env init_shell init_utils)
UTILS = $(addprefix $(UTILS_PREFIX), descriptors env_utils bool_utils builtins_utils error_1 error_2 ft_quicksort status save_ft_1 save_ft_2 signals_1 signals_2)
ENV = $(addprefix $(ENV_PREFIX), env_array env_get env_set env_remove)
AST = $(addprefix $(AST_PREFIX), ast_build ast_handle ast_init ast_parse)
EXECUTOR = $(addprefix $(EXECUTOR_PREFIX), execute commands commands_utils heredoc heredoc_process heredoc_utils pipes multi_pipes redirections redir_utils)


# Toutes les sources
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(MAIN) $(PARSING) $(BUILTINS) $(INIT) $(UTILS) $(ENV) $(AST) $(EXECUTOR)))
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(MAIN) $(PARSING) $(BUILTINS) $(INIT) $(UTILS) $(ENV) $(AST) $(EXECUTOR)))
# OBJS = $(SRCS:%.c=$(OBJS_DIR)%.o)

# Objects
GC_SRCS = $(addprefix $(GC_DIR), $(addsuffix .c, $(GC)))
GC_OBJS = $(addprefix $(GC_OBJS_DIR), $(addsuffix .o, $(GC)))

DIR_DUP = mkdir -p $(@D)

# Couleurs pour les messages
GREEN = \033[0;32m
RED = \033[0;31m
NC = \033[0m # No Color

# Rules
all: $(NAME)

$(NAME): $(OBJS) $(GC_OBJS)
	@echo "$(GREEN)Compiling libft...$(NC)"
	@make -C libft
	@echo "$(GREEN)Compiling $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) $(CPPFLAGS) $(OBJS) $(GC_OBJS) -L./libft -lft -lreadline $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(NC)"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@echo "$(GREEN)Compiling $<...$(NC)"
	@$(DIR_DUP)
	@$(CC) $(CFLAGS) $(INCLUDES) $(CPPFLAGS) -O3 -c $< -o $@

$(GC_OBJS_DIR)%.o : $(GC_DIR)%.c
	@$(DIR_DUP)
	@$(CC) $(CFLAGS) $(INCLUDES) $(CPPFLAGS) -O3 -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@make clean -C libft
	@rm -f $(OBJS)
	@rm -f $(GC_OBJS)
	@rm -rf $(OBJS_DIR) $(GC_OBJS_DIR)

fclean: clean
	@echo "$(RED)Cleaning everything...$(NC)"
	@make fclean -C libft
	@rm -f $(NAME)
	@echo "$(RED)Deep clean completed$(NC)"

re: fclean all

# test: all
# 	@echo "$(GREEN)Running tests...$(NC)"
# 	@make -C Test

.PHONY: all clean fclean re test 