/* --------------------------------------------------------------------------
 *    Name: select.c
 * Purpose: Associative array implemented as a critbit tree
 * ----------------------------------------------------------------------- */

#include <assert.h>
#include <stdlib.h>

#include "base/errors.h"
#include "base/types.h"

#include "datastruct/item.h"

#include "datastruct/critbit.h"

#include "impl.h"

typedef struct critbit__select_args
{
  int     k;
  item_t *item;
}
critbit__select_args_t;

static error critbit__select_node(critbit__node_t *n,
                                  int              level,
                                  void            *opaque)
{
  critbit__select_args_t *args = opaque;

  NOT_USED(level);

  if (args->k-- == 0)
  {
    critbit__extnode_t *e;

    e = FROM_STORE(n);

    args->item = &e->item;
    return error_STOP_WALK;
  }

  return error_OK;
}

/* Walk the tree until the k'th leaf is encountered and return it. */
const item_t *critbit_select(critbit_t *t, int k)
{
  error                  err;
  critbit__select_args_t args;

  args.k    = k;
  args.item = NULL;

  err = critbit__walk_internal(t,
                               critbit_WALK_LEAVES,
                               critbit__select_node,
                               &args);

  /* no errors save for the expected ones should happen here */
  assert(err == error_OK || err == error_STOP_WALK);

  return args.item;
}

