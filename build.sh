execute() {
    echo "$1"
    eval "$1"
}

execute "cc -o cascii main.c -Iexternal/ -Wall -Wextra -g -lm"
