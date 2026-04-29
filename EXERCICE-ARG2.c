#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void usage(void)
{
    printf("Usage: ./func 'f(x)=' '4x+1' 'pour' 'x=7'\n");
}

char get_var(char *a)
{
	return a[2];
}

int check_prefix(char *str, char *prefix)
{
    return strncmp(str, prefix, strlen(prefix)) == 0 && strlen(str) == strlen(prefix);
}

void parse_expr(char *expr, double *a, double *b, char var)
{
    char *x_pos = strchr(expr, var);

	if (!x_pos)
    {
        printf("Erreur: expression invalide, '%c' manquant\n", var);
        exit(1);
    }
	if (x_pos == expr)
	{
		*a = 1;
		*b = atof(x_pos + 1);
	}
	else
	{
		char *op = x_pos - 1;
		while (op > expr && *op != '+' && *op != '-')
			op--;
		if (*op == '+' || *op == '-')
		{
			*b = atof(expr);
			if (*(op + 1) == 'x')
			{
				if (*op == '-')
					*a = -1;
				else
					*a = 1;
			}
			else
				*a = atof(op);
		}
		else
		{
			*a = atof(expr);
			*b = atof(x_pos + 1);
		}
	}
}

double solve(char *expr, double x, char var)
{
    double a;
    double b;

    parse_expr(expr, &a, &b, var);
    return (a * x + b);
}

int main(int ac, char **av)
{
	double	x;
	double	res;
	char var = get_var(av[1]);

	if (!isalpha(var))
	{
		printf("Erreur: '%c' n'est pas une variable valide\n", var);
		return (0);
	}
    if (ac != 5)
	{
    	usage();
		return (0);
	}

    if (strlen(av[1]) != 5)
	{
		printf("Erreur: attendu 'f(var)='\n");
        return (0);
	}
	if (av[1][0] != 'f' || av[1][1] != '(' || av[1][3] != ')' || av[1][4] != '=')
    {
        printf("Erreur: format invalide, attendu 'f(var)='\n");
        return (0);
    }

	if (!check_prefix(av[3], "pour"))
	{
        printf("Erreur: attendu 'pour'\n");
		return (0);
	}
	if (av[4][0] != var)
	{
	    printf("Erreur: variable '%c' dans %s ne correspond pas a '%c'\n", av[4][0], av[4], var);
		return (0);
	}
    x = atof(av[4] + 2);
	res = solve(av[2], x, var);
	printf("f(%g) = %g\n", x, res);
    return 0;
}