/*******************************************************************************
 * file.x
 *
 *
 *
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "psc_interpreter.h"

/* system */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************
 * Define Macros
 ******************************************************************************/

/*******************************************************************************
 * Function-Like Macros
 ******************************************************************************/

/*******************************************************************************
 * Type Declarations
 ******************************************************************************/

/*******************************************************************************
 * Object Declarations
 ******************************************************************************/

/*******************************************************************************
 * Functions Declarations
 ******************************************************************************/
static void _Psc_Interpreter_Eat(Psc_Interpreter_T *    self,
                                 const Psc_Token_Type_T token_type);

/**
 * @brief _Psc_Lexer_Error
 * @param self
 * @param fmt
 */
static void _Psc_Interpreter_Error(Psc_Interpreter_T *self, const char *fmt,
                                   ...);

/**
 * @brief _Psc_Lexer_Print
 * @param self
 * @param fmt
 */
static void _Psc_Interpreter_Print(const Psc_Interpreter_T *self,
                                   const char *             fmt, ...);

/**
 * @brief _Psc_Interpreter_vPrint
 * @param self
 * @param fmt
 * @param arg
 */
static void _Psc_Interpreter_vPrint(const Psc_Interpreter_T *self,
                                    const char *fmt, va_list arg);

/*******************************************************************************
 * Private Functions Definitions
 ******************************************************************************/
static void _Psc_Interpreter_Print(const Psc_Interpreter_T *self,
                                   const char *             fmt, ...)
{
    va_list args;
    (void)self;

    va_start(args, fmt);
    _Psc_Interpreter_vPrint(self, fmt, args);
    va_end(args);
}

static void _Psc_Interpreter_vPrint(const Psc_Interpreter_T *self,
                                    const char *fmt, va_list args)
{
    (void)self;
    vprintf(fmt, args);
    printf("\n");
    fflush(stdout);
}

static void _Psc_Interpreter_Error(Psc_Interpreter_T *self, const char *fmt,
                                   ...)
{
    va_list args;

    printf("PSCI Error: ");

    va_start(args, fmt);
    _Psc_Interpreter_Print(self, fmt, args);
    va_end(args);

    self->lexer.eof = true;
    abort();
}

static void _Psc_Interpreter_Eat(Psc_Interpreter_T *    self,
                                 const Psc_Token_Type_T token_type)
{
    if (token_type == self->current_token.type)
    {
        self->current_token = Psc_Lexer_Get_Next_Token(&self->lexer);
    }
    else
    {
        _Psc_Interpreter_Error(self, "got wrong token type");
    }
}

/*******************************************************************************
 * Functions Definitions
 ******************************************************************************/
Psc_Interpreter_T Psc_Interpreter_Construct(const Psc_Lexer_T *lexer)
{
    Psc_Interpreter_T obj = {0};
    obj.lexer             = *lexer;
    obj.current_token     = Psc_Lexer_Get_Next_Token(&obj.lexer);
    return obj;
}

Psc_Int_T Psc_Interpreter_Factor(Psc_Interpreter_T *self)
{
    Psc_Token_T token;
    Psc_Int_T        value;

    if (PSC_TOKEN_L_PAREN == self->current_token.type)
    {
        _Psc_Interpreter_Eat(self, PSC_TOKEN_L_PAREN);
        value = Psc_Interpreter_Expr(self);
        _Psc_Interpreter_Eat(self, PSC_TOKEN_R_PAREN);
    }
    else
    {
        token = self->current_token;
        _Psc_Interpreter_Eat(self, PSC_TOKEN_INT);
        value = token.value.v_int;
    }

    return value;
}

Psc_Int_T Psc_Interpreter_Term(Psc_Interpreter_T *self)
{
    Psc_Int_T result = Psc_Interpreter_Factor(self);

    while (PSC_TOKEN_MUL == self->current_token.type ||
           PSC_TOKEN_DIV == self->current_token.type)
    {
        Psc_Token_T token = self->current_token;
        if (PSC_TOKEN_MUL == token.type)
        {
            _Psc_Interpreter_Eat(self, PSC_TOKEN_MUL);
            result = result * Psc_Interpreter_Factor(self);
        }
        else if (PSC_TOKEN_DIV == token.type)
        {
            _Psc_Interpreter_Eat(self, PSC_TOKEN_DIV);
            result = result / Psc_Interpreter_Factor(self);
        }
    }

    return result;
}


Psc_Int_T Psc_Interpreter_Expr(Psc_Interpreter_T *self)
{
    Psc_Int_T result = Psc_Interpreter_Term(self);

    while (PSC_TOKEN_ADD == self->current_token.type ||
           PSC_TOKEN_SUB == self->current_token.type)
    {
        Psc_Token_T token = self->current_token;
        if (PSC_TOKEN_ADD == token.type)
        {
            _Psc_Interpreter_Eat(self, PSC_TOKEN_ADD);
            result = result + Psc_Interpreter_Term(self);
        }
        else if (PSC_TOKEN_SUB == token.type)
        {
            _Psc_Interpreter_Eat(self, PSC_TOKEN_SUB);
            result = result - Psc_Interpreter_Term(self);
        }
    }

    return result;
}


/*******************************************************************************
 * End file.x
 ******************************************************************************/
