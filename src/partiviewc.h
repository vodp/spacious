#ifndef _PARTIVIEW_C_H
#define _PARTIVIEW_C_H
/*
 * UI-related glue functions for partiview.
 * Stuart Levy, slevy@ncsa.uiuc.edu
 * National Center for Supercomputing Applications,
 * University of Illinois 2001.
 * This file is part of partiview, released under the
 * Illinois Open Source License; see the file LICENSE.partiview for details.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CONST
# ifdef __cplusplus
# define CONST const
# else
# define CONST
# endif
#endif

#include "geometry.h"

struct stuff ;
struct Fl_Plot ;

#ifndef MAXSTUFF
#  define MAXSTUFF 48
#endif
extern struct stuff *stuffs[MAXSTUFF];

struct parser {
  int (*parsefunc)( struct stuff **stp, int argc, char *argv[], char *fname, void *etc );
  char *whose;			/* name */
  void *etc;			/* client data */
  struct parser *next;
};

#define OBJNO_CAMERA (-1)
#define OBJNO_WORLD  (-2)
#define OBJNO_NONE   (-3)

extern int parti_readpath( CONST char *fname );
extern void parti_play( CONST char *rate );
extern int parti_frame( CONST char *frameno, CONST struct wfpath **pp );
extern void parti_setpath( int nframes, struct wfframe *frames, float fps, float *focallens );
extern int parti_setframe( int fno );
extern float parti_focal( CONST char *newfocal );
extern int parti_focalpoint( int argc, char **argv, Point *focalpoint, float *minfocallen );
extern float parti_fovy( CONST char *newfovy );
extern int   parti_ortho( CONST char *newortho );
extern char *parti_clip( CONST char *znear, CONST char *zfar );
extern char *parti_bgcolor( CONST char *rgb );
extern char *parti_stereo( CONST char *stereosep );
extern float parti_getcensize( void );
extern void parti_nudge_camera( Point *displacement );
extern char *parti_winsize( CONST char *winsize );
extern void parti_censize( float v );
extern void parti_getcenter( Point *center );

/*Functions written by Phong Vo (vo@telecom-paristech.fr)*/

// Get the bounds from loaded points cloud
extern int spac_get_bound (Point *xmin, Point *xmax);

// Read an satellite image onto the right window
extern int spac_imread(const char* filename);

extern int spac_previmread(const char* filename);

// Set rectangular grid for satellite image
extern int spac_grid(int x, int y);

// Show several cells on satellite image. These cells are
// selected on the left window.
extern int spac_activate_grid(int* blks,int n);

// Selection tool for the right window. User can select a subset of activated cells
// and see where they are in the left window.
extern int spac_hitbox (Point cen, float xsize, float ysize, float zsize);

// Find the bounds for a subset of points cloud
extern int spac_setbound(int* idx, int n);

// Initialize bounds for graphical user controls. These bounds are computed
// from points cloud.
extern void spac_init_locators (void);

// Build minimum spanning tree
extern int spac_build_minspantree (void);

// Collapse/Expand the tree by mouse. CTRL+MIDDLE-MOUSE
// This functionality is not completed but can be used, anyway.
extern int spac_navigate_nodes(int vertex);

// Draw the spanning tree after any changes
extern int spac_update_spantree (void);

// batch expand the tree by showing hidden nodes if any
extern int spac_expand_spantree (void);

// collapse the tree by hiding one-degree nodes
extern int spac_collapse_spantree (void);

// display the original spanning tree
extern int spac_reset_spantree (void);

// deallocate memory for spanning tree
extern int spac_delete_spantree (void);

// Delete the drawing of spanning tree
extern int spac_hide_spantree (void);

// Dimensionality switching
extern void spac_switch_dimensions(int slot, int new_dim);

//---------------------------------------------------------------//

extern void parti_center( CONST Point * );
extern void parti_getc2w( Matrix *c2w );
extern void parti_setc2w( CONST Matrix *c2w );
extern void parti_geto2w( struct stuff *st, int objno, Matrix *obj2world );
extern void parti_seto2w( struct stuff *st, int objno, CONST Matrix *obj2world );
extern int  parti_objno(  CONST struct stuff *st );
extern int  parti_object( CONST char *objname, struct stuff **newst, int create );
extern int  parti_idof( struct stuff *st );
extern int  parti_move( CONST char *onoffobj, struct stuff **newst );
extern void parti_redraw(void);
extern void parti_update(void);
extern void parti_allobjs( int argc, char *argv[], int verbose );
extern int  parti_parse_args( struct stuff **stp, int argc, char *argv[], char *fname );
extern int  parti_read( struct stuff **stp, int argc, char *argv[], char *fname );
extern void parti_add_commands( int (*parsfunc)(struct stuff **, int, char *[], char *fname, void *), char *whose, void *etc );
extern void parti_add_reader( int (*parsfunc)(struct stuff **, int, char *[], char *fname, void *), char *whose, void *etc );
extern void parti_del_commands( char *whose, void *etc );
extern void parti_cmdtrace( void (*func)( struct stuff **, int argc, char *argv[] ) );

extern void parti_parent( struct stuff *st, int parent );

extern void parti_set_speed( struct stuff *st, double speed );
extern void parti_set_timestep( struct stuff *st, double timestep );
extern void parti_set_timebase( struct stuff *st, double timebase );
extern void parti_set_running( struct stuff *st, int running );
extern void parti_set_fwd( struct stuff *st, int fwd );
extern void parti_set_alias( struct stuff *st, CONST char *alias );
extern CONST char *parti_get_alias( struct stuff *st );

extern int parti_make_subcam( CONST char *name, int argc, char **params );
extern int parti_subcam_named( CONST char *name );
extern int parti_select_subcam( int index );
extern char *parti_subcam_list( void );
extern char *parti_get_subcam( int index, char *paramsp100 );
extern int parti_current_subcam( void );
extern struct Fl_Plot *parti_register_plot( struct stuff *st, void (*draw)(struct Fl_Plot *, void *obj, void *arg), void *arg );
extern void parti_hrdiag_on( int on );
extern int parti_inertia( int on );	/* parti_inertia(-1) returns cur val */

extern int getfloats( float *v, int nfloats, int arg0, int argc, char **argv );

#ifndef CAVEMENU
extern void parti_asyncfd( int fd );
extern void parti_unasyncfd( int fd );
extern int  parti_snapset( char *basename, char *frameno, char *imgsize );
extern int  parti_snapshot( char *snapinfo );
extern float parti_pickrange( char *newrange );
extern void parti_detachview( CONST char *how );
#endif

extern int msg( CONST char *fmt, ... );

extern char partiview_version[];

#ifdef __cplusplus
}
#endif

#endif /*!_PARTIVIEW_C_H*/
