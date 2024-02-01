

#include "../inc/minish.h"


bool	is_op(int op)
{
	if (op != 6)
		return (TRUE);
	return (FALSE);
}

int 	pipe_count(t_info *info)
{
	t_oken *tokens = info->head;
	int count = 0;
	while (tokens)
	{
		if (tokens->data_type == 5)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

t_cmd *lexer(t_info *info)
{
	int pipe_c = pipe_count(info);
	t_cmd *cmd = chad_alloc(sizeof(t_cmd), 1, info->alloc_head);

	cmd->cmd = chad_alloc(sizeof(char *), pipe_c, info->alloc_head);
	t_oken *tokens = info->head;
	int i = 0;
	while (tokens)
	{
		//loop until you find a pipe
		//if you find a pipe, create a new cmd
		//add the tokens to the cmd
		//if you find a redirect, add it to the cmd
		if (tokens == NULL)
			break;
		cmd->cmd[i] = tokens->token;
		if (tokens->data_type == 5)
		{
			cmd->cmd[i] = NULL;
			cmd->next = chad_alloc(sizeof(t_cmd), 1, info->alloc_head);
			cmd = cmd->next;
			i = 0;
		}
		i++;
		tokens = tokens->next;
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

//untested