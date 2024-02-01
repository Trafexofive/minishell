

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

int	words_before_pipe(t_info *info)
{
	t_oken	*tokens;
	int		count;

	tokens = info->head;
	count = 0;
	while (tokens)
	{
		if (tokens->data_type == 5)
			break ;
		if (tokens->data_type == 6)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

t_cmd	*lexer(t_info *info)
{
	int		word_count;
	t_cmd	*cmd;
	t_oken	*tokens;
	int		i;

	word_count = words_before_pipe(info) + 1;
	cmd = chad_alloc(sizeof(t_cmd), 1, info->alloc_head);
	cmd->cmd = chad_alloc(sizeof(char *), word_count, info->alloc_head);
	tokens = info->head;
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
				word_count = words_before_pipe(info) + 1;
				cmd->cmd = chad_alloc(sizeof(char *), word_count,
						info->alloc_head);
			}
			i = 0;
		}
		else
		{
			cmd->cmd[i] = tokens->token;
		}
		if (tokens->next == NULL)
			break ;
		tokens = tokens->next;
		printf("cmd => %s\n", cmd->cmd[i]);
		i++;
		word_count = words_before_pipe(info) + 1;
	}
	info->cmd = cmd;
	return (cmd);
}

// bool	errors(t_info *info)
// {
// 	t_oken *tokens = info->head;
// 	while (tokens)
// 	{
// 		if (tokens->data_type == 1)
// 		{
// 			if (tokens->next == NULL || tokens->next->data_type != 6)
// 			{
// 				printf("syntax error near unexpected token `newline'\n");
// 				return (TRUE);
// 			}
// 		}
// 		else if (tokens->data_type == 2)
// 		{
// 			if (tokens->next == NULL || tokens->next->data_type != 6)
// 			{
// 				printf("syntax error near unexpected token `newline'\n");
// 				return (TRUE);
// 			}
// 		}
// 		else if (tokens->data_type == 3)
// 		{
// 			if (tokens->next == NULL || tokens->next->data_type != 6)
// 			{
// 				printf("syntax error near unexpected token `newline'\n");
// 				return (TRUE);
// 			}
// 		}
// 		else if (tokens->data_type == 4)
// 		{
// 			if (tokens->next == NULL || tokens->next->data_type != 6)
// 			{
// 				printf("syntax error near unexpected token `newline'\n");
// 				return (TRUE);
// 			}
// 		}
// 		else if (tokens->data_type == 5)
// 		{
// 			if (tokens->next == NULL || tokens->next->data_type != 6)
// 			{
// 				printf("syntax error near unexpected token `newline'\n");
// 				return (TRUE);
// 			}
// 		}
// 		else if (tokens->data_type == 6)
// 		{
// 			if (tokens->next == NULL || tokens->next->data_type != 6)
// 			{
// 				printf("syntax error near unexpected token `newline'\n");
// 				return (TRUE);
// 			}
// 		}
// 		tokens = tokens->next;
// 	}
// 	return (FALSE);
// }

// untested