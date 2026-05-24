/**
z_, Core Language Module with datatypes, memory tracker, and beyond.
Copyright (C) 2025  Zakarouf

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ZAKAROUF__Z__LEXER_H
#define ZAKAROUF__Z__LEXER_H

#include "std/primitives.h"
#include "string.h"
#include "prep/base.h"

typedef struct z__Lexer z__Lexer;
typedef struct z__LexToken z__LexToken;
typedef struct z__LexTokenArr z__LexTokenArr;

struct z__LexToken {
    z__u8 const   *start;
    z__u32         size; 
    // NOTE: 3 Byte Padding
    z__u32          type;
};

struct z__LexTokenArr {
    z__LexToken     *data;
    z__u32          len;
    z__u32          lenUsed;
};

struct z__Lexer {
    z__u8 const   *begin;
    z__u8 const   *at;
    z__u8 const   *end;
    z__LexToken     token;
};

/************************************************************************
 *                              Lex Token Type                          *
 ************************************************************************/
#define TOKEN(x) zpp__CAT(Z__LEXTOKEN_, x)
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
    , TOKEN(QUOTE), TOKEN(DOUBLE_QUOTE), TOKEN(DOLLAR), TOKEN(HASH)
    , TOKEN(PIPE), TOKEN(PERCENT), TOKEN(AND), TOKEN(BACK_SLASH)
                                              
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
                      
    /* String */
    /**
     * NOTE: Lexer does not evaluate string, but does provide a function
     *       to evaluate a double-quoted string, use convert_dq_string
     */
    , TOKEN(STRING) 

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
      #undef TOKEN
};

#define z__LexToken_is(t, s) ((t).type == s)
#define z__LexToken_is_not(t, s) (!z__LexToken_is(t, s))

#define z__LexToken_is_valid(t) ((t).type < Z__LEXTOKEN_TOTAL)
#define z__LexToken_is_invalid(t) (!z__LexToken_is_valid(t))

#define z__LexToken_is_ws(t) ((t).type == Z__LEXTOKEN_SPACE\
                            ||(t).type == Z__LEXTOKEN_TABSPACE\
                            ||(t).type == Z__LEXTOKEN_NEWLINE)

#define z__LexToken_is_not_ws(t) (!z__LexToken_is_ws(t))


void z__Lexer_start(z__Lexer *lex, z__u8 const *data, z__size size);
void z__Lexer_next(z__Lexer *lex);
void z__Lexer_next_skipws(z__Lexer *lex);
void z__Lexer_next_until(z__Lexer *lex, enum z__LexTokenType type);
z__bool z__Lexer_next_expect(z__Lexer *lex, enum z__LexTokenType type);
z__bool z__Lexer_tiseq(z__Lexer *lex, char const *string, z__size string_size);

z__size z__Lexer_line(z__Lexer const *l);
z__size z__Lexer_col(z__Lexer const *l);
z__u8 const *z__Lexer_line_start(z__Lexer const *l);
z__bool z__Lexer_convert_dq_string(z__Lexer *l);
z__CStr z__LexToken_get_name(z__size token_type);


#ifdef Z__IMPLEMENTATION

#define TOKEN(x) [Z__LEXTOKEN_##x] = { .data = (void *)#x, .len = (sizeof(#x) -1) }
static z__CStr const z__TOKEN_NAMES[Z__LEXTOKEN_TOTAL+1] = {
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
    , TOKEN(PIPE), TOKEN(HASH), TOKEN(AND), TOKEN(BACK_SLASH)
                                              
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
                      
    /**/
    , TOKEN(STRING)

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


#define z__Lexer_prev_peek(l) (*(l)->at-1)
#define z__Lexer_peek(s) (*(s)->at)
#define z__Lexer_isend(s) ((s)->at >= (s)->end)
#define z__Lexer_save(lex) ((lex)->at)
#define z__Lexer_load(lex, with) {(lex)->at = (with);}

#define z__Lexer_check(lex, is) ((lex).token.type == is)

z__CStr z__LexToken_get_name(z__size token_type)
{
    //Z__ASSERT(token_type < Z__LEXTOKEN_TOTAL);
    if(token_type >= Z__LEXTOKEN_TOTAL) return (z__CStr){(void*)"<nil>", 5};
    return z__TOKEN_NAMES[token_type];
}

static inline void z__Lexer_make_token(z__Lexer *lex, enum z__LexTokenType token_type)
{
    lex->token.type = token_type;
    lex->token.size = lex->at - lex->token.start;
}

static inline void z__Lexer_make_token_err(z__Lexer *lex, z__u8 *msg, z__size size)
{
    z__Lexer_make_token(lex, Z__LEXTOKEN_ERROR);
    lex->token.start = msg;
    lex->token.size = size;
}

static inline z__bool z__Lexer_advance(z__Lexer *lex)
{
    lex->at += 1;
    return !z__Lexer_isend(lex);
}

static inline z__bool z__Lexer_retreat(z__Lexer *lex)
{
    lex->at -= 1;
    return (lex->at >= lex->begin);
}

static int z__Lexer_check_if_symbol(z__Lexer *lex)
{
    if(!(isalpha(lex->token.start[0]) || lex->token.start[0] == '_')) {
        return 0;
    }
    while( (isalnum(z__Lexer_peek(lex)) || (z__Lexer_peek(lex) == '_')) 
        && !z__Lexer_isend(lex)) {
        z__Lexer_advance(lex);
    }

    z__Lexer_make_token(lex, Z__LEXTOKEN_SYMBOL);
    return 1;
}

static int z__Lexer_check_if_number(z__Lexer *lex)
{
    if(!isdigit(lex->token.start[0])) {
        return 0;
    }

    z__u8 dot = 0;
    while(!z__Lexer_isend(lex)) {
        if(z__Lexer_peek(lex) == '.') {
            if(dot) {
                z__Lexer_make_token(lex, Z__LEXTOKEN_FLOAT);
                return 1; 
            } else { dot = 1; }
        } else if(!isdigit(z__Lexer_peek(lex))) { goto z__Lexer_L_eval; }
        z__Lexer_advance(lex);
    }
    
    z__Lexer_L_eval:
    if(dot) {
        z__u8 const *lsave = z__Lexer_save(lex);
        if(z__Lexer_peek(lex) == 'e' || z__Lexer_peek(lex) == 'E') {
            z__Lexer_advance(lex);
            if(!z__Lexer_isend(lex) 
            &&( z__Lexer_peek(lex) == '-' || isdigit(z__Lexer_peek(lex)))) {
                z__Lexer_advance(lex);
                while(!z__Lexer_isend(lex) && isdigit(z__Lexer_peek(lex))) z__Lexer_advance(lex);
            } else {
                z__Lexer_load(lex, lsave);
            }
        }
        z__Lexer_make_token(lex, Z__LEXTOKEN_FLOAT);
        return 1;
    }
    z__Lexer_make_token(lex, Z__LEXTOKEN_NUMBER);
    return 1;
}

static int z__Lexer_check_if_char(z__Lexer *lex)
{
    switch (lex->token.start[0]) {


    #define CAT2(x, y) x##y
    #define TOKEN(x) CAT2(Z__LEXTOKEN_, x)
        /* Single Char Case */
        #define _match(ch, Token)\
            break; case ch: {z__Lexer_make_token(lex, TOKEN(Token)); return 1;}

        case ' ': { while (z__Lexer_peek(lex) == ' ' && z__Lexer_advance(lex)){ }
                    z__Lexer_make_token(lex, TOKEN(SPACE));
                    return 1;
               }
        _match('\t', TABSPACE);
        case '\n': {
            z__Lexer_make_token(lex, TOKEN(NEWLINE));
            return 1;
        } break;

        //_match(EOF, END_OF_SOURCE);

        _match('(', PAREN_LEFT);
        _match(')', PAREN_RIGHT);
        _match('{', BRACE_LEFT);
        _match('}', BRACE_RIGHT);
        _match('[', SQR_BRACE_LEFT);
        _match(']', SQR_BRACE_RIGHT);

        _match(',', COMMA);
        _match('.', DOT);
        _match(':', COLON);
        _match(';', SEMI_COLON);
        _match('\'', QUOTE);
        _match('"', DOUBLE_QUOTE);
        _match('$', DOLLAR);
        _match('@', AT);
        _match('|', PIPE);
        _match('%', PERCENT);
        _match('#', HASH);
        _match('&', AND);

        _match('\\', BACK_SLASH);
    
        /**/

    /**
     * NOTE: OLD SOURCE USING z_, now deprecated
        #define check2_if(c, T)\
            if(_match_char(s, c)){ return z__Lexer_make_token(T, s); };

        #define check2_ifexpand(x) check2_if x

        #define check2(c1, T1, ...)\
                break; case c1: zpp__Args_map(check2_ifexpand, z__Lexer__VA_ARGS__);\
                                return z__Lexer_make_token(T1, s); break
      **/

        #define _match2(c1, T1, c2, T2)\
            case c1: {\
                z__u8 const *save = z__Lexer_save(lex);\
                z__Lexer_advance(lex);\
                if(!z__Lexer_isend(lex) && z__Lexer_peek(lex) == c2) {\
                    z__Lexer_make_token(lex, TOKEN(T2));\
                } else {\
                    z__Lexer_load(lex, save);\
                    z__Lexer_make_token(lex, TOKEN(T1));\
                }\
                return 1;\
            } break;\

        _match2('!', BANG
            , '=', BANG_EQUAL);
        
        _match2('=', EQUAL
             , '=', EQUAL_EQUAL);

        _match2('>', GREATER
             , '=', GREATER_EQUAL);

        _match2('<', LESS
             , '=', LESS_EQUAL);

        _match2('+', PLUS
             , '=', PLUS_EQUAL);

        _match2('-', MINUS
             , '=', MINUS_EQUAL);

        _match2('*', ASTER
             , '=', ASTER_EQUAL);

        _match2('/', SLASH
             , '=', SLASH_EQUAL);

    break;
    }

    #undef _match
    #undef _match2

    #undef TOKEN
    #undef CAT2
    return 0;
}

void z__Lexer_start(z__Lexer* lex, const z__u8 *string_data, z__size size)
{
    lex->begin = string_data;
    lex->at = string_data;
    lex->end = string_data + size;
    lex->token.start = lex->at;
    lex->token.size = 0;
    lex->token.type = Z__LEXTOKEN_UNKNOWN;
}

void z__Lexer_next(z__Lexer *lex)
{
    if(z__Lexer_isend(lex)) {
        z__Lexer_make_token(lex, Z__LEXTOKEN_END_OF_SOURCE);
        return;
    }
    
    lex->token.start = lex->at;
    z__Lexer_advance(lex);
    
    if(z__Lexer_check_if_char(lex))   { return; }
    if(z__Lexer_check_if_number(lex)) { return; }
    if(z__Lexer_check_if_symbol(lex)) { return; }

    //_check_if_char(lex);
    //if(!z__Lexer_check(*lex, Z__LEXTOKEN_NOT_FOUND)) { return; }

    z__Lexer_make_token_err(lex, (z__u8 *)"NO TOKEN MATCHED", sizeof("NO TOKEN MATCHED")-1);
}

void z__Lexer_next_skipws(z__Lexer *lex)
{
    do {
        z__Lexer_next(lex);
    } while(z__LexToken_is_ws(lex->token) && !z__Lexer_isend(lex));
}

void z__Lexer_next_until(z__Lexer *lex, enum z__LexTokenType type)
{
    do {
        z__Lexer_next(lex);
    } while (z__LexToken_is_not(lex->token, type) && !z__Lexer_isend(lex));
}

z__bool z__Lexer_next_expect(z__Lexer *lex, enum z__LexTokenType type)
{
    z__Lexer_next(lex);
    return lex->token.type == type;
}

z__bool z__Lexer_tiseq(z__Lexer *lex, char const *string, z__size string_size)
{
    if(string_size == lex->token.size) {
        return !memcmp(lex->token.start, string, string_size);
    }
    return 0;
}

z__bool z__Lexer_convert_dq_string(z__Lexer *l)
{
    while(z__Lexer_advance(l)) {
        if(z__Lexer_peek(l) == '"' && z__Lexer_prev_peek(l) != '\\') {
            z__Lexer_advance(l); // include '"'
            z__Lexer_make_token(l, Z__LEXTOKEN_STRING);
            return true;
        }
    }
    z__Lexer_make_token(l, Z__LEXTOKEN_ERROR);
    return false;
}

z__size z__Lexer_line(z__Lexer const *l)
{
    return z__str_calc_linecount((char *)l->begin, l->token.start - l->begin);
}

z__size z__Lexer_col(z__Lexer const *l)
{
    return z__str_calc_column((char *)l->token.start, (char *)l->begin);
}

z__u8 const *z__Lexer_line_start(z__Lexer const *l)
{
    return l->token.start - z__Lexer_col(l);    
}

z__bool z__Lexer_check_sanity(z__Lexer *l)
{
    if(!l) return 0;
    if(!l->at) return 0;
    if(!l->begin) return 0;
    if(!l->end) return 0;
    if(!l->token.start) return 0;
    return 1;
}
#endif //Z__IMPLEMENTATION
#endif
