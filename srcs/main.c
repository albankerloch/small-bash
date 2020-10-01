/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduchemi <aduchemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:24:18 by aduchemi          #+#    #+#             */
/*   Updated: 2020/07/15 16:59:40 by aduchemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_fix	fix;
	char *line;
	t_list *t;
	int	ret;
	int r;

	ft_fix_construct(&fix, envp);
	ret = 1;
	while (1)
	{
		t = ft_init_list(&fix);
		signal(SIGINT, ft_sig_handler);
		signal(SIGQUIT, SIG_IGN);
		if (ret == 1)
			ft_putstr("<minishell> ");
		line = NULL;
		ret = get_next_line(0, &line);
		if (ret == 0 || ret == -1)
		{
			ft_putstr("exit\n");
			free(line);
			ft_lstclear(&t, &ft_del_command);
			if (ret == 0)
				ft_exit_fix(&fix, -2, EXIT_SUCCESS);
			ft_exit_fix(&fix, -2, EXIT_FAILURE);
		}
		if (!(r = ft_parser(t, line, &fix)))
			ft_exec(t, line, &fix);
		//printf(" return parser : %d\n", r);
		//(void)r;
		free(line);
		ft_lstclear(&t, &ft_del_command);
	}
	/*
	ft_free_command(t->content);
	free(t);
	ft_exit_fix(&fix, -2, 0);
	*/
	return (0);
}
