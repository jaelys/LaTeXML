/*# /=====================================================================\ #
  # |  LaTeXML/src/mouth.h                                                | #
  # |                                                                     | #
  # |=====================================================================| #
  # | Part of LaTeXML:                                                    | #
  # |  Public domain software, produced as part of work done by the       | #
  # |  United States Government & not subject to copyright in the US.     | #
  # |---------------------------------------------------------------------| #
  # | Bruce Miller <bruce.miller@nist.gov>                        #_#     | #
  # | http://dlmf.nist.gov/LaTeXML/                              (o o)    | #
  # \=========================================================ooo==U==ooo=/ #  */

/*======================================================================
  C-level Mouth support */

#ifndef MOUTH_H
#define MOUTH_H

#define DEBUG_MOUTHNOT
#ifdef DEBUG_MOUTH
#  define DEBUG_Mouth(...) fprintf(stderr, __VA_ARGS__)
#  define DEBUGGING_Mouth 1
#else
#  define DEBUG_Mouth(...)
#  define DEBUGGING_Mouth 0
#endif

typedef struct Mouth_struct {
  UTF8 source;
  UTF8 short_source;
  SV * saved_state;
  UTF8 note_message;
  int lineno;
  STRLEN colno;
  UTF8 chars;
  STRLEN bufsize;
  STRLEN ptr;
  STRLEN nbytes;
  STRLEN prev_ptr;
  STRLEN prev_colno;
  int prev_lineno;
  int at_eof;
  LaTeXML_Core_Tokenstack pushback;
} T_Mouth;
typedef T_Mouth * LaTeXML_Core_Mouth;

#define SvMouth(arg)      INT2PTR(LaTeXML_Core_Mouth,      SvIV((SV*) SvRV(arg)))

extern void
mouth_setInput(pTHX_ LaTeXML_Core_Mouth mouth, UTF8 input);

extern LaTeXML_Core_Mouth
mouth_new(pTHX_ UTF8 source, UTF8 short_source, UTF8 content, SV * saved_state, UTF8 note_message);

extern void
mouth_DESTROY(pTHX_ LaTeXML_Core_Mouth mouth);

extern void
mouth_setInput(pTHX_ LaTeXML_Core_Mouth mouth, UTF8 input);

extern SV *
mouth_getLocator(pTHX_ LaTeXML_Core_Mouth mouth);

  /* Since readToken looks ahead, we'll need to be able to undo the effects of mouth_readChar! */
extern int
mouth_readChar(pTHX_ LaTeXML_Core_Mouth mouth, SV * state, char * character, int * catcode);
  /* Put back the previously parsed character.  Would be nice to save it for next call,
     but the catcodes can (& will) change by then! */

extern void
mouth_unreadChar(pTHX_ LaTeXML_Core_Mouth mouth);

extern int
mouth_readLine(pTHX_ LaTeXML_Core_Mouth mouth);

/*
extern int
mouth_fetchInput(pTHX_ LaTeXML_Core_Mouth mouth);
*/

extern void
mouth_unreadToken(pTHX_ LaTeXML_Core_Mouth mouth, SV * thing);

extern SV *
mouth_readToken(pTHX_ LaTeXML_Core_Mouth mouth, SV * state);

extern LaTeXML_Core_Tokens
mouth_readTokens(pTHX_ LaTeXML_Core_Mouth mouth, SV * state, SV * until);

#endif
