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

#ifdef Z__IMPLEMENTATION
#include <stdlib.h>
#include "std/alloc.h"

#include "string.h"
#include "hashset.h"
#include "arr.h"
#include "arena.h"
#include "lexer.h"
#include "assert.h"
#include "print.h"

enum z__BnfNodeType {
    z__BnfNodeType_VALUE,
    z__BnfNodeType_RULE,
    z__BnfNodeType_AND,
    z__BnfNodeType_OR,
};

typedef struct z__BnfNode z__BnfNode;
struct z__BnfNode {
    // value (string)
    // or (node || node)
    // and (node && node)
    union {
        z__Str     as_value;
        struct {
            z__u32     rule_id;
        } as_rule;
        struct { 
            z__BnfNode *self;
            z__BnfNode *next;
        } as_and;
        struct {
            z__BnfNode *self;
z__BnfNode *next;
        } as_or;
    };
    enum z__BnfNodeType type;
};

typedef struct z__Bnf z__Bnf;
struct z__Bnf {
    z__HashStr(z__u32) rules;
    z__Arr(z__BnfNode *) rule_nodes;
    z__StringList rule_names;
    z__Arena *node_pool;
};

#include "../lib/lexer.h"

void z__Bnf_new(z__Bnf *self)
{
    z__HashStr_new(&self->rules);
    z__Arr_new(&self->rule_nodes, 8);
    self->rule_names = z__StringList_new(8);
    self->node_pool =  z__Arena_new(sizeof(z__BnfNode) * 128);
}

void z__Bnf_delete(z__Bnf *self)
{
    z__Arena_delete(self->node_pool);
    z__HashStr_delete(&self->rules);
    z__Arr_delete(&self->rule_nodes);
    z__StringList_delete(&self->rule_names);
}

void z__Bnf_add_rule(z__Bnf *self, char *name, z__u32 size, z__BnfNode *node)
{
    z__Arr_push(&self->rule_nodes, node);
    z__StringList_push(&self->rule_names, name, size);
    z__u32 id = self->rule_nodes.lenUsed - 1;
    z__HashStr_set(&self->rules, z__Str(name, size), id);
}

z__i64 z__Bnf_get_rule_id(z__Bnf *self, z__Str const key)
{
    z__u32 *val = NULL;
    z__HashStr_getreff(&self->rules, key, &val);
    if(val != NULL) return *val;
    return -1;
}

z__BnfNode *z__Bnf_get_rule(z__Bnf *grammer, z__Str const key)
{
    z__u32 *valptr = NULL;
    z__HashStr_getreff(&grammer->rules, key, &valptr);
    if(valptr == NULL) return NULL;
    return grammer->rule_nodes.data[*valptr];
}

z__BnfNode *z__BnfNode_new(z__Arena *pool, enum z__BnfNodeType type)
{
    z__BnfNode *node = z__Arena_alloc(pool, sizeof(z__BnfNode));
    node->type = type;
    return node;
}

z__BnfNode *z__BnfNode_as_value(z__Arena *pool, z__Str const val)
{
    z__BnfNode *node = z__BnfNode_new(pool, z__BnfNodeType_VALUE);
    node->as_value = z__Str_newCopy(val);
    return node;
}

z__BnfNode *z__BnfNode_as_or(
    z__Arena *pool, z__BnfNode *primary, z__BnfNode *next)
{
    z__BnfNode *node = z__BnfNode_new(pool, z__BnfNodeType_OR);
    node->as_or.self = primary;
    node->as_or.next = next;
    return node;
}

z__BnfNode *z__BnfNode_as_and(
    z__Arena *pool, z__BnfNode *primary, z__BnfNode *next)
{
    z__BnfNode *node = z__BnfNode_new(pool, z__BnfNodeType_AND);
    node->as_and.self = primary;
    node->as_and.next = next;
    return node;
}

z__BnfNode *z__BnfNode_as_rule(z__Arena *pool, z__Bnf *grammer, z__Str const rule)
{
    z__BnfNode *node = z__BnfNode_new(pool, z__BnfNodeType_RULE);
    node->as_rule.rule_id = z__Bnf_get_rule_id(grammer, rule);
    return node;
}

z__bool static _compile_try_new_rule(z__Bnf *self, z__Lexer *l)
{
    z__LexToken rule = l->token;
    z__Lexer_next_skipws(l);
    if(z__LexToken_is_not(l->token, z__LEXTOKEN_EQUAL)) {
        return 0;
    }
    
    z__Bnf_add_rule(self, (void *)rule.start, rule.size, NULL);

    return 1;
}

z__bool static _compile_try_add_node_as_rule(z__Bnf *self, z__Lexer *l)
{

}

z__bool static _compile_node(z__Bnf *self, z__Lexer *l)
{
    switch (l->token.type) {
        break; case z__LEXTOKEN_SYMBOL: {
            if(_compile_try_new_rule(self, l)) {

            } else if(_compile_try_add_node_as_rule(self, l)) {

            } else {
                return 0;
            }
        }
        break; case z__LEXTOKEN_PIPE:
        break; case z__LEXTOKEN_AND:
        break; case z__LEXTOKEN_DOUBLE_QUOTE:
        break; default: return 0;
    }
    return 1;
}

static z__bool z__Lexer_next_skipws_expect(z__Lexer *l, enum z__LexTokenType tok)
{
    z__Lexer_next_skipws(l);
    return z__LexToken_is(l->token, tok);
}

z__bool z__Bnf_add_compile(z__Bnf *self, char const *source, z__u32 size)
{
    z__Lexer l;
    z__Lexer_start(&l, (void *)source, size);
    z__assert(z__Lexer_next_skipws_expect(&l, z__LEXTOKEN_SYMBOL));
    z__LexToken rule_name = l.token;
    z__assert(z__Lexer_next_skipws_expect(&l, z__LEXTOKEN_EQUAL));
    z__Bnf_add_rule(self, rule_name.start, rule_name.size, NULL);

}

void z__print_bnfnode(z__Bnf *grammer, z__BnfNode *node)
{
    switch (node->type) {
        break; case z__BnfNodeType_VALUE: 
            z__print("\"%.*s\"", node->as_value.len, node->as_value.data);
        break; case z__BnfNodeType_OR:
            z__print_bnfnode(grammer, node->as_or.self);
            z__print_char(' ');
            z__print_char('|');
            z__print_char(' ');
            z__print_bnfnode(grammer, node->as_or.next);
        break; case z__BnfNodeType_AND:
            z__print_bnfnode(grammer, node->as_and.self);
            z__print_char(' ');
            z__print_bnfnode(grammer, node->as_and.next);
        break; case z__BnfNodeType_RULE: {
                char const *name = grammer->rule_names.data[node->as_rule.rule_id];
                z__u32 const name_len = grammer->rule_names.slens[node->as_rule.rule_id];
                z__print("%.*s", name_len, name);
            }
    }
}

void z__print_bnf(z__Bnf *grammer)
{
    z__print("Grammer Print\n");
    for (size_t i = 0; i < grammer->rule_nodes.lenUsed; i++) {
        z__print("%.*s = ", grammer->rule_names.slens[i]
                          , grammer->rule_names.data[i]);
        z__print_bnfnode(grammer, grammer->rule_nodes.data[i]);
        
        z__print_char('\n');
    }
}


#endif //Z__IMPLEMENTATION
