#include "list.h"

t_list	*sort_list(t_list *lst, int (*cmp)(int, int))
{
	int			temp;
	t_list		*tmplst;
	t_list		*start;

	start = lst;
	tmplst = lst;
	if (!lst)
		return (lst);
	temp = lst->content;
	while (lst)
	{
		while (tmplst)
		{
			if (!cmp(lst->content, tmplst->content))
			{
				temp = lst->content;
				lst->content = tmplst->content;
				tmplst->content = temp;
			}
			tmplst = tmplst->next;
		}
		lst = lst->next;
		tmplst = lst;
	}
	return (start);
}