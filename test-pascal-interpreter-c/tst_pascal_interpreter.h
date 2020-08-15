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

typedef struct Calc_Assert_Tag
{
    std::string expr;
    Psc_Int_T expected_res;

} Calc_Assert_T;

TEST(pascal_psc_interpreter, pascal_psc_interpreter_mul)
{
    const Calc_Assert_T calc_asserts[] = {
        {"2*5",     10},
        {"2+2*2",   6},
    };

    for (auto && calc_assert: calc_asserts)
    {
        auto expr_text = calc_assert.expr;
        Psc_Lexer_T lexer = Psc_Lexer(expr_text.c_str(), expr_text.size());

        Psc_Interpreter_T interpreter = Psc_Interpreter_Construct(&lexer);
        Psc_Int_T              val         = 0;
        val                           = Psc_Interpreter_Expr(&interpreter);

        std::cout << "PSC_INTERPRETER input: " << interpreter.lexer.text
                  << " res: " << val << std::endl;

        EXPECT_EQ(val, calc_assert.expected_res);
    }
}
