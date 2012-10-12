/*
 * ---------- header ----------------------------------------------------------
 *
 * project       bpt
 *
 * license       BSD
 *
 * file          /home/mycure/bptx/examples/strings/strings.h
 *
 * created       julien quintard   [thu jul 12 17:01:53 2007]
 * updated       julien quintard   [sun jul 15 13:07:30 2007]
 */

#ifndef STRINGS_H
#define STRINGS_H

/*
 * ---------- macros ----------------------------------------------------------
 */

#define BPT_DEBUG
#define BPTX_DEBUG

/*
 * ---------- includes --------------------------------------------------------
 */

#include <sys/types.h>
#include <stdlib.h>

#include "../../bpt.h"
#include "../../bptx.h"

/*
 * ---------- macros ----------------------------------------------------------
 */

#define STRINGS_ADDR_T		u_int32_t
#define STRINGS_KEY_T		char*
#define STRINGS_VALUE_T		char /* limited to an age of 127 */

#define STRINGS_NODESZ		59
#define STRINGS_UNUSED_ADDR	0
#define STRINGS_UNUSED_KEY	NULL
#define STRINGS_UNUSED_VALUE	-1
#define STRINGS_FLAGS		BPT_FLAG_ZERO

/*
 * ---------- types -----------------------------------------------------------
 */

typedef struct		s_inentry
{
  STRINGS_KEY_T		name;
  STRINGS_ADDR_T	age;
}			t_inentry;

typedef struct		s_lfentry
{
  STRINGS_KEY_T		name;
  STRINGS_VALUE_T	age;
}			t_lfentry;

/*
 * ---------- bpt -------------------------------------------------------------
 */

bpt_make(strings, BPT_NDI_T, BPT_UNI_T, BPT_NODES_T,
	 BPT_HEIGHT_T, STRINGS_ADDR_T, STRINGS_KEY_T, STRINGS_VALUE_T,
	 t_inentry, t_lfentry, name, age);

/*
 * ---------- bptx ------------------------------------------------------------
 */

bptx_types(strings);

bptx_wrapper(strings, (void*)malloc, (void*)free);

bptx_storage(strings, RAM);

bptx_compare(strings, address, scalar);
bptx_compare(strings, value, scalar);

#endif
