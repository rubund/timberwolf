# Ymakefile for program nocut
#  "@(#) Ymakefile (Yale) version 1.1 7/30/91 " 
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
PNAME=Mincut

#where the object code is located
objdir=../obj
O=${objdir}/

SRC= \
	main.c \
	readcells.c \
	output.c

OBJ= \
	${O}main.o \
	${O}output.o \
	${O}readcells.o 

INS= \
	globals.h 

info:   ; 
	-@${ECHO} "make ${DEST}${PNAME} - usage:" 
	-@${ECHO} "   make install - build program" 
	-@${ECHO} "   make install_non_yale - build program at foreign host" 
	-@${ECHO} "   make clean - remove binary" 
	-@${ECHO} "   make depend - added makefile dependencies" 
	-@${ECHO} "   make sources - pull sources from SCCS" 
	-@${ECHO} "   make lint - run lint on the sources" 


# how to make nocut program
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

# how to make syntax lint
lint:  ; 
	${LINT} ${LINT_OPT} ${IDIR} ${OPTIONS} *.c > lint.out 

#used to make documentation
bnf :  ys.awk 
	${AWK} -f ys.awk readcells.y > foo
	sed -e 's/;//' foo > tw_bnf
	${RM} foo

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
${O}main.o:main.c
	${CC} ${CLEANUP} ${CFLAGS} ${IDIR} ${OPTIONS} -c  main.c
	${MV} main.o ${O}main.o
${O}output.o:output.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  output.c
	${MV} output.o ${O}output.o
${O}readcells.o:readcells.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  readcells.c
	${MV} readcells.o ${O}readcells.o

# end makefile
# DO NOT DELETE

main.o: /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h
main.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
main.o: /usr/include/gnu/stubs-64.h
main.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
main.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
main.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
main.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
main.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
main.o: /usr/include/signal.h /usr/include/bits/sigset.h
main.o: /usr/include/bits/signum.h /usr/include/time.h
main.o: /usr/include/bits/siginfo.h /usr/include/bits/sigaction.h
main.o: /usr/include/bits/sigcontext.h /usr/include/bits/sigstack.h
main.o: /usr/include/sys/ucontext.h /usr/include/bits/pthreadtypes.h
main.o: /usr/include/bits/sigthread.h ../../../include/yalecad/base.h
main.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
main.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
main.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
main.o: /usr/include/sys/types.h /usr/include/sys/select.h
main.o: /usr/include/bits/select.h /usr/include/bits/time.h
main.o: /usr/include/sys/sysmacros.h /usr/include/alloca.h
main.o: /usr/include/math.h /usr/include/bits/huge_val.h
main.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
main.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
main.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
main.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
main.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
main.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
main.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
main.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
main.o: ../../../include/yalecad/cleanup.h ../../../include/yalecad/file.h
main.o: ../../../include/yalecad/message.h ../../../include/yalecad/debug.h
main.o: globals.h
readcells.o: /usr/include/string.h /usr/include/features.h
readcells.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
readcells.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
readcells.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
readcells.o: /usr/include/xlocale.h ../../../include/yalecad/base.h
readcells.o: /usr/include/stdio.h /usr/include/bits/types.h
readcells.o: /usr/include/bits/typesizes.h /usr/include/libio.h
readcells.o: /usr/include/_G_config.h /usr/include/wchar.h
readcells.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
readcells.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
readcells.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
readcells.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
readcells.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
readcells.o: /usr/include/sys/types.h /usr/include/time.h
readcells.o: /usr/include/sys/select.h /usr/include/bits/select.h
readcells.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
readcells.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
readcells.o: /usr/include/alloca.h /usr/include/math.h
readcells.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
readcells.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
readcells.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
readcells.o: /usr/include/bits/mathcalls.h
readcells.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
readcells.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
readcells.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
readcells.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
readcells.o: /usr/include/bits/posix2_lim.h
readcells.o: ../../../include/yalecad/okmalloc.h
readcells.o: ../../../include/yalecad/message.h
readcells.o: ../../../include/yalecad/debug.h
readcells.o: ../../../include/yalecad/string.h globals.h readcells_l.h
output.o: /usr/include/string.h /usr/include/features.h
output.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
output.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
output.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
output.o: /usr/include/xlocale.h globals.h /usr/include/stdio.h
output.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
output.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
output.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
output.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
output.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
output.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
output.o: /usr/include/endian.h /usr/include/bits/endian.h
output.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
output.o: /usr/include/time.h /usr/include/sys/select.h
output.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
output.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
output.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
output.o: /usr/include/math.h /usr/include/bits/huge_val.h
output.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
output.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
output.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
output.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
output.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
output.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
output.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
output.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
output.o: ../../../include/yalecad/message.h ../../../include/yalecad/hash.h
output.o: ../../../include/yalecad/yreadpar.h
output.o: ../../../include/yalecad/rbtree.h
