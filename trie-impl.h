/* trie-impl.h -- associative array implemented as trie */

#ifndef TRIE_IMPL_H
#define TRIE_IMPL_H

#include "types.h"

#include "item.h"

#include "trie.h"

/* ----------------------------------------------------------------------- */

typedef struct trie__node
{
  /* using an array here rather than separate left,right elements makes some
   * operations more convenient */
  struct trie__node  *child[2]; /* left, right children */
  item_t              item;
  size_t              keylen;
}
trie__node_t;

struct trie
{
  trie__node_t       *root;

  int                 count;

  const void         *default_value;

  trie_compare       *compare;
  trie_destroy_key   *destroy_key;
  trie_destroy_value *destroy_value;
};

/* ----------------------------------------------------------------------- */

#define IS_LEAF(n) ((n)->child[0] == NULL && (n)->child[1] == NULL)

/* ----------------------------------------------------------------------- */

/* internal tree walk functions which return a pointer to a trie__node_t */

typedef error (trie__walk_internal_callback)(trie__node_t *n,
                                             int           level,
                                             void         *opaque);

error trie__walk_internal(trie_t                       *t,
                          trie_walk_flags               flags,
                          trie__walk_internal_callback *cb,
                          void                         *opaque);

/* ----------------------------------------------------------------------- */

error trie__breadthwalk_internal(trie_t                       *t,
                                 trie_walk_flags               flags,
                                 trie__walk_internal_callback *cb,
                                 void                         *opaque);

/* ----------------------------------------------------------------------- */

#endif /* TRIE_IMPL_H */
