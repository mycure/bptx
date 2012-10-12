/*
 * ---------- header ----------------------------------------------------------
 *
 * project       bpt
 *
 * license       BSD
 *
 * file          /home/mycure/bptx/examples/strings/strings.c
 *
 * created       julien quintard   [thu jul 12 17:01:40 2007]
 * updated       julien quintard   [sun jul 15 12:40:47 2007]
 */

#include "strings.h"

/*
 * ---------- functions -------------------------------------------------------
 */

int			strings_keycmp(t_bpt(strings)		*bpt,
				       t_bpt_key(strings)	key1,
				       t_bpt_key(strings)	key2)
{
  if (key1 == key2)
    return (0);

  if ((key1 == bpt->ukey) || (key2 == bpt->ukey))
    return (2);

  /*
   * sort in reverse alphabetical order.
   *
   * that is why we didn't use the bptx standard comparator.
   */
  return (strcmp(key2, key1));
}

void			strings_init(t_bpt(strings)		*bpt)
{
  if (bptx_init(strings, bpt, STRINGS_NODESZ, STRINGS_UNUSED_ADDR,
		STRINGS_UNUSED_KEY, STRINGS_UNUSED_VALUE, STRINGS_FLAGS,
		BPT_BALANCING_PLUS,
		bptx_load(strings), bptx_unload(strings),
		bptx_addrcmp(strings), strings_keycmp,
		bptx_valcmp(strings), NULL, NULL) != 0)
    {
      fprintf(stderr, "example: cannot initialize the tree\n");
      exit(EXIT_FAILURE);
    }
}

void			strings_add(t_bpt(strings)		*bpt,
				    t_bpt_key(strings)		name,
				    t_bpt_value(strings)	age)
{
  t_bpt_lfentry(strings) lfentry;

  lfentry.name = strdup(name);
  lfentry.age = age;

  if (bptx_add(strings, bpt, &lfentry) != 0)
    {
      fprintf(stderr, "example: cannot add an entry in the tree\n");
      exit(EXIT_FAILURE);
    }
}

void			strings_rem(t_bpt(strings)		*bpt,
				    t_bpt_key(strings)		name)
{
  if (bptx_remove(strings, bpt, name) != 0)
    {
      fprintf(stderr, "example: cannot remove an entry in the tree\n");
      exit(EXIT_FAILURE);
    }
}

void			strings_dump_entry(t_bpt(strings)	*bpt,
					   t_bpt_imm(strings)	*node,
					   t_bpt_ndi(strings)	i)
{
  printf("[%u] %s : %d\n",
	 i,
         BPT_KEYCMP(bpt, BPT_GET_ENTRY(strings, node, i, name),
		    bpt->ukey) == 0 ?
	 "nil" : BPT_GET_ENTRY(strings, node, i, name),
         BPT_KEYCMP(bpt, BPT_GET_ENTRY(strings, node, i, name),
		    bpt->ukey) == 0 ?
         -1 : BPT_GET_ENTRY(strings, node, i, age));
}

#define		STRINGS_INDENT(_level_)					\
  {									\
    int		_i_;							\
									\
    for (_i_ = 0; _i_ < (_level_ * 3); _i_++)				\
      printf(" ");							\
  }

void			strings_dump_node(t_bpt(strings)	*bpt,
					  t_bpt_imm(strings)	*node,
					  t_bpt_height(strings)	level)
{
  t_bpt_ndi(strings)	nkeys = BPT_NKEYS(strings, bpt, node);
  t_bpt_imm(strings)	child;
  t_bpt_ndi(strings)	i;

  STRINGS_INDENT(level);

  printf("[head] ");
  if (BPT_GET_HEAD(strings, node, type) == BPT_TYPE_INTERNAL)
    printf("internal");
  else
    printf("leaf");
  printf("\n");

  for (i = 0; i < nkeys; i++)
    {
      STRINGS_INDENT(level);

      if (BPT_GET_HEAD(strings, node, type) == BPT_TYPE_LEAF)
	strings_dump_entry(bpt, node, i);

      if ((BPT_GET_HEAD(strings, node, type) == BPT_TYPE_INTERNAL) &&
	  (BPT_KEYCMP(bpt, BPT_GET_ENTRY(strings, node, i, name),
		      bpt->ukey) != 0))
	{
	  BPT_LOAD(bpt, &child, BPT_GET_ENTRY(strings, node, i, age));

	  printf("\n");

	  strings_dump_node(bpt, &child, level + 1);

	  BPT_UNLOAD(bpt, &child);
	}
    }
}

void			strings_dump(t_bpt(strings)			*bpt)
{
  t_bpt_imm(strings)	root;

  BPT_LOAD(bpt, &root, bpt->root);
  strings_dump_node(bpt, &root, 0);
  BPT_UNLOAD(bpt, &root);
}

/*
 * main function
 */

int			main(void)
{
  t_bpt(strings)	bpt;

  strings_init(&bpt);

  strings_add(&bpt, "chiche", -3);
  strings_add(&bpt, "chodaboy", 9);
  strings_add(&bpt, "dave", 49);
  strings_add(&bpt, "orbison", 2);
  strings_add(&bpt, "hamster", 120);
  strings_add(&bpt, "enculees jumelles", 2);
  strings_add(&bpt, "chodachien", 89);
  strings_add(&bpt, "l'homme neutre", 1);
  strings_add(&bpt, "spermix zero", -8);

  strings_dump(&bpt);

  return (0);
}
