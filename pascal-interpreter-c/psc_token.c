/*******************************************************************************
 * psc_token.c
 *
 *
 * Psc_Token types
 *
 * EOF (end-of-file) psc_token is used to indicate that
 * there is no more input left for lexical analysis
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "psc_token.h"
#include "stdio.h"

/*******************************************************************************
 * Define Macros
 ******************************************************************************/
#define N_ELEMS(el) (sizeof(el) / sizeof((el)[0u]))

/*******************************************************************************
 * Function-Like Macros
 ******************************************************************************/

/*******************************************************************************
 * Type Declarations
 ******************************************************************************/

/*******************************************************************************
 * Object Declarations
 ******************************************************************************/
static const char *psc_token_names[] = {
    PSC_TOKEN_TYPE_X_FOREACH(PSC_TOKEN_X_STR)};

/*******************************************************************************
 * Functions Declarations
 ******************************************************************************/

/*******************************************************************************
 * Functions Definitions
 ******************************************************************************/
Psc_Token_T Psc_Token(Psc_Token_Type_T type, void *value_)
{
    Psc_Token_T obj = {0};
    obj.type        = type;
    obj.value_      = value_;
    return obj;
}

int Psc_Token_String(const Psc_Token_T *self_, char *buf_, size_t bufsize)
{
    void *      val_ = self_->value_;
    const char *psc_token_enum_name;

    if (NULL == self_)
    {
        return -1;
    }

    /** convert psc_token enum to string */
    if (self_->type < N_ELEMS(psc_token_names))
    {
        psc_token_enum_name = psc_token_names[self_->type];
    }
    else /** psc_token not in psc_token enum - str repr psc_token_enum_name not
            avaiable */
    {
        return -2;
    }

    switch (self_->type)
    {
    case PSC_TOKEN_INT:
    {
        int int_val = *((int *)val_);
        return snprintf(buf_, bufsize, "Psc_Token(%s, %d)", psc_token_enum_name,
                        int_val);
    }

    case PSC_TOKEN_MUL:
    case PSC_TOKEN_DIV:
    {
        char char_val = *((char *)val_);
        return snprintf(buf_, bufsize, "Psc_Token(%s, %c)", psc_token_enum_name,
                        char_val);
    }

    case PSC_TOKEN_EOF:
        return snprintf(buf_, bufsize, "Psc_Token(%s)", psc_token_enum_name);

    default:
        return -3;
    }
}

/*******************************************************************************
 * End psc_token.c
 ******************************************************************************/
