/*
    MIT License

    Copyright (c) 2024 Marvin Katapult

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the Software), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED AS IS, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/
#ifndef __C_TERM__
#define __C_TERM__

#include <stdbool.h>

typedef enum CT_Color {
    CT_Default = 0,
    CT_Black,
    CT_Red,
    CT_Green,
    CT_Yellow,
    CT_Blue,
    CT_Magenta,
    CT_Cyan,
    CT_White,
    CT_LBlack,
    CT_LRed,
    CT_LGreen,
    CT_LYellow,
    CT_LBlue,
    CT_LMagenta,
    CT_LCyan,
    CT_LWhite
} CT_Color;

/** Utils **/
void clearScreen(void);
void moveCursor(int x, int y);
void setPrintColor(CT_Color color);
void setBgColor(CT_Color color);
void resetCTColor(void);
bool isCtrlChar(int ch);

/** Terminal Geometry **/
int getTermWidth(void);
int getTermHeight(void);
void getTermSize(int * w, int * h);

/** Printing **/
void putStr(const char * str);
void putStrExt(const char * str, CT_Color print_col, CT_Color bg_col);
void putStrAt(const char * str, int x, int y);
void putStrAtExt(const char * str, int x, int y, CT_Color print_col, CT_Color bg_col);
void fillScreenBg(CT_Color color);

/** Rawmode **/
// From https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html
void disableRawMode(void);
void enableRawMode(void);
unsigned char readTermInput(void);

#endif // __C_TERM__
