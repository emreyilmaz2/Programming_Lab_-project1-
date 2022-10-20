#include "prolab.h"

int ft_strnstr(const char *haystack, const char *needle, int flag)
{
    size_t    i;
    size_t    c;
    size_t    n_len;
    char    *hay;

    i = 0;
    hay = (char *)haystack;
    n_len = strlen(needle);
    if (n_len == 0 || haystack == needle)
        return (0);
    while (hay[i] != '\0')
    {
        c = 0;
        while (hay[i + c] != '\0' && needle[c] != '\0'
            && hay[i + c] == needle[c])
            c++;
        if (c == n_len && flag == 0)
        {
			if(haystack[i-2] == '[' && haystack[i-1] == '[')
			{
				if(haystack[i+n_len] == ']' && haystack[i+n_len+1] == ']')
					return(1);
			}
			else
				return(0);
        }
        else if(c == n_len && flag ==1)
            return(1);
        i++;
    }
    return (0);
}
