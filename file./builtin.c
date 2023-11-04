#include "shell.h"

/**
 * exit_shell - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info->argv[0] != "exit"
 */
int exit_shell(info_t *info)
{
    int exit_check;

    if (info->argv[1])  /* If there is an exit argument */
    {
        exit_check = string_to_int(info->argv[1]);
        if (exit_check == -1)
        {
            info->status = 2;
            print_error(info, "Illegal number: ");
            print_string(info->argv[1]);
            print_char('\n');
            return (1);
        }
        info->err_num = string_to_int(info->argv[1]);
        return (-2);
    }
    info->err_num = -1;
    return (-2);
}

/**
 * change_directory - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int change_directory(info_t *info)
{
    char *s, *dir, buffer[1024];
    int chdir_ret;

    s = getcwd(buffer, 1024);
    if (!s)
        print_string("TODO: >>getcwd failure emsg here<<\n");
    if (!info->argv[1])
    {
        dir = getenv_var(info, "HOME=");
        if (!dir)
            chdir_ret = /* TODO: what should this be? */
                chdir((dir = getenv_var(info, "PWD=")) ? dir : "/");
        else
            chdir_ret = chdir(dir);
    }
    else if (_strcmp(info->argv[1], "-") == 0)
    {
        if (!getenv_var(info, "OLDPWD="))
        {
            print_string(s);
            print_char('\n');
            return (1);
        }
        print_string(getenv_var(info, "OLDPWD=")), print_char('\n');
        chdir_ret = /* TODO: what should this be? */
            chdir((dir = getenv_var(info, "OLDPWD=")) ? dir : "/");
    }
    else
        chdir_ret = chdir(info->argv[1]);
    if (chdir_ret == -1)
    {
        print_error(info, "can't cd to ");
        print_string(info->argv[1]), print_char('\n');
    }
    else
    {
        setenv_var(info, "OLDPWD", getenv_var(info, "PWD="));
        setenv_var(info, "PWD", getcwd(buffer, 1024));
    }
    return (0);
}

/**
 * help_command - displays help message
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int help_command(info_t *info)
{
    char **arg_array;

    arg_array = info->argv;
    print_string("help call works. Function not yet implemented \n");
    if (0)
        print_string(*arg_array); /* temp att_unused workaround */
    return (0);
}
