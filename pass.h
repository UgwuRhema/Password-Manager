#define MAX_PASS 256

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

