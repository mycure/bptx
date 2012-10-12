/*
 * ---------- header ----------------------------------------------------------
 *
 * project       bpt
 *
 * license       BSD
 *
 * file          /home/mycure/bptx/test/gen.c
 *
 * created       julien quintard   [thu jul 12 17:27:06 2007]
 * updated       julien quintard   [sun jul 15 14:08:55 2007]
 */

/*
 * includes
 */

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*
 * debug
 */

#define BPT_DEBUG
#define BPTX_DEBUG

#undef GEN_DEBUG

/*
 * used to generate a sequence of operations which can be used with
 * the bpt sh. very useful to debug bpt.h
 */

#undef GEN_DEBUG_SEQUENCE

/*
 * print on stderr the generated test
 */

#define GEN_DEBUG_GEN

/*
 * i advise you not to set GEN_VERIFY when generating huge tests
 */

#define GEN_VERIFY

/*
 * defines / types
 */

#define GEN_CONSTRUCTOR		100000
#define GEN_DESTRUCTOR		75000

#define GEN_NOPS		200000

#define GEN_ADDR_T		u_int64_t
#define GEN_KEY_T		u_int64_t
#define GEN_VALUE_T		u_int64_t
#define GEN_INTERVAL_T		u_int64_t

#define GEN_NODESZ		79
#define GEN_UNUSED_ADDR		-1
#define GEN_UNUSED_KEY		-1
#define GEN_UNUSED_VALUE	-1
#define GEN_FLAGS		BPT_FLAG_COLLIDE

#define GEN_KEY_MASK		0xffffffff
#define GEN_VALUE_MASK		0xffffffff

typedef struct			s_gen_inentry
{
  GEN_KEY_T			key;
  GEN_ADDR_T			value;
}				t_gen_inentry;

typedef struct			s_gen_lfentry
{
  GEN_KEY_T			key;
  GEN_VALUE_T			value;
}				t_gen_lfentry;

#define GEN_OP_MASK	10
#define GEN_OP_ADD	5
#define GEN_OP_REM	7
#define GEN_OP_MOD	9

typedef struct		s_entry
{
  GEN_KEY_T		key;
  GEN_ADDR_T		value;

  struct s_entry	*prev;
  struct s_entry	*next;
}			t_entry;

/*
 * global variables
 */

t_entry			*list = NULL;
u_int64_t		listsz = 0;

u_int64_t		___loaded = 0;
u_int64_t		___allocated = 0;

/*
 * make the tree
 */

#include "../bpt.h"

bpt_make(gen, BPT_NDI_T, BPT_UNI_T, BPT_NODES_T, BPT_HEIGHT_T,
         GEN_ADDR_T, GEN_KEY_T, GEN_VALUE_T, t_gen_inentry, t_gen_lfentry,
	 key, value);

/*
 * bptx.h
 */

#include "../bptx.h"

bptx_types(gen);

bptx_wrapper(gen, (void*)malloc, (void*)free);

bptx_storage(gen, RAM);

bptx_compare(gen, address, scalar);
bptx_compare(gen, key, scalar);
bptx_compare(gen, value, scalar);

/*
 * prototypes
 */

void			gen_exit(int				code,
				 char				*msg);

void			gen_verify(t_bpt(gen)			*bpt);

void			gen_insert_entry(t_bpt(gen)		*bpt,
					 t_bpt_key(gen)		key,
					 t_bpt_addr(gen)	value);

void			gen_delete_entry(t_bpt(gen)		*bpt,
					 t_bpt_key(gen)		key);

void			gen_modify_entry(t_bpt(gen)		*bpt,
					 t_bpt_key(gen)		key,
					 t_bpt_key(gen)		nkey,
					 t_bpt_addr(gen)	nvalue);

int			gen_exist(t_bpt(gen)			*bpt,
				  t_bpt_key(gen)		key);

int			gen_key(t_bpt(gen)			*bpt,
				t_bpt_key(gen)			*key);

int			gen_init(t_bpt(gen)			*bpt);

int			gen_clean(t_bpt(gen)			*bpt);

int			gen_rem(t_bpt(gen)			*bpt,
				u_int64_t			id);

int			gen_mod(t_bpt(gen)			*bpt,
				u_int64_t			id);

int			gen_add(t_bpt(gen)			*bpt,
				u_int64_t			id);

/*
 * functions
 */

void			gen_exit(int				code,
				 char				*msg)
{
  printf("%s\n", msg);
  exit(code);
}

void			gen_verify(t_bpt(gen)			*bpt)
{
  t_entry		*entry;
  u_int64_t		i;

#ifdef GEN_DEBUG
  printf("---[ verifying order ...\n");
#endif

  for (i = 0, entry = list; entry != NULL; entry = entry->next, i++)
    ;

#ifdef GEN_DEBUG_GEN
  fprintf(stderr, "#define IN_OUTPUT_NOPS		%qu\n\n", i);
  fprintf(stderr, "t_in_output	output[IN_OUTPUT_NOPS] =\n");
  fprintf(stderr, "{\n");
#endif

  for (entry = list; entry != NULL; entry = entry->next)
    {
      t_entry		*prev = entry->prev;
      t_entry		*nxt = entry->next;
      t_bpt_entry(gen)	previous;
      t_bpt_entry(gen)	current;
      t_bpt_entry(gen)	next;
      t_bpt_imm(gen)	node1;
      t_bpt_imm(gen)	node2;

#ifdef GEN_DEBUG_GEN
      fprintf(stderr, "  {	%qu,	%qu	},\n",
	      (u_int64_t)entry->key, (u_int64_t)entry->value);
#endif

      if (bptx_search(gen, bpt, entry->key, &current) != 0)
	{
	  fprintf(stderr, "[gen] cannot find the entry\n");
	  gen_exit(EXIT_FAILURE, "[KO]");
	}

      BPT_LOAD(bpt, &node1, current.node);

      if (prev != NULL)
	{
	  if (bptx_prev_entry(gen, bpt, current, &previous, BPT_OPT_TREE) != 0)
	    {
	      fprintf(stderr, "[gen] cannot found the previous entry\n");
	      gen_exit(EXIT_FAILURE, "[KO]");
	    }

	  BPT_LOAD(bpt, &node2, previous.node);

	  if ((BPT_GET_ENTRY(gen, &node2, previous.ndi, key) != prev->key) ||
	      (BPT_GET_ENTRY(gen, &node2, previous.ndi, value) != prev->value))
	    {
	      BPT_UNLOAD(bpt, &node2);
	      BPT_UNLOAD(bpt, &node1);
	      fprintf(stderr, "[gen] bad key or value for the previous "
		      "entry\n");
	      gen_exit(EXIT_FAILURE, "[KO]");
	    }

	  BPT_UNLOAD(bpt, &node2);
	}

      if (nxt != NULL)
	{
	  if (bptx_next_entry(gen, bpt, current, &next, BPT_OPT_TREE) != 0)
	    {
	      fprintf(stderr, "[gen] cannot found the next entry\n");
	      gen_exit(EXIT_FAILURE, "[KO]");
	    }

	  BPT_LOAD(bpt, &node2, next.node);

	  if ((BPT_GET_ENTRY(gen, &node2, next.ndi, key) != nxt->key) ||
	      (BPT_GET_ENTRY(gen, &node2, next.ndi, value) != nxt->value))
	    {
	      BPT_UNLOAD(bpt, &node2);
	      BPT_UNLOAD(bpt, &node1);
	      fprintf(stderr, "[gen] bad key or value for the next entry\n");
	      gen_exit(EXIT_FAILURE, "[KO]");
	    }

	  BPT_UNLOAD(bpt, &node2);
	}

      BPT_UNLOAD(bpt, &node1);
    }

#ifdef GEN_DEBUG_GEN
  fprintf(stderr, "};\n");
#endif

}

void			gen_insert_entry(t_bpt(gen)		*bpt,
					 t_bpt_key(gen)		key,
					 t_bpt_addr(gen)	value)
{
  t_entry		*entry;
  t_entry		*prev;
  t_entry		*new;

  listsz++;

  new = malloc(sizeof(t_entry));

  new->key = key;
  new->value = value;
  new->prev = NULL;
  new->next = NULL;

  if (list == NULL)
    {
      list = new;
      return ;
    }

  for (entry = list, prev = NULL; entry != NULL; prev = entry,
	 entry = entry->next)
    if (entry->key > new->key)
      {
        new->prev = prev;
        new->next = entry;

        if (prev != NULL)
          prev->next = new;

	entry->prev = new;

	if (list == entry)
          list = new;

        return ;
      }

  prev->next = new;
  new->prev = prev;
}

void			gen_delete_entry(t_bpt(gen)		*bpt,
					 t_bpt_key(gen)		key)
{
  t_entry		*entry;

  listsz--;

  for (entry = list; entry != NULL; entry = entry->next)
    if (entry->key == key)
      {
        t_entry		*prev = entry->prev;
        t_entry		*next = entry->next;

        if (prev != NULL)
          prev->next = next;

        if (next != NULL)
          next->prev = prev;

        if (entry == list)
	  list = next;

	free(entry);

	return ;
      }
}

void			gen_modify_entry(t_bpt(gen)		*bpt,
					 t_bpt_key(gen)		key,
					 t_bpt_key(gen)		nkey,
					 t_bpt_addr(gen)	nvalue)
{
  t_entry		*entry;
  t_entry		*new;

  new = malloc(sizeof(t_entry));

  for (entry = list; entry != NULL; entry = entry->next)
    if (key == entry->key)
      {
	t_entry		*prev = entry->prev;
	t_entry		*next = entry->next;

	if (nkey == entry->key)
          {
            entry->value = nvalue;
            return ;
          }

	if ((prev == NULL) && (next == NULL))
          {
            entry->key = nkey;
            entry->value = nvalue;
            return ;
          }

	if (prev != NULL)
          prev->next = next;

	if (next != NULL)
          next->prev = prev;

	if (list == entry)
          list = next;

	gen_insert_entry(bpt, nkey, nvalue);

	free(entry);

	return ;
      }
}

int			gen_exist(t_bpt(gen)			*bpt,
				  t_bpt_key(gen)		key)
{
  t_entry		*entry;

  for (entry = list; entry != NULL; entry = entry->next)
    if (entry->key == key)
      return (0);

  return (-1);
}

int			gen_key(t_bpt(gen)			*bpt,
				t_bpt_key(gen)			*key)
{
  u_int64_t		rnd = rand() % listsz;
  t_entry		*entry;
  u_int64_t		i;

  for (i = 0, entry = list; entry != NULL; entry = entry->next, i++)
    if (i == rnd)
      {
	*key = entry->key;
	return (0);
      }

  return (-1);
}

int			gen_init(t_bpt(gen)			*bpt)
{
  if (bptx_init(gen, bpt, GEN_NODESZ, GEN_UNUSED_ADDR, GEN_UNUSED_KEY,
		GEN_UNUSED_VALUE, GEN_FLAGS, 50, bptx_load(gen),
		bptx_unload(gen), bptx_addrcmp(gen), bptx_keycmp(gen),
		bptx_valcmp(gen), NULL, NULL) != 0)
    return (-1);

  return (0);
}

int			gen_clean(t_bpt(gen)			*bpt)
{
  if (bptx_clean(gen, bpt) != 0)
    return (-1);

  return (0);
}

int			gen_rem(t_bpt(gen)			*bpt,
				u_int64_t			id)
{
  t_bpt_key(gen)	key;

  if (gen_key(bpt, &key) != 0)
    return (-1);

#ifdef GEN_DEBUG
  printf("[rem] %qu\n", (u_int64_t)key);
#endif

#ifdef GEN_DEBUG_SEQUENCE
  fprintf(stderr, "rem %qu\n", (u_int64_t)key);
#endif

#ifdef GEN_DEBUG_GEN
  fprintf(stderr, "  {	%qu,	"
	  "IN_REM,	%qu,		0,		0	"
	  "},\n",
	  (u_int64_t)id, (u_int64_t)key);
#endif

  if (bptx_remove(gen, bpt, key) != 0)
    {
      fprintf(stderr, "[gen] cannot remove an entry\n");
      gen_exit(EXIT_FAILURE, "[KO]\n");
    }

  gen_delete_entry(bpt, key);

  return (0);
}

int			gen_mod(t_bpt(gen)			*bpt,
				u_int64_t			id)
{
  t_bpt_lfentry(gen)	lfentry;
  t_bpt_key(gen)	key;

  if (gen_key(bpt, &key) != 0)
    return (-1);

  do
    {
      lfentry.key = rand() % GEN_KEY_MASK;
    } while ((gen_exist(bpt, lfentry.key) == 0) || (lfentry.key == bpt->ukey));

  do
    {
      lfentry.value = rand() % GEN_VALUE_MASK;
    } while (lfentry.value == bpt->uval);

#ifdef GEN_DEBUG
  printf("[mod] %qu | %qu %qu\n",
	 (u_int64_t)key, (u_int64_t)lfentry.key, (u_int64_t)lfentry.value);
#endif

#ifdef GEN_DEBUG_SEQUENCE
  fprintf(stderr, "mod %qu %qu %qu\n",
	  (u_int64_t)key, (u_int64_t)lfentry.key, (u_int64_t)lfentry.value);
#endif

#ifdef GEN_DEBUG_GEN
  fprintf(stderr, "  {	%qu,	"
	  "IN_MOD,	%qu,		%qu,		%qu	"
	  "},\n",
	  (u_int64_t)id, (u_int64_t)key,
	  (u_int64_t)lfentry.key, (u_int64_t)lfentry.value);
#endif

  if (bptx_modify(gen, bpt, key, &lfentry) != 0)
    {
      fprintf(stderr, "[gen] cannot modify an entry\n");
      gen_exit(EXIT_FAILURE, "[KO]\n");
    }

  gen_modify_entry(bpt, key, lfentry.key, lfentry.value);

  return (0);
}

int			gen_add(t_bpt(gen)			*bpt,
				u_int64_t			id)
{
  t_bpt_lfentry(gen)	lfentry;

  do
    {
      lfentry.key = rand() % GEN_KEY_MASK;
    } while ((gen_exist(bpt, lfentry.key) == 0) || (lfentry.key == bpt->ukey));

  do
    {
      lfentry.value = rand() % GEN_VALUE_MASK;
    } while (lfentry.value == bpt->uval);

#ifdef GEN_DEBUG
  printf("[add] %qu %qu\n",
	 (u_int64_t)lfentry.key, (u_int64_t)lfentry.value);
#endif

#ifdef GEN_DEBUG_SEQUENCE
  fprintf(stderr, "add %qu %qu\n",
	  (u_int64_t)lfentry.key, (u_int64_t)lfentry.value);
#endif

#ifdef GEN_DEBUG_GEN
  fprintf(stderr, "  {	%qu,	"
	  "IN_ADD,	0,		%qu,		%qu	"
	  "},\n",
	  (u_int64_t)id, (u_int64_t)lfentry.key, (u_int64_t)lfentry.value);
#endif

  if (bptx_add(gen, bpt, &lfentry) != 0)
    {
      fprintf(stderr, "[gen] cannot add an entry\n");
      gen_exit(EXIT_FAILURE, "[KO]\n");
    }

  gen_insert_entry(bpt, lfentry.key, lfentry.value);

  return (0);
}

int			main(int				argc,
			     char				**argv)
{
  t_bpt(gen)		bpt;
  u_int64_t		i;

  printf("[%-5s]				:		", "gen");

  fflush(stdout);

  if (gen_init(&bpt) != 0)
    {
      fprintf(stderr, "[gen] error during initialization\n");
      gen_exit(EXIT_FAILURE, "[KO]");
    }

  srand(time(0));

#ifdef GEN_DEBUG_GEN
  fprintf(stderr, "#define IN_INPUT_NOPS		%u\n\n", GEN_NOPS);
  fprintf(stderr, "t_in_input		input[IN_INPUT_NOPS] =\n");
  fprintf(stderr, "{\n");
#endif

  for (i = 0; i < GEN_NOPS; )
    {
      int		ret = 0;
      unsigned char	op;

      if (i <= GEN_CONSTRUCTOR)
	op = GEN_OP_ADD;
      else if (i >= GEN_DESTRUCTOR)
	op = GEN_OP_REM;
      else
	op = rand() % GEN_OP_MASK;

      if (op <= GEN_OP_ADD)
	ret = gen_add(&bpt, i);
      else if (op <= GEN_OP_REM)
	ret = gen_rem(&bpt, i);
      else if (op <= GEN_OP_MOD)
	ret = gen_mod(&bpt, i);

      if (ret == -1)
	continue;
      else
	i++;
    }

#ifdef GEN_DEBUG_GEN
  fprintf(stderr, "};\n\n");
#endif

#ifdef GEN_VERIFY
  gen_verify(&bpt);
#endif

  gen_clean(&bpt);

  if (___loaded != 0)
    {
      fprintf(stderr, "[gen] this are blocks loaded\n");
      gen_exit(EXIT_FAILURE, "[KO]\n");
    }

  if (___allocated != 0)
    {
      fprintf(stderr, "[check] there are blocks allocated: %qu\n",
	      ___allocated);
      gen_exit(EXIT_FAILURE, "[KO]\n");
    }

  gen_exit(EXIT_SUCCESS, "[OK]\n");

  return (0);
}
