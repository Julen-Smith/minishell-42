
#include "../../include/minishell.h"

char **ft_duplicate_environment(char **str)
{
    char    **result;
    int     i;

    i = -1;
    result = (char **)malloc(sizeof(char *) * (ft_doublestrlen(str) + 1));
    if (!result)
        return (NULL);
    while (str[++i])
        result[i] = ft_strdup(str[i]);
    result[i] = 0;
    return (result);
}