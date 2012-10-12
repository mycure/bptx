#
# ---------- header -----------------------------------------------------------
#
# project       bpt
#
# license       BSD
#
# file          /home/mycure/bptx/test/Makefile
#
# created       julien quintard   [thu jul 12 17:02:21 2007]
# updated       julien quintard   [sun jul 15 14:16:09 2007]
#

#
# ---------- directives -------------------------------------------------------
#

.PHONY:				main gen sh list tree bench clear clean

#
# ---------- variables --------------------------------------------------------
#

CHECK_INPUT		=			link.in

CHECK_LIST		=			in/add0.in		\
						in/rem0.in		\
						in/rem1.in		\
						in/rem2.in		\
						in/rem3.in		\
						in/balancing0.in	\
						in/balancing1.in	\
						in/balancing2.in	\
						in/balancing3.in	\
						in/balancing4.in	\
						in/balancing5.in	\
						in/balancing6.in	\
						in/balancing7.in	\
						in/balancing8.in	\
						in/balancing9.in	\
						in/real0.in		\
						in/real1.in		\
						in/real2.in		\
						in/real3.in		\
						in/real5.in		\
						in/real6.in		

#
# big tests
#

#CHECK_LIST		+=			in/real4.in		\
#						in/real7.in		\
#						in/real8.in		\
#						in/real9.in		

CHECK_GENERATOR		=			gen

CHECK_SH		=			sh

CHECK_BENCH_LIST	=			list
CHECK_BENCH_BPT		=			tree

CC			=			gcc

CFLAGS			=			-lm			\
						-Wall			\
						-Werror			\
						-Wuninitialized		\
						-Wunused		\
						-O3

RM			=			rm -f
LN			=			ln -s
CAT			=			cat

#
# ---------- rules ------------------------------------------------------------
#

main:				bench

gen:
	@$(RM) $(CHECK_GENERATOR)
	@$(CC) $(CFLAGS) $(CHECK_GENERATOR).c -o $(CHECK_GENERATOR)
	@./$(CHECK_GENERATOR)

sh:
	@$(RM) $(CHECK_SH)
	@$(CC) $(CFLAGS) $(CHECK_SH).c -o $(CHECK_SH)
	@./$(CHECK_SH)

list:
	@for test in $(CHECK_LIST) ; do					\
	  $(RM) $(CHECK_INPUT) ;					\
	  $(LN) $$test $(CHECK_INPUT) ;					\
	  $(CC) $(CFLAGS) $(CHECK_BENCH_LIST).c -o $(CHECK_BENCH_LIST) ;\
	  ./$(CHECK_BENCH_LIST) ;					\
	done

tree:
	@for test in $(CHECK_LIST) ; do					\
	  $(RM) $(CHECK_INPUT) ;					\
	  $(LN) $$test $(CHECK_INPUT) ;					\
	  $(CC) $(CFLAGS) $(CHECK_BENCH_BPT).c -o $(CHECK_BENCH_BPT) ;	\
	  ./$(CHECK_BENCH_BPT) ;					\
	done

bench:		list tree

clear:
	@$(RM) $(CHECK_INPUT) *~

clean:				clear
	@$(RM) $(CHECK_SH) $(CHECK_GENERATOR)
	@$(RM) $(CHECK_BENCH_LIST) $(CHECK_BENCH_BPT)
