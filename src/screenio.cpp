#include<stdio.h>
#include<unistd.h>
#include<termios.h>
#include"screenio.hpp"


namespace gol
{
    void ScreenIO::initTty()
    {
        backupTty();
        fflush(nullptr);

        ANSIES(ASB);

        getTty();
        tty.c_lflag &= ~ICANON;
        tty.c_lflag &= ~ECHO;
        setTty();

        return;
    }

    void ScreenIO::uninitTty()
    {
        fflush(nullptr);
        ANSIES(MSB);

        restoreTty();

        return;
    }

    void ScreenIO::getTty()
    {
        tcgetattr(STDIN_FILENO, &tty);

        return;
    }

    void ScreenIO::setTty()
    {
        tcsetattr(STDIN_FILENO, TCSANOW, &tty);

        return;
    }

    // void ScreenIO::setStdinEcho(const bool echo)
    // {
    //     if(echo) tty.c_lflag &= ~ECHO;  // Disable
    //     else     tty.c_lflag |= ~ECHO;  // Enable

    //     return;
    // }

    void ScreenIO::backupTty()
    {
        tcgetattr(STDIN_FILENO, &otty);

        return;
    }

    void ScreenIO::restoreTty()
    {
        tcsetattr(STDIN_FILENO, TCSANOW, &otty);

        return;
    }
}
