#include "shell.h"

/**
 * buffer_input - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of length var
 *
 * Return: bytes read
 */
ssize_t buffer_input(info_t *info, char **buf, size_t *len)
{
    ssize_t bytes_read = 0;
    size_t len_p = 0;

    if (!*len) /* if nothing left in the buffer, fill it */
    {
        /*bfree((void **)info->cmd_buf);*/
        free(*buf);
        *buf = NULL;
        signal(SIGINT, handle_interrupt);
#if USE_GETLINE
        bytes_read = getline(buf, &len_p, stdin);
#else
        bytes_read = custom_getline(info, buf, &len_p);
#endif
        if (bytes_read > 0)
        {
            if ((*buf)[bytes_read - 1] == '\n')
            {
                (*buf)[bytes_read - 1] = '\0'; /* remove trailing newline */
                bytes_read--;
            }
            info->linecount_flag = 1;
            remove_comments(*buf);
            build_history_list(info, *buf, info->histcount++);
            /* if (_strchr(*buf, ';')) is this a command chain? */
            {
                *len = bytes_read;
                info->cmd_buf = buf;
            }
        }
    }
    return bytes_read;
}


/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
    static char *buf; /* the ';' command chain buffer */
    static size_t i, j, len;
    ssize_t bytes_read = 0;
    char **buf_p = &(info->arg), *p;

    _putchar(BUF_FLUSH);
    bytes_read = buffer_input(info, &buf, &len);
    if (bytes_read == -1) /* EOF */
        return -1;
    if (len) /* we have commands left in the chain buffer */
    {
        j = i; /* init new iterator to current buf position */
        p = buf + i; /* get pointer for return */

        check_chain(info, buf, &j, i, len);
        while (j < len) /* iterate to semicolon or end */
        {
            if (is_chain(info, buf, &j))
                break;
            j++;
        }

        i = j + 1; /* increment past nulled ';'' */
        if (i >= len) /* reached end of buffer? */
        {
            i = len = 0; /* reset position and length */
            info->cmd_buf_type = CMD_NORM;
        }

        *buf_p = p; /* pass back pointer to current command position */
        return strlen(p); /* return length of current command */
    }

    *buf_p = buf; /* else not a chain, pass back buffer from _getline() */
    return bytes_read; /* return length of buffer from _getline() */
}



ssize_t read_buffer(info_t *info, char *buffer, size_t *i)
{
    ssize_t bytes_read = 0;

    if (*i)
        return 0;
    bytes_read = read(info->readfd, buffer, READ_BUF_SIZE);
    if (bytes_read >= 0)
        *i = bytes_read;
    return bytes_read;
}



int custom_getline(info_t *info, char **ptr, size_t *length)
{
    static char buf[READ_BUF_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t bytes_read = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;
    if (p && length)
        bytes_read = *length;
    if (i == len)
    {
        i = len = 0;
    }

    bytes_read = read_buffer(info, buf, &len);
    if (bytes_read == -1 || (bytes_read == 0 && len == 0))
        return -1;

    c = _strchr(buf + i, '\n');
    k = c ? 1 + (unsigned int)(c - buf) : len;
    new_p = _realloc(p, bytes_read, bytes_read ? bytes_read + k : k + 1);
    if (!new_p) /* MALLOC FAILURE! */
        return p ? (free(p), -1) : -1;

    if (bytes_read)
        _custom_strncat(new_p, buf + i, k - i);
    else
        _custom_strncpy(new_p, buf + i, k - i + 1);

    bytes_read += k - i;
    i = k;
    p = new_p;

    if (length)
        *length = bytes_read;
    *ptr = p;
    return bytes_read;
}



void handle_interrupt(__attribute__((unused))int signal_num)
{
    _puts("\n");
    _puts("$ ");
    _putchar(BUF_FLUSH);
}
