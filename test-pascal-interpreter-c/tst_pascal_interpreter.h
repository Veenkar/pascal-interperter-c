#pragma once

extern "C"
{
#include "psc_interpreter.h"
}

#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include <string.h>
#include <stdio.h>

using namespace testing;

TEST(pascal_psc_interpreter, pascal_psc_interpreter_mul)
{
#define PSC_MUL_TEST_TEXT "2*5"
    const char *text  = PSC_MUL_TEST_TEXT;
    Psc_Lexer_T lexer = Psc_Lexer(text, sizeof(PSC_MUL_TEST_TEXT));
#undef PSC_MUL_TEST_TEXT
    Psc_Interpreter_T interpreter = Psc_Interpreter_Construct(&lexer);
    long              val         = 0;
    val                           = Psc_Interpreter_Expr(&interpreter);

    std::cout << "PSC_INTERPRETER input: " << interpreter.lexer.text
              << " res: " << val << std::endl;
    Psc_Interpreter_Destruct(&interpreter);

    EXPECT_EQ(val, 10);
}
