# cconsole
C console for quick code testing. Written by Eshaan Desh.
# How it works
You start in a main function and can write code in short snippets like the Python shell.
# How to install
- get the code with `wget -O cconsole_main.c https://raw.githubusercontent.com/eshnd/cconsole/refs/heads/main/src/main.c`
- compile it! e.g. (using gcc and moving it to /bin) `sudo gcc cconsole_main.c -o /bin/cconsole -lreadline -lncurses`
- remove the leftover C file with `rm cconsole_main.c`
- alternatively, you can install `cconsole` from the AUR
# How to run
- Choose your compiler when you run e.g. `cconsole clang` or `cconsole gcc` (gcc is default)
- Choose any inclusions you want to have before defining the main function
- Now write any code you want and it'll execute!
- `cconsole exit;` to exit safely
- `cconsole save <filename>;` to save code properly

