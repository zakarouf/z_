#ifndef ZAKAROUF__ZTYPES_TYPES__TREE_H
#define ZAKAROUF__ZTYPES_TYPES__TREE_H

#include "../prep/map.h"
#include "arr.h"

#define z__PRIV__Tree_apply_pointer(x) *x

#define z__Tree(Name, node_names, ...)            \
  typedef struct Name Name;                       \
  struct Name {                                   \
      z__RecordX(__VA_ARGS__) val;                \
                                                              \
      union {                                                 \
        Name *raw[zpp__Args_Count(zpp__UNPAREN(node_names))]; \
        struct {                                              \
          Name zpp__Args_maplist(                             \
              z__PRIV__Tree_apply_pointer, zpp__UNPAREN(node_names)); \
        };                                                            \
      } nodes;                                                        \
      Name *parent_node;            \
      z__u8 has_nodes;            \
  }


#define z__TreeHandle(T)\
    struct {\
        z__Arr(T) all_nodes;  \
        T* root;              \
        T* cursor;            \
    }

#define z__Tree_val(t) (t)->val
#define z__Tree_node(t, of) (t)->nodes.raw[of]
#define z__Tree_nodes(t) (t)->nodes
#define z__Tree_is_leaf(t) !(t)->has_nodes
#define z__Tree_has_nodes(t) (t)->has_nodes
#define z__Tree_get_nodeCount(t) (sizeof((t)->nodes.raw)/sizeof((t)->nodes.raw[0]))

#define z__Tree_setas_leaf(t, ...) {            \
  z__Record_assign((&(t)->val), __VA_ARGS__);   \
  (t)->has_nodes = false;                       \
}

#define z__Tree_setas_node(t, nd, ...) {              \
  z__Record_assign((&(t)->nodes), zpp__UNPAREN(nd));  \
  z__Record_assign((&(t)->val), __VA_ARGS__);         \
  (t)->has_nodes = true;                              \
}

#define z__Tree_match(tree)\
  for(z__typeof(tree) z__priv_tree_match_var = tree; z__priv_tree_match_var != NULL; z__priv_tree_match_var = NULL)\
    switch((tree)->has_nodes)

#define z__Tree_slLeaf(...) \
    break; case false:\
      { z__Record_toReffrence(&z__priv_tree_match_var->val, __VA_ARGS__)

#define z__Tree_slNode(n, ...)\
    break; case true:\
      { z__Record_toReffrence(&z__priv_tree_match_var->nodes, zpp__UNPAREN(n));\
        z__Record_toReffrence(&z__priv_tree_match_var->val, __VA_ARGS__);

#define z__Tree_sldefault()\
        break; default: 


#define z__Tree_unsl }

#endif

