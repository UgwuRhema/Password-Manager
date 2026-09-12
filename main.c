#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
#include "pass.h"

#define MAX_PASS 256
#define PERMS 0600

[[maybe_unused]]static struct Passwd *passwords[MAX_PASS];

int main([[maybe_unused]]int ac, [[maybe_unused]]char *av[], [[maybe_unused]]char *ev[])
{
    [[maybe_unused]]struct Passwd* (*np)(char*, char*, char*, int) = &new_password; //i just felt like using a function pointer lmao
    char *home_dir = getenv("HOME");
    if (!home_dir) { return 139; }
    size_t dest_file_size = strlen(home_dir) + strlen("/.passwds") + 1;
    char dest_file[dest_file_size];
    _Bool running = true;
    [[maybe_unused]]int pass_count = 0;

    const char intro[] = "===PASSWORD MANAGER===\n";
    (void)write(1, intro, sizeof(intro) - 1);
    const char making[] = "Making the passwords file...\n";
    (void)write(1, making, sizeof(making) - 1);
    strcpy(dest_file, home_dir);
    strcat(dest_file, "/.passwds");
    int pass_file = open(dest_file, O_CREAT | O_RDWR, PERMS);
    if (pass_file == -1 )
    {
        const char make_error[] = "failed to create passwords file";
        (void)write(2, make_error, sizeof(make_error) - 1);
        return 2;
    }
    system("chown root:root ~/.passwds"); 
    while (running)
    {
        const char choice_q[] = "Are you creating a new password or you want to view all your passwords? (n/v/e): ";
        (void)write(1, choice_q, sizeof(choice_q) - 1);
        char choice[2];
        int read_r = read(0, choice, 2);
        if (read_r == -1) {return -1;}
        switch(choice[0])
        {
            case 'n':
            case 'N': {
                const char pass[] = "Enter the new password: ";
                char pass_buf[256];
                memset(pass_buf, 0, 256); //unfortunately this almost is unneccesary, kind of
                (void)write(1, pass, sizeof(pass) - 1);
                int bytes_read = read(0, pass_buf, 256);
                if (bytes_read > 0) { pass_buf[bytes_read - 1] = '\0'; }
                const char key[] = "Enter a key(at most 16 characters): ";
                char key_buf[17];
                memset(key_buf, 0, 17);
                (void)write(1, key, sizeof(key) - 1);
                int key_bytes_read = read(0, key_buf, 17);
		        if (key_bytes_read > 0) { key_buf[key_bytes_read - 1] = '\0'; }
                break;
            }
            case 'v':
            case 'V': {
                break;
            }
            case 'e':
            case 'E': {
                (void)write(1, "exiting", 7);
                running  = false;
                break;
            }
            default: {
                const char def[] = "Invalid option, exiting";
                (void)write(2, def, sizeof(def) - 1);
                break;
            }
        }
    }
    close(pass_file);
    return 0;
}
