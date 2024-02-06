#include "shell.h"

int string_to_integer(char *s)
{
    int i = 0;
    unsigned long int result = 0;

    if (*s == '+')
        s++;  /* TODO: why does this make main return 255? */
    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            result *= 10;
            result += (s[i] - '0');
            if (result > INT_MAX)
                return (-1);
        }
        else
            return (-1);
    }
    return (result);
}

/**
 * print_error_message - prints an error message
 * @info: the parameter & return info struct
 * @error_string: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error_message(info_t *info, char *error_string)
{
    print_to_stderr(info->filename);
    print_to_stderr(": ");
    print_to_stderr(info->line_count, STDERR_FILENO);
    print_to_stderr(": ");
    print_to_stderr(info->argv[0]);
    print_to_stderr(": ");
    print_to_stderr(error_string);
}

/**
 * print_decimal - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int print_decimal(int input, int fd)
{
    int (*print_char_func)(char) = print_char;
    int i, count = 0;
    unsigned int absolute_value, current;

    if (fd == STDERR_FILENO)
        print_char_func = print_error_character;
    if (input < 0)
    {
        absolute_value = -input;
        print_char_func('-');
        count++;
    }
    else
        absolute_value = input;
    current = absolute_value;
    for (i = 1000000000; i > 1; i /= 10)
    {
        if (absolute_value / i)
        {
            print_char_func('0' + current / i);
            count++;
        }
        current %= i;
    }
    print_char_func('0' + current);
    count++;

    return (count);
}

/**
 * convert_number_to_string - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number_to_string(long int num, int base, int flags)
{
    static char *array;
    static char buffer[50];
    char sign = 0;
    char *ptr;
    unsigned long n = num;

    if (!(flags & CONVERT_UNSIGNED) && num < 0)
    {
        n = -num;
        sign = '-';
    }
    array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
    ptr = &buffer[49];
    *ptr = '\0';

    do
    {
        *--ptr = array[n % base];
        n /= base;
    } while (n != 0);

    if (sign)
        *--ptr = sign;
    return (ptr);
}

/**
 * replace_comment_with_null - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void replace_comment_with_null(char *buf)
{
    int i;

    for (i = 0; buf[i] != '\0'; i++)
        if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
        {
            buf[i] = '\0';
            break;
        }
}
