/*
 * ---------- header ----------------------------------------------------------
 *
 * project       bpt
 *
 * license       BSD
 *
 * file          /home/mycure/bptx/test/sh.c
 *
 * created       julien quintard   [thu jul 12 17:28:12 2007]
 * updated       julien quintard   [sun jul 15 14:07:16 2007]
 */

#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * debug
 */

#undef BPT_DEBUG
#undef BPTX_DEBUG

#undef SH_DEBUG

/*
 * types
 */

#define SH_KEY_T		u_int32_t
#define SH_VALUE_T		u_int32_t
#define SH_ADDR_T		u_int32_t
#define SH_INTERVAL_T		int32_t

typedef struct			s_sh_inentry
{
  SH_KEY_T			key;
  SH_ADDR_T			value;
  SH_INTERVAL_T			interval;
}				t_sh_inentry;

typedef struct			s_sh_lfentry
{
  SH_KEY_T			key;
  SH_VALUE_T			value;
  SH_INTERVAL_T			interval;
  u_int32_t			id;
}				t_sh_lfentry;

/*
 * defines
 */

#define SH_BLKSZ		70
#define SH_UNUSED_ADDR		-1
#define SH_UNUSED_KEY		-1
#define SH_UNUSED_VALUE		-1

#define SH_FLAGS		BPT_FLAG_ZERO /* BPT_FLAG_COLLIDE | BPT_FLAG_CALLBACK */

/*
 * make the bpt tree
 */

#include "../bpt.h"

bpt_make(sh, BPT_NDI_T, BPT_UNI_T, BPT_NODES_T, BPT_HEIGHT_T,
	 SH_ADDR_T, SH_KEY_T, SH_VALUE_T, t_sh_inentry, t_sh_lfentry,
	 key, value);

#include "../bptx.h"

bptx_types(sh);

bptx_wrapper(sh, (void*)malloc, (void*)free);

bptx_storage(sh, RAM);

bptx_compare(sh, address, scalar);
bptx_compare(sh, key, scalar);
bptx_compare(sh, value, scalar);

/*
 * command defines
 */

#define SH_ADD			"add"
#define SH_MOD			"mod"
#define SH_REM			"rem"
#define SH_COLL_MOD		"cmod"
#define SH_COLL_REM		"crem"
#define SH_COLL_DUMP		"cdump"
#define SH_LIST_DUMP		"ldump"
#define SH_DUMP			"dump"
#define SH_INFO			"info"
#define SH_REINIT		"reinit"
#define SH_QUIT			"quit"
#define SH_HELP			"help"

/*
 * global variables
 */

unsigned int    ___loaded = 0;
unsigned int    ___allocated = 0;

/*
 * prototypes
 */

SH_INTERVAL_T		sh_get_interval(t_bpt(sh)		*bpt,
					t_bpt_imm(sh)		*node);

void			sh_callback_update_node(t_bpt(sh)	*bpt,
						t_bpt_imm(sh)	*node,
						t_bpt_node(sh)	addr,
						SH_INTERVAL_T	interval);

void			sh_callback_update(t_bpt(sh)		*bpt,
					   t_bpt_imm(sh)	*node);

void			sh_callback_interval(t_bpt(sh)		*bpt,
					     t_bpt_imm(sh)	*node1,
					     t_bpt_ndi(sh)	ndi);

void			sh_callback_insert(t_bpt(sh)		*bpt,
					   t_bpt_cbctx(sh)	*cbctx);

void			sh_callback_split(t_bpt(sh)		*bpt,
					  t_bpt_cbctx(sh)	*cbctx);

void			sh_callback_modify(t_bpt(sh)		*bpt,
					   t_bpt_cbctx(sh)	*cbctx);

void			sh_callback_delete(t_bpt(sh)		*bpt,
					   t_bpt_cbctx(sh)	*cbctx);

void			sh_callback_migrate(t_bpt(sh)		*bpt,
					    t_bpt_cbctx(sh)	*cbctx);

void			sh_callback_balance(t_bpt(sh)		*bpt,
					    t_bpt_cbctx(sh)	*cbctx);

void			sh_callback(t_bpt(sh)		*bpt,
				    t_bpt_cbctx(sh)	*cbctx);

int			sh_init(t_bpt(sh)			*bpt);

int			sh_clean(t_bpt(sh)		*bpt);

unsigned int		sh_nargs(char			**cmds);

char			**sh_cut(char			*line,
				 char			*sep);

void			sh_add(t_bpt(sh)		*bpt,
			       char			**cmds);

void			sh_mod(t_bpt(sh)		*bpt,
			       char			**cmds);

void			sh_coll_mod(t_bpt(sh)		*bpt,
				    char		**cmds);

void			sh_rem(t_bpt(sh)		*bpt,
			       char			**cmds);

void			sh_coll_rem(t_bpt(sh)		*bpt,
				    char		**cmds);

void			sh_coll_dump(t_bpt(sh)		*bpt,
				     char		**cmds);

void			sh_dump_entry(t_bpt(sh)		*bpt,
				      t_bpt_imm(sh)	*node,
				      t_bpt_ndi(sh)	i);

void			sh_list_dump(t_bpt(sh)		*bpt,
				     char		**cmds);

void			sh_dump_node(t_bpt(sh)		*bpt,
				     t_bpt_imm(sh)	*node,
				     t_bpt_height(sh)	level);

void			sh_dump_tree(t_bpt(sh)		*bpt);

void			sh_dump(t_bpt(sh)		*bpt,
				char			**cmds);

void			sh_help(t_bpt(sh)		*bpt,
				char			**cmds);

void			sh_info(t_bpt(sh)		*bpt,
				char			**cmds);

void			sh_reinit(t_bpt(sh)		*bpt,
				  char			**cmds);

void			sh_quit(t_bpt(sh)		*bpt,
				char			**cmds);

void			sh_cmd(t_bpt(sh)		*bpt,
			       char			**cmds);

/*
 * functions in relation with bpt library
 */

SH_INTERVAL_T		sh_get_interval(t_bpt(sh)		*bpt,
					t_bpt_imm(sh)		*node)
{

  /*
   * we decide to keep the higher interval in each internal node
   */

  t_bpt_ndi(sh)		nkeys = BPT_NKEYS(sh, bpt, node);
  SH_INTERVAL_T		interval = -1;
  t_bpt_ndi(sh)		i;

  for (i = 0; (i < nkeys) &&
	 (BPT_GET_ENTRY(sh, node, i, key) != bpt->ukey);
       i++)
    {
      if (i == 0)
	interval = BPT_GET_ENTRY(sh, node, i, interval);

      if (interval < BPT_GET_ENTRY(sh, node, i, interval))
	interval = BPT_GET_ENTRY(sh, node, i, interval);
    }

  return (interval);
}

void			sh_callback_update_node(t_bpt(sh)	*bpt,
						t_bpt_imm(sh)	*node,
						t_bpt_node(sh)	addr,
						SH_INTERVAL_T	interval)
{
  t_bpt_imm(sh)		parent;
  t_bpt_ndi(sh)		ndi;

  /*
   * we use the node's address to retrieve the parent node entry that points
   * to the node to update.
   */

  if (bpt_ndi(sh, bpt, node, addr, &ndi) != 0)
    return ;

  if (interval == BPT_GET_ENTRY(sh, node, ndi, interval))
    return;

  BPT_SET_ENTRY(sh, node, ndi, interval, interval);

  if (BPT_GET_HEAD(sh, node, parent) == bpt->uaddr)
    return ;

  if ((interval = sh_get_interval(bpt, node)) == -1)
    return;

  BPT_LOAD(bpt, &parent, BPT_GET_HEAD(sh, node, parent));
  sh_callback_update_node(bpt, &parent, node->addr, interval);
  BPT_UNLOAD(bpt, &parent);  
}

void			sh_callback_update(t_bpt(sh)		*bpt,
					   t_bpt_imm(sh)	*node)
{
  SH_INTERVAL_T		interval;
  t_bpt_imm(sh)		parent;

  if (BPT_GET_HEAD(sh, node, parent) == bpt->uaddr)
    return;

  if ((interval = sh_get_interval(bpt, node)) == -1)
    return;

  BPT_LOAD(bpt, &parent, BPT_GET_HEAD(sh, node, parent));
  sh_callback_update_node(bpt, &parent, node->addr, interval);
  BPT_UNLOAD(bpt, &parent);  
}

void			sh_callback_interval(t_bpt(sh)		*bpt,
					     t_bpt_imm(sh)	*node1,
					     t_bpt_ndi(sh)	ndi)
{
  t_bpt_entry(sh)	current = { node1->addr, ndi };
  SH_INTERVAL_T		interval;
  t_bpt_imm(sh)		node2;
  t_bpt_entry(sh)	next;

  if (bpt_next_entry(sh, bpt, current, &next, BPT_OPT_TREE) == 0)
    {
      BPT_LOAD(bpt, &node2, next.node);

      interval = BPT_GET_ENTRY(sh, &node2, next.ndi, key) -
	(BPT_GET_ENTRY(sh, node1, current.ndi, key) +
	 BPT_GET_ENTRY(sh, node1, current.ndi, value));

      BPT_SET_ENTRY(sh, node1, current.ndi, interval, interval);

      BPT_UNLOAD(bpt, &node2);
    }
  else
    BPT_SET_ENTRY(sh, node1, current.ndi, interval, 0);
}

void			sh_callback_insert(t_bpt(sh)		*bpt,
					   t_bpt_cbctx(sh)	*cbctx)
{
  t_bpt_imm(sh)		update;
  t_bpt_imm(sh)		node1;
  t_bpt_entry(sh)	prev;

  BPT_LOAD(bpt, &node1, cbctx->current.node);
  sh_callback_interval(bpt, &node1, cbctx->current.ndi);
  BPT_UNLOAD(bpt, &node1);

  if (bpt_prev_entry(sh, bpt, cbctx->current, &prev, BPT_OPT_TREE) == 0)
    {
      t_bpt_imm(sh)	node2;

      BPT_LOAD(bpt, &node2, prev.node);
      sh_callback_interval(bpt, &node2, prev.ndi);
      sh_callback_update(bpt, &node2);
      BPT_UNLOAD(bpt, &node2);
    }

  BPT_LOAD(bpt, &update, cbctx->node);
  sh_callback_update(bpt, &update);
  BPT_UNLOAD(bpt, &update);
}

void			sh_callback_split(t_bpt(sh)		*bpt,
					  t_bpt_cbctx(sh)	*cbctx)
{
  t_bpt_imm(sh)		update;
  t_bpt_imm(sh)		node1;
  t_bpt_entry(sh)	prev;

  BPT_LOAD(bpt, &node1, cbctx->current.node);
  sh_callback_interval(bpt, &node1, cbctx->current.ndi);
  BPT_UNLOAD(bpt, &node1);

  if (bpt_prev_entry(sh, bpt, cbctx->current, &prev, BPT_OPT_TREE) == 0)
    {
      t_bpt_imm(sh)	node2;

      BPT_LOAD(bpt, &node2, prev.node);
      sh_callback_interval(bpt, &node2, prev.ndi);
      sh_callback_update(bpt, &node2);
      BPT_UNLOAD(bpt, &node2);
    }

  BPT_LOAD(bpt, &update, cbctx->node1);
  sh_callback_update(bpt, &update);
  BPT_UNLOAD(bpt, &update);

  BPT_LOAD(bpt, &update, cbctx->node2);
  sh_callback_update(bpt, &update);
  BPT_UNLOAD(bpt, &update);
}

void			sh_callback_modify(t_bpt(sh)		*bpt,
					   t_bpt_cbctx(sh)	*cbctx)
{
  t_bpt_imm(sh)		update;
  t_bpt_imm(sh)		node;

  BPT_LOAD(bpt, &node, cbctx->current.node);
  sh_callback_interval(bpt, &node, cbctx->current.ndi);
  BPT_UNLOAD(bpt, &node);

  BPT_LOAD(bpt, &update, cbctx->node);
  sh_callback_update(bpt, &update);
  BPT_UNLOAD(bpt, &update);
}

void			sh_callback_delete(t_bpt(sh)		*bpt,
					   t_bpt_cbctx(sh)	*cbctx)
{
  t_bpt_imm(sh)		update;
  t_bpt_imm(sh)		node;

  if (cbctx->previous.node != bpt->uaddr)
    {
      BPT_LOAD(bpt, &node, cbctx->previous.node);
      sh_callback_interval(bpt, &node, cbctx->previous.ndi);
      BPT_UNLOAD(bpt, &node);
    }

  BPT_LOAD(bpt, &update, cbctx->node);
  sh_callback_update(bpt, &update);
  BPT_UNLOAD(bpt, &update);
}

void			sh_callback_migrate(t_bpt(sh)		*bpt,
					    t_bpt_cbctx(sh)	*cbctx)
{
  t_bpt_imm(sh)		update;
  t_bpt_imm(sh)		node;

  if (cbctx->previous.node != bpt->uaddr)
    {
      BPT_LOAD(bpt, &node, cbctx->previous.node);
      sh_callback_interval(bpt, &node, cbctx->previous.ndi);
      BPT_UNLOAD(bpt, &node);
    }

  BPT_LOAD(bpt, &update, cbctx->node);
  sh_callback_update(bpt, &update);
  BPT_UNLOAD(bpt, &update);
}

void			sh_callback_balance(t_bpt(sh)		*bpt,
					    t_bpt_cbctx(sh)	*cbctx)
{
  t_bpt_imm(sh)		update;
  t_bpt_imm(sh)		node;

  if (cbctx->previous.node != bpt->uaddr)
    {
      BPT_LOAD(bpt, &node, cbctx->previous.node);
      sh_callback_interval(bpt, &node, cbctx->previous.ndi);
      BPT_UNLOAD(bpt, &node);
    }

  BPT_LOAD(bpt, &update, cbctx->node1);
  sh_callback_update(bpt, &update);
  BPT_UNLOAD(bpt, &update);

  BPT_LOAD(bpt, &update, cbctx->node2);
  sh_callback_update(bpt, &update);
  BPT_UNLOAD(bpt, &update);
}

void			sh_callback(t_bpt(sh)			*bpt,
				    t_bpt_cbctx(sh)		*cbctx)
{

#if 0
  printf("---[callback][0x%x] [prev] %d:%d [current] %d:%d [node] %d "
	 "[node1] %d [node2] %d\n",
	 cbctx->cb, cbctx->previous.node, cbctx->previous.ndi,
	 cbctx->current.node, cbctx->current.ndi,
	 cbctx->node, cbctx->node1, cbctx->node2);
#endif

  switch (cbctx->cb)
    {
    case BPT_CB_INSERT:
      sh_callback_insert(bpt, cbctx);
      break;
    case BPT_CB_SPLIT:
      sh_callback_split(bpt, cbctx);
      break;
    case BPT_CB_MODIFY:
      sh_callback_modify(bpt, cbctx);
      break;
    case BPT_CB_DELETE:
      sh_callback_delete(bpt, cbctx);
      break;
    case BPT_CB_MIGRATE:
      sh_callback_migrate(bpt, cbctx);
      break;
    case BPT_CB_BALANCE:
      sh_callback_balance(bpt, cbctx);
      break;
    }
}

/*
 * functions
 */

int			sh_init(t_bpt(sh)			*bpt)
{
  if (bptx_init(sh, bpt, SH_BLKSZ, SH_UNUSED_ADDR, SH_UNUSED_KEY,
		SH_UNUSED_VALUE, SH_FLAGS, 10, bptx_load(sh), bptx_unload(sh),
		bptx_addrcmp(sh), bptx_keycmp(sh), bptx_valcmp(sh),
		sh_callback, NULL) != 0)
    return (-1);

  return (0);
}

int			sh_clean(t_bpt(sh)			*bpt)
{
  if (bptx_clean(sh, bpt) != 0)
    return (-1);

  return (0);
}

unsigned int		sh_nargs(char				**cmds)
{
  unsigned int		i;

  for (i = 0; cmds[i]; i++)
    ;

  return (i);
}

char			**sh_cut(char				*line,
				 char				*sep)
{
  char			**data;
  unsigned long		cnt;
  unsigned long		i;
  unsigned long		p;

  for (p = 0, i = 0, cnt = 0; line[i]; cnt++)
    {
      while (line[i] && (strncmp(line + i, sep, strlen(sep)) == 0))
        i += strlen(sep);
      p = i;
      while (line[i] && (strncmp(line + i, sep, strlen(sep)) != 0))
        i += strlen(sep);
    }

  data = malloc((cnt + 1) * sizeof(char *));

  for (p = 0, i = 0, cnt = 0; line[i]; )
    {
      while (line[i] && (strncmp(line + i, sep, strlen(sep)) == 0))
        i += strlen(sep);
      p = i;
      while (line[i] && (strncmp(line + i, sep, strlen(sep)) != 0))
        i += strlen(sep);

      if (p != i)
        {
          data[cnt] = malloc((i - p + 1) * sizeof(char));
          strncpy(data[cnt], line + p, i - p);
          data[cnt++][i - p] = 0;
        }
    }
  data[cnt] = NULL;

  return (data);
}


void			sh_add(t_bpt(sh)			*bpt,
			       char				**cmds)
{
  t_bpt_lfentry(sh)	lfentry;

  if (sh_nargs(cmds) != 3)
    {
      fprintf(stderr, "[sh] syntax: add [key] [value]\n");
      return ;
    }

  lfentry.key = strtoull(cmds[1], NULL, 0);
  lfentry.value = strtoull(cmds[2], NULL, 0);
  lfentry.interval = 0;

  if (bptx_add(sh, bpt, &lfentry) != 0)
    {
      fprintf(stderr, "[sh] cannot add an entry\n");
      return ;
    }
}

void			sh_mod(t_bpt(sh)			*bpt,
			       char				**cmds)
{
  t_bpt_lfentry(sh)	lfentry;
  t_bpt_key(sh)		key;

  if (sh_nargs(cmds) != 4)
    {
      fprintf(stderr, "[sh] syntax: mod [oldkey] [newkey] [newvalue]\n");
      return ;
    }

  key = strtoull(cmds[1], NULL, 0);

  lfentry.key = strtoull(cmds[2], NULL, 0);
  lfentry.value = strtoull(cmds[3], NULL, 0);
  lfentry.interval = 0;

  if (bptx_modify(sh, bpt, key, &lfentry) != 0)
    {
      fprintf(stderr, "[sh] cannot modify an entry\n");
      return ;
    }
}

void			sh_coll_mod(t_bpt(sh)			*bpt,
				    char			**cmds)
{
  t_bpt_lfentry(sh)	lfentry;
  t_bpt_entry(sh)	entry;
  t_bpt_value(sh)	value;
  t_bpt_key(sh)		key;

  if (sh_nargs(cmds) != 5)
    {
      fprintf(stderr, "[sh] syntax: cmod [oldkey] [oldvalue] [newkey] "
		"[newvalue]\n");
      return ;
    }

  key = strtoull(cmds[1], NULL, 0);
  value = strtoull(cmds[2], NULL, 0);

  lfentry.key = strtoull(cmds[3], NULL, 0);
  lfentry.value = strtoull(cmds[4], NULL, 0);
  lfentry.interval = 0;

  if (bptx_collide_search(sh, bpt, key, value, &entry) != 0)
    {
      fprintf(stderr, "[sh] cannot find the entry\n");
      return ;
    }

  if (bptx_collide_modify(sh, bpt, entry, &lfentry) != 0)
    {
      fprintf(stderr, "[sh] cannot collide modify an entry\n");
      return ;
    }
}

void			sh_rem(t_bpt(sh)			*bpt,
			       char				**cmds)
{
  t_bpt_key(sh)		key;

  if (sh_nargs(cmds) != 2)
    {
      fprintf(stderr, "[sh] syntax: rem [key]\n");
      return ;
    }

  key = strtoull(cmds[1], NULL, 0);

  if (bptx_remove(sh, bpt, key) != 0)
    {
      fprintf(stderr, "[sh] cannot remove an entry\n");
      return ;
    }
}

void			sh_coll_rem(t_bpt(sh)			*bpt,
				    char			**cmds)
{
  t_bpt_entry(sh)	entry;
  t_bpt_value(sh)	value;
  t_bpt_key(sh)		key;

  if (sh_nargs(cmds) != 3)
    {
      fprintf(stderr, "[sh] syntax: crem [key] [value]\n");
      return ;
    }

  key = strtoull(cmds[1], NULL, 0);
  value = strtoull(cmds[2], NULL, 0);

  if (bptx_collide_search(sh, bpt, key, value, &entry) != 0)
    {
      fprintf(stderr, "[sh] cannot find the entry\n");
      return ;
    }

  if (bptx_collide_remove(sh, bpt, entry) != 0)
    {
      fprintf(stderr, "[sh] cannot remove an entry\n");
      return ;
    }
}

void			sh_coll_dump(t_bpt(sh)			*bpt,
				     char			**cmds)
{
  t_bpt_entry(sh)	entry;
  t_bpt_imm(sh)		node;
  t_bpt_key(sh)		key;

  if (sh_nargs(cmds) != 2)
    {
      fprintf(stderr, "[sh] syntax: cdump [key]\n");
      return ;
    }

  key = strtoull(cmds[1], NULL, 0);

  if (bptx_search(sh, bpt, key, &entry) != 0)
    {
      fprintf(stderr, "[sh] cannot find the entry\n");
      return ;
    }

  do
    {
      BPT_LOAD(bpt, &node, entry.node);

      printf("   [node] %qu   [ndi] %qu   [key] %qu   [value] %qu\n",
	     (u_int64_t)entry.node, (u_int64_t)entry.ndi,
	     BPT_GET_ENTRY(sh, &node, entry.ndi, key) == bpt->ukey ?
	     -1 : (u_int64_t)BPT_GET_ENTRY(sh, &node, entry.ndi, key),
	     BPT_GET_ENTRY(sh, &node, entry.ndi, key) == bpt->ukey ?
	     -1 : (u_int64_t)BPT_GET_ENTRY(sh, &node, entry.ndi, value));

      BPT_UNLOAD(bpt, &node);
    } while (bptx_collide_next(sh, bpt, key, &entry) == 0);
}

void			sh_dump_entry(t_bpt(sh)			*bpt,
				      t_bpt_imm(sh)		*node,
				      t_bpt_ndi(sh)		i)
{
  printf("[entry %3u] k: %10qd\t\tv: %10qd\t\ti: %10qd\n",
	 i,
         BPT_GET_ENTRY(sh, node, i, key) == bpt->ukey ?
         -1 : (int64_t)BPT_GET_ENTRY(sh, node, i, key),
         BPT_GET_ENTRY(sh, node, i, key) == bpt->ukey ?
         -1 : (int64_t)BPT_GET_ENTRY(sh, node, i, value),
         BPT_GET_ENTRY(sh, node, i, key) == bpt->ukey ?
         -1 : (int64_t)BPT_GET_ENTRY(sh, node, i, interval));
}

void			sh_list_dump(t_bpt(sh)			*bpt,
				     char			**cmds)
{
  t_bpt_entry(sh)	current;
  t_bpt_entry(sh)	entry;
  t_bpt_imm(sh)		node;

  if (sh_nargs(cmds) != 2)
    {
      fprintf(stderr, "[chk] syntax: ldump [option{front,back}]\n");
      return ;
    }

  if (strcmp(cmds[1], "front") == 0)
    {
      BPT_LOAD(bpt, &node, bpt->root);

      if (bptx_list(sh, bpt, &node, &entry, BPT_OPT_HEAD) != 0)
	{
	  BPT_UNLOAD(bpt, &node);
	  return ;
	}

      BPT_UNLOAD(bpt, &node);
      BPT_LOAD(bpt, &node, entry.node);

      do
	{
	  if (node.addr != entry.node)
	    {
	      BPT_UNLOAD(bpt, &node);
	      BPT_LOAD(bpt, &node, entry.node);
	    }

	  sh_dump_entry(bpt, &node, entry.ndi);

	  current.node = node.addr;
	  current.ndi = entry.ndi;
	} while (bptx_next_entry(sh, bpt, current, &entry, BPT_OPT_TREE) == 0);

      BPT_UNLOAD(bpt, &node);
    }
  else if (strcmp(cmds[1], "back") == 0)
    {
      BPT_LOAD(bpt, &node, bpt->root);

      if (bptx_list(sh, bpt, &node, &entry, BPT_OPT_TAIL) != 0)
	{
	  BPT_UNLOAD(bpt, &node);
	  return ;
	}

      BPT_UNLOAD(bpt, &node);
      BPT_LOAD(bpt, &node, entry.node);

      do
	{
	  if (node.addr != entry.node)
	    {
	      BPT_UNLOAD(bpt, &node);
	      BPT_LOAD(bpt, &node, entry.node);
	    }

	  sh_dump_entry(bpt, &node, entry.ndi);

	  current.node = node.addr;
	  current.ndi = entry.ndi;
	} while (bptx_prev_entry(sh, bpt, current, &entry, BPT_OPT_TREE) == 0);

      BPT_UNLOAD(bpt, &node);
    }
  else
    printf("[chk] unknown option\n");
}

#define		SH_INDENT(_level_)					\
  {									\
    int		_i_;							\
									\
    for (_i_ = 0; _i_ < (_level_ * 3); _i_++)				\
      printf(" ");							\
  }

void			sh_dump_node(t_bpt(sh)			*bpt,
				     t_bpt_imm(sh)		*node,
				     t_bpt_height(sh)		level)
{
  t_bpt_ndi(sh)		nkeys = BPT_NKEYS(sh, bpt, node);
  t_bpt_imm(sh)		child;
  t_bpt_ndi(sh)		i;

  SH_INDENT(level);

  printf("[head] t: ");
  if (BPT_GET_HEAD(sh, node, type) == BPT_TYPE_INTERNAL)
    printf("internal");
  else
    printf("leaf");

  printf(" (%qu)   parent: %qd   prv: %qd   nxt: %qd\n",
	 (int64_t)node->addr,
         BPT_GET_HEAD(sh, node, parent) == bpt->uaddr ?
	 -1 : (int64_t)BPT_GET_HEAD(sh, node, parent),
         BPT_GET_HEAD(sh, node, prv) == bpt->uaddr ?
	 -1 : (int64_t)BPT_GET_HEAD(sh, node, prv),
         BPT_GET_HEAD(sh, node, nxt) == bpt->uaddr ?
	 -1 : (int64_t)BPT_GET_HEAD(sh, node, nxt)); 

  for (i = 0; i < nkeys; i++)
    {
      SH_INDENT(level);

      sh_dump_entry(bpt, node, i);

      if ((BPT_GET_HEAD(sh, node, type) == BPT_TYPE_INTERNAL) &&
	  (BPT_GET_ENTRY(sh, node, i, key) != bpt->ukey))
	{
	  BPT_LOAD(bpt, &child, BPT_GET_ENTRY(sh, node, i, value));

	  sh_dump_node(bpt, &child, level + 1);

	  BPT_UNLOAD(bpt, &child);
	}
    }
}

void			sh_dump_tree(t_bpt(sh)			*bpt)
{
  t_bpt_imm(sh)		root;

  BPT_LOAD(bpt, &root, bpt->root);
  sh_dump_node(bpt, &root, 0);
  BPT_UNLOAD(bpt, &root);
}

void			sh_dump(t_bpt(sh)			*bpt,
				char				**cmds)
{
  sh_dump_tree(bpt);
}

void			sh_help(t_bpt(sh)			*bpt,
				char				**cmds)
{
  printf("\n---[ help\n");
  printf("add:\t\t\t\t add [key] [value]\n");
  printf("modify:\t\t\t\t mod [oldkey] [newkey] [newvalue]\n");
  printf("collide modify:\t\t\t cmod [oldkey] [oldvalue] [newkey] "
	 "[newvalue]\n");
  printf("dump collisions:\t\t cdump [key]\n");
  printf("remove:\t\t\t\t rem [key]\n");
  printf("collide remove:\t\t\t crem [key] [value]\n");
  printf("dump list:\t\t\t ldump [option{front,back}]\n");
  printf("dump sh:\t\t\t dump\n");
  printf("info:\t\t\t\t info\n");
  printf("reinit:\t\t\t\t reinit\n");
  printf("quit:\t\t\t\t quit\n");
  printf("help:\t\t\t\t help\n");
}

void			sh_info(t_bpt(sh)			*bpt,
				char				**cmds)
{
  printf("---[ loaded:\t\t\t%u\n", ___loaded);
  printf("---[ allocated:\t\t\t%u\n", ___allocated);
}

void			sh_reinit(t_bpt(sh)			*bpt,
				  char				**cmds)
{
  sh_clean(bpt);

  if (___loaded != 0)
    {
      fprintf(stderr, "[sh] there are blocks loaded\n");
      exit(EXIT_FAILURE);
    }

  if (___allocated != 0)
    {
      fprintf(stderr, "[sh] there are blocks allocated: %u\n", ___allocated);
      exit(EXIT_FAILURE);
    }

  if (sh_init(bpt) != 0)
    {
      fprintf(stderr, "[sh] cannot reinitialize the tree\n");
      exit(EXIT_FAILURE);
    }
}

void			sh_quit(t_bpt(sh)			*bpt,
				char				**cmds)
{
  sh_clean(bpt);

  if (___loaded != 0)
    {
      fprintf(stderr, "[sh] there are blocks loaded\n");
      exit(EXIT_FAILURE);
    }

  if (___allocated != 0)
    {
      fprintf(stderr, "[sh] there are blocks allocated: %u\n", ___allocated);
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);
}

void			sh_cmd(t_bpt(sh)			*bpt,
			       char				**cmds)
{
  if (sh_nargs(cmds) == 0)
    {
      fprintf(stderr, "unknown command\n");
      sh_help(bpt, cmds);
      return ;
    }

  if (strcmp(cmds[0],  SH_ADD) == 0)
    sh_add(bpt, cmds);
  else if (strcmp(cmds[0], SH_MOD) == 0)
    sh_mod(bpt, cmds);
  else if (strcmp(cmds[0], SH_COLL_MOD) == 0)
    sh_coll_mod(bpt, cmds);
  else if (strcmp(cmds[0], SH_REM) == 0)
    sh_rem(bpt, cmds);
  else if (strcmp(cmds[0], SH_COLL_REM) == 0)
    sh_coll_rem(bpt, cmds);
  else if (strcmp(cmds[0], SH_COLL_DUMP) == 0)
    sh_coll_dump(bpt, cmds);
  else if (strcmp(cmds[0], SH_LIST_DUMP) == 0)
    sh_list_dump(bpt, cmds);
  else if (strcmp(cmds[0], SH_DUMP) == 0)
    sh_dump(bpt, cmds);
  else if (strcmp(cmds[0], SH_HELP) == 0)
    sh_help(bpt, cmds);
  else if (strcmp(cmds[0], SH_INFO) == 0)
    sh_info(bpt, cmds);
  else if (strcmp(cmds[0], SH_REINIT) == 0)
    sh_reinit(bpt, cmds);
  else if (strcmp(cmds[0], SH_QUIT) == 0)
    sh_quit(bpt, cmds);
  else
    {
      fprintf(stderr, "%s: unknown command\n", cmds[0]);
      sh_help(bpt, cmds);
    }
}

int			main(int				argc,
			     char				**argv)
{
  t_bpt(sh)		bpt;

  if (sh_init(&bpt) != 0)
    {
      fprintf(stderr, "[sh] cannot initialize the tree\n");
      exit(EXIT_FAILURE);
    }

  while (1)
    {
      char		buffer[2048];
      char		**data;
      int		length;
      int		i;

      memset(buffer, 0x0, 2048);

      printf("[sh]# ");
      fflush(stdout);
      length = read(0, buffer, 2048);
      buffer[length - 1] = 0;

      data = sh_cut(buffer, " ");

      sh_cmd(&bpt, data);

      for (i = 0; data[i]; i++)
	free(data[i]);
      free(data);
    }

  sh_quit(&bpt, NULL);

  return (0);
}
