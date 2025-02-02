/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flturbou <flturbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 19:52:51 by flturbou          #+#    #+#             */
/*   Updated: 2025/02/02 22:29:26 by flturbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*res;
	unsigned int	i;
	unsigned int	j;

	i = strlen(s1);
	j = 0;
	res = (char *)malloc((i + strlen(s2) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	strcpy(res, s1);
	while (s2[j])
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = 0;
	return (res);
}

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
	char	*inter;
	char	*res;

	inter = ft_strjoin("\"", testline);
	res = ft_strjoin(inter, "\"");
	free(inter);
	inter = ft_strjoin(" ", res);
	free(res);
	res = ft_strjoin(name, inter);
	free(inter);
	inter = ft_strjoin("./", res);
	free(res);
	return (inter);
}

int	main(int argc, char **argv)
{
	FILE	*outputuser;
	FILE	*outputsolve;
	char	*testline;
	char	*userline;
	char	*solveline;
	char	buffersolve[128];
	char	bufferuser[128];
	int		fd;
	int		testgood;
	int		testnbr;

	if (argc != 3)
		return (printf("add program and solver names\n"), 1);
	fd = open("test4x4.txt", O_RDONLY);

	testline = get_code(fd);
	testnbr = 1;
	while (testline)
	{
		userline = create_line(testline, argv[1]);
		solveline = create_line(testline, argv[2]);
		outputuser = popen(userline, "r");
		if (outputuser == NULL)
			return (1);
		outputsolve = popen(solveline, "r");
		if (outputsolve == NULL)
			return (1);
		testgood = 0;
		for (int i = 0; i < 4; i++)
		{
			if (!(fgets(buffersolve, sizeof(buffersolve), outputsolve) && fgets(bufferuser, sizeof(bufferuser), outputuser)))
				break ;
			if (strcmp(buffersolve, bufferuser) == 0)
				testgood++;
		}
		printf("TEST %d: ", testnbr);
		if (testgood == 4)
			printf("OK\n");
		else
			printf("FAIL!!!!!!!!\n");
		testnbr++;
		pclose(outputuser);
		pclose(outputsolve);
		free(testline);
		free(userline);
		free(solveline);
		testline = get_code(fd);
	}
	close(fd);
	return (0);
	/*
	outputuser = popen(argv[1], "r");
	while (fgets(buffer, sizeof(buffer), outputuser) != NULL)
	{
		printf("%c\n", buffer[0]);
	}

	close(fd);
	pclose(outputuser);
	pclose(outputsolve);
	return (0);*/
}
