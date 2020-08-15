#pragma once

extern "C"
{
#include "psc_token.h"
}

#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include <string.h>

using namespace testing;

void Pascal_Psc_Token_Test(Psc_Token_Type_T token_type, Psc_Token_Value_T token_value)
{
    Psc_Token_T psc_token;

    /** CONSTRUCT INT PSC_TOKEN */
    {

        psc_token = Psc_Token(token_type, token_value);
        EXPECT_EQ(token_value.v_int, psc_token.value.v_int);
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

        switch (Psc_Token_Get_Memtype(&psc_token))
        {
            case PSC_TOKEN_MEM_INT:
                search_str_stream << token_value.v_int;
                break;
            case PSC_TOKEN_MEM_CHAR:
                search_str_stream << token_value.v_char;
                break;
            default:
                break;
        }



        std::string search_str(search_str_stream.str());
        std::cout << "searching for: " << search_str << std::endl;
        EXPECT_NE(std::string::npos, std::string(buf).find(search_str));
    }
}


TEST(pascal_psc_token, pascal_psc_token_int_str)
{
    Psc_Token_Value_T val;
    val.v_int = 5;
    Pascal_Psc_Token_Test(PSC_TOKEN_INT, val);
}

TEST(pascal_psc_token, pascal_psc_token_char_str)
{
    Psc_Token_Value_T val;
    val.v_char = '*';
    Pascal_Psc_Token_Test(PSC_TOKEN_MUL, val);
}
