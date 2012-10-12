/*
 * ---------- header ----------------------------------------------------------
 *
 * project       bpt
 *
 * license       BSD
 *
 * file          /home/mycure/bptx/examples/multi-files/multi-klc.h
 *
 * created       julien quintard   [thu jul 12 17:00:36 2007]
 * updated       julien quintard   [sun jul 15 13:01:36 2007]
 */

#ifndef MULTI_KLC_H
#define MULTI_KLC_H

/*
 * includes
 */

#include "multi.h"

/*
 * defines
 */

#define KLC_NODESZ		4096
#define KLC_UNUSED_ADDR		-1
#define KLC_UNUSED_KEY		-1
#define KLC_UNUSED_VALUE	-1
#define KLC_ADDR_T		u_int32_t
#define KLC_KEY_T		u_int32_t
#define KLC_VALUE_T		u_int32_t
#define KLC_FLAGS		BPT_FLAG_COLLIDE

/*
 * types
 */

typedef struct		s_klc_inentry
{
  union
  {
    struct
    {
      KLC_KEY_T		address;
    }			addr;

    u_int8_t		unknown;
  }			u;

  KLC_ADDR_T		nblocks;
}			t_klc_inentry;

typedef struct		s_klc_lfentry
{
  union
  {
    struct
    {
      KLC_KEY_T		address;
    }			addr;

    u_int8_t		unknown;
  }			u;

  KLC_VALUE_T		nblocks;
  u_int8_t		klc;
}			t_klc_lfentry;

/*
 * bpt types
 */

bpt_make_types(klc, BPT_NDI_T, BPT_UNI_T, BPT_NODES_T,
	       BPT_HEIGHT_T, KLC_ADDR_T, KLC_KEY_T, KLC_VALUE_T,
	       t_klc_inentry, t_klc_lfentry);

/*
 * bpt prototypes
 */

bpt_make_protos(klc);

/*
 * bptx types
 */

bptx_types(klc);

/*
 * prototypes
 */

void			klc_init(t_bpt(klc)			*bpt);

void			klc_add(t_bpt(klc)			*bpt,
				t_bpt_key(klc)			key,
				t_bpt_value(klc)		value);

void			klc_mod(t_bpt(klc)			*bpt,
				t_bpt_key(klc)			idk,
				t_bpt_key(klc)			key,
				t_bpt_value(klc)		value);

void			klc_cmod(t_bpt(klc)			*bpt,
				 t_bpt_key(klc)			idk,
				 t_bpt_value(klc)		idv,
				 t_bpt_key(klc)			key,
				 t_bpt_value(klc)		value);

void			klc_rem(t_bpt(klc)			*bpt,
				t_bpt_key(klc)			idk);

void			klc_crem(t_bpt(klc)			*bpt,
				 t_bpt_key(klc)			idk,
				 t_bpt_value(klc)		idv);

#endif
