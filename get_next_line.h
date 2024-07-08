#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42 //
#endif

//main function 
char *get_next_line(int fd);

//tools of the project
void ft_bzero(void *s, size_t n);//set all the value of all the bit i the memory to zero
size_t ft_strlen(const char *str);//to calc the length str
char *ft_strchr(const char *str, int c);//find the char in the string
char *ft_strjoin(const char *s1, const char *s2);//to concatnate two strings together

#endif