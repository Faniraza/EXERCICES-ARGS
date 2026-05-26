/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faniraza <faniraza@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 13:12:19 by faniraza          #+#    #+#             */
/*   Updated: 2026/05/03 16:13:00 by faniraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	is_prime(int n)
{
	int	i;

	i = 2;
	if (n < 2)
		return (0);
	while (i <= (n / 2))
	{
		if ((n % i) == 0)
			return (0);
		i++;
	}
	return (1);
}

int ft_lenchar(char *tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int ft_strlen(int *tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void write_prime()
{
	FILE *file = fopen("file.txt", "w");
	int	i;
	int	c;
	
	i = 0;
	c = 0;
	while (i < 500)
	{
		if (is_prime(i))
		{
			fprintf(file, "%d\n", i);
			c++;
		}
		if (c == 50)
			break ;
		i++;
	}
	fclose(file);
}

void change_5()
{
	int	i;
	int	j;
	int	modif;
	int	len;
	char tab[51][4];
	FILE *file = fopen("file.txt", "r");
	FILE *file_w = fopen("file_txt", "w");

	i = 0;
	j = 0;
	modif = 0;
	printf("== CHANGE 5 -> v : OK\n");
	while (!feof(file) && i < 50)
	{
		fscanf(file, "%s", tab[i]);
		len = ft_lenchar(tab[i]);
		j = 0;
		while (j < len)
		{
			if (tab[i][j] == '5')
			{
				tab[i][j] = 'v';
				modif++;
			}
			j++;
		}
		fprintf(file_w, "%s\n", tab[i]);
		i++;
	}
	printf("\n==========================\nNOMBRE DE MODIFICATION = %d\n==========================\n", modif);
	fclose(file);
	fclose(file_w);
}

void reverse_total()
{
	int	i;
	int	j;
	char	tmp;
	int	len;
	char tab[51][4];
	FILE *file = fopen("file_rev.txt", "r");
	FILE *new = fopen("file_rev_total.txt", "w");

	i = 0;
	j = 0;
	printf("== REVERSE TOTAL : OK\n");
	while (!feof(file))
	{
		fscanf(file, "%s", tab[i]);
		len = ft_lenchar(tab[i]);
		j = 0;
		while (j < (len / 2) && len != 1)
		{
			tmp = tab[i][j];
			tab[i][j] = tab[i][len - j - 1];
			tab[i][len - j - 1] = tmp;
			j++;
		}
		i++;
	}
	for (i = 0; i < 50; i++)
		fprintf(new, "%s\n", tab[i]);
	fclose(file);
	fclose(new);
}

void reverse_file(int *tab)
{
	int	i;
	int	tmp;
	int len;
	FILE *file;

	file = fopen("file_rev.txt", "w");
	i = 0;
	len = ft_strlen(tab);
	printf("== REVERSE FILE : OK\n");
	while (i < (len / 2))
	{
		tmp = tab[i];
		tab[i] = tab[len - i - 1];
		tab[len - i - 1] = tmp;
		i++;
	}
	for (i = 0; i < 50; i++)
		fprintf(file, "%d\n", tab[i]);
	fclose(file);
}

void get_nb_in_file()
{
	int	i;
	int	n;
	int *tab;
	FILE *file = fopen("file.txt", "r");

	tab = malloc((sizeof(int) * 50) + 1);
	if (!tab)
		return ;
	i = 0;
	while (!feof(file) && i < 50)
	{
		fscanf(file, "%d", &n);
		tab[i] = n;
		i++;
	}
	// for (i = 0; i <= 50; i++)
	// 	printf("tab[%d] = %d\n", i, tab[i]);
	reverse_file(tab);
	fclose(file);
}

void write_line3()
{
	int	i;
	int	n;
	FILE *file = fopen("file.txt", "r");

	i = 1;
	printf("== AFFICHAGE DES LIGNES DIV PAR 3: OK\n");
	while (!feof(file))
	{
		fscanf(file, "%d", &n);
		if ((i % 3) == 0)
			printf("%d\n", n);
		i++;
	}
	fclose(file);
}

void write_nb_div3()
{
	int	i;
	int	n;
	FILE *file = fopen("file.txt", "r");

	i = 1;
	printf("== AFFICHAGE DES NOMBRES DIV PAR 3: OK\n");
	while (!feof(file))
	{
		fscanf(file, "%d", &n);
		if ((n % 3) == 0)
			printf("%d\n", n);
		i++;
	}
	fclose(file);
}

int	main(void)
{
	write_prime();
	write_line3();
	write_nb_div3();
	get_nb_in_file();
	reverse_total();
	change_5();
}