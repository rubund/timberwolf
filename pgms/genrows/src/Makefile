#  Makefile for genrow standard cell row generator.
#  "@(#) Ymakefile (Yale) version 3.11 3/7/91"
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

SCCS_OP=get #normal sccs operation

#destination of output executable
DEST=../
PNAME=genrows

# name of the graphics menu and its final destination
MENU=genrows_menu genrows.dialog row.dialog macro.dialog

#where object code is located
objdir=../obj
O=${objdir}/

SRC=    draw.c\
	genrows.c \
	main.c \
	merge.c \
	readpar.c

OBJ=    ${O}draw.o\
	${O}genrows.o \
	${O}main.o \
	${O}merge.o \
	${O}readpar.o

INS= globals.h dialog.h menus.h dialog2.h dialog3.h

info:
	-@${ECHO} "make ${PNAME} - usage:"
	-@${ECHO} "Non-yale users should type "
	-@${ECHO} "    'make install_non_yale <CR>' "
	-@${ECHO} " "

# how to make genrow program
${DEST}${PNAME}:${OBJ} ${YALECAD} ${MENU}
	${GETDATE}
	${CC} ${CFLAGS} -I. -c ${DATE_C}
	${MV} date.o ${O}date.o 
	${CC} ${CFLAGS} ${OPTIONS} -o ${DEST}${PNAME} ${OBJ} ${O}date.o \
	${YALECAD} ${LINKLIB} 

# we can't do anything about yalecad but want to update if it has changed
${YALECAD}:


install:${DEST}${PNAME} ${MENU}

install_non_yale:
	-${S}if( test -d ${XLIB}${NOGRAPHICS} ) then \
		${ECHO} " " ; \
		${ECHO} "Note:found ${XLIB}"; \
		${ECHO} "making version with XWindow graphics..." ;\
		make ${DEST}${PNAME} GETDATE= CC=${CC} \
		    CLEANUP=${CLEANUP} NOGRAPHICS=${NOGRAPHICS} \
		    UNIX=${UNIX} DEBUG=${DEBUG} YALECAD=${YALECAD} \
		    CFLAGS="${CFLAGS}" ;\
		${ECHO} " " ; \
	else \
		${ECHO} " " ; \
		${ECHO} "Note:didn't find ${XLIB} or NOGRAPHICS requested" ; \
		${ECHO} "making version without XWindow graphics..." ; \
		make ${DEST}${PNAME} GETDATE= CC=${CC} \
		    CLEANUP=${CLEANUP} NOGRAPHICS=-DNOGRAPHICS \
		    UNIX=${UNIX} DEBUG=${DEBUG} YALECAD=${YALECAD} \
		    CFLAGS="${CFLAGS}" LINKLIB=-lm ;\
	fi ; 

clean:
	${RM} ${O}* *~ core *.bak

map :   
	nm -apg ${PNAME}

# how to build makefile dependencies
depend : ;
	${MAKEDEPEND} ${CFLAGS} ${OPTIONS} ${IDIR} ${SRC}

# ********************* begin sccs *********************************
#default sccs operation is get
SCCS_OP=get
#current release
REL=

# how to get sources from sccs
sources : ${SRC} ${INS} ${YMAKEFILE} ${MENU}
${SRC} ${INS} ${YMAKEFILE} ${MENU}: 
	${SCCS} ${SCCS_OP} ${REL} $@
# **********************  end sccs *********************************

#BEGIN DEPENDENCIES -- DO NOT DELETE THIS LINE

#END DEPENDENCIES -- DO NOT DELETE THIS LINE

#
# Now for the detail routing code
#
${O}genrows.o : genrows.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c genrows.c
	${MV} genrows.o ${O}genrows.o
${O}draw.o : draw.c
	${CC} ${CFLAGS} ${NOGRAPHICS} ${IDIR} ${OPTIONS} -c draw.c
	${MV} draw.o ${O}draw.o
${O}main.o : main.c
	${CC} ${NOGRAPHICS} ${CLEANUP} ${CFLAGS} ${IDIR} ${OPTIONS}\
		-c main.c 
	${MV} main.o ${O}main.o
${O}merge.o : merge.c
	${CC} ${CFLAGS} ${NOGRAPHICS} ${IDIR} ${OPTIONS} -c merge.c
	${MV} merge.o ${O}merge.o
${O}readpar.o : readpar.c
	${CC} ${CFLAGS} ${NOGRAPHICS} ${IDIR} ${OPTIONS} -c readpar.c
	${MV} readpar.o ${O}readpar.o
#end of makefile
# DO NOT DELETE

draw.o: /usr/include/string.h /usr/include/features.h
draw.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
draw.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
draw.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
draw.o: /usr/include/xlocale.h ../../../include/yalecad/base.h
draw.o: /usr/include/stdio.h /usr/include/bits/types.h
draw.o: /usr/include/bits/typesizes.h /usr/include/libio.h
draw.o: /usr/include/_G_config.h /usr/include/wchar.h
draw.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
draw.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
draw.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
draw.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
draw.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
draw.o: /usr/include/sys/types.h /usr/include/time.h
draw.o: /usr/include/sys/select.h /usr/include/bits/select.h
draw.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
draw.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
draw.o: /usr/include/alloca.h /usr/include/math.h
draw.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
draw.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
draw.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
draw.o: /usr/include/bits/mathcalls.h
draw.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
draw.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
draw.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
draw.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
draw.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
draw.o: ../../../include/yalecad/debug.h ../../../include/yalecad/message.h
draw.o: ./globals.h ../../../include/yalecad/file.h
draw.o: ../../../include/yalecad/draw.h ../../../include/yalecad/colors.h
draw.o: ../../../include/yalecad/dialog.h ../../../include/yalecad/relpos.h
draw.o: ./dialog.h ./dialog2.h ./dialog3.h ./menus.h
genrows.o: /usr/include/stdio.h /usr/include/features.h
genrows.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
genrows.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
genrows.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
genrows.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
genrows.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
genrows.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
genrows.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
genrows.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
genrows.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
genrows.o: /usr/include/endian.h /usr/include/bits/endian.h
genrows.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
genrows.o: /usr/include/time.h /usr/include/sys/select.h
genrows.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
genrows.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
genrows.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
genrows.o: /usr/include/math.h /usr/include/bits/huge_val.h
genrows.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
genrows.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
genrows.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
genrows.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
genrows.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
genrows.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
genrows.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
genrows.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
genrows.o: ../../../include/yalecad/file.h ../../../include/yalecad/debug.h
genrows.o: ../../../include/yalecad/message.h
genrows.o: ../../../include/yalecad/buster.h
genrows.o: ../../../include/yalecad/rbtree.h ./globals.h
main.o: /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h
main.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
main.o: /usr/include/gnu/stubs-64.h
main.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
main.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
main.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
main.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
main.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
main.o: ../../../include/yalecad/cleanup.h ../../../include/yalecad/message.h
main.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
main.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
main.o: /usr/include/endian.h /usr/include/bits/endian.h
main.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
main.o: /usr/include/time.h /usr/include/sys/select.h
main.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
main.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
main.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
main.o: /usr/include/math.h /usr/include/bits/huge_val.h
main.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
main.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
main.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
main.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
main.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
main.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
main.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
main.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
main.o: ../../../include/yalecad/file.h ../../../include/yalecad/string.h
main.o: ../../../include/yalecad/debug.h ./globals.h
merge.o: /usr/include/stdio.h /usr/include/features.h
merge.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
merge.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
merge.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
merge.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
merge.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
merge.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
merge.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
merge.o: ../../../include/yalecad/debug.h ../../../include/yalecad/message.h
merge.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
merge.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
merge.o: /usr/include/endian.h /usr/include/bits/endian.h
merge.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
merge.o: /usr/include/time.h /usr/include/sys/select.h
merge.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
merge.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
merge.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
merge.o: /usr/include/math.h /usr/include/bits/huge_val.h
merge.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
merge.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
merge.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
merge.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
merge.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
merge.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
merge.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
merge.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
merge.o: ./globals.h
readpar.o: ../../../include/yalecad/debug.h
readpar.o: ../../../include/yalecad/message.h ../../../include/yalecad/base.h
readpar.o: /usr/include/stdio.h /usr/include/features.h
readpar.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
readpar.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
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
readpar.o: ../../../include/yalecad/file.h ../../../include/yalecad/string.h
readpar.o: ../../../include/yalecad/yreadpar.h
readpar.o: ../../../include/yalecad/rbtree.h ./globals.h
