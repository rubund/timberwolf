/* ----------------------------------------------------------------- 
FILE:	    main.c
DESCRIPTION:This file contains main control routine for the make
    file generator program.  Although using fprintf statements to
    write the makefile is rather crude (one could read a template),
    it makes it easy for beginning programmers to change the 
    output format.  Please feel free to change the output format
    to your liking.
CONTENTS:   main( argc , argv )
		int argc ;
		char *argv[] ;
	    syntax()
	    add2list( srcname, type )
		char *srcname ;
		int  type ;
	    char **Ystrparser(str,dels,numtokens)
		char *str, *dels ;
		int  *numtokens ;
	    check_suffix( string, line  ) 
		char *string ;
DATE:	    Aug 24, 1989 
REVISIONS:  Dec  8, 1990 - fixed RM object files.
	    Mon Feb  4 14:47:05 EST 1991 - added YALE conditional
		to remove yacc and lex files on foreign machines. to 
	    Tue Feb  5 22:50:41 EST 1991 - changed Imakefile to
		Ymakefile to make everything consistent.
	    Tue Mar 12 17:12:24 CST 1991 - added missing semicolons.
----------------------------------------------------------------- */
#ifndef lint
char SccsId[] = "@(#) main.c (Yale) version 1.7 3/12/91" ; 
#endif

#define MAIN_VARS

#include <stdio.h>
#include <sys/types.h>
#include <sys/dir.h>


#define LRECL            256
#define STRINGEQ         0
#define EXPECTSRCS       100
#define TRUE             1
#define FALSE            0
#define EOS              0

#define CTYPE            0
#define CPLUSTYPE        1
#define PASTYPE          2
#define CINSTYPE         3
#define PASINSTYPE       4
#define LEXTYPE          5
#define YACCTYPE         6

#define CCOMP            "${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c "
#define CCOMP2           "${CC} ${CLEANUP} ${CFLAGS} ${IDIR} ${OPTIONS} -c "
#define CPLUSCOMP        "${CCXX} ${CFLAGS} ${IDIR} ${OPTIONS} -c "
#define PASCOMP          "${PAS} "
#define PASCOMP2         "${PASFLAGS} ${PIDIR} ${POPTIONS} "

typedef int BOOL ;          /* define a boolean type */

static char **srcS ;        /* array of source names */
static int  *typeS ;        /* array of source types */
static int  numsrcS = 0;    /* number of source files in makefile */
static BOOL yaleS = TRUE ;  /* whether Yale customization is on */
static BOOL graphicS=FALSE ;/* whether graphics are present */

main( argc , argv )
int argc ;
char *argv[] ;
{
    FILE *fp ;
    char buffer[LRECL], *bufferptr = buffer ;
    char filename[LRECL] ;
    char filedir[LRECL] ;   /* file or directory */
    char *strrchr() ;       /* find last . in mainName */
    char programName[LRECL];/* name of program */
    char mainName[LRECL];   /* name of main routine */
    char objdir[LRECL];     /* name of objectdir */
    char **tokens ;         /* tokenized line read from file */
    char **Ystrparser() ;   /* converts strings to tokens */
    char *ptr ;             /* look at option string */
    int  numtokens ;        /* number of tokens on line */ 
    int  line ;             /* line number of file */
    int  i ;                /* counter */
    BOOL moveObj ;          /* whether object needs to me moved */
    BOOL fileNotDir ;       /* TRUE for file FALSE for directory */
    DIR  *dirp ;            /* pointer to a directory */
    struct direct *dp ;     /* pointer to an entry in directory */
    extern char *rindex() ; /* find last dot */ 

    if( argc != 5 && argc != 6 ){
	syntax() ;
    }

    strcpy( filedir, argv[1] ) ;
    strcpy( filename, argv[2] ) ;
    for( ptr = &filedir[1]; *ptr; ptr++ ){
	switch( *ptr ){
	case 'd':
	    fileNotDir = FALSE ;
	    break ;
	case 'f':
	    fileNotDir = TRUE ;
	    if(!(fp = fopen( filename, "r" ))){
		printf( "Error:can't open file:%s\n", filename ) ;
		exit(1) ;
	    } 
	    break ;
	case 'g':
	    graphicS = TRUE ;
	    break ;
	case 'n':
	    yaleS = FALSE ;
	    break ;
	default:
	    printf( "Unknown option:%c\n", *ptr ) ;
	    syntax() ;
	}
    }
    strcpy( programName, argv[3] ) ;
    strcpy( objdir, argv[4] ) ;
    if( strcmp( objdir, "." ) == STRINGEQ ){
	moveObj = FALSE ;
    } else {
	moveObj = TRUE ;
    }
    if( argc == 6 ){
	strcpy( mainName, argv[5] ) ;
	if( bufferptr = strrchr( mainName, '.' )){
	    *bufferptr = EOS ;
	} 
    } else {
	sprintf( mainName, "main" ) ;
    }

    line = 0 ;
    srcS = (char **) malloc( EXPECTSRCS * sizeof(char *) ) ;
    typeS = (int *)  malloc( EXPECTSRCS * sizeof(int) ) ; 

    if( fileNotDir ){
	while( bufferptr=fgets(buffer,LRECL,fp )){
	    /* parse file */
	    line++ ; /* increment line number */
	    tokens = Ystrparser( bufferptr, " \t\n", &numtokens );

	    if( numtokens == 0 ){
		/* skip over blank lines */
		continue ;
	    }
	    check_suffix( tokens[0], line ) ;
	} /* end parsing loop */
	fclose( fp ) ;

    } else {  /* a directory */
	/* look at all the entries in a directory */
	if( dirp = opendir(filename) ){
	    for( dp = readdir(dirp) ;dp; dp = readdir(dirp) ){
		check_suffix( dp->d_name, 0 ) ;
	    }
	    closedir(dirp) ;
	} else {
	    printf( "Error:can't open directory:%s\n", filename ) ;
	    exit(1) ;
	}
    }

    /************ OUTPUT THE MAKEFILE ****************** */
    if(!(fp = fopen( "Ymakefile", "w" ))){
	printf( "Error:can't open file:Ymakefile\n" ) ;
	exit(1) ;
    } 

    /* put heading here */
    fprintf( fp, "# Ymakefile for program %s\n", programName ) ;
    fprintf( fp, "#  \"%@(#)% %main.c% (Yale) version %1.7% %3/12/91% \" \n" ) ;
    fprintf( fp, "#\n" ) ;

    fprintf( fp, "#include macros\n\n" ) ;

    fprintf( fp, "#destination of output executable\n" ) ;
    fprintf( fp, "DEST=../\n" ) ;
    fprintf( fp, "PNAME=%s\n\n", programName ) ;

    fprintf( fp, "#where the object code is located\n" ) ;
    fprintf( fp, "objdir=%s\n" , objdir ) ;
    fprintf( fp, "O=${objdir}/\n" ) ;

    /* now output the source */
    fprintf( fp, "\nSRC= " ) ;
    for( i=1; i<= numsrcS; i++ ){
	switch( typeS[i] ){
	case CTYPE:
	    fprintf( fp, "\\\n\t%s.c ", srcS[i] ) ;
	    break ;
	case CPLUSTYPE:
	    fprintf( fp, "\\\n\t%s.cxx ", srcS[i] ) ;
	    break ;
	case PASTYPE:
	    fprintf( fp, "\\\n\t%s.pas ", srcS[i] ) ;
	    break ;
	case LEXTYPE:
	    if( yaleS ){
		fprintf( fp, "\\\n#ifdef YALE " ) ;
		fprintf( fp, "\\\n\t%s.l ", srcS[i] ) ;
	    } else {
		fprintf( fp, "\\\n\t%s.l ", srcS[i] ) ;
	    }
	    if( yaleS ){
		fprintf( fp, "\\\n#endif \/\* YALE \*\/ " ) ;
	    }
	    break ;
	case YACCTYPE:
	    if( yaleS ){
		fprintf( fp, "\\\n#ifdef YALE " ) ;
		fprintf( fp, "\\\n\t%s.y ", srcS[i] ) ;
	    } else {
		fprintf( fp, "\\\n\t%s.y ", srcS[i] ) ;
	    }
	    if( yaleS ){
		fprintf( fp, "\\\n#else \/\* YALE \*\/ " ) ;
		fprintf( fp, "\\\n\t%s.c ", srcS[i] ) ;
		fprintf( fp, "\\\n#endif \/\* YALE \*\/ " ) ;
	    }
	    break ;
	}
    } /* end src loop */

    /* now output the objects */
    fprintf( fp, "\n\nOBJ= " ) ;
    for( i=1; i<= numsrcS; i++ ){
	switch( typeS[i] ){
	case CTYPE:
	case CPLUSTYPE:
	case PASTYPE:
	case YACCTYPE:
	    fprintf( fp, "\\\n\t${O}%s.o ", srcS[i] ) ;
	    break ;
	}
    } /* end src loop */

    /* now output the insert files */
    fprintf( fp, "\n\nINS= " ) ;
    for( i=1; i<= numsrcS; i++ ){
	switch( typeS[i] ){
	case CINSTYPE:
	    fprintf( fp, "\\\n\t%s.h ", srcS[i] ) ;
	    break ;
	case PASINSTYPE:
	    fprintf( fp, "\\\n\t%s.ins.pas ", srcS[i] ) ;
	    break ;
	}
    } /* end src loop */

    /* give user information on options */
    fprintf( fp, "\n\ninfo:   ; \n" ) ;
    fprintf( fp, "\t-@${ECHO} \"make ${DEST}${PNAME} - usage:\" \n" ) ;
    fprintf( fp, "\t-@${ECHO} \"   make install - build program\" \n" ) ;
    if( yaleS ){
	fprintf( fp, "\t-@${ECHO} \"   make install_non_yale - build program at foreign host\" \n" ) ;
    }
    fprintf( fp, "\t-@${ECHO} \"   make clean - remove binary\" \n" ) ;
    fprintf( fp, "\t-@${ECHO} \"   make depend - added makefile dependencies\" \n" ) ;
    fprintf( fp, "\t-@${ECHO} \"   make sources - pull sources from SCCS\" \n" ) ;
    fprintf( fp, "\t-@${ECHO} \"   make lint - run lint on the sources\" \n" ) ;

    fprintf( fp, "\n\n# how to make %s program\n", programName ) ;
    if( yaleS ){
	fprintf( fp, "${DEST}${PNAME}:${OBJ} ${YALECAD}\n" ) ;
	fprintf( fp, "\t${GETDATE}\n" ) ;
	fprintf( fp, "\t${CC} ${CFLAGS} -I. -c ${DATE_C}\n" ) ;
	if( moveObj ){
	    fprintf( fp, "\t${MV} date.o ${O}date.o\n" ) ;
	}
	fprintf( fp, "\t${CC} ${CFLAGS} ${OPTIONS} -o " ) ;
	fprintf( fp, "${DEST}${PNAME} ${OBJ} ${O}date.o \\\n" ) ;
	fprintf( fp, "\t${YALECAD} ${LINKLIB}\n\n" ) ;
	fprintf( fp, "# we can't do anything about yalecad but want to") ;
	fprintf( fp, " update if it has changed\n" ) ;
	fprintf( fp, "${YALECAD}: ;\n\n" ) ;
    } else {
	fprintf( fp, "${DEST}${PNAME}:${OBJ} \n" ) ;
	fprintf( fp, "\t${CC} ${CFLAGS} ${OPTIONS} -o " ) ;
	fprintf( fp, "${DEST}${PNAME} ${OBJ} ${LINKLIB} \n\n" ) ;
    }

    fprintf( fp, "install:${DEST}${PNAME}\n\n" ) ;
    if( yaleS ){
	fprintf( fp, "install_non_yale:${DEST}${PNAME}\n" ) ;
	if( graphicS ){
	    fprintf( fp,"\t-${S}if( test -d ${XLIB}${NOGRAPHICS} ) then \\\n" ) ;
	    fprintf( fp,"\t\techo \" \" ; \\\n" ) ;
	    fprintf( fp,"\t\techo \"Note:found ${XLIB}\"; \\\n" ) ;
	    fprintf( fp,"\t\techo \"making version with XWindow graphics...\" ;\\\n" ) ;
	    fprintf( fp,"\t\tmake ${DEST}${PNAME} GETDATE= CC=${CC} \\\n" ) ;
	    fprintf( fp,"\t\t\tCLEANUP=${CLEANUP} NOGRAPHICS=${NOGRAPHICS} \\\n" ) ;
	    fprintf( fp,"\t\t\tUNIX=${UNIX} DEBUG=${DEBUG} YALECAD=${YALECAD} ;\\\n" ) ;
	    fprintf( fp,"\t\techo \" \" ; \\\n" ) ;
	    fprintf( fp,"\telse \\\n" ) ;
	    fprintf( fp,"\t\techo \" \" ; \\\n" ) ;
	    fprintf( fp,"\t\techo \"Note:didn't find ${XLIB} or NOGRAPHICS requested\"; \\\n" ) ;
	    fprintf( fp,"\t\techo \"making version without XWindow graphics...\" ; \\\n" ) ;
	    fprintf( fp,"\t\tmake ${DEST}${PNAME} GETDATE= CC=${CC} \\\n" ) ;
	    fprintf( fp,"\t\t\tCLEANUP=${CLEANUP} NOGRAPHICS=-DNOGRAPHICS \\\n" ) ;
	    fprintf( fp,"\t\t\tUNIX=${UNIX} DEBUG=${DEBUG} YALECAD=${YALECAD} \\\n" ) ;
	    fprintf( fp,"\t\t\tCFLAGS=\"${CFLAGS}\" LINKLIB=\"${LINKLIB}\" ;\\\n" ) ;
	    fprintf( fp,"\tfi ;  \n" ) ;
	}
    }

    fprintf( fp, "\nclean: ;\n" ) ;
    if( moveObj ){
	fprintf( fp, "\t${RM} ${O}* ~* core *.bak foo* y.output y.tab.c\n\n" ) ;
    } else {
	fprintf( fp, "\t${RM} *.o ~* core *.bak foo* y.output y.tab.c\n\n" ) ;
    }

    fprintf( fp, "# how to build makefile dependencies\n" ) ;
    fprintf( fp, "depend : ;\n" ) ;
    fprintf( fp, "\t${MAKEDEPEND} ${CFLAGS} ${OPTIONS} ${IDIR} ${SRC}\n\n" ) ;

    fprintf( fp, "# how to make %s lint\n", programName ) ;
    fprintf( fp, "lint:  ; \n" ) ;
    fprintf( fp, "\t${LINT} ${LINT_OPT} ${IDIR} ${OPTIONS} *.c > lint.out \n\n" ) ;

    fprintf( fp, "#default sccs operation is get\n" ) ;
    fprintf( fp, "SCCS_OP=get\n" ) ;
    fprintf( fp, "#current release\n" ) ;
    fprintf( fp, "REL=\n\n" ) ;
    fprintf( fp, "# how to get sources from sccs\n" ) ;
    fprintf( fp, "sources : ${SRC} ${INS} ${YMAKEFILE}\n" ) ;
    fprintf( fp, "${SRC} ${INS} ${YMAKEFILE}: \n" ) ;
    fprintf( fp, "\t${SCCS} ${SCCS_OP} ${REL} $@\n\n" ) ;

    /* used by makedepend */
    /* important that this line is before sources otherwise make */
    /* will not work */
    fprintf( fp,"#BEGIN DEPENDENCIES -- DO NOT DELETE THIS LINE\n\n") ;
    fprintf( fp,"#END DEPENDENCIES -- DO NOT DELETE THIS LINE\n\n" ) ;

    /* now output the how to compile the individual sources */
    fprintf( fp, "\n# How to compile the sources\n" ) ;
    for( i=1; i<= numsrcS; i++ ){
	switch( typeS[i] ){
	case CTYPE:
	    fprintf( fp, "${O}%s.o:%s.c\n", srcS[i],srcS[i] ) ;
	    if( strcmp( srcS[i], mainName ) == STRINGEQ ){
		fprintf( fp, "\t%s %s.c\n", CCOMP2, srcS[i] ) ;
	    } else {
		fprintf( fp, "\t%s %s.c\n", CCOMP, srcS[i] ) ;
	    }
	    if( moveObj ){
		fprintf( fp, "\t${MV} %s.o ${O}%s.o\n", srcS[i], srcS[i] ) ;
	    }
	    break ;
	case CPLUSTYPE:
	    fprintf( fp, "${O}%s.o:%s.cxx\n", srcS[i],srcS[i] ) ;
	    fprintf( fp, "\t%s %s.cxx\n", CPLUSCOMP, srcS[i] ) ;
	    if( moveObj ){
		fprintf( fp, "\t${MV} %s.o ${O}%s.o\n", srcS[i], srcS[i] ) ;
	    }
	    break ;
	case PASTYPE:
	    fprintf( fp, "${O}%s.o:%s.pas\n", srcS[i],srcS[i] ) ;
	    fprintf( fp, "\t%s %s.pas %s\n", 
		PASCOMP, srcS[i], srcS[i], PASCOMP2 ) ;
	    if( moveObj ){
		fprintf( fp, "\t${MV} %s.bin ${O}%s.o\n", srcS[i], srcS[i] ) ;
	    }
	    break ;
	case YACCTYPE:
	    if( yaleS ){
		fprintf( fp, "#ifdef YALE\n" ) ;
	    }
	    fprintf( fp, "${O}%s.o:%s.y %s.l\n", srcS[i],srcS[i],
		srcS[i] ) ;
	    fprintf( fp, "\t${LEX} %s.l\n", srcS[i] ) ;
	    fprintf( fp, "\t${LEXMV} lex.yy.c %s_l.h\n", srcS[i] ) ;
	    fprintf( fp, "\t${YACC} %s.y\n", srcS[i] ) ;
	    fprintf( fp, "\t${YACCMV} y.tab.c %s.c\n", srcS[i] ) ;
	    fprintf( fp, "#\tuse grep to remove # line so dbx works correctly\n" ) ;
	    fprintf( fp, "\t${GREP} -v \"# line\" %s.c > tmp; ",
		srcS[i] ) ;
	    fprintf( fp, "\t${MV} tmp %s.c\n", srcS[i] ) ;
	    fprintf( fp, "\t%s %s.c\n", CCOMP, srcS[i] ) ;
	    if( moveObj ){
		fprintf( fp, "\t${MV} %s.o ${O}%s.o\n", srcS[i], srcS[i] ) ;
	    }
	    fprintf( fp, "%s.y:\n", srcS[i] ) ;
	    fprintf( fp, "%s.l:\n", srcS[i] ) ;
	    if( yaleS ){
		fprintf( fp, "#else  \/\* YALE \*\/ \n" ) ;
		fprintf( fp, "${O}%s.o:%s.c\n", srcS[i], srcS[i] ) ;
		fprintf( fp, "\t%s %s.c\n", CCOMP, srcS[i] ) ;
		if( moveObj ){
		    fprintf( fp, "\t${MV} %s.o ${O}%s.o\n", srcS[i], srcS[i] ) ;
		}
		fprintf( fp, "#endif \/\* YALE \*\/ \n" ) ;
	    }
	    break ;
	}
    } /* end src loop */
    fprintf( fp, "\n# end makefile\n" ) ;

    fclose( fp ) ;
    exit(0) ;

} /* end main */


/* give user correct syntax */
syntax()
{
   printf("\n" ) ; 
   printf("Incorrect syntax.  Correct syntax:\n");
   printf("\nmakehelper -{f|d}[ng] filelist|dir programName objectDir [mainName]\n" );
   printf("where\n" ) ;
   printf("\tf specifies a filelist - a file naming the c files,\n" ) ;
   printf("\tpascal files, etc. to be in the makefile one on a line.\n\n" );
   printf("\td specifies a directory - makehelper will assume\n" ) ;
   printf("\tfiles with proper suffixes are to be made.\n" ) ;
   printf("\tNote:makehelper knows how to handle SCCS directories -\n" ) ;
   printf("\t\tjust specify the full pathname of the SCCS directory.\n\n" ) ;
   printf("\tprogramName is the desired output program name.\n\n" ) ;
   printf("\tobjectDir is the object directory specified relative to the\n" ) ;
   printf("\tdirectory makefile resides.  Use '.' for current directory\n\n" ) ;
   printf("\tmainName (optional) is the name of the file containing the\n") ;
   printf("\tstart of the program.  If no argument is supplied, makehelper\n");
   printf("\twill assume main.c\n");
   printf("\tThe optional argument n will turn off YALECAD customizations\n");
   printf("\tThe optional argument g will include YALECAD graphics\n");
   printf("\tExample:\n" ) ;
   printf("\t\tmakehelper -d /user/bills/syntax/SCCS syntax ../obj\n" ) ;
   printf("\nmakehelper understands the following suffixes:\n" ) ;
   printf("\t.c, .cxx, .pas, .h, .ins.pas, .l, .y\n" ) ;
   printf("\nmakehelper will output an Ymakefile.  Use imake to " ) ;
   printf("convert to a makefile\n\n" ) ;
   exit(1);
} /* end syntax */


add2list( srcname, type )
char *srcname ;
int  type ;
{
    static int srcAlloc = EXPECTSRCS ;  /* current allocation of srcS array */
    char *suffix ;                      /* suffix start */
    char *rindex() ;                    /* find last x character in string */
    if( ++numsrcS >= srcAlloc ){
	srcAlloc += EXPECTSRCS ;
	srcS = (char **) realloc( srcS, srcAlloc * sizeof(char *) ) ; 
	typeS = (int *) realloc( typeS, srcAlloc * sizeof(int) ) ; 
    }
    if( suffix = rindex( srcname, '.' ) ){
	*suffix = EOS ;
    }
    if( type == PASINSTYPE ){
	if( suffix = rindex( srcname, '.' ) ){
	    *suffix = EOS ;
	}
    }
    srcS[numsrcS] = (char *) malloc( strlen(srcname) + 1 ) ;
    strcpy( srcS[numsrcS], srcname ) ;
    typeS[numsrcS] = type ;
} /* end add2list */


char **Ystrparser(str,dels,numtokens)
char *str;
char *dels ; /* delimiters */
int  *numtokens ; /* pass back number of tokens */
{

    static char *tokenBuf[LRECL] ; /* impossible to have more tokens */
				  /* than length of input line length */
    char *strtok() ;
    int  index = 0 ;

    /* use strtok to strip away delimiters */
    /* first call to strtok requires the string reference */
    tokenBuf[index] = strtok(str,dels) ;
    while( tokenBuf[index] ){
	/* subsequent calls to strtok doesn't requires the string ref */
	/* strtok remembers place in string */
	tokenBuf[++index] = strtok(NULL,dels) ;
    }
    /* return number of tokens and token buffer */
    *numtokens = index ;
    return(tokenBuf) ;
} /* end Ystrparser */

check_suffix( string, line  ) 
char *string ;
{
    char *suffix ;          /* suffix of file */
    char *ptr ;             /* used to check pas includes */
    extern char *rindex() ; /* find last dot */ 

    /* printf( "%s\n", string ) ; */
    /* look for SCCS files and avoid p. files */
    if( strncmp( string, "s.", 2 ) == STRINGEQ ){
	/* skip over s. */
	string += 2 ;
    } else if( strncmp( string, "p.", 2 ) == STRINGEQ ){
	return ;
    }
    /* find if pascal file or c file or ins file */
    if( suffix = rindex( string, '.' ) ){
	suffix++  ;
	if( !suffix || !(*suffix)){
	    return ;
	}
	if( strcmp( suffix, "c" ) == STRINGEQ ){
	    add2list( string, CTYPE ) ;
	} else if( strcmp( suffix, "cxx" ) == STRINGEQ ){
	    add2list( string, CPLUSTYPE ) ;
	} else if( strcmp( suffix, "pas" ) == STRINGEQ ){
	    /* check to see if it is an insert file .ins.pas */

	    /* go back to .ins */
	    ptr = suffix - 5 ;  
	    if( ptr > string ){
		/* make sure ptr is valid */
		if( strcmp( ptr, ".ins.pas" ) == STRINGEQ ){
		    add2list( string, PASINSTYPE ) ;
		    return ;
		}
	    }
	    add2list( string, PASTYPE ) ;
	} else if( strcmp( suffix, "h" ) == STRINGEQ ){
	    add2list( string, CINSTYPE ) ;
	} else if( strcmp( suffix, "l" ) == STRINGEQ ){
	    add2list( string, LEXTYPE ) ;
	} else if( strcmp( suffix, "y" ) == STRINGEQ ){
	    add2list( string, YACCTYPE ) ;
	} else {
	    printf( "Warning:unknown suffix for file:%s", string ) ;
	    if( line ){
		printf( "line:%d\n", line ) ;
	    } else {
		printf( "\n" ) ;
	    }
	    return ;
	}
    } /* end suffix processing */
} /* end check_suffix */
