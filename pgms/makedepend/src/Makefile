# Ymakefile for program makedepend
#  "@(#) Ymakefile (Yale) version 1.8 2/5/91 " 
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
PNAME=makedepend

#where the object code is located
objdir=../obj
O=${objdir}/

LINKLIB=-lm

SRC= \
	include.c \
	main.c \
	parse.c \
	pr.c 

OBJ= \
	${O}include.o \
	${O}main.o \
	${O}parse.o \
	${O}pr.o 

INS= \
	def.h 

info:   ; 
	-@${ECHO} "make ${DEST}${PNAME} - usage:" 
	-@${ECHO} "   make install - build program" 
	-@${ECHO} "   make clean - remove binary" 
	-@${ECHO} "   make depend - added makefile dependencies" 
	-@${ECHO} "   make sources - pull sources from SCCS" 


# how to make makedepend program
${DEST}${PNAME}:${OBJ} 
	${CC} ${CFLAGS} ${OPTIONS} -o ${DEST}${PNAME} ${OBJ} ${LINKLIB} 

install:${DEST}${PNAME}

install_non_yale:
	make ${DEST}${PNAME} GETDATE= CC=${CC} \
	    CLEANUP=${CLEANUP} NOGRAPHICS=${NOGRAPHICS} \
	    UNIX=${UNIX} DEBUG=${DEBUG} YALECAD=${YALECAD} \
	    CFLAGS="${CFLAGS}" LINKLIB="${LINKLIB}" ;
	echo " "

clean: ;
	${RM} ${O}* *~ core *.bak

# how to build makefile dependencies
depend : ;
	${MAKEDEPEND} ${OPTIONS} ${IDIR} ${SRC}

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
${O}cppsetup.o:cppsetup.c ${INS}
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  cppsetup.c
	${MV} cppsetup.o ${O}cppsetup.o
${O}include.o:include.c ${INS}
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  include.c
	${MV} include.o ${O}include.o
${O}main.o:main.c ${INS}
	${CC} ${CLEANUP} ${CFLAGS} ${IDIR} ${OPTIONS} -c  main.c
	${MV} main.o ${O}main.o
${O}parse.o:parse.c ${INS}
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  parse.c
	${MV} parse.o ${O}parse.o
${O}pr.o:pr.c ${INS}
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  pr.c
	${MV} pr.o ${O}pr.o

# end makefile
# DO NOT DELETE

include.o: /usr/include/string.h /usr/include/features.h
include.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
include.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
include.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
include.o: /usr/include/xlocale.h def.h /usr/include/stdio.h
include.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
include.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
include.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
include.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
include.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
include.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
include.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
include.o: /usr/include/sys/types.h /usr/include/time.h
include.o: /usr/include/sys/select.h /usr/include/bits/select.h
include.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
include.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
include.o: /usr/include/alloca.h /usr/include/ctype.h /usr/include/fcntl.h
include.o: /usr/include/bits/fcntl.h /usr/include/bits/stat.h
include.o: /usr/include/sys/stat.h
main.o: /usr/include/string.h /usr/include/features.h
main.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
main.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
main.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
main.o: /usr/include/xlocale.h def.h /usr/include/stdio.h
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
main.o: /usr/include/alloca.h /usr/include/ctype.h /usr/include/fcntl.h
main.o: /usr/include/bits/fcntl.h /usr/include/bits/stat.h
main.o: /usr/include/sys/stat.h /usr/include/sys/signal.h
main.o: /usr/include/signal.h /usr/include/bits/signum.h
main.o: /usr/include/bits/siginfo.h /usr/include/bits/sigaction.h
main.o: /usr/include/bits/sigcontext.h /usr/include/bits/sigstack.h
main.o: /usr/include/sys/ucontext.h /usr/include/bits/sigthread.h
parse.o: /usr/include/string.h /usr/include/features.h
parse.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
parse.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
parse.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
parse.o: /usr/include/xlocale.h def.h /usr/include/stdio.h
parse.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
parse.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
parse.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
parse.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
parse.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
parse.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
parse.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
parse.o: /usr/include/sys/types.h /usr/include/time.h
parse.o: /usr/include/sys/select.h /usr/include/bits/select.h
parse.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
parse.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
parse.o: /usr/include/alloca.h /usr/include/ctype.h /usr/include/fcntl.h
parse.o: /usr/include/bits/fcntl.h /usr/include/bits/stat.h
parse.o: /usr/include/sys/stat.h /usr/include/sys/signal.h
parse.o: /usr/include/signal.h /usr/include/bits/signum.h
parse.o: /usr/include/bits/siginfo.h /usr/include/bits/sigaction.h
parse.o: /usr/include/bits/sigcontext.h /usr/include/bits/sigstack.h
parse.o: /usr/include/sys/ucontext.h /usr/include/bits/sigthread.h
pr.o: /usr/include/string.h /usr/include/features.h /usr/include/sys/cdefs.h
pr.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
pr.o: /usr/include/gnu/stubs-64.h
pr.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
pr.o: /usr/include/xlocale.h def.h /usr/include/stdio.h
pr.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
pr.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
pr.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
pr.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
pr.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
pr.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
pr.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
pr.o: /usr/include/sys/types.h /usr/include/time.h /usr/include/sys/select.h
pr.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
pr.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
pr.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
pr.o: /usr/include/ctype.h /usr/include/fcntl.h /usr/include/bits/fcntl.h
pr.o: /usr/include/bits/stat.h /usr/include/sys/stat.h
