# Ymakefile for program gengraph
#  "@(#) Ymakefile (Yale) version 1.7 5/1/91 " 
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
PNAME=gengraph
MENU=gengraph_menu

#where the object code is located
objdir=../obj
O=${objdir}/

SRC= \
	23tree.c \
	changraph.c \
	dens.c \
	findnodes.c \
	fulllink.c \
	gentwf.c \
	gmain.c \
	graphics.c \
	hprobes.c \
	makelink.c \
	polar.c \
	printgph.c \
	readgeo.c \
	rectlin.c \
	reduceg.c \
	vprobes.c \
	xgraph.c \
	ygraph.c 

OBJ= \
	${O}23tree.o \
	${O}changraph.o \
	${O}dens.o \
	${O}findnodes.o \
	${O}fulllink.o \
	${O}gentwf.o \
	${O}gmain.o \
	${O}graphics.o \
	${O}hprobes.o \
	${O}makelink.o \
	${O}polar.o \
	${O}printgph.o \
	${O}readgeo.o \
	${O}rectlin.o \
	${O}reduceg.o \
	${O}vprobes.o \
	${O}xgraph.o \
	${O}ygraph.o 

INS= \
	23tree.h \
	dens.h \
	menus.h \
	geo.h 

info:   ; 
	-@${ECHO} "make ${DEST}${PNAME} - usage:" 
	-@${ECHO} "   make install - build program" 
	-@${ECHO} "   make install_non_yale - build program at foreign host" 
	-@${ECHO} "   make clean - remove binary" 
	-@${ECHO} "   make depend - added makefile dependencies" 
	-@${ECHO} "   make sources - pull sources from SCCS" 


# how to make gengraph program
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

lint:  
	${LINT} ${LINT_OPT} ${OPTIONS} ${IDIR} ${SRC}

clean: ;
	${RM} ${O}* *~ core *.bak

# how to build makefile dependencies
depend : ;
	${MAKEDEPEND} ${CFLAGS} ${OPTIONS} ${IDIR} ${SRC}

#default sccs operation is get
SCCS_OP=get
#current release
REL=

# how to get sources from sccs
sources : ${SRC} ${INS} ${YMAKEFILE} ${MENU}
${SRC} ${INS} ${YMAKEFILE} ${MENU}: 
	${SCCS} ${SCCS_OP} ${REL} $@

#BEGIN DEPENDENCIES -- DO NOT DELETE THIS LINE

#END DEPENDENCIES -- DO NOT DELETE THIS LINE


# How to compile the sources
${O}23tree.o:23tree.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  23tree.c
	${MV} 23tree.o ${O}23tree.o
${O}changraph.o:changraph.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  changraph.c
	${MV} changraph.o ${O}changraph.o
${O}dens.o:dens.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  dens.c
	${MV} dens.o ${O}dens.o
${O}findnodes.o:findnodes.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  findnodes.c
	${MV} findnodes.o ${O}findnodes.o
${O}fulllink.o:fulllink.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  fulllink.c
	${MV} fulllink.o ${O}fulllink.o
${O}gentwf.o:gentwf.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  gentwf.c
	${MV} gentwf.o ${O}gentwf.o
${O}gmain.o:gmain.c
	${CC} ${CFLAGS} ${CLEANUP} ${IDIR} ${OPTIONS} -c  gmain.c
	${MV} gmain.o ${O}gmain.o
${O}graphics.o:graphics.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  graphics.c
	${MV} graphics.o ${O}graphics.o
${O}hprobes.o:hprobes.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  hprobes.c
	${MV} hprobes.o ${O}hprobes.o
${O}makelink.o:makelink.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  makelink.c
	${MV} makelink.o ${O}makelink.o
${O}polar.o:polar.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  polar.c
	${MV} polar.o ${O}polar.o
${O}printgph.o:printgph.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  printgph.c
	${MV} printgph.o ${O}printgph.o
${O}readgeo.o:readgeo.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  readgeo.c
	${MV} readgeo.o ${O}readgeo.o
${O}rectlin.o:rectlin.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  rectlin.c
	${MV} rectlin.o ${O}rectlin.o
${O}reduceg.o:reduceg.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  reduceg.c
	${MV} reduceg.o ${O}reduceg.o
${O}vprobes.o:vprobes.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  vprobes.c
	${MV} vprobes.o ${O}vprobes.o
${O}xgraph.o:xgraph.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  xgraph.c
	${MV} xgraph.o ${O}xgraph.o
${O}ygraph.o:ygraph.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  ygraph.c
	${MV} ygraph.o ${O}ygraph.o

# end makefile
# DO NOT DELETE

23tree.o: ./23tree.h /usr/include/stdio.h /usr/include/features.h
23tree.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
23tree.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
23tree.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
23tree.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
23tree.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
23tree.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
23tree.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
23tree.o: ../../../include/yalecad/debug.h ../../../include/yalecad/message.h
23tree.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
23tree.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
23tree.o: /usr/include/endian.h /usr/include/bits/endian.h
23tree.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
23tree.o: /usr/include/time.h /usr/include/sys/select.h
23tree.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
23tree.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
23tree.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
23tree.o: /usr/include/math.h /usr/include/bits/huge_val.h
23tree.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
23tree.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
23tree.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
23tree.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
23tree.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
23tree.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
23tree.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
23tree.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
changraph.o: ./geo.h /usr/include/stdio.h /usr/include/features.h
changraph.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
changraph.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
changraph.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
changraph.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
changraph.o: /usr/include/libio.h /usr/include/_G_config.h
changraph.o: /usr/include/wchar.h
changraph.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
changraph.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
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
changraph.o: ../../../include/yalecad/okmalloc.h ./23tree.h
changraph.o: ../../../include/yalecad/rbtree.h
changraph.o: ../../../include/yalecad/debug.h
changraph.o: ../../../include/yalecad/message.h
dens.o: /usr/include/string.h /usr/include/features.h
dens.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
dens.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
dens.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
dens.o: /usr/include/xlocale.h ../../../include/yalecad/base.h
dens.o: /usr/include/stdio.h /usr/include/bits/types.h
dens.o: /usr/include/bits/typesizes.h /usr/include/libio.h
dens.o: /usr/include/_G_config.h /usr/include/wchar.h
dens.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
dens.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
dens.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
dens.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
dens.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
dens.o: /usr/include/sys/types.h /usr/include/time.h
dens.o: /usr/include/sys/select.h /usr/include/bits/select.h
dens.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
dens.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
dens.o: /usr/include/alloca.h /usr/include/math.h
dens.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
dens.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
dens.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
dens.o: /usr/include/bits/mathcalls.h
dens.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
dens.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
dens.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
dens.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
dens.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
dens.o: ../../../include/yalecad/debug.h ../../../include/yalecad/message.h
dens.o: ../../../include/yalecad/file.h ../../../include/yalecad/string.h
dens.o: ./geo.h ./23tree.h ../../../include/yalecad/rbtree.h ./dens.h
dens.o: ../../../include/yalecad/yreadpar.h
findnodes.o: ./geo.h /usr/include/stdio.h /usr/include/features.h
findnodes.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
findnodes.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
findnodes.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
findnodes.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
findnodes.o: /usr/include/libio.h /usr/include/_G_config.h
findnodes.o: /usr/include/wchar.h
findnodes.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
findnodes.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
findnodes.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
findnodes.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
findnodes.o: /usr/include/endian.h /usr/include/bits/endian.h
findnodes.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
findnodes.o: /usr/include/time.h /usr/include/sys/select.h
findnodes.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
findnodes.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
findnodes.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
findnodes.o: /usr/include/math.h /usr/include/bits/huge_val.h
findnodes.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
findnodes.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
findnodes.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
findnodes.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
findnodes.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
findnodes.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
findnodes.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
findnodes.o: /usr/include/bits/posix2_lim.h
findnodes.o: ../../../include/yalecad/okmalloc.h ./23tree.h
findnodes.o: ../../../include/yalecad/rbtree.h
findnodes.o: ../../../include/yalecad/debug.h
findnodes.o: ../../../include/yalecad/message.h
fulllink.o: ./geo.h /usr/include/stdio.h /usr/include/features.h
fulllink.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
fulllink.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
fulllink.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
fulllink.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
fulllink.o: /usr/include/libio.h /usr/include/_G_config.h
fulllink.o: /usr/include/wchar.h
fulllink.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
fulllink.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
fulllink.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
fulllink.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
fulllink.o: /usr/include/endian.h /usr/include/bits/endian.h
fulllink.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
fulllink.o: /usr/include/time.h /usr/include/sys/select.h
fulllink.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
fulllink.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
fulllink.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
fulllink.o: /usr/include/math.h /usr/include/bits/huge_val.h
fulllink.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
fulllink.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
fulllink.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
fulllink.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
fulllink.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
fulllink.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
fulllink.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
fulllink.o: /usr/include/bits/posix2_lim.h
fulllink.o: ../../../include/yalecad/okmalloc.h ./23tree.h
fulllink.o: ../../../include/yalecad/rbtree.h
fulllink.o: ../../../include/yalecad/debug.h
fulllink.o: ../../../include/yalecad/message.h
gentwf.o: /usr/include/string.h /usr/include/features.h
gentwf.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
gentwf.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
gentwf.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
gentwf.o: /usr/include/xlocale.h ./geo.h /usr/include/stdio.h
gentwf.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
gentwf.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
gentwf.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
gentwf.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
gentwf.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
gentwf.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
gentwf.o: /usr/include/endian.h /usr/include/bits/endian.h
gentwf.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
gentwf.o: /usr/include/time.h /usr/include/sys/select.h
gentwf.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
gentwf.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
gentwf.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
gentwf.o: /usr/include/math.h /usr/include/bits/huge_val.h
gentwf.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
gentwf.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
gentwf.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
gentwf.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
gentwf.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
gentwf.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
gentwf.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
gentwf.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
gentwf.o: ./23tree.h ../../../include/yalecad/rbtree.h
gentwf.o: ../../../include/yalecad/debug.h ../../../include/yalecad/message.h
gentwf.o: ../../../include/yalecad/file.h ../../../include/yalecad/string.h
gmain.o: ./geo.h /usr/include/stdio.h /usr/include/features.h
gmain.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
gmain.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
gmain.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
gmain.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
gmain.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
gmain.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
gmain.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
gmain.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
gmain.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
gmain.o: /usr/include/endian.h /usr/include/bits/endian.h
gmain.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
gmain.o: /usr/include/time.h /usr/include/sys/select.h
gmain.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
gmain.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
gmain.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
gmain.o: /usr/include/math.h /usr/include/bits/huge_val.h
gmain.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
gmain.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
gmain.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
gmain.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
gmain.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
gmain.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
gmain.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
gmain.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
gmain.o: ./23tree.h ../../../include/yalecad/rbtree.h
gmain.o: ../../../include/yalecad/debug.h ../../../include/yalecad/message.h
gmain.o: ../../../include/yalecad/cleanup.h ../../../include/yalecad/file.h
gmain.o: ../../../include/yalecad/string.h
graphics.o: ./geo.h /usr/include/stdio.h /usr/include/features.h
graphics.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
graphics.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
graphics.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
graphics.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
graphics.o: /usr/include/libio.h /usr/include/_G_config.h
graphics.o: /usr/include/wchar.h
graphics.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
graphics.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
graphics.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
graphics.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
graphics.o: /usr/include/endian.h /usr/include/bits/endian.h
graphics.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
graphics.o: /usr/include/time.h /usr/include/sys/select.h
graphics.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
graphics.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
graphics.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
graphics.o: /usr/include/math.h /usr/include/bits/huge_val.h
graphics.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
graphics.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
graphics.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
graphics.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
graphics.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
graphics.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
graphics.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
graphics.o: /usr/include/bits/posix2_lim.h
graphics.o: ../../../include/yalecad/okmalloc.h ./23tree.h
graphics.o: ../../../include/yalecad/rbtree.h ./dens.h
graphics.o: ../../../include/yalecad/debug.h
graphics.o: ../../../include/yalecad/message.h
graphics.o: ../../../include/yalecad/colors.h ../../../include/yalecad/draw.h
graphics.o: ../../../include/yalecad/system.h ./menus.h
hprobes.o: ./geo.h /usr/include/stdio.h /usr/include/features.h
hprobes.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
hprobes.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
hprobes.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
hprobes.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
hprobes.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
hprobes.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
hprobes.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
hprobes.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
hprobes.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
hprobes.o: /usr/include/endian.h /usr/include/bits/endian.h
hprobes.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
hprobes.o: /usr/include/time.h /usr/include/sys/select.h
hprobes.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
hprobes.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
hprobes.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
hprobes.o: /usr/include/math.h /usr/include/bits/huge_val.h
hprobes.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
hprobes.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
hprobes.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
hprobes.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
hprobes.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
hprobes.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
hprobes.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
hprobes.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
hprobes.o: ./23tree.h ../../../include/yalecad/rbtree.h
hprobes.o: ../../../include/yalecad/debug.h
hprobes.o: ../../../include/yalecad/message.h
makelink.o: ./geo.h /usr/include/stdio.h /usr/include/features.h
makelink.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
makelink.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
makelink.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
makelink.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
makelink.o: /usr/include/libio.h /usr/include/_G_config.h
makelink.o: /usr/include/wchar.h
makelink.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
makelink.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
makelink.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
makelink.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
makelink.o: /usr/include/endian.h /usr/include/bits/endian.h
makelink.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
makelink.o: /usr/include/time.h /usr/include/sys/select.h
makelink.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
makelink.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
makelink.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
makelink.o: /usr/include/math.h /usr/include/bits/huge_val.h
makelink.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
makelink.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
makelink.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
makelink.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
makelink.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
makelink.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
makelink.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
makelink.o: /usr/include/bits/posix2_lim.h
makelink.o: ../../../include/yalecad/okmalloc.h ./23tree.h
makelink.o: ../../../include/yalecad/rbtree.h
makelink.o: ../../../include/yalecad/debug.h
makelink.o: ../../../include/yalecad/message.h
polar.o: ./geo.h /usr/include/stdio.h /usr/include/features.h
polar.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
polar.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
polar.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
polar.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
polar.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
polar.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
polar.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
polar.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
polar.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
polar.o: /usr/include/endian.h /usr/include/bits/endian.h
polar.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
polar.o: /usr/include/time.h /usr/include/sys/select.h
polar.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
polar.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
polar.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
polar.o: /usr/include/math.h /usr/include/bits/huge_val.h
polar.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
polar.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
polar.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
polar.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
polar.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
polar.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
polar.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
polar.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
polar.o: ./23tree.h ../../../include/yalecad/rbtree.h
polar.o: ../../../include/yalecad/debug.h ../../../include/yalecad/message.h
polar.o: ../../../include/yalecad/file.h
printgph.o: ./geo.h /usr/include/stdio.h /usr/include/features.h
printgph.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
printgph.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
printgph.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
printgph.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
printgph.o: /usr/include/libio.h /usr/include/_G_config.h
printgph.o: /usr/include/wchar.h
printgph.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
printgph.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
printgph.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
printgph.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
printgph.o: /usr/include/endian.h /usr/include/bits/endian.h
printgph.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
printgph.o: /usr/include/time.h /usr/include/sys/select.h
printgph.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
printgph.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
printgph.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
printgph.o: /usr/include/math.h /usr/include/bits/huge_val.h
printgph.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
printgph.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
printgph.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
printgph.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
printgph.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
printgph.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
printgph.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
printgph.o: /usr/include/bits/posix2_lim.h
printgph.o: ../../../include/yalecad/okmalloc.h ./23tree.h
printgph.o: ../../../include/yalecad/rbtree.h
printgph.o: ../../../include/yalecad/debug.h
printgph.o: ../../../include/yalecad/message.h
printgph.o: ../../../include/yalecad/file.h
readgeo.o: ./geo.h /usr/include/stdio.h /usr/include/features.h
readgeo.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
readgeo.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
readgeo.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
readgeo.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
readgeo.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
readgeo.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
readgeo.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
readgeo.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
readgeo.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
readgeo.o: /usr/include/endian.h /usr/include/bits/endian.h
readgeo.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
readgeo.o: /usr/include/time.h /usr/include/sys/select.h
readgeo.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
readgeo.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
readgeo.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
readgeo.o: /usr/include/math.h /usr/include/bits/huge_val.h
readgeo.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
readgeo.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
readgeo.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
readgeo.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
readgeo.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
readgeo.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
readgeo.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
readgeo.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
readgeo.o: ./23tree.h ../../../include/yalecad/rbtree.h
readgeo.o: ../../../include/yalecad/debug.h
readgeo.o: ../../../include/yalecad/message.h
rectlin.o: ./geo.h /usr/include/stdio.h /usr/include/features.h
rectlin.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
rectlin.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
rectlin.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
rectlin.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
rectlin.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
rectlin.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
rectlin.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
rectlin.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
rectlin.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
rectlin.o: /usr/include/endian.h /usr/include/bits/endian.h
rectlin.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
rectlin.o: /usr/include/time.h /usr/include/sys/select.h
rectlin.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
rectlin.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
rectlin.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
rectlin.o: /usr/include/math.h /usr/include/bits/huge_val.h
rectlin.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
rectlin.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
rectlin.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
rectlin.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
rectlin.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
rectlin.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
rectlin.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
rectlin.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
rectlin.o: ./23tree.h ../../../include/yalecad/rbtree.h
rectlin.o: ../../../include/yalecad/queue.h ../../../include/yalecad/debug.h
rectlin.o: ../../../include/yalecad/message.h
reduceg.o: ./geo.h /usr/include/stdio.h /usr/include/features.h
reduceg.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
reduceg.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
reduceg.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
reduceg.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
reduceg.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
reduceg.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
reduceg.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
reduceg.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
reduceg.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
reduceg.o: /usr/include/endian.h /usr/include/bits/endian.h
reduceg.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
reduceg.o: /usr/include/time.h /usr/include/sys/select.h
reduceg.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
reduceg.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
reduceg.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
reduceg.o: /usr/include/math.h /usr/include/bits/huge_val.h
reduceg.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
reduceg.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
reduceg.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
reduceg.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
reduceg.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
reduceg.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
reduceg.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
reduceg.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
reduceg.o: ./23tree.h ../../../include/yalecad/rbtree.h
reduceg.o: ../../../include/yalecad/debug.h
reduceg.o: ../../../include/yalecad/message.h
vprobes.o: ./geo.h /usr/include/stdio.h /usr/include/features.h
vprobes.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
vprobes.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
vprobes.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
vprobes.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
vprobes.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
vprobes.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
vprobes.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
vprobes.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
vprobes.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
vprobes.o: /usr/include/endian.h /usr/include/bits/endian.h
vprobes.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
vprobes.o: /usr/include/time.h /usr/include/sys/select.h
vprobes.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
vprobes.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
vprobes.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
vprobes.o: /usr/include/math.h /usr/include/bits/huge_val.h
vprobes.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
vprobes.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
vprobes.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
vprobes.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
vprobes.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
vprobes.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
vprobes.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
vprobes.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
vprobes.o: ./23tree.h ../../../include/yalecad/rbtree.h
vprobes.o: ../../../include/yalecad/debug.h
vprobes.o: ../../../include/yalecad/message.h
xgraph.o: ./geo.h /usr/include/stdio.h /usr/include/features.h
xgraph.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
xgraph.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
xgraph.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
xgraph.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
xgraph.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
xgraph.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
xgraph.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
xgraph.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
xgraph.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
xgraph.o: /usr/include/endian.h /usr/include/bits/endian.h
xgraph.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
xgraph.o: /usr/include/time.h /usr/include/sys/select.h
xgraph.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
xgraph.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
xgraph.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
xgraph.o: /usr/include/math.h /usr/include/bits/huge_val.h
xgraph.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
xgraph.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
xgraph.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
xgraph.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
xgraph.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
xgraph.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
xgraph.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
xgraph.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
xgraph.o: ./23tree.h ../../../include/yalecad/rbtree.h
xgraph.o: ../../../include/yalecad/debug.h ../../../include/yalecad/message.h
ygraph.o: ./geo.h /usr/include/stdio.h /usr/include/features.h
ygraph.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
ygraph.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
ygraph.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
ygraph.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
ygraph.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
ygraph.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
ygraph.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
ygraph.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
ygraph.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
ygraph.o: /usr/include/endian.h /usr/include/bits/endian.h
ygraph.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
ygraph.o: /usr/include/time.h /usr/include/sys/select.h
ygraph.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
ygraph.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
ygraph.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
ygraph.o: /usr/include/math.h /usr/include/bits/huge_val.h
ygraph.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
ygraph.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
ygraph.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
ygraph.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
ygraph.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
ygraph.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
ygraph.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
ygraph.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
ygraph.o: ./23tree.h ../../../include/yalecad/rbtree.h
ygraph.o: ../../../include/yalecad/debug.h ../../../include/yalecad/message.h
