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
/* project */
#include "psc_token.h"
#include "stdlib.h"

/* system */
#include <assert.h>
#include <stdio.h>

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
static const char *_psc_token_names[] = {
    PSC_TOKEN_TYPE_X_FOREACH(PSC_TOKEN_X_STR)};

static const Psc_Token_Mem_T _psc_token_mems[] = {
    PSC_TOKEN_TYPE_X_FOREACH(PSC_TOKEN_X_ENUM_2)};


/*******************************************************************************
 * Private Functions Declarations
 ******************************************************************************/
static Psc_Token_Mem_T _Psc_Token_Mem(Psc_Token_Type_T token_type);


/**
 * @brief Psc_Token
 * @param type
 * @param value_
 * @return
 */
static Psc_Token_T Psc_Token(Psc_Token_Type_T type, void *value_);

/*******************************************************************************
 * Private Functions Definitions
 ******************************************************************************/

static Psc_Token_T Psc_Token(Psc_Token_Type_T type, void *value_)
{
    Psc_Token_T obj = {0};
    obj.type        = type;
    obj.value_      = value_;
    return obj;
}

Psc_Token_Mem_T _Psc_Token_Mem(Psc_Token_Type_T token_type)
{
    assert(token_type < N_ELEMS(_psc_token_mems));
    return _psc_token_mems[token_type];
}

/*******************************************************************************
 * Functions Definitions
 ******************************************************************************/
Psc_Token_T Psc_Token_Construct(Psc_Token_Type_T type, const void *value_)
{
    Psc_Token_T           obj           = Psc_Token(type, NULL);
    const Psc_Token_Mem_T token_memtype = _Psc_Token_Mem(type);

    switch (token_memtype)
    {
        case PSC_TOKEN_MEM_INT:
        {
            long *value_mem_ = (long *)malloc(sizeof(long));
            *value_mem_      = *(const long *)value_;
            obj.value_       = value_mem_;
            break;
        }

        case PSC_TOKEN_MEM_CHAR:
        {
            char *value_mem_ = (char *)malloc(sizeof(char));
            *value_mem_      = *(const char *)value_;
            obj.value_       = value_mem_;
            break;
        }

        case PSC_TOKEN_MEM_NULL:
        default:
            /* TODO: add error handling (error + abort) here */
            obj.value_ = NULL;
            break;
    }

    return obj;
}

void Psc_Token_Descruct(Psc_Token_T *self)
{
    if (NULL != self->value_)
    {
        // free(self->value_);
    }
    self->value_ = NULL;
}

Psc_Token_T Psc_Token_Eof()
{
    return Psc_Token(PSC_TOKEN_EOF, NULL);
}

int Psc_Token_To_String(const Psc_Token_T *self, char *buf_, size_t bufsize)
{
    void *                val_ = self->value_;
    const char *          psc_token_enum_name;
    const Psc_Token_Mem_T token_memtype = _Psc_Token_Mem(self->type);

    if (NULL == self)
    {
        return snprintf(buf_, bufsize, "Psc_Token([nullptr])");
    }

    /** convert psc_token enum to string */
    assert(self->type < N_ELEMS(_psc_token_names));
    psc_token_enum_name = _psc_token_names[self->type];

    switch (token_memtype)
    {
        case PSC_TOKEN_MEM_INT:
        {
            int int_val = *((int *)val_);
            return snprintf(buf_, bufsize, "Psc_Token(%s, %d)",
                            psc_token_enum_name, int_val);
        }

        case PSC_TOKEN_MEM_CHAR:
        {
            char char_val = *((char *)val_);
            return snprintf(buf_, bufsize, "Psc_Token(%s, %c)",
                            psc_token_enum_name, char_val);
        }

        case PSC_TOKEN_MEM_NULL:
        {
            return snprintf(buf_, bufsize, "Psc_Token(%s)",
                            psc_token_enum_name);
        }

        default:
        {
            return snprintf(buf_, bufsize, "Psc_Token([unknown token %d])",
                            self->type);
        }
    }
}

/*******************************************************************************
 * End psc_token.c
 ******************************************************************************/
