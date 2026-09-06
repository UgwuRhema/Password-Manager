#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define MAX_PASS 256

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

int main([[maybe_unused]]int ac, [[maybe_unused]]char **av)
{
    const char intro[] = "===PASSWORD MANAGER===\n";
    (void)write(1, intro, sizeof(intro) - 1);
    const char making[] = "Making the passwords file...\n";
    (void)write(1, making, sizeof(making) - 1);
    sleep(2);
    return 0;
}
