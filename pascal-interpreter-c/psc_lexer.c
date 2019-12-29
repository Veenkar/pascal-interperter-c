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
#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************
 * Define Macros
 ******************************************************************************/
#define PSC_LEXER_INT_STR_BUF_SIZE    64u

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

static int _Psc_Lexer_Integer(Psc_Lexer_T *self);

/*******************************************************************************
 * Private Functions Definitions
 ******************************************************************************/
static void _Psc_Lexer_Skip_Whitespace(Psc_Lexer_T *self)
{
    while (!self->eof && isspace(self->current_char)) {
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
        self->eof = true;
    }
    else
    {
        self->current_char = self->text[self->pos];
    }
}

static int _Psc_Lexer_Integer(Psc_Lexer_T *self)
{
    char buf[PSC_LEXER_INT_STR_BUF_SIZE];
    size_t buf_pos = 0;
    int res;

    while (!self->eof && isdigit(self->current_char))
    {
        if (buf_pos >= PSC_LEXER_INT_STR_BUF_SIZE - 1)
        {
            buf[PSC_LEXER_INT_STR_BUF_SIZE - 1] = '\0';
            printf("Psc_Lexer error: integer %s... to big", buf);
            self->eof = true;
            return 0;
        }
        buf[buf_pos++] = self->current_char;
    }
    buf[buf_pos] = '\0';


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
        obj.eof = true;
        obj.current_char = '\0';
    }
    else
    {
        obj.eof = false;
        obj.current_char = text[0];
    }



    return obj;
}


Psc_Token_T Psc_Lexer_Get_Next_Token(Psc_Lexer_T * self)
{
    /** error handling */
    if (NULL == self)
    {
        printf("Psc_Lexer error: self argument is null.");
        return Psc_Token_Eof();
    }
    if (self->eof)
    {
        printf("Psc_Lexer: end of file.");
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

    printf("Psc_Lexer error: unhandled character: %c", self->current_char);
    return Psc_Token_Eof();

}


/*******************************************************************************
 * End psc_lexer.c
 ******************************************************************************/
