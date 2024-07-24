#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include "hash.h"

#define DIGEST_NAME "SHA512"

hash_t *hash_new(char *message)
{
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len;

    md = EVP_get_digestbyname(DIGEST_NAME);
    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex2(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, message, strlen((const char *) message));
    EVP_DigestFinal_ex(mdctx, md_value, &md_len);
    EVP_MD_CTX_free(mdctx);

    unsigned char *content = (unsigned char *) malloc(sizeof(unsigned char)
            * md_len);
    memcpy(content, md_value, md_len);
    hash_t *hash = (hash_t *) malloc(sizeof(hash_t));
    hash->content = content;
    hash->len = md_len;
    return hash;
}

void hash_free(hash_t *hash)
{
    free(hash->content);
    free(hash);
}


