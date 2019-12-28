#include "cpsc_token.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int * p_token_value_ = malloc(sizeof(int));
    *p_token_value_ = 5;
    Token_T token = Token(TOKEN_INT, p_token_value_);
    static char buf[256u];
    int res;
    res = Token_String(&token, buf, sizeof(buf));
    printf("TEST\n");
    printf("TOKEN res: %d, contents: %s\n", res,  buf);
    free(p_token_value_);

    return 0;
}
