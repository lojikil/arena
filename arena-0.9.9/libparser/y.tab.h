#ifndef BISON_Y_TAB_H
# define BISON_Y_TAB_H

#ifndef YYSTYPE
typedef union {
	char *string;
	int unused;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
# define	CONST_BOOL	257
# define	CONST_INT	258
# define	CONST_FLOAT	259
# define	CONST_STRING	260
# define	KW_INC	261
# define	KW_IF	262
# define	KW_ELSE	263
# define	KW_WHILE	264
# define	KW_DO	265
# define	KW_RETURN	266
# define	KW_FOR	267
# define	KW_CONTINUE	268
# define	KW_BREAK	269
# define	KW_SWITCH	270
# define	KW_CASE	271
# define	KW_DEFAULT	272
# define	KW_FORCE	273
# define	KW_TRY	274
# define	KW_THROW	275
# define	KW_CATCH	276
# define	KW_TMPL	277
# define	KW_EXTENDS	278
# define	KW_NEW	279
# define	KW_STATIC	280
# define	KW_FILE	281
# define	KW_LINE	282
# define	TYPE_VOID	283
# define	TYPE_BOOL	284
# define	TYPE_INT	285
# define	TYPE_FLOAT	286
# define	TYPE_STRING	287
# define	TYPE_ARRAY	288
# define	TYPE_STRUCT	289
# define	TYPE_FN	290
# define	TYPE_RES	291
# define	TYPE_MIXED	292
# define	OP_ASSIGN	293
# define	OP_APLUS	294
# define	OP_AMINUS	295
# define	OP_AMUL	296
# define	OP_ADIV	297
# define	OP_AAND	298
# define	OP_AOR	299
# define	OP_AXOR	300
# define	OP_ALSHIFT	301
# define	OP_ARSHIFT	302
# define	OP_BOOL_OR	303
# define	OP_BOOL_AND	304
# define	OP_NOT	305
# define	OP_EQUAL	306
# define	OP_NOT_EQUAL	307
# define	OP_SEQ	308
# define	OP_LEQ	309
# define	OP_SMALLER	310
# define	OP_LARGER	311
# define	OP_AND	312
# define	OP_OR	313
# define	OP_XOR	314
# define	OP_PLUS	315
# define	OP_MINUS	316
# define	OP_MUL	317
# define	OP_DIV	318
# define	OP_MOD	319
# define	OP_POW	320
# define	OP_LSHIFT	321
# define	OP_RSHIFT	322
# define	UNARY_MINUS	323
# define	OP_NEG	324
# define	OP_PLUSPLUS	325
# define	OP_MINUSMINUS	326
# define	CAST_VOID	327
# define	CAST_BOOL	328
# define	CAST_INT	329
# define	CAST_UINT	330
# define	CAST_FLOAT	331
# define	CAST_STRING	332
# define	CAST_ARRAY	333
# define	CAST_STRUCT	334
# define	ID	335


extern YYSTYPE yylval;

#endif /* not BISON_Y_TAB_H */
