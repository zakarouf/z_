#ifndef ZAKAROUF__ZPREP_NM_PRAGMA_H
#define ZAKAROUF__ZPREP_NM_PRAGMA_H

#define zpp__PRIV_PRAGMA(str_literal) _Pragma(str_literal)
#define zpp__pragma(...) zpp__PRIV_PRAGMA(#__VA_ARGS__)

#endif
