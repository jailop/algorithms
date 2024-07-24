#include <stdio.h>
#include <stdlib.h>
#include "easyc.h"

int main() {
        string_t *s = string_new("Hello, world!");
        for (size_t i = 0; i < 10030000; i++)
                s = string_append(s, " another time");
        free(s);
        return 0;
}
