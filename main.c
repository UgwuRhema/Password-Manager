#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PASS 256
#define PERMS 0660

struct Passwd
{
    char *key; //what you'll use to access this password...so no intruder can see it...
    char *password;
    char *host;
    int id;
};

struct Passwd* new_password(char *key, char *password, char *host, int id)
{
    struct Passwd *psk = (struct Passwd*)malloc(sizeof(struct Passwd));
    psk->key = strdup(key);
    psk->password = strdup(password);
    psk->host = strdup(host);
    psk->id = id;
    return psk;
}

//add a password to the global list
void addPasswordToList(struct Passwd **list, struct Passwd *password, int *offset)
{
    if (list == NULL || password == NULL || *offset >= MAX_PASS) return;
    list[*offset] = password;
    (*offset)++;
}

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
    while (running)
    {
        const char choice_q[] = "Are you creating a new password or you want to view all your passwords? (n/v/e): ";
        (void)write(1, choice_q, sizeof(choice_q) - 1);
        char choice;
        int read_r = read(0, &choice, 1);
        if (read_r == -1) {return -1;}
        switch(choice)
        {
            case 'n':
            case 'N': {
                const char pass[] = "Enter the new password: ";
                char pass_buf[256];
                memset(pass_buf, 0, 256);
                (void)write(1, pass, sizeof(pass) - 1);
                int bytes_read = read(0, pass_buf, 256);
                pass_buf[bytes_read - 1] = '\0'; 
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
                return 139; 
            }
        }
    }
    close(pass_file);
    return 0;
}
