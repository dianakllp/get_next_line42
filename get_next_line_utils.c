#include "get_next_line.h"
#include <stddef.h>

void ft_bzero(void *s, size_t n)
//asigning zero to every element to the buffer //we use it to clear the buffer 
{
    unsigned char *ptr = (unsigned char *)s;
    while (n)
    {
        *ptr++ = '\0';
        n--;
    }
}

size_t ft_strlen(const char *str)
{
    size_t count;

    count = 0;
    if(str == NULL)
    {
        return(0);
    }
    while (*str != '\0')
    {
        count++;
        str++;
    }
    return(count);
}

char *ft_strchr(const char *str, int c)
{
    if(str == NULL)
    {
        return(NULL);
    }
    while(*str != '\0')
    {
        if(*str == c)
        {
            return(char *)str;
        }
        str++;
    }
    if (c == '\0' && *str == '\0')
    {
        return ((char *)str);
    }
    return(NULL);
}

char *ft_strjoin(const char *s1, const char *s2) // in this function we are allocating memory for stash and buffer 
{
    size_t i;
    size_t len;
    char *dest;

    len = ft_strlen(s1) + ft_strlen(s2) + 1;//here we insialized the len to len(s1) + len(s2) + '\0'
    dest = (char *)malloc(len * sizeof(char));//we allocating the memory
    i = 0;
    if(!dest)//checking the mem allocation errors
    {
        return(NULL);
    }

    while (s1 && *s1)
    {
        dest[i++] = *(s1++);
    }
    while(s2 && *s2)
    {
        dest[i++] = *(s2++);
    }
    dest[i] = '\0';
    return (dest);
}