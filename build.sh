execute() {
    echo "$1"
    eval "$1"
}

inc_cterm="-Iexternal/cterm external/cterm/cterm.c"

execute "cc -o cascii main.c -Iexternal/ $inc_cterm -Wall -Wextra -g -lm"
