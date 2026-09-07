#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define MAX_PASS 256
#define PERMS 0660

struct Passwd
{
    char *key; //what you'll use to access this password...so no intruder can see it...
    char *password;
};

struct Passwd* new_password(char *key, char *password)
{
    struct Passwd *psk = (struct Passwd*)malloc(sizeof(struct Passwd));
    psk->key = strdup(key);
    psk->password = strdup(password);
    return psk;
}

[[maybe_unused]]static struct Passwd *passwords[MAX_PASS];

int main([[maybe_unused]]int ac, [[maybe_unused]]char *av[], [[maybe_unused]]char *ev[])
{
    [[maybe_unused]]struct Passwd* (*np)(char*, char*) = &new_password; //i just felt like using a function pointer lmao
    char *home_dir = getenv("HOME");
    size_t dest_file_size = strlen(home_dir) + strlen("/.passwds") + 1;
    char dest_file[dest_file_size];
    if (!home_dir) { return 2; }
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
    const char pass[] = "Enter a password: ";
    char pass_buf[256];
    (void)write(1, pass, sizeof(pass) - 1);
    (void)read(0, pass_buf, 256);
    close(pass_file);
    return 0;
}
