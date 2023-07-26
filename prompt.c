#include "shell_library.h"

/**
*main - input the command and create child proccess to execute it
*@ac: count the strings entered
*@argv: number of strings read in
*
*Return: 0
*/
int main(int ac, char **argv)
{
    char *string = NULL, *string_copy = NULL;
    int i, status, string_length;
    size_t n = 0;
    ssize_t number_character;
    pid_t child_pid;
    char *arguments;
    int arguments_count = 0;

    (void)ac;

    while (1)
    {

        if (isatty(STDIN_FILENO))
        {
            printf ("cisfun$ ");
        }

        number_character = getline(&string, &n, stdin);
        if (number_character == -1)
        {
            free(string); 
            exit(EXIT_FAILURE);
        }

        string_copy = malloc(sizeof(char) * number_character);
        if (string_copy == NULL)
        {
            perror("error memory allocation");
            return (-1);
        }

        string_length = _strlen(string);
        _strncpy(string_copy, string, string_length);
        arguments = strtok(string, " \n");
        while (arguments != NULL)
        {
            arguments_count++;
            arguments = strtok(NULL, " \n");
        }
        arguments_count++;

        argv = malloc(sizeof(char *) * arguments_count);
        arguments = strtok(string_copy, " \n");

        for (i = 0; arguments != NULL; i++){
            argv[i] = malloc(sizeof(char) * _strlen(arguments));
            _strncpy(argv[i], arguments, string_length);

            arguments = strtok(NULL, " \n");
        }
        argv[i] = NULL;

        if (check_builtin(argv, number_character))
            continue;

        child_pid = fork();
        if (child_pid == -1)
        {
            free(string);
            exit(EXIT_FAILURE);
        }
        if (child_pid == 0)
        {
            execution_command(argv);
        }
        else
            wait(&status);
    }

    free(string);
    free(string_copy);

    return(0);
}
