/*
 * ---------- header ----------------------------------------------------------
 *
 * project       bpt
 *
 * license       BSD
 *
 * file          /home/mycure/bpt/test/tree.h
 *
 * created       julien quintard   [thu jul 12 17:29:58 2007]
 * updated       julien quintard   [thu jul 12 17:30:05 2007]
 */

#ifndef TREE_H
#define TREE_H

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/*
 * in structure
 */

typedef struct		s_in_input
{
  u_int32_t		no;

#define IN_ADD			0x0
#define IN_REM			0x1
#define IN_MOD			0x2

  u_int8_t		op;

  IN_KEY_T		id;
  IN_KEY_T		key;
  IN_ADDR_T		value;

  /*
   * add operation uses:
   *  . key
   *  . value
   *
   * mod operation uses:
   *  . id
   *  . key
   *  . value
   *
   * rem operation uses:
   *  . id
   */
}			t_in_input;

typedef struct		s_in_output
{
  IN_KEY_T		key;
  IN_ADDR_T		value;
}			t_in_output;

#endif
