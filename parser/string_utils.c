#include "cub3d.h"

bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\t');
}

void	ft_free_split(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
