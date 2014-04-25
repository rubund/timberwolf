# Ymakefile for program twflow
#  "@(#) Ymakefile (Yale) version 2.6 3/12/91 " 
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
PNAME=twflow

#where the object code is located
objdir=../obj
O=${objdir}/

SRC= \
	autoflow.c \
	findflow.c \
	graphics.c \
	io.c \
	main.c \
	readobjects.c \
	program.c

OBJ= \
	${O}autoflow.o \
	${O}findflow.o \
	${O}graphics.o \
	${O}io.o \
	${O}main.o \
	${O}program.o \
	${O}readobjects.o 

INS= \
	globals.h \
	menus.h 

info:   ; 
	-@${ECHO} "make ${DEST}${PNAME} - usage:" 
	-@${ECHO} "   make install - build program" 
	-@${ECHO} "   make install_non_yale - build program at foreign host" 
	-@${ECHO} "   make clean - remove binary" 
	-@${ECHO} "   make depend - added makefile dependencies" 
	-@${ECHO} "   make sources - pull sources from SCCS" 
	-@${ECHO} "   make lint - run lint on the sources" 


# how to make twflow program
${DEST}${PNAME}:${OBJ} ${YALECAD}
	${GETDATE}
	${CC} ${CFLAGS} -I. -c ${DATE_C}
	${MV} date.o ${O}date.o
	${CC} ${CFLAGS} ${OPTIONS} -o ${DEST}${PNAME} ${OBJ} ${O}date.o \
	${YALECAD} ${LINKLIB}

# we can't do anything about yalecad but want to update if it has changed
${YALECAD}: ;

install:${DEST}${PNAME}

install_non_yale:
	-${S}if( test -d ${XLIB}${NOGRAPHICS} ) then \
		echo " " ; \
		echo "Note:found ${XLIB}"; \
		echo "making version with XWindow graphics..." ;\
		make ${DEST}${PNAME} GETDATE= CC=${CC} \
			CLEANUP=${CLEANUP} NOGRAPHICS=${NOGRAPHICS} \
			UNIX=${UNIX} DEBUG=${DEBUG} YALECAD=${YALECAD} ;\
		echo " " ; \
	else \
		echo " " ; \
		echo "Note:didn't find ${XLIB} or NOGRAPHICS requested"; \
		echo "making version without XWindow graphics..." ; \
		make ${DEST}${PNAME} GETDATE= CC=${CC} \
			CLEANUP=${CLEANUP} NOGRAPHICS=-DNOGRAPHICS \
			UNIX=${UNIX} DEBUG=${DEBUG} YALECAD=${YALECAD} \
			CFLAGS="${CFLAGS}" LINKLIB="${LINKLIB}" ;\
	fi ;  

clean: ;
	${RM} ${O}* ~* core *.bak foo* y.output y.tab.c

# how to build makefile dependencies
depend : ;
	${MAKEDEPEND} ${CFLAGS} ${OPTIONS} ${IDIR} ${SRC}

# how to make twflow lint
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
${O}autoflow.o:autoflow.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  autoflow.c
	${MV} autoflow.o ${O}autoflow.o
${O}findflow.o:findflow.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  findflow.c
	${MV} findflow.o ${O}findflow.o
${O}graphics.o:graphics.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  graphics.c
	${MV} graphics.o ${O}graphics.o
${O}io.o:io.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  io.c
	${MV} io.o ${O}io.o
${O}main.o:main.c
	${CC} ${CLEANUP} ${CFLAGS} ${IDIR} ${OPTIONS} -c  main.c
	${MV} main.o ${O}main.o
${O}program.o:program.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  program.c
	${MV} program.o ${O}program.o
${O}readobjects.o:readobjects.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  readobjects.c
	${MV} readobjects.o ${O}readobjects.o

# end makefile
# DO NOT DELETE

autoflow.o: /usr/include/string.h /usr/include/features.h
autoflow.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
autoflow.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
autoflow.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
autoflow.o: /usr/include/xlocale.h ../../../include/yalecad/base.h
autoflow.o: /usr/include/stdio.h /usr/include/bits/types.h
autoflow.o: /usr/include/bits/typesizes.h /usr/include/libio.h
autoflow.o: /usr/include/_G_config.h /usr/include/wchar.h
autoflow.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
autoflow.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
autoflow.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
autoflow.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
autoflow.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
autoflow.o: /usr/include/sys/types.h /usr/include/time.h
autoflow.o: /usr/include/sys/select.h /usr/include/bits/select.h
autoflow.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
autoflow.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
autoflow.o: /usr/include/alloca.h /usr/include/math.h
autoflow.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
autoflow.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
autoflow.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
autoflow.o: /usr/include/bits/mathcalls.h
autoflow.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
autoflow.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
autoflow.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
autoflow.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
autoflow.o: /usr/include/bits/posix2_lim.h
autoflow.o: ../../../include/yalecad/okmalloc.h
autoflow.o: ../../../include/yalecad/message.h
autoflow.o: ../../../include/yalecad/debug.h ./globals.h
findflow.o: /usr/include/stdio.h /usr/include/features.h
findflow.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
findflow.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
findflow.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
findflow.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
findflow.o: /usr/include/libio.h /usr/include/_G_config.h
findflow.o: /usr/include/wchar.h
findflow.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
findflow.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
findflow.o: ./globals.h ../../../include/yalecad/base.h /usr/include/stdlib.h
findflow.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
findflow.o: /usr/include/endian.h /usr/include/bits/endian.h
findflow.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
findflow.o: /usr/include/time.h /usr/include/sys/select.h
findflow.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
findflow.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
findflow.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
findflow.o: /usr/include/math.h /usr/include/bits/huge_val.h
findflow.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
findflow.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
findflow.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
findflow.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
findflow.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
findflow.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
findflow.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
findflow.o: /usr/include/bits/posix2_lim.h
findflow.o: ../../../include/yalecad/okmalloc.h
findflow.o: ../../../include/yalecad/message.h
findflow.o: ../../../include/yalecad/debug.h ../../../include/yalecad/file.h
findflow.o: ../../../include/yalecad/string.h ../../../include/yalecad/draw.h
findflow.o: ../../../include/yalecad/colors.h
graphics.o: /usr/include/string.h /usr/include/features.h
graphics.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
graphics.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
graphics.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
graphics.o: /usr/include/xlocale.h ../../../include/yalecad/base.h
graphics.o: /usr/include/stdio.h /usr/include/bits/types.h
graphics.o: /usr/include/bits/typesizes.h /usr/include/libio.h
graphics.o: /usr/include/_G_config.h /usr/include/wchar.h
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
graphics.o: ../../../include/yalecad/message.h
graphics.o: ../../../include/yalecad/draw.h ../../../include/yalecad/string.h
graphics.o: ../../../include/yalecad/colors.h
graphics.o: ../../../include/yalecad/debug.h ./globals.h ./menus.h
io.o: /usr/include/string.h /usr/include/features.h /usr/include/sys/cdefs.h
io.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
io.o: /usr/include/gnu/stubs-64.h
io.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
io.o: /usr/include/xlocale.h ./globals.h ../../../include/yalecad/base.h
io.o: /usr/include/stdio.h /usr/include/bits/types.h
io.o: /usr/include/bits/typesizes.h /usr/include/libio.h
io.o: /usr/include/_G_config.h /usr/include/wchar.h
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
io.o: ../../../include/yalecad/message.h ../../../include/yalecad/debug.h
io.o: ../../../include/yalecad/file.h ../../../include/yalecad/draw.h
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
main.o: /usr/include/bits/sigthread.h ../../../include/yalecad/cleanup.h
main.o: ../../../include/yalecad/message.h ../../../include/yalecad/base.h
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
main.o: ../../../include/yalecad/program.h ../../../include/yalecad/string.h
main.o: ../../../include/yalecad/file.h ../../../include/yalecad/debug.h
main.o: ./globals.h
readobjects.o: /usr/include/string.h /usr/include/features.h
readobjects.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
readobjects.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
readobjects.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
readobjects.o: /usr/include/xlocale.h ./globals.h
readobjects.o: ../../../include/yalecad/base.h /usr/include/stdio.h
readobjects.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
readobjects.o: /usr/include/libio.h /usr/include/_G_config.h
readobjects.o: /usr/include/wchar.h
readobjects.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
readobjects.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
readobjects.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
readobjects.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
readobjects.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
readobjects.o: /usr/include/sys/types.h /usr/include/time.h
readobjects.o: /usr/include/sys/select.h /usr/include/bits/select.h
readobjects.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
readobjects.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
readobjects.o: /usr/include/alloca.h /usr/include/math.h
readobjects.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
readobjects.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
readobjects.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
readobjects.o: /usr/include/bits/mathcalls.h
readobjects.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
readobjects.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
readobjects.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
readobjects.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
readobjects.o: /usr/include/bits/posix2_lim.h
readobjects.o: ../../../include/yalecad/okmalloc.h
readobjects.o: ../../../include/yalecad/message.h
readobjects.o: ../../../include/yalecad/file.h
readobjects.o: ../../../include/yalecad/debug.h
readobjects.o: ../../../include/yalecad/string.h readobjects_l.h
program.o: /usr/include/string.h /usr/include/features.h
program.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
program.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
program.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
program.o: /usr/include/xlocale.h ../../../include/yalecad/base.h
program.o: /usr/include/stdio.h /usr/include/bits/types.h
program.o: /usr/include/bits/typesizes.h /usr/include/libio.h
program.o: /usr/include/_G_config.h /usr/include/wchar.h
program.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
program.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
program.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
program.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
program.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
program.o: /usr/include/sys/types.h /usr/include/time.h
program.o: /usr/include/sys/select.h /usr/include/bits/select.h
program.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
program.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
program.o: /usr/include/alloca.h /usr/include/math.h
program.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
program.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
program.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
program.o: /usr/include/bits/mathcalls.h
program.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
program.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
program.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
program.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
program.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
program.o: ../../../include/yalecad/message.h
program.o: ../../../include/yalecad/string.h ../../../include/yalecad/file.h
program.o: ../../../include/yalecad/debug.h ./globals.h
