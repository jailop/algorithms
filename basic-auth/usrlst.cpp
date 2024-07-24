#include "usrlst.h"
#include "hash.h"

const char *User::getUsername()
{
    return _username.c_str;
}

const char *User::getPassowrd()
{
    return _password.c_str;
}

const char *User::hashUsername()
{
    string hashed = hash(_username);
    return hashed.c_str;
}

const char *User::hashPassword()
{
    string hashed = hash(_password);
    return hashed.c_str;
}
