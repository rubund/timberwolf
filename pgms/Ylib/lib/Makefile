# Ymakefile for Yalecad libary archives.
#  "@(#) Ymakefile (Yale) version 3.36 3/6/92 " 
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

# name of archive 1) using system memory manager 2) yale memory manager.
NYCADSYS=libycad.sys.a 
NYCADMEM=libycad.mem.a

#where the object code is located
objdir=../obj
O=${objdir}/

SRC= \
	assign.c \
	buster.c \
	cleanup.c \
	colors.c \
	deck.c \
	dialog.c \
	draw.c \
	dset.c \
	edcolors.c \
	file.c \
	getftime.c \
        graph.c \
	grid.c \
	hash.c \
	heap.c \
	list.c \
	log.c \
	matrix.c \
	menus.c \
	message.c \
	mst.c \
	mytime.c \
	okmalloc.c \
	path.c \
	plot.c \
	program.c \
	project.c \
	queue.c \
	quicksort.c \
	radixsort.c \
	rand.c \
	rbtree.c \
	relpath.c \
	set.c \
	stat.c \
	stats.c \
	string.c \
	svd.c \
	system.c \
	time.c \
	timer.c \
	trans.c \
	wgraphics.c \
	ydebug.c \
	yreadpar.c 

OBJ= \
	${O}assign.o \
	${O}buster.o \
	${O}cleanup.o \
	${O}colors.o \
	${O}deck.o \
	${O}dialog.o \
	${O}draw.o \
	${O}dset.o \
	${O}edcolors.o \
	${O}file.o \
	${O}getftime.o \
	${O}graph.o \
	${O}grid.o \
	${O}hash.o \
	${O}heap.o \
	${O}list.o \
	${O}log.o \
	${O}matrix.o \
	${O}menus.o \
	${O}message.o \
	${O}mst.o \
	${O}mytime.o \
	${O}path.o \
	${O}plot.o \
	${O}program.o \
	${O}project.o \
	${O}queue.o \
	${O}quicksort.o \
	${O}radixsort.o \
	${O}rand.o \
	${O}rbtree.o \
	${O}relpath.o \
	${O}set.o \
	${O}stat.o \
	${O}stats.o \
	${O}string.o \
	${O}svd.o \
	${O}system.o \
	${O}time.o \
	${O}timer.o \
	${O}trans.o \
	${O}wgraphics.o \
	${O}ydebug.o \
	${O}yreadpar.o 

INS= \
	info.h 


info:   ;
	-@echo "make archives - usage:"
	-@echo "Non-yale users should type 'make install_non_yale'"
	-@echo " "

# we need to specify all variables so that master makefile can override
# them.
archives:
	-@if( test -d ${XLIB}${NOGRAPHICS} ) then \
		echo " " ; \
		echo "Note:found ${XLIB}"; \
		echo "making library version with XWindow graphics..." ;\
		make ${YCADMEM} MEMORYFLAG= CC=${CC} \
		    CLEANUP=${CLEANUP} NOGRAPHICS=${NOGRAPHICS} \
		    UNIX=${UNIX} DEBUG=${DEBUG} CFLAGS="${CFLAGS}" \
		    YCADSYS=${YCADSYS} YCADMEM=${YCADMEM} AR=${AR} ; \
		make ${YCADSYS} MEMORYFLAG= CC=${CC} \
		    CLEANUP=${CLEANUP} NOGRAPHICS=${NOGRAPHICS} \
		    UNIX=${UNIX} DEBUG=${DEBUG} CFLAGS="${CFLAGS}" \
		    YCADSYS=${YCADSYS} YCADMEM=${YCADMEM} AR=${AR} ; \
		echo " " ; \
	else \
		echo " " ; \
		echo "Note:didn't find ${XLIB} or NOGRAPHICS requested"; \
		echo "making version without XWindow graphics..." ; \
		make ${YCADMEM} MEMORYFLAG= CC=${CC} \
		    CLEANUP=${CLEANUP} NOGRAPHICS=-DNOGRAPHICS \
		    UNIX=${UNIX} DEBUG=${DEBUG} CFLAGS="${CFLAGS}" \
		    YCADSYS=${YCADSYS} YCADMEM=${YCADMEM} AR=${AR} ; \
		make ${YCADSYS} MEMORYFLAG= CC=${CC} \
		    CLEANUP=${CLEANUP} NOGRAPHICS=-DNOGRAPHICS \
		    CLEANUP=${CLEANUP} NOGRAPHICS=-DNOGRAPHICS \
		    UNIX=${UNIX} DEBUG=${DEBUG} CFLAGS="${CFLAGS}" \
		    YCADSYS=${YCADSYS} YCADMEM=${YCADMEM} AR=${AR} ; \
		echo " " ; \
	fi ; 

# puts library in correct system place at Yale
install_yale: 
	make archives CC=${CC} CLEANUP=${CLEANUP} \
		NOGRAPHICS=${NOGRAPHICS} UNIX=${UNIX} DEBUG=${DEBUG} \
		CFLAGS="${CFLAGS}" AR=${AR} RANLIB=${RANLIB}

# puts library relative to this directory at Yale
install:install_non_yale

install_non_yale:
	make archives CC=${CC} CLEANUP=${CLEANUP} \
		NOGRAPHICS=${NOGRAPHICS} UNIX=${UNIX} DEBUG=${DEBUG} \
		CFLAGS="${CFLAGS}" \
		YCADSYS=${NYCADSYS} YCADMEM=${NYCADMEM} AR=${AR}

clean:
	${RM} ${O}* *~ foo *.bak

# how to build makefile dependencies
depend : ;
	-@if( test -d ${XLIB} ) then \
	    ${ECHO} "depending with graphics" ; \
	    ${ECHO} "${MAKEDEPEND} ${CFLAGS} ${OPTIONS}  ${IDIR} ${SRC}" ; \
	    ${MAKEDEPEND} ${CFLAGS} ${OPTIONS}  ${IDIR} ${SRC} ; \
	else \
	    ${ECHO} "depending with no X graphics " ; \
	    ${ECHO} "${MAKEDEPEND} ${CFLAGS} -DNOGRAPHICS ${OPTIONS} \
	    ${IDIR} ${SRC}" ; \
	    ${MAKEDEPEND} ${CFLAGS} -DNOGRAPHICS ${OPTIONS} ${IDIR} ${SRC}; \
	fi ; 

# for apollo inlibs 
inlib: ;
	${LD} -o ycadmemlib -A allmarks -A noallres ${O}mem.mem.o ${OBJ}
	${LD} -o ycadsyslib -A allmarks -A noallres ${O}mem.sys.o ${OBJ}

motiflib: ;
	${MV} draw.c motif/xdraw.c
	${MV} menus.c motif/xmenus.c
	${MV} motif/menus.c menus.c
	${MV} motif/draw.c draw.c

xlib: ;
	${MV} draw.c motif/mdraw.c
	${MV} menus.c motif/mmenus.c
	${MV} motif/xmenus.c menus.c
	${MV} motif/xdraw.c draw.c
	${MV} motif/mmenus.c motif/menus.c
	${MV} motif/mdraw.c motif/draw.c

# make the library quickly at yale.
quick :
	make install AR=echo RANLIB=echo
	make reset

# how to make lib lint
lint:  ; 
	${LINT} ${LINT_OPT} ${IDIR} ${OPTIONS} *.c > lint.out 

reset: $(OBJ)
	make reset_lib O=""

reset_lib:
	${RM} ${NYCADMEM} ${NYCADSYS}
	${RM} ${objdir}/${NYCADMEM} ${objdir}/${NYCADSYS}
	for i in $(OBJ); do \
		( cd ${objdir} ;${AR} qv ${NYCADMEM} $$i ; \
		${AR} qv ${NYCADSYS} $$i ; ) \
	done ;
	( cd ${objdir} ; \
	    ${AR} rv ${NYCADMEM} mem.mem.o ; \
	    ${AR} rv ${NYCADSYS} mem.sys.o ; \
	    ${MV} ${NYCADMEM} ../lib/${NYCADMEM} ; \
	    ${MV} ${NYCADSYS} ../lib/${NYCADSYS} ; \
	) ;
	${RANLIB} ${NYCADMEM}
	${RANLIB} ${NYCADSYS}

# profiling library.
profile:
	make prolib objdir="../obj.pro" NYCADSYS=libycad.sys-p.a  \
	NYCADMEM=libycad.mem-p.a CFLAGS="-O -pg"


prolib: 
	make ${NYCADMEM} MEMORYFLAG= CC=${CC} \
	    CLEANUP=${CLEANUP} NOGRAPHICS=${NOGRAPHICS} \
	    UNIX=${UNIX} DEBUG=${DEBUG} CFLAGS="${CFLAGS}" \
	    NYCADSYS=${NYCADSYS} NYCADMEM=${NYCADMEM} \
	    objdir="${objdir}" ;
	make ${NYCADSYS} MEMORYFLAG= CC=${CC} \
	    CLEANUP=${CLEANUP} NOGRAPHICS=${NOGRAPHICS} \
	    UNIX=${UNIX} DEBUG=${DEBUG} CFLAGS="${CFLAGS}" \
	    NYCADSYS=${NYCADSYS} NYCADMEM=${NYCADMEM} \
	    objdir="${objdir}" ;

proclean:
	${RM} ../obj.pro/* *~ foo *.bak

# memory debug library.
memory:
	make memlib objdir="../obj.mem" NYCADMEM=libycad.mem-d.a  \
	CFLAGS="-g -DMEM_DEBUG"


memlib: 
	make ${NYCADMEM} MEMORYFLAG= CC=${CC} \
	    CLEANUP=${CLEANUP} NOGRAPHICS=${NOGRAPHICS} \
	    UNIX=${UNIX} DEBUG=${DEBUG} CFLAGS="${CFLAGS}" \
	    NYCADSYS=${NYCADSYS} NYCADMEM=${NYCADMEM} \
	    objdir="${objdir}" ;

memclean:
	${RM} ../obj.mem/* *~ foo *.bak

# test program rules.

test:	assign.test dset.test graph.test list.test path.test plot.test \
        radixsort.test rand.test rbtree.test stats.test svd.test mem.test

testclean:
	${RM} assign.test dset.test graph.test list.test path.test plot.test \
        radixsort.test rand.test rbtree.test stats.test svd.test mem.test
	${RM} assign.o dset.o graph.o list.o path.o plot.o rand.o \
	radixsort.test rbtree.o stats.o svd.o okmalloc.o


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



# How to compile the sources
${O}assign.o:assign.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  assign.c
	${AR} rv ${NYCADMEM} assign.o
	${AR} rv ${NYCADSYS} assign.o
	${MV} assign.o ${O}assign.o
${O}buster.o:buster.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  buster.c
	${AR} rv ${NYCADMEM} buster.o
	${AR} rv ${NYCADSYS} buster.o
	${MV} buster.o ${O}buster.o
${O}cleanup.o:cleanup.c
	${CC} ${CLEANUP} ${CFLAGS} ${IDIR} ${OPTIONS} -c cleanup.c
	${AR} rv ${NYCADMEM} cleanup.o
	${AR} rv ${NYCADSYS} cleanup.o
	${MV} cleanup.o ${O}cleanup.o
${O}colors.o:colors.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  colors.c
	${AR} rv ${NYCADMEM} colors.o
	${AR} rv ${NYCADSYS} colors.o
	${MV} colors.o ${O}colors.o
${O}deck.o:deck.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  deck.c
	${AR} rv ${NYCADMEM} deck.o
	${AR} rv ${NYCADSYS} deck.o
	${MV} deck.o ${O}deck.o
${O}dialog.o:dialog.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  dialog.c
	${AR} rv ${NYCADMEM} dialog.o
	${AR} rv ${NYCADSYS} dialog.o
	${MV} dialog.o ${O}dialog.o
${O}draw.o:draw.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  draw.c
	${AR} rv ${NYCADMEM} draw.o
	${AR} rv ${NYCADSYS} draw.o
	${MV} draw.o ${O}draw.o
${O}dset.o:dset.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  dset.c
	${AR} rv ${NYCADMEM} dset.o
	${AR} rv ${NYCADSYS} dset.o
	${MV} dset.o ${O}dset.o
${O}edcolors.o:edcolors.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  edcolors.c
	${AR} rv ${NYCADMEM} edcolors.o
	${AR} rv ${NYCADSYS} edcolors.o
	${MV} edcolors.o ${O}edcolors.o
${O}file.o:file.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  file.c
	${AR} rv ${NYCADMEM} file.o
	${AR} rv ${NYCADSYS} file.o
	${MV} file.o ${O}file.o
${O}getftime.o:getftime.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  getftime.c
	${AR} rv ${NYCADMEM} getftime.o
	${AR} rv ${NYCADSYS} getftime.o
	${MV} getftime.o ${O}getftime.o
${O}graph.o:graph.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  graph.c
	${AR} rv ${NYCADMEM} graph.o
	${AR} rv ${NYCADSYS} graph.o
	${MV} graph.o ${O}graph.o
${O}grid.o:grid.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  grid.c
	${AR} rv ${NYCADMEM} grid.o
	${AR} rv ${NYCADSYS} grid.o
	${MV} grid.o ${O}grid.o
${O}hash.o:hash.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  hash.c
	${AR} rv ${NYCADMEM} hash.o
	${AR} rv ${NYCADSYS} hash.o
	${MV} hash.o ${O}hash.o
${O}heap.o:heap.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  heap.c
	${AR} rv ${NYCADMEM} heap.o
	${AR} rv ${NYCADSYS} heap.o
	${MV} heap.o ${O}heap.o
${O}list.o:list.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  list.c
	${AR} rv ${NYCADMEM} list.o
	${AR} rv ${NYCADSYS} list.o
	${MV} list.o ${O}list.o
${O}log.o:log.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  log.c
	${AR} rv ${NYCADMEM} log.o
	${AR} rv ${NYCADSYS} log.o
	${MV} log.o ${O}log.o
${O}matrix.o:matrix.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  matrix.c
	${AR} rv ${NYCADMEM} matrix.o
	${AR} rv ${NYCADSYS} matrix.o
	${MV} matrix.o ${O}matrix.o
${O}menus.o:menus.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  menus.c
	${AR} rv ${NYCADMEM} menus.o
	${AR} rv ${NYCADSYS} menus.o
	${MV} menus.o ${O}menus.o
${O}message.o:message.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  message.c
	${AR} rv ${NYCADMEM} message.o
	${AR} rv ${NYCADSYS} message.o
	${MV} message.o ${O}message.o
${O}mst.o:mst.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  mst.c
	${AR} rv ${NYCADMEM} mst.o
	${AR} rv ${NYCADSYS} mst.o
	${MV} mst.o ${O}mst.o
${O}mytime.o:mytime.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  mytime.c
	${AR} rv ${NYCADMEM} mytime.o
	${AR} rv ${NYCADSYS} mytime.o
	${MV} mytime.o ${O}mytime.o
# NOTE that okmalloc has been shortened to mem so it will fit using ar.
# the two different version of memory routines
# system version
${O}mem.sys.o:	okmalloc.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c okmalloc.c
	${MV} okmalloc.o mem.sys.o
	${AR} rv ${NYCADSYS} mem.sys.o
	${MV} mem.sys.o ${O}mem.sys.o
# memory manager version
${O}mem.mem.o:	okmalloc.c
	${CC} ${MEMORYFLAG} ${CFLAGS} ${IDIR} ${OPTIONS} -c okmalloc.c
	${MV} okmalloc.o mem.mem.o
	${AR} rv ${NYCADMEM} mem.mem.o
	${MV} mem.mem.o ${O}mem.mem.o
${O}path.o:path.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  path.c
	${AR} rv ${NYCADMEM} path.o
	${AR} rv ${NYCADSYS} path.o
	${MV} path.o ${O}path.o
${O}plot.o:plot.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  plot.c
	${AR} rv ${NYCADMEM} plot.o
	${AR} rv ${NYCADSYS} plot.o
	${MV} plot.o ${O}plot.o
${O}program.o:program.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  program.c
	${AR} rv ${NYCADMEM} program.o
	${AR} rv ${NYCADSYS} program.o
	${MV} program.o ${O}program.o
${O}project.o:project.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  project.c
	${AR} rv ${NYCADMEM} project.o
	${AR} rv ${NYCADSYS} project.o
	${MV} project.o ${O}project.o
${O}queue.o:queue.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  queue.c
	${AR} rv ${NYCADMEM} queue.o
	${AR} rv ${NYCADSYS} queue.o
	${MV} queue.o ${O}queue.o
${O}quicksort.o:quicksort.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  quicksort.c
	${AR} rv ${NYCADMEM} quicksort.o
	${AR} rv ${NYCADSYS} quicksort.o
	${MV} quicksort.o ${O}quicksort.o
${O}rand.o:rand.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  rand.c
	${AR} rv ${NYCADMEM} rand.o
	${AR} rv ${NYCADSYS} rand.o
	${MV} rand.o ${O}rand.o
${O}radixsort.o:radixsort.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  radixsort.c
	${AR} rv ${NYCADMEM} radixsort.o
	${AR} rv ${NYCADSYS} radixsort.o
	${MV} radixsort.o ${O}radixsort.o
${O}rbtree.o:rbtree.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  rbtree.c
	${AR} rv ${NYCADMEM} rbtree.o
	${AR} rv ${NYCADSYS} rbtree.o
	${MV} rbtree.o ${O}rbtree.o
${O}relpath.o:relpath.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  relpath.c
	${AR} rv ${NYCADMEM} relpath.o
	${AR} rv ${NYCADSYS} relpath.o
	${MV} relpath.o ${O}relpath.o
${O}set.o:set.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  set.c
	${AR} rv ${NYCADMEM} set.o
	${AR} rv ${NYCADSYS} set.o
	${MV} set.o ${O}set.o
${O}stat.o:stat.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  stat.c
	${AR} rv ${NYCADMEM} stat.o
	${AR} rv ${NYCADSYS} stat.o
	${MV} stat.o ${O}stat.o
${O}stats.o:stats.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  stats.c
	${AR} rv ${NYCADMEM} stats.o
	${AR} rv ${NYCADSYS} stats.o
	${MV} stats.o ${O}stats.o
${O}string.o:string.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  string.c
	${AR} rv ${NYCADMEM} string.o
	${AR} rv ${NYCADSYS} string.o
	${MV} string.o ${O}string.o
${O}svd.o:svd.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  svd.c
	${AR} rv ${NYCADMEM} svd.o
	${AR} rv ${NYCADSYS} svd.o
	${MV} svd.o ${O}svd.o
${O}system.o:system.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  system.c
	${AR} rv ${NYCADMEM} system.o
	${AR} rv ${NYCADSYS} system.o
	${MV} system.o ${O}system.o
${O}tech.o:tech.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  tech.c
	${AR} rv ${NYCADMEM} tech.o
	${AR} rv ${NYCADSYS} tech.o
	${MV} tech.o ${O}tech.o
${O}time.o:time.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  time.c
	${AR} rv ${NYCADMEM} time.o
	${AR} rv ${NYCADSYS} time.o
	${MV} time.o ${O}time.o
${O}timer.o:timer.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  timer.c
	${AR} rv ${NYCADMEM} timer.o
	${AR} rv ${NYCADSYS} timer.o
	${MV} timer.o ${O}timer.o
${O}trans.o:trans.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  trans.c
	${AR} rv ${NYCADMEM} trans.o
	${AR} rv ${NYCADSYS} trans.o
	${MV} trans.o ${O}trans.o
${O}wgraphics.o:wgraphics.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  wgraphics.c
	${AR} rv ${NYCADMEM} wgraphics.o
	${AR} rv ${NYCADSYS} wgraphics.o
	${MV} wgraphics.o ${O}wgraphics.o
${O}ydebug.o:ydebug.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  ydebug.c
	${AR} rv ${NYCADMEM} ydebug.o
	${AR} rv ${NYCADSYS} ydebug.o
	${MV} ydebug.o ${O}ydebug.o
${O}yreadpar.o:yreadpar.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  yreadpar.c
	${AR} rv ${NYCADMEM} yreadpar.o
	${AR} rv ${NYCADSYS} yreadpar.o
	${MV} yreadpar.o ${O}yreadpar.o
# updating the two archive files 
${NYCADMEM}: ${O}mem.mem.o ${OBJ}
	${RANLIB} ${NYCADMEM}
	${RANLIB} ${NYCADSYS}

${NYCADSYS}: ${O}mem.sys.o ${OBJ}
	${RANLIB} ${NYCADSYS}

# ################### TEST PROGRAMS ##############################
assign.test: assign.c
	${CC} -o assign.test ${CFLAGS} ${IDIR} ${OPTIONS} -DTEST assign.c \
	${NYCADMEM} ../../date/src/date.c

dset.test: dset.c
	${CC} -o dset.test ${CFLAGS} ${IDIR} ${OPTIONS} -DTEST dset.c \
	${NYCADMEM} ../../date/src/date.c

graph.test: graph.c
	${CC} -o graph.test ${CFLAGS} ${IDIR} ${OPTIONS} -DTEST graph.c \
	${NYCADMEM} ../../date/src/date.c -lX11 -lm

list.test: list.c
	${CC} -o list.test ${CFLAGS} ${IDIR} ${OPTIONS} -DTEST list.c \
	${NYCADMEM} ../../date/src/date.c

path.test: path.c
	${CC} -o path.test ${CFLAGS} ${IDIR} ${OPTIONS} -DTEST path.c \
	${NYCADMEM} ../../date/src/date.c

plot.test: plot.c
	${CC} -o plot.test ${CFLAGS} ${IDIR} ${OPTIONS} -DTEST plot.c \
	${NYCADMEM} ../../date/src/date.c

radixsort.test: radixsort.c
	${CC} -o radixsort.test ${CFLAGS} ${IDIR} ${OPTIONS} -DTEST radixsort.c \
	${NYCADMEM} ../../date/src/date.c

rand.test: rand.c
	${CC} -o rand.test ${CFLAGS} ${IDIR} ${OPTIONS} -DTEST rand.c \
	${NYCADMEM} ../../date/src/date.c

rbtree.test: rbtree.c
	${CC} -o rbtree.test ${CFLAGS} ${IDIR} ${OPTIONS} -DTEST rbtree.c \
	${NYCADMEM} ../../date/src/date.c

slist.test: slist.c
	${CC} -o slist.test ${CFLAGS} ${IDIR} ${OPTIONS} -DTEST slist.c \
	${NYCADMEM} ../../date/src/date.c

stats.test: stats.c
	${CC} -o stats.test ${CFLAGS} ${IDIR} ${OPTIONS} -DTEST stats.c \
	${NYCADMEM} ../../date/src/date.c

svd.test: svd.c
	${CC} -o svd.test ${CFLAGS} ${IDIR} ${OPTIONS} -DTEST svd.c \
	${NYCADMEM} ../../date/src/date.c -lm

mem.test: okmalloc.c
	${CC} -o mem.test ${CFLAGS} ${IDIR} ${OPTIONS} \
	-DTEST -DMEM_DEBUG okmalloc.c \
	libycad.mem-d.a ../../date/src/date.c -lm

# end makefile
# DO NOT DELETE

assign.o: ../../../include/yalecad/base.h /usr/include/stdio.h
assign.o: /usr/include/features.h /usr/include/sys/cdefs.h
assign.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
assign.o: /usr/include/gnu/stubs-64.h
assign.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
assign.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
assign.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
assign.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
assign.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
assign.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
assign.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
assign.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
assign.o: /usr/include/sys/types.h /usr/include/time.h
assign.o: /usr/include/sys/select.h /usr/include/bits/select.h
assign.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
assign.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
assign.o: /usr/include/alloca.h /usr/include/math.h
assign.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
assign.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
assign.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
assign.o: /usr/include/bits/mathcalls.h
assign.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
assign.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
assign.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
assign.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
assign.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
assign.o: ../../../include/yalecad/message.h
assign.o: ../../../include/yalecad/program.h
assign.o: ../../../include/yalecad/assign.h ../../../include/yalecad/debug.h
buster.o: ../../../include/yalecad/base.h /usr/include/stdio.h
buster.o: /usr/include/features.h /usr/include/sys/cdefs.h
buster.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
buster.o: /usr/include/gnu/stubs-64.h
buster.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
buster.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
buster.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
buster.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
buster.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
buster.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
buster.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
buster.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
buster.o: /usr/include/sys/types.h /usr/include/time.h
buster.o: /usr/include/sys/select.h /usr/include/bits/select.h
buster.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
buster.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
buster.o: /usr/include/alloca.h /usr/include/math.h
buster.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
buster.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
buster.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
buster.o: /usr/include/bits/mathcalls.h
buster.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
buster.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
buster.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
buster.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
buster.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
buster.o: ../../../include/yalecad/buster.h ../../../include/yalecad/debug.h
buster.o: ../../../include/yalecad/message.h
cleanup.o: ../../../include/yalecad/cleanup.h
colors.o: ../../../include/yalecad/base.h /usr/include/stdio.h
colors.o: /usr/include/features.h /usr/include/sys/cdefs.h
colors.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
colors.o: /usr/include/gnu/stubs-64.h
colors.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
colors.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
colors.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
colors.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
colors.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
colors.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
colors.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
colors.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
colors.o: /usr/include/sys/types.h /usr/include/time.h
colors.o: /usr/include/sys/select.h /usr/include/bits/select.h
colors.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
colors.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
colors.o: /usr/include/alloca.h /usr/include/math.h
colors.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
colors.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
colors.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
colors.o: /usr/include/bits/mathcalls.h
colors.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
colors.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
colors.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
colors.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
colors.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
deck.o: ../../../include/yalecad/deck.h ../../../include/yalecad/base.h
deck.o: /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h
deck.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
deck.o: /usr/include/gnu/stubs-64.h
deck.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
deck.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
deck.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
deck.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
deck.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
deck.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
deck.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
deck.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
deck.o: /usr/include/sys/types.h /usr/include/time.h
deck.o: /usr/include/sys/select.h /usr/include/bits/select.h
deck.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
deck.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
deck.o: /usr/include/alloca.h /usr/include/math.h
deck.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
deck.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
deck.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
deck.o: /usr/include/bits/mathcalls.h
deck.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
deck.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
deck.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
deck.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
deck.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
deck.o: ../../../include/yalecad/message.h
dialog.o: /usr/include/stdio.h /usr/include/features.h
dialog.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
dialog.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
dialog.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
dialog.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
dialog.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
dialog.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
dialog.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
dialog.o: /usr/include/string.h /usr/include/xlocale.h
dialog.o: /usr/include/X11/Xlib.h /usr/include/sys/types.h
dialog.o: /usr/include/time.h /usr/include/endian.h
dialog.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
dialog.o: /usr/include/sys/select.h /usr/include/bits/select.h
dialog.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
dialog.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
dialog.o: /usr/include/X11/X.h /usr/include/X11/Xfuncproto.h
dialog.o: /usr/include/X11/Xosdefs.h /usr/include/X11/Xatom.h
dialog.o: /usr/include/X11/Xutil.h /usr/include/X11/keysym.h
dialog.o: /usr/include/X11/keysymdef.h /usr/include/X11/cursorfont.h
dialog.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
dialog.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
dialog.o: /usr/include/alloca.h /usr/include/math.h
dialog.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
dialog.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
dialog.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
dialog.o: /usr/include/bits/mathcalls.h
dialog.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
dialog.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
dialog.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
dialog.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
dialog.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
dialog.o: ../../../include/yalecad/file.h ../../../include/yalecad/colors.h
dialog.o: ../../../include/yalecad/message.h ../../../include/yalecad/hash.h
dialog.o: ../../../include/yalecad/string.h ../../../include/yalecad/debug.h
dialog.o: ../../../include/yalecad/draw.h ../../../include/yalecad/dialog.h
dialog.o: info.h
draw.o: /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h
draw.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
draw.o: /usr/include/gnu/stubs-64.h
draw.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
draw.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
draw.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
draw.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
draw.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
draw.o: /usr/include/string.h /usr/include/xlocale.h /usr/include/X11/Xlib.h
draw.o: /usr/include/sys/types.h /usr/include/time.h /usr/include/endian.h
draw.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
draw.o: /usr/include/sys/select.h /usr/include/bits/select.h
draw.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
draw.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
draw.o: /usr/include/X11/X.h /usr/include/X11/Xfuncproto.h
draw.o: /usr/include/X11/Xosdefs.h /usr/include/X11/Xatom.h
draw.o: /usr/include/X11/Xutil.h /usr/include/X11/keysym.h
draw.o: /usr/include/X11/keysymdef.h ../../../include/yalecad/base.h
draw.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
draw.o: /usr/include/bits/waitstatus.h /usr/include/alloca.h
draw.o: /usr/include/math.h /usr/include/bits/huge_val.h
draw.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
draw.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
draw.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
draw.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
draw.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
draw.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
draw.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
draw.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
draw.o: ../../../include/yalecad/file.h ../../../include/yalecad/message.h
draw.o: ../../../include/yalecad/hash.h ../../../include/yalecad/string.h
draw.o: ../../../include/yalecad/draw.h ../../../include/yalecad/debug.h
draw.o: ../../../include/yalecad/buster.h ../../../include/yalecad/dbinary.h
draw.o: ../../../include/yalecad/project.h info.h
dset.o: ../../../include/yalecad/base.h /usr/include/stdio.h
dset.o: /usr/include/features.h /usr/include/sys/cdefs.h
dset.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
dset.o: /usr/include/gnu/stubs-64.h
dset.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
dset.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
dset.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
dset.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
dset.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
dset.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
dset.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
dset.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
dset.o: /usr/include/sys/types.h /usr/include/time.h
dset.o: /usr/include/sys/select.h /usr/include/bits/select.h
dset.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
dset.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
dset.o: /usr/include/alloca.h /usr/include/math.h
dset.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
dset.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
dset.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
dset.o: /usr/include/bits/mathcalls.h
dset.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
dset.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
dset.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
dset.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
dset.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
dset.o: ../../../include/yalecad/debug.h ../../../include/yalecad/message.h
dset.o: ../../../include/yalecad/rbtree.h ../../../include/yalecad/dset.h
edcolors.o: /usr/include/stdio.h /usr/include/features.h
edcolors.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
edcolors.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
edcolors.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
edcolors.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
edcolors.o: /usr/include/libio.h /usr/include/_G_config.h
edcolors.o: /usr/include/wchar.h
edcolors.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
edcolors.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
edcolors.o: /usr/include/X11/Xlib.h /usr/include/sys/types.h
edcolors.o: /usr/include/time.h /usr/include/endian.h
edcolors.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
edcolors.o: /usr/include/sys/select.h /usr/include/bits/select.h
edcolors.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
edcolors.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
edcolors.o: /usr/include/X11/X.h /usr/include/X11/Xfuncproto.h
edcolors.o: /usr/include/X11/Xosdefs.h /usr/include/X11/Xatom.h
edcolors.o: /usr/include/X11/Xutil.h /usr/include/X11/keysym.h
edcolors.o: /usr/include/X11/keysymdef.h ../../../include/yalecad/base.h
edcolors.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
edcolors.o: /usr/include/bits/waitstatus.h /usr/include/alloca.h
edcolors.o: /usr/include/math.h /usr/include/bits/huge_val.h
edcolors.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
edcolors.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
edcolors.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
edcolors.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
edcolors.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
edcolors.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
edcolors.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
edcolors.o: /usr/include/bits/posix2_lim.h
edcolors.o: ../../../include/yalecad/okmalloc.h
edcolors.o: ../../../include/yalecad/dialog.h
edcolors.o: ../../../include/yalecad/colors.h ../../../include/yalecad/draw.h
edcolors.o: ../../../include/yalecad/string.h info.h
file.o: /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h
file.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
file.o: /usr/include/gnu/stubs-64.h
file.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
file.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
file.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
file.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
file.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
file.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
file.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
file.o: /usr/include/endian.h /usr/include/bits/endian.h
file.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
file.o: /usr/include/time.h /usr/include/sys/select.h
file.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
file.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
file.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
file.o: /usr/include/math.h /usr/include/bits/huge_val.h
file.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
file.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
file.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
file.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
file.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
file.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
file.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
file.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
file.o: ../../../include/yalecad/file.h ../../../include/yalecad/message.h
file.o: /usr/include/sys/stat.h /usr/include/bits/stat.h
file.o: /usr/include/sys/dir.h /usr/include/dirent.h
file.o: /usr/include/bits/dirent.h /usr/include/sys/file.h
file.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
getftime.o: ../../../include/yalecad/base.h /usr/include/stdio.h
getftime.o: /usr/include/features.h /usr/include/sys/cdefs.h
getftime.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
getftime.o: /usr/include/gnu/stubs-64.h
getftime.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
getftime.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
getftime.o: /usr/include/libio.h /usr/include/_G_config.h
getftime.o: /usr/include/wchar.h
getftime.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
getftime.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
getftime.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
getftime.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
getftime.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
getftime.o: /usr/include/sys/types.h /usr/include/time.h
getftime.o: /usr/include/sys/select.h /usr/include/bits/select.h
getftime.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
getftime.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
getftime.o: /usr/include/alloca.h /usr/include/math.h
getftime.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
getftime.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
getftime.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
getftime.o: /usr/include/bits/mathcalls.h
getftime.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
getftime.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
getftime.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
getftime.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
getftime.o: /usr/include/bits/posix2_lim.h
getftime.o: ../../../include/yalecad/okmalloc.h
getftime.o: ../../../include/yalecad/debug.h
getftime.o: ../../../include/yalecad/message.h /usr/include/sys/stat.h
getftime.o: /usr/include/bits/stat.h
graph.o: ../../../include/yalecad/base.h /usr/include/stdio.h
graph.o: /usr/include/features.h /usr/include/sys/cdefs.h
graph.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
graph.o: /usr/include/gnu/stubs-64.h
graph.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
graph.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
graph.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
graph.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
graph.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
graph.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
graph.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
graph.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
graph.o: /usr/include/sys/types.h /usr/include/time.h
graph.o: /usr/include/sys/select.h /usr/include/bits/select.h
graph.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
graph.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
graph.o: /usr/include/alloca.h /usr/include/math.h
graph.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
graph.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
graph.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
graph.o: /usr/include/bits/mathcalls.h
graph.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
graph.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
graph.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
graph.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
graph.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
graph.o: ../../../include/yalecad/colors.h ../../../include/yalecad/debug.h
graph.o: ../../../include/yalecad/message.h ../../../include/yalecad/deck.h
graph.o: ../../../include/yalecad/draw.h ../../../include/yalecad/dset.h
graph.o: ../../../include/yalecad/rbtree.h ../../../include/yalecad/heap.h
graph.o: ../../../include/yalecad/graph.h
grid.o: ../../../include/yalecad/base.h /usr/include/stdio.h
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
hash.o: /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h
hash.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
hash.o: /usr/include/gnu/stubs-64.h
hash.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
hash.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
hash.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
hash.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
hash.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
hash.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
hash.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
hash.o: /usr/include/endian.h /usr/include/bits/endian.h
hash.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
hash.o: /usr/include/time.h /usr/include/sys/select.h
hash.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
hash.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
hash.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
hash.o: /usr/include/math.h /usr/include/bits/huge_val.h
hash.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
hash.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
hash.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
hash.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
hash.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
hash.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
hash.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
hash.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
hash.o: ../../../include/yalecad/hash.h ../../../include/yalecad/debug.h
hash.o: ../../../include/yalecad/message.h
heap.o: ../../../include/yalecad/heap.h ../../../include/yalecad/base.h
heap.o: /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h
heap.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
heap.o: /usr/include/gnu/stubs-64.h
heap.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
heap.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
heap.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
heap.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
heap.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
heap.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
heap.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
heap.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
heap.o: /usr/include/sys/types.h /usr/include/time.h
heap.o: /usr/include/sys/select.h /usr/include/bits/select.h
heap.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
heap.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
heap.o: /usr/include/alloca.h /usr/include/math.h
heap.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
heap.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
heap.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
heap.o: /usr/include/bits/mathcalls.h
heap.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
heap.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
heap.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
heap.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
heap.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
list.o: ../../../include/yalecad/list.h ../../../include/yalecad/base.h
list.o: /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h
list.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
list.o: /usr/include/gnu/stubs-64.h
list.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
list.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
list.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
list.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
list.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
list.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
list.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
list.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
list.o: /usr/include/sys/types.h /usr/include/time.h
list.o: /usr/include/sys/select.h /usr/include/bits/select.h
list.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
list.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
list.o: /usr/include/alloca.h /usr/include/math.h
list.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
list.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
list.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
list.o: /usr/include/bits/mathcalls.h
list.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
list.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
list.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
list.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
list.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
log.o: /usr/include/string.h /usr/include/features.h /usr/include/sys/cdefs.h
log.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
log.o: /usr/include/gnu/stubs-64.h
log.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
log.o: /usr/include/xlocale.h ../../../include/yalecad/base.h
log.o: /usr/include/stdio.h /usr/include/bits/types.h
log.o: /usr/include/bits/typesizes.h /usr/include/libio.h
log.o: /usr/include/_G_config.h /usr/include/wchar.h
log.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
log.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
log.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
log.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
log.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
log.o: /usr/include/sys/types.h /usr/include/time.h /usr/include/sys/select.h
log.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
log.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
log.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
log.o: /usr/include/math.h /usr/include/bits/huge_val.h
log.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
log.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
log.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
log.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
log.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
log.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
log.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
log.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
log.o: ../../../include/yalecad/message.h ../../../include/yalecad/file.h
matrix.o: ../../../include/yalecad/base.h /usr/include/stdio.h
matrix.o: /usr/include/features.h /usr/include/sys/cdefs.h
matrix.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
matrix.o: /usr/include/gnu/stubs-64.h
matrix.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
matrix.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
matrix.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
matrix.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
matrix.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
matrix.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
matrix.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
matrix.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
matrix.o: /usr/include/sys/types.h /usr/include/time.h
matrix.o: /usr/include/sys/select.h /usr/include/bits/select.h
matrix.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
matrix.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
matrix.o: /usr/include/alloca.h /usr/include/math.h
matrix.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
matrix.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
matrix.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
matrix.o: /usr/include/bits/mathcalls.h
matrix.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
matrix.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
matrix.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
matrix.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
matrix.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
matrix.o: ../../../include/yalecad/message.h ../../../include/yalecad/debug.h
matrix.o: ../../../include/yalecad/linalg.h
menus.o: /usr/include/stdio.h /usr/include/features.h
menus.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
menus.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
menus.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
menus.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
menus.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
menus.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
menus.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
menus.o: /usr/include/string.h /usr/include/xlocale.h /usr/include/X11/Xlib.h
menus.o: /usr/include/sys/types.h /usr/include/time.h /usr/include/endian.h
menus.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
menus.o: /usr/include/sys/select.h /usr/include/bits/select.h
menus.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
menus.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
menus.o: /usr/include/X11/X.h /usr/include/X11/Xfuncproto.h
menus.o: /usr/include/X11/Xosdefs.h /usr/include/X11/Xatom.h
menus.o: /usr/include/X11/Xutil.h /usr/include/X11/keysym.h
menus.o: /usr/include/X11/keysymdef.h ../../../include/yalecad/base.h
menus.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
menus.o: /usr/include/bits/waitstatus.h /usr/include/alloca.h
menus.o: /usr/include/math.h /usr/include/bits/huge_val.h
menus.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
menus.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
menus.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
menus.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
menus.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
menus.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
menus.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
menus.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
menus.o: ../../../include/yalecad/file.h ../../../include/yalecad/message.h
menus.o: ../../../include/yalecad/hash.h ../../../include/yalecad/string.h
menus.o: ../../../include/yalecad/debug.h ../../../include/yalecad/draw.h
menus.o: ../../../include/yalecad/colors.h info.h /usr/include/ctype.h
message.o: /usr/include/stdio.h /usr/include/features.h
message.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
message.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
message.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
message.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
message.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
message.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
message.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
message.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
message.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
message.o: /usr/include/endian.h /usr/include/bits/endian.h
message.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
message.o: /usr/include/time.h /usr/include/sys/select.h
message.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
message.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
message.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
message.o: /usr/include/math.h /usr/include/bits/huge_val.h
message.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
message.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
message.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
message.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
message.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
message.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
message.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
message.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
message.o: ../../../include/yalecad/message.h ../../../include/yalecad/file.h
mst.o: ../../../include/yalecad/base.h /usr/include/stdio.h
mst.o: /usr/include/features.h /usr/include/sys/cdefs.h
mst.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
mst.o: /usr/include/gnu/stubs-64.h
mst.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
mst.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
mst.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
mst.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
mst.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
mst.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
mst.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
mst.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
mst.o: /usr/include/sys/types.h /usr/include/time.h /usr/include/sys/select.h
mst.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
mst.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
mst.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
mst.o: /usr/include/math.h /usr/include/bits/huge_val.h
mst.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
mst.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
mst.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
mst.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
mst.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
mst.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
mst.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
mst.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
mst.o: ../../../include/yalecad/debug.h ../../../include/yalecad/message.h
mst.o: ../../../include/yalecad/draw.h ../../../include/yalecad/colors.h
mytime.o: ../../../include/yalecad/base.h /usr/include/stdio.h
mytime.o: /usr/include/features.h /usr/include/sys/cdefs.h
mytime.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
mytime.o: /usr/include/gnu/stubs-64.h
mytime.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
mytime.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
mytime.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
mytime.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
mytime.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
mytime.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
mytime.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
mytime.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
mytime.o: /usr/include/sys/types.h /usr/include/time.h
mytime.o: /usr/include/sys/select.h /usr/include/bits/select.h
mytime.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
mytime.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
mytime.o: /usr/include/alloca.h /usr/include/math.h
mytime.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
mytime.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
mytime.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
mytime.o: /usr/include/bits/mathcalls.h
mytime.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
mytime.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
mytime.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
mytime.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
mytime.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
mytime.o: /usr/include/sys/time.h
okmalloc.o: /usr/include/stdio.h /usr/include/features.h
okmalloc.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
okmalloc.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
okmalloc.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
okmalloc.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
okmalloc.o: /usr/include/libio.h /usr/include/_G_config.h
okmalloc.o: /usr/include/wchar.h
okmalloc.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
okmalloc.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
okmalloc.o: /usr/include/unistd.h /usr/include/bits/posix_opt.h
okmalloc.o: /usr/include/bits/environments.h /usr/include/bits/confname.h
okmalloc.o: /usr/include/getopt.h /usr/include/signal.h
okmalloc.o: /usr/include/bits/sigset.h /usr/include/bits/signum.h
okmalloc.o: /usr/include/time.h /usr/include/bits/siginfo.h
okmalloc.o: /usr/include/bits/sigaction.h /usr/include/bits/sigcontext.h
okmalloc.o: /usr/include/bits/sigstack.h /usr/include/sys/ucontext.h
okmalloc.o: /usr/include/bits/pthreadtypes.h /usr/include/bits/sigthread.h
okmalloc.o: /usr/include/errno.h /usr/include/bits/errno.h
okmalloc.o: /usr/include/linux/errno.h /usr/include/asm/errno.h
okmalloc.o: /usr/include/asm-generic/errno.h
okmalloc.o: /usr/include/asm-generic/errno-base.h
okmalloc.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
okmalloc.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
okmalloc.o: /usr/include/endian.h /usr/include/bits/endian.h
okmalloc.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
okmalloc.o: /usr/include/sys/select.h /usr/include/bits/select.h
okmalloc.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
okmalloc.o: /usr/include/alloca.h /usr/include/math.h
okmalloc.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
okmalloc.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
okmalloc.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
okmalloc.o: /usr/include/bits/mathcalls.h
okmalloc.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
okmalloc.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
okmalloc.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
okmalloc.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
okmalloc.o: /usr/include/bits/posix2_lim.h
okmalloc.o: ../../../include/yalecad/okmalloc.h
okmalloc.o: ../../../include/yalecad/message.h
path.o: /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h
path.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
path.o: /usr/include/gnu/stubs-64.h
path.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
path.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
path.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
path.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
path.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
path.o: /usr/include/unistd.h /usr/include/bits/posix_opt.h
path.o: /usr/include/bits/environments.h /usr/include/bits/confname.h
path.o: /usr/include/getopt.h /usr/include/string.h /usr/include/xlocale.h
path.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
path.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
path.o: /usr/include/endian.h /usr/include/bits/endian.h
path.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
path.o: /usr/include/time.h /usr/include/sys/select.h
path.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
path.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
path.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
path.o: /usr/include/math.h /usr/include/bits/huge_val.h
path.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
path.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
path.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
path.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
path.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
path.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
path.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
path.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
path.o: ../../../include/yalecad/string.h /usr/include/pwd.h
plot.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
plot.o: /usr/include/string.h /usr/include/features.h
plot.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
plot.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
plot.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
plot.o: /usr/include/xlocale.h ../../../include/yalecad/base.h
plot.o: /usr/include/stdio.h /usr/include/bits/types.h
plot.o: /usr/include/bits/typesizes.h /usr/include/libio.h
plot.o: /usr/include/_G_config.h /usr/include/wchar.h
plot.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
plot.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
plot.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
plot.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
plot.o: /usr/include/sys/types.h /usr/include/time.h
plot.o: /usr/include/sys/select.h /usr/include/bits/select.h
plot.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
plot.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
plot.o: /usr/include/alloca.h /usr/include/math.h
plot.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
plot.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
plot.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
plot.o: /usr/include/bits/mathcalls.h
plot.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
plot.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
plot.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
plot.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
plot.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
plot.o: ../../../include/yalecad/debug.h ../../../include/yalecad/message.h
plot.o: ../../../include/yalecad/file.h ../../../include/yalecad/string.h
program.o: ../../../include/yalecad/base.h /usr/include/stdio.h
program.o: /usr/include/features.h /usr/include/sys/cdefs.h
program.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
program.o: /usr/include/gnu/stubs-64.h
program.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
program.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
program.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
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
program.o: ../../../include/yalecad/program.h
project.o: ../../../include/yalecad/base.h /usr/include/stdio.h
project.o: /usr/include/features.h /usr/include/sys/cdefs.h
project.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
project.o: /usr/include/gnu/stubs-64.h
project.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
project.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
project.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
project.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
project.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
project.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
project.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
project.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
project.o: /usr/include/sys/types.h /usr/include/time.h
project.o: /usr/include/sys/select.h /usr/include/bits/select.h
project.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
project.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
project.o: /usr/include/alloca.h /usr/include/math.h
project.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
project.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
project.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
project.o: /usr/include/bits/mathcalls.h
project.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
project.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
project.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
project.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
project.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
project.o: ../../../include/yalecad/project.h
queue.o: /usr/include/stdio.h /usr/include/features.h
queue.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
queue.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
queue.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
queue.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
queue.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
queue.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
queue.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
queue.o: ../../../include/yalecad/queue.h ../../../include/yalecad/base.h
queue.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
queue.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
queue.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
queue.o: /usr/include/sys/types.h /usr/include/time.h
queue.o: /usr/include/sys/select.h /usr/include/bits/select.h
queue.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
queue.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
queue.o: /usr/include/alloca.h /usr/include/math.h
queue.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
queue.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
queue.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
queue.o: /usr/include/bits/mathcalls.h
queue.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
queue.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
queue.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
queue.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
queue.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
quicksort.o: ../../../include/yalecad/base.h /usr/include/stdio.h
quicksort.o: /usr/include/features.h /usr/include/sys/cdefs.h
quicksort.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
quicksort.o: /usr/include/gnu/stubs-64.h
quicksort.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
quicksort.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
quicksort.o: /usr/include/libio.h /usr/include/_G_config.h
quicksort.o: /usr/include/wchar.h
quicksort.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
quicksort.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
quicksort.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
quicksort.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
quicksort.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
quicksort.o: /usr/include/sys/types.h /usr/include/time.h
quicksort.o: /usr/include/sys/select.h /usr/include/bits/select.h
quicksort.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
quicksort.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
quicksort.o: /usr/include/alloca.h /usr/include/math.h
quicksort.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
quicksort.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
quicksort.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
quicksort.o: /usr/include/bits/mathcalls.h
quicksort.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
quicksort.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
quicksort.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
quicksort.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
quicksort.o: /usr/include/bits/posix2_lim.h
quicksort.o: ../../../include/yalecad/okmalloc.h
radixsort.o: /usr/include/string.h /usr/include/features.h
radixsort.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
radixsort.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
radixsort.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
radixsort.o: /usr/include/xlocale.h ../../../include/yalecad/base.h
radixsort.o: /usr/include/stdio.h /usr/include/bits/types.h
radixsort.o: /usr/include/bits/typesizes.h /usr/include/libio.h
radixsort.o: /usr/include/_G_config.h /usr/include/wchar.h
radixsort.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
radixsort.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
radixsort.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
radixsort.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
radixsort.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
radixsort.o: /usr/include/sys/types.h /usr/include/time.h
radixsort.o: /usr/include/sys/select.h /usr/include/bits/select.h
radixsort.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
radixsort.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
radixsort.o: /usr/include/alloca.h /usr/include/math.h
radixsort.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
radixsort.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
radixsort.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
radixsort.o: /usr/include/bits/mathcalls.h
radixsort.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
radixsort.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
radixsort.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
radixsort.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
radixsort.o: /usr/include/bits/posix2_lim.h
radixsort.o: ../../../include/yalecad/okmalloc.h
rand.o: ../../../include/yalecad/base.h /usr/include/stdio.h
rand.o: /usr/include/features.h /usr/include/sys/cdefs.h
rand.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
rand.o: /usr/include/gnu/stubs-64.h
rand.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
rand.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
rand.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
rand.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
rand.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
rand.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
rand.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
rand.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
rand.o: /usr/include/sys/types.h /usr/include/time.h
rand.o: /usr/include/sys/select.h /usr/include/bits/select.h
rand.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
rand.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
rand.o: /usr/include/alloca.h /usr/include/math.h
rand.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
rand.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
rand.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
rand.o: /usr/include/bits/mathcalls.h
rand.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
rand.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
rand.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
rand.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
rand.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
rand.o: ../../../include/yalecad/debug.h ../../../include/yalecad/message.h
rbtree.o: ../../../include/yalecad/base.h /usr/include/stdio.h
rbtree.o: /usr/include/features.h /usr/include/sys/cdefs.h
rbtree.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
rbtree.o: /usr/include/gnu/stubs-64.h
rbtree.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
rbtree.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
rbtree.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
rbtree.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
rbtree.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
rbtree.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
rbtree.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
rbtree.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
rbtree.o: /usr/include/sys/types.h /usr/include/time.h
rbtree.o: /usr/include/sys/select.h /usr/include/bits/select.h
rbtree.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
rbtree.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
rbtree.o: /usr/include/alloca.h /usr/include/math.h
rbtree.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
rbtree.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
rbtree.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
rbtree.o: /usr/include/bits/mathcalls.h
rbtree.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
rbtree.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
rbtree.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
rbtree.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
rbtree.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
rbtree.o: ../../../include/yalecad/debug.h ../../../include/yalecad/message.h
rbtree.o: ../../../include/yalecad/deck.h ../../../include/yalecad/rbtree.h
relpath.o: /usr/include/string.h /usr/include/features.h
relpath.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
relpath.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
relpath.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
relpath.o: /usr/include/xlocale.h ../../../include/yalecad/base.h
relpath.o: /usr/include/stdio.h /usr/include/bits/types.h
relpath.o: /usr/include/bits/typesizes.h /usr/include/libio.h
relpath.o: /usr/include/_G_config.h /usr/include/wchar.h
relpath.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
relpath.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
relpath.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
relpath.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
relpath.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
relpath.o: /usr/include/sys/types.h /usr/include/time.h
relpath.o: /usr/include/sys/select.h /usr/include/bits/select.h
relpath.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
relpath.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
relpath.o: /usr/include/alloca.h /usr/include/math.h
relpath.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
relpath.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
relpath.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
relpath.o: /usr/include/bits/mathcalls.h
relpath.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
relpath.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
relpath.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
relpath.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
relpath.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
relpath.o: ../../../include/yalecad/string.h
set.o: ../../../include/yalecad/base.h /usr/include/stdio.h
set.o: /usr/include/features.h /usr/include/sys/cdefs.h
set.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
set.o: /usr/include/gnu/stubs-64.h
set.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
set.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
set.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
set.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
set.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
set.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
set.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
set.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
set.o: /usr/include/sys/types.h /usr/include/time.h /usr/include/sys/select.h
set.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
set.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
set.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
set.o: /usr/include/math.h /usr/include/bits/huge_val.h
set.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
set.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
set.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
set.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
set.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
set.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
set.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
set.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
set.o: ../../../include/yalecad/debug.h ../../../include/yalecad/message.h
set.o: ../../../include/yalecad/set.h
stat.o: ../../../include/yalecad/base.h /usr/include/stdio.h
stat.o: /usr/include/features.h /usr/include/sys/cdefs.h
stat.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
stat.o: /usr/include/gnu/stubs-64.h
stat.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
stat.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
stat.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
stat.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
stat.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
stat.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
stat.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
stat.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
stat.o: /usr/include/sys/types.h /usr/include/time.h
stat.o: /usr/include/sys/select.h /usr/include/bits/select.h
stat.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
stat.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
stat.o: /usr/include/alloca.h /usr/include/math.h
stat.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
stat.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
stat.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
stat.o: /usr/include/bits/mathcalls.h
stat.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
stat.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
stat.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
stat.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
stat.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
stats.o: ../../../include/yalecad/base.h /usr/include/stdio.h
stats.o: /usr/include/features.h /usr/include/sys/cdefs.h
stats.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
stats.o: /usr/include/gnu/stubs-64.h
stats.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
stats.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
stats.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
stats.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
stats.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
stats.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
stats.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
stats.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
stats.o: /usr/include/sys/types.h /usr/include/time.h
stats.o: /usr/include/sys/select.h /usr/include/bits/select.h
stats.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
stats.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
stats.o: /usr/include/alloca.h /usr/include/math.h
stats.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
stats.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
stats.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
stats.o: /usr/include/bits/mathcalls.h
stats.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
stats.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
stats.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
stats.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
stats.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
stats.o: /usr/include/sys/time.h /usr/include/sys/resource.h
stats.o: /usr/include/bits/resource.h
string.o: /usr/include/string.h /usr/include/features.h
string.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
string.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
string.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
string.o: /usr/include/xlocale.h ../../../include/yalecad/base.h
string.o: /usr/include/stdio.h /usr/include/bits/types.h
string.o: /usr/include/bits/typesizes.h /usr/include/libio.h
string.o: /usr/include/_G_config.h /usr/include/wchar.h
string.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
string.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
string.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
string.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
string.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
string.o: /usr/include/sys/types.h /usr/include/time.h
string.o: /usr/include/sys/select.h /usr/include/bits/select.h
string.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
string.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
string.o: /usr/include/alloca.h /usr/include/math.h
string.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
string.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
string.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
string.o: /usr/include/bits/mathcalls.h
string.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
string.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
string.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
string.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
string.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
string.o: ../../../include/yalecad/string.h
svd.o: ../../../include/yalecad/base.h /usr/include/stdio.h
svd.o: /usr/include/features.h /usr/include/sys/cdefs.h
svd.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
svd.o: /usr/include/gnu/stubs-64.h
svd.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
svd.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
svd.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
svd.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
svd.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
svd.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
svd.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
svd.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
svd.o: /usr/include/sys/types.h /usr/include/time.h /usr/include/sys/select.h
svd.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
svd.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
svd.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
svd.o: /usr/include/math.h /usr/include/bits/huge_val.h
svd.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
svd.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
svd.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
svd.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
svd.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
svd.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
svd.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
svd.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
svd.o: ../../../include/yalecad/message.h ../../../include/yalecad/debug.h
svd.o: ../../../include/yalecad/linalg.h
system.o: ../../../include/yalecad/file.h ../../../include/yalecad/base.h
system.o: /usr/include/stdio.h /usr/include/features.h
system.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
system.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
system.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
system.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
system.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
system.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
system.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
system.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
system.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
system.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
system.o: /usr/include/sys/types.h /usr/include/time.h
system.o: /usr/include/sys/select.h /usr/include/bits/select.h
system.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
system.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
system.o: /usr/include/alloca.h /usr/include/math.h
system.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
system.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
system.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
system.o: /usr/include/bits/mathcalls.h
system.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
system.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
system.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
system.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
system.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
system.o: ../../../include/yalecad/message.h
time.o: /usr/include/time.h /usr/include/bits/types.h /usr/include/features.h
time.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
time.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
time.o: /usr/include/bits/typesizes.h ../../../include/yalecad/base.h
time.o: /usr/include/stdio.h
time.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
time.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
time.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
time.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
time.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
time.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
time.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
time.o: /usr/include/sys/types.h /usr/include/sys/select.h
time.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
time.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
time.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
time.o: /usr/include/math.h /usr/include/bits/huge_val.h
time.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
time.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
time.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
time.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
time.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
time.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
time.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
time.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
timer.o: ../../../include/yalecad/base.h /usr/include/stdio.h
timer.o: /usr/include/features.h /usr/include/sys/cdefs.h
timer.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
timer.o: /usr/include/gnu/stubs-64.h
timer.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
timer.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
timer.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
timer.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
timer.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
timer.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
timer.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
timer.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
timer.o: /usr/include/sys/types.h /usr/include/time.h
timer.o: /usr/include/sys/select.h /usr/include/bits/select.h
timer.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
timer.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
timer.o: /usr/include/alloca.h /usr/include/math.h
timer.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
timer.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
timer.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
timer.o: /usr/include/bits/mathcalls.h
timer.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
timer.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
timer.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
timer.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
timer.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
timer.o: /usr/include/sys/timeb.h
trans.o: ../../../include/yalecad/base.h /usr/include/stdio.h
trans.o: /usr/include/features.h /usr/include/sys/cdefs.h
trans.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
trans.o: /usr/include/gnu/stubs-64.h
trans.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
trans.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
trans.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
trans.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
trans.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
trans.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
trans.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
trans.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
trans.o: /usr/include/sys/types.h /usr/include/time.h
trans.o: /usr/include/sys/select.h /usr/include/bits/select.h
trans.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
trans.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
trans.o: /usr/include/alloca.h /usr/include/math.h
trans.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
trans.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
trans.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
trans.o: /usr/include/bits/mathcalls.h
trans.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
trans.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
trans.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
trans.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
trans.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
trans.o: ../../../include/yalecad/relpos.h ../../../include/yalecad/message.h
wgraphics.o: /usr/include/stdio.h /usr/include/features.h
wgraphics.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
wgraphics.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
wgraphics.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
wgraphics.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
wgraphics.o: /usr/include/libio.h /usr/include/_G_config.h
wgraphics.o: /usr/include/wchar.h
wgraphics.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
wgraphics.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
wgraphics.o: /usr/include/string.h /usr/include/xlocale.h
wgraphics.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
wgraphics.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
wgraphics.o: /usr/include/endian.h /usr/include/bits/endian.h
wgraphics.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
wgraphics.o: /usr/include/time.h /usr/include/sys/select.h
wgraphics.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
wgraphics.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
wgraphics.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
wgraphics.o: /usr/include/math.h /usr/include/bits/huge_val.h
wgraphics.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
wgraphics.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
wgraphics.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
wgraphics.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
wgraphics.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
wgraphics.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
wgraphics.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
wgraphics.o: /usr/include/bits/posix2_lim.h
wgraphics.o: ../../../include/yalecad/okmalloc.h
wgraphics.o: ../../../include/yalecad/file.h
wgraphics.o: ../../../include/yalecad/message.h
wgraphics.o: ../../../include/yalecad/debug.h
wgraphics.o: ../../../include/yalecad/dbinary.h
wgraphics.o: ../../../include/yalecad/wgraphics.h
wgraphics.o: ../../../include/yalecad/string.h
ydebug.o: ../../../include/yalecad/base.h /usr/include/stdio.h
ydebug.o: /usr/include/features.h /usr/include/sys/cdefs.h
ydebug.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
ydebug.o: /usr/include/gnu/stubs-64.h
ydebug.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
ydebug.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
ydebug.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
ydebug.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
ydebug.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
ydebug.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
ydebug.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
ydebug.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
ydebug.o: /usr/include/sys/types.h /usr/include/time.h
ydebug.o: /usr/include/sys/select.h /usr/include/bits/select.h
ydebug.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
ydebug.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
ydebug.o: /usr/include/alloca.h /usr/include/math.h
ydebug.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
ydebug.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
ydebug.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
ydebug.o: /usr/include/bits/mathcalls.h
ydebug.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
ydebug.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
ydebug.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
ydebug.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
ydebug.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
ydebug.o: ../../../include/yalecad/rbtree.h ../../../include/yalecad/file.h
ydebug.o: ../../../include/yalecad/message.h
ydebug.o: ../../../include/yalecad/string.h
yreadpar.o: /usr/include/string.h /usr/include/features.h
yreadpar.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
yreadpar.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
yreadpar.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
yreadpar.o: /usr/include/xlocale.h ../../../include/yalecad/file.h
yreadpar.o: ../../../include/yalecad/base.h /usr/include/stdio.h
yreadpar.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
yreadpar.o: /usr/include/libio.h /usr/include/_G_config.h
yreadpar.o: /usr/include/wchar.h
yreadpar.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
yreadpar.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
yreadpar.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
yreadpar.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
yreadpar.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
yreadpar.o: /usr/include/sys/types.h /usr/include/time.h
yreadpar.o: /usr/include/sys/select.h /usr/include/bits/select.h
yreadpar.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
yreadpar.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
yreadpar.o: /usr/include/alloca.h /usr/include/math.h
yreadpar.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
yreadpar.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
yreadpar.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
yreadpar.o: /usr/include/bits/mathcalls.h
yreadpar.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
yreadpar.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
yreadpar.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
yreadpar.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
yreadpar.o: /usr/include/bits/posix2_lim.h
yreadpar.o: ../../../include/yalecad/okmalloc.h
yreadpar.o: ../../../include/yalecad/rbtree.h
yreadpar.o: ../../../include/yalecad/message.h
yreadpar.o: ../../../include/yalecad/string.h
yreadpar.o: ../../../include/yalecad/yreadpar.h
