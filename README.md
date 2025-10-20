# cshell
C shell for quick code testing. Written by Eshaan Desh.
# How it works
You start in a main function and can write code in short snippets like the Python shell.
# How to install
- get the code with `wget -O cshell_main.c https://raw.githubusercontent.com/eshnd/cshell/refs/heads/main/src/main.c`
- compile it! e.g. (using gcc and moving it to /bin) `sudo gcc cshell_main.c -o /bin/cshell`
- remove the leftover C file with `rm cshell_main.c`
- alternatively, you can install `cshell` from the AUR
# How to run
- Choose your compiler when you run e.g. `cshell clang` or `cshell gcc` (gcc is default)
