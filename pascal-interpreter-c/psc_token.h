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
/* system */
#include <stddef.h>

/*******************************************************************************
 * Define Macros
 ******************************************************************************/
/* clang-format off */
#define PSC_TOKEN_TYPE_X_FOREACH(PSC_TOKEN_X_MACRO)         \
    PSC_TOKEN_X_MACRO(PSC_TOKEN_INT, PSC_TOKEN_MEM_INT),    \
    PSC_TOKEN_X_MACRO(PSC_TOKEN_MUL, PSC_TOKEN_MEM_CHAR),   \
    PSC_TOKEN_X_MACRO(PSC_TOKEN_DIV, PSC_TOKEN_MEM_CHAR),   \
    PSC_TOKEN_X_MACRO(PSC_TOKEN_ADD, PSC_TOKEN_MEM_CHAR),   \
    PSC_TOKEN_X_MACRO(PSC_TOKEN_SUB, PSC_TOKEN_MEM_CHAR),   \
    PSC_TOKEN_X_MACRO(PSC_TOKEN_EOF, PSC_TOKEN_MEM_NULL)    \
/* END PSC_TOKEN_TYPE_X_FOREACH */
/* clang-format on */

/*******************************************************************************
 * Function-Like Macros
 ******************************************************************************/
#define PSC_TOKEN_X_ENUM(ENUM_valNAME, ...) ENUM_valNAME

#define PSC_TOKEN_X_STR(STR_CONTENT, ...) #STR_CONTENT

#define PSC_TOKEN_X_ENUM_2(SKIP_0, ENUM_valNAME, ...) ENUM_valNAME

/*******************************************************************************
 * Type Declarations
 ******************************************************************************/
typedef long Psc_Int_T;
typedef char Psc_Char_T;

typedef enum Psc_Token_Mem_Tag
{
    PSC_TOKEN_MEM_INT,
    PSC_TOKEN_MEM_CHAR,
    PSC_TOKEN_MEM_STR,
    PSC_TOKEN_MEM_NULL,
    COUNT_PSC_TOKEN_MEM

} Psc_Token_Mem_T;

typedef enum Psc_Token_Type_Tag
{
    PSC_TOKEN_TYPE_X_FOREACH(PSC_TOKEN_X_ENUM),
    COUNT_PSC_TOKEN_TYPE

} Psc_Token_Type_T;

typedef union Psc_Token_Value_Tag
{
    Psc_Int_T   v_int;
    Psc_Char_T  v_char;
    char *      v_str;

} Psc_Token_Value_T;

typedef struct Psc_Token_Tag
{
    Psc_Token_Type_T    type;
    Psc_Token_Value_T   value;

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
 * @brief Psc_Token_Construct
 * @param type
 * @param value
 * @return
 */
Psc_Token_T Psc_Token_Construct(Psc_Token_Type_T type, Psc_Token_Value_T value);

/**
 * @brief Psc_Token_Descruct
 * @param self
 */
void Psc_Token_Descruct(Psc_Token_T *self);

/**
 * @brief Psc_Token_Eof
 * @return
 */
Psc_Token_T Psc_Token_Eof(void);

/**
 * @brief Psc_Token_String: string representation of the class instance.
 * @example:
 *   Psc_Token(INTEGER, 3)
 *   Psc_Token(MUL, '*')
 * @param self
 * @param buf_
 * @param bufsize
 * @return
 */
int Psc_Token_To_String(const Psc_Token_T *self, char *buf_, size_t bufsize);

/**
 * @brief Psc_Token_Get_Memtype
 * @param self
 * @return
 */
Psc_Token_Mem_T Psc_Token_Get_Memtype(const Psc_Token_T * self);

/*******************************************************************************
 * End psc_token.x
 ******************************************************************************/
