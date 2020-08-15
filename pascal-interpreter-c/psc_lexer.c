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
/**
 * @brief _Psc_Lexer_Error
 * @param self
 * @param fmt
 */
static void _Psc_Lexer_Error(Psc_Lexer_T *self, const char *fmt, ...);

/**
 * @brief _Psc_Lexer_Print
 * @param self
 * @param fmt
 */
static void _Psc_Lexer_Print(const Psc_Lexer_T *self, const char *fmt, ...);

/**
 * @brief _Psc_Lexer_vPrint
 * @param self
 * @param fmt
 * @param args
 */
static void _Psc_Lexer_vPrint(const Psc_Lexer_T *self, const char *fmt,
                              va_list args);

/**
 * @brief _Psc_Lexer_Skip_Whitespace
 * @param self
 */
static void _Psc_Lexer_Skip_Whitespace(Psc_Lexer_T *self);

/**
 * @brief _Psc_Lexer_Advance
 * @param self
 */
static void _Psc_Lexer_Advance(Psc_Lexer_T *self);

/**
 * @brief _Psc_Lexer_Integer
 * @param self
 * @return
 */
static Psc_Int_T _Psc_Lexer_Integer(Psc_Lexer_T *self);

/**
 * @brief _Psc_Lexer_Get_Char_Token
 * @param self
 * @return
 */
Psc_Token_T _Psc_Lexer_Get_Char_Token(Psc_Lexer_T *self);

/**
 * @brief _Psc_Lexer_Set_Pos
 * @param pos
 */
void _Psc_Lexer_Set_Pos(Psc_Lexer_T *self, size_t pos);

/*******************************************************************************
 * Private Functions Definitions
 ******************************************************************************/
/* TODO: move logging to separate file */
static void _Psc_Lexer_Error(Psc_Lexer_T *self, const char *fmt, ...)
{
    va_list args;

    printf("PSC Lexer Error: ");

    va_start(args, fmt);
    _Psc_Lexer_vPrint(self, fmt, args);
    va_end(args);

    self->eof = true;

    abort();
}

static void _Psc_Lexer_vPrint(const Psc_Lexer_T *self, const char *fmt,
                              va_list args)
{
    (void)self;
    vprintf(fmt, args);
    printf("\n");
    fflush(stdout);
}

static void _Psc_Lexer_Print(const Psc_Lexer_T *self, const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    _Psc_Lexer_vPrint(self, fmt, args);
    va_end(args);

    printf("\n");
}

static void _Psc_Lexer_Skip_Whitespace(Psc_Lexer_T *self)
{
    while (!self->eof && isspace(self->current_char))
    {
        _Psc_Lexer_Advance(self);
    }
}

static void _Psc_Lexer_Advance(Psc_Lexer_T *self)
{
    _Psc_Lexer_Set_Pos(self, self->pos + 1);
}

static Psc_Int_T _Psc_Lexer_Integer(Psc_Lexer_T *self)
{
    char *      strtol_char_ptr_;
    const char *current_char_ptr_ = &(self->text[self->pos]);
    Psc_Int_T        val;

    if (self->eof || !isdigit(self->current_char))
    {
        _Psc_Lexer_Error(self, "end of file");
        return 0;
    }

    val = strtol(current_char_ptr_, &strtol_char_ptr_, 10);
    if (NULL != strtol_char_ptr_ && strtol_char_ptr_ != current_char_ptr_)
    {
        _Psc_Lexer_Set_Pos(
            self, self->pos + (size_t)(strtol_char_ptr_ - current_char_ptr_));
        return val;
    }
    else
    {
        _Psc_Lexer_Error(self, "integer conversion failed");
        return 0;
    }
}

void _Psc_Lexer_Set_Pos(Psc_Lexer_T *self, size_t pos)
{
    self->pos = pos;

    if (self->pos >= self->text_length || '\0' == self->text[self->pos])
    {
        self->current_char = '\0';
        self->eof          = true;
    }
    else
    {
        self->current_char = self->text[self->pos];
    }
}
/*******************************************************************************
 * Functions Definitions
 ******************************************************************************/
Psc_Lexer_T Psc_Lexer(const char *text, size_t text_length)
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
    Psc_Token_T res = Psc_Token_Eof();
    (void)self;

    /** error handling */
    if (NULL == self)
    {
        _Psc_Lexer_Print(self, "self argument is null.");
        return Psc_Token_Eof();
    }
    if (self->eof)
    {
        //_Psc_Lexer_Print(self, "end of file.");
        return Psc_Token_Eof();
    }

    /** tokenize */
    if (isspace(self->current_char))
    {
        _Psc_Lexer_Skip_Whitespace(self);
    }

    if (isdigit(self->current_char))
    {
        Psc_Token_Value_T token_value;
        token_value.v_int = _Psc_Lexer_Integer(self);
        res      = Psc_Token(PSC_TOKEN_INT, token_value);
    }
    else
    {
        /* char token */
        res = _Psc_Lexer_Get_Char_Token(self);
    }

    if (PSC_TOKEN_EOF == res.type)
    {
        _Psc_Lexer_Error(self, "unhandled character: %c", self->current_char);
    }

    return res;
}

Psc_Token_T _Psc_Lexer_Get_Char_Token(Psc_Lexer_T *self)
{
    const char current_char = self->current_char;
    Psc_Token_Value_T token_value;
    token_value.v_char = current_char;
    switch (current_char)
    {
        case '*':
        {
            _Psc_Lexer_Advance(self);
            return Psc_Token(PSC_TOKEN_MUL, token_value);
        }
        case '/':
        {
            _Psc_Lexer_Advance(self);
            return Psc_Token(PSC_TOKEN_DIV, token_value);
        }
        case '+':
        {
            _Psc_Lexer_Advance(self);
            return Psc_Token(PSC_TOKEN_ADD, token_value);
        }
        case '-':
        {
            _Psc_Lexer_Advance(self);
            return Psc_Token(PSC_TOKEN_SUB, token_value);
        }
        default:
        {
            return Psc_Token_Eof();
        }
    }
}

/*******************************************************************************
 * End psc_lexer.c
 ******************************************************************************/
