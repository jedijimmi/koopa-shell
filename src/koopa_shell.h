#ifndef KOOPA_SHELL_KOOPA_SHELL_H
#define KOOPA_SHELL_KOOPA_SHELL_H

#include <stddef.h>
#include <stdbool.h>

typedef struct ShellCommand {
    const char *command;
    int (*handler)(int argc, char *argv[]);
    const char *help;
} ShellCommand;

#pragma section("._koopa_commands$a")
#pragma section("._koopa_commands$u")
#pragma section("._koopa_commands$z")

__declspec(allocate("._koopa_commands$a")) int start_koopa_commands = 0;
__declspec(allocate("._koopa_commands$z")) int stop_koopa_commands   = 0;

#define KOOPA_ADD_COMMAND(n, f, h)                          \
    __declspec(allocate("._koopa_commands$u"))          \
    static ShellCommand kooba_command_##_n  = {             \
        .command = (n),                                     \
        .handler = (f),                                     \
        .help = (h),                                        \
    }

//extern const ShellCommand *const koopa_commands;
//extern const size_t koopa_commands_len;


//        __declspec((used, section("_koopa_commands"))) = {     \
//            .command = (n),                                     \
//            .handler = (f),                                     \
//            .help = (h),                                        \
//        }

//extern const ShellCommand *const __start_koopa_commands;
//extern const ShellCommand *const __stop_koopa_commands;
//extern const ShellCommand *const koopa_commands;
//extern const size_t koopa_commands_len;

void koopa_start();

void koopa_set_echo(bool enabled);

void koopa_put_char(char c);

//! Must be implemented by the client
void koopa_receive_char(char c);

#endif //KOOPA_SHELL_KOOPA_SHELL_H
