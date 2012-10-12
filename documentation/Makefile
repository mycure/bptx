#
# ---------- header -----------------------------------------------------------
#
# project       bpt
#
# license       BSD
#
# file          /home/mycure/bptx/documentation/Makefile
#
# created       julien quintard   [thu jul 12 17:30:49 2007]
# updated       julien quintard   [sun jul 15 14:34:35 2007]
#

#
# ---------- variables --------------------------------------------------------
#

PAPER		=		bptx

GARBAGE		=		$(PAPER).aux				\
				$(PAPER).log				\
				$(PAPER).nav				\
				$(PAPER).out				\
				$(PAPER).srm				\
				$(PAPER).toc				\
				$(PAPER).dvi				\
				$(PAPER).ps				\
				$(PAPER).pdf				\
				$(PAPER).bbl				\
				$(PAPER).blg				

LATEX		=		pdflatex
RM		=		rm -f

#
# ---------- rules ------------------------------------------------------------
#

main:			$(PAPER)

$(PAPER):
	@$(LATEX) $(PAPER)
	@$(LATEX) $(PAPER)

clear:
	@$(RM) $(GARBAGE) *~

clean:			clear
	@$(RM) $(PAPER).pdf
