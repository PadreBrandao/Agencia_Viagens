#include <stdio.h>
#include <unistd.h>
#ifdef _WIN32
    #include <conio.h>
    #define OS "Windows"
    #define Clear "cls"
#else
    #include <termios.h>
    #define OS "Mac" // Assuming you're running on macOS for this example
    #define Clear "clear"
#endif

// Function to disable echo (only for Unix-like systems)
#ifndef _WIN32
void disable_echo(struct termios *old_tio) {
    struct termios new_tio;

    tcgetattr(STDIN_FILENO, old_tio);
    new_tio = *old_tio;
    new_tio.c_lflag &= ~(ECHO | ECHONL);

    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
}

// Function to enable echo (only for Unix-like systems)
void enable_echo(struct termios *old_tio) {
    tcsetattr(STDIN_FILENO, TCSANOW, old_tio);
}
#endif

// Function to get password without echoing input
void get_password(char *password, size_t size) {
    printf("Password: ");
    fflush(stdout);

    size_t i = 0;
    char ch;
#ifdef _WIN32
    while (i < size - 1 && (ch = _getch()) != '\r') {
        if (ch == 8) { // Handle backspace (ASCII 8)
            if (i > 0) {
                printf("\b \b");
                fflush(stdout);
                i--;
            }
        } else {
            password[i++] = ch;
            printf("*");
            fflush(stdout);
        }
    }
#else
    struct termios old_tio;
    disable_echo(&old_tio);

    while (i < size - 1 && read(STDIN_FILENO, &ch, 1) == 1 && ch != '\n') {
        if (ch == 127) { // Handle backspace (ASCII 127)
            if (i > 0) {
                printf("\b \b");
                fflush(stdout);
                i--;
            }
        } else {
            password[i++] = ch;
            printf("*");
            fflush(stdout);
        }
    }
    enable_echo(&old_tio);
#endif
    password[i] = '\0';
    printf("\n");
}