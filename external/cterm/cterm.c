#include "./cterm.h"

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>

#include <ctype.h>

void clearScreen() {
    printf("\033[2J");
}

void moveCursor(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

void putStr(const char * str) {
    printf(str);
}

void putStrExt(const char * str, CT_Color print_col, CT_Color bg_col) {
    setPrintColor(print_col);
    setBgColor(bg_col);
    printf(str);
    resetCTColor();
}

void putStrAt(const char * str, int x, int y) {
    moveCursor(x, y);
    printf(str);
}

void putStrAtExt(const char * str, int x, int y, CT_Color print_col, CT_Color bg_col) {
    setPrintColor(print_col);
    setBgColor(bg_col);
    moveCursor(x, y);
    printf(str);
    resetCTColor();
}

int getTermWidth(void) {
    int w = 0;
    getTermSize(&w, NULL);
    return w;
}

int getTermHeight(void) {
    int h = 0;
    getTermSize(NULL, &h);
    return h;
}

void getTermSize(int * w, int * h) {
    struct winsize win;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
    if (w) *w = win.ws_col;
    if (h) *h = win.ws_row;
}

void fillScreenBg(CT_Color color) {
    moveCursor(0, 0);
    setBgColor(color);
    int w, h;
    getTermSize(&w, &h);
    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            printf(" ");
        }
    }
    moveCursor(0, 0);
}

void setPrintColor(CT_Color color) {
    switch (color) {
        case CT_Default:  printf("\033[39m"); break;
        case CT_Black:    printf("\033[30m"); break;
        case CT_Red:      printf("\033[31m"); break;
        case CT_Green:    printf("\033[32m"); break;
        case CT_Yellow:   printf("\033[33m"); break;
        case CT_Blue:     printf("\033[34m"); break;
        case CT_Magenta:  printf("\033[35m"); break;
        case CT_Cyan:     printf("\033[36m"); break;
        case CT_White:    printf("\033[37m"); break;
        case CT_LBlack:   printf("\033[90m"); break;
        case CT_LRed:     printf("\033[91m"); break;
        case CT_LGreen:   printf("\033[92m"); break;
        case CT_LYellow:  printf("\033[93m"); break;
        case CT_LBlue:    printf("\033[94m"); break;
        case CT_LMagenta: printf("\033[95m"); break;
        case CT_LCyan:    printf("\033[96m"); break;
        case CT_LWhite:   printf("\033[97m"); break;
        default:          printf("\033[39m"); break;
    }
}

void setBgColor(CT_Color color) {
    switch (color) {
        case CT_Default:  printf("\033[49m");  break;
        case CT_Black:    printf("\033[40m");  break;
        case CT_Red:      printf("\033[41m");  break;
        case CT_Green:    printf("\033[42m");  break;
        case CT_Yellow:   printf("\033[43m");  break;
        case CT_Blue:     printf("\033[44m");  break;
        case CT_Magenta:  printf("\033[45m");  break;
        case CT_Cyan:     printf("\033[46m");  break;
        case CT_White:    printf("\033[47m");  break;
        case CT_LBlack:   printf("\033[100m"); break;
        case CT_LRed:     printf("\033[101m"); break;
        case CT_LGreen:   printf("\033[102m"); break;
        case CT_LYellow:  printf("\033[103m"); break;
        case CT_LBlue:    printf("\033[104m"); break;
        case CT_LMagenta: printf("\033[105m"); break;
        case CT_LCyan:    printf("\033[106m"); break;
        case CT_LWhite:   printf("\033[107m"); break;
        default:          printf("\033[49m");  break;
    }
}

void resetCTColor(void) {
    setPrintColor(CT_Default);
    setBgColor(CT_Default);
}

static struct termios orig_termios;

// From https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html
void disableRawMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
  tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(disableRawMode);
  struct termios raw = orig_termios;
  raw.c_iflag &= ~(ICRNL | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

bool isCtrlChar(int ch) {
    return iscntrl(ch);
}

unsigned char readTermInput(void) {
    char c = '\0';
    read(STDIN_FILENO, &c, 1);
    return c;
}
