
inc_cterm=-Iexternal/cterm external/cterm/cterm.c

all:
	cc -o cascii main.c -Iexternal/ $(inc_cterm) -Wall -Wextra -g -lm
