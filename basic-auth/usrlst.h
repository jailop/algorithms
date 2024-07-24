#ifndef _USRLST_H
#define _USRLST_H 1

#include <vector>
#include <string>

using namespace std;

class User {
public:
    User(string username, string password, string salt = ""):
        _username(username), _password(password), _salt(salt) {}
    const char *getUsername();
    const char *getPassowrd();
    const char *hashUsername();
    const char *hashPassword();
private:
    string _username;
    string _password;
    string _salt;
};

class UserList {
public:
    UserList(const char *_salt): salt(_salt) {};
    bool load(const char *filename);
    void print();
    bool digest(const char *filename); 
private:
    const char *salt;
    vector<User> list;
};

#endif // _LISTMGR_H
