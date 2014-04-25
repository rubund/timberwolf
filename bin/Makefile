# Makefile for the bin cshells and awk scripts.
# "@(#) Makefile version 1.1 4/27/91"

AWK =  \
	reverse_corners.awk \
	splt_file.a

CSHELLS= \
	change_flow \
	cleandata \
	cleanfiles \
	edit_mcfiles \
	edit_twfiles \
	reverse_corners \
	show_flows



# *************************** SCCS *******************************
SCCS=sccs
SCCS_OP=get
sources: ${CSHELLS} ${AWK} Makefile
	
${CSHELLS}:
	${SCCS} ${SCCS_OP} ${REL} $@
	chmod 777 $@

${AWK} Makefile :
	${SCCS} ${SCCS_OP} ${REL} $@

# ************************ END SCCS *****************************
# end makefile
