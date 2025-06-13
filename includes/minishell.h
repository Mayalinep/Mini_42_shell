/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:44:52 by mpelage           #+#    #+#             */
/*   Updated: 2025/06/10 20:46:59 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L

# include "../libft/libft.h"
# include "gc/gc.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

/* Constantes */
# define PROMPT "minishell$ "
# define MAX_PATH 4096
# define MAX_ARGS 1024
# define ERROR 0
# define SUCCESS 1
# define ERROR_SYNTAX 2

/* ==============================================
   STRUCTURES DE DONNÉES
   ============================================== */

typedef struct s_list_redir
{
	void				*content;
	struct s_list_redir	*next;
}						t_list_redir;

typedef struct s_pipe_data
{
	int					pipe_fd[2];
	pid_t				pid_left;
	pid_t				pid_right;
	int					status;
}						t_pipe_data;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_COMMAND,
	TOKEN_BUILTIN,
	TOKEN_ARG,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_FILENAME,
	TOKEN_HEREDOC,
	TOKEN_LIMITER,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_BACKGROUND,
	TOKEN_PAREN_OPEN,
	TOKEN_PAREN_CLOSE
}						t_token_type;

typedef struct s_quote_state
{
	int					in_single_quote;
	int					in_double_quote;
}						t_quote_state;

typedef struct s_saved_fds
{
	int					saved_stdin;
	int					saved_stdout;
	int					saved_stderr;
}						t_saved_fds;

typedef struct s_token
{
	char				*value;
	t_token_type		type;
	int					quote_type;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_ast
{
	t_token_type		type;
	char				*value;
	char				**args;
	bool				is_simple;
	bool				is_double;
	struct s_ast		*left;
	struct s_ast		*right;
	struct s_ast		*next;
}						t_ast;

typedef struct s_shell
{
	t_token				*token_list;
	t_ast				*ast_root;
	t_env				*env;
	t_quote_state		quotes;
	char				*input;
	int					saved_stdin;
	int					saved_stdout;
	int					saved_stderr;
	int					exit_status;
	int					is_running;
	int					signal_status;
	t_gc				*gc;
}						t_shell;

/* ==============================================
	VARIABLES GLOBALES
	============================================== */

extern int				g_signal_pid;
/* ==============================================
	FONCTIONS D'INITIALISATION
	============================================== */

int						init_shell(t_shell *shell, char **env);
int						init_env(t_shell *shell, char **env);
int						init_empty_env(t_shell *shell);
void					cleanup_shell(t_shell *shell);

/* ==============================================
	FONCTIONS ENVIRONNEMENT
	============================================== */

t_env					*create_env_node(char *env_var);
int						add_env_node(t_env **env, t_env *new_node);
int						add_env_var(t_env **env, t_env *new);
void					free_env(t_env *env);
char					*get_env_value(t_env *env, char *key);
int						set_env_value(t_env **env, char *key, char *value);
int						modify_env_value(t_env *current, char *value);
int						remove_env_var(t_env **env, char *key);
char					**env_to_array(t_env *env);
void					free_env_array(char **env_array);
int						is_env_exist(t_env *env, char *key);

/* ==============================================
	FONCTIONS DE GESTION DES SIGNAUX
	============================================== */

void					clear_rl_line(void);
void					signals(void);
void					setup_heredoc_signals(void);

/* ==============================================
	FONCTIONS DE PARSING
	============================================== */

int						parse_command(t_shell *shell);
char					*handle_quotes(char *str);
int						get_quote_type_at_position(char *original_cmd,
							int position);
int						check_unclosed_quotes(char *command);
int						get_quote_type(char *value);
int						expand_variables(t_shell *shell, char **line);
int						add_char(char **str, char c);
int						handle_exit_status(t_shell *shell, int status);
char					**split_pipes(char *str);
int						tokenize_command(t_shell *shell, char *command,
							char *original_cmd);
void					free_tokens(t_token *token_list);
void					cleanup_tokens_only(t_shell *shell);
int						is_special(char *str, char *original_cmd, int position);
int						add_token_to_list(t_token **list, t_token *new_token);
int						print_token_error(t_token_type type);
char					*get_token_str(t_token_type type);
int						check_token_syntax_error(char *str);
int						check_control_operators(t_token *token_list);
int						check_redirections(t_token *token_list);
int						check_parentheses(t_token *token_list);
int						append_token(t_token **list, char *value, int type);
void					copy_token(char *command, int length, char *str);

/* Fonctions d'expansion des variables */
int						handle_special_var(t_shell *shell, char *line, int *i,
							char **new_str);
int						handle_normal_var(t_shell *shell, char *line, int *i,
							char **new_str);
int						handle_variable_expansion(t_shell *shell, char *line,
							int *i, char **new_str);
int						add_expanded_var(t_shell *shell, char *var_name,
							char **new_str);

/* ==============================================
	FONCTIONS DE CONSTRUCTION AST
	============================================== */

t_ast					*build_ast(t_shell *shell);
t_ast					*build_ast_recursive(t_gc *gc, t_token **tokens);
t_ast					*build_command_node(t_gc *gc, t_token **tokens,
							t_ast *left_node);
t_ast					*build_builtin_node(t_gc *gc, t_token **tokens,
							t_ast *left_node);
t_ast					*parse_logical_op(t_gc *gc, t_token **tokens);
t_ast					*parse_pipeline(t_gc *gc, t_token **tokens);
t_ast					*parse_redirection(t_gc *gc, t_token **tokens);
t_ast					*parse_command_ast(t_gc *gc, t_token **tokens);
t_ast					*parse_parentheses(t_gc *gc, t_token **tokens);

/* Fonctions de manipulMakefileation des nœuds AST */
t_ast					*create_ast_node(t_gc *gc, t_token_type type,
							char *value);
void					add_command_arg(t_gc *gc, t_ast *node, char *arg);
void					add_builtin_arg(t_gc *gc, t_ast *node, char *arg);
t_ast					*handle_logical_operator(t_gc *gc, t_token **tokens,
							t_ast *left_node, t_token *current);
t_ast					*handle_pipe_operator(t_gc *gc, t_token **tokens,
							t_ast *left_node, t_token *current);
t_ast					*handle_redirection(t_gc *gc, t_token **tokens,
							t_ast *left_node, t_token *current);
t_ast					*handle_file_redirection(t_gc *gc, t_token **tokens,
							t_ast *node);
t_ast					*handle_heredoc_redirection(t_gc *gc, t_token **tokens,
							t_ast *node);

/* ==============================================
	FONCTIONS D'EXÉCUTION PRINCIPALES
	============================================== */

int						execute_shell(t_shell *shell);
int						execute_ast(t_shell *shell, t_ast *node,
							bool child_process);
int						execute_parenthesis(t_shell *shell, t_ast *node);

/* ==============================================
	FONCTIONS DE COMMANDES
	============================================== */

int						execute_command(t_shell *shell, t_ast *node,
							bool child_process);
int						execute_command_child(t_shell *shell, t_ast *ast);
int						execute_command_extern(t_shell *shell, t_ast *ast,
							bool child_process);
int						execute_external(t_shell *shell, char **args);
char					*find_command_path(t_shell *shell, char *cmd);

/* ==============================================
	FONCTIONS BUILTIN
	============================================== */

/* Exécution des builtins */
int						execute_builtin(t_shell *shell, t_ast *node);
int						exec_builtin(t_shell *shell, char **args);

/* Commandes builtin individuelles */
int						builtin_echo(t_shell *shell, t_ast *ast);
int						builtin_cd(t_shell *shell, t_ast *ast);
int						builtin_pwd(t_shell *shell, t_ast *ast);
int						builtin_export(t_shell *shell, t_ast *ast);
int						builtin_unset(t_shell *shell, t_ast *ast);
int						builtin_env(t_shell *shell, t_ast *ast);
int						builtin_exit(t_shell *shell, t_ast *ast);

/* Fonctions d'aide aux builtins */

int						update_pwd(char *oldpath, t_shell *shell);
int						change_directory(char *old_pwd, char *path);
int						is_same_char(const char *str, const char cmp);
char					*find_command_path(t_shell *shell, char *command);

/* Fonctions Export */
int						display_export_vars(t_shell *shell);
char					**value_to_args(t_gc *gc, char *value);
int						process_export_arg(t_shell *shell, char **args);
char					**handle_with_equal(t_gc *gc, char *value,
							char *equal_pos);
char					**handle_no_equal(t_gc *gc, char *value);
int						handle_key_arg(t_shell *shell, char **args);
int						handle_with_plus(t_shell *shell, char *key,
							char *value);
int						is_valid_key(char **args);

/* ==============================================
	FONCTIONS DE REDIRECTION
	============================================== */

int						execute_redirection(t_shell *shell, t_ast *node);
int						execute_multiple_redirections(t_shell *shell,
							t_ast *ast);
void					add_to_list(t_list_redir **list, void *content);
bool					collect_redirections(t_shell *shell, t_ast *ast,
							t_ast **cmd_node, t_list_redir **redirs);
void					restore_all_redirections(t_list_redir *redirs);
int						apply_redir_heredocs(t_shell *shell, t_ast *ast);

/* ==============================================
	FONCTIONS DE PIPES
	============================================== */

int						execute_pipeline(t_shell *shell, t_ast *node);
int						execute_multiple_pipes(t_shell *shell, t_ast *ast);
int						execute_pipe(t_shell *shell, t_ast *ast);

/* ==============================================
	FONCTIONS HEREDOC
	============================================== */

int						execute_heredoc(t_shell *shell, t_ast *node);
int						process_single_heredoc(t_shell *shell, char *delimiter);
int						process_heredoc_line(int write_fd, char *delimiter);
void					heredoc_child_process(int pipe_fd[2], char *delimiter);
pid_t					create_heredoc_child(int pipe_fd[2], char *delimiter);
char					**collect_heredoc_delimiters(t_shell *shell, t_ast *ast,
							int *count);
int						count_heredocs(t_ast *ast);
void					fill_delimiters(char **delimiters, t_ast *ast,
							int count);
t_ast					*find_command_after_heredocs(t_ast *ast);
int						setup_heredoc_redirection(t_shell *shell, int read_fd);
int						execute_with_heredoc(t_shell *shell, t_ast *ast,
							int read_fd);
int						process_heredocs_loop(t_shell *shell, char **delimiters,
							int count);

/* ==============================================
	FONCTIONS OPÉRATEURS LOGIQUES
	============================================== */

int						execute_op(t_shell *shell, t_ast *node);
int						execute_or(t_shell *shell, t_ast *node);
int						execute_and(t_shell *shell, t_ast *node);

/* ==============================================
	FONCTIONS UTILITAIRES D'EXÉCUTION
	============================================== */

bool					is_builtins(char *cmd);
bool					is_redir(t_token_type type);
bool					is_op(t_token_type type);

/* ==============================================
	FONCTIONS DE GESTION DES DESCRIPTEURS
	============================================== */

int						save_descriptor(int fd);
int						save_all_descriptors(t_saved_fds *saved);
int						restore_descriptor(int saved_fd, int target_fd);
int						restore_all_descriptors(t_saved_fds *saved);
void					save_close(int *fd);
void					save_close_pipe_fds(t_pipe_data *data);
int						save_open(t_shell *shell, char *filename, int flags,
							mode_t mode);
int						save_getcwd(char **buffer, char *cmd_name);
int						save_access(char *path, int type, char *cmd_name);
int						save_stat(char *path, char *cmd_name);
pid_t					safe_fork(t_shell *shell);

/* ==============================================
	FONCTIONS UTILITAIRES GÉNÉRALES
	============================================== */

int						is_directory(char *path, char *cmd_name);
int						is_file(char *path);
int						is_symlink(char *path, char *cmd_name);
int						is_same_char(const char *str, const char cmp);
void					ft_quicksort(t_env *arr[], int low, int high);
int						count_env_vars(t_env *env);
t_env					**create_arr_list(t_env *env, t_gc *gc);
int						open_output_file(t_shell *shell, t_ast *ast);
int						open_input_file(t_shell *shell, t_ast *ast);

/* ==============================================
	FONCTIONS DE GESTION D'ERREUR
	============================================== */

int						print_errno(char *cmd_name, char *path,
							int force_errno);
void					error_invalid_option(char *cmd, char *key, char *str);
void					error_invalid_identifier(char *cmd, char *key);
void					print_error(bool prefix, char *cmd_name, char *path,
							char *str);
int						handle_child_exit(int status, t_shell *shell);
char					*free_s(char *s);
int						handle_invalid_arg(t_shell *shell);
int						handle_fork_error(t_pipe_data *data);

/* ==============================================
	FONCTIONS DE DÉBOGAGE
	============================================== */

void					print_ast(t_ast *root);
void					print_ast_tree(t_ast *node, char *prefix, int is_last,
							char *role);
void					print_ast_node(t_ast *node, int depth);
/* ==============================================
	FONCTIONS DE GESTION DES SIGNAUX
	============================================== */

int						handle_parent_process(t_shell *shell, pid_t pid);
int						handle_heredoc_signals(int status, t_shell *shell,
							int pipe_fd);
void					setup_child_signals(void);
void					handle_sigquit(int sig);
void					setup_signals(void);

#endif
