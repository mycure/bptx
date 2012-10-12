/*
 * ---------- header ----------------------------------------------------------
 *
 * project       bpt
 *
 * license       BSD
 *
 * file          /home/mycure/bptx/examples/multi-files/multi-klc.c
 *
 * created       julien quintard   [thu jul 12 17:00:15 2007]
 * updated       julien quintard   [sun jul 15 12:53:49 2007]
 */

#include "multi.h"

void			klc_init(t_bpt(klc)			*bpt)
{
  bptx_init(klc, bpt, KLC_NODESZ, KLC_UNUSED_ADDR, KLC_UNUSED_KEY,
	    KLC_UNUSED_VALUE, KLC_FLAGS, BPT_BALANCING_PLUS,
	    bptx_load(klc), bptx_unload(klc),
	    bptx_addrcmp(klc), bptx_keycmp(klc), bptx_valcmp(klc),
	    NULL, NULL);
}

void			klc_add(t_bpt(klc)			*bpt,
				t_bpt_key(klc)			address,
				t_bpt_value(klc)		nblocks)
{
  t_bpt_lfentry(klc)	lfentry;

  lfentry.u.addr.address = address;
  lfentry.nblocks = nblocks;

  bptx_add(klc, bpt, &lfentry);
}

void			klc_mod(t_bpt(klc)			*bpt,
				t_bpt_key(klc)			idk,
				t_bpt_key(klc)			address,
				t_bpt_value(klc)		nblocks)
{
  t_bpt_lfentry(klc)	lfentry;

  lfentry.u.addr.address = address;
  lfentry.nblocks = nblocks;

  bptx_modify(klc, bpt, idk, &lfentry);
}

void			klc_cmod(t_bpt(klc)			*bpt,
				 t_bpt_key(klc)			idk,
				 t_bpt_value(klc)		idv,
				 t_bpt_key(klc)			address,
				 t_bpt_value(klc)		nblocks)
{
  t_bpt_lfentry(klc)	lfentry;
  t_bpt_entry(klc)	entry;

  bptx_collide_search(klc, bpt, idk, idv, &entry);

  lfentry.u.addr.address = address;
  lfentry.nblocks = nblocks;

  bptx_collide_modify(klc, bpt, entry, &lfentry);
}

void			klc_rem(t_bpt(klc)			*bpt,
				t_bpt_key(klc)			idk)
{
  bptx_remove(klc, bpt, idk);
}

void			klc_crem(t_bpt(klc)			*bpt,
				 t_bpt_key(klc)			idk,
				 t_bpt_value(klc)		idv)
{
  t_bpt_entry(klc)	entry;

  bptx_collide_search(klc, bpt, idk, idv, &entry);

  bptx_collide_remove(klc, bpt, entry);
}
