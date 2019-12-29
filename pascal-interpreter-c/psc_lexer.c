/*******************************************************************************
 * psc_lexer.c
 *
 *
 *
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
/* project */
#include "psc_lexer.h"

/* system */
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************
 * Define Macros
 ******************************************************************************/
#define PSC_LEXER_INT_STR_BUF_SIZE 64u

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
static void _Psc_Lexer_Skip_Whitespace(Psc_Lexer_T *self);

static void _Psc_Lexer_Advance(Psc_Lexer_T *self);

static long _Psc_Lexer_Integer(Psc_Lexer_T *self);

static void _Psc_Lexer_Error(Psc_Lexer_T *self, const char *fmt, ...);

/*******************************************************************************
 * Private Functions Definitions
 ******************************************************************************/
static void _Psc_Lexer_Skip_Whitespace(Psc_Lexer_T *self)
{
    while (!self->eof && isspace(self->current_char))
    {
        _Psc_Lexer_Advance(self);
    }
}

static void _Psc_Lexer_Advance(Psc_Lexer_T *self)
{
    if (self->eof)
    {
        return;
    }

    ++(self->pos);
    if (self->pos >= self->text_length)
    {
        self->current_char = '\0';
        self->eof          = true;
    }
    else
    {
        self->current_char = self->text[self->pos];
    }
}

static long _Psc_Lexer_Integer(Psc_Lexer_T *self)
{
    char *strtol_char_ptr_;
    char *current_char_ptr_ = &(self->text[self->pos]);
    long  val;

    if (!self->eof || !isdigit(self->current_char))
    {
        _Psc_Lexer_Error(self, "end of file");
        self->eof = true;
        return 0;
    }

    if (!self->eof || !isdigit(self->current_char))
    {
        _Psc_Lexer_Error(self, "end of file");
        self->eof = true;
        return 0;
    }

    val = strtol(current_char_ptr_, &strtol_char_ptr_, 10);
    if (NULL != strtol_char_ptr_ && strtol_char_ptr_ != current_char_ptr_)
    {
        self->pos = (size_t)(strtol_char_ptr_ - current_char_ptr_);
        return val;
    }
    else
    {
        _Psc_Lexer_Error(self, "integer conversion failed");
        return 0;
    }
}

static void _Psc_Lexer_Error(Psc_Lexer_T *self, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    printf(fmt, args);
    self->eof = true;

    va_end(args);
}

/*******************************************************************************
 * Functions Definitions
 ******************************************************************************/
Psc_Lexer_T Psc_Lexer(char *text, size_t text_length)
{
    Psc_Lexer_T obj = {0};
    obj.text        = text;
    obj.text_length = text_length;
    obj.pos         = 0;

    if (NULL == text || text_length <= 0)
    {
        obj.eof          = true;
        obj.current_char = '\0';
    }
    else
    {
        obj.eof          = false;
        obj.current_char = text[0];
    }


    return obj;
}


Psc_Token_T Psc_Lexer_Get_Next_Token(Psc_Lexer_T *self)
{
    /** error handling */
    if (NULL == self)
    {
        _Psc_Lexer_Error(self, "self argument is null.");
        return Psc_Token_Eof();
    }
    if (self->eof)
    {
        _Psc_Lexer_Error(self, "end of file.");
        return Psc_Token_Eof();
    }

    /** tokenize */
    if (isspace(self->current_char))
    {
        _Psc_Lexer_Skip_Whitespace(self);
    }
    if (isdigit(self->current_char))
    {
        return Psc_Token(PSC_TOKEN_INT, _Psc_Lexer_Integer(self));
    }

    _Psc_Lexer_Error(self, "unhandled character: %c", self->current_char);

    return Psc_Token_Eof();
}


/*******************************************************************************
 * End psc_lexer.c
 ******************************************************************************/
