#include <stdio.h>
#include <stdlib.h>

int is_not_number(char c)
{
	if (c >= '0' && c <= '9')
		return (0);
	return (1);
}

int check_number(char *s)
{
	int i = 0;

	while (s[i])
	{
		if (is_not_number(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int check_av(char **a)
{
	if (!check_number(a[1]) || !check_number(a[3]))
	{
		printf("On veut calculer des nombres et pas des lettres\n");
		return (0);
	}
	return (1);
}

int main(int ac, char **av)
{
	float result;
	
	result = 0;
	if (ac != 4)
	{
		printf("Entrer ton calcul pas autre chose !\n");
		return (0);
	}

	if (check_av(av) == 0)
		return (0);

	if (av[2][1] == 0)
	{
		if (av[2][0] == '+')
			result = atof(av[1]) + atof(av[3]);
		else if (av[2][0] == '-')
			result = atof(av[1]) - atof(av[3]);
		else if (av[2][0] == '*')
			result = atof(av[1]) * atof(av[3]);
		else if (av[2][0] == '/')
			result = atof(av[1]) / atof(av[3]);
		else
		{
			printf("Erreur, utilise des - + * ou /\n");
			return (0);
		}
	}
	else
	{
		printf("Erreur, utilise des - + * ou /\n");
		return (0);
	}
	
	printf("%s %s %s = %f\n", av[1], av[2], av[3], result);
}