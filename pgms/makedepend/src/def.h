/*
 * $XConsortium: def.h,v 1.6 88/09/22 13:52:33 jim Exp $
 */

#ifndef DEF_H
#define DEF_H

#ifndef lint
static char SccsDef_h[] = "@(#) def.h (Yale) version 1.2 8/24/89" ; 
#endif

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

#define INCLUDEDIR      "/usr/include"

#define MAXDEFINES	512
#define MAXFILES	512
#define MAXDIRS		10
#define SYMTABINC	10	/* must be > 1 for define() to work right */
#define	TRUE		1
#define	FALSE		0
#define	STRINGEQ	0

/* the following must match the directives table in main.c */
#define	IF		0
#define	IFDEF		1
#define	IFNDEF		2
#define	ELSE		3
#define	ENDIF		4
#define	DEFINE		5
#define	UNDEF		6
#define	INCLUDE		7
#define	LINE		8
#define	PRAGMA		9
#define ELIF		10
#define EJECT		11
#define	IFFALSE		12	/* pseudo value --- never matched */
#define ELIFFALSE	13	/* pseudo value --- never matched */
#define	INCLUDEDOT	14	/* pseudo value --- never matched */
#define	IDENT	        15	/* added for Apollo ignored */

#define	debug0
#define	debug1
#define	debug2
#define	debug3
#define	debug4
#define	debug5
#define	debug6

typedef	int	boolean;

struct symtab {
	char	*s_name;
	char	*s_value;
};

struct	inclist {
	char		*i_incstring;	/* string from #include line */
	char		*i_file;	/* path name of the include file */
	struct inclist	**i_list;	/* list of files it itself includes */
	int		i_listlen;	/* length of i_list */
	struct symtab	*i_defs;	/* symbol table for this file */
	struct symtab	*i_lastdef;	/* last symbol defined */
	int		i_deflen;	/* number of defines */
	boolean		i_defchecked;	/* whether defines have been checked */
	boolean		i_notified;	/* whether we have revealed includes */
	boolean		i_marked;	/* whether it's in the makefile */
	boolean		i_searched;	/* whether we have read this */
	boolean         i_included_sym; /* whether #include SYMBOL was found */
					/* Can't use i_list if TRUE */
};

struct filepointer {
	char	*f_p;
	char	*f_base;
	char	*f_end;
	long	f_len;
	long	f_line;
};

char			*copy();
/* char			*malloc(); */
/* char			*realloc(); */
char			*basename();
char			*get_line();
struct symtab		*slookup();
struct symtab		*defined();
struct symtab		*fdefined();
struct filepointer	*getfile();
struct inclist		*newinclude();
struct inclist		*inc_path();

#endif /* DEF_H */
