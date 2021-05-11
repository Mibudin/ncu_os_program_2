#include<stdio.h>
#include<unistd.h>
#include<termios.h>
#include"screenio.hpp"


namespace gol
{
    void Screenio::initTty()
    {
        backupTty();
        fflush(nullptr);

        ANSIES(ASB);

        getTty();
        tty.c_lflag &= ~ICANON;
        tty.c_lflag &= ~ECHO;
        setTty();

        ANSIES(CUH ED(2) CUP(1,1));

        return;
    }

    void Screenio::uninitTty()
    {
        ANSIES(CUS);

        fflush(nullptr);
        ANSIES(MSB);

        restoreTty();

        return;
    }

    void Screenio::getTty()
    {
        tcgetattr(STDIN_FILENO, &tty);

        return;
    }

    void Screenio::setTty()
    {
        tcsetattr(STDIN_FILENO, TCSANOW, &tty);

        return;
    }

    // void Screenio::setStdinEcho(const bool echo)
    // {
    //     if(echo) tty.c_lflag &= ~ECHO;  // Disable
    //     else     tty.c_lflag |= ~ECHO;  // Enable

    //     return;
    // }

    void Screenio::backupTty()
    {
        tcgetattr(STDIN_FILENO, &otty);

        return;
    }

    void Screenio::restoreTty()
    {
        tcsetattr(STDIN_FILENO, TCSANOW, &otty);

        return;
    }
}
