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
#include "string.h"

/* system */
#include <assert.h>
#include <stdio.h>

/*******************************************************************************
 * Define Macros
 ******************************************************************************/
#define STR_MAX_SIZE    (256u)

/*******************************************************************************
 * Function-Like Macros
 ******************************************************************************/
#define N_ELEMS(el) (sizeof(el) / sizeof((el)[0u]))

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
 * @param value
 * @return
 */
static Psc_Token_T _Psc_Empty_Token(Psc_Token_Type_T type);

/*******************************************************************************
 * Private Functions Definitions
 ******************************************************************************/

static Psc_Token_T _Psc_Empty_Token(Psc_Token_Type_T type)
{
    Psc_Token_T obj = {0};
    obj.type        = type;
    obj.value.v_int = 0;
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
Psc_Token_T Psc_Token_Construct(Psc_Token_Type_T type, Psc_Token_Value_T value)
{
    Psc_Token_T           obj           = _Psc_Empty_Token(type);
    const Psc_Token_Mem_T token_memtype = _Psc_Token_Mem(type);

    switch (token_memtype)
    {
        case PSC_TOKEN_MEM_STR:
        {
            char *valuemem_ = (char *)malloc(STR_MAX_SIZE);
            strncpy(valuemem_, value.v_str, STR_MAX_SIZE);
            obj.value.v_str = valuemem_;
            break;
        }
        case PSC_TOKEN_MEM_NULL:
        {
            /* TODO: add error handling (error + abort) here */
            obj.value.v_int = 0;
            break;
        }
        default:
        {
            obj.value = value;
            break;
        }
    }

    return obj;
}

void Psc_Token_Descruct(Psc_Token_T *self)
{
    const Psc_Token_Mem_T token_memtype = Psc_Token_Get_Memtype(self);
    if ( (token_memtype == PSC_TOKEN_MEM_STR) && (NULL != self->value.v_str) )
    {
        free(self->value.v_str);
    }

    *self = Psc_Token_Eof();
}

Psc_Token_T Psc_Token_Eof()
{
    return _Psc_Empty_Token(PSC_TOKEN_EOF);
}

int Psc_Token_To_String(const Psc_Token_T *self, char *buf_, size_t bufsize)
{


    if (NULL == self)
    {
        return snprintf(buf_, bufsize, "Psc_Token([nullptr])");
    }
    else
    {
        const char *          psc_token_enum_name;
        const Psc_Token_Mem_T token_memtype = Psc_Token_Get_Memtype(self);
        Psc_Token_Value_T     val  = self->value;

        /** convert psc_token enum to string */
        assert(self->type < N_ELEMS(_psc_token_names));
        psc_token_enum_name = _psc_token_names[self->type];

        switch (token_memtype)
        {
            case PSC_TOKEN_MEM_INT:
            {
                Psc_Int_T int_val = val.v_int;
                return snprintf(buf_, bufsize, "Psc_Token(%s, %lu)",
                                psc_token_enum_name, int_val);
            }

            case PSC_TOKEN_MEM_CHAR:
            {
                Psc_Char_T char_val = val.v_char;
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
}

Psc_Token_Mem_T Psc_Token_Get_Memtype(const Psc_Token_T * self)
{
    return _Psc_Token_Mem(self->type);
}

/*******************************************************************************
 * End psc_token.c
 ******************************************************************************/
