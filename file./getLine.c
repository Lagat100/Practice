#include "shell.h"

void initialize_info(info_t *info)
{
	info->argument = NULL;
	info->arguments_vector = NULL;
	info->path = NULL;
	info->argument_count = 0;
}

/**
 * configure_info - initializes info_t struct
 * @info: struct address
 * @arguments: argument vector
 */
void configure_info(info_t *info, char **arguments)
{
	int i = 0;

	info->filename = arguments[0];
	if (info->argument)
	{
		info->arguments_vector = strtow(info->argument, " \t");
		if (!info->arguments_vector)
		{

			info->arguments_vector = malloc(sizeof(char *) * 2);
			if (info->arguments_vector)
			{
				info->arguments_vector[0] = _strdup(info->argument);
				info->arguments_vector[1] = NULL;
			}
		}
		for (i = 0; info->arguments_vector && info->arguments_vector[i]; i++)
			;
		info->argument_count = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * deallocate_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void deallocate_info(info_t *info, int all)
{
	ffree(info->arguments_vector);
	info->arguments_vector = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->command_buffer)
			free(info->argument);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environment);
			info->environment = NULL;
		bfree((void **)info->command_buffer);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
