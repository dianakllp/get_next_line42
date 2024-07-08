/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dianakolopenyuk <dianakolopenyuk@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:39:28 by dianakolope       #+#    #+#             */
/*   Updated: 2024/07/08 19:23:25 by dianakolope      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>    // For printf()
#include <fcntl.h>    // For open()
#include <unistd.h>  

static int read_Buffer(int fd, char **stash, char *buffer)
{
    char *temp; 
    int bytes; 
    
    ft_bzero(buffer, BUFFER_SIZE + 1);
    bytes = read(fd, buffer, BUFFER_SIZE); //it stops at null term
    //read returns the number of bytes that it has read. And the data is saved in buffer in read()
    
    if (bytes < 0 || buffer == NULL) //if read returns negative or buffer is zero; bytes always should be
    //non negative
    {
        free(*stash);
        *stash = NULL;
        return (-1);
    }
    if (bytes == 0) //when read returns 0 it means that its OK
    {
        return(0); //return (0) doesn't exit the function 
    }
    temp = ft_strjoin(*stash, buffer); // this function is adding the data from buffer to stash 
    //(previous line that has been in stash + new from buffer)
    free(*stash); // it saving our memory for us
    *stash = temp; 
    return (bytes); 
}

static void remove_result(char **stash)
{
    char *nl; 
    char *temp; 
    size_t i;
    size_t j;
    
    nl = ft_strchr(*stash, '\n');
    if (!nl)
    {
        free(*stash);
        *stash = NULL;
        return ;
    }
    temp = malloc((ft_strlen(nl)) * sizeof(char));
    i = 0;
    j = ft_strlen(*stash) - ft_strlen(nl) + 1; //pointer to the index to the character after we find 
    //the new line (so the first charcet of the nex sentence)
    // "1234567\n90"
    while (j < ft_strlen(*stash))
    {
        temp[i++] = (*stash)[j++];
    }
    temp[i] = '\0';
    free(*stash);
    *stash = temp; 
    if (**stash == 0)
    {
        free(*stash);
        *stash = NULL;
    }
}

static void get_result(char **stash, char **result)//This function extracts the next complete line from stash and stores it in result.
{
    char *nl;
    size_t i; 
    size_t len;

    nl = ft_strchr(*stash, '\n'); //it returns the pointer to the character where it founds a new line
    if (!nl)
        nl = ft_strchr(*stash, '\0');
    len = ft_strlen(*stash) - ft_strlen(nl) + 2; //here we are looking for the len after we find a new line char
    // (why + 2? we are adding null terminator and new line character);
    *result = (char *)malloc (len * sizeof(char)); //assigning the memory 
    if (!result)
    {
        return;
    } 
    i = 0;
    while(i < len - 1) //assigning the data from stash until we find a new line 
    {
        (*result)[i] = (*stash)[i];
        i++;
    }
    (*result)[i] = '\0';
}

char *get_next_line(int fd)
{
    static char *stash;
    char *buffer;
    char *result;
    int  bytes; 

    if(fd < 0 || BUFFER_SIZE <= 0) //If the file descriptor fd is invalid or BUFFER_SIZE is not positive, return NULL
        return (NULL);
    buffer = (char *)malloc((BUFFER_SIZE + 1) *sizeof(char)); // allocating memory 
    if (!buffer) 
    {
        return (NULL);
    }
    bytes = 1;
    while (!ft_strchr(stash, '\n') && bytes > 0) // Read data in a loop until a newline character (\n) is found
    // in stash or no more data can be read (bytes > 0).
    
    {
        bytes = read_Buffer(fd, &stash, buffer);//Reads data from fd into the stash using buffer.
    }
    free(buffer); //Free the allocated buffer after reading.
    
    if(bytes == -1)
    {
        return(NULL);
    }
    if (ft_strlen(stash) == 0) //If stash is empty, return NULL.
        return NULL;

    get_result(&stash, &result); //The & indicates passing the address of stash to modify it directly.
    remove_result(&stash);
    return(result); //Return the extracted line.
}

// aditional: the buffer will stop and move the memory in 2 cases: 1) when it is full (so filled with 42 bytes)
// or when it has found a new line. Even if it has only 3 bytes

/*int main() {
    int fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    char *line = get_next_line(fd);
    if (line) {
        printf("%s\n", line);
        // Free the line if necessary
    }

    close(fd);
    return 0;
}*/