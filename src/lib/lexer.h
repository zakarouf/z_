#ifndef ZAKAROUF__Z__LEXER_H
#define ZAKAROUF__Z__LEXER_H

#include "std/primitives.h"

typedef struct z__LexToken z__LexToken;
struct z__LexToken {
    z__byte const *line_start;
    z__byte const *start;
    z__u32 line;
    z__u32 size;
    z__u8  type;
};

typedef struct z__Lexer z__Lexer;
struct z__Lexer {
    z__byte const *begin;
    z__byte const *at;
    z__byte const *end;
    z__LexToken   token;
};

#define z__LexToken_is(t, s) ((t).type == s)
#define z__LexToken_is_not(t, s) (!z__LexToken_is(t, s))

#define z__LexToken_is_valid(t) ((t).type < z__LEXTOKEN_TOTAL)
#define z__LexToken_is_invalid(t) (!z__LexToken_is_valid(t))

#define z__LexToken_is_ws(t) ((t).type == z__LEXTOKEN_SPACE\
                            ||(t).type == z__LEXTOKEN_TABSPACE\
                            ||(t).type == z__LEXTOKEN_NEWLINE)

#define z__LexToken_is_not_ws(t) (!z__LexToken_is_ws(t))

#define TOKEN(x) z__LEXTOKEN_##x
enum z__LexTokenType {
    /* Unknown Token */
      TOKEN(UNKNOWN)

    /* Error  */
    , TOKEN(ERROR)

    /* Defined Token */
    , TOKEN(SPACE)
    , TOKEN(TABSPACE)
    , TOKEN(NEWLINE)

    , TOKEN(PAREN_LEFT), TOKEN(PAREN_RIGHT)
    , TOKEN(BRACE_LEFT), TOKEN(BRACE_RIGHT)
    , TOKEN(SQR_BRACE_LEFT), TOKEN(SQR_BRACE_RIGHT)
                                              
    , TOKEN(COMMA), TOKEN(DOT), TOKEN(COLON), TOKEN(SEMI_COLON), TOKEN(AT)
    , TOKEN(PERCENT), TOKEN(QUOTE), TOKEN(DOUBLE_QUOTE), TOKEN(DOLLAR)
    , TOKEN(HASH), TOKEN(AND), TOKEN(BACK_SLASH), TOKEN(PIPE)
                                              
    /* Single or Multi Character Tokens */    
    , TOKEN(PLUS), TOKEN(MINUS), TOKEN(SLASH), TOKEN(ASTER)
    , TOKEN(PLUS_EQUAL), TOKEN(MINUS_EQUAL)
    , TOKEN(SLASH_EQUAL), TOKEN(ASTER_EQUAL)
                                              
    , TOKEN(BANG), TOKEN(BANG_EQUAL)
    , TOKEN(EQUAL), TOKEN(EQUAL_EQUAL)        
    , TOKEN(GREATER), TOKEN(GREATER_EQUAL)
    , TOKEN(LESS), TOKEN(LESS_EQUAL)
                                
    /* Literals */    
    , TOKEN(SYMBOL)
    , TOKEN(NUMBER), TOKEN(FLOAT)
                      
    /* Keywords */    
    /*
     * NOTE: As per the new spec, keywords are handled by the
     *       individual compiler rather than lexer. So same
     *       lexer can be used for all forms of compilers and transpiler.
    , TOKEN(RETURN)
    , TOKEN(FUNCTION)
    , TOKEN(LET)
    , TOKEN(AND, OR         
    , TOKEN(TRUE, FALSE     
    , TOKEN(IF, ELIF, ELSE  
    , TOKEN(FOR, WHILE      
    */

    /* End of source code passed */                     
    , TOKEN(END_OF_SOURCE)
                                                        
    /* Token Not Found, for internal evaluation and assertion only */ 
    , TOKEN(NOT_FOUND) 
                                                        
    /* Total number of defined tokens */                
    , TOKEN(TOTAL)

};
#undef TOKEN

void z__Lexer_start(z__Lexer* lex, const z__byte *string_data, z__u32 size);
void z__Lexer_next(z__Lexer *lex);
void z__Lexer_next_skipws(z__Lexer *lex);
void z__Lexer_next_until(z__Lexer *lex, enum z__LexTokenType type);
z__bool z__Lexer_next_expect(z__Lexer *lex, enum z__LexTokenType type);
z__bool z__Lexer_tiseq(z__Lexer *lex, char const *string, z__u32 string_size);

#endif

