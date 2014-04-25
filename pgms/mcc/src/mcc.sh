#!/bin/sh
#
#  @(#) mcc -  Merges syntax error messages from C compiler into
#	 source and brings up vi with cursor at first error.
#	 Re-compiles automatically when editor exits.
#  Author: Brent Callaghan

trap "rm -f /tmp/$$.* ; exit \$RSLT" 0 1 2 3 15	# clean up
quit() { cat /tmp/$$.err1 ; exit ; }		# give up gracefully

until ${COMPILER:=vcc} "$@" >/tmp/$$.err1 2>&1 
do
	RSLT=$?
	sed -e 's/^"\(.*\)", line \([0-9][0-9]*\): /\1	\2	/' \
	    -e 's/^\(.*\): \([0-9][0-9]*\): /\1	\2	/' \
	    < /tmp/$$.err1 > /tmp/$$.err2
	read SRC LINE null < /tmp/$$.err2
	case "$LINE" in [0-9]*) ;; *) quit ;; esac	# valid line # ?
	if [ ! -w "$SRC" ] ; then quit ; fi		# source writeable ?
	awk -F"	" '/^'$SRC'/{printf "%s5\t>>>>  %s  <<<<\n", $2, $3}' \
	    < /tmp/$$.err2 > /tmp/$$.mrg1
	awk '{printf "%d0\t%s\n", NR, $0}' < $SRC |
	sort -m -n /tmp/$$.mrg1 - |			# merge err msgs
	sed -e 's/^[0-9][0-9]*	//' > /tmp/$$.$SRC
	CHKSUM=`sum /tmp/$$.$SRC`
	vi +$LINE /tmp/$$.$SRC				# fix errors
	if [ "$CHKSUM" = "`sum /tmp/$$.$SRC`" ] ; then exit ; fi
	echo "  $COMPILER $*"
	grep -v "^>>>> " /tmp/$$.$SRC > /tmp/$$.mrg2	# strip err msgs
	mv /tmp/$$.mrg2 $SRC
done
cat /tmp/$$.err1					# list warnings
RSLT=0							# compiled OK
