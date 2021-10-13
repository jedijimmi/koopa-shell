#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "src/koopa_shell.h"

bool running = true;


void koopa_receive_char(char c) {
    printf("%c", c);
}

int main(int argc, char **argv) {
    setbuf(stdout, 0);

    koopa_set_echo(false);
    koopa_start();

    char line[256];
    size_t line_len;

    while (running) {
        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("Input error.\n");
            return 1;
        }

        line_len = strlen(line);
        for (int i = 0; i < line_len; i++) {
            koopa_put_char(line[i]);
        }

    }

    return 0;
}

int my_test(int argc, char *argv[]) {
    printf("my test\n");
    return 0;
}

int command_quit(int argc, char *argv[]) {
    running = false;
    return 0;
}


KOOPA_ADD_COMMAND("test", my_test, "haha");