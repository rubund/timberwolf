# Ymakefile for program Tomus
#  "@(#)%main.c(Yale) version % /12/91" 
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
PNAME=Tomus

#where the object code is located
objdir=../obj
O=${objdir}/

SRC= \
	acceptt.c \
	b_sort.c \
	cluster.c \
	dimbox.c \
	findcost.c \
	gr.c \
	hash.c \
	init_cost.c \
	lib.c \
	main.c \
	maindraw.c \
	mergetile.c \
	newtemp.c \
	output.c \
	paint.c \
	partition.c \
	paths.c \
	readcell.c \
	readmver.c \
	readnets.c \
	readpar.c \
	set_limits.c \
	sortpin.c \
	tilecost.c \
	tilepenal.c \
	ucxx1.c \
	ucxx2.c \
	uloop.c \
	ulp_end.c \
	ulp_util.c \
	utemp.c 

OBJ= \
	${O}acceptt.o \
	${O}b_sort.o \
	${O}cluster.o \
	${O}dimbox.o \
	${O}findcost.o \
	${O}gr.o \
	${O}hash.o \
	${O}init_cost.o \
	${O}lib.o \
	${O}main.o \
	${O}maindraw.o \
	${O}mergetile.o \
	${O}newtemp.o \
	${O}output.o \
	${O}paint.o \
	${O}partition.o \
	${O}paths.o \
	${O}readcell.o \
	${O}readmver.o \
	${O}readnets.o \
	${O}readpar.o \
	${O}set_limits.o \
	${O}sortpin.o \
	${O}tilecost.o \
	${O}tilepenal.o \
	${O}ucxx1.o \
	${O}ucxx2.o \
	${O}uloop.o \
	${O}ulp_end.o \
	${O}ulp_util.o \
	${O}utemp.o 

INS= \
	date.h \
	dialog.h \
	dialogpart.h \
	main.h \
	menus.h \
	parser.h \
	readcell.h \
	readmver.h \
	readnets.h \
	standard.h 

info:   ; 
	-@${ECHO} "make ${DEST}${PNAME} - usage:" 
	-@${ECHO} "   make install - build program" 
	-@${ECHO} "   make install_non_yale - build program at foreign host" 
	-@${ECHO} "   make clean - remove binary" 
	-@${ECHO} "   make depend - added makefile dependencies" 
	-@${ECHO} "   make sources - pull sources from SCCS" 
	-@${ECHO} "   make lint - run lint on the sources" 


# how to make Tomus program
${DEST}${PNAME}:${OBJ} ${YALECAD}
	${GETDATE}
	${CC} ${CFLAGS} -I. -c ${DATE_C}
	${MV} date.o ${O}date.o
	${CC} ${CFLAGS} ${OPTIONS} -o ${DEST}${PNAME} ${OBJ} ${O}date.o \
	${YALECAD} ${LINKLIB}

# we can't do anything about yalecad but want to update if it has changed
${YALECAD}: ;

install:${DEST}${PNAME}

install_non_yale:${DEST}${PNAME}

clean: ;
	${RM} ${O}* ~* core *.bak foo* y.output y.tab.c

# how to build makefile dependencies
depend : ;
	${MAKEDEPEND} ${CFLAGS} ${OPTIONS} ${IDIR} ${SRC}

# how to make Tomus lint
lint:  ; 
	${LINT} ${LINT_OPT} ${IDIR} ${OPTIONS} *.c > lint.out 

#default sccs operation is get
SCCS_OP=get
#current release
REL=

# how to get sources from sccs
sources : ${SRC} ${INS} ${YMAKEFILE}
${SRC} ${INS} ${YMAKEFILE}: 
	${SCCS} ${SCCS_OP} ${REL} $@

#BEGIN DEPENDENCIES -- DO NOT DELETE THIS LINE

#END DEPENDENCIES -- DO NOT DELETE THIS LINE


# How to compile the sources
${O}acceptt.o:acceptt.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  acceptt.c
	${MV} acceptt.o ${O}acceptt.o
${O}b_sort.o:b_sort.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  b_sort.c
	${MV} b_sort.o ${O}b_sort.o
${O}cluster.o:cluster.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  cluster.c
	${MV} cluster.o ${O}cluster.o
${O}dimbox.o:dimbox.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  dimbox.c
	${MV} dimbox.o ${O}dimbox.o
${O}findcost.o:findcost.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  findcost.c
	${MV} findcost.o ${O}findcost.o
${O}gr.o:gr.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  gr.c
	${MV} gr.o ${O}gr.o
${O}hash.o:hash.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  hash.c
	${MV} hash.o ${O}hash.o
${O}init_cost.o:init_cost.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  init_cost.c
	${MV} init_cost.o ${O}init_cost.o
${O}lib.o:lib.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  lib.c
	${MV} lib.o ${O}lib.o
${O}main.o:main.c
	${CC} ${CLEANUP} ${CFLAGS} ${IDIR} ${OPTIONS} -c  main.c
	${MV} main.o ${O}main.o
${O}maindraw.o:maindraw.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  maindraw.c
	${MV} maindraw.o ${O}maindraw.o
${O}mergetile.o:mergetile.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  mergetile.c
	${MV} mergetile.o ${O}mergetile.o
${O}newtemp.o:newtemp.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  newtemp.c
	${MV} newtemp.o ${O}newtemp.o
${O}output.o:output.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  output.c
	${MV} output.o ${O}output.o
${O}paint.o:paint.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  paint.c
	${MV} paint.o ${O}paint.o
${O}partition.o:partition.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  partition.c
	${MV} partition.o ${O}partition.o
${O}paths.o:paths.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  paths.c
	${MV} paths.o ${O}paths.o
${O}readcell.o:readcell.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  readcell.c
	${MV} readcell.o ${O}readcell.o
${O}readmver.o:readmver.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  readmver.c
	${MV} readmver.o ${O}readmver.o
${O}readnets.o:readnets.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  readnets.c
	${MV} readnets.o ${O}readnets.o
${O}readpar.o:readpar.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  readpar.c
	${MV} readpar.o ${O}readpar.o
${O}set_limits.o:set_limits.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  set_limits.c
	${MV} set_limits.o ${O}set_limits.o
${O}sortpin.o:sortpin.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  sortpin.c
	${MV} sortpin.o ${O}sortpin.o
${O}tilecost.o:tilecost.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  tilecost.c
	${MV} tilecost.o ${O}tilecost.o
${O}tilepenal.o:tilepenal.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  tilepenal.c
	${MV} tilepenal.o ${O}tilepenal.o
${O}ucxx1.o:ucxx1.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  ucxx1.c
	${MV} ucxx1.o ${O}ucxx1.o
${O}ucxx2.o:ucxx2.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  ucxx2.c
	${MV} ucxx2.o ${O}ucxx2.o
${O}uloop.o:uloop.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  uloop.c
	${MV} uloop.o ${O}uloop.o
${O}ulp_end.o:ulp_end.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  ulp_end.c
	${MV} ulp_end.o ${O}ulp_end.o
${O}ulp_util.o:ulp_util.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  ulp_util.c
	${MV} ulp_util.o ${O}ulp_util.o
${O}utemp.o:utemp.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  utemp.c
	${MV} utemp.o ${O}utemp.o

# end makefile
# DO NOT DELETE

acceptt.o: /usr/include/stdio.h /usr/include/features.h
acceptt.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
acceptt.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
acceptt.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
acceptt.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
acceptt.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
acceptt.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
acceptt.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
b_sort.o: /usr/include/stdio.h /usr/include/features.h
b_sort.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
b_sort.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
b_sort.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
b_sort.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
b_sort.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
b_sort.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
b_sort.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
cluster.o: /usr/include/string.h /usr/include/features.h
cluster.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
cluster.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
cluster.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
cluster.o: /usr/include/xlocale.h standard.h ../../../include/yalecad/base.h
cluster.o: /usr/include/stdio.h /usr/include/bits/types.h
cluster.o: /usr/include/bits/typesizes.h /usr/include/libio.h
cluster.o: /usr/include/_G_config.h /usr/include/wchar.h
cluster.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
cluster.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
cluster.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
cluster.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
cluster.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
cluster.o: /usr/include/sys/types.h /usr/include/time.h
cluster.o: /usr/include/sys/select.h /usr/include/bits/select.h
cluster.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
cluster.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
cluster.o: /usr/include/alloca.h /usr/include/math.h
cluster.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
cluster.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
cluster.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
cluster.o: /usr/include/bits/mathcalls.h
cluster.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
cluster.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
cluster.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
cluster.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
cluster.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
cluster.o: parser.h ../../../include/yalecad/string.h
cluster.o: ../../../include/yalecad/debug.h
cluster.o: ../../../include/yalecad/message.h
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
findcost.o: ../../../include/yalecad/debug.h
findcost.o: ../../../include/yalecad/message.h
gr.o: ../../../include/yalecad/deck.h ../../../include/yalecad/base.h
gr.o: /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h
gr.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
gr.o: /usr/include/gnu/stubs-64.h
gr.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
gr.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
gr.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
gr.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
gr.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
gr.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
gr.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
gr.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
gr.o: /usr/include/sys/types.h /usr/include/time.h /usr/include/sys/select.h
gr.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
gr.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
gr.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
gr.o: /usr/include/math.h /usr/include/bits/huge_val.h
gr.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
gr.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
gr.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
gr.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
gr.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
gr.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
gr.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
gr.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
gr.o: ../../../include/yalecad/message.h ../../../include/yalecad/graph.h
gr.o: ../../../include/yalecad/dset.h ../../../include/yalecad/rbtree.h
gr.o: ../../../include/yalecad/draw.h ../../../include/yalecad/colors.h
gr.o: standard.h
hash.o: /usr/include/string.h /usr/include/features.h
hash.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
hash.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
hash.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
hash.o: /usr/include/xlocale.h standard.h ../../../include/yalecad/base.h
hash.o: /usr/include/stdio.h /usr/include/bits/types.h
hash.o: /usr/include/bits/typesizes.h /usr/include/libio.h
hash.o: /usr/include/_G_config.h /usr/include/wchar.h
hash.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
hash.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
hash.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
hash.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
hash.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
hash.o: /usr/include/sys/types.h /usr/include/time.h
hash.o: /usr/include/sys/select.h /usr/include/bits/select.h
hash.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
hash.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
hash.o: /usr/include/alloca.h /usr/include/math.h
hash.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
hash.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
hash.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
hash.o: /usr/include/bits/mathcalls.h
hash.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
hash.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
hash.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
hash.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
hash.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
init_cost.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
init_cost.o: /usr/include/features.h /usr/include/sys/cdefs.h
init_cost.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
init_cost.o: /usr/include/gnu/stubs-64.h
init_cost.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
init_cost.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
init_cost.o: /usr/include/libio.h /usr/include/_G_config.h
init_cost.o: /usr/include/wchar.h
init_cost.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
init_cost.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
init_cost.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
init_cost.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
init_cost.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
init_cost.o: /usr/include/sys/types.h /usr/include/time.h
init_cost.o: /usr/include/sys/select.h /usr/include/bits/select.h
init_cost.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
init_cost.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
init_cost.o: /usr/include/alloca.h /usr/include/math.h
init_cost.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
init_cost.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
init_cost.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
init_cost.o: /usr/include/bits/mathcalls.h
init_cost.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
init_cost.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
init_cost.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
init_cost.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
init_cost.o: /usr/include/bits/posix2_lim.h
init_cost.o: ../../../include/yalecad/okmalloc.h
init_cost.o: ../../../include/yalecad/debug.h
init_cost.o: ../../../include/yalecad/message.h
init_cost.o: ../../../include/yalecad/file.h
lib.o: /usr/include/string.h /usr/include/features.h /usr/include/sys/cdefs.h
lib.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
lib.o: /usr/include/gnu/stubs-64.h
lib.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
lib.o: /usr/include/xlocale.h standard.h ../../../include/yalecad/base.h
lib.o: /usr/include/stdio.h /usr/include/bits/types.h
lib.o: /usr/include/bits/typesizes.h /usr/include/libio.h
lib.o: /usr/include/_G_config.h /usr/include/wchar.h
lib.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
lib.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
lib.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
lib.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
lib.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
lib.o: /usr/include/sys/types.h /usr/include/time.h /usr/include/sys/select.h
lib.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
lib.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
lib.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
lib.o: /usr/include/math.h /usr/include/bits/huge_val.h
lib.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
lib.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
lib.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
lib.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
lib.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
lib.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
lib.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
lib.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
lib.o: main.h parser.h ../../../include/yalecad/message.h
lib.o: ../../../include/yalecad/hash.h ../../../include/yalecad/debug.h
lib.o: ../../../include/yalecad/file.h ../../../include/yalecad/rbtree.h
lib.o: ../../../include/yalecad/string.h
main.o: /usr/include/string.h /usr/include/features.h
main.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
main.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
main.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
main.o: /usr/include/xlocale.h ../../../include/yalecad/cleanup.h
main.o: ../../../include/yalecad/file.h ../../../include/yalecad/base.h
main.o: /usr/include/stdio.h /usr/include/bits/types.h
main.o: /usr/include/bits/typesizes.h /usr/include/libio.h
main.o: /usr/include/_G_config.h /usr/include/wchar.h
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
main.o: ../../../include/yalecad/message.h ../../../include/yalecad/string.h
main.o: standard.h main.h parser.h
maindraw.o: /usr/include/string.h /usr/include/features.h
maindraw.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
maindraw.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
maindraw.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
maindraw.o: /usr/include/xlocale.h ../../../include/yalecad/file.h
maindraw.o: ../../../include/yalecad/base.h /usr/include/stdio.h
maindraw.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
maindraw.o: /usr/include/libio.h /usr/include/_G_config.h
maindraw.o: /usr/include/wchar.h
maindraw.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
maindraw.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
maindraw.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
maindraw.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
maindraw.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
maindraw.o: /usr/include/sys/types.h /usr/include/time.h
maindraw.o: /usr/include/sys/select.h /usr/include/bits/select.h
maindraw.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
maindraw.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
maindraw.o: /usr/include/alloca.h /usr/include/math.h
maindraw.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
maindraw.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
maindraw.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
maindraw.o: /usr/include/bits/mathcalls.h
maindraw.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
maindraw.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
maindraw.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
maindraw.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
maindraw.o: /usr/include/bits/posix2_lim.h
maindraw.o: ../../../include/yalecad/okmalloc.h
maindraw.o: ../../../include/yalecad/message.h
maindraw.o: ../../../include/yalecad/debug.h ../../../include/yalecad/draw.h
maindraw.o: ../../../include/yalecad/colors.h
maindraw.o: ../../../include/yalecad/dialog.h
maindraw.o: ../../../include/yalecad/rbtree.h standard.h ./menus.h ./dialog.h
maindraw.o: ./dialogpart.h
mergetile.o: /usr/include/string.h /usr/include/features.h
mergetile.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
mergetile.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
mergetile.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
mergetile.o: /usr/include/xlocale.h ../../../include/yalecad/base.h
mergetile.o: /usr/include/stdio.h /usr/include/bits/types.h
mergetile.o: /usr/include/bits/typesizes.h /usr/include/libio.h
mergetile.o: /usr/include/_G_config.h /usr/include/wchar.h
mergetile.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
mergetile.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
mergetile.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
mergetile.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
mergetile.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
mergetile.o: /usr/include/sys/types.h /usr/include/time.h
mergetile.o: /usr/include/sys/select.h /usr/include/bits/select.h
mergetile.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
mergetile.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
mergetile.o: /usr/include/alloca.h /usr/include/math.h
mergetile.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
mergetile.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
mergetile.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
mergetile.o: /usr/include/bits/mathcalls.h
mergetile.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
mergetile.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
mergetile.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
mergetile.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
mergetile.o: /usr/include/bits/posix2_lim.h
mergetile.o: ../../../include/yalecad/okmalloc.h
mergetile.o: ../../../include/yalecad/rbtree.h
mergetile.o: ../../../include/yalecad/file.h
mergetile.o: ../../../include/yalecad/string.h
mergetile.o: ../../../include/yalecad/message.h standard.h parser.h
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
newtemp.o: ../../../include/yalecad/debug.h
newtemp.o: ../../../include/yalecad/message.h
output.o: /usr/include/string.h /usr/include/features.h
output.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
output.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
output.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
output.o: /usr/include/xlocale.h standard.h ../../../include/yalecad/base.h
output.o: /usr/include/stdio.h /usr/include/bits/types.h
output.o: /usr/include/bits/typesizes.h /usr/include/libio.h
output.o: /usr/include/_G_config.h /usr/include/wchar.h
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
output.o: parser.h ../../../include/yalecad/string.h
output.o: ../../../include/yalecad/file.h ../../../include/yalecad/rbtree.h
output.o: ../../../include/yalecad/message.h
output.o: ../../../include/yalecad/colors.h ../../../include/yalecad/draw.h
output.o: ../../../include/yalecad/yreadpar.h
paint.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
paint.o: /usr/include/features.h /usr/include/sys/cdefs.h
paint.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
paint.o: /usr/include/gnu/stubs-64.h
paint.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
paint.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
paint.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
paint.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
paint.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
paint.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
paint.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
paint.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
paint.o: /usr/include/sys/types.h /usr/include/time.h
paint.o: /usr/include/sys/select.h /usr/include/bits/select.h
paint.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
paint.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
paint.o: /usr/include/alloca.h /usr/include/math.h
paint.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
paint.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
paint.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
paint.o: /usr/include/bits/mathcalls.h
paint.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
paint.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
paint.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
paint.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
paint.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
paint.o: parser.h ../../../include/yalecad/string.h
paint.o: ../../../include/yalecad/message.h ../../../include/yalecad/draw.h
paint.o: ../../../include/yalecad/dialog.h ../../../include/yalecad/colors.h
partition.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
partition.o: /usr/include/features.h /usr/include/sys/cdefs.h
partition.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
partition.o: /usr/include/gnu/stubs-64.h
partition.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
partition.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
partition.o: /usr/include/libio.h /usr/include/_G_config.h
partition.o: /usr/include/wchar.h
partition.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
partition.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
partition.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
partition.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
partition.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
partition.o: /usr/include/sys/types.h /usr/include/time.h
partition.o: /usr/include/sys/select.h /usr/include/bits/select.h
partition.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
partition.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
partition.o: /usr/include/alloca.h /usr/include/math.h
partition.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
partition.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
partition.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
partition.o: /usr/include/bits/mathcalls.h
partition.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
partition.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
partition.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
partition.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
partition.o: /usr/include/bits/posix2_lim.h
partition.o: ../../../include/yalecad/okmalloc.h parser.h
partition.o: ../../../include/yalecad/string.h
partition.o: ../../../include/yalecad/message.h
partition.o: ../../../include/yalecad/draw.h
partition.o: ../../../include/yalecad/dialog.h
partition.o: ../../../include/yalecad/debug.h
partition.o: ../../../include/yalecad/rbtree.h
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
paths.o: main.h ../../../include/yalecad/debug.h
paths.o: ../../../include/yalecad/message.h readnets.h
paths.o: ../../../include/yalecad/stat.h ../../../include/yalecad/file.h
readcell.o: /usr/include/string.h /usr/include/features.h
readcell.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
readcell.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
readcell.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
readcell.o: /usr/include/xlocale.h ../../../include/yalecad/message.h
readcell.o: ../../../include/yalecad/base.h /usr/include/stdio.h
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
readcell.o: ../../../include/yalecad/string.h
readcell.o: ../../../include/yalecad/debug.h standard.h readcell.h parser.h
readcell.o: readcell_l.h
readmver.o: /usr/include/string.h /usr/include/features.h
readmver.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
readmver.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
readmver.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
readmver.o: /usr/include/xlocale.h ../../../include/yalecad/message.h
readmver.o: ../../../include/yalecad/base.h /usr/include/stdio.h
readmver.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
readmver.o: /usr/include/libio.h /usr/include/_G_config.h
readmver.o: /usr/include/wchar.h
readmver.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
readmver.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
readmver.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
readmver.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
readmver.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
readmver.o: /usr/include/sys/types.h /usr/include/time.h
readmver.o: /usr/include/sys/select.h /usr/include/bits/select.h
readmver.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
readmver.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
readmver.o: /usr/include/alloca.h /usr/include/math.h
readmver.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
readmver.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
readmver.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
readmver.o: /usr/include/bits/mathcalls.h
readmver.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
readmver.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
readmver.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
readmver.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
readmver.o: /usr/include/bits/posix2_lim.h
readmver.o: ../../../include/yalecad/okmalloc.h
readmver.o: ../../../include/yalecad/string.h readmver.h parser.h
readmver.o: readmver_l.h
readnets.o: /usr/include/string.h /usr/include/features.h
readnets.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
readnets.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
readnets.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
readnets.o: /usr/include/xlocale.h ../../../include/yalecad/message.h
readnets.o: ../../../include/yalecad/base.h /usr/include/stdio.h
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
readnets.o: ../../../include/yalecad/debug.h
readnets.o: ../../../include/yalecad/string.h ../../../include/yalecad/hash.h
readnets.o: readnets.h standard.h readnets_l.h
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
readpar.o: main.h parser.h ../../../include/yalecad/file.h
readpar.o: ../../../include/yalecad/yreadpar.h
readpar.o: ../../../include/yalecad/rbtree.h
readpar.o: ../../../include/yalecad/message.h
set_limits.o: /usr/include/math.h /usr/include/features.h
set_limits.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
set_limits.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
set_limits.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
set_limits.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
set_limits.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
set_limits.o: /usr/include/bits/mathcalls.h standard.h
set_limits.o: ../../../include/yalecad/base.h /usr/include/stdio.h
set_limits.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
set_limits.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
set_limits.o: /usr/include/libio.h /usr/include/_G_config.h
set_limits.o: /usr/include/wchar.h
set_limits.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
set_limits.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
set_limits.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
set_limits.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
set_limits.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
set_limits.o: /usr/include/sys/types.h /usr/include/time.h
set_limits.o: /usr/include/sys/select.h /usr/include/bits/select.h
set_limits.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
set_limits.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
set_limits.o: /usr/include/alloca.h
set_limits.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
set_limits.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
set_limits.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
set_limits.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
set_limits.o: /usr/include/bits/posix2_lim.h
set_limits.o: ../../../include/yalecad/okmalloc.h parser.h
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
tilecost.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
tilecost.o: /usr/include/features.h /usr/include/sys/cdefs.h
tilecost.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
tilecost.o: /usr/include/gnu/stubs-64.h
tilecost.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
tilecost.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
tilecost.o: /usr/include/libio.h /usr/include/_G_config.h
tilecost.o: /usr/include/wchar.h
tilecost.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
tilecost.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
tilecost.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
tilecost.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
tilecost.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
tilecost.o: /usr/include/sys/types.h /usr/include/time.h
tilecost.o: /usr/include/sys/select.h /usr/include/bits/select.h
tilecost.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
tilecost.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
tilecost.o: /usr/include/alloca.h /usr/include/math.h
tilecost.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
tilecost.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
tilecost.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
tilecost.o: /usr/include/bits/mathcalls.h
tilecost.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
tilecost.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
tilecost.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
tilecost.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
tilecost.o: /usr/include/bits/posix2_lim.h
tilecost.o: ../../../include/yalecad/okmalloc.h
tilecost.o: ../../../include/yalecad/debug.h
tilecost.o: ../../../include/yalecad/message.h
tilepenal.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
tilepenal.o: /usr/include/features.h /usr/include/sys/cdefs.h
tilepenal.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
tilepenal.o: /usr/include/gnu/stubs-64.h
tilepenal.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
tilepenal.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
tilepenal.o: /usr/include/libio.h /usr/include/_G_config.h
tilepenal.o: /usr/include/wchar.h
tilepenal.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
tilepenal.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
tilepenal.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
tilepenal.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
tilepenal.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
tilepenal.o: /usr/include/sys/types.h /usr/include/time.h
tilepenal.o: /usr/include/sys/select.h /usr/include/bits/select.h
tilepenal.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
tilepenal.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
tilepenal.o: /usr/include/alloca.h /usr/include/math.h
tilepenal.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
tilepenal.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
tilepenal.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
tilepenal.o: /usr/include/bits/mathcalls.h
tilepenal.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
tilepenal.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
tilepenal.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
tilepenal.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
tilepenal.o: /usr/include/bits/posix2_lim.h
tilepenal.o: ../../../include/yalecad/okmalloc.h parser.h
ucxx1.o: ../../../include/yalecad/debug.h ../../../include/yalecad/message.h
ucxx1.o: ../../../include/yalecad/base.h /usr/include/stdio.h
ucxx1.o: /usr/include/features.h /usr/include/sys/cdefs.h
ucxx1.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
ucxx1.o: /usr/include/gnu/stubs-64.h
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
ucxx1.o: standard.h main.h
ucxx2.o: ../../../include/yalecad/debug.h ../../../include/yalecad/message.h
ucxx2.o: ../../../include/yalecad/base.h /usr/include/stdio.h
ucxx2.o: /usr/include/features.h /usr/include/sys/cdefs.h
ucxx2.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
ucxx2.o: /usr/include/gnu/stubs-64.h
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
ucxx2.o: standard.h main.h
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
uloop.o: main.h
ulp_end.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
ulp_end.o: /usr/include/features.h /usr/include/sys/cdefs.h
ulp_end.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
ulp_end.o: /usr/include/gnu/stubs-64.h
ulp_end.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
ulp_end.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
ulp_end.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
ulp_end.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
ulp_end.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
ulp_end.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
ulp_end.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
ulp_end.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
ulp_end.o: /usr/include/sys/types.h /usr/include/time.h
ulp_end.o: /usr/include/sys/select.h /usr/include/bits/select.h
ulp_end.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
ulp_end.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
ulp_end.o: /usr/include/alloca.h /usr/include/math.h
ulp_end.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
ulp_end.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
ulp_end.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
ulp_end.o: /usr/include/bits/mathcalls.h
ulp_end.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
ulp_end.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
ulp_end.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
ulp_end.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
ulp_end.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
ulp_util.o: standard.h ../../../include/yalecad/base.h /usr/include/stdio.h
ulp_util.o: /usr/include/features.h /usr/include/sys/cdefs.h
ulp_util.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
ulp_util.o: /usr/include/gnu/stubs-64.h
ulp_util.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
ulp_util.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
ulp_util.o: /usr/include/libio.h /usr/include/_G_config.h
ulp_util.o: /usr/include/wchar.h
ulp_util.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
ulp_util.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
ulp_util.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
ulp_util.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
ulp_util.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
ulp_util.o: /usr/include/sys/types.h /usr/include/time.h
ulp_util.o: /usr/include/sys/select.h /usr/include/bits/select.h
ulp_util.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
ulp_util.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
ulp_util.o: /usr/include/alloca.h /usr/include/math.h
ulp_util.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
ulp_util.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
ulp_util.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
ulp_util.o: /usr/include/bits/mathcalls.h
ulp_util.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
ulp_util.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
ulp_util.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
ulp_util.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
ulp_util.o: /usr/include/bits/posix2_lim.h
ulp_util.o: ../../../include/yalecad/okmalloc.h main.h
utemp.o: ../../../include/yalecad/message.h ../../../include/yalecad/base.h
utemp.o: /usr/include/stdio.h /usr/include/features.h
utemp.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
utemp.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
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
utemp.o: standard.h main.h
