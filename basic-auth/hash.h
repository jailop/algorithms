#ifndef _HASH_H
#define _HASH_H 1

typedef struct {
    unsigned char *content;
    unsigned int len;
} hash_t;

hash_t *hash_new(char *message);
void hash_free(hash_t *hash); 

#endif // _HASH_H:w
