#include "easyc.h"
#include <stdlib.h>
#include <string.h>

string_t *string_new(const char *str) {
        size_t cap = BUFSIZE;
        size_t len = strlen(str);
        while (cap <= len + 1) cap *= 2;
        string_t *s = (string_t *) malloc(sizeof(string_t) + sizeof(char)
                * cap);
        *s = (string_t){.cap=cap, .len=len};
        strncpy(s->str, str, len);
        return s;
}

string_t *string_append(string_t *s, const char *str) {
        size_t cap = s->cap;
        size_t len = strlen(str);
        size_t new_len = s->len + len;
        while (cap <= new_len + 1) cap *= 2;
        if (cap != s->cap) {
                string_t *aux = (string_t *) malloc(sizeof(string_t)
                        + sizeof(char) * cap);
                *aux = (string_t) {.cap=cap, .len=s->len};
                strncpy(aux->str, s->str, s->len);
                free(s);
                s = aux;
        }
        strncpy(&(s->str[s->len]), str, strlen(str));
        s->len = new_len;
        return s;
}
