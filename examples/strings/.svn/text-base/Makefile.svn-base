#
# ---------- header -----------------------------------------------------------
#
# project       bpt
#
# license       BSD
#
# file          /home/mycure/bpt/examples/strings/Makefile
#
# created       julien quintard   [thu jul 12 16:50:32 2007]
# updated       julien quintard   [thu jul 12 17:05:54 2007]
#

#
# ---------- variables --------------------------------------------------------
#

STRINGS			=			strings

STRINGS_SRCS		=			strings.c

STRINGS_OBJS		=			$(STRINGS_SRCS:.c=.o)

CC			=			gcc
CFLAGS			=			-Wall			\
						-Werror			\
						-Wuninitialized		\
						-Wunused		\
						-O3

RM			=			rm -f

#
# ---------- rules ------------------------------------------------------------
#

main:		$(STRINGS_OBJS)
	$(CC) $(CFLAGS) $(STRINGS_OBJS) -o $(STRINGS)

clear:
	@$(RM) $(STRINGS_OBJS) *~

clean:			clear
	@$(RM) $(STRINGS)
