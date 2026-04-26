#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage(void)
{
    printf("Usage: ./func 'f(x)=' '4x+1' 'pour' 'x=7'\n");
}

int check_prefix(char *str, char *prefix)
{
    return strncmp(str, prefix, strlen(prefix)) == 0 && strlen(str) == strlen(prefix);
}

void parse_expr(char *expr, double *a, double *b)
{
    char *x_pos = strchr(expr, 'x');

	if (!x_pos)
    {
        printf("Erreur: expression invalide, 'x' manquant\n");
        exit(1);
    }
    *a = atof(expr);
    *b = atof(x_pos + 1);
}

double solve(char *expr, double x)
{
    double a;
    double b;

    parse_expr(expr, &a, &b);
    return (a * x + b);
}

int main(int ac, char **av)
{
	double	x;
	double	res;

    if (ac != 5)
	{
    	usage();
		return (0);
	}
    if (!check_prefix(av[1], "f(x)="))
	{
		printf("Erreur: attendu 'f(x)='\n");
        return (0);
	}
	if (!check_prefix(av[3], "pour"))
	{
        printf("Erreur: attendu 'pour'\n");
		return (0);
	}
	if (strncmp(av[4], "x=", 2) != 0)
	{
		printf("Erreur: attendu 'x=<valeur>'\n");
		return (0);
	}
    x = atof(av[4] + 2);
	res = solve(av[2], x);
	printf("f(%g) = %g\n", x, res);
    return 0;
}