#pragma once

extern "C"
{
    #include "psc_token.h"
}

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <string.h>

using namespace testing;

TEST(pascal_psc_token, pascal_psc_token_str)
{
    Psc_Token_T psc_token;
    static const int psc_token_value = 5;

    /** CONSTRUCT INT PSC_TOKEN */
    {
        int * p_psc_token_value_ = (int*)malloc(sizeof(int));
        *p_psc_token_value_ = psc_token_value;
        psc_token = Psc_Token(PSC_TOKEN_INT, p_psc_token_value_);
        EXPECT_NE(nullptr, psc_token.value_);
        EXPECT_EQ(psc_token.type, PSC_TOKEN_INT);
    }

    /** STRINGIFY */
    {
        static char buf[256u];
        int res = Psc_Token_String(&psc_token, buf, sizeof(buf));
        EXPECT_GT(res, 0);
        printf("TEST\n");
        printf("PSC_TOKEN res: %d, contents: %s\n", res,  buf);
        std::stringstream search_str_stream;
        search_str_stream << psc_token_value;
        std::string search_str (search_str_stream.str());
        EXPECT_NE(std::string::npos, std::string(buf).find(search_str));
    }

    /** DESTRUCT */
    free(psc_token.value_);
    psc_token.value_ = nullptr;
}

