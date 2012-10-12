/*
 * ---------- header ----------------------------------------------------------
 *
 * project       bpt
 *
 * license       BSD
 *
 * file          /home/mycure/bptx/bptx.h
 *
 * created       julien quintard   [wed jul 11 17:19:36 2007]
 * updated       julien quintard   [sun jul 15 20:31:18 2007]
 */

#ifndef BPTX_H
#define BPTX_H

/*
 * ---------- macros ----------------------------------------------------------
 */

/*
 * includes
 */

#include <bpt.h>

#include <string.h>

/*
 * version
 */

#define BPTX_VERSION	"0.17"

/*
 * ---------- debug macro -----------------------------------------------------
 */

#ifdef BPTX_DEBUG
# define	bptx_debug(_stream_, _fmt_...)                                \
  {                                                                           \
    fprintf((_stream_), "[%s:%u] ", __FILE__, __LINE__);                      \
    fprintf((_stream_), ##_fmt_);                                             \
  }
#else
# define	bptx_debug(_stream_, _fmt_...)
#endif

/*
 * ---------- interface -------------------------------------------------------
 */

#define bptx_init(T, _bpt_, _nodesz_, _uaddr_, _arguments_...)                \
  (                                                                           \
    {                                                                         \
      t_bpt_uni(T)	_alloc_ = BPT_INIT_ALLOC();                           \
      t_bpt_uni(T)	_size_ = BPT_INIT_SIZE();                             \
      t_bpt_unused(T)	_unused_;                                             \
      int		_r_;                                                  \
                                                                              \
      bptx_prolog(T, _nodesz_, _uaddr_, _alloc_, _size_, _unused_);           \
                                                                              \
      _r_ = bpt_init(T, _bpt_, _nodesz_, _uaddr_, _arguments_, &_unused_);    \
                                                                              \
      bptx_epilog(T, _unused_, _uaddr_, _size_);                              \
                                                                              \
      _r_;                                                                    \
    }                                                                         \
  )

#define bptx_add(T, _bpt_, _arguments_...)                                    \
  (                                                                           \
    {                                                                         \
      t_bpt_uni(T)	_alloc_ = BPT_ADD_ALLOC(_bpt_);                       \
      t_bpt_uni(T)	_size_ = BPT_ADD_SIZE(_bpt_);                         \
      t_bpt_unused(T)	_unused_;                                             \
      int		_r_;                                                  \
                                                                              \
      bptx_prolog(T, (_bpt_)->nodesz, (_bpt_)->uaddr, _alloc_,                \
                  _size_, _unused_);                                          \
                                                                              \
      _r_ = bpt_add(T, _bpt_, _arguments_, &_unused_);                        \
                                                                              \
      bptx_epilog(T, _unused_, (_bpt_)->uaddr, _size_);                       \
                                                                              \
      _r_;                                                                    \
    }                                                                         \
  )

#define bptx_modify(T, _bpt_, _arguments_...)                                 \
  (                                                                           \
    {                                                                         \
      t_bpt_uni(T)	_alloc_ = BPT_MODIFY_ALLOC(_bpt_);                    \
      t_bpt_uni(T)	_size_ = BPT_MODIFY_SIZE(_bpt_);                      \
      t_bpt_unused(T)	_unused_;                                             \
      int		_r_;                                                  \
                                                                              \
      bptx_prolog(T, (_bpt_)->nodesz, (_bpt_)->uaddr, _alloc_,                \
                  _size_, _unused_);                                          \
                                                                              \
      _r_ = bpt_modify(T, _bpt_, _arguments_, &_unused_);                     \
                                                                              \
      bptx_epilog(T, _unused_, (_bpt_)->uaddr, _size_);                       \
                                                                              \
      _r_;                                                                    \
    }                                                                         \
  )

#define bptx_remove(T, _bpt_, _arguments_...)                                 \
  (                                                                           \
    {                                                                         \
      t_bpt_uni(T)	_alloc_ = BPT_REMOVE_ALLOC(_bpt_);                    \
      t_bpt_uni(T)	_size_ = BPT_REMOVE_SIZE(_bpt_);                      \
      t_bpt_unused(T)	_unused_;                                             \
      int		_r_;                                                  \
                                                                              \
      bptx_prolog(T, (_bpt_)->nodesz, (_bpt_)->uaddr, _alloc_,                \
                  _size_, _unused_);                                          \
                                                                              \
      _r_ = bpt_remove(T, _bpt_, _arguments_, &_unused_);                     \
                                                                              \
      bptx_epilog(T, _unused_, (_bpt_)->uaddr, _size_);                       \
                                                                              \
      _r_;                                                                    \
    }                                                                         \
  )

#define bptx_search(_arguments_...)                                           \
  bpt_search(_arguments_)

#define bptx_clean(T, _bpt_)                                                  \
  (                                                                           \
    {                                                                         \
      t_bpt_uni(T)	_alloc_ = BPT_CLEAN_ALLOC(_bpt_);                     \
      t_bpt_uni(T)	_size_ = BPT_CLEAN_SIZE(_bpt_);                       \
      t_bpt_unused(T)	_unused_;                                             \
      int		_r_;                                                  \
                                                                              \
      bptx_prolog(T, (_bpt_)->nodesz, (_bpt_)->uaddr, _alloc_,                \
                  _size_, _unused_);                                          \
                                                                              \
      _r_ = bpt_clean(T, _bpt_, &_unused_);                                   \
                                                                              \
      bptx_epilog(T, _unused_, (_bpt_)->uaddr, _size_);                       \
                                                                              \
      _r_;                                                                    \
    }                                                                         \
  )

#define bptx_first_entry(_arguments_...)                                      \
  bpt_first_entry(_arguments_)

#define bptx_last_entry(_arguments_...)                                       \
  bpt_list(_arguments_)

#define bptx_prev_entry(_arguments_...)                                       \
  bpt_prev_entry(_arguments_)

#define bptx_next_entry(_arguments_...)                                       \
  bpt_next_entry(_arguments_)

#define bptx_search_entry(_arguments_...)                                     \
  bpt_search_entry(_arguments_)

#define bptx_node_size(_arguments_...)                                        \
  bpt_node_size(_arguments_)

#define bptx_list(_arguments_...)                                             \
  bpt_list(_arguments_)

#define bptx_key(_arguments_...)                                              \
  bpt_key(_arguments_)

#define bptx_update(_arguments_...)                                           \
  bpt_update(_arguments_)

#define bptx_foreach(_arguments_...)                                          \
  bpt_foreach(_arguments_)

#define bptx_collide_search(_arguments_...)                                   \
  bpt_collide_search(_arguments_)

#define bptx_collide_modify(T, _bpt_, _arguments_...)                         \
  (                                                                           \
    {                                                                         \
      t_bpt_uni(T)	_alloc_ = BPT_MODIFY_ALLOC(_bpt_);                    \
      t_bpt_uni(T)	_size_ = BPT_MODIFY_SIZE(_bpt_);                      \
      t_bpt_unused(T)	_unused_;                                             \
      int		_r_;                                                  \
                                                                              \
      bptx_prolog(T, (_bpt_)->nodesz, (_bpt_)->uaddr, _alloc_,                \
                  _size_, _unused_);                                          \
                                                                              \
      _r_ = bpt_collide_modify(T, _bpt_, _arguments_, &_unused_);             \
                                                                              \
      bptx_epilog(T, _unused_, (_bpt_)->uaddr, _size_);                       \
                                                                              \
      _r_;                                                                    \
    }                                                                         \
  )

#define bptx_collide_remove(T, _bpt_, _arguments_...)                         \
  (                                                                           \
    {                                                                         \
      t_bpt_uni(T)	_alloc_ = BPT_REMOVE_ALLOC(_bpt_);                    \
      t_bpt_uni(T)	_size_ = BPT_REMOVE_SIZE(_bpt_);                      \
      t_bpt_unused(T)	_unused_;                                             \
      int		_r_;                                                  \
                                                                              \
      bptx_prolog(T, (_bpt_)->nodesz, (_bpt_)->uaddr, _alloc_,                \
                  _size_, _unused_);                                          \
                                                                              \
      _r_ = bpt_collide_remove(T, _bpt_, _arguments_, &_unused_);             \
                                                                              \
      bptx_epilog(T, _unused_, (_bpt_)->uaddr, _size_);                       \
                                                                              \
      _r_;                                                                    \
    }                                                                         \
  )

#define bptx_collide_next(_arguments_...)                                     \
  bpt_collide_next(_arguments_)

/*
 * ---------- _unused array_ management ---------------------------------------
 */

#define bptx_prolog(T, _nodesz_, _uaddr_, _alloc_, _size_, _unused_)          \
  t_bpt_addr(T)		_array_[_size_];                                      \
                                                                              \
  _unused_.array = _array_;                                                   \
  _unused_.index = _alloc_ - 1;                                               \
                                                                              \
  {                                                                           \
    t_bpt_uni(T)	_i_;                                                  \
                                                                              \
    for (_i_ = 0; _i_ < _size_; _i_++)                                        \
      _unused_.array[_i_] = (t_bpt_addr(T))_uaddr_;                           \
                                                                              \
    for (_i_ = 0; _i_ < _alloc_; _i_++)                                       \
      _unused_.array[_i_] = (t_bpt_addr(T))bptx_allocate_##T(_nodesz_);       \
  }

#define bptx_epilog(T, _unused_, _uaddr_, _size_)                             \
  {                                                                           \
    t_bpt_uni(T)	_i_;                                                  \
                                                                              \
    for (_i_ = 0; _i_ < _size_; _i_++)                                        \
      if (_unused_.array[_i_] != _uaddr_)                                     \
        bptx_free_##T(_unused_.array[_i_]);                                   \
  }

/*
 * ---------- wrapper ---------------------------------------------------------
 */

#define bptx_wrapper(T, _allocate_, _free_)                                   \
  f_bptx_allocate_##T		bptx_allocate_##T = _allocate_;               \
  f_bptx_free_##T		bptx_free_##T = _free_;

/*
 * ---------- storage ---------------------------------------------------------
 */

#define bptx_storage_RAM(T)                                                   \
                                                                              \
void		bptx_load_##T(t_bpt(T)				*bpt,         \
			      t_bpt_imm(T)			*node,        \
			      t_bpt_node(T)			addr)         \
{                                                                             \
  node->addr = addr;                                                          \
  node->buf = (void *)((unsigned int)addr);                                   \
                                                                              \
  /*                                                                          \
   * do nothing as the tree is stored in RAM main memory.                     \
   */                                                                         \
}                                                                             \
                                                                              \
void		bptx_unload_##T(t_bpt(T)			*bpt,         \
				t_bpt_imm(T)			*node)        \
{                                                                             \
  /*                                                                          \
   * nothing to do, again...                                                  \
   */                                                                         \
}

#define bptx_storage(T, _storage_)                                   	      \
  bptx_storage_##_storage_(T)

/*
 * ---------- compare ---------------------------------------------------------
 */

#define bptx_compare_scalar(T, _function_, _object_)                          \
                                                                              \
int		bptx_##_function_##_##T(t_bpt(T)		*bpt,         \
					t_bpt_##_object_(T)	object1,      \
					t_bpt_##_object_(T)	object2)      \
{                                                                             \
  if (object1 < object2)                                                      \
    return (-1);                                                              \
                                                                              \
  return (object1 > object2);                                                 \
}

#define bptx_compare_string(T, _function_, _object_)                          \
                                                                              \
int		bptx_##_function_##_##T(t_bpt(T)		*bpt,         \
					t_bpt_##_object_(T)	object1,      \
					t_bpt_##_object_(T)	object2)      \
{                                                                             \
  if (object1 == object2)                                                     \
    return (0);                                                               \
                                                                              \
  if ((object1 == bpt->ukey) || (object2 == bpt->ukey))                       \
    return (2);                                                               \
                                                                              \
  return (strcmp(object1, object2));                                          \
}

#define bptx_compare_address(T, _type_)                                       \
  bptx_compare_##_type_(T, addrcmp, addr)

#define bptx_compare_key(T, _type_)                                           \
  bptx_compare_##_type_(T, keycmp, key)

#define bptx_compare_value(T, _type_)                                         \
  bptx_compare_##_type_(T, valcmp, value)

#define bptx_compare(T, _object_, _type_)                                     \
  bptx_compare_##_object_(T, _type_)

/*
 * ---------- traps -----------------------------------------------------------
 */

#define bptx_load(T)                                                          \
  bptx_load_##T

#define bptx_unload(T)                                                        \
  bptx_unload_##T

#define bptx_addrcmp(T)                                                       \
  bptx_addrcmp_##T

#define bptx_keycmp(T)                                                        \
  bptx_keycmp_##T

#define bptx_valcmp(T)                                                        \
  bptx_valcmp_##T

/*
 * ---------- prototypes ------------------------------------------------------
 */

#define bptx_types(T)                                                         \
                                                                              \
void		bptx_load_##T(t_bpt(T)				*bpt,         \
			      t_bpt_imm(T)			*node,        \
			      t_bpt_node(T)			addr);        \
                                                                              \
void		bptx_unload_##T(t_bpt(T)			*bpt,         \
				t_bpt_imm(T)			*node);       \
                                                                              \
int		bptx_addrcmp_##T(t_bpt(T)			*bpt,         \
				 t_bpt_addr(T)			object1,      \
				 t_bpt_addr(T)			object2);     \
                                                                              \
int		bptx_keycmp_##T(t_bpt(T)			*bpt,         \
				t_bpt_key(T)			object1,      \
				t_bpt_key(T)			object2);     \
                                                                              \
int		bptx_valcmp_##T(t_bpt(T)			*bpt,         \
				t_bpt_value(T)			object1,      \
				t_bpt_value(T)			object2);     \
                                                                              \
typedef t_bpt_addr(T)		(*f_bptx_allocate_##T)(unsigned int);         \
typedef void			(*f_bptx_free_##T)(t_bpt_addr(T));            \
                                                                              \
extern f_bptx_allocate_##T	bptx_allocate_##T;                            \
extern f_bptx_free_##T		bptx_free_##T;

#endif
