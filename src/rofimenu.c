#include "dwm.h"
#include "str2num.h"

// The size of the buffer to parse the return int.
// 32 chars should be totally enough, 2**64 is only 20 chars long
#define BUFFER_SIZE 32

#define RD 0
#define WR 1

static int launch_printf(const RofiMenu *menu)
{
    // create the pipe that can later be used as stdin for rofi

    int pipes[2];

    if (pipe(pipes) < -1)
        return -1;

    // prepare argv array for the printf command:
    // printf '%s\n' arg1 arg2 arg3 ...

    int arg_count = menu->entry_count + 2;
    const char **argv = ecalloc(arg_count, sizeof(char *));

    argv[0] = "/usr/bin/printf";
    argv[1] = "%s\n";

    for (int i = 0; i < menu->entry_count; i++)
        argv[i + 2] = menu->menu_entries[i].name;

    pid_t pid = fork();

    if (pid < 0)
    {
        free(argv);
        close(pipes[RD]);
        close(pipes[WR]);
        return -1;
    }
    else if (pid == 0)
    {
        // the reading end of the pipe is not needed in the child process
        close(pipes[RD]);

        // link STDOUT to the writing end of the pipe
        dup2(pipes[WR], STDOUT_FILENO);
        close(pipes[WR]);

        // exec the printf command
        execv(argv[0], (char *const *)argv);

        // exec should not return if sucessfull
        return -1;
    }
    else
    {
        // the writing end of the pipe is not needed in the parent process
        close(pipes[WR]);

        // wait for the child to exit and then free the memory
        waitpid(pid, NULL, 0);
        free(argv);

        // return the reading end of the pipe, so it can be used later for the rofi command
        return pipes[RD];
    }
}

static int launch_rofi(const RofiMenu *menu)
{
    int stdin_pipe = launch_printf(menu);

    if (stdin_pipe < 0)
        return -1;

    int pipes[2];

    if (pipe(pipes) < 0)
    {
        close(stdin_pipe);
        return -1;
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        close(stdin_pipe);
        close(pipes[RD]);
        close(pipes[WR]);
        return -1;
    }
    else if (pid == 0)
    {

        // the reading end is not needed, we will use stdin_pipe as stdin
        close(pipes[RD]);

        // set STDOUT to the writing end of the pipe
        dup2(pipes[WR], STDOUT_FILENO);
        close(pipes[WR]);

        // set STDIN to the stdin_pipe
        dup2(stdin_pipe, STDIN_FILENO);
        close(stdin_pipe);

        const char *const argv[] = {
            "/usr/bin/rofi",
            "-dmenu",
            "-i",
            "-format",
            "i",
            "-bc",
            menu->border_color,
            "-bg",
            menu->bg_color,
            "-fg",
            menu->fg_color,
            "-hlfg",
            menu->hlfg_color,
            "-hlbg",
            menu->hlbg_color,
            "-theme",
            menu->config_file,
            "-p",
            menu->prompt,
        };

        execv(argv[0], (char *const *)argv);

        // again, if exec only returns on error
        return -1;
    }
    else
    {
        // the writing end is not needed
        close(pipes[WR]);

        // wait for rofi to exit
        waitpid(pid, NULL, 0);

        // return the readable end to the pipe, it will contain the selection from the rofi menu
        return pipes[RD];
    }
}

void rofimenu(const Arg *arg)
{
    const RofiMenu *menu = (RofiMenu *)arg->v;

    int stdout_pipe = launch_rofi(menu);

    char buffer[BUFFER_SIZE];
    ssize_t chars_read = read(stdout_pipe, buffer, BUFFER_SIZE - 1);

    close(stdout_pipe);

    if (chars_read <= 0)
        return;

    // trim trailing whitespace
    char *end = buffer + chars_read - 1;
    while (end > buffer && isspace((unsigned char)*end))
        end--;

    end[1] = '\0';

    int result;
    if ((str2int(&result, buffer, 10)) != STR2NUM_SUCCESS)
        return;

    if (result < 0 || result > menu->entry_count)
        return; // that would probably be a bug in rofi

    const char **argv = menu->menu_entries[result].argv;

    if (argv)
    {
        Arg spawn_arg = {.v = argv};
        spawn(&spawn_arg);
    }
}