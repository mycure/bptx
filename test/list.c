/*
 * ---------- header ----------------------------------------------------------
 *
 * project       bpt
 *
 * license       BSD
 *
 * file          /home/mycure/bpt/test/list.c
 *
 * created       julien quintard   [thu jul 12 17:27:56 2007]
 * updated       julien quintard   [thu jul 12 17:27:59 2007]
 */

/*
 * debug
 */

#undef LIST_DEBUG

/*
 * includes
 */

#include <sys/types.h>
#include "link.in"

/*
 * structures
 */

typedef struct		s_entry
{
  IN_KEY_T		key;
  IN_ADDR_T		value;

  struct s_entry	*prev;
  struct s_entry	*next;
}			t_entry;

/*
 * global variable
 */

t_entry			*list = NULL;

/*
 * prototypes
 */

void			list_dump(void);

void			list_add(t_in_input		input);

void			list_mod(t_in_input		input);

void			list_rem(t_in_input		input);

void			list_exit(int			code,
				  char			*msg);

void			list_main(void);

/*
 * functions
 */

void			list_add(t_in_input		input)
{
  t_entry		*entry;
  t_entry		*prev;
  t_entry		*new;

  new = malloc(sizeof(t_entry));

#ifdef LIST_DEBUG
  printf("[add] %u %u\n", input.key, input.value);
#endif

  new->key = input.key;
  new->value = input.value;
  new->prev = NULL;
  new->next = NULL;

  if (list == NULL)
    {
      list = new;
      return ;
    }

  for (entry = list, prev = NULL; entry != NULL;
       prev = entry, entry = entry->next)
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

void			list_mod(t_in_input		input)
{
  t_entry		*entry;
  t_entry		*new;

  new = malloc(sizeof(t_entry));

#ifdef LIST_DEBUG
  printf("[mod] %u | %u %u\n", input.id, input.key, input.value);
#endif

  for (entry = list; entry != NULL; entry = entry->next)
    if (input.id == entry->key)
      {
	t_entry		*prev = entry->prev;
	t_entry		*next = entry->next;
	t_in_input	in;

	if (input.key == entry->key)
	  {
	    entry->value = input.value;
	    return ;
	  }

	if ((prev == NULL) && (next == NULL))
	  {
	    entry->key = input.key;
	    entry->value = input.value;
	    return ;
	  }

	if (prev != NULL)
	  prev->next = next;

	if (next != NULL)
	  next->prev = prev;

	if (list == entry)
	  list = next;

	in.no = 0;
	in.op = IN_ADD;
	in.id = 0;
	in.key = input.key;
	in.value = input.value;

	list_add(in);

	free(entry);

	return ;
      }
}

void			list_rem(t_in_input		input)
{
  t_entry		*entry;

#ifdef LIST_DEBUG
  printf("[rem] %u\n", input.id);
#endif

  for (entry = list; entry != NULL; entry = entry->next)
    if (entry->key == input.id)
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

void			list_exit(int			code,
				  char			*msg)
{
  printf("%s\n", msg);

  exit(code);
}

void			list_main(void)
{
  t_entry		*entry;
  unsigned int		i;

  for (i = 0; i < IN_INPUT_NOPS; i++)
    {
      if (input[i].op == IN_ADD)
	list_add(input[i]);
      else if (input[i].op == IN_MOD)
	list_mod(input[i]);
      else if (input[i].op == IN_REM)
	list_rem(input[i]);
    }

  for (entry = list, i = 0; i < IN_OUTPUT_NOPS; entry = entry->next, i++)
    {
      if (entry == NULL)
	list_exit(EXIT_FAILURE, "[KO]");

      if ((entry->key != output[i].key) ||
	  (entry->value != output[i].value))
	list_exit(EXIT_FAILURE, "[KO]");
    }

  while (list != NULL)
    {
      t_in_input	in;

      in.no = 0;
      in.op = IN_REM;
      in.id = list->key;
      in.key = 0;
      in.value = 0;

      list_rem(in);
    }
}

int			main(int			argc,
			     char			**argv)
{
  struct timeval	reftime;
  struct timeval	curtime;
  struct timeval	diff;
  struct timezone	tzp;

  printf("[%-5s] running %-15s		", "list", IN_NAME);
  fflush(stdout);

  gettimeofday(&reftime, &tzp);
  list_main();
  gettimeofday(&curtime, &tzp);

  timersub(&curtime, &reftime, &diff);

  printf("%u.%u ", (unsigned int)diff.tv_sec,
	 (unsigned int)diff.tv_usec);

  list_exit(EXIT_SUCCESS, "[OK]");

  return (0);
}
