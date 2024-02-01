

#include "../inc/minish.h"


bool	is_op(int op)
{
	if (op == PIPE || op == REDIR_OUT || op == REDIR_IN)
		return (TRUE);
	return (FALSE);

}

t_cmd *lexer(t_oken *head, info *info)
{
	t_cmd *cmd = chad_alloc(sizeof(t_cmd), 1, info->alloc_head);
	t_oken *iter = head;
	int i = 0;
	while (iter)
	{
		if (iter->data_type == OPERATOR)
		{
			cmd->operator[i] = iter->token;
			i++;
		}
		else if (iter->data_type == WORD)
		{
			cmd->word[i] = iter->token;
			i++;
		}
		iter = iter->next;
	}
	return (cmd);
}
