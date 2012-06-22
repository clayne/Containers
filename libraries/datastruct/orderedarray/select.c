/* --------------------------------------------------------------------------
 *    Name: select.c
 * Purpose: Ordered array
 * ----------------------------------------------------------------------- */

#include "datastruct/item.h"

#include "datastruct/orderedarray.h"

#include "impl.h"

const item_t *orderedarray_select(orderedarray_t *t, int k)
{
  return (k < t->nelems) ? &t->array[k].item : t->default_value;
}

