/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flturbou <flturbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 19:52:51 by flturbou          #+#    #+#             */
/*   Updated: 2025/02/02 21:32:27 by flturbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

char	*get_code(int fd)
{
	char *code;
	
	code = get_next_line(fd);
	if (code == NULL)
		return (NULL);
	if (strlen(code) != 32)
		return (NULL);
	code[31] = 0;
	return(code);
}

char	*create_line(char *testline, char *name)
{
	
}

int	main(int argc, char **argv)
{
	FILE	*outputuser;
	FILE	*outputsolve;
	char	*testline;
	char	*userline;
	char	*solveline;
	char	buffer[128];
	int		fd;

	if (argc != 3)
		return (printf("add program and solver names\n"), 1);
	fd = open("test4x4.txt", O_RDONLY);

	testline = get_code(fd);
	while (testline)
	{
		userline = create_line(testline, argv[1]);
		solveline = create_line(testline, argv[2]);
		free(userline);
		
		free(testline);
		testline = get_code(fd);
	}
	return (0);
	outputuser = popen(argv[1], "r");
	while (fgets(buffer, sizeof(buffer), outputuser) != NULL)
	{
		printf("%c\n", buffer[0]);
	}

	close(fd);
	pclose(outputuser);
	pclose(outputsolve);
	return (0);
}
