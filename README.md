# simple_shell

### Implementation of a basic Unix-flavoured shell.
- Displays a prompt and waits for input from user.
- Prompt is repeated after each command is executed.
- Handles "end of file condition" (Ctrl+D) fed as an input.
- Handles commands with variable length arguments. eg /usr/bin/ls -l
- Handles PATH for commands eg. ls as input correctly resolves to /usr/bin/ls.
- Properly manages memory.

### Usage:

>Build: gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o ash
>
>Run: ./ash
