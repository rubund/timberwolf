#  Makefile for TimberWolfSC.
#  "@(#) Ymakefile (Yale) version 4.21 9/19/91"
#
# ******************************************************************
# YMAKE MACRO SUBSTITUTION FILE.
# ****************** switches for compilation *******************
CFLAGS=-g
#
# The target foreign machine is assumed to be running UNIX, if not
# comment out following line.
UNIX=-DUNIX
#
# If users system does not support UNIX signals, comment out the
# signal handler defined on the next line.
CLEANUP=-DCLEANUP_C 
#
# The makefile should automatically define this variable if an X11
# server is not present, that is, /usr/include/X11 is not present.
# uncomment line if you which to override.
#NOGRAPHICS=-DNOGRAPHICS
#
# Normally the program is compiled with assertion checking.  If a 
# on a sys5 machine uncomment out next line systype
# use this only if problems arise with include files.
# also check below for problems with ranlib.
#SYS5=-DSYS5

# smaller faster version is desired comment out next line.
DEBUG=-DDEBUG
#
# if all feedthrus should have the same name uncomment the next line.
# DFEED=-DNO_FEED_INSTANCES 

# available for adding future options.
OPTIONS=${UNIX} ${DEBUG} ${NOGRAPHICS} ${SYS5} ${DFEED} -Dlinux -Wall
#
# place where Xwindow include files reside
XLIB=/usr/include/X11
#
# where the libraries are
# where the <yalecad/base.h> etc. are located.
# how set set the search directories for compilation
INCLUDE=../../../include/ -I/usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/
YALELIB=${INCLUDE}yalecad/
# ****************** switches for linking *******************
# Yale library - the first library uses the Yale memory manager
# the second library uses the system's memory manager.
NYCADSYS=libycad.sys.a
NYCADMEM=libycad.mem.a
YCADMEM=../../Ylib/lib/${NYCADMEM}
YCADSYS=../../Ylib/lib/${NYCADSYS}
# on this line pick which library you want
# YALECAD=${YCADMEM}
YALECAD=${YCADSYS}


IDIR=-I. -I${INCLUDE} -I${XLIB}
# ****************** switches for linking *******************

#
# place where link libraries exist
# user must supply math library and X11 library.
# use -L option if libraries exist elsewhere ie. -L/usr/bills/X -lX11
#
# for decStation need -lc first because of lame libraries
# (Note:  Use the line with /usr/X11R6/lib64 for 64-bit Linux systems)
# LINKLIB=-L/usr/X11R6/lib -lc -lX11 -lm
LINKLIB=-L/usr/X11R6/lib64 -lc -lX11 -lm
#
# need these lines for yale installation. Null otherwise.
GETDATE=
DATE_C=../../date/src/date.c
#
# ******************* RENAME PROGRAMS *************************
#
AR=ar # archiving program.
AWK=awk # awk language interpreter.
CAT=cat # concatenate program.
CC=cc # C compiler switch
CHMOD=chmod # C compiler switch
ECHO=echo # echo to the screen
GREP=grep
YMAKE=../../ymake/ymake # path of ymake program
# if problems arise with makedepend uncomment out following line
#YMAKEARGS=nodepend  # path of ymake program
YMAKEFILE=Ymakefile # name of ymakefile.
LEX=${ECHO}
LD=ld # linker
MAKE=/usr/bin/make
MAKEDEPEND=makedepend
MV=mv # move program name
# PAS=/com/pas
PAS=${ECHO}
# on sys5 machines ranlib not supported uncomment second line
RANLIB=ranlib
#RANLIB=${ECHO}
RM=/bin/rm -f
STRIP=strip # strip symbol table from code.
SCCS=sccs # software control program
SCCS_OP=get #normal sccs operation
# always use Bourne shell in makefile.
SHELL=/bin/sh
YACC=${ECHO}
# if you dont have yacc and lex set to nop operation like echo
LEXMV=${ECHO}
YACCMV=${ECHO}
# ******************************************************************

#destination of output executable
DEST=../
PNAME=TimberWolfSC

IDIR=-I${INCLUDE} -I. -I${XLIB} 

ONAME=obj

O=../${ONAME}/

INC=standard.h

REL=

SRC=	acceptt.c\
 	buildimp.c\
	cell_width.c\
	cglbroute.c\
 	changrid.c\
	coarseglb.c\
 	configpads.c\
 	configure.c\
 	countf.c\
 	crossbus.c\
 	debug.c\
 	debug2.c\
 	dimbox.c\
	feedest.c\
 	findcost.c\
 	findcostf.c\
 	findrcost.c\
 	findunlap.c\
 	gateswap.c\
 	globe.c\
 	globroute.c\
 	graphics.c\
 	main.c\
	mergeseg.c\
	netgraph.c\
	newtemp.c\
 	outpins.c\
 	outpins1.c\
 	output.c\
 	overlap.c\
 	parser.c\
	paths.c\
	placepads.c\
 	readblck.c\
 	readcell.c\
	readnets.c\
 	readpar.c\
 	reconfig.c\
	rmoverlap.c\
	rowevener.c\
 	savewolf.c\
 	seagate.c\
 	sortpin.c\
 	sortpad.c\
 	sort.c\
	steiner.c\
 	uc0.c\
 	ucxx1.c\
 	ucxx2.c\
 	ucxxo1.c\
 	ucxxo2.c\
 	ucxxp.c\
 	uloop.c\
 	unlap.c\
 	upair.c\
 	urcost.c\
 	utemp.c\
 	xpickint.c\
	outcm.c

LIBSRC= assign.c \
	cleanup.c \
	deck.c \
	file.c \
	hash.c\
	message.c \
	mytime.c \
	okmalloc.c \
	quicksort.c \
	rand.c \
	rbtree.c \
	stat.c \
	stats.c \
	string.c \
	system.c \
	time.c \
	timer.c \
	trans.c \
	program.c \
	ydebug.c \
	yreadpar.c

OBJ=	${O}acceptt.o\
	${O}buildimp.o\
	${O}cell_width.o\
	${O}cglbroute.o\
	${O}changrid.o\
	${O}coarseglb.o\
	${O}configpads.o\
	${O}configure.o\
	${O}countf.o\
	${O}crossbus.o\
	${O}dimbox.o\
	${O}feedest.o\
	${O}findcost.o\
	${O}findcostf.o\
	${O}findrcost.o\
	${O}findunlap.o\
	${O}gateswap.o\
	${O}globe.o\
	${O}globroute.o\
	${O}graphics.o\
	${O}main.o\
	${O}mergeseg.o\
	${O}netgraph.o\
	${O}newtemp.o\
	${O}outpins.o\
	${O}outpins1.o\
	${O}output.o\
	${O}overlap.o\
	${O}parser.o\
	${O}paths.o\
	${O}placepads.o\
	${O}readblck.o\
	${O}readcell.o\
	${O}readnets.o\
	${O}readpar.o\
	${O}reconfig.o\
	${O}rmoverlap.o\
	${O}rowevener.o\
	${O}savewolf.o\
	${O}seagate.o\
	${O}sort.o\
	${O}sortpin.o\
	${O}sortpad.o\
	${O}steiner.o\
	${O}uc0.o\
	${O}ucxx1.o\
	${O}ucxx2.o\
	${O}ucxxo1.o\
	${O}ucxxo2.o\
	${O}ucxxp.o\
	${O}uloop.o\
	${O}unlap.o\
	${O}upair.o\
	${O}urcost.o\
	${O}utemp.o\
	${O}xpickint.o\
	${O}outcm.o

LIBOBJ= \
	${O}assign.o \
	${O}cleanup.o \
	${O}deck.o \
	${O}file.o \
	${O}hash.o \
	${O}message.o \
	${O}mytime.o \
	${O}okmalloc.o \
	${O}program.o \
	${O}quicksort.o \
	${O}rand.o \
	${O}rbtree.o \
	${O}stat.o \
	${O}stats.o \
	${O}system.o \
	${O}time.o \
	${O}timer.o \
	${O}trans.o \
	${O}string.o \
	${O}ydebug.o \
	${O}yreadpar.o 

HEADER= standard.h groute.h main.h ucxxglb.h readnets.h parser.h \
config.h feeds.h readpar.h readblck.h readcell.h pads.h

MENU=sc_menu menus.h

#debug object code
DOBJ=${O}debug.o ${O}debug2.o

info:   ;
	-@echo "make ${PNAME} - usage:"
	-@echo "Non-Yale users should type 'make install_non_yale'"
	-@echo "Yale users should type 'make install'"
	-@echo "Non-Yale without the Yalecad library should type 'make nolib'"
	-@echo " "

${DEST}${PNAME}:    ${OBJ} ${USEROBJ} ${YALECAD} ${DOBJ}
	${GETDATE}
	${CC} -c -I. ${CFLAGS} ${DATE_C}
	${MV} date.o ${O}date.o 
	${CC} ${CFLAGS} ${OPTIONS} -o ${DEST}${PNAME} ${O}date.o \
	${DOBJ} ${OBJ} ${USEROBJ} ${YALECAD} ${LINKLIB}

nolib :;
	make nolibm GETDATE= UNIX=${UNIX} NOGRAPHICS=-DNOGRAPHICS \
	CLEANUP=${CLEANUP} DEBUG=${DEBUG} INCLUDE=lib \
	CFLAGS="-O -DSIZEOF_VOID_P=`getconf LONG_BIT`" CC=cc \
	LINKLIB="${LINKLIB}"

nolibm :${OBJ} ${LIBOBJ} ${DOBJ}
	${GETDATE}
	${CC} -c -I. ${CFLAGS} date.c
	${MV} date.o ${O}date.o 
	${CC} ${CFLAGS} -o ${DEST}${PNAME} ${O}date.o \
	${DOBJ} ${OBJ} \
	${LIBOBJ} \
	${LINKLIB}

install:${DEST}${PNAME}

install_non_yale:
	make ${DEST}${PNAME} GETDATE= UNIX=${UNIX} YALECAD=${YALECAD} \
	CLEANUP=${CLEANUP} DEBUG=${DEBUG} \
	CFLAGS="-g -DSIZEOF_VOID_P=`getconf LONG_BIT`" CC=${CC}

clean:
	${RM} ${O}* *~ core *.bak foo y.output

cleanall:
	make clean
	${RM} readcell.c readnets.c readcell_l.h readnets_l.h
    

# how to build makefile dependencies
depend :
	${MAKEDEPEND} ${CFLAGS} ${OPTIONS} ${IDIR} ${SRC}

#BEGIN DEPENDENCIES -- DO NOT DELETE THIS LINE

#END DEPENDENCIES -- DO NOT DELETE THIS LINE

#default sccs operation is get
SCCS_OP=get
#current release
REL=

# how to get sources from sccs
sources : ${SRC} ${HEADER} ${YMAKEFILE} ${MENU}
${SRC} ${HEADER} ${YMAKEFILE} ${MENU}: 
	${SCCS} ${SCCS_OP} ${REL} $@

library: ;
	(cd ${TWDIR}/pgms/Ylib/lib;\
	tar cvf ${HOME}/tar.ylib ${LIBSRC} ) ; 
	(tar xvf ${HOME}/tar.ylib ) ; 
	${RM} ${HOME}/tar.ylib
	(cd ${TWDIR}/pgms/date/src;\
	tar cvf ${HOME}/tar.ylib date.c ) ; 
	(tar xvf ${HOME}/tar.ylib ) ; 
	${RM} ${HOME}/tar.ylib
	(cd ${TWDIR}/pgms/Ylib/include;\
	tar cvfFF ${HOME}/tar.ylib . ) ; 
	mkdir lib ; cd lib; mkdir yalecad ;
	(cd lib/yalecad;\
	tar xvf ${HOME}/tar.ylib ) ; 
	${RM} ${HOME}/tar.ylib

del_lib: ;
	${RM} ${LIBSRC} date.c
	${RM} -rf lib

lint:
	${LINT} ${LINT_OPT} -DNOGRAPHICS ${IDIR} ${OPTIONS} \
	${SRC} ${LIBSRC} >lint.out

#used to make documentation
bnf :  ys.awk 
	${AWK} -f ys.awk readcell.y > foo
	sed -e 's/;//' foo > cells_bnf
	${AWK} -f ys.awk readnets.y > foo
	sed -e 's/;//' foo > nets_bnf
	${RM} foo

# we can't do anything about yalecad but want to update if it has changed
${YALECAD}: ;

# How to compile the user file
user.o:user.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  user.c
	
# how to compile the individual src files
${O}acceptt.o:	acceptt.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} acceptt.c
	mv acceptt.o ${O}acceptt.o 

${O}buildimp.o:	buildimp.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} buildimp.c
	mv buildimp.o ${O}buildimp.o 

${O}cell_width.o:	cell_width.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} cell_width.c
	mv cell_width.o ${O}cell_width.o 

${O}cglbroute.o:	cglbroute.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} cglbroute.c
	mv cglbroute.o ${O}cglbroute.o 

${O}changrid.o:	changrid.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} changrid.c
	mv changrid.o ${O}changrid.o 

${O}overlap.o:	overlap.c
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} overlap.c
	mv overlap.o ${O}overlap.o 

${O}coarseglb.o:	coarseglb.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} coarseglb.c
	mv coarseglb.o ${O}coarseglb.o 

${O}configpads.o:	configpads.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} configpads.c
	mv configpads.o ${O}configpads.o 

${O}configure.o:	configure.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} configure.c
	mv configure.o ${O}configure.o 

${O}countf.o:	countf.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} countf.c
	mv countf.o ${O}countf.o 

${O}crossbus.o:	crossbus.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} crossbus.c
	mv crossbus.o ${O}crossbus.o 

${O}debug.o:	debug.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} debug.c
	mv debug.o ${O}debug.o 

${O}debug2.o:	debug2.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} debug2.c
	mv debug2.o ${O}debug2.o 

${O}dimbox.o:	dimbox.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} dimbox.c
	mv dimbox.o ${O}dimbox.o 

${O}feedest.o:	feedest.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} feedest.c
	mv feedest.o ${O}feedest.o 

${O}findcost.o:	findcost.c
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} findcost.c
	mv findcost.o ${O}findcost.o 

${O}findcostf.o:	findcostf.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} findcostf.c
	mv findcostf.o ${O}findcostf.o 

${O}findrcost.o:	findrcost.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} findrcost.c
	mv findrcost.o ${O}findrcost.o 

${O}findunlap.o:	findunlap.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} findunlap.c
	mv findunlap.o ${O}findunlap.o 

${O}gateswap.o:	gateswap.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} gateswap.c
	mv gateswap.o ${O}gateswap.o 

${O}globe.o:	globe.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} globe.c
	mv globe.o ${O}globe.o 

${O}globroute.o:	globroute.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} globroute.c
	mv globroute.o ${O}globroute.o 

${O}graphics.o:	graphics.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} graphics.c
	mv graphics.o ${O}graphics.o 

${O}main.o:	main.c 
	${CC} -c ${CFLAGS} ${IDIR} ${CLEANUP} ${OPTIONS} main.c
	mv main.o ${O}main.o 

${O}mergeseg.o:	mergeseg.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} mergeseg.c
	mv mergeseg.o ${O}mergeseg.o 

${O}netgraph.o:	netgraph.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} netgraph.c
	mv netgraph.o ${O}netgraph.o 

${O}newtemp.o:	newtemp.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} newtemp.c
	mv newtemp.o ${O}newtemp.o 

${O}outpins.o:	outpins.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} outpins.c
	mv outpins.o ${O}outpins.o 

${O}outpins1.o:	outpins1.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} outpins1.c
	mv outpins1.o ${O}outpins1.o 

${O}output.o:	output.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} output.c
	mv output.o ${O}output.o 

${O}parser.o:	parser.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} parser.c
	mv parser.o ${O}parser.o 

${O}paths.o:	paths.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} paths.c
	mv paths.o ${O}paths.o 

${O}placepads.o:	placepads.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} placepads.c
	mv placepads.o ${O}placepads.o 

${O}readblck.o:	readblck.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} readblck.c
	mv readblck.o ${O}readblck.o 

${O}readcell.o: readcell.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -w -c readcell.c
	${MV} readcell.o ${O}readcell.o

${O}readnets.o: readnets.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -w -c readnets.c
	${MV} readnets.o ${O}readnets.o

${O}readpar.o:	readpar.c
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} readpar.c
	mv readpar.o ${O}readpar.o 

${O}reconfig.o:	reconfig.c
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} reconfig.c
	mv reconfig.o ${O}reconfig.o 

${O}rmoverlap.o:	rmoverlap.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} rmoverlap.c
	mv rmoverlap.o ${O}rmoverlap.o 

${O}rowevener.o:	rowevener.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} rowevener.c
	mv rowevener.o ${O}rowevener.o 

${O}savewolf.o:	savewolf.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} savewolf.c
	mv savewolf.o ${O}savewolf.o 

${O}seagate.o:	seagate.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} seagate.c
	mv seagate.o ${O}seagate.o 

${O}sort.o:	sort.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} sort.c
	mv sort.o ${O}sort.o 

${O}sortpin.o:	sortpin.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} sortpin.c
	mv sortpin.o ${O}sortpin.o 

${O}sortpad.o:	sortpad.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} sortpad.c
	mv sortpad.o ${O}sortpad.o 

${O}steiner.o:	steiner.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} steiner.c
	mv steiner.o ${O}steiner.o 

${O}uc0.o:	uc0.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} uc0.c
	mv uc0.o ${O}uc0.o 

${O}ucxx1.o:	ucxx1.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} ucxx1.c
	mv ucxx1.o ${O}ucxx1.o 

${O}ucxx2.o:	ucxx2.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} ucxx2.c
	mv ucxx2.o ${O}ucxx2.o 

${O}ucxxo1.o:	ucxxo1.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} ucxxo1.c
	mv ucxxo1.o ${O}ucxxo1.o 

${O}ucxxo2.o:	ucxxo2.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} ucxxo2.c
	mv ucxxo2.o ${O}ucxxo2.o 

${O}ucxxp.o:	ucxxp.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} ucxxp.c
	mv ucxxp.o ${O}ucxxp.o 

${O}uloop.o:	uloop.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} uloop.c
	mv uloop.o ${O}uloop.o 

${O}unlap.o:	unlap.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} unlap.c
	mv unlap.o ${O}unlap.o 

${O}upair.o:	upair.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} upair.c
	mv upair.o ${O}upair.o 

${O}urcost.o:	urcost.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} urcost.c
	mv urcost.o ${O}urcost.o 

${O}utemp.o:	utemp.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} utemp.c
	mv utemp.o ${O}utemp.o 

${O}xpickint.o:	xpickint.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} xpickint.c
	mv xpickint.o ${O}xpickint.o 

${O}outcm.o:	outcm.c 
	${CC} -c ${CFLAGS} ${IDIR} ${OPTIONS} outcm.c
	mv outcm.o ${O}outcm.o 

# ############## how to build the library #################
# this is only used if the yalecad library is not used 
${O}assign.o:assign.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  assign.c
	${MV} assign.o ${O}assign.o
${O}cleanup.o:cleanup.c
	${CC} ${CLEANUP} ${CFLAGS} ${IDIR} ${OPTIONS} -c  cleanup.c
	${MV} cleanup.o ${O}cleanup.o
${O}deck.o:deck.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  deck.c
	${MV} deck.o ${O}deck.o
${O}file.o:file.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  file.c
	${MV} file.o ${O}file.o
${O}hash.o:hash.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  hash.c
	${MV} hash.o ${O}hash.o
${O}message.o:message.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  message.c
	${MV} message.o ${O}message.o
${O}mytime.o:mytime.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  mytime.c
	${MV} mytime.o ${O}mytime.o
${O}okmalloc.o:okmalloc.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  okmalloc.c
	${MV} okmalloc.o ${O}okmalloc.o
${O}program.o:program.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  program.c
	${MV} program.o ${O}program.o
${O}quicksort.o:quicksort.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  quicksort.c
	${MV} quicksort.o ${O}quicksort.o
${O}rand.o:rand.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  rand.c
	${MV} rand.o ${O}rand.o
${O}rbtree.o:rbtree.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  rbtree.c
	${MV} rbtree.o ${O}rbtree.o
${O}stat.o:stat.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  stat.c
	${MV} stat.o ${O}stat.o
${O}stats.o:stats.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  stats.c
	${MV} stats.o ${O}stats.o
${O}string.o:string.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  string.c
	${MV} string.o ${O}string.o
${O}system.o:system.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  system.c
	${MV} system.o ${O}system.o
${O}time.o:time.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  time.c
	${MV} time.o ${O}time.o
${O}timer.o:timer.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  timer.c
	${MV} timer.o ${O}timer.o
${O}trans.o:trans.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  trans.c
	${MV} trans.o ${O}trans.o
${O}ydebug.o:ydebug.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  ydebug.c
	${MV} ydebug.o ${O}ydebug.o
${O}yreadpar.o:yreadpar.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  yreadpar.c
	${MV} yreadpar.o ${O}yreadpar.o
# end makefile
# DO NOT DELETE

acceptt.o: ../../../include/yalecad/base.h /usr/include/stdio.h
acceptt.o: /usr/include/features.h /usr/include/sys/cdefs.h
acceptt.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
acceptt.o: /usr/include/gnu/stubs-64.h
acceptt.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
acceptt.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
acceptt.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
acceptt.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
acceptt.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
acceptt.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
acceptt.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
acceptt.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
acceptt.o: /usr/include/sys/types.h /usr/include/time.h
acceptt.o: /usr/include/sys/select.h /usr/include/bits/select.h
acceptt.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
acceptt.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
acceptt.o: /usr/include/alloca.h /usr/include/math.h
acceptt.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
acceptt.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
acceptt.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
acceptt.o: /usr/include/bits/mathcalls.h
acceptt.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
acceptt.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
acceptt.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
acceptt.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
acceptt.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
acceptt.o: ../../../include/yalecad/debug.h
acceptt.o: ../../../include/yalecad/message.h main.h standard.h
acceptt.o: ../../../include/yalecad/file.h
buildimp.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
buildimp.o: /usr/include/features.h /usr/include/sys/cdefs.h
buildimp.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
buildimp.o: /usr/include/gnu/stubs-64.h
buildimp.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
buildimp.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
buildimp.o: /usr/include/libio.h /usr/include/_G_config.h
buildimp.o: /usr/include/wchar.h
buildimp.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
buildimp.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
buildimp.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
buildimp.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
buildimp.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
buildimp.o: /usr/include/sys/types.h /usr/include/time.h
buildimp.o: /usr/include/sys/select.h /usr/include/bits/select.h
buildimp.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
buildimp.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
buildimp.o: /usr/include/alloca.h /usr/include/math.h
buildimp.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
buildimp.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
buildimp.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
buildimp.o: /usr/include/bits/mathcalls.h
buildimp.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
buildimp.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
buildimp.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
buildimp.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
buildimp.o: /usr/include/bits/posix2_lim.h
buildimp.o: ../../../include/yalecad/okmalloc.h
buildimp.o: ../../../include/yalecad/file.h groute.h feeds.h
cell_width.o: /usr/include/string.h /usr/include/features.h
cell_width.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
cell_width.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
cell_width.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
cell_width.o: /usr/include/xlocale.h standard.h
cell_width.o: ../../../include/yalecad/base.h /usr/include/stdio.h
cell_width.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
cell_width.o: /usr/include/libio.h /usr/include/_G_config.h
cell_width.o: /usr/include/wchar.h
cell_width.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
cell_width.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
cell_width.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
cell_width.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
cell_width.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
cell_width.o: /usr/include/sys/types.h /usr/include/time.h
cell_width.o: /usr/include/sys/select.h /usr/include/bits/select.h
cell_width.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
cell_width.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
cell_width.o: /usr/include/alloca.h /usr/include/math.h
cell_width.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
cell_width.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
cell_width.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
cell_width.o: /usr/include/bits/mathcalls.h
cell_width.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
cell_width.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
cell_width.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
cell_width.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
cell_width.o: /usr/include/bits/posix2_lim.h
cell_width.o: ../../../include/yalecad/okmalloc.h
cell_width.o: ../../../include/yalecad/file.h main.h config.h readpar.h
cell_width.o: parser.h ../../../include/yalecad/debug.h
cell_width.o: ../../../include/yalecad/message.h
cell_width.o: ../../../include/yalecad/rbtree.h
cell_width.o: ../../../include/yalecad/string.h
cglbroute.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
cglbroute.o: /usr/include/features.h /usr/include/sys/cdefs.h
cglbroute.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
cglbroute.o: /usr/include/gnu/stubs-64.h
cglbroute.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
cglbroute.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
cglbroute.o: /usr/include/libio.h /usr/include/_G_config.h
cglbroute.o: /usr/include/wchar.h
cglbroute.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
cglbroute.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
cglbroute.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
cglbroute.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
cglbroute.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
cglbroute.o: /usr/include/sys/types.h /usr/include/time.h
cglbroute.o: /usr/include/sys/select.h /usr/include/bits/select.h
cglbroute.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
cglbroute.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
cglbroute.o: /usr/include/alloca.h /usr/include/math.h
cglbroute.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
cglbroute.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
cglbroute.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
cglbroute.o: /usr/include/bits/mathcalls.h
cglbroute.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
cglbroute.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
cglbroute.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
cglbroute.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
cglbroute.o: /usr/include/bits/posix2_lim.h
cglbroute.o: ../../../include/yalecad/okmalloc.h
cglbroute.o: ../../../include/yalecad/file.h main.h groute.h
changrid.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
changrid.o: /usr/include/features.h /usr/include/sys/cdefs.h
changrid.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
changrid.o: /usr/include/gnu/stubs-64.h
changrid.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
changrid.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
changrid.o: /usr/include/libio.h /usr/include/_G_config.h
changrid.o: /usr/include/wchar.h
changrid.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
changrid.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
changrid.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
changrid.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
changrid.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
changrid.o: /usr/include/sys/types.h /usr/include/time.h
changrid.o: /usr/include/sys/select.h /usr/include/bits/select.h
changrid.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
changrid.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
changrid.o: /usr/include/alloca.h /usr/include/math.h
changrid.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
changrid.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
changrid.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
changrid.o: /usr/include/bits/mathcalls.h
changrid.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
changrid.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
changrid.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
changrid.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
changrid.o: /usr/include/bits/posix2_lim.h
changrid.o: ../../../include/yalecad/okmalloc.h
changrid.o: ../../../include/yalecad/file.h groute.h
coarseglb.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
coarseglb.o: /usr/include/features.h /usr/include/sys/cdefs.h
coarseglb.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
coarseglb.o: /usr/include/gnu/stubs-64.h
coarseglb.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
coarseglb.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
coarseglb.o: /usr/include/libio.h /usr/include/_G_config.h
coarseglb.o: /usr/include/wchar.h
coarseglb.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
coarseglb.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
coarseglb.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
coarseglb.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
coarseglb.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
coarseglb.o: /usr/include/sys/types.h /usr/include/time.h
coarseglb.o: /usr/include/sys/select.h /usr/include/bits/select.h
coarseglb.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
coarseglb.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
coarseglb.o: /usr/include/alloca.h /usr/include/math.h
coarseglb.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
coarseglb.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
coarseglb.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
coarseglb.o: /usr/include/bits/mathcalls.h
coarseglb.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
coarseglb.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
coarseglb.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
coarseglb.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
coarseglb.o: /usr/include/bits/posix2_lim.h
coarseglb.o: ../../../include/yalecad/okmalloc.h
coarseglb.o: ../../../include/yalecad/file.h groute.h main.h feeds.h parser.h
coarseglb.o: pads.h readpar.h
configpads.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
configpads.o: /usr/include/features.h /usr/include/sys/cdefs.h
configpads.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
configpads.o: /usr/include/gnu/stubs-64.h
configpads.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
configpads.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
configpads.o: /usr/include/libio.h /usr/include/_G_config.h
configpads.o: /usr/include/wchar.h
configpads.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
configpads.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
configpads.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
configpads.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
configpads.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
configpads.o: /usr/include/sys/types.h /usr/include/time.h
configpads.o: /usr/include/sys/select.h /usr/include/bits/select.h
configpads.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
configpads.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
configpads.o: /usr/include/alloca.h /usr/include/math.h
configpads.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
configpads.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
configpads.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
configpads.o: /usr/include/bits/mathcalls.h
configpads.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
configpads.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
configpads.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
configpads.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
configpads.o: /usr/include/bits/posix2_lim.h
configpads.o: ../../../include/yalecad/okmalloc.h
configpads.o: ../../../include/yalecad/file.h pads.h parser.h
configpads.o: ../../../include/yalecad/relpos.h
configpads.o: ../../../include/yalecad/message.h
configure.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
configure.o: /usr/include/features.h /usr/include/sys/cdefs.h
configure.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
configure.o: /usr/include/gnu/stubs-64.h
configure.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
configure.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
configure.o: /usr/include/libio.h /usr/include/_G_config.h
configure.o: /usr/include/wchar.h
configure.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
configure.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
configure.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
configure.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
configure.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
configure.o: /usr/include/sys/types.h /usr/include/time.h
configure.o: /usr/include/sys/select.h /usr/include/bits/select.h
configure.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
configure.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
configure.o: /usr/include/alloca.h /usr/include/math.h
configure.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
configure.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
configure.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
configure.o: /usr/include/bits/mathcalls.h
configure.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
configure.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
configure.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
configure.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
configure.o: /usr/include/bits/posix2_lim.h
configure.o: ../../../include/yalecad/okmalloc.h
configure.o: ../../../include/yalecad/file.h config.h parser.h pads.h main.h
configure.o: readpar.h ../../../include/yalecad/debug.h
configure.o: ../../../include/yalecad/message.h
countf.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
countf.o: /usr/include/features.h /usr/include/sys/cdefs.h
countf.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
countf.o: /usr/include/gnu/stubs-64.h
countf.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
countf.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
countf.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
countf.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
countf.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
countf.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
countf.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
countf.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
countf.o: /usr/include/sys/types.h /usr/include/time.h
countf.o: /usr/include/sys/select.h /usr/include/bits/select.h
countf.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
countf.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
countf.o: /usr/include/alloca.h /usr/include/math.h
countf.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
countf.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
countf.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
countf.o: /usr/include/bits/mathcalls.h
countf.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
countf.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
countf.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
countf.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
countf.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
countf.o: ../../../include/yalecad/file.h groute.h feeds.h main.h ucxxglb.h
countf.o: readpar.h parser.h pads.h
crossbus.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
crossbus.o: /usr/include/features.h /usr/include/sys/cdefs.h
crossbus.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
crossbus.o: /usr/include/gnu/stubs-64.h
crossbus.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
crossbus.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
crossbus.o: /usr/include/libio.h /usr/include/_G_config.h
crossbus.o: /usr/include/wchar.h
crossbus.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
crossbus.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
crossbus.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
crossbus.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
crossbus.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
crossbus.o: /usr/include/sys/types.h /usr/include/time.h
crossbus.o: /usr/include/sys/select.h /usr/include/bits/select.h
crossbus.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
crossbus.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
crossbus.o: /usr/include/alloca.h /usr/include/math.h
crossbus.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
crossbus.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
crossbus.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
crossbus.o: /usr/include/bits/mathcalls.h
crossbus.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
crossbus.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
crossbus.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
crossbus.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
crossbus.o: /usr/include/bits/posix2_lim.h
crossbus.o: ../../../include/yalecad/okmalloc.h
crossbus.o: ../../../include/yalecad/file.h main.h groute.h pads.h
debug.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
debug.o: /usr/include/features.h /usr/include/sys/cdefs.h
debug.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
debug.o: /usr/include/gnu/stubs-64.h
debug.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
debug.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
debug.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
debug.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
debug.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
debug.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
debug.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
debug.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
debug.o: /usr/include/sys/types.h /usr/include/time.h
debug.o: /usr/include/sys/select.h /usr/include/bits/select.h
debug.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
debug.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
debug.o: /usr/include/alloca.h /usr/include/math.h
debug.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
debug.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
debug.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
debug.o: /usr/include/bits/mathcalls.h
debug.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
debug.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
debug.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
debug.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
debug.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
debug.o: ../../../include/yalecad/file.h groute.h pads.h
debug2.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
debug2.o: /usr/include/features.h /usr/include/sys/cdefs.h
debug2.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
debug2.o: /usr/include/gnu/stubs-64.h
debug2.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
debug2.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
debug2.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
debug2.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
debug2.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
debug2.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
debug2.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
debug2.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
debug2.o: /usr/include/sys/types.h /usr/include/time.h
debug2.o: /usr/include/sys/select.h /usr/include/bits/select.h
debug2.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
debug2.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
debug2.o: /usr/include/alloca.h /usr/include/math.h
debug2.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
debug2.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
debug2.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
debug2.o: /usr/include/bits/mathcalls.h
debug2.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
debug2.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
debug2.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
debug2.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
debug2.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
debug2.o: ../../../include/yalecad/file.h groute.h feeds.h pads.h
debug2.o: ../../../include/yalecad/debug.h ../../../include/yalecad/message.h
dimbox.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
dimbox.o: /usr/include/features.h /usr/include/sys/cdefs.h
dimbox.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
dimbox.o: /usr/include/gnu/stubs-64.h
dimbox.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
dimbox.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
dimbox.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
dimbox.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
dimbox.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
dimbox.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
dimbox.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
dimbox.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
dimbox.o: /usr/include/sys/types.h /usr/include/time.h
dimbox.o: /usr/include/sys/select.h /usr/include/bits/select.h
dimbox.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
dimbox.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
dimbox.o: /usr/include/alloca.h /usr/include/math.h
dimbox.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
dimbox.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
dimbox.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
dimbox.o: /usr/include/bits/mathcalls.h
dimbox.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
dimbox.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
dimbox.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
dimbox.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
dimbox.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
dimbox.o: ../../../include/yalecad/file.h
feedest.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
feedest.o: /usr/include/features.h /usr/include/sys/cdefs.h
feedest.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
feedest.o: /usr/include/gnu/stubs-64.h
feedest.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
feedest.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
feedest.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
feedest.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
feedest.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
feedest.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
feedest.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
feedest.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
feedest.o: /usr/include/sys/types.h /usr/include/time.h
feedest.o: /usr/include/sys/select.h /usr/include/bits/select.h
feedest.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
feedest.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
feedest.o: /usr/include/alloca.h /usr/include/math.h
feedest.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
feedest.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
feedest.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
feedest.o: /usr/include/bits/mathcalls.h
feedest.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
feedest.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
feedest.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
feedest.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
feedest.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
feedest.o: ../../../include/yalecad/file.h groute.h feeds.h main.h
findcost.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
findcost.o: /usr/include/features.h /usr/include/sys/cdefs.h
findcost.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
findcost.o: /usr/include/gnu/stubs-64.h
findcost.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
findcost.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
findcost.o: /usr/include/libio.h /usr/include/_G_config.h
findcost.o: /usr/include/wchar.h
findcost.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
findcost.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
findcost.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
findcost.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
findcost.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
findcost.o: /usr/include/sys/types.h /usr/include/time.h
findcost.o: /usr/include/sys/select.h /usr/include/bits/select.h
findcost.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
findcost.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
findcost.o: /usr/include/alloca.h /usr/include/math.h
findcost.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
findcost.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
findcost.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
findcost.o: /usr/include/bits/mathcalls.h
findcost.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
findcost.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
findcost.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
findcost.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
findcost.o: /usr/include/bits/posix2_lim.h
findcost.o: ../../../include/yalecad/okmalloc.h
findcost.o: ../../../include/yalecad/file.h groute.h main.h config.h
findcost.o: readpar.h parser.h ../../../include/yalecad/debug.h
findcost.o: ../../../include/yalecad/message.h
findcostf.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
findcostf.o: /usr/include/features.h /usr/include/sys/cdefs.h
findcostf.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
findcostf.o: /usr/include/gnu/stubs-64.h
findcostf.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
findcostf.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
findcostf.o: /usr/include/libio.h /usr/include/_G_config.h
findcostf.o: /usr/include/wchar.h
findcostf.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
findcostf.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
findcostf.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
findcostf.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
findcostf.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
findcostf.o: /usr/include/sys/types.h /usr/include/time.h
findcostf.o: /usr/include/sys/select.h /usr/include/bits/select.h
findcostf.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
findcostf.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
findcostf.o: /usr/include/alloca.h /usr/include/math.h
findcostf.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
findcostf.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
findcostf.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
findcostf.o: /usr/include/bits/mathcalls.h
findcostf.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
findcostf.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
findcostf.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
findcostf.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
findcostf.o: /usr/include/bits/posix2_lim.h
findcostf.o: ../../../include/yalecad/okmalloc.h
findcostf.o: ../../../include/yalecad/file.h groute.h config.h parser.h
findcostf.o: feeds.h main.h ../../../include/yalecad/debug.h
findcostf.o: ../../../include/yalecad/message.h
findrcost.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
findrcost.o: /usr/include/features.h /usr/include/sys/cdefs.h
findrcost.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
findrcost.o: /usr/include/gnu/stubs-64.h
findrcost.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
findrcost.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
findrcost.o: /usr/include/libio.h /usr/include/_G_config.h
findrcost.o: /usr/include/wchar.h
findrcost.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
findrcost.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
findrcost.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
findrcost.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
findrcost.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
findrcost.o: /usr/include/sys/types.h /usr/include/time.h
findrcost.o: /usr/include/sys/select.h /usr/include/bits/select.h
findrcost.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
findrcost.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
findrcost.o: /usr/include/alloca.h /usr/include/math.h
findrcost.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
findrcost.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
findrcost.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
findrcost.o: /usr/include/bits/mathcalls.h
findrcost.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
findrcost.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
findrcost.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
findrcost.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
findrcost.o: /usr/include/bits/posix2_lim.h
findrcost.o: ../../../include/yalecad/okmalloc.h
findrcost.o: ../../../include/yalecad/file.h groute.h
findunlap.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
findunlap.o: /usr/include/features.h /usr/include/sys/cdefs.h
findunlap.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
findunlap.o: /usr/include/gnu/stubs-64.h
findunlap.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
findunlap.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
findunlap.o: /usr/include/libio.h /usr/include/_G_config.h
findunlap.o: /usr/include/wchar.h
findunlap.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
findunlap.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
findunlap.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
findunlap.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
findunlap.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
findunlap.o: /usr/include/sys/types.h /usr/include/time.h
findunlap.o: /usr/include/sys/select.h /usr/include/bits/select.h
findunlap.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
findunlap.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
findunlap.o: /usr/include/alloca.h /usr/include/math.h
findunlap.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
findunlap.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
findunlap.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
findunlap.o: /usr/include/bits/mathcalls.h
findunlap.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
findunlap.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
findunlap.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
findunlap.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
findunlap.o: /usr/include/bits/posix2_lim.h
findunlap.o: ../../../include/yalecad/okmalloc.h
findunlap.o: ../../../include/yalecad/file.h main.h groute.h feeds.h
findunlap.o: ../../../include/yalecad/debug.h
findunlap.o: ../../../include/yalecad/message.h
gateswap.o: /usr/include/string.h /usr/include/features.h
gateswap.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
gateswap.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
gateswap.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
gateswap.o: /usr/include/xlocale.h ucxxglb.h standard.h
gateswap.o: ../../../include/yalecad/base.h /usr/include/stdio.h
gateswap.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
gateswap.o: /usr/include/libio.h /usr/include/_G_config.h
gateswap.o: /usr/include/wchar.h
gateswap.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
gateswap.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
gateswap.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
gateswap.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
gateswap.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
gateswap.o: /usr/include/sys/types.h /usr/include/time.h
gateswap.o: /usr/include/sys/select.h /usr/include/bits/select.h
gateswap.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
gateswap.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
gateswap.o: /usr/include/alloca.h /usr/include/math.h
gateswap.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
gateswap.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
gateswap.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
gateswap.o: /usr/include/bits/mathcalls.h
gateswap.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
gateswap.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
gateswap.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
gateswap.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
gateswap.o: /usr/include/bits/posix2_lim.h
gateswap.o: ../../../include/yalecad/okmalloc.h
gateswap.o: ../../../include/yalecad/file.h parser.h
gateswap.o: ../../../include/yalecad/debug.h
gateswap.o: ../../../include/yalecad/message.h readnets.h
globe.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
globe.o: /usr/include/features.h /usr/include/sys/cdefs.h
globe.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
globe.o: /usr/include/gnu/stubs-64.h
globe.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
globe.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
globe.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
globe.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
globe.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
globe.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
globe.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
globe.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
globe.o: /usr/include/sys/types.h /usr/include/time.h
globe.o: /usr/include/sys/select.h /usr/include/bits/select.h
globe.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
globe.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
globe.o: /usr/include/alloca.h /usr/include/math.h
globe.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
globe.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
globe.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
globe.o: /usr/include/bits/mathcalls.h
globe.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
globe.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
globe.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
globe.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
globe.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
globe.o: ../../../include/yalecad/file.h groute.h main.h parser.h feeds.h
globe.o: ../../../include/yalecad/assign.h ../../../include/yalecad/debug.h
globe.o: ../../../include/yalecad/message.h
globroute.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
globroute.o: /usr/include/features.h /usr/include/sys/cdefs.h
globroute.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
globroute.o: /usr/include/gnu/stubs-64.h
globroute.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
globroute.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
globroute.o: /usr/include/libio.h /usr/include/_G_config.h
globroute.o: /usr/include/wchar.h
globroute.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
globroute.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
globroute.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
globroute.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
globroute.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
globroute.o: /usr/include/sys/types.h /usr/include/time.h
globroute.o: /usr/include/sys/select.h /usr/include/bits/select.h
globroute.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
globroute.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
globroute.o: /usr/include/alloca.h /usr/include/math.h
globroute.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
globroute.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
globroute.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
globroute.o: /usr/include/bits/mathcalls.h
globroute.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
globroute.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
globroute.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
globroute.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
globroute.o: /usr/include/bits/posix2_lim.h
globroute.o: ../../../include/yalecad/okmalloc.h
globroute.o: ../../../include/yalecad/file.h groute.h main.h
graphics.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
graphics.o: /usr/include/features.h /usr/include/sys/cdefs.h
graphics.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
graphics.o: /usr/include/gnu/stubs-64.h
graphics.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
graphics.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
graphics.o: /usr/include/libio.h /usr/include/_G_config.h
graphics.o: /usr/include/wchar.h
graphics.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
graphics.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
graphics.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
graphics.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
graphics.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
graphics.o: /usr/include/sys/types.h /usr/include/time.h
graphics.o: /usr/include/sys/select.h /usr/include/bits/select.h
graphics.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
graphics.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
graphics.o: /usr/include/alloca.h /usr/include/math.h
graphics.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
graphics.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
graphics.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
graphics.o: /usr/include/bits/mathcalls.h
graphics.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
graphics.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
graphics.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
graphics.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
graphics.o: /usr/include/bits/posix2_lim.h
graphics.o: ../../../include/yalecad/okmalloc.h
graphics.o: ../../../include/yalecad/file.h main.h readpar.h pads.h
graphics.o: ../../../include/yalecad/debug.h
graphics.o: ../../../include/yalecad/message.h
graphics.o: ../../../include/yalecad/colors.h ../../../include/yalecad/draw.h
graphics.o: ../../../include/yalecad/relpos.h ./menus.h
main.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
main.o: /usr/include/features.h /usr/include/sys/cdefs.h
main.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
main.o: /usr/include/gnu/stubs-64.h
main.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
main.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
main.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
main.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
main.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
main.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
main.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
main.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
main.o: /usr/include/sys/types.h /usr/include/time.h
main.o: /usr/include/sys/select.h /usr/include/bits/select.h
main.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
main.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
main.o: /usr/include/alloca.h /usr/include/math.h
main.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
main.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
main.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
main.o: /usr/include/bits/mathcalls.h
main.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
main.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
main.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
main.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
main.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
main.o: ../../../include/yalecad/file.h main.h groute.h readpar.h parser.h
main.o: feeds.h pads.h /usr/include/string.h /usr/include/xlocale.h
main.o: /usr/include/signal.h /usr/include/bits/signum.h
main.o: /usr/include/bits/siginfo.h /usr/include/bits/sigaction.h
main.o: /usr/include/bits/sigcontext.h /usr/include/bits/sigstack.h
main.o: /usr/include/sys/ucontext.h /usr/include/bits/sigthread.h
main.o: ../../../include/yalecad/cleanup.h ../../../include/yalecad/message.h
mergeseg.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
mergeseg.o: /usr/include/features.h /usr/include/sys/cdefs.h
mergeseg.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
mergeseg.o: /usr/include/gnu/stubs-64.h
mergeseg.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
mergeseg.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
mergeseg.o: /usr/include/libio.h /usr/include/_G_config.h
mergeseg.o: /usr/include/wchar.h
mergeseg.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
mergeseg.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
mergeseg.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
mergeseg.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
mergeseg.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
mergeseg.o: /usr/include/sys/types.h /usr/include/time.h
mergeseg.o: /usr/include/sys/select.h /usr/include/bits/select.h
mergeseg.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
mergeseg.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
mergeseg.o: /usr/include/alloca.h /usr/include/math.h
mergeseg.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
mergeseg.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
mergeseg.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
mergeseg.o: /usr/include/bits/mathcalls.h
mergeseg.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
mergeseg.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
mergeseg.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
mergeseg.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
mergeseg.o: /usr/include/bits/posix2_lim.h
mergeseg.o: ../../../include/yalecad/okmalloc.h
mergeseg.o: ../../../include/yalecad/file.h groute.h
netgraph.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
netgraph.o: /usr/include/features.h /usr/include/sys/cdefs.h
netgraph.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
netgraph.o: /usr/include/gnu/stubs-64.h
netgraph.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
netgraph.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
netgraph.o: /usr/include/libio.h /usr/include/_G_config.h
netgraph.o: /usr/include/wchar.h
netgraph.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
netgraph.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
netgraph.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
netgraph.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
netgraph.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
netgraph.o: /usr/include/sys/types.h /usr/include/time.h
netgraph.o: /usr/include/sys/select.h /usr/include/bits/select.h
netgraph.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
netgraph.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
netgraph.o: /usr/include/alloca.h /usr/include/math.h
netgraph.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
netgraph.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
netgraph.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
netgraph.o: /usr/include/bits/mathcalls.h
netgraph.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
netgraph.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
netgraph.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
netgraph.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
netgraph.o: /usr/include/bits/posix2_lim.h
netgraph.o: ../../../include/yalecad/okmalloc.h
netgraph.o: ../../../include/yalecad/file.h groute.h main.h
newtemp.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
newtemp.o: /usr/include/features.h /usr/include/sys/cdefs.h
newtemp.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
newtemp.o: /usr/include/gnu/stubs-64.h
newtemp.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
newtemp.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
newtemp.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
newtemp.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
newtemp.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
newtemp.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
newtemp.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
newtemp.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
newtemp.o: /usr/include/sys/types.h /usr/include/time.h
newtemp.o: /usr/include/sys/select.h /usr/include/bits/select.h
newtemp.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
newtemp.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
newtemp.o: /usr/include/alloca.h /usr/include/math.h
newtemp.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
newtemp.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
newtemp.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
newtemp.o: /usr/include/bits/mathcalls.h
newtemp.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
newtemp.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
newtemp.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
newtemp.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
newtemp.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
newtemp.o: ../../../include/yalecad/file.h ../../../include/yalecad/debug.h
newtemp.o: ../../../include/yalecad/message.h
outpins.o: /usr/include/string.h /usr/include/features.h
outpins.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
outpins.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
outpins.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
outpins.o: /usr/include/xlocale.h standard.h ../../../include/yalecad/base.h
outpins.o: /usr/include/stdio.h /usr/include/bits/types.h
outpins.o: /usr/include/bits/typesizes.h /usr/include/libio.h
outpins.o: /usr/include/_G_config.h /usr/include/wchar.h
outpins.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
outpins.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
outpins.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
outpins.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
outpins.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
outpins.o: /usr/include/sys/types.h /usr/include/time.h
outpins.o: /usr/include/sys/select.h /usr/include/bits/select.h
outpins.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
outpins.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
outpins.o: /usr/include/alloca.h /usr/include/math.h
outpins.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
outpins.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
outpins.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
outpins.o: /usr/include/bits/mathcalls.h
outpins.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
outpins.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
outpins.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
outpins.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
outpins.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
outpins.o: ../../../include/yalecad/file.h groute.h main.h readpar.h pads.h
outpins.o: ../../../include/yalecad/debug.h
outpins.o: ../../../include/yalecad/message.h
outpins1.o: /usr/include/string.h /usr/include/features.h
outpins1.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
outpins1.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
outpins1.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
outpins1.o: /usr/include/xlocale.h standard.h ../../../include/yalecad/base.h
outpins1.o: /usr/include/stdio.h /usr/include/bits/types.h
outpins1.o: /usr/include/bits/typesizes.h /usr/include/libio.h
outpins1.o: /usr/include/_G_config.h /usr/include/wchar.h
outpins1.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
outpins1.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
outpins1.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
outpins1.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
outpins1.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
outpins1.o: /usr/include/sys/types.h /usr/include/time.h
outpins1.o: /usr/include/sys/select.h /usr/include/bits/select.h
outpins1.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
outpins1.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
outpins1.o: /usr/include/alloca.h /usr/include/math.h
outpins1.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
outpins1.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
outpins1.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
outpins1.o: /usr/include/bits/mathcalls.h
outpins1.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
outpins1.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
outpins1.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
outpins1.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
outpins1.o: /usr/include/bits/posix2_lim.h
outpins1.o: ../../../include/yalecad/okmalloc.h
outpins1.o: ../../../include/yalecad/file.h groute.h main.h readpar.h pads.h
outpins1.o: ../../../include/yalecad/debug.h
outpins1.o: ../../../include/yalecad/message.h
output.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
output.o: /usr/include/features.h /usr/include/sys/cdefs.h
output.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
output.o: /usr/include/gnu/stubs-64.h
output.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
output.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
output.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
output.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
output.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
output.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
output.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
output.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
output.o: /usr/include/sys/types.h /usr/include/time.h
output.o: /usr/include/sys/select.h /usr/include/bits/select.h
output.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
output.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
output.o: /usr/include/alloca.h /usr/include/math.h
output.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
output.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
output.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
output.o: /usr/include/bits/mathcalls.h
output.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
output.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
output.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
output.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
output.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
output.o: ../../../include/yalecad/file.h groute.h main.h readpar.h config.h
output.o: pads.h /usr/include/string.h /usr/include/xlocale.h
output.o: ../../../include/yalecad/debug.h ../../../include/yalecad/message.h
overlap.o: ucxxglb.h standard.h ../../../include/yalecad/base.h
overlap.o: /usr/include/stdio.h /usr/include/features.h
overlap.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
overlap.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
overlap.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
overlap.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
overlap.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
overlap.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
overlap.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
overlap.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
overlap.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
overlap.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
overlap.o: /usr/include/sys/types.h /usr/include/time.h
overlap.o: /usr/include/sys/select.h /usr/include/bits/select.h
overlap.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
overlap.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
overlap.o: /usr/include/alloca.h /usr/include/math.h
overlap.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
overlap.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
overlap.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
overlap.o: /usr/include/bits/mathcalls.h
overlap.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
overlap.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
overlap.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
overlap.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
overlap.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
overlap.o: ../../../include/yalecad/file.h
parser.o: /usr/include/string.h /usr/include/features.h
parser.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
parser.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
parser.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
parser.o: /usr/include/xlocale.h standard.h ../../../include/yalecad/base.h
parser.o: /usr/include/stdio.h /usr/include/bits/types.h
parser.o: /usr/include/bits/typesizes.h /usr/include/libio.h
parser.o: /usr/include/_G_config.h /usr/include/wchar.h
parser.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
parser.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
parser.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
parser.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
parser.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
parser.o: /usr/include/sys/types.h /usr/include/time.h
parser.o: /usr/include/sys/select.h /usr/include/bits/select.h
parser.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
parser.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
parser.o: /usr/include/alloca.h /usr/include/math.h
parser.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
parser.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
parser.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
parser.o: /usr/include/bits/mathcalls.h
parser.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
parser.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
parser.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
parser.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
parser.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
parser.o: ../../../include/yalecad/file.h groute.h parser.h main.h readblck.h
parser.o: readpar.h config.h feeds.h pads.h ../../../include/yalecad/hash.h
parser.o: ../../../include/yalecad/message.h
parser.o: ../../../include/yalecad/relpos.h ../../../include/yalecad/string.h
parser.o: ../../../include/yalecad/debug.h
paths.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
paths.o: /usr/include/features.h /usr/include/sys/cdefs.h
paths.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
paths.o: /usr/include/gnu/stubs-64.h
paths.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
paths.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
paths.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
paths.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
paths.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
paths.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
paths.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
paths.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
paths.o: /usr/include/sys/types.h /usr/include/time.h
paths.o: /usr/include/sys/select.h /usr/include/bits/select.h
paths.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
paths.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
paths.o: /usr/include/alloca.h /usr/include/math.h
paths.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
paths.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
paths.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
paths.o: /usr/include/bits/mathcalls.h
paths.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
paths.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
paths.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
paths.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
paths.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
paths.o: ../../../include/yalecad/file.h main.h
paths.o: ../../../include/yalecad/debug.h ../../../include/yalecad/message.h
paths.o: readnets.h ../../../include/yalecad/stat.h
placepads.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
placepads.o: /usr/include/features.h /usr/include/sys/cdefs.h
placepads.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
placepads.o: /usr/include/gnu/stubs-64.h
placepads.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
placepads.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
placepads.o: /usr/include/libio.h /usr/include/_G_config.h
placepads.o: /usr/include/wchar.h
placepads.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
placepads.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
placepads.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
placepads.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
placepads.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
placepads.o: /usr/include/sys/types.h /usr/include/time.h
placepads.o: /usr/include/sys/select.h /usr/include/bits/select.h
placepads.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
placepads.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
placepads.o: /usr/include/alloca.h /usr/include/math.h
placepads.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
placepads.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
placepads.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
placepads.o: /usr/include/bits/mathcalls.h
placepads.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
placepads.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
placepads.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
placepads.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
placepads.o: /usr/include/bits/posix2_lim.h
placepads.o: ../../../include/yalecad/okmalloc.h
placepads.o: ../../../include/yalecad/file.h pads.h config.h parser.h
placepads.o: ../../../include/yalecad/debug.h
placepads.o: ../../../include/yalecad/message.h
readblck.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
readblck.o: /usr/include/features.h /usr/include/sys/cdefs.h
readblck.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
readblck.o: /usr/include/gnu/stubs-64.h
readblck.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
readblck.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
readblck.o: /usr/include/libio.h /usr/include/_G_config.h
readblck.o: /usr/include/wchar.h
readblck.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
readblck.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
readblck.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
readblck.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
readblck.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
readblck.o: /usr/include/sys/types.h /usr/include/time.h
readblck.o: /usr/include/sys/select.h /usr/include/bits/select.h
readblck.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
readblck.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
readblck.o: /usr/include/alloca.h /usr/include/math.h
readblck.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
readblck.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
readblck.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
readblck.o: /usr/include/bits/mathcalls.h
readblck.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
readblck.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
readblck.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
readblck.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
readblck.o: /usr/include/bits/posix2_lim.h
readblck.o: ../../../include/yalecad/okmalloc.h
readblck.o: ../../../include/yalecad/file.h main.h parser.h readpar.h
readblck.o: config.h readblck.h
readcell.o: ../../../include/yalecad/base.h /usr/include/stdio.h
readcell.o: /usr/include/features.h /usr/include/sys/cdefs.h
readcell.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
readcell.o: /usr/include/gnu/stubs-64.h
readcell.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
readcell.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
readcell.o: /usr/include/libio.h /usr/include/_G_config.h
readcell.o: /usr/include/wchar.h
readcell.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
readcell.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
readcell.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
readcell.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
readcell.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
readcell.o: /usr/include/sys/types.h /usr/include/time.h
readcell.o: /usr/include/sys/select.h /usr/include/bits/select.h
readcell.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
readcell.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
readcell.o: /usr/include/alloca.h /usr/include/math.h
readcell.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
readcell.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
readcell.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
readcell.o: /usr/include/bits/mathcalls.h
readcell.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
readcell.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
readcell.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
readcell.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
readcell.o: /usr/include/bits/posix2_lim.h
readcell.o: ../../../include/yalecad/okmalloc.h
readcell.o: ../../../include/yalecad/message.h
readcell.o: ../../../include/yalecad/string.h
readcell.o: ../../../include/yalecad/debug.h readcell.h standard.h
readcell.o: ../../../include/yalecad/file.h parser.h main.h readcell_l.h
readnets.o: ../../../include/yalecad/message.h
readnets.o: ../../../include/yalecad/base.h /usr/include/stdio.h
readnets.o: /usr/include/features.h /usr/include/sys/cdefs.h
readnets.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
readnets.o: /usr/include/gnu/stubs-64.h
readnets.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
readnets.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
readnets.o: /usr/include/libio.h /usr/include/_G_config.h
readnets.o: /usr/include/wchar.h
readnets.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
readnets.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
readnets.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
readnets.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
readnets.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
readnets.o: /usr/include/sys/types.h /usr/include/time.h
readnets.o: /usr/include/sys/select.h /usr/include/bits/select.h
readnets.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
readnets.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
readnets.o: /usr/include/alloca.h /usr/include/math.h
readnets.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
readnets.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
readnets.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
readnets.o: /usr/include/bits/mathcalls.h
readnets.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
readnets.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
readnets.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
readnets.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
readnets.o: /usr/include/bits/posix2_lim.h
readnets.o: ../../../include/yalecad/okmalloc.h
readnets.o: ../../../include/yalecad/debug.h ../../../include/yalecad/hash.h
readnets.o: readnets.h standard.h ../../../include/yalecad/file.h main.h
readnets.o: readnets_l.h
readpar.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
readpar.o: /usr/include/features.h /usr/include/sys/cdefs.h
readpar.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
readpar.o: /usr/include/gnu/stubs-64.h
readpar.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
readpar.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
readpar.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
readpar.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
readpar.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
readpar.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
readpar.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
readpar.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
readpar.o: /usr/include/sys/types.h /usr/include/time.h
readpar.o: /usr/include/sys/select.h /usr/include/bits/select.h
readpar.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
readpar.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
readpar.o: /usr/include/alloca.h /usr/include/math.h
readpar.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
readpar.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
readpar.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
readpar.o: /usr/include/bits/mathcalls.h
readpar.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
readpar.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
readpar.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
readpar.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
readpar.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
readpar.o: ../../../include/yalecad/file.h main.h parser.h readpar.h groute.h
readpar.o: feeds.h config.h pads.h ../../../include/yalecad/message.h
readpar.o: ../../../include/yalecad/string.h
readpar.o: ../../../include/yalecad/yreadpar.h
readpar.o: ../../../include/yalecad/rbtree.h
reconfig.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
reconfig.o: /usr/include/features.h /usr/include/sys/cdefs.h
reconfig.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
reconfig.o: /usr/include/gnu/stubs-64.h
reconfig.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
reconfig.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
reconfig.o: /usr/include/libio.h /usr/include/_G_config.h
reconfig.o: /usr/include/wchar.h
reconfig.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
reconfig.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
reconfig.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
reconfig.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
reconfig.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
reconfig.o: /usr/include/sys/types.h /usr/include/time.h
reconfig.o: /usr/include/sys/select.h /usr/include/bits/select.h
reconfig.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
reconfig.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
reconfig.o: /usr/include/alloca.h /usr/include/math.h
reconfig.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
reconfig.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
reconfig.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
reconfig.o: /usr/include/bits/mathcalls.h
reconfig.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
reconfig.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
reconfig.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
reconfig.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
reconfig.o: /usr/include/bits/posix2_lim.h
reconfig.o: ../../../include/yalecad/okmalloc.h
reconfig.o: ../../../include/yalecad/file.h readpar.h main.h
reconfig.o: ../../../include/yalecad/message.h
reconfig.o: ../../../include/yalecad/string.h
reconfig.o: ../../../include/yalecad/debug.h
rmoverlap.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
rmoverlap.o: /usr/include/features.h /usr/include/sys/cdefs.h
rmoverlap.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
rmoverlap.o: /usr/include/gnu/stubs-64.h
rmoverlap.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
rmoverlap.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
rmoverlap.o: /usr/include/libio.h /usr/include/_G_config.h
rmoverlap.o: /usr/include/wchar.h
rmoverlap.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
rmoverlap.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
rmoverlap.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
rmoverlap.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
rmoverlap.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
rmoverlap.o: /usr/include/sys/types.h /usr/include/time.h
rmoverlap.o: /usr/include/sys/select.h /usr/include/bits/select.h
rmoverlap.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
rmoverlap.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
rmoverlap.o: /usr/include/alloca.h /usr/include/math.h
rmoverlap.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
rmoverlap.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
rmoverlap.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
rmoverlap.o: /usr/include/bits/mathcalls.h
rmoverlap.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
rmoverlap.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
rmoverlap.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
rmoverlap.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
rmoverlap.o: /usr/include/bits/posix2_lim.h
rmoverlap.o: ../../../include/yalecad/okmalloc.h
rmoverlap.o: ../../../include/yalecad/file.h groute.h
rowevener.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
rowevener.o: /usr/include/features.h /usr/include/sys/cdefs.h
rowevener.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
rowevener.o: /usr/include/gnu/stubs-64.h
rowevener.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
rowevener.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
rowevener.o: /usr/include/libio.h /usr/include/_G_config.h
rowevener.o: /usr/include/wchar.h
rowevener.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
rowevener.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
rowevener.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
rowevener.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
rowevener.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
rowevener.o: /usr/include/sys/types.h /usr/include/time.h
rowevener.o: /usr/include/sys/select.h /usr/include/bits/select.h
rowevener.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
rowevener.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
rowevener.o: /usr/include/alloca.h /usr/include/math.h
rowevener.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
rowevener.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
rowevener.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
rowevener.o: /usr/include/bits/mathcalls.h
rowevener.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
rowevener.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
rowevener.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
rowevener.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
rowevener.o: /usr/include/bits/posix2_lim.h
rowevener.o: ../../../include/yalecad/okmalloc.h
rowevener.o: ../../../include/yalecad/file.h groute.h feeds.h readpar.h
savewolf.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
savewolf.o: /usr/include/features.h /usr/include/sys/cdefs.h
savewolf.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
savewolf.o: /usr/include/gnu/stubs-64.h
savewolf.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
savewolf.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
savewolf.o: /usr/include/libio.h /usr/include/_G_config.h
savewolf.o: /usr/include/wchar.h
savewolf.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
savewolf.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
savewolf.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
savewolf.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
savewolf.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
savewolf.o: /usr/include/sys/types.h /usr/include/time.h
savewolf.o: /usr/include/sys/select.h /usr/include/bits/select.h
savewolf.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
savewolf.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
savewolf.o: /usr/include/alloca.h /usr/include/math.h
savewolf.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
savewolf.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
savewolf.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
savewolf.o: /usr/include/bits/mathcalls.h
savewolf.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
savewolf.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
savewolf.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
savewolf.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
savewolf.o: /usr/include/bits/posix2_lim.h
savewolf.o: ../../../include/yalecad/okmalloc.h
savewolf.o: ../../../include/yalecad/file.h main.h groute.h feeds.h readpar.h
savewolf.o: parser.h ../../../include/yalecad/message.h
seagate.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
seagate.o: /usr/include/features.h /usr/include/sys/cdefs.h
seagate.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
seagate.o: /usr/include/gnu/stubs-64.h
seagate.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
seagate.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
seagate.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
seagate.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
seagate.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
seagate.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
seagate.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
seagate.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
seagate.o: /usr/include/sys/types.h /usr/include/time.h
seagate.o: /usr/include/sys/select.h /usr/include/bits/select.h
seagate.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
seagate.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
seagate.o: /usr/include/alloca.h /usr/include/math.h
seagate.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
seagate.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
seagate.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
seagate.o: /usr/include/bits/mathcalls.h
seagate.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
seagate.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
seagate.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
seagate.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
seagate.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
seagate.o: ../../../include/yalecad/file.h groute.h main.h readpar.h pads.h
sortpin.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
sortpin.o: /usr/include/features.h /usr/include/sys/cdefs.h
sortpin.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
sortpin.o: /usr/include/gnu/stubs-64.h
sortpin.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
sortpin.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
sortpin.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
sortpin.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
sortpin.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
sortpin.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
sortpin.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
sortpin.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
sortpin.o: /usr/include/sys/types.h /usr/include/time.h
sortpin.o: /usr/include/sys/select.h /usr/include/bits/select.h
sortpin.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
sortpin.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
sortpin.o: /usr/include/alloca.h /usr/include/math.h
sortpin.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
sortpin.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
sortpin.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
sortpin.o: /usr/include/bits/mathcalls.h
sortpin.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
sortpin.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
sortpin.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
sortpin.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
sortpin.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
sortpin.o: ../../../include/yalecad/file.h groute.h feeds.h
sortpad.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
sortpad.o: /usr/include/features.h /usr/include/sys/cdefs.h
sortpad.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
sortpad.o: /usr/include/gnu/stubs-64.h
sortpad.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
sortpad.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
sortpad.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
sortpad.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
sortpad.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
sortpad.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
sortpad.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
sortpad.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
sortpad.o: /usr/include/sys/types.h /usr/include/time.h
sortpad.o: /usr/include/sys/select.h /usr/include/bits/select.h
sortpad.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
sortpad.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
sortpad.o: /usr/include/alloca.h /usr/include/math.h
sortpad.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
sortpad.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
sortpad.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
sortpad.o: /usr/include/bits/mathcalls.h
sortpad.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
sortpad.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
sortpad.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
sortpad.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
sortpad.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
sortpad.o: ../../../include/yalecad/file.h pads.h parser.h
sortpad.o: ../../../include/yalecad/debug.h
sortpad.o: ../../../include/yalecad/message.h
sort.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
sort.o: /usr/include/features.h /usr/include/sys/cdefs.h
sort.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
sort.o: /usr/include/gnu/stubs-64.h
sort.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
sort.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
sort.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
sort.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
sort.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
sort.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
sort.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
sort.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
sort.o: /usr/include/sys/types.h /usr/include/time.h
sort.o: /usr/include/sys/select.h /usr/include/bits/select.h
sort.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
sort.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
sort.o: /usr/include/alloca.h /usr/include/math.h
sort.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
sort.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
sort.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
sort.o: /usr/include/bits/mathcalls.h
sort.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
sort.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
sort.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
sort.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
sort.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
sort.o: ../../../include/yalecad/file.h groute.h feeds.h
steiner.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
steiner.o: /usr/include/features.h /usr/include/sys/cdefs.h
steiner.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
steiner.o: /usr/include/gnu/stubs-64.h
steiner.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
steiner.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
steiner.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
steiner.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
steiner.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
steiner.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
steiner.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
steiner.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
steiner.o: /usr/include/sys/types.h /usr/include/time.h
steiner.o: /usr/include/sys/select.h /usr/include/bits/select.h
steiner.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
steiner.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
steiner.o: /usr/include/alloca.h /usr/include/math.h
steiner.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
steiner.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
steiner.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
steiner.o: /usr/include/bits/mathcalls.h
steiner.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
steiner.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
steiner.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
steiner.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
steiner.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
steiner.o: ../../../include/yalecad/file.h groute.h feeds.h
uc0.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
uc0.o: /usr/include/features.h /usr/include/sys/cdefs.h
uc0.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
uc0.o: /usr/include/gnu/stubs-64.h
uc0.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
uc0.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
uc0.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
uc0.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
uc0.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
uc0.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
uc0.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
uc0.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
uc0.o: /usr/include/sys/types.h /usr/include/time.h /usr/include/sys/select.h
uc0.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
uc0.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
uc0.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
uc0.o: /usr/include/math.h /usr/include/bits/huge_val.h
uc0.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
uc0.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
uc0.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
uc0.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
uc0.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
uc0.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
uc0.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
uc0.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
uc0.o: ../../../include/yalecad/file.h ../../../include/yalecad/debug.h
uc0.o: ../../../include/yalecad/message.h
ucxx1.o: ucxxglb.h standard.h ../../../include/yalecad/base.h
ucxx1.o: /usr/include/stdio.h /usr/include/features.h
ucxx1.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
ucxx1.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
ucxx1.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
ucxx1.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
ucxx1.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
ucxx1.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
ucxx1.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
ucxx1.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
ucxx1.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
ucxx1.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
ucxx1.o: /usr/include/sys/types.h /usr/include/time.h
ucxx1.o: /usr/include/sys/select.h /usr/include/bits/select.h
ucxx1.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
ucxx1.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
ucxx1.o: /usr/include/alloca.h /usr/include/math.h
ucxx1.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
ucxx1.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
ucxx1.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
ucxx1.o: /usr/include/bits/mathcalls.h
ucxx1.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
ucxx1.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
ucxx1.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
ucxx1.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
ucxx1.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
ucxx1.o: ../../../include/yalecad/file.h ../../../include/yalecad/debug.h
ucxx1.o: ../../../include/yalecad/message.h
ucxx2.o: ucxxglb.h standard.h ../../../include/yalecad/base.h
ucxx2.o: /usr/include/stdio.h /usr/include/features.h
ucxx2.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
ucxx2.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
ucxx2.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
ucxx2.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
ucxx2.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
ucxx2.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
ucxx2.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
ucxx2.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
ucxx2.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
ucxx2.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
ucxx2.o: /usr/include/sys/types.h /usr/include/time.h
ucxx2.o: /usr/include/sys/select.h /usr/include/bits/select.h
ucxx2.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
ucxx2.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
ucxx2.o: /usr/include/alloca.h /usr/include/math.h
ucxx2.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
ucxx2.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
ucxx2.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
ucxx2.o: /usr/include/bits/mathcalls.h
ucxx2.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
ucxx2.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
ucxx2.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
ucxx2.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
ucxx2.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
ucxx2.o: ../../../include/yalecad/file.h readpar.h
ucxx2.o: ../../../include/yalecad/debug.h ../../../include/yalecad/message.h
ucxxo1.o: ucxxglb.h standard.h ../../../include/yalecad/base.h
ucxxo1.o: /usr/include/stdio.h /usr/include/features.h
ucxxo1.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
ucxxo1.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
ucxxo1.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
ucxxo1.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
ucxxo1.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
ucxxo1.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
ucxxo1.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
ucxxo1.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
ucxxo1.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
ucxxo1.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
ucxxo1.o: /usr/include/sys/types.h /usr/include/time.h
ucxxo1.o: /usr/include/sys/select.h /usr/include/bits/select.h
ucxxo1.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
ucxxo1.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
ucxxo1.o: /usr/include/alloca.h /usr/include/math.h
ucxxo1.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
ucxxo1.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
ucxxo1.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
ucxxo1.o: /usr/include/bits/mathcalls.h
ucxxo1.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
ucxxo1.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
ucxxo1.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
ucxxo1.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
ucxxo1.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
ucxxo1.o: ../../../include/yalecad/file.h ../../../include/yalecad/debug.h
ucxxo1.o: ../../../include/yalecad/message.h
ucxxo2.o: ucxxglb.h standard.h ../../../include/yalecad/base.h
ucxxo2.o: /usr/include/stdio.h /usr/include/features.h
ucxxo2.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
ucxxo2.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
ucxxo2.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
ucxxo2.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
ucxxo2.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
ucxxo2.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
ucxxo2.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
ucxxo2.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
ucxxo2.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
ucxxo2.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
ucxxo2.o: /usr/include/sys/types.h /usr/include/time.h
ucxxo2.o: /usr/include/sys/select.h /usr/include/bits/select.h
ucxxo2.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
ucxxo2.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
ucxxo2.o: /usr/include/alloca.h /usr/include/math.h
ucxxo2.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
ucxxo2.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
ucxxo2.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
ucxxo2.o: /usr/include/bits/mathcalls.h
ucxxo2.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
ucxxo2.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
ucxxo2.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
ucxxo2.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
ucxxo2.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
ucxxo2.o: ../../../include/yalecad/file.h readpar.h
ucxxo2.o: ../../../include/yalecad/debug.h ../../../include/yalecad/message.h
ucxxp.o: ucxxglb.h standard.h ../../../include/yalecad/base.h
ucxxp.o: /usr/include/stdio.h /usr/include/features.h
ucxxp.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
ucxxp.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
ucxxp.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
ucxxp.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
ucxxp.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
ucxxp.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
ucxxp.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
ucxxp.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
ucxxp.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
ucxxp.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
ucxxp.o: /usr/include/sys/types.h /usr/include/time.h
ucxxp.o: /usr/include/sys/select.h /usr/include/bits/select.h
ucxxp.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
ucxxp.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
ucxxp.o: /usr/include/alloca.h /usr/include/math.h
ucxxp.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
ucxxp.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
ucxxp.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
ucxxp.o: /usr/include/bits/mathcalls.h
ucxxp.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
ucxxp.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
ucxxp.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
ucxxp.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
ucxxp.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
ucxxp.o: ../../../include/yalecad/file.h ../../../include/yalecad/debug.h
ucxxp.o: ../../../include/yalecad/message.h
uloop.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
uloop.o: /usr/include/features.h /usr/include/sys/cdefs.h
uloop.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
uloop.o: /usr/include/gnu/stubs-64.h
uloop.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
uloop.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
uloop.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
uloop.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
uloop.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
uloop.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
uloop.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
uloop.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
uloop.o: /usr/include/sys/types.h /usr/include/time.h
uloop.o: /usr/include/sys/select.h /usr/include/bits/select.h
uloop.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
uloop.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
uloop.o: /usr/include/alloca.h /usr/include/math.h
uloop.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
uloop.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
uloop.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
uloop.o: /usr/include/bits/mathcalls.h
uloop.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
uloop.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
uloop.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
uloop.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
uloop.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
uloop.o: ../../../include/yalecad/file.h ucxxglb.h main.h readpar.h parser.h
uloop.o: ../../../include/yalecad/message.h ../../../include/yalecad/debug.h
unlap.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
unlap.o: /usr/include/features.h /usr/include/sys/cdefs.h
unlap.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
unlap.o: /usr/include/gnu/stubs-64.h
unlap.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
unlap.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
unlap.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
unlap.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
unlap.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
unlap.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
unlap.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
unlap.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
unlap.o: /usr/include/sys/types.h /usr/include/time.h
unlap.o: /usr/include/sys/select.h /usr/include/bits/select.h
unlap.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
unlap.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
unlap.o: /usr/include/alloca.h /usr/include/math.h
unlap.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
unlap.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
unlap.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
unlap.o: /usr/include/bits/mathcalls.h
unlap.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
unlap.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
unlap.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
unlap.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
unlap.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
unlap.o: ../../../include/yalecad/file.h groute.h
upair.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
upair.o: /usr/include/features.h /usr/include/sys/cdefs.h
upair.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
upair.o: /usr/include/gnu/stubs-64.h
upair.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
upair.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
upair.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
upair.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
upair.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
upair.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
upair.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
upair.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
upair.o: /usr/include/sys/types.h /usr/include/time.h
upair.o: /usr/include/sys/select.h /usr/include/bits/select.h
upair.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
upair.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
upair.o: /usr/include/alloca.h /usr/include/math.h
upair.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
upair.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
upair.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
upair.o: /usr/include/bits/mathcalls.h
upair.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
upair.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
upair.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
upair.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
upair.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
upair.o: ../../../include/yalecad/file.h main.h
upair.o: ../../../include/yalecad/debug.h ../../../include/yalecad/message.h
urcost.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
urcost.o: /usr/include/features.h /usr/include/sys/cdefs.h
urcost.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
urcost.o: /usr/include/gnu/stubs-64.h
urcost.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
urcost.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
urcost.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
urcost.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
urcost.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
urcost.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
urcost.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
urcost.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
urcost.o: /usr/include/sys/types.h /usr/include/time.h
urcost.o: /usr/include/sys/select.h /usr/include/bits/select.h
urcost.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
urcost.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
urcost.o: /usr/include/alloca.h /usr/include/math.h
urcost.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
urcost.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
urcost.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
urcost.o: /usr/include/bits/mathcalls.h
urcost.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
urcost.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
urcost.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
urcost.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
urcost.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
urcost.o: ../../../include/yalecad/file.h groute.h
urcost.o: ../../../include/yalecad/debug.h ../../../include/yalecad/message.h
utemp.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
utemp.o: /usr/include/features.h /usr/include/sys/cdefs.h
utemp.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
utemp.o: /usr/include/gnu/stubs-64.h
utemp.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
utemp.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
utemp.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
utemp.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
utemp.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
utemp.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
utemp.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
utemp.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
utemp.o: /usr/include/sys/types.h /usr/include/time.h
utemp.o: /usr/include/sys/select.h /usr/include/bits/select.h
utemp.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
utemp.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
utemp.o: /usr/include/alloca.h /usr/include/math.h
utemp.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
utemp.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
utemp.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
utemp.o: /usr/include/bits/mathcalls.h
utemp.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
utemp.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
utemp.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
utemp.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
utemp.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
utemp.o: ../../../include/yalecad/file.h main.h groute.h ucxxglb.h readpar.h
utemp.o: parser.h ../../../include/yalecad/message.h
utemp.o: ../../../include/yalecad/debug.h
xpickint.o: ../../../include/yalecad/base.h /usr/include/stdio.h
xpickint.o: /usr/include/features.h /usr/include/sys/cdefs.h
xpickint.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
xpickint.o: /usr/include/gnu/stubs-64.h
xpickint.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
xpickint.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
xpickint.o: /usr/include/libio.h /usr/include/_G_config.h
xpickint.o: /usr/include/wchar.h
xpickint.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
xpickint.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
xpickint.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
xpickint.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
xpickint.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
xpickint.o: /usr/include/sys/types.h /usr/include/time.h
xpickint.o: /usr/include/sys/select.h /usr/include/bits/select.h
xpickint.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
xpickint.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
xpickint.o: /usr/include/alloca.h /usr/include/math.h
xpickint.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
xpickint.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
xpickint.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
xpickint.o: /usr/include/bits/mathcalls.h
xpickint.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
xpickint.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
xpickint.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
xpickint.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
xpickint.o: /usr/include/bits/posix2_lim.h
xpickint.o: ../../../include/yalecad/okmalloc.h
outcm.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
outcm.o: /usr/include/features.h /usr/include/sys/cdefs.h
outcm.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
outcm.o: /usr/include/gnu/stubs-64.h
outcm.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
outcm.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
outcm.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
outcm.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
outcm.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
outcm.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
outcm.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
outcm.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
outcm.o: /usr/include/sys/types.h /usr/include/time.h
outcm.o: /usr/include/sys/select.h /usr/include/bits/select.h
outcm.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
outcm.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
outcm.o: /usr/include/alloca.h /usr/include/math.h
outcm.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
outcm.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
outcm.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
outcm.o: /usr/include/bits/mathcalls.h
outcm.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
outcm.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
outcm.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
outcm.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
outcm.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
outcm.o: ../../../include/yalecad/file.h groute.h main.h
