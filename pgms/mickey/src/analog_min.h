/***********************************************************
static char SccsId[] = "@(#)analog_min.h	v1.1 5/23/91 Copyright 1991 Mentor Graphics";
***********************************************************/

#define FFLUSH	(void)fflush

/***********************************************************
* Define a data structure for a linked list of channels or
* a linked list of active sets.
***********************************************************/
typedef struct _channel_list {
    int index;
    struct _channel_list *next;
} CLIST,
*CLISTPTR;

/***********************************************************
* Define a data structure for a pin location in a channel.
***********************************************************/
typedef struct _chan {
    int penalty; /* penalty for this pin */
    int distance; /* distance from the left end to this pin */
    int mixed; /* number of nets with mixed type at this pin */
    int noisy; /* number of nets with noisy type at this pin */
    int sensitive; /* number of nets with sensitive type at this pin */
    int shielding; /* number of nets with shielding type at this pin */
    struct hlist *Pheap; /* pointer to the priority tree of this pin */
    struct nlist *Pnlist; /* linked list of nets at this pin */
} CHANS,
*CHANSPTR;

/***********************************************************
* Define a data structure for a super-channel (or an active
* set).
***********************************************************/
typedef struct _active_set {
    /***********************************************************
    * penalty from crossing nets of this active set.
    ***********************************************************/
    int penalty;
    int mixed;
    int noisy;
    int sensitive;
    int shielding;
    int numpin;
    /***********************************************************
    * linked list of channels in the set.
    ***********************************************************/
    struct _channel_list *Phead;
    /***********************************************************
    * linked list of crossing nets.
    ***********************************************************/
    struct nlist *Pnlist;
    /***********************************************************
    *  priority tree.
    ***********************************************************/
    struct hlist **Aindex;
    /***********************************************************
    *  array of pin locations in the set.
    ***********************************************************/
    struct _chan **Achan;
} ACTSET,
*ACTSETPTR;
