#include "koopa_shell.h"

#include <stddef.h>
#include <string.h>

#define SHELL_RX_BUFFER_SIZE (256)
#define SHELL_MAX_ARGS (16)

#ifndef SHELL_PROMPT
#define SHELL_PROMPT "koopa> "
#endif

#ifndef SHELL_LINE_ENDING
#define SHELL_LINE_ENDING '\n'
#endif

//#define SHELL_FOR_EACH_COMMAND(command)               \
//  ShellCommand *command = start_koopa_commands;    \
//  for (; command < stop_koopa_commands; ++command)

//#define SHELL_FOR_EACH_COMMAND(command) \
//  for (const ShellCommand *command = koopa_commands; \
//    command < &koopa_commands[koopa_commands_len]; \
//    ++command)

static bool enable_echo = false;
static size_t rx_size;
static char rx_buffer[SHELL_RX_BUFFER_SIZE];

int koopa_help_handler(int argc, char *argv[]);

static void prv_send_char(char c) {
    koopa_receive_char(c);
}

static void prv_echo(char c) {
    if (SHELL_LINE_ENDING == c) {
        prv_send_char('\r');
        prv_send_char('\n');
    } else if ('\b' == c) {
        prv_send_char('\b');
        prv_send_char(' ');
        prv_send_char('\b');
    } else {
        prv_send_char(c);
    }
}

static char prv_last_char(void) {
    return rx_buffer[rx_size - 1];
}

static bool prv_is_rx_buffer_full(void) {
    return rx_size >= SHELL_RX_BUFFER_SIZE;
}

static void prv_reset_rx_buffer(void) {
    memset(rx_buffer, 0, sizeof(rx_buffer));
    rx_size = 0;
}

static void prv_echo_str(const char *str) {
    for (const char *c = str; *c != '\0'; ++c) {
        prv_echo(*c);
    }
}

static void prv_send_prompt(void) {
    prv_echo_str(SHELL_PROMPT);
}

static const ShellCommand *prv_find_command(const char *name) {
//    SHELL_FOR_EACH_COMMAND(command) {
//        if (strcmp(command->command, name) == 0) {
//            return command;
//        }
//    }
    ShellCommand* command = (ShellCommand*) (&start_koopa_commands);


    return command;
}

static void prv_process(void) {
    if (prv_last_char() != SHELL_LINE_ENDING && !prv_is_rx_buffer_full()) {
        return;
    }

    char *argv[SHELL_MAX_ARGS] = {0};
    int argc = 0;

    char *next_arg = NULL;
    for (size_t i = 0; i < rx_size && argc < SHELL_MAX_ARGS; ++i) {
        char *const c = &rx_buffer[i];
        if (*c == ' ' || *c == '\n' || i == rx_size - 1) {
            *c = '\0';
            if (next_arg) {
                argv[argc++] = next_arg;
                next_arg = NULL;
            }
        } else if (!next_arg) {
            next_arg = c;
        }
    }

    if (rx_size == SHELL_RX_BUFFER_SIZE) {
        prv_echo('\n');
    }

    if (argc >= 1) {
        const ShellCommand *command = prv_find_command(argv[0]);
        if (!command) {
            prv_echo_str("Unknown command: ");
            prv_echo_str(argv[0]);
            prv_echo('\n');
            prv_echo_str("Type 'help' to list all commands\n");
        } else {
            command->handler(argc, argv);
        }
    }
    prv_reset_rx_buffer();
    prv_send_prompt();
}

void koopa_start() {
    prv_reset_rx_buffer();
    prv_echo(SHELL_LINE_ENDING);
    prv_echo_str(SHELL_PROMPT);
}

void koopa_set_echo(bool enabled) {
    enable_echo = enabled;
}

void koopa_put_char(char c) {
    if (c == '\r' || prv_is_rx_buffer_full()) {
        return;
    }

if (enable_echo == true) {
    prv_echo(c);
}

    if (c == '\b') {
        rx_buffer[--rx_size] = '\0';
        return;
    }

    rx_buffer[rx_size++] = c;

    prv_process();
}

int koopa_help_handler(int argc, char *argv[]) {
//    SHELL_FOR_EACH_COMMAND(command) {
//        prv_echo_str(command->command);
//        prv_echo_str(": ");
//        prv_echo_str(command->help);
//        prv_echo(SHELL_LINE_ENDING);
//    }
    return 0;
}
