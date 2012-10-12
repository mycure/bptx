/*
 * ---------- header ----------------------------------------------------------
 *
 * project       bpt
 *
 * license       BSD
 *
 * file          /home/mycure/bpt/examples/multi-files/multi-lse.h
 *
 * created       julien quintard   [thu jul 12 17:01:12 2007]
 * updated       julien quintard   [fri jul 13 01:09:16 2007]
 */

#ifndef MULTI_LSE_H
#define MULTI_LSE_H

/*
 * defines
 */

#define LSE_NODESZ		512
#define LSE_UNUSED_ADDR		0
#define LSE_UNUSED_KEY		0
#define LSE_UNUSED_VALUE	0
#define LSE_ADDR_T		u_int64_t
#define LSE_KEY_T		u_int64_t
#define LSE_VALUE_T		u_int64_t
#define LSE_FLAGS		BPT_FLAG_ZERO

/*
 * includes
 */

#include "multi.h"

/*
 * types
 */

typedef struct		s_lse_inentry
{
  LSE_ADDR_T		value;
  LSE_KEY_T		key;
}			t_lse_inentry;

typedef struct		s_lse_lfentry
{
  LSE_VALUE_T		value;
  u_int32_t		lse;
  LSE_KEY_T		key;
}			t_lse_lfentry;

/*
 * bpt types
 */

bpt_make_types(lse, BPT_NDI_T, BPT_UNI_T, BPT_NODES_T,
	       BPT_HEIGHT_T, LSE_ADDR_T, LSE_KEY_T, LSE_VALUE_T,
	       t_lse_inentry, t_lse_lfentry);

/*
 * bpt prototypes
 */

bpt_make_protos(lse);

#endif
