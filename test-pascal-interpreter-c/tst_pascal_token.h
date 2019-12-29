#pragma once

extern "C"
{
#include "psc_token.h"
}

#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include <string.h>

using namespace testing;

template <typename T>
void Pascal_Psc_Token_Test(Psc_Token_Type_T token_type, const T token_value)
{
    Psc_Token_T psc_token;

    /** CONSTRUCT INT PSC_TOKEN */
    {
        T *p_psc_token_value_ = (T *)malloc(sizeof(T));
        *p_psc_token_value_   = token_value;
        psc_token             = Psc_Token(token_type, p_psc_token_value_);
        EXPECT_NE(nullptr, psc_token.value_);
        EXPECT_EQ(psc_token.type, token_type);
    }

    /** STRINGIFY */
    {
        static char buf[256u];
        int         res = Psc_Token_To_String(&psc_token, buf, sizeof(buf));
        EXPECT_GT(res, 0);
        std::cout << "PSC_TOKEN res: " << res << ", val: " << std::string(buf)
                  << std::endl;
        std::stringstream search_str_stream;
        search_str_stream << token_value;
        std::string search_str(search_str_stream.str());
        std::cout << "searching for: " << search_str << std::endl;
        EXPECT_NE(std::string::npos, std::string(buf).find(search_str));
    }

    /** DESTRUCT */
    free(psc_token.value_);
    psc_token.value_ = nullptr;
}


TEST(pascal_psc_token, pascal_psc_token_int_str)
{
    Pascal_Psc_Token_Test<int>(PSC_TOKEN_INT, 5);
}

TEST(pascal_psc_token, pascal_psc_token_char_str)
{
    Pascal_Psc_Token_Test<char>(PSC_TOKEN_MUL, '*');
}
