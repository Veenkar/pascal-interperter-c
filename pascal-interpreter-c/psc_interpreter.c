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

/*******************************************************************************
 * Private Functions Definitions
 ******************************************************************************/
static void _Psc_Interpreter_Print(const Psc_Interpreter_T *self,
                                   const char *             fmt, ...)
{
    va_list args;
    (void)self;

    va_start(args, fmt);

    vprintf(fmt, args);

    va_end(args);
}

static void _Psc_Interpreter_Error(Psc_Interpreter_T *self, const char *fmt,
                                   ...)
{
    va_list args;
    va_start(args, fmt);

    _Psc_Interpreter_Print(self, fmt, args);
    Psc_Token_Descruct(&self->current_token);
    self->lexer.eof = true;
    abort();

    va_end(args);
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

void Psc_Interpreter_Destruct(Psc_Interpreter_T *self)
{
    Psc_Token_Descruct(&self->current_token);
}

long Psc_Interpreter_Factor(Psc_Interpreter_T *self)
{
    Psc_Token_T token;
    long        value;

    token = self->current_token;
    _Psc_Interpreter_Eat(self, PSC_TOKEN_INT);
    value = *((long *)token.value_);
    Psc_Token_Descruct(&token);

    return value;
}

long Psc_Interpreter_Expr(Psc_Interpreter_T *self)
{
    long result = Psc_Interpreter_Factor(self);

    while (PSC_TOKEN_MUL == self->current_token.type ||
           PSC_TOKEN_DIV == self->current_token.type)
    {
        Psc_Token_T token = self->current_token;
        if (PSC_TOKEN_DIV == token.type)
        {
            _Psc_Interpreter_Eat(self, PSC_TOKEN_DIV);
            result = result / Psc_Interpreter_Factor(self);
            Psc_Token_Descruct(&token);
        }
        else if (PSC_TOKEN_MUL == token.type)
        {
            _Psc_Interpreter_Eat(self, PSC_TOKEN_MUL);
            result = result * Psc_Interpreter_Factor(self);
            Psc_Token_Descruct(&token);
        }
    }

    return result;
}


/*******************************************************************************
 * End file.x
 ******************************************************************************/