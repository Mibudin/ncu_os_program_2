#pragma once
#ifndef SCREEN_H
#define SCREEN_H


/**
 * ANSI Escape Sequences
 * More on: https://docs.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences#mode-changes
 */

// Escape Sequence
#define ESC "\033"   // Escape Character
#define BEL "\007"   // Bell
#define CSI ESC "["  // Control Sequence Introducer
#define OSC ESC "]"  // Operating System Command

// Operating System Command
#define SWT(s) OSC "2;" #s BEL  // Set Window Title

// Control Sequence Introducer
#define CUU(n)    CSI #n        "A"  // Cursor Up
#define CUD(n)    CSI #n        "B"  // Cursor Down
#define CUF(n)    CSI #n        "C"  // Cursor Forward
#define CUB(n)    CSI #n        "D"  // Cursor Back
#define VPA(n)    CSI #n        "d"  // Vertical Line Position Absolute
#define CHA(n)    CSI #n        "G"  // Cursor Horizontal Absolute
#define CUP(n, m) CSI #n ";" #m "H"  // Cursor Position
#define ED(n)     CSI #n        "J"  // Erase in Display (0: cursor to line end, 1: cursor to line start, 2: all screen)
#define SGR(l)    CSI #l        "m"  // Select Graphic Rendition
#define DSR       CSI          "6n"  // Device Status Report
#define ECH(n)    CSI #n        "P"  // Erace Character
#define SCP       CSI           "s"  // Save Cursor Position
#define RCP       CSI           "u"  // Restore Cursor Position

// Control Sequence Introducer (Set Environment Booleans)
#define CUS CSI "?25h"    // Text Cursor Enable Mode Show
#define CUH CSI "?25l"    // Text Cursor Enable Mode Hide
#define ASB CSI "?1049h"  // Use Alternate Screen Buffer
#define MSB CSI "?1049l"  // Use Main Screen Buffer

// Select Graphic Rendition
#define SGR_ATTR(n)    SGR(#n)         // Set attributes
#define SGR_CLOR(b, f) SGR(#b ";" #f)  // Set colors of baclground and foreground

// Select Graphic Rendition (Attributes)
#define SGR_DEFT SGR_ATTR(0)   // Set to default
#define SGR_BDBR SGR_ATTR(1)   // Set to be bold and bright
#define SGR_NOBB SGR_ATTR(22)  // Set to be not bold and bright
#define SGR_UDLN SGR_ATTR(4)   // Set to be with underline
#define SGR_NOUL SGR_ATTR(24)  // Set to be with no underline
#define SGR_NEGA SGR_ATTR(7)   // Swaps foreground and background colors
#define SGR_POSI SGR_ATTR(27)  // Returns foreground adn background to normal


namespace gol
{
    #define sdfs 3
    class e;
}


// Hide input echo

// #include <termios.h>

// ...

// void HideStdinKeystrokes()
// {
//     termios tty;

//     tcgetattr(STDIN_FILENO, &tty);

//     /* we want to disable echo */
//     tty.c_lflag &= ~ECHO;

//     tcsetattr(STDIN_FILENO, TCSANOW, &tty);
// }

// void ShowStdinKeystrokes()
// {
//    termios tty;

//     tcgetattr(STDIN_FILENO, &tty);

//     /* we want to reenable echo */
//     tty.c_lflag |= ECHO;

//     tcsetattr(STDIN_FILENO, TCSANOW, &tty);
// }

#endif
