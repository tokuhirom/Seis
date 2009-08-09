/* A recursive-descent parser generated by greg 0.2.0 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define YYRULECOUNT 36

# include "greg.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <libgen.h>
# include <assert.h>

  typedef struct Header Header;

  struct Header {
    char   *text;
    Header *next;
  };

  FILE *input= 0;

  int   verboseFlag= 0;

  static int	 lineNumber= 0;
  static char	*fileName= 0;
  static char	*trailer= 0;
  static Header	*headers= 0;

  void makeHeader(char *text);
  void makeTrailer(char *text);

  void yyerror(char *message);

# define YY_INPUT(buf, result, max)		\
  {						\
    int c= getc(input);				\
    if ('\n' == c || '\r' == c) ++lineNumber;	\
    result= (EOF == c) ? 0 : (*(buf)= c, 1);	\
  }

# define YY_LOCAL(T)	static T
# define YY_RULE(T)	static T

#ifndef YY_VARIABLE
#define YY_VARIABLE(T)	static T
#endif
#ifndef YY_LOCAL
#define YY_LOCAL(T)	static T
#endif
#ifndef YY_ACTION
#define YY_ACTION(T)	static T
#endif
#ifndef YY_RULE
#define YY_RULE(T)	static T
#endif
#ifndef YY_PARSE
#define YY_PARSE(T)	T
#endif
#ifndef YYPARSE
#define YYPARSE		yyparse
#endif
#ifndef YYPARSEFROM
#define YYPARSEFROM	yyparsefrom
#endif
#ifndef YY_INPUT
#define YY_INPUT(buf, result, max_size)			\
  {							\
    int yyc= getchar();					\
    result= (EOF == yyc) ? 0 : (*(buf)= yyc, 1);	\
    yyprintf((stderr, "<%c>", yyc));			\
  }
#endif
#ifndef YY_BEGIN
#define YY_BEGIN	( yybegin= yypos, 1)
#endif
#ifndef YY_END
#define YY_END		( yyend= yypos, 1)
#endif
#ifdef YY_DEBUG
# define yyprintf(args)	fprintf args
#else
# define yyprintf(args)
#endif
#ifndef YYSTYPE
#define YYSTYPE	int
#endif

#ifndef YY_PART

typedef void (*yyaction)(char *yytext, int yyleng);
typedef struct _yythunk { int begin, end;  yyaction  action;  struct _yythunk *next; } yythunk;

YY_VARIABLE(char *   ) yybuf= 0;
YY_VARIABLE(int	     ) yybuflen= 0;
YY_VARIABLE(int	     ) yypos= 0;
YY_VARIABLE(int	     ) yylimit= 0;
YY_VARIABLE(char *   ) yytext= 0;
YY_VARIABLE(int	     ) yytextlen= 0;
YY_VARIABLE(int	     ) yybegin= 0;
YY_VARIABLE(int	     ) yyend= 0;
YY_VARIABLE(int	     ) yytextmax= 0;
YY_VARIABLE(yythunk *) yythunks= 0;
YY_VARIABLE(int	     ) yythunkslen= 0;
YY_VARIABLE(int      ) yythunkpos= 0;
YY_VARIABLE(YYSTYPE  ) yy;
YY_VARIABLE(YYSTYPE *) yyval= 0;
YY_VARIABLE(YYSTYPE *) yyvals= 0;
YY_VARIABLE(int      ) yyvalslen= 0;

YY_LOCAL(int) yyrefill(void)
{
  int yyn;
  while (yybuflen - yypos < 512)
    {
      yybuflen *= 2;
      yybuf= realloc(yybuf, yybuflen);
    }
  YY_INPUT((yybuf + yypos), yyn, (yybuflen - yypos));
  if (!yyn) return 0;
  yylimit += yyn;
  return 1;
}

YY_LOCAL(int) yymatchDot(void)
{
  if (yypos >= yylimit && !yyrefill()) return 0;
  ++yypos;
  return 1;
}

YY_LOCAL(int) yymatchChar(int c)
{
  if (yypos >= yylimit && !yyrefill()) return 0;
  if ((unsigned char)yybuf[yypos] == c)
    {
      ++yypos;
      yyprintf((stderr, "  ok   yymatchChar(%c) @ %s\n", c, yybuf+yypos));
      return 1;
    }
  yyprintf((stderr, "  fail yymatchChar(%c) @ %s\n", c, yybuf+yypos));
  return 0;
}

YY_LOCAL(int) yymatchString(char *s)
{
  int yysav= yypos;
  while (*s)
    {
      if (yypos >= yylimit && !yyrefill()) return 0;
      if (yybuf[yypos] != *s)
        {
          yypos= yysav;
          return 0;
        }
      ++s;
      ++yypos;
    }
  return 1;
}

YY_LOCAL(int) yymatchClass(unsigned char *bits)
{
  int c;
  if (yypos >= yylimit && !yyrefill()) return 0;
  c= (unsigned char)yybuf[yypos];
  if (bits[c >> 3] & (1 << (c & 7)))
    {
      ++yypos;
      yyprintf((stderr, "  ok   yymatchClass @ %s\n", yybuf+yypos));
      return 1;
    }
  yyprintf((stderr, "  fail yymatchClass @ %s\n", yybuf+yypos));
  return 0;
}

YY_LOCAL(void) yyDo(yyaction action, int begin, int end)
{
  while (yythunkpos >= yythunkslen)
    {
      yythunkslen *= 2;
      yythunks= realloc(yythunks, sizeof(yythunk) * yythunkslen);
    }
  yythunks[yythunkpos].begin=  begin;
  yythunks[yythunkpos].end=    end;
  yythunks[yythunkpos].action= action;
  ++yythunkpos;
}

YY_LOCAL(int) yyText(int begin, int end)
{
  int yyleng= end - begin;
  if (yyleng <= 0)
    yyleng= 0;
  else
    {
      while (yytextlen < (yyleng - 1))
	{
	  yytextlen *= 2;
	  yytext= realloc(yytext, yytextlen);
	}
      memcpy(yytext, yybuf + begin, yyleng);
    }
  yytext[yyleng]= '\0';
  return yyleng;
}

YY_LOCAL(void) yyDone(void)
{
  int pos;
  for (pos= 0;  pos < yythunkpos;  ++pos)
    {
      yythunk *thunk= &yythunks[pos];
      int yyleng= thunk->end ? yyText(thunk->begin, thunk->end) : thunk->begin;
      yyprintf((stderr, "DO [%d] %p %s\n", pos, thunk->action, yytext));
      thunk->action(yytext, yyleng);
    }
  yythunkpos= 0;
}

YY_LOCAL(void) yyCommit()
{
  if ((yylimit -= yypos))
    {
      memmove(yybuf, yybuf + yypos, yylimit);
    }
  yybegin -= yypos;
  yyend -= yypos;
  yypos= yythunkpos= 0;
}

YY_LOCAL(int) yyAccept(int tp0)
{
  if (tp0)
    {
      fprintf(stderr, "accept denied at %d\n", tp0);
      return 0;
    }
  else
    {
      yyDone();
      yyCommit();
    }
  return 1;
}

YY_LOCAL(void) yyPush(char *text, int count)	{ yyval += count; }
YY_LOCAL(void) yyPop(char *text, int count)	{ yyval -= count; }
YY_LOCAL(void) yySet(char *text, int count)	{ yyval[count]= yy; }

#endif /* YY_PART */

#define	YYACCEPT	yyAccept(yythunkpos0)

YY_RULE(int) yy_end_of_line(); /* 36 */
YY_RULE(int) yy_comment(); /* 35 */
YY_RULE(int) yy_space(); /* 34 */
YY_RULE(int) yy_braces(); /* 33 */
YY_RULE(int) yy_range(); /* 32 */
YY_RULE(int) yy_char(); /* 31 */
YY_RULE(int) yy_END(); /* 30 */
YY_RULE(int) yy_BEGIN(); /* 29 */
YY_RULE(int) yy_DOT(); /* 28 */
YY_RULE(int) yy_class(); /* 27 */
YY_RULE(int) yy_literal(); /* 26 */
YY_RULE(int) yy_CLOSE(); /* 25 */
YY_RULE(int) yy_OPEN(); /* 24 */
YY_RULE(int) yy_COLON(); /* 23 */
YY_RULE(int) yy_PLUS(); /* 22 */
YY_RULE(int) yy_STAR(); /* 21 */
YY_RULE(int) yy_QUESTION(); /* 20 */
YY_RULE(int) yy_primary(); /* 19 */
YY_RULE(int) yy_NOT(); /* 18 */
YY_RULE(int) yy_suffix(); /* 17 */
YY_RULE(int) yy_action(); /* 16 */
YY_RULE(int) yy_AND(); /* 15 */
YY_RULE(int) yy_prefix(); /* 14 */
YY_RULE(int) yy_BAR(); /* 13 */
YY_RULE(int) yy_sequence(); /* 12 */
YY_RULE(int) yy_SEMICOLON(); /* 11 */
YY_RULE(int) yy_expression(); /* 10 */
YY_RULE(int) yy_EQUAL(); /* 9 */
YY_RULE(int) yy_identifier(); /* 8 */
YY_RULE(int) yy_RPERCENT(); /* 7 */
YY_RULE(int) yy_end_of_file(); /* 6 */
YY_RULE(int) yy_trailer(); /* 5 */
YY_RULE(int) yy_definition(); /* 4 */
YY_RULE(int) yy_declaration(); /* 3 */
YY_RULE(int) yy__(); /* 2 */
YY_RULE(int) yy_grammar(); /* 1 */

YY_ACTION(void) yy_9_primary(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_9_primary\n"));
   push(makePredicate("YY_END")); ;
}
YY_ACTION(void) yy_8_primary(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_8_primary\n"));
   push(makePredicate("YY_BEGIN")); ;
}
YY_ACTION(void) yy_7_primary(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_7_primary\n"));
   push(makeAction(yytext)); ;
}
YY_ACTION(void) yy_6_primary(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_6_primary\n"));
   push(makeDot()); ;
}
YY_ACTION(void) yy_5_primary(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_5_primary\n"));
   push(makeClass(yytext)); ;
}
YY_ACTION(void) yy_4_primary(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_4_primary\n"));
   push(makeString(yytext)); ;
}
YY_ACTION(void) yy_3_primary(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_3_primary\n"));
   push(makeName(findRule(yytext))); ;
}
YY_ACTION(void) yy_2_primary(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_2_primary\n"));
   Node *name= makeName(findRule(yytext));  name->name.variable= pop();  push(name); ;
}
YY_ACTION(void) yy_1_primary(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_1_primary\n"));
   push(makeVariable(yytext)); ;
}
YY_ACTION(void) yy_3_suffix(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_3_suffix\n"));
   push(makePlus (pop())); ;
}
YY_ACTION(void) yy_2_suffix(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_2_suffix\n"));
   push(makeStar (pop())); ;
}
YY_ACTION(void) yy_1_suffix(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_1_suffix\n"));
   push(makeQuery(pop())); ;
}
YY_ACTION(void) yy_3_prefix(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_3_prefix\n"));
   push(makePeekNot(pop())); ;
}
YY_ACTION(void) yy_2_prefix(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_2_prefix\n"));
   push(makePeekFor(pop())); ;
}
YY_ACTION(void) yy_1_prefix(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_1_prefix\n"));
   push(makePredicate(yytext)); ;
}
YY_ACTION(void) yy_1_sequence(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_1_sequence\n"));
   Node *f= pop();  push(Sequence_append(pop(), f)); ;
}
YY_ACTION(void) yy_1_expression(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_1_expression\n"));
   Node *f= pop();  push(Alternate_append(pop(), f)); ;
}
YY_ACTION(void) yy_2_definition(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_2_definition\n"));
   Node *e= pop();  Rule_setExpression(pop(), e); ;
}
YY_ACTION(void) yy_1_definition(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_1_definition\n"));
   if (push(beginRule(findRule(yytext)))->rule.expression)
							    fprintf(stderr, "rule '%s' redefined\n", yytext); ;
}
YY_ACTION(void) yy_1_trailer(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_1_trailer\n"));
   makeTrailer(yytext); ;
}
YY_ACTION(void) yy_1_declaration(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_1_declaration\n"));
   makeHeader(yytext); ;
}

YY_RULE(int) yy_end_of_line()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "end_of_line"));
  {  int yypos2= yypos, yythunkpos2= yythunkpos;  if (!yymatchString("\r\n")) goto l3;  goto l2;
  l3:;	  yypos= yypos2; yythunkpos= yythunkpos2;  if (!yymatchChar('\n')) goto l4;  goto l2;
  l4:;	  yypos= yypos2; yythunkpos= yythunkpos2;  if (!yymatchChar('\r')) goto l1;
  }
  l2:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "end_of_line", yybuf+yypos));
  return 1;
  l1:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "end_of_line", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_comment()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "comment"));  if (!yymatchChar('#')) goto l5;
  l6:;	
  {  int yypos7= yypos, yythunkpos7= yythunkpos;
  {  int yypos8= yypos, yythunkpos8= yythunkpos;  if (!yy_end_of_line()) goto l8;  goto l7;
  l8:;	  yypos= yypos8; yythunkpos= yythunkpos8;
  }  if (!yymatchDot()) goto l7;  goto l6;
  l7:;	  yypos= yypos7; yythunkpos= yythunkpos7;
  }  if (!yy_end_of_line()) goto l5;
  yyprintf((stderr, "  ok   %s @ %s\n", "comment", yybuf+yypos));
  return 1;
  l5:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "comment", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_space()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "space"));
  {  int yypos10= yypos, yythunkpos10= yythunkpos;  if (!yymatchChar(' ')) goto l11;  goto l10;
  l11:;	  yypos= yypos10; yythunkpos= yythunkpos10;  if (!yymatchChar('\t')) goto l12;  goto l10;
  l12:;	  yypos= yypos10; yythunkpos= yythunkpos10;  if (!yy_end_of_line()) goto l9;
  }
  l10:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "space", yybuf+yypos));
  return 1;
  l9:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "space", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_braces()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "braces"));
  {  int yypos14= yypos, yythunkpos14= yythunkpos;  if (!yymatchChar('{')) goto l15;
  l16:;	
  {  int yypos17= yypos, yythunkpos17= yythunkpos;
  {  int yypos18= yypos, yythunkpos18= yythunkpos;  if (!yymatchChar('}')) goto l18;  goto l17;
  l18:;	  yypos= yypos18; yythunkpos= yythunkpos18;
  }  if (!yymatchDot()) goto l17;  goto l16;
  l17:;	  yypos= yypos17; yythunkpos= yythunkpos17;
  }  if (!yymatchChar('}')) goto l15;  goto l14;
  l15:;	  yypos= yypos14; yythunkpos= yythunkpos14;
  {  int yypos19= yypos, yythunkpos19= yythunkpos;  if (!yymatchChar('}')) goto l19;  goto l13;
  l19:;	  yypos= yypos19; yythunkpos= yythunkpos19;
  }  if (!yymatchDot()) goto l13;
  }
  l14:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "braces", yybuf+yypos));
  return 1;
  l13:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "braces", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_range()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "range"));
  {  int yypos21= yypos, yythunkpos21= yythunkpos;  if (!yy_char()) goto l22;  if (!yymatchChar('-')) goto l22;  if (!yy_char()) goto l22;  goto l21;
  l22:;	  yypos= yypos21; yythunkpos= yythunkpos21;  if (!yy_char()) goto l20;
  }
  l21:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "range", yybuf+yypos));
  return 1;
  l20:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "range", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_char()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "char"));
  {  int yypos24= yypos, yythunkpos24= yythunkpos;  if (!yymatchChar('\\')) goto l25;  if (!yymatchClass((unsigned char *)"\000\000\000\000\204\000\000\000\000\000\000\070\146\100\124\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l25;  goto l24;
  l25:;	  yypos= yypos24; yythunkpos= yythunkpos24;  if (!yymatchChar('\\')) goto l26;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\000\017\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l26;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\000\377\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l26;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\000\377\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l26;  goto l24;
  l26:;	  yypos= yypos24; yythunkpos= yythunkpos24;  if (!yymatchChar('\\')) goto l27;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\000\377\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l27;
  {  int yypos28= yypos, yythunkpos28= yythunkpos;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\000\377\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l28;  goto l29;
  l28:;	  yypos= yypos28; yythunkpos= yythunkpos28;
  }
  l29:;	  goto l24;
  l27:;	  yypos= yypos24; yythunkpos= yythunkpos24;
  {  int yypos30= yypos, yythunkpos30= yythunkpos;  if (!yymatchChar('\\')) goto l30;  goto l23;
  l30:;	  yypos= yypos30; yythunkpos= yythunkpos30;
  }  if (!yymatchDot()) goto l23;
  }
  l24:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "char", yybuf+yypos));
  return 1;
  l23:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "char", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_END()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "END"));  if (!yymatchChar('>')) goto l31;  if (!yy__()) goto l31;
  yyprintf((stderr, "  ok   %s @ %s\n", "END", yybuf+yypos));
  return 1;
  l31:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "END", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_BEGIN()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "BEGIN"));  if (!yymatchChar('<')) goto l32;  if (!yy__()) goto l32;
  yyprintf((stderr, "  ok   %s @ %s\n", "BEGIN", yybuf+yypos));
  return 1;
  l32:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "BEGIN", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_DOT()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "DOT"));  if (!yymatchChar('.')) goto l33;  if (!yy__()) goto l33;
  yyprintf((stderr, "  ok   %s @ %s\n", "DOT", yybuf+yypos));
  return 1;
  l33:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "DOT", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_class()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "class"));  if (!yymatchChar('[')) goto l34;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l34;
  l35:;	
  {  int yypos36= yypos, yythunkpos36= yythunkpos;
  {  int yypos37= yypos, yythunkpos37= yythunkpos;  if (!yymatchChar(']')) goto l37;  goto l36;
  l37:;	  yypos= yypos37; yythunkpos= yythunkpos37;
  }  if (!yy_range()) goto l36;  goto l35;
  l36:;	  yypos= yypos36; yythunkpos= yythunkpos36;
  }  yyText(yybegin, yyend);  if (!(YY_END)) goto l34;  if (!yymatchChar(']')) goto l34;  if (!yy__()) goto l34;
  yyprintf((stderr, "  ok   %s @ %s\n", "class", yybuf+yypos));
  return 1;
  l34:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "class", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_literal()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "literal"));
  {  int yypos39= yypos, yythunkpos39= yythunkpos;  if (!yymatchClass((unsigned char *)"\000\000\000\000\200\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l40;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l40;
  l41:;	
  {  int yypos42= yypos, yythunkpos42= yythunkpos;
  {  int yypos43= yypos, yythunkpos43= yythunkpos;  if (!yymatchClass((unsigned char *)"\000\000\000\000\200\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l43;  goto l42;
  l43:;	  yypos= yypos43; yythunkpos= yythunkpos43;
  }  if (!yy_char()) goto l42;  goto l41;
  l42:;	  yypos= yypos42; yythunkpos= yythunkpos42;
  }  yyText(yybegin, yyend);  if (!(YY_END)) goto l40;  if (!yymatchClass((unsigned char *)"\000\000\000\000\200\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l40;  if (!yy__()) goto l40;  goto l39;
  l40:;	  yypos= yypos39; yythunkpos= yythunkpos39;  if (!yymatchClass((unsigned char *)"\000\000\000\000\004\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l38;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l38;
  l44:;	
  {  int yypos45= yypos, yythunkpos45= yythunkpos;
  {  int yypos46= yypos, yythunkpos46= yythunkpos;  if (!yymatchClass((unsigned char *)"\000\000\000\000\004\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l46;  goto l45;
  l46:;	  yypos= yypos46; yythunkpos= yythunkpos46;
  }  if (!yy_char()) goto l45;  goto l44;
  l45:;	  yypos= yypos45; yythunkpos= yythunkpos45;
  }  yyText(yybegin, yyend);  if (!(YY_END)) goto l38;  if (!yymatchClass((unsigned char *)"\000\000\000\000\004\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l38;  if (!yy__()) goto l38;
  }
  l39:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "literal", yybuf+yypos));
  return 1;
  l38:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "literal", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_CLOSE()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "CLOSE"));  if (!yymatchChar(')')) goto l47;  if (!yy__()) goto l47;
  yyprintf((stderr, "  ok   %s @ %s\n", "CLOSE", yybuf+yypos));
  return 1;
  l47:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "CLOSE", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_OPEN()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "OPEN"));  if (!yymatchChar('(')) goto l48;  if (!yy__()) goto l48;
  yyprintf((stderr, "  ok   %s @ %s\n", "OPEN", yybuf+yypos));
  return 1;
  l48:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "OPEN", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_COLON()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "COLON"));  if (!yymatchChar(':')) goto l49;  if (!yy__()) goto l49;
  yyprintf((stderr, "  ok   %s @ %s\n", "COLON", yybuf+yypos));
  return 1;
  l49:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "COLON", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_PLUS()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "PLUS"));  if (!yymatchChar('+')) goto l50;  if (!yy__()) goto l50;
  yyprintf((stderr, "  ok   %s @ %s\n", "PLUS", yybuf+yypos));
  return 1;
  l50:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "PLUS", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_STAR()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "STAR"));  if (!yymatchChar('*')) goto l51;  if (!yy__()) goto l51;
  yyprintf((stderr, "  ok   %s @ %s\n", "STAR", yybuf+yypos));
  return 1;
  l51:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "STAR", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_QUESTION()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "QUESTION"));  if (!yymatchChar('?')) goto l52;  if (!yy__()) goto l52;
  yyprintf((stderr, "  ok   %s @ %s\n", "QUESTION", yybuf+yypos));
  return 1;
  l52:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "QUESTION", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_primary()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "primary"));
  {  int yypos54= yypos, yythunkpos54= yythunkpos;  if (!yy_identifier()) goto l55;  yyDo(yy_1_primary, yybegin, yyend);  if (!yy_COLON()) goto l55;  if (!yy_identifier()) goto l55;
  {  int yypos56= yypos, yythunkpos56= yythunkpos;  if (!yy_EQUAL()) goto l56;  goto l55;
  l56:;	  yypos= yypos56; yythunkpos= yythunkpos56;
  }  yyDo(yy_2_primary, yybegin, yyend);  goto l54;
  l55:;	  yypos= yypos54; yythunkpos= yythunkpos54;  if (!yy_identifier()) goto l57;
  {  int yypos58= yypos, yythunkpos58= yythunkpos;  if (!yy_EQUAL()) goto l58;  goto l57;
  l58:;	  yypos= yypos58; yythunkpos= yythunkpos58;
  }  yyDo(yy_3_primary, yybegin, yyend);  goto l54;
  l57:;	  yypos= yypos54; yythunkpos= yythunkpos54;  if (!yy_OPEN()) goto l59;  if (!yy_expression()) goto l59;  if (!yy_CLOSE()) goto l59;  goto l54;
  l59:;	  yypos= yypos54; yythunkpos= yythunkpos54;  if (!yy_literal()) goto l60;  yyDo(yy_4_primary, yybegin, yyend);  goto l54;
  l60:;	  yypos= yypos54; yythunkpos= yythunkpos54;  if (!yy_class()) goto l61;  yyDo(yy_5_primary, yybegin, yyend);  goto l54;
  l61:;	  yypos= yypos54; yythunkpos= yythunkpos54;  if (!yy_DOT()) goto l62;  yyDo(yy_6_primary, yybegin, yyend);  goto l54;
  l62:;	  yypos= yypos54; yythunkpos= yythunkpos54;  if (!yy_action()) goto l63;  yyDo(yy_7_primary, yybegin, yyend);  goto l54;
  l63:;	  yypos= yypos54; yythunkpos= yythunkpos54;  if (!yy_BEGIN()) goto l64;  yyDo(yy_8_primary, yybegin, yyend);  goto l54;
  l64:;	  yypos= yypos54; yythunkpos= yythunkpos54;  if (!yy_END()) goto l53;  yyDo(yy_9_primary, yybegin, yyend);
  }
  l54:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "primary", yybuf+yypos));
  return 1;
  l53:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "primary", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_NOT()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "NOT"));  if (!yymatchChar('!')) goto l65;  if (!yy__()) goto l65;
  yyprintf((stderr, "  ok   %s @ %s\n", "NOT", yybuf+yypos));
  return 1;
  l65:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "NOT", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_suffix()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "suffix"));  if (!yy_primary()) goto l66;
  {  int yypos67= yypos, yythunkpos67= yythunkpos;
  {  int yypos69= yypos, yythunkpos69= yythunkpos;  if (!yy_QUESTION()) goto l70;  yyDo(yy_1_suffix, yybegin, yyend);  goto l69;
  l70:;	  yypos= yypos69; yythunkpos= yythunkpos69;  if (!yy_STAR()) goto l71;  yyDo(yy_2_suffix, yybegin, yyend);  goto l69;
  l71:;	  yypos= yypos69; yythunkpos= yythunkpos69;  if (!yy_PLUS()) goto l67;  yyDo(yy_3_suffix, yybegin, yyend);
  }
  l69:;	  goto l68;
  l67:;	  yypos= yypos67; yythunkpos= yythunkpos67;
  }
  l68:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "suffix", yybuf+yypos));
  return 1;
  l66:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "suffix", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_action()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "action"));  if (!yymatchChar('{')) goto l72;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l72;
  l73:;	
  {  int yypos74= yypos, yythunkpos74= yythunkpos;  if (!yy_braces()) goto l74;  goto l73;
  l74:;	  yypos= yypos74; yythunkpos= yythunkpos74;
  }  yyText(yybegin, yyend);  if (!(YY_END)) goto l72;  if (!yymatchChar('}')) goto l72;  if (!yy__()) goto l72;
  yyprintf((stderr, "  ok   %s @ %s\n", "action", yybuf+yypos));
  return 1;
  l72:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "action", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_AND()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "AND"));  if (!yymatchChar('&')) goto l75;  if (!yy__()) goto l75;
  yyprintf((stderr, "  ok   %s @ %s\n", "AND", yybuf+yypos));
  return 1;
  l75:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "AND", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_prefix()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "prefix"));
  {  int yypos77= yypos, yythunkpos77= yythunkpos;  if (!yy_AND()) goto l78;  if (!yy_action()) goto l78;  yyDo(yy_1_prefix, yybegin, yyend);  goto l77;
  l78:;	  yypos= yypos77; yythunkpos= yythunkpos77;  if (!yy_AND()) goto l79;  if (!yy_suffix()) goto l79;  yyDo(yy_2_prefix, yybegin, yyend);  goto l77;
  l79:;	  yypos= yypos77; yythunkpos= yythunkpos77;  if (!yy_NOT()) goto l80;  if (!yy_suffix()) goto l80;  yyDo(yy_3_prefix, yybegin, yyend);  goto l77;
  l80:;	  yypos= yypos77; yythunkpos= yythunkpos77;  if (!yy_suffix()) goto l76;
  }
  l77:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "prefix", yybuf+yypos));
  return 1;
  l76:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "prefix", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_BAR()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "BAR"));  if (!yymatchChar('|')) goto l81;  if (!yy__()) goto l81;
  yyprintf((stderr, "  ok   %s @ %s\n", "BAR", yybuf+yypos));
  return 1;
  l81:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "BAR", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_sequence()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "sequence"));  if (!yy_prefix()) goto l82;
  l83:;	
  {  int yypos84= yypos, yythunkpos84= yythunkpos;  if (!yy_prefix()) goto l84;  yyDo(yy_1_sequence, yybegin, yyend);  goto l83;
  l84:;	  yypos= yypos84; yythunkpos= yythunkpos84;
  }
  yyprintf((stderr, "  ok   %s @ %s\n", "sequence", yybuf+yypos));
  return 1;
  l82:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "sequence", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_SEMICOLON()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "SEMICOLON"));  if (!yymatchChar(';')) goto l85;  if (!yy__()) goto l85;
  yyprintf((stderr, "  ok   %s @ %s\n", "SEMICOLON", yybuf+yypos));
  return 1;
  l85:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "SEMICOLON", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_expression()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "expression"));  if (!yy_sequence()) goto l86;
  l87:;	
  {  int yypos88= yypos, yythunkpos88= yythunkpos;  if (!yy_BAR()) goto l88;  if (!yy_sequence()) goto l88;  yyDo(yy_1_expression, yybegin, yyend);  goto l87;
  l88:;	  yypos= yypos88; yythunkpos= yythunkpos88;
  }
  yyprintf((stderr, "  ok   %s @ %s\n", "expression", yybuf+yypos));
  return 1;
  l86:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "expression", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_EQUAL()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "EQUAL"));  if (!yymatchChar('=')) goto l89;  if (!yy__()) goto l89;
  yyprintf((stderr, "  ok   %s @ %s\n", "EQUAL", yybuf+yypos));
  return 1;
  l89:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "EQUAL", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_identifier()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "identifier"));  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l90;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\040\000\000\376\377\377\207\376\377\377\007\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l90;
  l91:;	
  {  int yypos92= yypos, yythunkpos92= yythunkpos;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\040\377\003\376\377\377\207\376\377\377\007\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l92;  goto l91;
  l92:;	  yypos= yypos92; yythunkpos= yythunkpos92;
  }  yyText(yybegin, yyend);  if (!(YY_END)) goto l90;  if (!yy__()) goto l90;
  yyprintf((stderr, "  ok   %s @ %s\n", "identifier", yybuf+yypos));
  return 1;
  l90:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "identifier", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_RPERCENT()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "RPERCENT"));  if (!yymatchString("%}")) goto l93;  if (!yy__()) goto l93;
  yyprintf((stderr, "  ok   %s @ %s\n", "RPERCENT", yybuf+yypos));
  return 1;
  l93:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "RPERCENT", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_end_of_file()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "end_of_file"));
  {  int yypos95= yypos, yythunkpos95= yythunkpos;  if (!yymatchDot()) goto l95;  goto l94;
  l95:;	  yypos= yypos95; yythunkpos= yythunkpos95;
  }
  yyprintf((stderr, "  ok   %s @ %s\n", "end_of_file", yybuf+yypos));
  return 1;
  l94:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "end_of_file", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_trailer()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "trailer"));  if (!yymatchString("%%")) goto l96;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l96;
  l97:;	
  {  int yypos98= yypos, yythunkpos98= yythunkpos;  if (!yymatchDot()) goto l98;  goto l97;
  l98:;	  yypos= yypos98; yythunkpos= yythunkpos98;
  }  yyText(yybegin, yyend);  if (!(YY_END)) goto l96;  yyDo(yy_1_trailer, yybegin, yyend);
  yyprintf((stderr, "  ok   %s @ %s\n", "trailer", yybuf+yypos));
  return 1;
  l96:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "trailer", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_definition()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "definition"));  if (!yy_identifier()) goto l99;  yyDo(yy_1_definition, yybegin, yyend);  if (!yy_EQUAL()) goto l99;  if (!yy_expression()) goto l99;  yyDo(yy_2_definition, yybegin, yyend);
  {  int yypos100= yypos, yythunkpos100= yythunkpos;  if (!yy_SEMICOLON()) goto l100;  goto l101;
  l100:;	  yypos= yypos100; yythunkpos= yythunkpos100;
  }
  l101:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "definition", yybuf+yypos));
  return 1;
  l99:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "definition", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_declaration()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "declaration"));  if (!yymatchString("%{")) goto l102;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l102;
  l103:;	
  {  int yypos104= yypos, yythunkpos104= yythunkpos;
  {  int yypos105= yypos, yythunkpos105= yythunkpos;  if (!yymatchString("%}")) goto l105;  goto l104;
  l105:;	  yypos= yypos105; yythunkpos= yythunkpos105;
  }  if (!yymatchDot()) goto l104;  goto l103;
  l104:;	  yypos= yypos104; yythunkpos= yythunkpos104;
  }  yyText(yybegin, yyend);  if (!(YY_END)) goto l102;  if (!yy_RPERCENT()) goto l102;  yyDo(yy_1_declaration, yybegin, yyend);
  yyprintf((stderr, "  ok   %s @ %s\n", "declaration", yybuf+yypos));
  return 1;
  l102:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "declaration", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy__()
{
  yyprintf((stderr, "%s\n", "_"));
  l107:;	
  {  int yypos108= yypos, yythunkpos108= yythunkpos;
  {  int yypos109= yypos, yythunkpos109= yythunkpos;  if (!yy_space()) goto l110;  goto l109;
  l110:;	  yypos= yypos109; yythunkpos= yythunkpos109;  if (!yy_comment()) goto l108;
  }
  l109:;	  goto l107;
  l108:;	  yypos= yypos108; yythunkpos= yythunkpos108;
  }
  yyprintf((stderr, "  ok   %s @ %s\n", "_", yybuf+yypos));
  return 1;
}
YY_RULE(int) yy_grammar()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "grammar"));  if (!yy__()) goto l111;
  {  int yypos114= yypos, yythunkpos114= yythunkpos;  if (!yy_declaration()) goto l115;  goto l114;
  l115:;	  yypos= yypos114; yythunkpos= yythunkpos114;  if (!yy_definition()) goto l111;
  }
  l114:;	
  l112:;	
  {  int yypos113= yypos, yythunkpos113= yythunkpos;
  {  int yypos116= yypos, yythunkpos116= yythunkpos;  if (!yy_declaration()) goto l117;  goto l116;
  l117:;	  yypos= yypos116; yythunkpos= yythunkpos116;  if (!yy_definition()) goto l113;
  }
  l116:;	  goto l112;
  l113:;	  yypos= yypos113; yythunkpos= yythunkpos113;
  }
  {  int yypos118= yypos, yythunkpos118= yythunkpos;  if (!yy_trailer()) goto l118;  goto l119;
  l118:;	  yypos= yypos118; yythunkpos= yythunkpos118;
  }
  l119:;	  if (!yy_end_of_file()) goto l111;
  yyprintf((stderr, "  ok   %s @ %s\n", "grammar", yybuf+yypos));
  return 1;
  l111:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "grammar", yybuf+yypos));
  return 0;
}

#ifndef YY_PART

typedef int (*yyrule)();

YY_PARSE(int) YYPARSEFROM(yyrule yystart)
{
  int yyok;
  if (!yybuflen)
    {
      yybuflen= 1024;
      yybuf= malloc(yybuflen);
      yytextlen= 1024;
      yytext= malloc(yytextlen);
      yythunkslen= 32;
      yythunks= malloc(sizeof(yythunk) * yythunkslen);
      yyvalslen= 32;
      yyvals= malloc(sizeof(YYSTYPE) * yyvalslen);
      yybegin= yyend= yypos= yylimit= yythunkpos= 0;
    }
  yybegin= yyend= yypos;
  yythunkpos= 0;
  yyval= yyvals;
  yyok= yystart();
  if (yyok) yyDone();
  yyCommit();
  return yyok;
  (void)yyrefill;
  (void)yymatchDot;
  (void)yymatchChar;
  (void)yymatchString;
  (void)yymatchClass;
  (void)yyDo;
  (void)yyText;
  (void)yyDone;
  (void)yyCommit;
  (void)yyAccept;
  (void)yyPush;
  (void)yyPop;
  (void)yySet;
  (void)yytextmax;
}

YY_PARSE(int) YYPARSE(void)
{
  return YYPARSEFROM(yy_grammar);
}

#endif


void yyerror(char *message)
{
  fprintf(stderr, "%s:%d: %s", fileName, lineNumber, message);
  if (yytext[0]) fprintf(stderr, " near token '%s'", yytext);
  if (yypos < yylimit || !feof(input))
    {
      yybuf[yylimit]= '\0';
      fprintf(stderr, " before text \"");
      while (yypos < yylimit)
	{
	  if ('\n' == yybuf[yypos] || '\r' == yybuf[yypos]) break;
	  fputc(yybuf[yypos++], stderr);
	}
      if (yypos == yylimit)
	{
	  int c;
	  while (EOF != (c= fgetc(input)) && '\n' != c && '\r' != c)
	    fputc(c, stderr);
	}
      fputc('\"', stderr);
    }
  fprintf(stderr, "\n");
  exit(1);
}

void makeHeader(char *text)
{
  Header *header= (Header *)malloc(sizeof(Header));
  header->text= strdup(text);
  header->next= headers;
  headers= header;
}

void makeTrailer(char *text)
{
  trailer= strdup(text);
}

static void version(char *name)
{
  printf("%s version %d.%d.%d\n", name, GREG_MAJOR, GREG_MINOR, GREG_LEVEL);
}

static void usage(char *name)
{
  version(name);
  fprintf(stderr, "usage: %s [<option>...] [<file>...]\n", name);
  fprintf(stderr, "where <option> can be\n");
  fprintf(stderr, "  -h          print this help information\n");
  fprintf(stderr, "  -o <ofile>  write output to <ofile>\n");
  fprintf(stderr, "  -v          be verbose\n");
  fprintf(stderr, "  -V          print version number and exit\n");
  fprintf(stderr, "if no <file> is given, input is read from stdin\n");
  fprintf(stderr, "if no <ofile> is given, output is written to stdout\n");
  exit(1);
}

int main(int argc, char **argv)
{
  Node *n;
  int   c;

  output= stdout;
  input= stdin;
  lineNumber= 1;
  fileName= "<stdin>";

  while (-1 != (c= getopt(argc, argv, "Vho:v")))
    {
      switch (c)
	{
	case 'V':
	  version(basename(argv[0]));
	  exit(0);

	case 'h':
	  usage(basename(argv[0]));
	  break;

	case 'o':
	  if (!(output= fopen(optarg, "w")))
	    {
	      perror(optarg);
	      exit(1);
	    }
	  break;

	case 'v':
	  verboseFlag= 1;
	  break;

	default:
	  fprintf(stderr, "for usage try: %s -h\n", argv[0]);
	  exit(1);
	}
    }
  argc -= optind;
  argv += optind;

  if (argc)
    {
      for (;  argc;  --argc, ++argv)
	{
	  if (!strcmp(*argv, "-"))
	    {
	      input= stdin;
	      fileName= "<stdin>";
	    }
	  else
	    {
	      if (!(input= fopen(*argv, "r")))
		{
		  perror(*argv);
		  exit(1);
		}
	      fileName= *argv;
	    }
	  lineNumber= 1;
	  if (!yyparse())
	    yyerror("syntax error");
	  if (input != stdin)
	    fclose(input);
	}
    }
  else
    if (!yyparse())
      yyerror("syntax error");

  if (verboseFlag)
    for (n= rules;  n;  n= n->any.next)
      Rule_print(n);

  Rule_compile_c_header();

  for (; headers;  headers= headers->next)
    fprintf(output, "%s\n", headers->text);

  if (rules)
    Rule_compile_c(rules);

  if (trailer)
    fprintf(output, "%s\n", trailer);

  return 0;
}

