#pragma once
/*******************************************************************************
 * psc_token.h
 *
 *
 *
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stddef.h>

/*******************************************************************************
 * Define Macros
 ******************************************************************************/
#define PSC_TOKEN_TYPE_X_FOREACH(PSC_TOKEN_X_MACRO)                     \
    PSC_TOKEN_X_MACRO(PSC_TOKEN_INT), PSC_TOKEN_X_MACRO(PSC_TOKEN_MUL), \
        PSC_TOKEN_X_MACRO(PSC_TOKEN_DIV),                               \
        PSC_TOKEN_X_MACRO(PSC_TOKEN_EOF) /* END PSC_TOKEN_TYPE_X_FOREACH */

/*******************************************************************************
 * Function-Like Macros
 ******************************************************************************/
#define PSC_TOKEN_X_ENUM(ENUM_VAL_NAME) ENUM_VAL_NAME

#define PSC_TOKEN_X_STR(STR_CONTENT) #STR_CONTENT

/*******************************************************************************
 * Type Declarations
 ******************************************************************************/
typedef enum Psc_Token_Type_Tag
{
    PSC_TOKEN_TYPE_X_FOREACH(PSC_TOKEN_X_ENUM),
    COUNT_PSC_TOKEN_TYPE

} Psc_Token_Type_T;

typedef struct Psc_Token_Tag
{
    Psc_Token_Type_T type;
    void *           value_;

} Psc_Token_T;

/*******************************************************************************
 * Object Declarations
 ******************************************************************************/

/*******************************************************************************
 * Functions Declarations
 ******************************************************************************/

/*******************************************************************************
 * Functions Definitions
 ******************************************************************************/
/**
 * @brief Psc_Token
 * @param type
 * @param value_
 * @return
 */
Psc_Token_T Psc_Token(Psc_Token_Type_T type, void *value_);

/**
 * @brief Psc_Token_String: string representation of the class instance.
 * @example:
 *   Psc_Token(INTEGER, 3)
 *   Psc_Token(MUL, '*')
 * @param self_
 * @param buf_
 * @param bufsize
 * @return
 */
int Psc_Token_String(const Psc_Token_T *self_, char *buf_, size_t bufsize);

/*******************************************************************************
 * End psc_token.x
 ******************************************************************************/
