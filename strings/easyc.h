#include <stddef.h>
#include <stdint.h>

#define BUFSIZE 64

typedef struct string {
        size_t cap;
        size_t len;
        char str[];
} string_t;

string_t *string_new(const char *str);
string_t *string_append(string_t *s, const char *str);
