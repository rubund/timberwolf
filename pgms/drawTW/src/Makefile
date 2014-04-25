#  makefile for graphics program drawTW 
#  "@(#) Ymakefile (Yale) version 3.7 6/12/91"
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
PNAME=drawTW
DEST=../

#where object code is located
objdir=../obj
O=${objdir}/

SRC=    main.c    \
	quick.c   \
	twmc.c    \
	twsc.c 

OBJ=    ${O}main.o   \
	${O}quick.o  \
	${O}twmc.o  \
	${O}twsc.o

INS=globals.h

info:
	-@echo "make ${PNAME} - usage:"
	-@echo "Non-yale users should type "
	-@echo "    'make install_non_yale' - for first compile or "
	-@echo "    'make non_yale' for subsequent compiles"
	-@echo " "

# how to make draw program
${DEST}${PNAME}:${OBJ} ${YALECAD} 
	${GETDATE}
	${CC} ${CFLAGS} -I. -c ${DATE_C}
	${MV} date.o ${O}date.o 
	${CC} ${CFLAGS} ${OPTIONS} -o ${DEST}${PNAME} ${OBJ} ${O}date.o \
	${YALECAD} ${LINKLIB} 

# we can't do anything about yalecad but want to update if it has changed
${YALECAD}:


install:${DEST}${PNAME} 

install_non_yale:
	if( test -d ${XLIB} ) then \
		echo " " ; \
		echo "Note:found ${XLIB}"; \
		echo "making version with XWindow graphics..." ;\
		make ${DEST}${PNAME} GETDATE= CC=${CC} \
		    CLEANUP=${CLEANUP} NOGRAPHICS=${NOGRAPHICS} \
		    UNIX=${UNIX} DEBUG=${DEBUG} YALECAD=${YALECAD} \
		    CFLAGS="${CFLAGS}" ;\
		echo " " ; \
	else \
		echo " " ; \
		echo "Note:didn't find ${XLIB}" ; \
		echo "making version without XWindow graphics..." ; \
		make ${DEST}${PNAME} GETDATE= CC=${CC} \
		    CLEANUP=${CLEANUP} NOGRAPHICS=-DNOGRAPHICS \
		    UNIX=${UNIX} DEBUG=${DEBUG} YALECAD=${YALECAD} \
		    CFLAGS="${CFLAGS}" LINKLIB=-lm ;\
	fi ; 

clean:
	rm -r -f ${O}*

clean_no_yacc:
	rm -r -f ${OBJ} y.tab.c

map :   
	nm -apg ${PNAME}

lint:
#	lint ${IDIR} -Ctwtmp ${SRC2}
#	lint ${IDIR} ${SRC} llib-ltwtmp.ln
	lint ${IDIR} *.c  > fool

# how to build makefile dependencies
depend : ;
	${MAKEDEPEND} ${CFLAGS} ${OPTIONS} ${IDIR} ${SRC}

# ********************* begin sccs *********************************
#default sccs operation is get
SCCS_OP=get
#current release
REL=

# how to get sources from sccs
sources : ${SRC} ${INS} ${YMAKEFILE}
${SRC} ${INS} ${YMAKEFILE}: 
	${SCCS} ${SCCS_OP} ${REL} $@
# **********************  end sccs *********************************

#BEGIN DEPENDENCIES -- DO NOT DELETE THIS LINE

#END DEPENDENCIES -- DO NOT DELETE THIS LINE

# how to compile the src 
${O}main.o:	main.c ${INS}
	${CC} ${IDIR} ${CLEANUP} ${CFLAGS} ${OPTIONS} -c main.c
	${MV} main.o ${O}main.o 

${O}quick.o:	quick.c ${INS}
	${CC} ${IDIR} ${CFLAGS} ${OPTIONS} -c quick.c
	${MV} quick.o ${O}quick.o 

${O}twmc.o:	twmc.c ${INS}
	${CC} ${IDIR} ${CFLAGS} ${OPTIONS} -c twmc.c
	${MV} twmc.o ${O}twmc.o 

${O}twsc.o:	twsc.c ${INS}
	${CC} ${IDIR} ${CFLAGS} ${OPTIONS} -c twsc.c
	${MV} twsc.o ${O}twsc.o 


#end of makefile
# DO NOT DELETE

main.o: /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h
main.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
main.o: /usr/include/gnu/stubs-64.h
main.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
main.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
main.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
main.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
main.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
main.o: globals.h ../../../include/yalecad/base.h /usr/include/stdlib.h
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
main.o: ../../../include/yalecad/program.h ../../../include/yalecad/string.h
main.o: ../../../include/yalecad/message.h
main.o: ../../../include/yalecad/wgraphics.h
main.o: ../../../include/yalecad/colors.h ../../../include/yalecad/debug.h
main.o: ../../../include/yalecad/cleanup.h ../../../include/yalecad/file.h
quick.o: /usr/include/stdio.h /usr/include/features.h
quick.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
quick.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
quick.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
quick.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
quick.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
quick.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
quick.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
quick.o: globals.h ../../../include/yalecad/base.h /usr/include/stdlib.h
quick.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
quick.o: /usr/include/endian.h /usr/include/bits/endian.h
quick.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
quick.o: /usr/include/time.h /usr/include/sys/select.h
quick.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
quick.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
quick.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
quick.o: /usr/include/math.h /usr/include/bits/huge_val.h
quick.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
quick.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
quick.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
quick.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
quick.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
quick.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
quick.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
quick.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
quick.o: ../../../include/yalecad/program.h ../../../include/yalecad/string.h
quick.o: ../../../include/yalecad/message.h
quick.o: ../../../include/yalecad/wgraphics.h
quick.o: ../../../include/yalecad/colors.h ../../../include/yalecad/debug.h
twmc.o: /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h
twmc.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
twmc.o: /usr/include/gnu/stubs-64.h
twmc.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
twmc.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
twmc.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
twmc.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
twmc.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
twmc.o: globals.h ../../../include/yalecad/base.h /usr/include/stdlib.h
twmc.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
twmc.o: /usr/include/endian.h /usr/include/bits/endian.h
twmc.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
twmc.o: /usr/include/time.h /usr/include/sys/select.h
twmc.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
twmc.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
twmc.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
twmc.o: /usr/include/math.h /usr/include/bits/huge_val.h
twmc.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
twmc.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
twmc.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
twmc.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
twmc.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
twmc.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
twmc.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
twmc.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
twmc.o: ../../../include/yalecad/program.h ../../../include/yalecad/string.h
twmc.o: ../../../include/yalecad/message.h
twmc.o: ../../../include/yalecad/wgraphics.h
twmc.o: ../../../include/yalecad/colors.h ../../../include/yalecad/debug.h
twsc.o: /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h
twsc.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
twsc.o: /usr/include/gnu/stubs-64.h
twsc.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
twsc.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
twsc.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
twsc.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
twsc.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
twsc.o: globals.h ../../../include/yalecad/base.h /usr/include/stdlib.h
twsc.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
twsc.o: /usr/include/endian.h /usr/include/bits/endian.h
twsc.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
twsc.o: /usr/include/time.h /usr/include/sys/select.h
twsc.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
twsc.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
twsc.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
twsc.o: /usr/include/math.h /usr/include/bits/huge_val.h
twsc.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
twsc.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
twsc.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
twsc.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
twsc.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
twsc.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
twsc.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
twsc.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
twsc.o: ../../../include/yalecad/program.h ../../../include/yalecad/string.h
twsc.o: ../../../include/yalecad/message.h
twsc.o: ../../../include/yalecad/wgraphics.h
twsc.o: ../../../include/yalecad/colors.h ../../../include/yalecad/debug.h
