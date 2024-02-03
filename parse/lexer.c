

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
    // printf("%s\n", cmd->cmd[i]);
}

// bool	check_syntax(char *line)
// {


// }



bool	check_token_syntax(t_info *info)
{
	t_oken	*tokens;

	tokens = info->head;
	while (tokens)
	{
		if (tokens == NULL)
			break ;
		if (tokens->data_type == 1 || tokens->data_type == 2 || tokens->data_type == 3
			|| tokens->data_type == 4 || tokens->data_type == 5)
		{
			if (tokens->next == NULL || tokens->next->data_type != 6)
			{
				printf("syntax error near unexpected token `newline'\n");
				exit(1);
				return (TRUE);
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
		if (tokens->data_type == 5 || tokens->next == NULL)
		{
			break ;
		}
		else if (tokens->data_type == 6)
			count++;
		tokens = tokens->next;
	}
	if (tokens == NULL)
		count++;
	return (count);
}


t_cmd	*lexer(t_info *info)
{
	int		word_count;
	t_cmd	*cmd;
	t_oken	*tokens;
	int		i;

	tokens = info->head;
	word_count = words_before_pipe(tokens) + 1;
	cmd = chad_alloc(sizeof(t_cmd), 1, info->alloc_head);
	cmd->cmd = chad_alloc(sizeof(char *), word_count, info->alloc_head);
	// print_tokens(tokens);
	i = 0;
	while (tokens != NULL)
	{
		// loop until you find a pipe
		// if you find a pipe, create a new cmd
		// add the tokens to the cmd
		// if you find a redirect, add it to the cmd
		if (tokens->data_type == 5)
		{
			// printf("token => %s\n", tokens->token);
			cmd->cmd[i] = NULL;
			cmd->next = chad_alloc(sizeof(t_cmd), 1, info->alloc_head);
			cmd = cmd->next;
			if (tokens->next != NULL)
			{
				word_count = words_before_pipe(tokens) + 1;
				cmd->cmd = chad_alloc(sizeof(char *), word_count,
						info->alloc_head);
			}
			i = 0;
		}
		else if (tokens->data_type == 6)
		{
			cmd->cmd[i] = tokens->token;
		}
		if (tokens->next == NULL)
		{
			cmd->cmd[i + 1] = NULL;
			break ;
		}
		tokens = tokens->next;
		printf("cmd => %s\n", cmd->cmd[i]);
		i++;
		// word_count = words_before_pipe(tokens) + 1;
	}
	printf("cmd => %s\n", cmd->cmd[i]);
	printf("cmd => %s\n", cmd->cmd[i + 1]);
	info->cmd = cmd;
	return (cmd);
}

// t_cmd	*lexer(t_info *info)
// {
// 	int		word_count;
// 	t_cmd	*cmd;
// 	t_oken	*tokens;
// 	int		i;

// 	// check_syntax(info->line);
// 	// if (check_token_syntax(info))
// 	// 	exit(e);

// 	tokens = info->head;
// 	word_count = words_before_pipe(tokens) + 1;
// 	cmd = chad_alloc(sizeof(t_cmd), 1, info->alloc_head);
// 	cmd->cmd = chad_alloc(sizeof(char *), word_count, info->alloc_head);
// 	// print_tokens(tokens);
// 	i = 0;
// 	while (tokens != NULL)
// 	{
// 		// loop until you find a pipe
// 		// if you find a pipe, create a new cmd
// 		// add the tokens to the cmd
// 		// if you find a redirect, add it to the cmd		
// 		if (tokens->data_type == 5)
// 		{
// 			// printf("token => %s\n", tokens->token);
// 			cmd->cmd[i] = NULL;
// 			cmd->next = chad_alloc(sizeof(t_cmd), 1, info->alloc_head);
// 			cmd = cmd->next;
// 			if (tokens->next != NULL)
// 			{
// 				// word_count = words_before_pipe(tokens) + 1;
// 				printf("token => %s\n", tokens->next->token);
// 				word_count = words_before_pipe(tokens->next);
// 				printf("word count => %d\n", word_count);
// 				cmd->cmd = chad_alloc(sizeof(char *), word_count,
// 						info->alloc_head);
// 			}
// 			i = 0;
// 			tokens = tokens->next;
// 		}
// 		else if (tokens->data_type == 6)
// 		{
// 			cmd->cmd[i] = tokens->token;
// 			// printf("cmd[%d] => %s\n", i, cmd->cmd[i]);
// 		}
// 		if (tokens->next == NULL)
// 		{
// 			cmd->cmd[i + 1] = NULL;
// 			break ;
// 		}
// 		// else if (tokens->data_type != 6 && tokens->data_type != 5)
// 		// 	{
// 		// 		//for redir
// 		// 		break;
// 		// 	}
// 			// print_cmd(cmd);
// 		// if (tokens->next == NULL)
// 		// 	break ;
// 			// printf("cmd[%d] => %s\n", i, cmd->cmd[i]);
// 		tokens = tokens->next;
// 		i++;
// 		// word_count = words_before_pipe(tokens) + 1;
// 		// printf("word count => %d\n", word_count);
// 	}
// 	// while (cmd->cmd[i] != NULL)
// 	// {
// 	// 	printf("cmd[%d] => %s\n", i, cmd->cmd[i]);
// 	// 	i++;
// 	// }
// 	// print_all_cmd(cmd);
// 	// info->cmd = cmd;
// 	// free_token(info->head);
// 	return (cmd);
// }

