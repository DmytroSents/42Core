typedef struct    s_list
{
    struct s_list *next;
    void          *data;
}                 t_list;

#include <unistd.h>

int	ft_list_size(t_list *begin_list)
{
	int amount = 0;
	t_list *tmp = NULL;

	while (tmp)
	{	tmp = tmp->next;	amount++; }
	return (amount);
}

