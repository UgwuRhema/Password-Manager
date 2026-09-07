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
    const char *home_dir = strdup(getenv("$HOME"));
    (void)write(1, home_dir, strlen(home_dir));
    const char intro[] = "===PASSWORD MANAGER===\n";
    (void)write(1, intro, sizeof(intro) - 1);
    const char making[] = "Making the passwords file...\n";
    (void)write(1, making, sizeof(making) - 1);
    /* if (open("", O_CREAT | O_RDWR, PERMS) != )
    {
        const char make_error[] = "failed to create passwords file";
        (void)write(2, make_error, sizeof(make_error) - 1);
        return 2;
    }
    */
    sleep(2);
    free((void*)home_dir);
    return 0;
}
