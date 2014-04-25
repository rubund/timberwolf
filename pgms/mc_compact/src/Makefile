# Ymakefile for program mc_compact
#  "@(#) Ymakefile (Yale) version 7.5 2/23/91 " 
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
PNAME=mc_compact

#where the object code is located
objdir=../obj
O=${objdir}/

SRC= \
	cdraw.c \
	cmain.c \
	changraph.c \
	compactor.c \
	debug2.c \
	grid.c \
	io.c \
	movestrat.c \
	movestrat2.c \
	multi.c \
	readtiles.c \
	stdmacro.c \
	xcompact.c \
	readcgraph.c \
	ycompact.c

OBJ= \
	${O}cdraw.o \
	${O}changraph.o \
	${O}cmain.o \
	${O}compactor.o \
	${O}debug2.o \
	${O}grid.o \
	${O}io.o \
	${O}movestrat.o \
	${O}movestrat2.o \
	${O}multi.o \
	${O}readtiles.o \
	${O}stdmacro.o \
	${O}xcompact.o \
	${O}ycompact.o \
	${O}readcgraph.o 

INS= \
	compact.h \
	menus.h \
	readcgraph.h

info:   ; 
	-@${ECHO} "make ${DEST}${PNAME} - usage:" 
	-@${ECHO} "   make install - build program" 
	-@${ECHO} "   make install_non_yale - build program at foreign host" 
	-@${ECHO} "   make clean - remove binary" 
	-@${ECHO} "   make depend - added makefile dependencies" 
	-@${ECHO} "   make sources - pull sources from SCCS" 
	-@${ECHO} "   make lint - run lint on the sources" 


# how to make mc_compact program
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

# how to make mc_compact lint
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
${O}cdraw.o:cdraw.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  cdraw.c
	${MV} cdraw.o ${O}cdraw.o
${O}cmain.o:cmain.c
	${CC} ${CLEANUP} ${CFLAGS} ${IDIR} ${OPTIONS} -c  cmain.c
	${MV} cmain.o ${O}cmain.o
${O}compactor.o:compactor.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  compactor.c
	${MV} compactor.o ${O}compactor.o
${O}changraph.o:changraph.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  changraph.c
	${MV} changraph.o ${O}changraph.o
${O}debug2.o:debug2.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  debug2.c
	${MV} debug2.o ${O}debug2.o
${O}grid.o:grid.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  grid.c
	${MV} grid.o ${O}grid.o
${O}io.o:io.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  io.c
	${MV} io.o ${O}io.o
${O}movestrat.o:movestrat.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  movestrat.c
	${MV} movestrat.o ${O}movestrat.o
${O}movestrat2.o:movestrat2.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  movestrat2.c
	${MV} movestrat2.o ${O}movestrat2.o
${O}multi.o:multi.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  multi.c
	${MV} multi.o ${O}multi.o
${O}readtiles.o:readtiles.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  readtiles.c
	${MV} readtiles.o ${O}readtiles.o
${O}stdmacro.o:stdmacro.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  stdmacro.c
	${MV} stdmacro.o ${O}stdmacro.o
${O}xcompact.o:xcompact.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  xcompact.c
	${MV} xcompact.o ${O}xcompact.o
${O}ycompact.o:ycompact.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  ycompact.c
	${MV} ycompact.o ${O}ycompact.o
${O}readcgraph.o:readcgraph.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  readcgraph.c
	${MV} readcgraph.o ${O}readcgraph.o

# end makefile
# DO NOT DELETE

cdraw.o: ../../../include/yalecad/base.h /usr/include/stdio.h
cdraw.o: /usr/include/features.h /usr/include/sys/cdefs.h
cdraw.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
cdraw.o: /usr/include/gnu/stubs-64.h
cdraw.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
cdraw.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
cdraw.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
cdraw.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
cdraw.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
cdraw.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
cdraw.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
cdraw.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
cdraw.o: /usr/include/sys/types.h /usr/include/time.h
cdraw.o: /usr/include/sys/select.h /usr/include/bits/select.h
cdraw.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
cdraw.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
cdraw.o: /usr/include/alloca.h /usr/include/math.h
cdraw.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
cdraw.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
cdraw.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
cdraw.o: /usr/include/bits/mathcalls.h
cdraw.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
cdraw.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
cdraw.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
cdraw.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
cdraw.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
cdraw.o: ../../../include/yalecad/message.h ../../../include/yalecad/draw.h
cdraw.o: ../../../include/yalecad/colors.h ../../../include/yalecad/debug.h
cdraw.o: ./compact.h ../../../include/yalecad/set.h
cdraw.o: ../../../include/yalecad/rbtree.h ../../../include/yalecad/deck.h
cdraw.o: ./menus.h
cmain.o: /usr/include/stdio.h /usr/include/features.h
cmain.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
cmain.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
cmain.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
cmain.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
cmain.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
cmain.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
cmain.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
cmain.o: /usr/include/signal.h /usr/include/bits/sigset.h
cmain.o: /usr/include/bits/signum.h /usr/include/time.h
cmain.o: /usr/include/bits/siginfo.h /usr/include/bits/sigaction.h
cmain.o: /usr/include/bits/sigcontext.h /usr/include/bits/sigstack.h
cmain.o: /usr/include/sys/ucontext.h /usr/include/bits/pthreadtypes.h
cmain.o: /usr/include/bits/sigthread.h ../../../include/yalecad/cleanup.h
cmain.o: ../../../include/yalecad/message.h ../../../include/yalecad/base.h
cmain.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
cmain.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
cmain.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
cmain.o: /usr/include/sys/types.h /usr/include/sys/select.h
cmain.o: /usr/include/bits/select.h /usr/include/bits/time.h
cmain.o: /usr/include/sys/sysmacros.h /usr/include/alloca.h
cmain.o: /usr/include/math.h /usr/include/bits/huge_val.h
cmain.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
cmain.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
cmain.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
cmain.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
cmain.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
cmain.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
cmain.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
cmain.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
cmain.o: ../../../include/yalecad/program.h ../../../include/yalecad/string.h
cmain.o: ../../../include/yalecad/debug.h ./compact.h
cmain.o: ../../../include/yalecad/set.h ../../../include/yalecad/rbtree.h
cmain.o: ../../../include/yalecad/deck.h
changraph.o: /usr/include/stdio.h /usr/include/features.h
changraph.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
changraph.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
changraph.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
changraph.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
changraph.o: /usr/include/libio.h /usr/include/_G_config.h
changraph.o: /usr/include/wchar.h
changraph.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
changraph.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
changraph.o: ../../../include/yalecad/message.h
changraph.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
changraph.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
changraph.o: /usr/include/endian.h /usr/include/bits/endian.h
changraph.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
changraph.o: /usr/include/time.h /usr/include/sys/select.h
changraph.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
changraph.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
changraph.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
changraph.o: /usr/include/math.h /usr/include/bits/huge_val.h
changraph.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
changraph.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
changraph.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
changraph.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
changraph.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
changraph.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
changraph.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
changraph.o: /usr/include/bits/posix2_lim.h
changraph.o: ../../../include/yalecad/okmalloc.h
changraph.o: ../../../include/yalecad/string.h
changraph.o: ../../../include/yalecad/debug.h
changraph.o: ../../../include/yalecad/rbtree.h ../../../include/yalecad/set.h
changraph.o: ./compact.h ../../../include/yalecad/deck.h
compactor.o: ./compact.h ../../../include/yalecad/base.h /usr/include/stdio.h
compactor.o: /usr/include/features.h /usr/include/sys/cdefs.h
compactor.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
compactor.o: /usr/include/gnu/stubs-64.h
compactor.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
compactor.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
compactor.o: /usr/include/libio.h /usr/include/_G_config.h
compactor.o: /usr/include/wchar.h
compactor.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
compactor.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
compactor.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
compactor.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
compactor.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
compactor.o: /usr/include/sys/types.h /usr/include/time.h
compactor.o: /usr/include/sys/select.h /usr/include/bits/select.h
compactor.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
compactor.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
compactor.o: /usr/include/alloca.h /usr/include/math.h
compactor.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
compactor.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
compactor.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
compactor.o: /usr/include/bits/mathcalls.h
compactor.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
compactor.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
compactor.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
compactor.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
compactor.o: /usr/include/bits/posix2_lim.h
compactor.o: ../../../include/yalecad/okmalloc.h
compactor.o: ../../../include/yalecad/message.h
compactor.o: ../../../include/yalecad/set.h ../../../include/yalecad/rbtree.h
compactor.o: ../../../include/yalecad/deck.h ../../../include/yalecad/debug.h
debug2.o: ./compact.h ../../../include/yalecad/base.h /usr/include/stdio.h
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
debug2.o: ../../../include/yalecad/message.h ../../../include/yalecad/set.h
debug2.o: ../../../include/yalecad/rbtree.h ../../../include/yalecad/deck.h
debug2.o: ../../../include/yalecad/debug.h ../../../include/yalecad/file.h
grid.o: ./compact.h ../../../include/yalecad/base.h /usr/include/stdio.h
grid.o: /usr/include/features.h /usr/include/sys/cdefs.h
grid.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
grid.o: /usr/include/gnu/stubs-64.h
grid.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
grid.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
grid.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
grid.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
grid.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
grid.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
grid.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
grid.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
grid.o: /usr/include/sys/types.h /usr/include/time.h
grid.o: /usr/include/sys/select.h /usr/include/bits/select.h
grid.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
grid.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
grid.o: /usr/include/alloca.h /usr/include/math.h
grid.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
grid.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
grid.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
grid.o: /usr/include/bits/mathcalls.h
grid.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
grid.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
grid.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
grid.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
grid.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
grid.o: ../../../include/yalecad/message.h ../../../include/yalecad/set.h
grid.o: ../../../include/yalecad/rbtree.h ../../../include/yalecad/deck.h
grid.o: ../../../include/yalecad/debug.h
io.o: ./compact.h ../../../include/yalecad/base.h /usr/include/stdio.h
io.o: /usr/include/features.h /usr/include/sys/cdefs.h
io.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
io.o: /usr/include/gnu/stubs-64.h
io.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
io.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
io.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
io.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
io.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
io.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
io.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
io.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
io.o: /usr/include/sys/types.h /usr/include/time.h /usr/include/sys/select.h
io.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
io.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
io.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
io.o: /usr/include/math.h /usr/include/bits/huge_val.h
io.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
io.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
io.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
io.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
io.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
io.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
io.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
io.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
io.o: ../../../include/yalecad/message.h ../../../include/yalecad/set.h
io.o: ../../../include/yalecad/rbtree.h ../../../include/yalecad/deck.h
io.o: ../../../include/yalecad/debug.h ../../../include/yalecad/file.h
movestrat.o: ./compact.h ../../../include/yalecad/base.h /usr/include/stdio.h
movestrat.o: /usr/include/features.h /usr/include/sys/cdefs.h
movestrat.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
movestrat.o: /usr/include/gnu/stubs-64.h
movestrat.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
movestrat.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
movestrat.o: /usr/include/libio.h /usr/include/_G_config.h
movestrat.o: /usr/include/wchar.h
movestrat.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
movestrat.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
movestrat.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
movestrat.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
movestrat.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
movestrat.o: /usr/include/sys/types.h /usr/include/time.h
movestrat.o: /usr/include/sys/select.h /usr/include/bits/select.h
movestrat.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
movestrat.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
movestrat.o: /usr/include/alloca.h /usr/include/math.h
movestrat.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
movestrat.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
movestrat.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
movestrat.o: /usr/include/bits/mathcalls.h
movestrat.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
movestrat.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
movestrat.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
movestrat.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
movestrat.o: /usr/include/bits/posix2_lim.h
movestrat.o: ../../../include/yalecad/okmalloc.h
movestrat.o: ../../../include/yalecad/message.h
movestrat.o: ../../../include/yalecad/set.h ../../../include/yalecad/rbtree.h
movestrat.o: ../../../include/yalecad/deck.h ../../../include/yalecad/debug.h
movestrat2.o: ./compact.h ../../../include/yalecad/base.h
movestrat2.o: /usr/include/stdio.h /usr/include/features.h
movestrat2.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
movestrat2.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
movestrat2.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
movestrat2.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
movestrat2.o: /usr/include/libio.h /usr/include/_G_config.h
movestrat2.o: /usr/include/wchar.h
movestrat2.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
movestrat2.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
movestrat2.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
movestrat2.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
movestrat2.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
movestrat2.o: /usr/include/sys/types.h /usr/include/time.h
movestrat2.o: /usr/include/sys/select.h /usr/include/bits/select.h
movestrat2.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
movestrat2.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
movestrat2.o: /usr/include/alloca.h /usr/include/math.h
movestrat2.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
movestrat2.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
movestrat2.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
movestrat2.o: /usr/include/bits/mathcalls.h
movestrat2.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
movestrat2.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
movestrat2.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
movestrat2.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
movestrat2.o: /usr/include/bits/posix2_lim.h
movestrat2.o: ../../../include/yalecad/okmalloc.h
movestrat2.o: ../../../include/yalecad/message.h
movestrat2.o: ../../../include/yalecad/set.h
movestrat2.o: ../../../include/yalecad/rbtree.h
movestrat2.o: ../../../include/yalecad/deck.h
movestrat2.o: ../../../include/yalecad/debug.h
multi.o: ./compact.h ../../../include/yalecad/base.h /usr/include/stdio.h
multi.o: /usr/include/features.h /usr/include/sys/cdefs.h
multi.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
multi.o: /usr/include/gnu/stubs-64.h
multi.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
multi.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
multi.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
multi.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
multi.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
multi.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
multi.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
multi.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
multi.o: /usr/include/sys/types.h /usr/include/time.h
multi.o: /usr/include/sys/select.h /usr/include/bits/select.h
multi.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
multi.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
multi.o: /usr/include/alloca.h /usr/include/math.h
multi.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
multi.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
multi.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
multi.o: /usr/include/bits/mathcalls.h
multi.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
multi.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
multi.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
multi.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
multi.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
multi.o: ../../../include/yalecad/message.h ../../../include/yalecad/set.h
multi.o: ../../../include/yalecad/rbtree.h ../../../include/yalecad/deck.h
multi.o: ../../../include/yalecad/debug.h
readtiles.o: /usr/include/string.h /usr/include/features.h
readtiles.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
readtiles.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
readtiles.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
readtiles.o: /usr/include/xlocale.h ./compact.h
readtiles.o: ../../../include/yalecad/base.h /usr/include/stdio.h
readtiles.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
readtiles.o: /usr/include/libio.h /usr/include/_G_config.h
readtiles.o: /usr/include/wchar.h
readtiles.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
readtiles.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
readtiles.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
readtiles.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
readtiles.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
readtiles.o: /usr/include/sys/types.h /usr/include/time.h
readtiles.o: /usr/include/sys/select.h /usr/include/bits/select.h
readtiles.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
readtiles.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
readtiles.o: /usr/include/alloca.h /usr/include/math.h
readtiles.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
readtiles.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
readtiles.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
readtiles.o: /usr/include/bits/mathcalls.h
readtiles.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
readtiles.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
readtiles.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
readtiles.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
readtiles.o: /usr/include/bits/posix2_lim.h
readtiles.o: ../../../include/yalecad/okmalloc.h
readtiles.o: ../../../include/yalecad/message.h
readtiles.o: ../../../include/yalecad/set.h ../../../include/yalecad/rbtree.h
readtiles.o: ../../../include/yalecad/deck.h ../../../include/yalecad/file.h
readtiles.o: ../../../include/yalecad/debug.h readtiles_l.h
readtiles.o: ../../../include/yalecad/string.h
stdmacro.o: ./compact.h ../../../include/yalecad/base.h /usr/include/stdio.h
stdmacro.o: /usr/include/features.h /usr/include/sys/cdefs.h
stdmacro.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
stdmacro.o: /usr/include/gnu/stubs-64.h
stdmacro.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
stdmacro.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
stdmacro.o: /usr/include/libio.h /usr/include/_G_config.h
stdmacro.o: /usr/include/wchar.h
stdmacro.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
stdmacro.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
stdmacro.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
stdmacro.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
stdmacro.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
stdmacro.o: /usr/include/sys/types.h /usr/include/time.h
stdmacro.o: /usr/include/sys/select.h /usr/include/bits/select.h
stdmacro.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
stdmacro.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
stdmacro.o: /usr/include/alloca.h /usr/include/math.h
stdmacro.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
stdmacro.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
stdmacro.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
stdmacro.o: /usr/include/bits/mathcalls.h
stdmacro.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
stdmacro.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
stdmacro.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
stdmacro.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
stdmacro.o: /usr/include/bits/posix2_lim.h
stdmacro.o: ../../../include/yalecad/okmalloc.h
stdmacro.o: ../../../include/yalecad/message.h ../../../include/yalecad/set.h
stdmacro.o: ../../../include/yalecad/rbtree.h ../../../include/yalecad/deck.h
stdmacro.o: ../../../include/yalecad/debug.h
xcompact.o: ./compact.h ../../../include/yalecad/base.h /usr/include/stdio.h
xcompact.o: /usr/include/features.h /usr/include/sys/cdefs.h
xcompact.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
xcompact.o: /usr/include/gnu/stubs-64.h
xcompact.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
xcompact.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
xcompact.o: /usr/include/libio.h /usr/include/_G_config.h
xcompact.o: /usr/include/wchar.h
xcompact.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
xcompact.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
xcompact.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
xcompact.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
xcompact.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
xcompact.o: /usr/include/sys/types.h /usr/include/time.h
xcompact.o: /usr/include/sys/select.h /usr/include/bits/select.h
xcompact.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
xcompact.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
xcompact.o: /usr/include/alloca.h /usr/include/math.h
xcompact.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
xcompact.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
xcompact.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
xcompact.o: /usr/include/bits/mathcalls.h
xcompact.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
xcompact.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
xcompact.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
xcompact.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
xcompact.o: /usr/include/bits/posix2_lim.h
xcompact.o: ../../../include/yalecad/okmalloc.h
xcompact.o: ../../../include/yalecad/message.h ../../../include/yalecad/set.h
xcompact.o: ../../../include/yalecad/rbtree.h ../../../include/yalecad/deck.h
xcompact.o: ../../../include/yalecad/debug.h
readcgraph.o: /usr/include/string.h /usr/include/features.h
readcgraph.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
readcgraph.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
readcgraph.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
readcgraph.o: /usr/include/xlocale.h ./compact.h
readcgraph.o: ../../../include/yalecad/base.h /usr/include/stdio.h
readcgraph.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
readcgraph.o: /usr/include/libio.h /usr/include/_G_config.h
readcgraph.o: /usr/include/wchar.h
readcgraph.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
readcgraph.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
readcgraph.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
readcgraph.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
readcgraph.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
readcgraph.o: /usr/include/sys/types.h /usr/include/time.h
readcgraph.o: /usr/include/sys/select.h /usr/include/bits/select.h
readcgraph.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
readcgraph.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
readcgraph.o: /usr/include/alloca.h /usr/include/math.h
readcgraph.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
readcgraph.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
readcgraph.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
readcgraph.o: /usr/include/bits/mathcalls.h
readcgraph.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
readcgraph.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
readcgraph.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
readcgraph.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
readcgraph.o: /usr/include/bits/posix2_lim.h
readcgraph.o: ../../../include/yalecad/okmalloc.h
readcgraph.o: ../../../include/yalecad/message.h
readcgraph.o: ../../../include/yalecad/set.h
readcgraph.o: ../../../include/yalecad/rbtree.h
readcgraph.o: ../../../include/yalecad/deck.h ./readcgraph.h
readcgraph.o: ../../../include/yalecad/debug.h
readcgraph.o: ../../../include/yalecad/file.h readcgraph_l.h
readcgraph.o: ../../../include/yalecad/string.h
ycompact.o: ./compact.h ../../../include/yalecad/base.h /usr/include/stdio.h
ycompact.o: /usr/include/features.h /usr/include/sys/cdefs.h
ycompact.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
ycompact.o: /usr/include/gnu/stubs-64.h
ycompact.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
ycompact.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
ycompact.o: /usr/include/libio.h /usr/include/_G_config.h
ycompact.o: /usr/include/wchar.h
ycompact.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
ycompact.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
ycompact.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
ycompact.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
ycompact.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
ycompact.o: /usr/include/sys/types.h /usr/include/time.h
ycompact.o: /usr/include/sys/select.h /usr/include/bits/select.h
ycompact.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
ycompact.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
ycompact.o: /usr/include/alloca.h /usr/include/math.h
ycompact.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
ycompact.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
ycompact.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
ycompact.o: /usr/include/bits/mathcalls.h
ycompact.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
ycompact.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
ycompact.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
ycompact.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
ycompact.o: /usr/include/bits/posix2_lim.h
ycompact.o: ../../../include/yalecad/okmalloc.h
ycompact.o: ../../../include/yalecad/message.h ../../../include/yalecad/set.h
ycompact.o: ../../../include/yalecad/rbtree.h ../../../include/yalecad/deck.h
ycompact.o: ../../../include/yalecad/debug.h
