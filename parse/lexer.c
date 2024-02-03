

#include "../inc/minish.h"


bool	is_op(int op)
{
	if (op != 6)
		return (TRUE);
	return (FALSE);
}

int	pipe_count(t_info *info)
{
	t_oken	*tokens;
	int		count;

	tokens = info->head;
	count = 0;
	while (tokens)
	{
		if (tokens->data_type == 5)
			count++;
		tokens = tokens->next;
	}
	return (count + 1);
}

int	redir_count(t_info *info)
{
	t_oken	*tokens;
	int		count;

	tokens = info->head;
	count = 0;
	while (tokens)
	{
		if (tokens->data_type == 2 || tokens->data_type == 3
			|| tokens->data_type == 4)
			count++;
		tokens = tokens->next;
	}
	return (count);
}


void  free_token(t_oken *token) {
  while (token->next != NULL) {
  if (token->token)
    free(token->token);
  free(token);
    token = token->next;
  }
}

void print_cmd(t_cmd *cmd) {
  int i = 0;
  while (cmd->cmd[i] != NULL) {
    printf("cmd token[%d]=>%s\n", i, cmd->cmd[i]);
    i++;
  }
    printf("%s\n", cmd->cmd[i]);
}

// bool	check_syntax(char *line)
// {


// }



bool	check_token_syntax(t_oken *tokens)
{
//	free on exit

	if (tokens->data_type != WORD)
	{
		printf("syntax error near unexpected token `newline'\n");
		exit(1);
		return (TRUE);
	}
	else if (tokens->data_type == PIPE)
	{
		printf("syntax error near unexpected token `|'\n");
		exit(1);
		return (TRUE);
	}
	while (tokens)
	{
		if (tokens == NULL)
			break ;
		if (tokens->data_type == REDIR_IN || tokens->data_type == REDIR_OUT || tokens->data_type == HEREDOC
			|| tokens->data_type == HERESTRING || tokens->data_type == PIPE)
		{
			if (tokens->next == NULL)
			{

				printf("syntax error near unexpected token `newline'\n");
				exit(1);
				return (TRUE);
			}				
			else if (tokens->next->data_type != WORD)
				{
					printf("syntax error near unexpected token `%s'\n", tokens->token);
					exit(1);
				}
		}

		// else if (tokens->data_type == 6)
		// {
		// 	if (tokens->next == NULL || tokens->next->data_type != 6)
		// 	{
		// 		printf("syntax error near unexpected token `newline'\n");
		// 		return (TRUE);
		// 	}
		// }
		tokens = tokens->next;
	}
	return (FALSE);
}
int	words_before_pipe(t_oken *tokens)
{
	int		count;

	// if (info->pipe == NULL)
	// 	tokens = info->pipe;
	count = 0;
	while (tokens)
	{
		if (tokens->data_type == 5 || tokens == NULL)
			return (count);
		else
			count++;
		tokens = tokens->next;
	}
	return (count);
}


t_cmd	*lexer(t_info *info)
{
	int		word_count;
	t_cmd	*cmd;
	t_cmd	*head;
	t_oken	*tokens;
	int		i;

	tokens = info->head;
	check_token_syntax(tokens);
	word_count = words_before_pipe(tokens) + 1;
	printf("word count => %d\n", word_count);
	cmd = chad_alloc(sizeof(t_cmd), 1, info->alloc_head);
	head = cmd;
	cmd->cmd = chad_alloc(sizeof(char *), word_count, info->alloc_head);
	// print_tokens(tokens);
	i = 0;
	while (tokens != NULL)
	{
		// loop until you find a pipe
		// if you find a pipe, create a new cmd
		// add the tokens to the cmd
		// if you find a redirect, add it to the cmd


			// printf("token => %s : type = %s\n", tokens->token, translate(tokens->data_type));

		// if (tokens->data_type != 6 && tokens->data_type != 5)
		// {
		// 	handle_redir(tokens, info);
		// 	tokens = tokens->next;
		// 	continue ;
		// }
		if (tokens->data_type == PIPE)
		{
			cmd->cmd[i] = NULL;
			cmd->next = chad_alloc(sizeof(t_cmd), 1, info->alloc_head);
			cmd = cmd->next;
			word_count = words_before_pipe(tokens->next) + 1;
			cmd->cmd = chad_alloc(sizeof(char *), word_count, info->alloc_head);
			// printf("cmd => %s\n", cmd->cmd[0]);
			tokens = tokens->next;

			i = 0;
		}
		if (tokens->data_type == WORD)
		{
			cmd->cmd[i] = tokens->token;
		}
		if (tokens->next == NULL)
		{
			cmd->cmd[i + 1] = NULL;
			break ;
		}
		tokens = tokens->next;
		i++;
	}
	info->cmd = head;
	return (head);
}

