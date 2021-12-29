#ifndef ZAKAROUF__ZTYPES_TYPES__TREE_H
#define ZAKAROUF__ZTYPES_TYPES__TREE_H

#include "../prep/map.h"
#include "../prep/nm/assert.h"
#include "arr.h"

#define z__PRIV__Tree_apply_pointer(x) *x

#define z__Tree(Name, node_names, ...)            \
  typedef struct Name Name;                       \
  struct Name {                                   \
      z__RecordX(__VA_ARGS__) val;                \
      union {                                                      \
        union {                                                 \
          Name *raw[zpp__Args_Count(zpp__UNPAREN(node_names))]; \
          struct {                                              \
            Name zpp__Args_maplist(                             \
                z__PRIV__Tree_apply_pointer, zpp__UNPAREN(node_names)); \
          };                                                            \
        } nodes;                                                        \
        z__Vector(z__u64, zpp__UNPAREN(node_names)) index_nodes;        \
      };                                                                \
      Name *parent_node;            \
      z__u8 nodesUsed;              \
  }

#define z__Tree_val(t) (t)->val
#define z__Tree_node(t, of) (t)->nodes.raw[of]
#define z__Tree_nodes(t) (t)->nodes
#define z__Tree_is_leaf(t) !(t)->nodesUsed
#define z__Tree_nodesUsed(t) (t)->nodesUsed
#define z__Tree_get_nodeCount(t) (sizeof((t)->nodes.raw)/sizeof((t)->nodes.raw[0]))

#define z__Tree_setas_leaf(t, ...) {            \
  z__Record_assign((&(t)->val), __VA_ARGS__);   \
  (t)->nodesUsed = 0;                           \
}

#define z__Tree_setas_node(t, nd, ...) {              \
  z__Record_assign((&(t)->nodes), zpp__UNPAREN(nd));  \
  z__Record_assign((&(t)->val), __VA_ARGS__);         \
  (t)->nodesUsed = zpp__Args_Count(zpp__UNPAREN(nd)); \
  _Static_assert(zpp__Args_Count(zpp__UNPAREN(nd)) == z__Tree_get_nodeCount(t), \
      "Dangling/Unused nodes detected "\
      "Of :: " #t);\
}

#define z__Tree_setas_index_node(t, nd, ...) {            \
  z__Record_assign((&(t)->index_nodes), zpp__UNPAREN(nd));  \
  z__Record_assign((&(t)->val), __VA_ARGS__);         \
  (t)->nodesUsed = zpp__Args_Count(zpp__UNPAREN(nd)); \
  _Static_assert(zpp__Args_Count(zpp__UNPAREN(nd)) == z__Tree_get_nodeCount(t), \
      "Dangling/Unused nodes detected "\
      "Of :: " #t);\
}

#define z__Tree_changeto_node(t, ...) {           \
  z__Record_assign(&(t)->nodes, __VA_ARGS__);     \
  (t)->nodesUsed = zpp__Args_Count(__VA_ARGS__);  \
  _Static_assert(zpp__Args_Count(zpp__UNPAREN(nd)) == z__Tree_get_nodeCount(t), \
      "Dangling/Unused nodes detected "                                         \
      "Of :: " #t);                                                             \
}

#define z__Tree_changeto_leaf(t) {                          \
  (t)->nodesUsed = 0;                                       \
  for(z__size i = 0; i < z__Tree_get_nodeCount(t); i += 1) {\
    (t)->nodes.raw[i] = NULL;                               \
  }                                                         \
}

#endif

