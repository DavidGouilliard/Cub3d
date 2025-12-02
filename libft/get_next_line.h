/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 05:50:34 by dagouill          #+#    #+#             */
/*   Updated: 2024/12/13 08:34:43 by dagouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
int		check_line(char *line);
void	gnl_clear_leftover(void);
char	**gnl_leftover_slot(void);
char	*gnl_finalize_line(char **slot, char *final_line, char *left_over);
char	*get_leftover(char *left_over);

#endif
