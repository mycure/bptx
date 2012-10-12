#
# ---------- header -----------------------------------------------------------
#
# project       bpt
#
# license       BSD
#
# file          /home/mycure/bpt/examples/multi-files/Makefile
#
# created       julien quintard   [thu jul 12 16:57:32 2007]
# updated       julien quintard   [thu jul 12 17:05:46 2007]
#

#
# ---------- variables --------------------------------------------------------
#

MULTI			=			multi

MULTI_SRCS		=			multi.c		\
						multi-klc.c		\
						multi-lse.c
MULTI_OBJS		=			$(MULTI_SRCS:.c=.o)

CFLAGS			=			-Wall			\
						-Werror			\
						-Wuninitialized		\
						-Wunused		\
						-O3

RM			=			rm -f

#
# ---------- rules ------------------------------------------------------------
#

main:		$(MULTI_OBJS)
	$(CC) $(CFLAGS) $(MULTI_OBJS) -o $(MULTI)

clear:
	@$(RM) $(MULTI_OBJS) *~

clean:			clear
	@$(RM) $(MULTI)
