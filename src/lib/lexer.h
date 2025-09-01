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

char const* z__Lexer_get_token_name(z__u8 token_type, z__u32 *size);



#ifdef Z__IMPLEMENTATION
#include "string.h"
#include "assert.h"
#include <ctype.h>
#include <string.h>

#define TOKEN(x) [z__LEXTOKEN_##x] = { .data = (void *)#x, .len = (sizeof(#x) -1) }
static const z__CStr z__TOKEN_NAMES[z__LEXTOKEN_TOTAL+1] = {
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


#define _peek(s) (*(s)->at)
#define _isend(s) ((s)->at >= (s)->end)

#define z__Lexer_check(lex, is) ((lex).token.type == is)

char const* z__Lexer_get_token_name(z__u8 token_type, z__u32 *size)
{
    z__assert(token_type < z__LEXTOKEN_TOTAL);
    *size = z__TOKEN_NAMES[token_type].len;
    return z__TOKEN_NAMES[token_type].data;
}

static inline void _make_token(z__Lexer *lex, enum z__LexTokenType token_type)
{
    lex->token.type = token_type;
    lex->token.size = lex->at - lex->token.start;
}

static inline void _make_token_err(z__Lexer *lex, z__byte *msg, z__u32 size)
{
    _make_token(lex, z__LEXTOKEN_ERROR);
    lex->token.start = msg;
    lex->token.size = size;
}

static inline z__u32 _advance(z__Lexer *lex)
{
    lex->at += 1;
    return lex->at[-1];
}

static int _check_if_symbol(z__Lexer *lex)
{
    if(!(isalpha(lex->token.start[0]) || lex->token.start[0] == '_')) {
        return 0;
    }
    while( (isalnum(_peek(lex)) || (_peek(lex) == '_')) 
        && !_isend(lex)) {
        _advance(lex);
    }

    _make_token(lex, z__LEXTOKEN_SYMBOL);
    return 1;
}

static int _check_if_number(z__Lexer *lex)
{
    if(!isdigit(lex->token.start[0])) {
        return 0;
    }
    z__byte dot = 0;
    if(_peek(lex) == '.') {
        dot += 1;
        _advance(lex);
    }

    while(isdigit(_peek(lex)) && !_isend(lex)) {
        _advance(lex);
        if(_peek(lex) == '.') {
            if(dot) {
                _make_token(lex, z__LEXTOKEN_FLOAT);
                return 1;
            } else {
                dot += 1;
            }
        }
    }

    _make_token(lex, z__LEXTOKEN_NUMBER);
    return 1;
}

static int _check_if_char(z__Lexer *lex)
{
    switch (lex->token.start[0]) {


    #define CAT2(x, y) x##y
    #define TOKEN(x) CAT2(z__LEXTOKEN_, x)
        /* Single Char Case */
        #define _match(ch, Token)\
            break; case ch: {_make_token(lex, TOKEN(Token)); return 1;}

        _match(' ', SPACE);
        _match('\t', TABSPACE);
        case '\n': {
            lex->token.line += 1; 
            lex->token.line_start = lex->at;
            _make_token(lex, TOKEN(NEWLINE));
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
        _match('%', PERCENT);
        _match('#', HASH);
        _match('&', AND);
        _match('|', PIPE);

        _match('\\', BACK_SLASH);
    
        /**/

    /**
     * NOTE: OLD SOURCE USING z_, now deprecated
        #define check2_if(c, T)\
            if(_match_char(s, c)){ return _make_token(T, s); };

        #define check2_ifexpand(x) check2_if x

        #define check2(c1, T1, ...)\
                break; case c1: zpp__Args_map(check2_ifexpand, __VA_ARGS__);\
                                return _make_token(T1, s); break
      **/

        #define _match2(c1, T1, c2, T2)\
            case c1: {\
                _advance(lex);\
                if(_peek(lex) == c2) {\
                    _make_token(lex, TOKEN(T2));\
                } else {\
                    _make_token(lex, TOKEN(T1));\
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

/**
#include <stdio.h>
static void _print_token(z__Lexer *lex)
{
    z__assert(lex->token.type < z__LEXTOKEN_TOTAL);
    if(lex->token.type == z__LEXTOKEN_NEWLINE) {
        printf(" -> NEWLINE\n");
        return;
    }
    z__CStr const tokname = z__get_token_name(lex->token.type);
printf("%.*s -> %.*s\n | \n", (int)lex->token.size, lex->token.start,
            (int)tokname.len, tokname.data);
    
}**/

void z__Lexer_start(z__Lexer* lex, const z__byte *string_data, z__u32 size)
{
    lex->begin = string_data;
    lex->at = string_data;
    lex->end = string_data + size;
    lex->token.start = lex->at;
    lex->token.line_start = lex->at;
    lex->token.size = 0;
    lex->token.line = 1;
    lex->token.type = z__LEXTOKEN_UNKNOWN;
}

void z__Lexer_next(z__Lexer *lex)
{
    if(_isend(lex)) {
        _make_token(lex, z__LEXTOKEN_END_OF_SOURCE);
        return;
    }
    
    lex->token.start = lex->at;
    _advance(lex);
    
    if(_check_if_char(lex))   { return; }
    if(_check_if_number(lex)) { return; }
    if(_check_if_symbol(lex)) { return; }

    //_check_if_char(lex);
    //if(!z__Lexer_check(*lex, z__LEXTOKEN_NOT_FOUND)) { return; }

    _make_token_err(lex, (void *)z__cstr("NO TOKEN MATCHED").data,
                         z__cstr("NO TOKEN MATCHED").len);
}

void z__Lexer_next_skipws(z__Lexer *lex)
{
    do {
        z__Lexer_next(lex);
    } while(z__LexToken_is_ws(lex->token) && !_isend(lex));
}

void z__Lexer_next_until(z__Lexer *lex, enum z__LexTokenType type)
{
    do {
        z__Lexer_next(lex);
    } while (z__LexToken_is_not(lex->token, type) && !_isend(lex));
}

z__bool z__Lexer_next_expect(z__Lexer *lex, enum z__LexTokenType type)
{
    z__Lexer_next(lex);
    return lex->token.type == type;
}

z__bool z__Lexer_tiseq(z__Lexer *lex, char const *string, z__u32 string_size)
{
    if(string_size == lex->token.size) {
        return !memcmp(lex->token.start, string, string_size);
    }
    return 0;
}

#endif

#endif

