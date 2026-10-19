*This project has been created as part of the 42 curriculum by keblanch.*

# libft

## Description

The goal of this project is to create a basic library including functions from the libc library, a few additional functions for string manipulation and output as well as a linked list structure and functions to manipulate it.

All functions only use the system libraries `unistd` and `stdlib`.

## Instructions

Create the library using `make` at the root of the project.

The library will be named `libft.a`.

## Ressources

- man

## Detailed description

In the following sections, the word `string` is used to refer to C strings.

### Libc functions

- `ft_isalpha`: returns 1 if the parameter corresponds to an alphabetical ASCII value, 0 otherwise.
- `ft_isdigit`: returns 1 if the parameter corresponds to a digit ASCII value, 0 otherwise.
- `ft_isalnum`: returns 1 if the parameter corresponds to an alphanumerical ASCII value, 0 otherwise.
- `ft_isascii`: returns 1 if the parameter corresponds to an ASCII value, 0 otherwise.
- `ft_isprintable`: returns 1 if the parameter corresponds to a printable ASCII value, 0 otherwise.
- `ft_strlen`: returns the length of the string passed as parameter.
- `ft_memset`: sets each byte of the memory area passed as parameter to the value passed as parameter.
- `ft_bzero`: sets each byte of the memory area passed as parameter to 0.
- `ft_memcpy`: copies a number of bytes from a source to a destination.
- `ft_memmove`: moves a number of bytes from a source to a destination.
- `ft_strlcpy`: copies a number of characters from a source to a destination.
- `ft_strlcat`: concatenates a number of characters from a source to the end of a destination.
- `ft_toupper`: converts char to uppercase.
- `ft_tolower`: converts char to uppercase.
- `ft_strchr`: returns the position of the first occurence of a character in a string, null if the character is not in the string.
- `ft_strrchr`: returns the position of the last occurence of a character in a string, null if the character is not in the string.
- `ft_strncmp`: returns the difference between two strings, up to `n` characters.
- `ft_memchr`: returns the position of the first occurence of a value in a given memory area, null if the value is not in the area.
- `ft_memcmp`: returns the difference between two memory areas, up to `n` bytes.
- `ft_strnstr`: returns the position of the first occurence of a substring in a string, null if the substring is not in the string.
- `ft_atoi`: converts an ASCII string to integer.
- `ft_calloc`: returns a malloc'd area that is filled with 0.
- `ft_strdup`: returns a malloc'd string that is a copy of a given string.

### Additional functions

- `ft_substr`: returns a malloc'd substring of a given string.
- `ft_strjoin`: returns a malloc'd concatenation of two strings.
- `ft_strtrim`: returns a malloc's trimmed copy of a string.
- `ft_split`: returns a malloc'd array of malloc'd strings from a split string.
- `ft_itoa`: returns an ASCII string representation of an integer.
- `ft_strmapi`: returns a malloc'd string resulting of the application of a function to each character of a given string.
- `ft_striteri`: applies a function to each character of a given string.
- `ft_putchar_fd`: prints a character to the given file descriptor.
- `ft_putstr_fd`: prints a string to the given file descriptor.
- `ft_putendl_fd`: prints a newline character to the given file descriptor.
- `ft_putnbr_fd`: prints a number as ASCII to the given file descriptor.

### Linked list

- `ft_lstnew`: returns a malloc'd linked list element.
- `ft_lstadd_front`: adds an element to the front of a linked list.
- `ft_lstsize`: returns the length of a linked list.
- `ft_lstlast`: returns the last element of a linked list.
- `ft_lstadd_back`: add an element to the back of a linked list.
- `ft_lstdelone`: frees the content of an element.
- `ft_lstclear`: frees a linked list.
- `ft_lstiter`: applies a function to each element of a linked list.
- `ft_lstmap`: returns a new linked list resulting of the application of a function to each element of a linked list.
