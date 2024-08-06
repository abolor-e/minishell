/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:37:49 by abolor-e          #+#    #+#             */
/*   Updated: 2024/08/06 17:46:13 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <sys/wait.h>
# include <string.h>

//Action to take!
# define SHIFT_TO_STACK		0
# define REDUCE_STACK		1
# define ACCEPT				2
# define REJECT				3

# define LINES				100
# define BISON_AUTOMATON	"/syntax_analysis/parsing_table"

# define ERROR -1
# define W 0x0001
# define C 0x00000200
# define A 0x00000008
# define T 0x00000400

typedef struct s_command
{
	char				**args;
	char				*output_file;
	char				*input_file;
	char				*heredoc_content;
	int					append_output;
	char				*delimiter;
	struct s_command	*next;
}	t_command;

typedef struct s_piped
{
	int			**fd;
	int			stdin_cpy;
	int			stdout_cpy;
	char		**env;
	char		**paths;
	pid_t		*pid;
	int			num_cmds;
	t_command	*commands;
}	t_piped;

typedef struct s_table
{
	int	action;
	int	state;
	int	token_type;
	int	next_state;
	int	nb_reduce;
}				t_table;

typedef enum e_rules
{
	R_PIPE_SEQUENCE = 100,
	R_SIMPLE_COMMAND,
	R_CMD_NAME,
	R_CMD_WORD,
	R_CMD_PREFIX,
	R_CMD_SUFFIX,
	R_IO_REDIRECT,
	R_IO_FILE,
	R_FILENAME,
	R_IO_HERE,
	R_HERE_END
}				t_rules;

typedef struct s_stack
{
	int				type;
	int				state;
	int				quote;
	void			*data;
	struct s_stack	*next;
}	t_stack;

typedef enum e_ast_types
{
	A_CMD = 0,
	A_RED_TO,
	A_RED_FROM,
	A_DLESS,
	A_DGREAT,
	A_PIPE,
	A_PARAM,
	A_FILE,
	A_LIMITER
}	t_ast_types;

typedef struct s_tree
{
	struct s_tree	*right;
	struct s_tree	*left;
	struct s_tree	*next;
	void			*data;
	int				type;
	int				reduc;
	int				qt_rm;
}				t_tree;

typedef enum e_token_types
{
	T_END = -2,
	T_WORD = 0,
	T_RED_TO,
	T_RED_FROM,
	T_DLESS,
	T_DGREAT,
	T_PIPE
}			t_ttypes;

typedef struct s_sdQuote
{
	int	single_q;
	int	double_q;
	int	type;
}				t_sdQuote;

typedef struct s_token
{
	int				quote;
	int				type;
	void			*value;
	struct s_token	*next;
}				t_token;

typedef struct s_env
{
	char			*name;
	char			*content;
	int				if_env;
	struct s_env	*next;
}					t_env;

typedef struct s_varcomb
{
	char	*s;
}				t_varcomb;

typedef struct s_varquote
{
	int	a;
	int	i;
	int	qt;
}				t_varquote;

typedef struct s_envb
{
	int		shlvl;
	int		exstatus;
	char	*pwd;
	char	*oldpwd;
	char	**env;
	char	*usr;
}	t_envb;

//Lexical
void		sep_util(char *line, int a, t_sdQuote *sdq);
int			replace_var_util(char *str, int length, char *new, int *i_new);
void		initial(char *new);
t_token		*ft_token(char *line, t_sdQuote sdquote);

void		minishell_loop(t_envb *env, char *pt_path, t_token *input);
void		control_d(void);
void		check_envvar_util(char *new, int *i_new);
void		change_single_env(t_varcomb *vc);

t_token		*ft_lexer(char *line);
void		ft_tokenadd_back(t_token **lst, t_token *new);
int			check_env(t_varcomb vc, char *new, int *i, int *i_new);

char		*token_str(int token_len, char *line);
int			replace_quote(t_varcomb vc, char *new, int *i, int *i_new);
int			sq_dollar(char *str, char sq);
int			replace_double(t_varcomb vc, char *new, int *i_new, t_varquote i);
int			check_envvar(t_varcomb vc, char *new, int *i_new, t_varquote i);
int			replace_var(t_varcomb vc, int index, char *new, int *i_new);
int			replace_var_2(char *new, char *newstr, int *i_new, int len);
int			envvar_len(char *str);
int			s_ck(char *str, int temp, int i, char sd);
int			check_ds(char *str, int a, int i);
int			check_quote(int *i, char *str);
int			quote_count(int *i, char *str, t_sdQuote *quote);
int			quote_type(t_sdQuote *quote);

void		init_sdquote(t_sdQuote *q);
int			sep_to_sep_len(char *line, t_sdQuote *sdq);
int			check_sep(char c);
int			catego_toketype(char *content, int c);
void		*ft_newtoken(void *content, int c);
int			tok_sep_len(char *line, int i);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_itoa(int n);
int			ft_digits(int n);
char		*ft_strdup(const char *s1);
int			ft_strlen(const char *s);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
char		*ft_getenv(char *var);
void		*token_creation(char *line, int *q);

//syntactical!
int			add_syntax_tree(t_tree **syntax_tree,
				t_stack **token_list, int rule);
void	free_line_args(char *line, char **args);
int			build_syntax_tree(t_tree **tree, t_tree *rdc, t_stack **tokens);
void		remove_node_from_list(t_tree **head, t_tree *target_node);
t_tree		*stack_to_node(t_stack *popped);
t_tree		*syntax_analysis(t_token *token, t_table **parsingtable);
t_tree		*fix_parameter_types(t_tree *syntax_tree);
int			reject(void);
int			accept(void);
t_table		*getentry(t_token *token, t_table **parsingtable, t_stack *stack);
t_stack		*init_stack(void);
int			change_stack_state(int next_state, t_stack **stack);
int			reduce_stack(t_table *table_entry,
				t_tree **tree, t_stack **stack, t_table **pt);
int			pro_red_next_state(t_stack *stack, t_table **parsingtable);
int			push_reducted(t_stack **stack, int next);
void		pop_check(t_stack **red, t_stack *stack);
t_table		**ft_init_parsing_table(char *path);
int			ft_create_table_state(int fd, t_table **table);
t_table		*ft_add_table_line(char **arg_line);
void		free_table(t_table **trans);
int			ft_get_next_line(int fd, char **line);
char		**ft_split(const char *s, char c);
char		**ft_free(char **split_array);
int			ft_atoi(const char *str);
char		*ft_substr(char const *s, int start, size_t len);
void		*ft_calloc(size_t count, size_t size);
void		clear_stack(t_stack *stack);
void		parser_cleaning(t_tree **tree,
				t_stack *stack, t_token *input, int ret);
void		clear_tree(t_tree **node);
void		clear_input(t_token *input);

/*EXECUTION*/
int			ast_executor(t_tree *tree, t_envb *env);
int			tree_finder(t_tree *tree, int param, int nb);
int			exec_simple_cmd(t_tree *tree, t_envb *env);
char		*ft_strchr(const char *s, int c);
char		**add_in_tab(char **cmd_tab, char *str_to_add);
int			tab_len(char **cmd_tab);
char		**tab_space_manager(char **cmd_tab, char *space_str);
void		free_tab(char **tab);
int			is_builtin(char *cmd);
char		**get_paths(char **envp);
char		*ft_strjoin(char const *s1, char const *s2);
char		*get_cmd(char **paths, char *cmd);
int			do_redirection(t_tree *ast, int error, t_envb *env);
int			main_pipe(int ac, char **av, t_envb *env);
char		**last_touch(char **tab, int i);
char		**last_touch2(char **tab, int i);
void		check_tab(char **tab);
char		**glue_tab(char **tab, int i);
char		**order_tab(char **tab);
char		**new_tab(void);
char		**init_simple_cmd(t_tree *tree, char **cmd_tab, t_envb *env);
int			creat_pipe(t_piped *piped, t_envb *env, char **av, int num_cmds);
void		init_creat(t_piped *piped, char **envp, int num_cmds, char **av);
void		parse_redirections(t_command *cmd_node, t_envb *env);
void		add_command(t_piped *piped, char *cmd);
t_command	*create_command_node(char *cmd);
void		adj_exec(t_command *cmd_node, t_piped *piped,
				char *cmd, int cmd_index);
void		close_pipe(t_piped *piped);
void		red_deal_out(char *cmd,
				t_command *cmd_node, t_piped *piped, int fd);
void		red_deal_in(char *cmd, t_command *cmd_node, t_piped *piped, int fd);
void		red_dealer(char *cmd, t_command *cmd_node, t_piped *piped);
int			exit_status(int status, t_envb *env);
void		adjust_command_for_tee(t_command *cmd_node);
int			env_uti(char *str);
void		error_handle(char **cmd_tab, int option);
void		free_env(t_envb *env);
void		hd_handler(char *delimiter, t_envb *env);
char		**check_dollar(char **cmd_tab, t_envb *env);
char		*check_path_dollar(char *str, t_envb *env);
int			info_path(char *str);
void		error_handle(char **cmd_tab, int option);
int			open_files(t_command *cmd_node);

/*BUILTINS*/
int			exec_builtin(char **cmd_tab, t_envb *env);
t_envb		*env_init(char **env);
int			env_size(char **env);
int			main_cd(int ac, char **av, t_envb *env);
int			main_echo(int ac, char **av);
int			main_exit(int ac, char **av, t_envb *env);
char		ft_comp(char *s1, char *s2);
void		freetab(char **tab);
void		ft_swap(char **a, char **b);
int			check_args(char *av);
int			main_env(int ac, char **av, t_envb *env);
int			main_export(int ac, char **av, t_envb *env);
int			main_pwd(char **av);
int			main_unset(char **av, t_envb *env);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *s1, const char *s2, size_t len);
int			cd_error(char **av, int nbr);
char		*get_pwd(char *buff);
int			new_env2(t_envb *env, int j, char *str);
void		check_export_utils(char **env);
int			check_stupid(char *tmp, char stupid);
int			check_export(char *str);
int			check_print(char *str);
void		print_all_utils(char **env);
int			trash(t_envb *env);
void		change_old_pwd(t_envb *env, char *buff);
int			change_pwd(t_envb *env, int option);
char		*dollar_parse(char *str, t_envb *env);

/*SIGNALS*/
void		rl_replace_line(const char *text, int clear_undo);
void		sigint_handler(int sig);
void		signal_handlers(void);
void		reset_signal_handlers(void);

#endif
