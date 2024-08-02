NAME 		= minishell
CC 			= gcc
CFLAGS 		= -Wall -Wextra -Werror -g3 -g -fsanitize=address 
RDLN_FLAG	= -L/Users/$(whoami)/.brew/opt/readline/lib -I/Users/$(whoami)/.brew/opt/readline/include -lreadline
MLXFLAGS	= -L ./minilibx -lmlx -framework OpenGl -framework Appkit

RED			= \033[1;31m
BLUE		= \033[1;34m
RESET		= \033[0m

SRC			= execution/builtins/cd.c	\
			  execution/builtins/echo.c	\
			  execution/builtins/env.c	\
			  execution/builtins/exit.c	\
			  execution/builtins/export.c	\
			  execution/builtins/export_utils.c	\
			  execution/builtins/ft_strncmp.c	\
			  execution/builtins/ft_strnstr.c	\
			  execution/builtins/pwd.c	\
			  execution/builtins/unset.c	\
			  execution/utils/ft_strjoin.c	\
			  execution/utils/utils_simple_cmd.c	\
			  execution/utils/utils_simple_cmd2.c	\
			  execution/env_init.c	\
			  execution/main_executor.c	\
			  execution/pipe_exec.c	\
			  execution/redirection_handler.c	\
			  execution/simple_cmd.c	\
			  lexycal_analysis/lexer.c	\
			  lexycal_analysis/list.c	\
			  lexycal_analysis/quote_utils.c	\
			  lexycal_analysis/replace_quote.c	\
			  lexycal_analysis/utils1.c	\
			  lexycal_analysis/utils2.c	\
			  lexycal_analysis/utils3.c	\
			  lexycal_analysis/utils7.c	\
			  syntax_analysis/get_next_line.c	\
			  syntax_analysis/get_next_line_utils.c	\
			  syntax_analysis/parsing_table.c	\
			  syntax_analysis/stack1.c	\
			  syntax_analysis/stack2.c	\
			  syntax_analysis/syntax.c	\
			  syntax_analysis/tree.c	\
			  syntax_analysis/utils4.c	\
			  syntax_analysis/utils5.c	\
			  syntax_analysis/utils6.c	\
			  signals.c	\
			  main.c

OBJ = $(SRC:.c=.o)

all: cute ${NAME}

${NAME}: $(OBJ)
		@echo "$(BLUE)███████████████████████ Making minishell ███████████████████████$(RESET)"
		$(MAKE) --no-print-directory -C
		$(CC) $(CFLAGS) $(RDLN_FLAG) -lm $(SRC) -o $(NAME)
		@echo "$(BLUE)███████████████████████ Compiling is DONE ██████████████████████$(RESET)"

clean:
		@echo "$(RED)deleting object files$(RESET)
		@rm -rf $(OBJ)

fclean: clean
		@echo "$(RED)deleting MINIHELL$(RESET)
		@rm -rf $(NAME) $(OBJ)

re: fclean all

.PHONY: all clean fclean re

cute:
	@echo "███╗   ███╗██╗███╗   ██╗██╗   ██╗  ██╗███████╗██╗     ██╗     "
	@echo "████╗ ████║██║████╗  ██║██║   ██║  ██║██╔════╝██║     ██║     "
	@echo "██╔████╔██║██║██╔██╗ ██║██║   ███████║█████╗  ██║     ██║     "
	@echo "██║╚██╔╝██║██║██║╚██╗██║██║   ██╔══██║██╔══╝  ██║     ██║     "
	@echo "██║ ╚═╝ ██║██║██║ ╚████║██║   ██║  ██║███████╗███████╗███████╗"
	@echo "╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝   ╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"
	@echo "         Made by : \033[1;91mabolor-e\033[m and \033[1;91molmarech\033[m"