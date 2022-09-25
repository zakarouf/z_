#ifndef ZAKAROUF_Z_IMP__HTMLFMT_H
#define ZAKAROUF_Z_IMP__HTMLFMT_H

#include "../prep/base.h"
#include "../prep/args.h"
#include "../prep/map.h"

/* Create a Single Unclosed Tag */
#define z__html_fmt_tag(tag) "<" z__PRIV__html_tag_open(tag) ">"

/* Creates a tag encapsulates data */
#define z__html_fmt(tag_data, ...)\
    z__html_fmt_tag(tag_data)\
    __VA_ARGS__\
    "</" z__PRIV__html_tag_close(tag_data) ">"



/*! PRIV STUFFF !*/

/*-----------------HTML---------------*/
#define z__PRIV__html_tag_open__IS_PAREN_0(tag) zpp__TO_STRING(tag)
#define z__PRIV__html_tag_open__IS_PAREN_1(tag) zpp__TO_STRING(zpp__PRIV__Args_get_1 tag) " " zpp__TO_STRING(zpp__Args_skip_1 tag)

#define z__PRIV__html_tag_open(tag) zpp__CAT(z__PRIV__html_tag_open__IS_PAREN_, zpp__IS_PAREN(tag))(tag)


#define z__PRIV__html_tag_close(tag) zpp__CAT(z__PRIV__html_tag_close__IS_PAREN_, zpp__IS_PAREN(tag))(tag)
#define z__PRIV__html_tag_close__IS_PAREN_0(tag) zpp__TO_STRING(tag)
#define z__PRIV__html_tag_close__IS_PAREN_1(tag) zpp__TO_STRING(zpp__PRIV__Args_get_1 tag)

#endif

