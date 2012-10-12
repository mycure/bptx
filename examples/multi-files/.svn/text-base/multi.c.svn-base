/*
 * bpt.h
 * 
 * multi.c
 * 
 * path          
 * 
 * made by mycure
 *         quintard julien   [quinta_j@epita.fr]
 * 
 * started on    Mon Oct 25 11:38:49 2004   mycure
 * last update   Fri Apr  8 19:21:31 2005   mycure
 */

#include "multi.h"

/*
 * ---------- bpt -------------------------------------------------------------
 */

/*
 * build the first tree, called klc
 *
 * this tree accepts collisions, uses blocks of 4096 bytes and uses
 * the value -1 as the unused address
 *
 * the types used are: 32-bit (key), 32-bit (addr), 8-bit (interval)
 *                     and 32-bit (value)
 *
 * this tree can be used, for example, for memory management
 */

bpt_make_functions(klc, u.addr.address, nblocks);

/*
 * build the second tree, called lse
 *
 * this tree does not accept either collision or intervals,
 * uses blocks of 512 bytes and uses the value 0 as the unused address
 *
 * the types used are: 64-bit (key), 64-bit (adddr), 8-bit (interval)
 *                     and 64-bit (value)
 *
 * this tree can be used on storage devices like hard drives.
 */

bpt_make_functions(lse, key, value);

/*
 * ---------- bptx ------------------------------------------------------------
 */

bptx_wrapper(klc, (void*)malloc, (void*)free);

bptx_storage(klc, RAM);

bptx_compare(klc, address, scalar);
bptx_compare(klc, key, scalar);
bptx_compare(klc, value, scalar);

/*
 * ---------- functions -------------------------------------------------------
 */

int			main(void)
{
  t_bpt(klc)		bpt;

  klc_init(&bpt);

  klc_add(&bpt, 19, 42);
  klc_add(&bpt, 15, 1);
  klc_add(&bpt, 199891, 561);

  klc_mod(&bpt, 15, 19, 84);

  klc_crem(&bpt, 19, 84);

  /*
   * this call will produce an error
   */

  klc_add(&bpt, KLC_UNUSED_KEY, 9561);

  return (0);
}
