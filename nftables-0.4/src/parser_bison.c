/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1

/* Substitute the variable and function names.  */
#define yyparse         nft_parse
#define yylex           nft_lex
#define yyerror         nft_error
#define yylval          nft_lval
#define yychar          nft_char
#define yydebug         nft_debug
#define yynerrs         nft_nerrs
#define yylloc          nft_lloc

/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 11 "parser_bison.y"


#include <stddef.h>
#include <stdio.h>
#include <inttypes.h>
#include <syslog.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include <linux/netfilter.h>
#include <linux/netfilter/nf_tables.h>
#include <linux/netfilter/nf_conntrack_tuple_common.h>
#include <linux/netfilter/nf_nat.h>
#include <netinet/ip_icmp.h>
#include <netinet/icmp6.h>
#include <libnftnl/common.h>
#include <libnftnl/set.h>

#include <rule.h>
#include <statement.h>
#include <expression.h>
#include <utils.h>
#include <parser.h>
#include <erec.h>

#include "parser_bison.h"

void parser_init(struct parser_state *state, struct list_head *msgs)
{
	memset(state, 0, sizeof(*state));
	init_list_head(&state->cmds);
	init_list_head(&state->top_scope.symbols);
	state->msgs = msgs;
	state->scopes[0] = scope_init(&state->top_scope, NULL);
	state->ectx.msgs = msgs;
}

static void yyerror(struct location *loc, void *scanner,
		    struct parser_state *state, const char *s)
{
	erec_queue(error(loc, "%s", s), state->msgs);
}

static struct scope *current_scope(const struct parser_state *state)
{
	return state->scopes[state->scope];
}

static void open_scope(struct parser_state *state, struct scope *scope)
{
	assert(state->scope < array_size(state->scopes) - 1);
	scope_init(scope, current_scope(state));
	state->scopes[++state->scope] = scope;
}

static void close_scope(struct parser_state *state)
{
	assert(state->scope > 0);
	state->scope--;
}

static void location_init(void *scanner, struct parser_state *state,
			  struct location *loc)
{
	memset(loc, 0, sizeof(*loc));
	loc->indesc = state->indesc;
}

static void location_update(struct location *loc, struct location *rhs, int n)
{
	if (n) {
		loc->indesc       = rhs[n].indesc;
		loc->token_offset = rhs[1].token_offset;
		loc->line_offset  = rhs[1].line_offset;
		loc->first_line   = rhs[1].first_line;
		loc->first_column = rhs[1].first_column;
		loc->last_line    = rhs[n].last_line;
		loc->last_column  = rhs[n].last_column;
	} else {
		loc->indesc       = rhs[0].indesc;
		loc->token_offset = rhs[0].token_offset;
		loc->line_offset  = rhs[0].line_offset;
		loc->first_line   = loc->last_line   = rhs[0].last_line;
		loc->first_column = loc->last_column = rhs[0].last_column;
	}
}

#define YYLLOC_DEFAULT(Current, Rhs, N)	location_update(&Current, Rhs, N)



/* Line 268 of yacc.c  */
#line 170 "parser_bison.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOKEN_EOF = 0,
     JUNK = 258,
     NEWLINE = 259,
     COLON = 260,
     SEMICOLON = 261,
     COMMA = 262,
     DOT = 263,
     EQ = 264,
     NEQ = 265,
     LT = 266,
     GT = 267,
     GTE = 268,
     LTE = 269,
     LSHIFT = 270,
     RSHIFT = 271,
     AMPERSAND = 272,
     CARET = 273,
     NOT = 274,
     SLASH = 275,
     ASTERISK = 276,
     DASH = 277,
     AT = 278,
     VMAP = 279,
     INCLUDE = 280,
     DEFINE = 281,
     HOOK = 282,
     TABLE = 283,
     TABLES = 284,
     CHAIN = 285,
     CHAINS = 286,
     RULE = 287,
     RULES = 288,
     SETS = 289,
     SET = 290,
     ELEMENT = 291,
     MAP = 292,
     HANDLE = 293,
     RULESET = 294,
     INET = 295,
     ADD = 296,
     CREATE = 297,
     INSERT = 298,
     DELETE = 299,
     LIST = 300,
     FLUSH = 301,
     RENAME = 302,
     DESCRIBE = 303,
     EXPORT = 304,
     MONITOR = 305,
     ACCEPT = 306,
     DROP = 307,
     CONTINUE = 308,
     JUMP = 309,
     GOTO = 310,
     RETURN = 311,
     TO = 312,
     CONSTANT = 313,
     INTERVAL = 314,
     ELEMENTS = 315,
     POLICY = 316,
     MEMORY = 317,
     PERFORMANCE = 318,
     SIZE = 319,
     NUM = 320,
     STRING = 321,
     QUOTED_STRING = 322,
     ERROR = 323,
     LL_HDR = 324,
     NETWORK_HDR = 325,
     TRANSPORT_HDR = 326,
     BRIDGE = 327,
     ETHER = 328,
     SADDR = 329,
     DADDR = 330,
     TYPE = 331,
     VLAN = 332,
     ID = 333,
     CFI = 334,
     PCP = 335,
     ARP = 336,
     HTYPE = 337,
     PTYPE = 338,
     HLEN = 339,
     PLEN = 340,
     OPERATION = 341,
     IP = 342,
     VERSION = 343,
     HDRLENGTH = 344,
     TOS = 345,
     LENGTH = 346,
     FRAG_OFF = 347,
     TTL = 348,
     PROTOCOL = 349,
     CHECKSUM = 350,
     ICMP = 351,
     CODE = 352,
     SEQUENCE = 353,
     GATEWAY = 354,
     MTU = 355,
     IP6 = 356,
     PRIORITY = 357,
     FLOWLABEL = 358,
     NEXTHDR = 359,
     HOPLIMIT = 360,
     ICMP6 = 361,
     PPTR = 362,
     MAXDELAY = 363,
     AH = 364,
     RESERVED = 365,
     SPI = 366,
     ESP = 367,
     COMP = 368,
     FLAGS = 369,
     CPI = 370,
     UDP = 371,
     SPORT = 372,
     DPORT = 373,
     UDPLITE = 374,
     CSUMCOV = 375,
     TCP = 376,
     ACKSEQ = 377,
     DOFF = 378,
     WINDOW = 379,
     URGPTR = 380,
     DCCP = 381,
     SCTP = 382,
     VTAG = 383,
     RT = 384,
     RT0 = 385,
     RT2 = 386,
     SEG_LEFT = 387,
     ADDR = 388,
     HBH = 389,
     FRAG = 390,
     RESERVED2 = 391,
     MORE_FRAGMENTS = 392,
     DST = 393,
     MH = 394,
     META = 395,
     NFPROTO = 396,
     L4PROTO = 397,
     MARK = 398,
     IIF = 399,
     IIFNAME = 400,
     IIFTYPE = 401,
     OIF = 402,
     OIFNAME = 403,
     OIFTYPE = 404,
     SKUID = 405,
     SKGID = 406,
     NFTRACE = 407,
     RTCLASSID = 408,
     IBRIPORT = 409,
     OBRIPORT = 410,
     PKTTYPE = 411,
     CPU = 412,
     IIFGROUP = 413,
     OIFGROUP = 414,
     CGROUP = 415,
     CT = 416,
     DIRECTION = 417,
     STATE = 418,
     STATUS = 419,
     EXPIRATION = 420,
     HELPER = 421,
     L3PROTOCOL = 422,
     PROTO_SRC = 423,
     PROTO_DST = 424,
     LABEL = 425,
     COUNTER = 426,
     PACKETS = 427,
     BYTES = 428,
     LOG = 429,
     PREFIX = 430,
     GROUP = 431,
     SNAPLEN = 432,
     QUEUE_THRESHOLD = 433,
     LEVEL = 434,
     LEVEL_EMERG = 435,
     LEVEL_ALERT = 436,
     LEVEL_CRIT = 437,
     LEVEL_ERR = 438,
     LEVEL_WARN = 439,
     LEVEL_NOTICE = 440,
     LEVEL_INFO = 441,
     LEVEL_DEBUG = 442,
     LIMIT = 443,
     RATE = 444,
     NANOSECOND = 445,
     MICROSECOND = 446,
     MILLISECOND = 447,
     SECOND = 448,
     MINUTE = 449,
     HOUR = 450,
     DAY = 451,
     WEEK = 452,
     _REJECT = 453,
     RESET = 454,
     WITH = 455,
     ICMPX = 456,
     SNAT = 457,
     DNAT = 458,
     MASQUERADE = 459,
     REDIRECT = 460,
     RANDOM = 461,
     FULLY_RANDOM = 462,
     PERSISTENT = 463,
     QUEUE = 464,
     QUEUENUM = 465,
     BYPASS = 466,
     FANOUT = 467,
     POSITION = 468,
     COMMENT = 469,
     XML = 470,
     JSON = 471
   };
#endif
/* Tokens.  */
#define TOKEN_EOF 0
#define JUNK 258
#define NEWLINE 259
#define COLON 260
#define SEMICOLON 261
#define COMMA 262
#define DOT 263
#define EQ 264
#define NEQ 265
#define LT 266
#define GT 267
#define GTE 268
#define LTE 269
#define LSHIFT 270
#define RSHIFT 271
#define AMPERSAND 272
#define CARET 273
#define NOT 274
#define SLASH 275
#define ASTERISK 276
#define DASH 277
#define AT 278
#define VMAP 279
#define INCLUDE 280
#define DEFINE 281
#define HOOK 282
#define TABLE 283
#define TABLES 284
#define CHAIN 285
#define CHAINS 286
#define RULE 287
#define RULES 288
#define SETS 289
#define SET 290
#define ELEMENT 291
#define MAP 292
#define HANDLE 293
#define RULESET 294
#define INET 295
#define ADD 296
#define CREATE 297
#define INSERT 298
#define DELETE 299
#define LIST 300
#define FLUSH 301
#define RENAME 302
#define DESCRIBE 303
#define EXPORT 304
#define MONITOR 305
#define ACCEPT 306
#define DROP 307
#define CONTINUE 308
#define JUMP 309
#define GOTO 310
#define RETURN 311
#define TO 312
#define CONSTANT 313
#define INTERVAL 314
#define ELEMENTS 315
#define POLICY 316
#define MEMORY 317
#define PERFORMANCE 318
#define SIZE 319
#define NUM 320
#define STRING 321
#define QUOTED_STRING 322
#define ERROR 323
#define LL_HDR 324
#define NETWORK_HDR 325
#define TRANSPORT_HDR 326
#define BRIDGE 327
#define ETHER 328
#define SADDR 329
#define DADDR 330
#define TYPE 331
#define VLAN 332
#define ID 333
#define CFI 334
#define PCP 335
#define ARP 336
#define HTYPE 337
#define PTYPE 338
#define HLEN 339
#define PLEN 340
#define OPERATION 341
#define IP 342
#define VERSION 343
#define HDRLENGTH 344
#define TOS 345
#define LENGTH 346
#define FRAG_OFF 347
#define TTL 348
#define PROTOCOL 349
#define CHECKSUM 350
#define ICMP 351
#define CODE 352
#define SEQUENCE 353
#define GATEWAY 354
#define MTU 355
#define IP6 356
#define PRIORITY 357
#define FLOWLABEL 358
#define NEXTHDR 359
#define HOPLIMIT 360
#define ICMP6 361
#define PPTR 362
#define MAXDELAY 363
#define AH 364
#define RESERVED 365
#define SPI 366
#define ESP 367
#define COMP 368
#define FLAGS 369
#define CPI 370
#define UDP 371
#define SPORT 372
#define DPORT 373
#define UDPLITE 374
#define CSUMCOV 375
#define TCP 376
#define ACKSEQ 377
#define DOFF 378
#define WINDOW 379
#define URGPTR 380
#define DCCP 381
#define SCTP 382
#define VTAG 383
#define RT 384
#define RT0 385
#define RT2 386
#define SEG_LEFT 387
#define ADDR 388
#define HBH 389
#define FRAG 390
#define RESERVED2 391
#define MORE_FRAGMENTS 392
#define DST 393
#define MH 394
#define META 395
#define NFPROTO 396
#define L4PROTO 397
#define MARK 398
#define IIF 399
#define IIFNAME 400
#define IIFTYPE 401
#define OIF 402
#define OIFNAME 403
#define OIFTYPE 404
#define SKUID 405
#define SKGID 406
#define NFTRACE 407
#define RTCLASSID 408
#define IBRIPORT 409
#define OBRIPORT 410
#define PKTTYPE 411
#define CPU 412
#define IIFGROUP 413
#define OIFGROUP 414
#define CGROUP 415
#define CT 416
#define DIRECTION 417
#define STATE 418
#define STATUS 419
#define EXPIRATION 420
#define HELPER 421
#define L3PROTOCOL 422
#define PROTO_SRC 423
#define PROTO_DST 424
#define LABEL 425
#define COUNTER 426
#define PACKETS 427
#define BYTES 428
#define LOG 429
#define PREFIX 430
#define GROUP 431
#define SNAPLEN 432
#define QUEUE_THRESHOLD 433
#define LEVEL 434
#define LEVEL_EMERG 435
#define LEVEL_ALERT 436
#define LEVEL_CRIT 437
#define LEVEL_ERR 438
#define LEVEL_WARN 439
#define LEVEL_NOTICE 440
#define LEVEL_INFO 441
#define LEVEL_DEBUG 442
#define LIMIT 443
#define RATE 444
#define NANOSECOND 445
#define MICROSECOND 446
#define MILLISECOND 447
#define SECOND 448
#define MINUTE 449
#define HOUR 450
#define DAY 451
#define WEEK 452
#define _REJECT 453
#define RESET 454
#define WITH 455
#define ICMPX 456
#define SNAT 457
#define DNAT 458
#define MASQUERADE 459
#define REDIRECT 460
#define RANDOM 461
#define FULLY_RANDOM 462
#define PERSISTENT 463
#define QUEUE 464
#define QUEUENUM 465
#define BYPASS 466
#define FANOUT 467
#define POSITION 468
#define COMMENT 469
#define XML 470
#define JSON 471




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 122 "parser_bison.y"

	uint64_t		val;
	const char *		string;

	struct list_head	*list;
	struct cmd		*cmd;
	struct handle		handle;
	struct table		*table;
	struct chain		*chain;
	struct rule		*rule;
	struct stmt		*stmt;
	struct expr		*expr;
	struct set		*set;



/* Line 293 of yacc.c  */
#line 657 "parser_bison.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 682 "parser_bison.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2166

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  226
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  169
/* YYNRULES -- Number of rules.  */
#define YYNRULES  504
/* YYNRULES -- Number of states.  */
#define YYNSTATES  706

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   471

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,   220,     2,     2,     2,
     221,   222,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   217,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   224,     2,   225,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   218,   223,   219,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,     9,    11,    13,    14,    18,
      24,    27,    29,    31,    34,    37,    39,    42,    45,    48,
      51,    54,    57,    60,    63,    66,    69,    72,    79,    82,
      89,    93,    96,   103,   110,   114,   117,   124,   127,   134,
     138,   141,   144,   147,   150,   153,   157,   160,   163,   166,
     169,   172,   175,   178,   181,   184,   187,   191,   193,   197,
     198,   200,   201,   203,   205,   207,   209,   211,   212,   214,
     216,   218,   220,   221,   222,   225,   228,   237,   246,   255,
     256,   257,   260,   263,   267,   271,   272,   273,   276,   279,
     284,   289,   294,   298,   302,   304,   306,   308,   309,   310,
     313,   316,   323,   328,   333,   337,   340,   343,   345,   347,
     354,   362,   364,   366,   368,   369,   371,   373,   375,   377,
     379,   381,   384,   386,   389,   391,   394,   396,   397,   400,
     401,   404,   408,   409,   412,   413,   415,   418,   420,   423,
     425,   427,   429,   431,   433,   435,   437,   439,   441,   443,
     445,   447,   449,   451,   455,   459,   462,   464,   468,   472,
     478,   480,   483,   485,   487,   490,   493,   496,   498,   501,
     503,   505,   508,   511,   514,   517,   520,   523,   525,   527,
     529,   531,   533,   535,   537,   539,   545,   547,   549,   551,
     553,   555,   558,   560,   561,   566,   571,   576,   580,   583,
     585,   587,   589,   593,   596,   599,   601,   604,   606,   609,
     611,   613,   616,   618,   622,   624,   628,   630,   632,   634,
     636,   639,   641,   643,   646,   649,   651,   653,   657,   659,
     661,   663,   665,   668,   671,   673,   675,   677,   679,   681,
     683,   685,   689,   691,   695,   699,   701,   705,   707,   711,
     713,   717,   719,   721,   725,   729,   733,   737,   741,   743,
     745,   747,   749,   751,   753,   757,   759,   761,   763,   765,
     767,   769,   773,   775,   779,   783,   787,   793,   799,   801,
     803,   806,   809,   813,   815,   817,   819,   821,   823,   825,
     827,   829,   831,   834,   837,   839,   842,   844,   846,   848,
     850,   852,   854,   856,   858,   860,   862,   864,   866,   868,
     870,   872,   874,   876,   878,   880,   882,   884,   886,   888,
     890,   892,   894,   899,   903,   906,   908,   910,   912,   914,
     916,   918,   920,   922,   924,   926,   928,   930,   932,   937,
     939,   941,   943,   945,   947,   949,   951,   953,   955,   957,
     959,   961,   963,   965,   967,   969,   976,   978,   980,   982,
     985,   987,   989,   991,   993,   996,   998,  1000,  1002,  1004,
    1006,  1009,  1011,  1013,  1015,  1017,  1019,  1021,  1024,  1026,
    1028,  1030,  1032,  1034,  1036,  1038,  1040,  1042,  1044,  1046,
    1048,  1051,  1053,  1055,  1057,  1059,  1061,  1063,  1065,  1067,
    1070,  1072,  1074,  1076,  1078,  1080,  1082,  1084,  1086,  1088,
    1091,  1093,  1095,  1097,  1099,  1101,  1103,  1105,  1107,  1109,
    1112,  1114,  1116,  1118,  1120,  1122,  1124,  1127,  1129,  1131,
    1133,  1136,  1138,  1140,  1142,  1144,  1147,  1149,  1151,  1153,
    1155,  1157,  1160,  1162,  1164,  1166,  1168,  1170,  1173,  1175,
    1177,  1179,  1181,  1183,  1185,  1187,  1189,  1191,  1193,  1195,
    1198,  1200,  1202,  1204,  1206,  1209,  1211,  1213,  1215,  1217,
    1219,  1221,  1223,  1225,  1227,  1229,  1231,  1233,  1236,  1238,
    1240,  1243,  1245,  1247,  1249,  1251,  1254,  1259,  1262,  1264,
    1267,  1269,  1271,  1273,  1275,  1277,  1279,  1282,  1284,  1286,
    1289,  1291,  1293,  1295,  1297
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     227,     0,    -1,    -1,   227,   231,    -1,     4,    -1,     6,
      -1,     4,    -1,    -1,    25,    67,   228,    -1,    26,   260,
     217,   335,   228,    -1,     1,   228,    -1,   230,    -1,   228,
      -1,   232,   228,    -1,   232,     0,    -1,   233,    -1,    41,
     233,    -1,    42,   234,    -1,    43,   235,    -1,    44,   236,
      -1,    45,   237,    -1,    46,   238,    -1,    47,   239,    -1,
      49,   240,    -1,    50,   241,    -1,    48,   246,    -1,    28,
     264,    -1,    28,   264,   247,   218,   248,   219,    -1,    30,
     266,    -1,    30,   266,   249,   218,   250,   219,    -1,    32,
     272,   275,    -1,   272,   275,    -1,    35,   268,   251,   218,
     252,   219,    -1,    37,   268,   255,   218,   256,   219,    -1,
      36,   268,   332,    -1,    28,   264,    -1,    28,   264,   247,
     218,   248,   219,    -1,    30,   266,    -1,    30,   266,   249,
     218,   250,   219,    -1,    32,   272,   275,    -1,    28,   264,
      -1,    30,   266,    -1,    32,   272,    -1,    35,   268,    -1,
      37,   268,    -1,    36,   268,   332,    -1,    28,   264,    -1,
      29,   265,    -1,    30,   266,    -1,    34,   265,    -1,    35,
     268,    -1,    39,   274,    -1,    28,   264,    -1,    30,   266,
      -1,    35,   268,    -1,    39,   274,    -1,    30,   266,   260,
      -1,   245,    -1,   242,   243,   244,    -1,    -1,    66,    -1,
      -1,    29,    -1,    31,    -1,    34,    -1,    33,    -1,    60,
      -1,    -1,   245,    -1,   215,    -1,   216,    -1,   316,    -1,
      -1,    -1,   248,   230,    -1,   248,   228,    -1,   248,    30,
     267,   249,   218,   250,   219,   228,    -1,   248,    35,   269,
     251,   218,   252,   219,   228,    -1,   248,    37,   269,   255,
     218,   256,   219,   228,    -1,    -1,    -1,   250,   230,    -1,
     250,   228,    -1,   250,   259,   228,    -1,   250,   275,   228,
      -1,    -1,    -1,   252,   230,    -1,   252,   228,    -1,   252,
      76,   260,   228,    -1,   252,   114,   253,   228,    -1,   252,
      60,   217,   332,    -1,   252,   257,   228,    -1,   253,     7,
     254,    -1,   254,    -1,    58,    -1,    59,    -1,    -1,    -1,
     256,   230,    -1,   256,   228,    -1,   256,    76,   260,     5,
     260,   228,    -1,   256,   114,   253,   228,    -1,   256,    60,
     217,   332,    -1,   256,   257,   228,    -1,    61,   258,    -1,
      64,    65,    -1,    63,    -1,    62,    -1,    76,    66,    27,
      66,   102,    65,    -1,    76,    66,    27,    66,   102,    22,
      65,    -1,    66,    -1,    66,    -1,    67,    -1,    -1,   263,
      -1,    87,    -1,   101,    -1,    40,    -1,    81,    -1,    72,
      -1,   262,   260,    -1,   262,    -1,   264,   260,    -1,   260,
      -1,   264,   260,    -1,   260,    -1,    -1,    38,    65,    -1,
      -1,   213,    65,    -1,   266,   270,   271,    -1,    -1,   214,
     261,    -1,    -1,   263,    -1,   276,   273,    -1,   277,    -1,
     276,   277,    -1,   278,    -1,   313,    -1,   283,    -1,   343,
      -1,   287,    -1,   292,    -1,   294,    -1,   297,    -1,   307,
      -1,   346,    -1,   300,    -1,   302,    -1,   338,    -1,   279,
      -1,   322,    24,   280,    -1,   218,   281,   219,    -1,    23,
     260,    -1,   282,    -1,   281,     7,   282,    -1,   281,     7,
     229,    -1,   229,   328,     5,   338,   229,    -1,   284,    -1,
     284,   285,    -1,   171,    -1,   286,    -1,   285,   286,    -1,
     172,    65,    -1,   173,    65,    -1,   288,    -1,   288,   289,
      -1,   174,    -1,   290,    -1,   289,   290,    -1,   175,   261,
      -1,   176,    65,    -1,   177,    65,    -1,   178,    65,    -1,
     179,   291,    -1,   180,    -1,   181,    -1,   182,    -1,   183,
      -1,   184,    -1,   185,    -1,   186,    -1,   187,    -1,   188,
     189,    65,    20,   293,    -1,   193,    -1,   194,    -1,   195,
      -1,   196,    -1,   197,    -1,   295,   296,    -1,   198,    -1,
      -1,   200,    96,    76,    66,    -1,   200,   106,    76,    66,
      -1,   200,   201,    76,    66,    -1,   200,   121,   199,    -1,
     298,   299,    -1,   202,    -1,   203,    -1,   330,    -1,   330,
       5,   330,    -1,     5,   330,    -1,   299,   305,    -1,   301,
      -1,   301,   305,    -1,   204,    -1,   303,   304,    -1,   303,
      -1,   205,    -1,    57,   330,    -1,   305,    -1,    57,   330,
     305,    -1,   306,    -1,   305,     7,   306,    -1,   206,    -1,
     207,    -1,   208,    -1,   308,    -1,   308,   309,    -1,   209,
      -1,   310,    -1,   309,   310,    -1,   210,   330,    -1,   311,
      -1,   312,    -1,   311,     7,   312,    -1,   211,    -1,   212,
      -1,   336,    -1,   261,    -1,   220,   260,    -1,    23,   260,
      -1,    65,    -1,   314,    -1,   315,    -1,   347,    -1,   380,
      -1,   339,    -1,   344,    -1,   221,   321,   222,    -1,   316,
      -1,   317,    15,   316,    -1,   317,    16,   316,    -1,   317,
      -1,   318,    17,   317,    -1,   318,    -1,   319,    18,   318,
      -1,   319,    -1,   320,   223,   319,    -1,   320,    -1,   321,
      -1,   322,     8,   321,    -1,   321,     7,   321,    -1,   323,
       7,   321,    -1,   321,    20,    65,    -1,   321,    22,   321,
      -1,    21,    -1,   324,    -1,   325,    -1,   326,    -1,   327,
      -1,   322,    -1,   322,    37,   330,    -1,   322,    -1,   332,
      -1,   329,    -1,   327,    -1,   331,    -1,    68,    -1,   218,
     333,   219,    -1,   334,    -1,   333,     7,   334,    -1,   333,
       7,   229,    -1,   229,   330,   229,    -1,   229,   328,     5,
     322,   229,    -1,   229,   328,     5,   338,   229,    -1,   330,
      -1,   323,    -1,   330,   330,    -1,   330,   323,    -1,   330,
     337,   330,    -1,     9,    -1,    10,    -1,    11,    -1,    12,
      -1,    13,    -1,    14,    -1,    51,    -1,    52,    -1,    53,
      -1,    54,   260,    -1,    55,   260,    -1,    56,    -1,   140,
     340,    -1,   342,    -1,   341,    -1,   342,    -1,    91,    -1,
     141,    -1,   142,    -1,    94,    -1,   102,    -1,   143,    -1,
     144,    -1,   145,    -1,   146,    -1,   147,    -1,   148,    -1,
     149,    -1,   150,    -1,   151,    -1,   152,    -1,   153,    -1,
     154,    -1,   155,    -1,   156,    -1,   157,    -1,   158,    -1,
     159,    -1,   160,    -1,   140,   340,    35,   330,    -1,   342,
      35,   330,    -1,   161,   345,    -1,   163,    -1,   162,    -1,
     164,    -1,   143,    -1,   165,    -1,   166,    -1,   167,    -1,
      74,    -1,    75,    -1,    94,    -1,   168,    -1,   169,    -1,
     170,    -1,   161,   345,    35,   330,    -1,   348,    -1,   350,
      -1,   352,    -1,   354,    -1,   356,    -1,   358,    -1,   360,
      -1,   362,    -1,   364,    -1,   366,    -1,   368,    -1,   370,
      -1,   372,    -1,   374,    -1,   376,    -1,   378,    -1,    23,
     349,     7,    65,     7,    65,    -1,    69,    -1,    70,    -1,
      71,    -1,    73,   351,    -1,    73,    -1,    74,    -1,    75,
      -1,    76,    -1,    77,   353,    -1,    77,    -1,    78,    -1,
      79,    -1,    80,    -1,    76,    -1,    81,   355,    -1,    81,
      -1,    82,    -1,    83,    -1,    84,    -1,    85,    -1,    86,
      -1,    87,   357,    -1,    87,    -1,    88,    -1,    89,    -1,
      90,    -1,    91,    -1,    78,    -1,    92,    -1,    93,    -1,
      94,    -1,    95,    -1,    74,    -1,    75,    -1,    96,   359,
      -1,    96,    -1,    76,    -1,    97,    -1,    95,    -1,    78,
      -1,    98,    -1,    99,    -1,   100,    -1,   101,   361,    -1,
     101,    -1,    88,    -1,   102,    -1,   103,    -1,    91,    -1,
     104,    -1,   105,    -1,    74,    -1,    75,    -1,   106,   363,
      -1,   106,    -1,    76,    -1,    97,    -1,    95,    -1,   107,
      -1,   100,    -1,    78,    -1,    98,    -1,   108,    -1,   109,
     365,    -1,   109,    -1,   104,    -1,    89,    -1,   110,    -1,
     111,    -1,    98,    -1,   112,   367,    -1,   112,    -1,   111,
      -1,    98,    -1,   113,   369,    -1,   113,    -1,   104,    -1,
     114,    -1,   115,    -1,   116,   371,    -1,   116,    -1,   117,
      -1,   118,    -1,    91,    -1,    95,    -1,   119,   373,    -1,
     119,    -1,   117,    -1,   118,    -1,   120,    -1,    95,    -1,
     121,   375,    -1,   121,    -1,   117,    -1,   118,    -1,    98,
      -1,   122,    -1,   123,    -1,   110,    -1,   114,    -1,   124,
      -1,    95,    -1,   125,    -1,   126,   377,    -1,   126,    -1,
     117,    -1,   118,    -1,    76,    -1,   127,   379,    -1,   127,
      -1,   117,    -1,   118,    -1,   128,    -1,    95,    -1,   381,
      -1,   383,    -1,   385,    -1,   387,    -1,   389,    -1,   391,
      -1,   393,    -1,   134,   382,    -1,   104,    -1,    89,    -1,
     129,   384,    -1,   104,    -1,    89,    -1,    76,    -1,   132,
      -1,   130,   386,    -1,   133,   224,    65,   225,    -1,   131,
     388,    -1,   133,    -1,   135,   390,    -1,   104,    -1,   110,
      -1,    92,    -1,   136,    -1,   137,    -1,    78,    -1,   138,
     392,    -1,   104,    -1,    89,    -1,   139,   394,    -1,   104,
      -1,    89,    -1,    76,    -1,   110,    -1,    95,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   544,   544,   545,   562,   563,   566,   567,   570,   578,
     591,   599,   600,   601,   602,   631,   632,   633,   634,   635,
     636,   637,   638,   639,   640,   641,   644,   648,   655,   659,
     667,   671,   675,   682,   689,   695,   699,   706,   710,   720,
     726,   730,   734,   738,   742,   746,   752,   756,   760,   764,
     768,   772,   778,   782,   786,   790,   796,   803,   811,   820,
     821,   824,   825,   826,   827,   828,   829,   832,   833,   836,
     837,   840,   849,   855,   856,   857,   858,   869,   879,   892,
     898,   899,   900,   901,   902,   910,   915,   916,   917,   918,
     928,   933,   938,   941,   945,   948,   949,   953,   959,   960,
     961,   962,   982,   987,   992,   995,   999,  1005,  1006,  1009,
    1026,  1045,  1048,  1049,  1052,  1053,  1056,  1057,  1058,  1059,
    1060,  1063,  1071,  1079,  1086,  1093,  1100,  1108,  1111,  1118,
    1121,  1127,  1136,  1139,  1146,  1150,  1157,  1170,  1176,  1183,
    1184,  1185,  1186,  1187,  1188,  1189,  1190,  1191,  1192,  1193,
    1194,  1197,  1201,  1207,  1213,  1218,  1227,  1232,  1237,  1240,
    1247,  1248,  1250,  1256,  1260,  1263,  1267,  1273,  1274,  1277,
    1283,  1287,  1290,  1295,  1300,  1305,  1310,  1317,  1318,  1319,
    1320,  1321,  1322,  1323,  1324,  1327,  1335,  1336,  1337,  1338,
    1339,  1342,  1345,  1352,  1356,  1366,  1376,  1385,  1391,  1394,
    1399,  1406,  1410,  1415,  1419,  1425,  1426,  1433,  1436,  1437,
    1440,  1443,  1447,  1451,  1458,  1459,  1465,  1466,  1467,  1470,
    1471,  1474,  1480,  1484,  1487,  1491,  1497,  1498,  1504,  1505,
    1508,  1514,  1521,  1535,  1544,  1555,  1556,  1557,  1558,  1559,
    1560,  1561,  1564,  1565,  1569,  1575,  1576,  1582,  1583,  1589,
    1590,  1596,  1599,  1600,  1619,  1625,  1633,  1639,  1645,  1656,
    1657,  1658,  1661,  1662,  1665,  1671,  1672,  1673,  1674,  1675,
    1678,  1687,  1694,  1699,  1704,  1707,  1711,  1715,  1721,  1722,
    1725,  1729,  1733,  1739,  1740,  1741,  1742,  1743,  1744,  1747,
    1751,  1755,  1759,  1763,  1767,  1773,  1777,  1783,  1784,  1787,
    1788,  1789,  1790,  1791,  1794,  1795,  1796,  1797,  1798,  1799,
    1800,  1801,  1802,  1803,  1804,  1805,  1806,  1807,  1808,  1809,
    1810,  1811,  1814,  1818,  1824,  1830,  1831,  1832,  1833,  1834,
    1835,  1836,  1837,  1838,  1839,  1840,  1841,  1842,  1845,  1851,
    1852,  1853,  1854,  1855,  1856,  1857,  1858,  1859,  1860,  1861,
    1862,  1863,  1864,  1865,  1866,  1869,  1879,  1880,  1881,  1884,
    1888,  1896,  1897,  1898,  1901,  1905,  1913,  1914,  1915,  1916,
    1919,  1923,  1931,  1932,  1933,  1934,  1935,  1938,  1942,  1950,
    1951,  1952,  1953,  1954,  1955,  1956,  1957,  1958,  1959,  1960,
    1963,  1967,  1976,  1977,  1978,  1979,  1980,  1981,  1982,  1985,
    1989,  1997,  1998,  1999,  2000,  2001,  2002,  2003,  2004,  2006,
    2010,  2019,  2020,  2021,  2022,  2023,  2024,  2025,  2026,  2029,
    2033,  2042,  2043,  2044,  2045,  2046,  2049,  2053,  2062,  2063,
    2066,  2070,  2079,  2080,  2081,  2084,  2088,  2097,  2098,  2099,
    2100,  2103,  2107,  2116,  2117,  2118,  2119,  2122,  2126,  2135,
    2136,  2137,  2138,  2139,  2140,  2141,  2142,  2143,  2144,  2147,
    2151,  2160,  2161,  2162,  2165,  2169,  2178,  2179,  2180,  2181,
    2184,  2185,  2186,  2187,  2188,  2189,  2190,  2193,  2199,  2200,
    2203,  2209,  2210,  2211,  2212,  2215,  2221,  2227,  2233,  2236,
    2242,  2243,  2244,  2245,  2246,  2247,  2250,  2256,  2257,  2260,
    2266,  2267,  2268,  2269,  2270
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "$undefined", "\"junk\"", "\"newline\"",
  "\"colon\"", "\"semicolon\"", "\"comma\"", "\".\"", "\"==\"", "\"!=\"",
  "\"<\"", "\">\"", "\">=\"", "\"<=\"", "\"<<\"", "\">>\"", "\"&\"",
  "\"^\"", "\"!\"", "\"/\"", "\"*\"", "\"-\"", "\"@\"", "\"vmap\"",
  "\"include\"", "\"define\"", "\"hook\"", "\"table\"", "\"tables\"",
  "\"chain\"", "\"chains\"", "\"rule\"", "\"rules\"", "\"sets\"",
  "\"set\"", "\"element\"", "\"map\"", "\"handle\"", "\"ruleset\"",
  "\"inet\"", "\"add\"", "\"create\"", "\"insert\"", "\"delete\"",
  "\"list\"", "\"flush\"", "\"rename\"", "\"describe\"", "\"export\"",
  "\"monitor\"", "\"accept\"", "\"drop\"", "\"continue\"", "\"jump\"",
  "\"goto\"", "\"return\"", "\"to\"", "\"constant\"", "\"interval\"",
  "\"elements\"", "\"policy\"", "\"memory\"", "\"performance\"",
  "\"size\"", "\"number\"", "\"string\"", "QUOTED_STRING", "\"error\"",
  "\"ll\"", "\"nh\"", "\"th\"", "\"bridge\"", "\"ether\"", "\"saddr\"",
  "\"daddr\"", "\"type\"", "\"vlan\"", "\"id\"", "\"cfi\"", "\"pcp\"",
  "\"arp\"", "\"htype\"", "\"ptype\"", "\"hlen\"", "\"plen\"",
  "\"operation\"", "\"ip\"", "\"version\"", "\"hdrlength\"", "\"tos\"",
  "\"length\"", "\"frag-off\"", "\"ttl\"", "\"protocol\"", "\"checksum\"",
  "\"icmp\"", "\"code\"", "\"seq\"", "\"gateway\"", "\"mtu\"", "\"ip6\"",
  "\"priority\"", "\"flowlabel\"", "\"nexthdr\"", "\"hoplimit\"",
  "\"icmpv6\"", "\"param-problem\"", "\"max-delay\"", "\"ah\"",
  "\"reserved\"", "\"spi\"", "\"esp\"", "\"comp\"", "\"flags\"", "\"cpi\"",
  "\"udp\"", "\"sport\"", "\"dport\"", "\"udplite\"", "\"csumcov\"",
  "\"tcp\"", "\"ackseq\"", "\"doff\"", "\"window\"", "\"urgptr\"",
  "\"dccp\"", "\"sctp\"", "\"vtag\"", "\"rt\"", "\"rt0\"", "\"rt2\"",
  "\"seg-left\"", "\"addr\"", "\"hbh\"", "\"frag\"", "\"reserved2\"",
  "\"more-fragments\"", "\"dst\"", "\"mh\"", "\"meta\"", "\"nfproto\"",
  "\"l4proto\"", "\"mark\"", "\"iif\"", "\"iifname\"", "\"iiftype\"",
  "\"oif\"", "\"oifname\"", "\"oiftype\"", "\"skuid\"", "\"skgid\"",
  "\"nftrace\"", "\"rtclassid\"", "\"ibriport\"", "\"obriport\"",
  "\"pkttype\"", "\"cpu\"", "\"iifgroup\"", "\"oifgroup\"", "\"cgroup\"",
  "\"ct\"", "\"direction\"", "\"state\"", "\"status\"", "\"expiration\"",
  "\"helper\"", "\"l3proto\"", "\"proto-src\"", "\"proto-dst\"",
  "\"label\"", "\"counter\"", "\"packets\"", "\"bytes\"", "\"log\"",
  "\"prefix\"", "\"group\"", "\"snaplen\"", "\"queue-threshold\"",
  "\"level\"", "\"emerg\"", "\"alert\"", "\"crit\"", "\"err\"", "\"warn\"",
  "\"notice\"", "\"info\"", "\"debug\"", "\"limit\"", "\"rate\"",
  "\"nanosecond\"", "\"microsecond\"", "\"millisecond\"", "\"second\"",
  "\"minute\"", "\"hour\"", "\"day\"", "\"week\"", "\"reject\"",
  "\"reset\"", "\"with\"", "\"icmpx\"", "\"snat\"", "\"dnat\"",
  "\"masquerade\"", "\"redirect\"", "\"random\"", "\"fully-random\"",
  "\"persistent\"", "\"queue\"", "\"num\"", "\"bypass\"", "\"fanout\"",
  "\"position\"", "\"comment\"", "\"xml\"", "\"json\"", "'='", "'{'",
  "'}'", "'$'", "'('", "')'", "'|'", "'['", "']'", "$accept", "input",
  "stmt_seperator", "opt_newline", "common_block", "line", "base_cmd",
  "add_cmd", "create_cmd", "insert_cmd", "delete_cmd", "list_cmd",
  "flush_cmd", "rename_cmd", "export_cmd", "monitor_cmd", "monitor_event",
  "monitor_object", "monitor_format", "export_format", "describe_cmd",
  "table_block_alloc", "table_block", "chain_block_alloc", "chain_block",
  "set_block_alloc", "set_block", "set_flag_list", "set_flag",
  "map_block_alloc", "map_block", "set_mechanism", "set_policy_spec",
  "hook_spec", "identifier", "string", "family_spec",
  "family_spec_explicit", "table_spec", "tables_spec", "chain_spec",
  "chain_identifier", "set_spec", "set_identifier", "handle_spec",
  "position_spec", "ruleid_spec", "comment_spec", "ruleset_spec", "rule",
  "stmt_list", "stmt", "verdict_stmt", "verdict_map_stmt",
  "verdict_map_expr", "verdict_map_list_expr",
  "verdict_map_list_member_expr", "counter_stmt", "counter_stmt_alloc",
  "counter_args", "counter_arg", "log_stmt", "log_stmt_alloc", "log_args",
  "log_arg", "level_type", "limit_stmt", "time_unit", "reject_stmt",
  "reject_stmt_alloc", "reject_opts", "nat_stmt", "nat_stmt_alloc",
  "nat_stmt_args", "masq_stmt", "masq_stmt_alloc", "redir_stmt",
  "redir_stmt_alloc", "redir_stmt_arg", "nf_nat_flags", "nf_nat_flag",
  "queue_stmt", "queue_stmt_alloc", "queue_stmt_args", "queue_stmt_arg",
  "queue_stmt_flags", "queue_stmt_flag", "match_stmt", "symbol_expr",
  "integer_expr", "primary_expr", "shift_expr", "and_expr",
  "exclusive_or_expr", "inclusive_or_expr", "basic_expr", "concat_expr",
  "list_expr", "prefix_expr", "range_expr", "wildcard_expr",
  "multiton_expr", "map_lhs_expr", "map_expr", "expr", "error_expr",
  "set_expr", "set_list_expr", "set_list_member_expr", "initializer_expr",
  "relational_expr", "relational_op", "verdict_expr", "meta_expr",
  "meta_key", "meta_key_qualified", "meta_key_unqualified", "meta_stmt",
  "ct_expr", "ct_key", "ct_stmt", "payload_expr", "payload_raw_expr",
  "payload_base_spec", "eth_hdr_expr", "eth_hdr_field", "vlan_hdr_expr",
  "vlan_hdr_field", "arp_hdr_expr", "arp_hdr_field", "ip_hdr_expr",
  "ip_hdr_field", "icmp_hdr_expr", "icmp_hdr_field", "ip6_hdr_expr",
  "ip6_hdr_field", "icmp6_hdr_expr", "icmp6_hdr_field", "auth_hdr_expr",
  "auth_hdr_field", "esp_hdr_expr", "esp_hdr_field", "comp_hdr_expr",
  "comp_hdr_field", "udp_hdr_expr", "udp_hdr_field", "udplite_hdr_expr",
  "udplite_hdr_field", "tcp_hdr_expr", "tcp_hdr_field", "dccp_hdr_expr",
  "dccp_hdr_field", "sctp_hdr_expr", "sctp_hdr_field", "exthdr_expr",
  "hbh_hdr_expr", "hbh_hdr_field", "rt_hdr_expr", "rt_hdr_field",
  "rt0_hdr_expr", "rt0_hdr_field", "rt2_hdr_expr", "rt2_hdr_field",
  "frag_hdr_expr", "frag_hdr_field", "dst_hdr_expr", "dst_hdr_field",
  "mh_hdr_expr", "mh_hdr_field", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,    61,   123,   125,
      36,    40,    41,   124,    91,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   226,   227,   227,   228,   228,   229,   229,   230,   230,
     230,   231,   231,   231,   231,   232,   232,   232,   232,   232,
     232,   232,   232,   232,   232,   232,   233,   233,   233,   233,
     233,   233,   233,   233,   233,   234,   234,   234,   234,   235,
     236,   236,   236,   236,   236,   236,   237,   237,   237,   237,
     237,   237,   238,   238,   238,   238,   239,   240,   241,   242,
     242,   243,   243,   243,   243,   243,   243,   244,   244,   245,
     245,   246,   247,   248,   248,   248,   248,   248,   248,   249,
     250,   250,   250,   250,   250,   251,   252,   252,   252,   252,
     252,   252,   252,   253,   253,   254,   254,   255,   256,   256,
     256,   256,   256,   256,   256,   257,   257,   258,   258,   259,
     259,   260,   261,   261,   262,   262,   263,   263,   263,   263,
     263,   264,   265,   266,   267,   268,   269,   270,   270,   271,
     271,   272,   273,   273,   274,   274,   275,   276,   276,   277,
     277,   277,   277,   277,   277,   277,   277,   277,   277,   277,
     277,   278,   278,   279,   280,   280,   281,   281,   281,   282,
     283,   283,   284,   285,   285,   286,   286,   287,   287,   288,
     289,   289,   290,   290,   290,   290,   290,   291,   291,   291,
     291,   291,   291,   291,   291,   292,   293,   293,   293,   293,
     293,   294,   295,   296,   296,   296,   296,   296,   297,   298,
     298,   299,   299,   299,   299,   300,   300,   301,   302,   302,
     303,   304,   304,   304,   305,   305,   306,   306,   306,   307,
     307,   308,   309,   309,   310,   310,   311,   311,   312,   312,
     313,   314,   314,   314,   315,   316,   316,   316,   316,   316,
     316,   316,   317,   317,   317,   318,   318,   319,   319,   320,
     320,   321,   322,   322,   323,   323,   324,   325,   326,   327,
     327,   327,   328,   328,   329,   330,   330,   330,   330,   330,
     331,   332,   333,   333,   333,   334,   334,   334,   335,   335,
     336,   336,   336,   337,   337,   337,   337,   337,   337,   338,
     338,   338,   338,   338,   338,   339,   339,   340,   340,   341,
     341,   341,   341,   341,   342,   342,   342,   342,   342,   342,
     342,   342,   342,   342,   342,   342,   342,   342,   342,   342,
     342,   342,   343,   343,   344,   345,   345,   345,   345,   345,
     345,   345,   345,   345,   345,   345,   345,   345,   346,   347,
     347,   347,   347,   347,   347,   347,   347,   347,   347,   347,
     347,   347,   347,   347,   347,   348,   349,   349,   349,   350,
     350,   351,   351,   351,   352,   352,   353,   353,   353,   353,
     354,   354,   355,   355,   355,   355,   355,   356,   356,   357,
     357,   357,   357,   357,   357,   357,   357,   357,   357,   357,
     358,   358,   359,   359,   359,   359,   359,   359,   359,   360,
     360,   361,   361,   361,   361,   361,   361,   361,   361,   362,
     362,   363,   363,   363,   363,   363,   363,   363,   363,   364,
     364,   365,   365,   365,   365,   365,   366,   366,   367,   367,
     368,   368,   369,   369,   369,   370,   370,   371,   371,   371,
     371,   372,   372,   373,   373,   373,   373,   374,   374,   375,
     375,   375,   375,   375,   375,   375,   375,   375,   375,   376,
     376,   377,   377,   377,   378,   378,   379,   379,   379,   379,
     380,   380,   380,   380,   380,   380,   380,   381,   382,   382,
     383,   384,   384,   384,   384,   385,   386,   387,   388,   389,
     390,   390,   390,   390,   390,   390,   391,   392,   392,   393,
     394,   394,   394,   394,   394
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     0,     3,     5,
       2,     1,     1,     2,     2,     1,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     6,     2,     6,
       3,     2,     6,     6,     3,     2,     6,     2,     6,     3,
       2,     2,     2,     2,     2,     3,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     3,     1,     3,     0,
       1,     0,     1,     1,     1,     1,     1,     0,     1,     1,
       1,     1,     0,     0,     2,     2,     8,     8,     8,     0,
       0,     2,     2,     3,     3,     0,     0,     2,     2,     4,
       4,     4,     3,     3,     1,     1,     1,     0,     0,     2,
       2,     6,     4,     4,     3,     2,     2,     1,     1,     6,
       7,     1,     1,     1,     0,     1,     1,     1,     1,     1,
       1,     2,     1,     2,     1,     2,     1,     0,     2,     0,
       2,     3,     0,     2,     0,     1,     2,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     2,     1,     3,     3,     5,
       1,     2,     1,     1,     2,     2,     2,     1,     2,     1,
       1,     2,     2,     2,     2,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     5,     1,     1,     1,     1,
       1,     2,     1,     0,     4,     4,     4,     3,     2,     1,
       1,     1,     3,     2,     2,     1,     2,     1,     2,     1,
       1,     2,     1,     3,     1,     3,     1,     1,     1,     1,
       2,     1,     1,     2,     2,     1,     1,     3,     1,     1,
       1,     1,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     3,     3,     1,     3,     1,     3,     1,
       3,     1,     1,     3,     3,     3,     3,     3,     1,     1,
       1,     1,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     3,     1,     3,     3,     3,     5,     5,     1,     1,
       2,     2,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     4,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     6,     1,     1,     1,     2,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       2,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       2,     1,     1,     1,     1,     2,     4,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     2,
       1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     1,     0,     4,     5,     0,     0,   114,   114,
     114,   114,   114,   114,   118,   114,     0,     0,     0,     0,
       0,     0,     0,     0,    59,   120,   119,   116,   117,    12,
      11,     3,     0,    15,     0,   115,     0,   127,     0,    10,
       0,   111,     0,    26,    28,     0,     0,    85,     0,    97,
      16,   114,   114,    17,   114,    18,   114,   114,   114,   114,
     114,   114,    19,   114,   114,   114,   114,   114,   134,    20,
     114,   114,   114,   134,    21,   114,    22,     0,   234,   112,
     113,   360,   365,   371,   378,   391,   400,   410,   420,   427,
     431,   436,   442,   448,   460,   465,     0,     0,     0,     0,
       0,     0,     0,     0,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,     0,     0,     0,    25,   231,   235,   236,    71,
     239,   296,   240,   237,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     238,   470,   471,   472,   473,   474,   475,   476,    69,    70,
      23,    57,    60,    24,    61,    14,    13,   121,   123,     0,
     129,   258,   289,   290,   291,     0,     0,   294,   270,     0,
       0,   162,   169,     0,   192,   199,   200,   207,   210,   221,
       7,    31,   132,   137,   139,   152,   141,   160,   143,   167,
     144,   145,   193,   146,     0,   149,   205,   150,   209,   147,
     219,   140,   242,   245,   247,   249,   251,   252,   265,   259,
     260,   261,   268,   267,     0,   269,   266,   230,   151,   296,
     142,   148,     8,     0,     0,     0,    30,   125,     0,    34,
       0,    35,    37,     0,    40,    41,    42,    43,     0,    44,
      46,   122,    47,    48,    49,    50,   135,    51,    52,    53,
      54,    55,     0,   356,   357,   358,   233,     0,   361,   362,
     363,   359,   369,   366,   367,   368,   364,   372,   373,   374,
     375,   376,   370,   388,   389,   383,   379,   380,   381,   382,
     384,   385,   386,   387,   377,   392,   395,   394,   393,   396,
     397,   398,   390,   407,   408,   401,   404,   402,   403,   405,
     406,   399,   411,   416,   413,   412,   417,   415,   414,   418,
     409,   422,   425,   421,   423,   424,   419,   429,   428,   426,
     432,   433,   434,   430,   439,   440,   437,   438,   435,   446,
     443,   444,   445,   441,   457,   451,   454,   455,   449,   450,
     452,   453,   456,   458,   447,   463,   461,   462,   459,   469,
     466,   467,   468,   464,   483,   482,   481,   484,   480,     0,
     485,   488,   487,   479,   478,   477,   495,   492,   490,   491,
     493,   494,   489,   498,   497,   496,   502,   501,   504,   500,
     503,   499,   299,   302,   303,   300,   301,   295,   297,   298,
     332,   333,   334,   328,   326,   325,   327,   329,   330,   331,
     335,   336,   337,   324,   232,     0,    62,    63,    65,    64,
      66,    67,   128,     0,   131,   292,   293,   295,   324,     0,
       6,     0,     0,   272,     0,   136,   138,     0,     0,   161,
     163,     0,     0,     0,     0,     0,   168,   170,     0,   191,
       0,   198,   265,   201,   216,   217,   218,   206,   214,     0,
     208,   212,     0,   228,   229,   220,   222,   225,   226,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   283,
     284,   285,   286,   287,   288,   252,   281,   280,     0,     0,
     279,   278,     0,    73,    80,    86,    98,     0,     0,    39,
      45,    56,     0,     0,   241,    58,    68,   130,     0,     0,
       0,   265,   268,     0,     7,     7,   271,   133,   165,   166,
     164,   172,   173,   174,   175,   177,   178,   179,   180,   181,
     182,   183,   184,   176,   171,     0,     0,     0,     0,   203,
     204,     0,     0,   211,   224,   223,     0,   243,   244,   246,
     248,   250,   256,   257,   253,     0,     7,   153,   264,     0,
       0,   282,   323,     9,     0,     0,     0,     0,    73,    80,
       0,     0,   322,   338,     0,     0,   275,   274,   273,     0,
       0,   197,     0,   202,   215,   213,   227,   155,     0,     0,
     156,   254,   255,     0,     0,     0,    27,    75,    74,     0,
      29,    82,    81,     0,     0,     0,     0,     0,     0,     0,
      32,    88,    87,     0,     0,     0,     0,    33,   100,    99,
       0,     0,     0,     0,   486,   186,   187,   188,   189,   190,
     185,   252,     7,     7,   194,   195,   196,   263,   262,     0,
       7,   154,   124,    79,   126,    85,    97,     0,    83,    84,
       0,   108,   107,   105,   106,     0,    95,    96,     0,    94,
      92,     0,     0,     0,   104,    36,    38,   355,   276,   277,
       0,   158,   157,     0,     0,     0,     0,    91,    89,     0,
      90,   103,     0,   102,     7,    80,    86,    98,     0,    93,
       0,   159,     0,     0,     0,     0,   101,     0,     0,     0,
       0,   109,    76,    77,    78,   110
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,   601,   431,   602,    31,    32,    33,    53,    55,
      62,    69,    74,    76,   160,   163,   164,   421,   505,   161,
     125,   234,   564,   235,   565,   238,   566,   658,   659,   240,
     567,   613,   653,   603,   644,   126,    34,    35,    36,   252,
      37,   643,    47,   645,   170,   424,    38,   435,   257,   604,
     192,   193,   194,   195,   557,   589,   590,   196,   197,   439,
     440,   198,   199,   446,   447,   533,   200,   630,   201,   202,
     449,   203,   204,   451,   205,   206,   207,   208,   460,   457,
     458,   209,   210,   465,   466,   467,   468,   211,   127,   128,
     212,   213,   214,   215,   216,   217,   452,   486,   219,   220,
     221,   222,   513,   223,   224,   225,   226,   432,   433,   492,
     227,   488,   228,   130,   397,   398,   131,   230,   132,   413,
     231,   133,   134,   267,   135,   271,   136,   276,   137,   282,
     138,   294,   139,   302,   140,   311,   141,   320,   142,   326,
     143,   329,   144,   333,   145,   338,   146,   343,   147,   354,
     148,   358,   149,   363,   150,   151,   375,   152,   368,   153,
     370,   154,   372,   155,   382,   156,   385,   157,   391
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -569
static const yytype_int16 yypact[] =
{
    -569,   389,  -569,   325,  -569,  -569,   -23,     9,    76,    76,
      76,    76,    76,    76,  -569,   304,   168,    51,   562,   415,
     229,    48,  1945,  -163,    26,  -569,  -569,  -569,  -569,  -569,
    -569,  -569,   297,  -569,     9,  -569,     9,    57,  1447,  -569,
     325,  -569,  -107,   -96,   -67,  1447,     9,  -569,   -53,  -569,
    -569,    76,    76,  -569,    76,  -569,    76,    76,    76,    76,
      76,    76,  -569,    76,    76,    76,    76,    76,    76,  -569,
      76,    76,    76,    76,  -569,    76,  -569,   257,  -569,  -569,
    -569,   272,   409,   288,   550,   301,   404,   386,   435,    23,
     166,   188,    58,   457,   -27,   -58,    29,    37,    62,   -76,
     -24,    13,   274,  1160,  -569,  -569,  -569,  -569,  -569,  -569,
    -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,
    -569,  -569,   334,     9,  1945,  -569,  -569,  -569,  -569,  -569,
    -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,
    -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,
    -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,
    -569,  -569,  -569,  -569,   282,  -569,  -569,  -569,  -569,   136,
      35,  -569,  -569,  -569,  -569,     9,     9,  -569,  -569,  1160,
     334,  -569,  -569,    66,  -569,  -569,  -569,  -569,  -569,  -569,
     259,  -569,  1276,  -569,  -569,  -569,  -569,   -42,  -569,   359,
    -569,  -569,    85,  -569,   977,  -569,   174,  -569,   -40,  -569,
     192,  -569,  -569,   172,   249,   286,    77,   345,   156,  -569,
    -569,  -569,  -569,  -569,  1134,  -569,  -569,  -569,  -569,   275,
    -569,  -569,  -569,  1593,    89,    96,  -569,  -569,    99,  -569,
     102,   -96,   -67,  1447,  -569,  -569,  -569,  -569,   -53,  -569,
    -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,
    -569,  -569,     9,  -569,  -569,  -569,  -569,   331,  -569,  -569,
    -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,
    -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,
    -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,
    -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,
    -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,
    -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,
    -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,
    -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,
    -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,
    -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,   119,
    -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,
    -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,
    -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,
    -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,
    -569,  -569,  -569,  -569,  -569,   127,  -569,  -569,  -569,  -569,
    -569,  -163,  -569,   291,  -569,  -569,  -569,   348,   357,   341,
    -569,  1593,    16,  -569,   148,  -569,  -569,   342,   346,   -42,
    -569,   148,   351,   353,   355,   449,   359,  -569,   -45,  -569,
    1593,   174,    18,   408,  -569,  -569,  -569,   387,  -569,  1593,
    -569,   387,  1593,  -569,  -569,   192,  -569,   416,  -569,  1945,
    1945,  1945,  1945,  1945,   362,  1945,  1945,    -8,  1593,  -569,
    -569,  -569,  -569,  -569,  -569,    43,   433,  -569,  1593,  1593,
     433,  -569,   325,  -569,  -569,  -569,  -569,   204,   228,  -569,
    -569,  -569,   382,   383,  -569,  -569,  -569,  -569,  1593,  1593,
     431,   115,   447,   448,   259,   259,  -569,  -569,  -569,  -569,
    -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,
    -569,  -569,  -569,  -569,  -569,   380,   390,   264,   393,  -569,
     387,  1593,   174,   174,  -569,  -569,    78,  -569,  -569,   172,
     249,   286,  -569,  -569,  -569,     9,   259,  -569,  -569,  1945,
    1945,  -569,  -569,  -569,    32,    73,    21,    83,  -569,  -569,
     451,   240,  -569,  -569,   420,  1848,  -569,  1593,  -569,   439,
     444,  -569,   446,  -569,  -569,   387,  -569,  -569,  1735,    17,
    -569,  -569,  -569,     9,     9,     9,  -569,  -569,  -569,   452,
    -569,  -569,  -569,   325,   325,   258,   233,   417,     9,   294,
    -569,  -569,  -569,   325,   296,     9,   294,  -569,  -569,  -569,
     325,   329,   659,   450,  -569,  -569,  -569,  -569,  -569,  -569,
    -569,  -569,   128,   259,  -569,  -569,  -569,   466,  -569,   509,
     259,  -569,  -569,  -569,  -569,  -569,  -569,   490,  -569,  -569,
     -53,  -569,  -569,  -569,  -569,   325,  -569,  -569,   177,  -569,
    -569,   -53,   517,   177,  -569,  -569,  -569,  -569,  -569,  -569,
     505,  1735,  -569,   307,   308,   311,   474,  -569,  -569,   294,
    -569,  -569,     9,  -569,   259,  -569,  -569,  -569,   440,  -569,
     325,  -569,   820,   248,   261,     7,  -569,   325,   325,   325,
     479,  -569,  -569,  -569,  -569,  -569
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -569,  -569,    -1,  -272,     6,  -569,  -569,   532,  -569,  -569,
    -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,   129,
    -569,   312,   -19,  -233,  -548,   -83,  -122,   -48,  -110,   -70,
    -109,  -549,  -569,  -569,    -4,  -370,   322,   -33,   460,   511,
      36,  -569,   178,   -12,  -569,  -569,    46,  -569,   513,     3,
    -569,   392,  -569,  -569,  -569,  -569,   -49,  -569,  -569,  -569,
     154,  -569,  -569,  -569,   141,  -569,  -569,  -569,  -569,  -569,
    -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -198,
      53,  -569,  -569,  -569,   131,  -569,    54,  -569,  -569,  -569,
     -10,   130,   133,   135,  -569,  -118,   -34,   373,  -569,  -569,
    -569,  -415,  -568,  -569,  -190,  -569,   -43,  -569,    94,  -569,
    -569,  -569,  -556,  -569,   442,  -569,   -37,  -569,  -569,   430,
    -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,
    -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,
    -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,
    -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,
    -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569,  -569
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -264
static const yytype_int16 yytable[] =
{
      29,   229,    39,    42,   218,   239,   415,    30,   229,   498,
     461,   218,   129,   373,   453,   555,   512,   459,   620,   633,
     639,   622,     3,   515,   640,     4,   476,     5,   374,   700,
     167,   166,   168,     3,   487,   256,     4,   359,     5,   232,
     256,   191,   237,   491,    40,    44,     6,     7,   236,   355,
     559,   535,   158,   159,   376,   478,    45,     6,     7,   360,
     361,   536,   593,   474,   517,   475,   399,   594,   377,   595,
     362,   521,   701,   266,     3,    41,   537,     4,    75,     5,
     378,   605,   606,    54,     3,   607,   379,     4,   242,     5,
     356,   357,   162,   245,   171,   169,    77,   608,     6,     7,
     243,   253,   383,   639,   246,   364,   485,   259,     6,     7,
     233,   262,   380,   381,   684,   485,    14,   384,   365,   414,
    -263,   327,   -72,   476,   172,   173,   174,   175,   176,   177,
     437,   438,   430,   366,   328,   609,   476,   692,    78,    79,
      80,   178,   399,   614,   606,   620,    81,   607,    25,   599,
      82,   -79,   478,   339,    83,   229,   538,    26,   218,   615,
      84,   367,   512,    27,   476,   190,   454,   455,   456,    85,
     369,   425,   426,   638,    86,   340,   341,    28,   342,    87,
     477,     4,    88,     5,   679,    89,    90,   469,   470,    91,
      48,    49,    92,   478,    93,   371,    51,   616,    52,    94,
      95,   422,    96,    97,    98,   500,   229,    99,   100,   218,
     556,   101,   102,   179,    79,    80,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   180,   516,   641,   247,   248,   249,
     610,   514,   576,   577,   181,   255,   499,   182,   423,     3,
     260,   596,     4,   540,     5,   429,   638,    70,   501,    71,
     539,   183,     3,   430,    72,     4,   471,     5,    73,   543,
     330,   184,   544,     6,     7,   185,   186,   187,   188,   334,
     331,   332,   189,   335,   588,   448,     6,     7,   558,   463,
     464,   190,   600,   123,   124,   651,   652,   165,   561,   562,
     473,     4,   617,     5,   472,   336,   337,   493,   605,   606,
     489,   416,   607,   417,   494,   418,   419,   495,   572,   573,
     496,   614,   606,    41,   608,   607,   263,   264,   265,     4,
       3,     5,     8,     4,     9,     5,    10,   615,   502,    11,
      12,    13,   420,   503,    14,   585,   268,   269,   270,   504,
     386,   583,   656,   657,     6,     7,   507,   553,   554,   593,
     668,   669,   609,   387,   594,   474,   595,   475,   671,   388,
     277,   278,   279,   280,   281,   616,    25,   295,   389,   296,
     454,   455,   456,   508,   390,    26,   251,   514,   251,     2,
       3,    27,   509,     4,   542,     5,   297,   511,   298,   299,
     300,   301,   462,   463,   464,    28,   510,   518,   400,   401,
     673,   519,   691,   541,     6,     7,   522,     8,   523,     9,
     524,    10,   568,   546,    11,    12,    13,   552,   402,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
     560,   591,   592,    63,    64,    65,   569,   570,   571,    66,
      67,   574,  -262,   575,    68,  -114,   579,   631,   623,   547,
     548,    25,   312,   581,   313,   624,   580,   698,    43,   582,
      26,    46,    46,    46,   476,   650,    27,   403,   303,   304,
     699,   314,   654,   315,   316,   272,   317,   273,   274,   275,
      28,   563,   305,   318,   319,   306,   404,   405,   406,   407,
     408,   409,   410,   411,   412,   634,   307,   308,   309,   310,
     635,   241,   636,   661,   670,   667,   244,   676,   647,    46,
      46,    46,   682,   250,   321,   685,   686,    46,   229,   687,
     258,   218,    46,   322,   441,   442,   443,   444,   445,   323,
     688,   632,   695,   511,   705,   324,   325,    50,   665,   621,
     506,   587,   344,   497,   637,   345,   172,   173,   174,   175,
     176,   177,   674,   597,   693,   611,   618,   346,   663,   689,
     598,   347,   612,   619,   348,   349,   675,   254,   694,   350,
     351,   352,   353,   646,   436,   229,   261,   534,   218,   642,
      56,   672,    57,   520,    58,   584,   545,    59,    60,    61,
     586,   549,   648,   649,   655,   550,   490,   677,   551,   578,
     428,   662,   660,   625,   626,   627,   628,   629,   681,   664,
     597,   427,     0,     0,   283,   284,     0,   598,   285,   525,
     526,   527,   528,   529,   530,   531,   532,   637,   286,   287,
     288,   289,   290,   291,   292,   293,     0,     0,     0,     0,
       0,     0,     0,     0,   678,   229,     0,   680,   218,     0,
       3,     0,   683,     4,     0,     5,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   690,     0,
     171,     0,    77,     0,     6,     7,     0,     0,     0,   696,
       0,     0,   611,   618,     0,     0,   702,   703,   704,   612,
     619,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     172,   173,   174,   175,   176,   177,     0,     0,     0,     0,
       0,     0,     0,     0,    78,    79,    80,   178,     0,     0,
       0,     0,    81,     0,     0,   599,    82,     0,     0,     0,
      83,     0,     0,     0,     0,     0,    84,     0,     0,     0,
       0,     0,     0,     0,     0,    85,     0,     0,     0,     0,
      86,     0,     0,     0,     0,    87,     0,     0,    88,     0,
       0,    89,    90,     0,     0,    91,     0,     0,    92,     0,
      93,     0,     0,     0,     0,    94,    95,     0,    96,    97,
      98,     0,     0,    99,   100,     0,     0,   101,   102,   179,
       0,     0,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     180,     3,     0,     0,     4,     0,     5,     0,     0,     0,
     181,     0,     0,   182,     0,     0,     0,     0,     0,     0,
       0,   171,     0,    77,     0,     6,     7,   183,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   184,     0,     0,
       0,   185,   186,   187,   188,     0,     0,     0,   189,     0,
       0,   172,   173,   174,   175,   176,   177,   190,   666,   123,
     124,     0,     0,     0,     0,    78,    79,    80,   178,     0,
       0,     0,     0,    81,     0,     0,   599,    82,     0,     0,
       0,    83,     0,     0,     0,     0,     0,    84,     0,     0,
       0,     0,     0,     0,     0,     0,    85,     0,     0,     0,
       0,    86,     0,     0,     0,     0,    87,     0,     0,    88,
       0,     0,    89,    90,     0,     0,    91,     0,     0,    92,
       0,    93,     0,     0,     0,     0,    94,    95,     0,    96,
      97,    98,     0,     0,    99,   100,     0,     0,   101,   102,
     179,     0,     0,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   180,   450,     0,     0,     0,     0,     0,     0,     0,
       0,   181,     0,     0,   182,     0,     0,     0,   171,     0,
      77,     0,     0,     0,     0,     0,     0,     0,   183,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   184,     0,
       0,     0,   185,   186,   187,   188,     0,     0,     0,   189,
       0,     0,     0,     0,     0,     0,     0,     0,   190,   697,
     123,   124,    78,    79,    80,   178,     0,     0,     0,     0,
      81,     0,     0,     0,    82,     0,     0,     0,    83,     0,
       0,     0,     0,     0,    84,     0,     0,     0,     0,     0,
       0,     0,     0,    85,     0,     0,     0,     0,    86,     0,
       0,     0,     0,    87,     0,     0,    88,     0,     0,    89,
      90,     0,     0,    91,     0,     0,    92,     0,    93,     0,
       0,     0,     0,    94,    95,     0,    96,    97,    98,     0,
       0,    99,   100,     0,     0,   101,   102,   103,     0,     0,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,     0,
       0,     0,     0,   479,   480,   481,   482,   483,   484,     0,
       0,     0,     0,     0,     0,   171,     0,    77,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   190,     0,   123,   124,    78,
      79,    80,   178,     0,     0,     0,     0,    81,     0,     0,
       0,    82,     0,     0,     0,    83,     0,     0,     0,     0,
       0,    84,     0,     0,     0,     0,     0,     0,     0,     0,
      85,     0,     0,     0,     0,    86,     0,     0,     0,     0,
      87,     0,     0,    88,     0,     0,    89,    90,     0,     0,
      91,   392,     0,    92,   393,    93,     0,     0,     0,     0,
      94,    95,   394,    96,    97,    98,     0,     0,    99,   100,
       0,     0,   101,   102,   103,     0,     0,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,     0,   171,     0,    77,
       0,   395,   396,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,     0,     0,     0,     0,     0,     0,   172,   173,   174,
     175,   176,   177,     0,     0,     0,     0,     0,     0,     0,
       0,    78,    79,    80,   178,     0,     0,     0,     0,    81,
       0,     0,   190,    82,   123,   124,     0,    83,     0,     0,
       0,     0,     0,    84,     0,     0,     0,     0,     0,     0,
       0,     0,    85,     0,     0,     0,     0,    86,     0,     0,
       0,     0,    87,     0,     0,    88,     0,     0,    89,    90,
       0,     0,    91,     0,     0,    92,     0,    93,     0,     0,
       0,     0,    94,    95,     0,    96,    97,    98,     0,     0,
      99,   100,     0,     0,   101,   102,   179,     0,     0,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   180,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   181,     0,     0,
     182,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   183,     0,     0,     0,   171,     0,
      77,     0,     0,     0,   184,     0,     0,     0,   185,   186,
     187,   188,     0,     0,     0,   189,     0,     0,     0,     0,
     434,     0,     0,     0,   190,     0,   123,   124,   172,   173,
     174,   175,   176,   177,     0,     0,     0,     0,     0,     0,
       0,     0,    78,    79,    80,   178,     0,     0,     0,     0,
      81,     0,     0,     0,    82,     0,     0,     0,    83,     0,
       0,     0,     0,     0,    84,     0,     0,     0,     0,     0,
       0,     0,     0,    85,     0,     0,     0,     0,    86,     0,
       0,     0,     0,    87,     0,     0,    88,     0,     0,    89,
      90,     0,     0,    91,     0,     0,    92,     0,    93,     0,
       0,     0,     0,    94,    95,     0,    96,    97,    98,     0,
       0,    99,   100,     0,     0,   101,   102,   179,     0,     0,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   180,     0,
       0,     0,     0,     0,   171,     0,    77,     0,   181,     0,
       0,   182,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   183,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   184,     0,     0,     0,   185,
     186,   187,   188,     0,     0,     0,   189,     0,    78,    79,
      80,   178,     0,     0,     0,   190,    81,   123,   124,     0,
      82,     0,     0,     0,    83,     0,     0,     0,     0,     0,
      84,     0,     0,     0,     0,     0,     0,     0,     0,    85,
       0,     0,     0,     0,    86,     0,     0,     0,     0,    87,
       0,     0,    88,     0,     0,    89,    90,     0,     0,    91,
       0,     0,    92,     0,    93,     0,     0,     0,     0,    94,
      95,     0,    96,    97,    98,     0,     0,    99,   100,     0,
       0,   101,   102,   103,     0,     0,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,     0,   171,     0,    77,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      78,    79,    80,     0,     0,     0,     0,     0,    81,     0,
       0,   190,    82,   123,   124,     0,    83,     0,     0,     0,
       0,     0,    84,     0,     0,     0,     0,     0,     0,     0,
       0,    85,     0,     0,     0,     0,    86,     0,     0,     0,
       0,    87,     0,     0,    88,     0,     0,    89,    90,     0,
       0,    91,     0,     0,    92,     0,    93,     0,     0,     0,
       0,    94,    95,     0,    96,    97,    98,     0,     0,    99,
     100,    77,     0,   101,   102,   103,     0,     0,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,     0,     0,   172,
     173,   174,   175,   176,   177,     0,     0,     0,     0,     0,
       0,     0,     0,    78,    79,    80,     0,     0,     0,     0,
       0,    81,     0,     0,     0,    82,     0,     0,     0,    83,
       0,     0,     0,     0,     0,    84,     0,     0,     0,     0,
       0,     0,     0,     0,    85,     0,     0,     0,     0,    86,
       0,     0,     0,     0,    87,   123,   124,    88,     0,     0,
      89,    90,     0,     0,    91,     0,     0,    92,    77,    93,
       0,     0,     0,     0,    94,    95,     0,    96,    97,    98,
       0,     0,    99,   100,     0,     0,   101,   102,   103,     0,
       0,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
      78,    79,    80,     0,     0,     0,     0,     0,    81,     0,
       0,     0,    82,     0,     0,     0,    83,     0,     0,     0,
       0,     0,    84,     0,     0,     0,     0,     0,     0,     0,
       0,    85,     0,     0,     0,     0,    86,     0,     0,     0,
       0,    87,     0,     0,    88,     0,     0,    89,    90,     0,
       0,    91,     0,     0,    92,     0,    93,     0,   123,   124,
       0,    94,    95,     0,    96,    97,    98,     0,     0,    99,
     100,     0,     0,   101,   102,   103,     0,     0,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   123,   124
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-569))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       1,    38,     3,     7,    38,    48,   124,     1,    45,   242,
     208,    45,    22,    89,   204,    23,   431,    57,   567,   575,
     588,   569,     1,     7,     7,     4,     8,     6,   104,    22,
      34,    32,    36,     1,   224,    68,     4,    95,     6,    40,
      73,    38,    46,   233,    67,     9,    25,    26,    45,    76,
       7,    96,   215,   216,    78,    37,    10,    25,    26,   117,
     118,   106,    30,    20,   434,    22,   103,    35,    92,    37,
     128,   441,    65,    77,     1,    66,   121,     4,    30,     6,
     104,    60,    61,    32,     1,    64,   110,     4,    52,     6,
     117,   118,    66,    57,    21,    38,    23,    76,    25,    26,
      54,    65,    89,   671,    58,    76,   224,    71,    25,    26,
     217,    75,   136,   137,   670,   233,    40,   104,    89,   123,
       5,    98,   218,     8,    51,    52,    53,    54,    55,    56,
     172,   173,     4,   104,   111,   114,     8,   685,    65,    66,
      67,    68,   179,    60,    61,   694,    73,    64,    72,    76,
      77,   218,    37,    95,    81,   192,   201,    81,   192,    76,
      87,   132,   577,    87,     8,   218,   206,   207,   208,    96,
     133,   175,   176,   588,   101,   117,   118,   101,   120,   106,
      24,     4,   109,     6,     7,   112,   113,    15,    16,   116,
      12,    13,   119,    37,   121,   133,    28,   114,    30,   126,
     127,    65,   129,   130,   131,   248,   243,   134,   135,   243,
     218,   138,   139,   140,    66,    67,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   219,   219,    59,    60,    61,
     219,   431,   514,   515,   171,    67,   243,   174,   213,     1,
      72,   219,     4,   451,     6,   189,   671,    28,   262,    30,
     450,   188,     1,     4,    35,     4,    17,     6,    39,   459,
     104,   198,   462,    25,    26,   202,   203,   204,   205,    91,
     114,   115,   209,    95,   556,   200,    25,    26,   478,   211,
     212,   218,   219,   220,   221,    62,    63,     0,   488,   489,
     223,     4,   219,     6,    18,   117,   118,   218,    60,    61,
      35,    29,    64,    31,   218,    33,    34,   218,   508,   509,
     218,    60,    61,    66,    76,    64,    69,    70,    71,     4,
       1,     6,    28,     4,    30,     6,    32,    76,     7,    35,
      36,    37,    60,   224,    40,   543,    74,    75,    76,   222,
      76,   541,    58,    59,    25,    26,    65,   475,   476,    30,
     632,   633,   114,    89,    35,    20,    37,    22,   640,    95,
      82,    83,    84,    85,    86,   114,    72,    76,   104,    78,
     206,   207,   208,    35,   110,    81,    64,   577,    66,     0,
       1,    87,    35,     4,     7,     6,    95,   431,    97,    98,
      99,   100,   210,   211,   212,   101,    65,    65,    74,    75,
     643,    65,   684,     5,    25,    26,    65,    28,    65,    30,
      65,    32,   218,     7,    35,    36,    37,    65,    94,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
       7,   559,   560,    28,    29,    30,   218,    65,    65,    34,
      35,    20,     5,     5,    39,    66,    76,   575,     7,   469,
     470,    72,    76,   199,    78,   225,    76,   219,     8,    76,
      81,    11,    12,    13,     8,   217,    87,   143,    74,    75,
     219,    95,    65,    97,    98,    76,   100,    78,    79,    80,
     101,   492,    88,   107,   108,    91,   162,   163,   164,   165,
     166,   167,   168,   169,   170,    66,   102,   103,   104,   105,
      66,    51,    66,   217,     5,    65,    56,    27,    66,    59,
      60,    61,     5,    63,    89,   218,   218,    67,   565,   218,
      70,   565,    72,    98,   175,   176,   177,   178,   179,   104,
      66,   575,   102,   577,    65,   110,   111,    15,   219,   568,
     421,   555,    95,   241,   588,    98,    51,    52,    53,    54,
      55,    56,   645,   564,   686,   566,   567,   110,   616,   679,
     564,   114,   566,   567,   117,   118,   646,    66,   687,   122,
     123,   124,   125,   595,   192,   622,    73,   446,   622,   593,
      28,   640,    30,   439,    32,   542,   465,    35,    36,    37,
     546,   471,   603,   604,   608,   472,   233,   650,   473,   515,
     180,   615,   613,   193,   194,   195,   196,   197,   661,   620,
     621,   179,    -1,    -1,    74,    75,    -1,   621,    78,   180,
     181,   182,   183,   184,   185,   186,   187,   671,    88,    89,
      90,    91,    92,    93,    94,    95,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   655,   692,    -1,   658,   692,    -1,
       1,    -1,   663,     4,    -1,     6,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   682,    -1,
      21,    -1,    23,    -1,    25,    26,    -1,    -1,    -1,   690,
      -1,    -1,   693,   694,    -1,    -1,   697,   698,   699,   693,
     694,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      51,    52,    53,    54,    55,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    66,    67,    68,    -1,    -1,
      -1,    -1,    73,    -1,    -1,    76,    77,    -1,    -1,    -1,
      81,    -1,    -1,    -1,    -1,    -1,    87,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,    -1,    -1,
     101,    -1,    -1,    -1,    -1,   106,    -1,    -1,   109,    -1,
      -1,   112,   113,    -1,    -1,   116,    -1,    -1,   119,    -1,
     121,    -1,    -1,    -1,    -1,   126,   127,    -1,   129,   130,
     131,    -1,    -1,   134,   135,    -1,    -1,   138,   139,   140,
      -1,    -1,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,     1,    -1,    -1,     4,    -1,     6,    -1,    -1,    -1,
     171,    -1,    -1,   174,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    -1,    23,    -1,    25,    26,   188,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   198,    -1,    -1,
      -1,   202,   203,   204,   205,    -1,    -1,    -1,   209,    -1,
      -1,    51,    52,    53,    54,    55,    56,   218,   219,   220,
     221,    -1,    -1,    -1,    -1,    65,    66,    67,    68,    -1,
      -1,    -1,    -1,    73,    -1,    -1,    76,    77,    -1,    -1,
      -1,    81,    -1,    -1,    -1,    -1,    -1,    87,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,    -1,
      -1,   101,    -1,    -1,    -1,    -1,   106,    -1,    -1,   109,
      -1,    -1,   112,   113,    -1,    -1,   116,    -1,    -1,   119,
      -1,   121,    -1,    -1,    -1,    -1,   126,   127,    -1,   129,
     130,   131,    -1,    -1,   134,   135,    -1,    -1,   138,   139,
     140,    -1,    -1,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,     5,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   171,    -1,    -1,   174,    -1,    -1,    -1,    21,    -1,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   188,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   198,    -1,
      -1,    -1,   202,   203,   204,   205,    -1,    -1,    -1,   209,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   218,   219,
     220,   221,    65,    66,    67,    68,    -1,    -1,    -1,    -1,
      73,    -1,    -1,    -1,    77,    -1,    -1,    -1,    81,    -1,
      -1,    -1,    -1,    -1,    87,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    96,    -1,    -1,    -1,    -1,   101,    -1,
      -1,    -1,    -1,   106,    -1,    -1,   109,    -1,    -1,   112,
     113,    -1,    -1,   116,    -1,    -1,   119,    -1,   121,    -1,
      -1,    -1,    -1,   126,   127,    -1,   129,   130,   131,    -1,
      -1,   134,   135,    -1,    -1,   138,   139,   140,    -1,    -1,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,    -1,
      -1,    -1,    -1,     9,    10,    11,    12,    13,    14,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   218,    -1,   220,   221,    65,
      66,    67,    68,    -1,    -1,    -1,    -1,    73,    -1,    -1,
      -1,    77,    -1,    -1,    -1,    81,    -1,    -1,    -1,    -1,
      -1,    87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      96,    -1,    -1,    -1,    -1,   101,    -1,    -1,    -1,    -1,
     106,    -1,    -1,   109,    -1,    -1,   112,   113,    -1,    -1,
     116,    91,    -1,   119,    94,   121,    -1,    -1,    -1,    -1,
     126,   127,   102,   129,   130,   131,    -1,    -1,   134,   135,
      -1,    -1,   138,   139,   140,    -1,    -1,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,    -1,    21,    -1,    23,
      -1,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,    -1,    -1,    -1,    -1,    -1,    -1,    51,    52,    53,
      54,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    66,    67,    68,    -1,    -1,    -1,    -1,    73,
      -1,    -1,   218,    77,   220,   221,    -1,    81,    -1,    -1,
      -1,    -1,    -1,    87,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    96,    -1,    -1,    -1,    -1,   101,    -1,    -1,
      -1,    -1,   106,    -1,    -1,   109,    -1,    -1,   112,   113,
      -1,    -1,   116,    -1,    -1,   119,    -1,   121,    -1,    -1,
      -1,    -1,   126,   127,    -1,   129,   130,   131,    -1,    -1,
     134,   135,    -1,    -1,   138,   139,   140,    -1,    -1,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   171,    -1,    -1,
     174,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   188,    -1,    -1,    -1,    21,    -1,
      23,    -1,    -1,    -1,   198,    -1,    -1,    -1,   202,   203,
     204,   205,    -1,    -1,    -1,   209,    -1,    -1,    -1,    -1,
     214,    -1,    -1,    -1,   218,    -1,   220,   221,    51,    52,
      53,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    66,    67,    68,    -1,    -1,    -1,    -1,
      73,    -1,    -1,    -1,    77,    -1,    -1,    -1,    81,    -1,
      -1,    -1,    -1,    -1,    87,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    96,    -1,    -1,    -1,    -1,   101,    -1,
      -1,    -1,    -1,   106,    -1,    -1,   109,    -1,    -1,   112,
     113,    -1,    -1,   116,    -1,    -1,   119,    -1,   121,    -1,
      -1,    -1,    -1,   126,   127,    -1,   129,   130,   131,    -1,
      -1,   134,   135,    -1,    -1,   138,   139,   140,    -1,    -1,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    23,    -1,   171,    -1,
      -1,   174,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   188,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   198,    -1,    -1,    -1,   202,
     203,   204,   205,    -1,    -1,    -1,   209,    -1,    65,    66,
      67,    68,    -1,    -1,    -1,   218,    73,   220,   221,    -1,
      77,    -1,    -1,    -1,    81,    -1,    -1,    -1,    -1,    -1,
      87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    96,
      -1,    -1,    -1,    -1,   101,    -1,    -1,    -1,    -1,   106,
      -1,    -1,   109,    -1,    -1,   112,   113,    -1,    -1,   116,
      -1,    -1,   119,    -1,   121,    -1,    -1,    -1,    -1,   126,
     127,    -1,   129,   130,   131,    -1,    -1,   134,   135,    -1,
      -1,   138,   139,   140,    -1,    -1,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,    -1,    21,    -1,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    66,    67,    -1,    -1,    -1,    -1,    -1,    73,    -1,
      -1,   218,    77,   220,   221,    -1,    81,    -1,    -1,    -1,
      -1,    -1,    87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    96,    -1,    -1,    -1,    -1,   101,    -1,    -1,    -1,
      -1,   106,    -1,    -1,   109,    -1,    -1,   112,   113,    -1,
      -1,   116,    -1,    -1,   119,    -1,   121,    -1,    -1,    -1,
      -1,   126,   127,    -1,   129,   130,   131,    -1,    -1,   134,
     135,    23,    -1,   138,   139,   140,    -1,    -1,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,    -1,    -1,    51,
      52,    53,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    66,    67,    -1,    -1,    -1,    -1,
      -1,    73,    -1,    -1,    -1,    77,    -1,    -1,    -1,    81,
      -1,    -1,    -1,    -1,    -1,    87,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    96,    -1,    -1,    -1,    -1,   101,
      -1,    -1,    -1,    -1,   106,   220,   221,   109,    -1,    -1,
     112,   113,    -1,    -1,   116,    -1,    -1,   119,    23,   121,
      -1,    -1,    -1,    -1,   126,   127,    -1,   129,   130,   131,
      -1,    -1,   134,   135,    -1,    -1,   138,   139,   140,    -1,
      -1,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
      65,    66,    67,    -1,    -1,    -1,    -1,    -1,    73,    -1,
      -1,    -1,    77,    -1,    -1,    -1,    81,    -1,    -1,    -1,
      -1,    -1,    87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    96,    -1,    -1,    -1,    -1,   101,    -1,    -1,    -1,
      -1,   106,    -1,    -1,   109,    -1,    -1,   112,   113,    -1,
      -1,   116,    -1,    -1,   119,    -1,   121,    -1,   220,   221,
      -1,   126,   127,    -1,   129,   130,   131,    -1,    -1,   134,
     135,    -1,    -1,   138,   139,   140,    -1,    -1,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   220,   221
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   227,     0,     1,     4,     6,    25,    26,    28,    30,
      32,    35,    36,    37,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    72,    81,    87,   101,   228,
     230,   231,   232,   233,   262,   263,   264,   266,   272,   228,
      67,    66,   260,   264,   266,   272,   264,   268,   268,   268,
     233,    28,    30,   234,    32,   235,    28,    30,    32,    35,
      36,    37,   236,    28,    29,    30,    34,    35,    39,   237,
      28,    30,    35,    39,   238,    30,   239,    23,    65,    66,
      67,    73,    77,    81,    87,    96,   101,   106,   109,   112,
     113,   116,   119,   121,   126,   127,   129,   130,   131,   134,
     135,   138,   139,   140,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   220,   221,   246,   261,   314,   315,   316,
     339,   342,   344,   347,   348,   350,   352,   354,   356,   358,
     360,   362,   364,   366,   368,   370,   372,   374,   376,   378,
     380,   381,   383,   385,   387,   389,   391,   393,   215,   216,
     240,   245,    66,   241,   242,     0,   228,   260,   260,    38,
     270,    21,    51,    52,    53,    54,    55,    56,    68,   140,
     161,   171,   174,   188,   198,   202,   203,   204,   205,   209,
     218,   275,   276,   277,   278,   279,   283,   284,   287,   288,
     292,   294,   295,   297,   298,   300,   301,   302,   303,   307,
     308,   313,   316,   317,   318,   319,   320,   321,   322,   324,
     325,   326,   327,   329,   330,   331,   332,   336,   338,   342,
     343,   346,   228,   217,   247,   249,   275,   260,   251,   332,
     255,   264,   266,   272,   264,   266,   272,   268,   268,   268,
     264,   262,   265,   266,   265,   268,   263,   274,   264,   266,
     268,   274,   266,    69,    70,    71,   260,   349,    74,    75,
      76,   351,    76,    78,    79,    80,   353,    82,    83,    84,
      85,    86,   355,    74,    75,    78,    88,    89,    90,    91,
      92,    93,    94,    95,   357,    76,    78,    95,    97,    98,
      99,   100,   359,    74,    75,    88,    91,   102,   103,   104,
     105,   361,    76,    78,    95,    97,    98,   100,   107,   108,
     363,    89,    98,   104,   110,   111,   365,    98,   111,   367,
     104,   114,   115,   369,    91,    95,   117,   118,   371,    95,
     117,   118,   120,   373,    95,    98,   110,   114,   117,   118,
     122,   123,   124,   125,   375,    76,   117,   118,   377,    95,
     117,   118,   128,   379,    76,    89,   104,   132,   384,   133,
     386,   133,   388,    89,   104,   382,    78,    92,   104,   110,
     136,   137,   390,    89,   104,   392,    76,    89,    95,   104,
     110,   394,    91,    94,   102,   141,   142,   340,   341,   342,
      74,    75,    94,   143,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   345,   260,   321,    29,    31,    33,    34,
      60,   243,    65,   213,   271,   260,   260,   340,   345,   189,
       4,   229,   333,   334,   214,   273,   277,   172,   173,   285,
     286,   175,   176,   177,   178,   179,   289,   290,   200,   296,
       5,   299,   322,   330,   206,   207,   208,   305,   306,    57,
     304,   305,   210,   211,   212,   309,   310,   311,   312,    15,
      16,    17,    18,   223,    20,    22,     8,    24,    37,     9,
      10,    11,    12,    13,    14,   321,   323,   330,   337,    35,
     323,   330,   335,   218,   218,   218,   218,   247,   249,   275,
     332,   260,     7,   224,   222,   244,   245,    65,    35,    35,
      65,   322,   327,   328,   330,     7,   219,   261,    65,    65,
     286,   261,    65,    65,    65,   180,   181,   182,   183,   184,
     185,   186,   187,   291,   290,    96,   106,   121,   201,   330,
     305,     5,     7,   330,   330,   310,     7,   316,   316,   317,
     318,   319,    65,   321,   321,    23,   218,   280,   330,     7,
       7,   330,   330,   228,   248,   250,   252,   256,   218,   218,
      65,    65,   330,   330,    20,     5,   229,   229,   334,    76,
      76,   199,    76,   330,   306,   305,   312,   260,   229,   281,
     282,   321,   321,    30,    35,    37,   219,   228,   230,    76,
     219,   228,   230,   259,   275,    60,    61,    64,    76,   114,
     219,   228,   230,   257,    60,    76,   114,   219,   228,   230,
     257,   248,   250,     7,   225,   193,   194,   195,   196,   197,
     293,   321,   322,   338,    66,    66,    66,   322,   327,   328,
       7,   219,   260,   267,   260,   269,   269,    66,   228,   228,
     217,    62,    63,   258,    65,   260,    58,    59,   253,   254,
     228,   217,   260,   253,   228,   219,   219,    65,   229,   229,
       5,   229,   282,   249,   251,   255,    27,   332,   228,     7,
     228,   332,     5,   228,   338,   218,   218,   218,    66,   254,
     260,   229,   250,   252,   256,   102,   228,   219,   219,   219,
      22,    65,   228,   228,   228,    65
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (&yylloc, scanner, state, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, &yylloc, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, &yylloc, scanner)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location, scanner, state); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, void *scanner, struct parser_state *state)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, scanner, state)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    void *scanner;
    struct parser_state *state;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
  YYUSE (scanner);
  YYUSE (state);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, void *scanner, struct parser_state *state)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp, scanner, state)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    void *scanner;
    struct parser_state *state;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, scanner, state);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, void *scanner, struct parser_state *state)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule, scanner, state)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
    void *scanner;
    struct parser_state *state;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       , scanner, state);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule, scanner, state); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, void *scanner, struct parser_state *state)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp, scanner, state)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
    void *scanner;
    struct parser_state *state;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (scanner);
  YYUSE (state);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {
      case 66: /* "\"string\"" */

/* Line 1391 of yacc.c  */
#line 214 "parser_bison.y"
	{ xfree((yyvaluep->string)); };

/* Line 1391 of yacc.c  */
#line 2758 "parser_bison.c"
	break;
      case 67: /* "QUOTED_STRING" */

/* Line 1391 of yacc.c  */
#line 214 "parser_bison.y"
	{ xfree((yyvaluep->string)); };

/* Line 1391 of yacc.c  */
#line 2767 "parser_bison.c"
	break;
      case 68: /* "\"error\"" */

/* Line 1391 of yacc.c  */
#line 214 "parser_bison.y"
	{ xfree((yyvaluep->string)); };

/* Line 1391 of yacc.c  */
#line 2776 "parser_bison.c"
	break;
      case 231: /* "line" */

/* Line 1391 of yacc.c  */
#line 400 "parser_bison.y"
	{ cmd_free((yyvaluep->cmd)); };

/* Line 1391 of yacc.c  */
#line 2785 "parser_bison.c"
	break;
      case 232: /* "base_cmd" */

/* Line 1391 of yacc.c  */
#line 403 "parser_bison.y"
	{ cmd_free((yyvaluep->cmd)); };

/* Line 1391 of yacc.c  */
#line 2794 "parser_bison.c"
	break;
      case 233: /* "add_cmd" */

/* Line 1391 of yacc.c  */
#line 403 "parser_bison.y"
	{ cmd_free((yyvaluep->cmd)); };

/* Line 1391 of yacc.c  */
#line 2803 "parser_bison.c"
	break;
      case 234: /* "create_cmd" */

/* Line 1391 of yacc.c  */
#line 403 "parser_bison.y"
	{ cmd_free((yyvaluep->cmd)); };

/* Line 1391 of yacc.c  */
#line 2812 "parser_bison.c"
	break;
      case 235: /* "insert_cmd" */

/* Line 1391 of yacc.c  */
#line 403 "parser_bison.y"
	{ cmd_free((yyvaluep->cmd)); };

/* Line 1391 of yacc.c  */
#line 2821 "parser_bison.c"
	break;
      case 236: /* "delete_cmd" */

/* Line 1391 of yacc.c  */
#line 403 "parser_bison.y"
	{ cmd_free((yyvaluep->cmd)); };

/* Line 1391 of yacc.c  */
#line 2830 "parser_bison.c"
	break;
      case 237: /* "list_cmd" */

/* Line 1391 of yacc.c  */
#line 403 "parser_bison.y"
	{ cmd_free((yyvaluep->cmd)); };

/* Line 1391 of yacc.c  */
#line 2839 "parser_bison.c"
	break;
      case 238: /* "flush_cmd" */

/* Line 1391 of yacc.c  */
#line 403 "parser_bison.y"
	{ cmd_free((yyvaluep->cmd)); };

/* Line 1391 of yacc.c  */
#line 2848 "parser_bison.c"
	break;
      case 239: /* "rename_cmd" */

/* Line 1391 of yacc.c  */
#line 403 "parser_bison.y"
	{ cmd_free((yyvaluep->cmd)); };

/* Line 1391 of yacc.c  */
#line 2857 "parser_bison.c"
	break;
      case 240: /* "export_cmd" */

/* Line 1391 of yacc.c  */
#line 403 "parser_bison.y"
	{ cmd_free((yyvaluep->cmd)); };

/* Line 1391 of yacc.c  */
#line 2866 "parser_bison.c"
	break;
      case 241: /* "monitor_cmd" */

/* Line 1391 of yacc.c  */
#line 403 "parser_bison.y"
	{ cmd_free((yyvaluep->cmd)); };

/* Line 1391 of yacc.c  */
#line 2875 "parser_bison.c"
	break;
      case 242: /* "monitor_event" */

/* Line 1391 of yacc.c  */
#line 539 "parser_bison.y"
	{ xfree((yyvaluep->string)); };

/* Line 1391 of yacc.c  */
#line 2884 "parser_bison.c"
	break;
      case 246: /* "describe_cmd" */

/* Line 1391 of yacc.c  */
#line 403 "parser_bison.y"
	{ cmd_free((yyvaluep->cmd)); };

/* Line 1391 of yacc.c  */
#line 2893 "parser_bison.c"
	break;
      case 247: /* "table_block_alloc" */

/* Line 1391 of yacc.c  */
#line 412 "parser_bison.y"
	{ close_scope(state); table_free((yyvaluep->table)); };

/* Line 1391 of yacc.c  */
#line 2902 "parser_bison.c"
	break;
      case 249: /* "chain_block_alloc" */

/* Line 1391 of yacc.c  */
#line 414 "parser_bison.y"
	{ close_scope(state); chain_free((yyvaluep->chain)); };

/* Line 1391 of yacc.c  */
#line 2911 "parser_bison.c"
	break;
      case 251: /* "set_block_alloc" */

/* Line 1391 of yacc.c  */
#line 423 "parser_bison.y"
	{ set_free((yyvaluep->set)); };

/* Line 1391 of yacc.c  */
#line 2920 "parser_bison.c"
	break;
      case 255: /* "map_block_alloc" */

/* Line 1391 of yacc.c  */
#line 426 "parser_bison.y"
	{ set_free((yyvaluep->set)); };

/* Line 1391 of yacc.c  */
#line 2929 "parser_bison.c"
	break;
      case 260: /* "identifier" */

/* Line 1391 of yacc.c  */
#line 397 "parser_bison.y"
	{ xfree((yyvaluep->string)); };

/* Line 1391 of yacc.c  */
#line 2938 "parser_bison.c"
	break;
      case 261: /* "string" */

/* Line 1391 of yacc.c  */
#line 397 "parser_bison.y"
	{ xfree((yyvaluep->string)); };

/* Line 1391 of yacc.c  */
#line 2947 "parser_bison.c"
	break;
      case 264: /* "table_spec" */

/* Line 1391 of yacc.c  */
#line 406 "parser_bison.y"
	{ handle_free(&(yyvaluep->handle)); };

/* Line 1391 of yacc.c  */
#line 2956 "parser_bison.c"
	break;
      case 265: /* "tables_spec" */

/* Line 1391 of yacc.c  */
#line 406 "parser_bison.y"
	{ handle_free(&(yyvaluep->handle)); };

/* Line 1391 of yacc.c  */
#line 2965 "parser_bison.c"
	break;
      case 266: /* "chain_spec" */

/* Line 1391 of yacc.c  */
#line 406 "parser_bison.y"
	{ handle_free(&(yyvaluep->handle)); };

/* Line 1391 of yacc.c  */
#line 2974 "parser_bison.c"
	break;
      case 267: /* "chain_identifier" */

/* Line 1391 of yacc.c  */
#line 406 "parser_bison.y"
	{ handle_free(&(yyvaluep->handle)); };

/* Line 1391 of yacc.c  */
#line 2983 "parser_bison.c"
	break;
      case 268: /* "set_spec" */

/* Line 1391 of yacc.c  */
#line 408 "parser_bison.y"
	{ handle_free(&(yyvaluep->handle)); };

/* Line 1391 of yacc.c  */
#line 2992 "parser_bison.c"
	break;
      case 269: /* "set_identifier" */

/* Line 1391 of yacc.c  */
#line 408 "parser_bison.y"
	{ handle_free(&(yyvaluep->handle)); };

/* Line 1391 of yacc.c  */
#line 3001 "parser_bison.c"
	break;
      case 272: /* "ruleid_spec" */

/* Line 1391 of yacc.c  */
#line 406 "parser_bison.y"
	{ handle_free(&(yyvaluep->handle)); };

/* Line 1391 of yacc.c  */
#line 3010 "parser_bison.c"
	break;
      case 273: /* "comment_spec" */

/* Line 1391 of yacc.c  */
#line 397 "parser_bison.y"
	{ xfree((yyvaluep->string)); };

/* Line 1391 of yacc.c  */
#line 3019 "parser_bison.c"
	break;
      case 274: /* "ruleset_spec" */

/* Line 1391 of yacc.c  */
#line 406 "parser_bison.y"
	{ handle_free(&(yyvaluep->handle)); };

/* Line 1391 of yacc.c  */
#line 3028 "parser_bison.c"
	break;
      case 275: /* "rule" */

/* Line 1391 of yacc.c  */
#line 416 "parser_bison.y"
	{ rule_free((yyvaluep->rule)); };

/* Line 1391 of yacc.c  */
#line 3037 "parser_bison.c"
	break;
      case 276: /* "stmt_list" */

/* Line 1391 of yacc.c  */
#line 429 "parser_bison.y"
	{ stmt_list_free((yyvaluep->list)); xfree((yyvaluep->list)); };

/* Line 1391 of yacc.c  */
#line 3046 "parser_bison.c"
	break;
      case 277: /* "stmt" */

/* Line 1391 of yacc.c  */
#line 431 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3055 "parser_bison.c"
	break;
      case 278: /* "verdict_stmt" */

/* Line 1391 of yacc.c  */
#line 431 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3064 "parser_bison.c"
	break;
      case 279: /* "verdict_map_stmt" */

/* Line 1391 of yacc.c  */
#line 477 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3073 "parser_bison.c"
	break;
      case 280: /* "verdict_map_expr" */

/* Line 1391 of yacc.c  */
#line 480 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3082 "parser_bison.c"
	break;
      case 281: /* "verdict_map_list_expr" */

/* Line 1391 of yacc.c  */
#line 480 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3091 "parser_bison.c"
	break;
      case 282: /* "verdict_map_list_member_expr" */

/* Line 1391 of yacc.c  */
#line 480 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3100 "parser_bison.c"
	break;
      case 283: /* "counter_stmt" */

/* Line 1391 of yacc.c  */
#line 433 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3109 "parser_bison.c"
	break;
      case 284: /* "counter_stmt_alloc" */

/* Line 1391 of yacc.c  */
#line 433 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3118 "parser_bison.c"
	break;
      case 287: /* "log_stmt" */

/* Line 1391 of yacc.c  */
#line 439 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3127 "parser_bison.c"
	break;
      case 288: /* "log_stmt_alloc" */

/* Line 1391 of yacc.c  */
#line 439 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3136 "parser_bison.c"
	break;
      case 292: /* "limit_stmt" */

/* Line 1391 of yacc.c  */
#line 442 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3145 "parser_bison.c"
	break;
      case 294: /* "reject_stmt" */

/* Line 1391 of yacc.c  */
#line 445 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3154 "parser_bison.c"
	break;
      case 295: /* "reject_stmt_alloc" */

/* Line 1391 of yacc.c  */
#line 445 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3163 "parser_bison.c"
	break;
      case 297: /* "nat_stmt" */

/* Line 1391 of yacc.c  */
#line 447 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3172 "parser_bison.c"
	break;
      case 298: /* "nat_stmt_alloc" */

/* Line 1391 of yacc.c  */
#line 447 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3181 "parser_bison.c"
	break;
      case 300: /* "masq_stmt" */

/* Line 1391 of yacc.c  */
#line 447 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3190 "parser_bison.c"
	break;
      case 301: /* "masq_stmt_alloc" */

/* Line 1391 of yacc.c  */
#line 447 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3199 "parser_bison.c"
	break;
      case 302: /* "redir_stmt" */

/* Line 1391 of yacc.c  */
#line 447 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3208 "parser_bison.c"
	break;
      case 303: /* "redir_stmt_alloc" */

/* Line 1391 of yacc.c  */
#line 447 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3217 "parser_bison.c"
	break;
      case 307: /* "queue_stmt" */

/* Line 1391 of yacc.c  */
#line 450 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3226 "parser_bison.c"
	break;
      case 308: /* "queue_stmt_alloc" */

/* Line 1391 of yacc.c  */
#line 450 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3235 "parser_bison.c"
	break;
      case 313: /* "match_stmt" */

/* Line 1391 of yacc.c  */
#line 431 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3244 "parser_bison.c"
	break;
      case 314: /* "symbol_expr" */

/* Line 1391 of yacc.c  */
#line 454 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3253 "parser_bison.c"
	break;
      case 315: /* "integer_expr" */

/* Line 1391 of yacc.c  */
#line 454 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3262 "parser_bison.c"
	break;
      case 316: /* "primary_expr" */

/* Line 1391 of yacc.c  */
#line 456 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3271 "parser_bison.c"
	break;
      case 317: /* "shift_expr" */

/* Line 1391 of yacc.c  */
#line 456 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3280 "parser_bison.c"
	break;
      case 318: /* "and_expr" */

/* Line 1391 of yacc.c  */
#line 456 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3289 "parser_bison.c"
	break;
      case 319: /* "exclusive_or_expr" */

/* Line 1391 of yacc.c  */
#line 458 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3298 "parser_bison.c"
	break;
      case 320: /* "inclusive_or_expr" */

/* Line 1391 of yacc.c  */
#line 458 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3307 "parser_bison.c"
	break;
      case 321: /* "basic_expr" */

/* Line 1391 of yacc.c  */
#line 460 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3316 "parser_bison.c"
	break;
      case 322: /* "concat_expr" */

/* Line 1391 of yacc.c  */
#line 469 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3325 "parser_bison.c"
	break;
      case 323: /* "list_expr" */

/* Line 1391 of yacc.c  */
#line 467 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3334 "parser_bison.c"
	break;
      case 324: /* "prefix_expr" */

/* Line 1391 of yacc.c  */
#line 465 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3343 "parser_bison.c"
	break;
      case 325: /* "range_expr" */

/* Line 1391 of yacc.c  */
#line 465 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3352 "parser_bison.c"
	break;
      case 326: /* "wildcard_expr" */

/* Line 1391 of yacc.c  */
#line 465 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3361 "parser_bison.c"
	break;
      case 327: /* "multiton_expr" */

/* Line 1391 of yacc.c  */
#line 463 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3370 "parser_bison.c"
	break;
      case 328: /* "map_lhs_expr" */

/* Line 1391 of yacc.c  */
#line 469 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3379 "parser_bison.c"
	break;
      case 329: /* "map_expr" */

/* Line 1391 of yacc.c  */
#line 474 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3388 "parser_bison.c"
	break;
      case 330: /* "expr" */

/* Line 1391 of yacc.c  */
#line 486 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3397 "parser_bison.c"
	break;
      case 331: /* "error_expr" */

/* Line 1391 of yacc.c  */
#line 471 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3406 "parser_bison.c"
	break;
      case 332: /* "set_expr" */

/* Line 1391 of yacc.c  */
#line 483 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3415 "parser_bison.c"
	break;
      case 333: /* "set_list_expr" */

/* Line 1391 of yacc.c  */
#line 483 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3424 "parser_bison.c"
	break;
      case 334: /* "set_list_member_expr" */

/* Line 1391 of yacc.c  */
#line 483 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3433 "parser_bison.c"
	break;
      case 335: /* "initializer_expr" */

/* Line 1391 of yacc.c  */
#line 486 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3442 "parser_bison.c"
	break;
      case 336: /* "relational_expr" */

/* Line 1391 of yacc.c  */
#line 489 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3451 "parser_bison.c"
	break;
      case 338: /* "verdict_expr" */

/* Line 1391 of yacc.c  */
#line 454 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3460 "parser_bison.c"
	break;
      case 339: /* "meta_expr" */

/* Line 1391 of yacc.c  */
#line 530 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3469 "parser_bison.c"
	break;
      case 343: /* "meta_stmt" */

/* Line 1391 of yacc.c  */
#line 437 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3478 "parser_bison.c"
	break;
      case 344: /* "ct_expr" */

/* Line 1391 of yacc.c  */
#line 534 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3487 "parser_bison.c"
	break;
      case 346: /* "ct_stmt" */

/* Line 1391 of yacc.c  */
#line 435 "parser_bison.y"
	{ stmt_free((yyvaluep->stmt)); };

/* Line 1391 of yacc.c  */
#line 3496 "parser_bison.c"
	break;
      case 347: /* "payload_expr" */

/* Line 1391 of yacc.c  */
#line 493 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3505 "parser_bison.c"
	break;
      case 348: /* "payload_raw_expr" */

/* Line 1391 of yacc.c  */
#line 493 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3514 "parser_bison.c"
	break;
      case 350: /* "eth_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 496 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3523 "parser_bison.c"
	break;
      case 352: /* "vlan_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 496 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3532 "parser_bison.c"
	break;
      case 354: /* "arp_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 499 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3541 "parser_bison.c"
	break;
      case 356: /* "ip_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 502 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3550 "parser_bison.c"
	break;
      case 358: /* "icmp_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 502 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3559 "parser_bison.c"
	break;
      case 360: /* "ip6_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 505 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3568 "parser_bison.c"
	break;
      case 362: /* "icmp6_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 505 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3577 "parser_bison.c"
	break;
      case 364: /* "auth_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 508 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3586 "parser_bison.c"
	break;
      case 366: /* "esp_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 508 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3595 "parser_bison.c"
	break;
      case 368: /* "comp_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 508 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3604 "parser_bison.c"
	break;
      case 370: /* "udp_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 511 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3613 "parser_bison.c"
	break;
      case 372: /* "udplite_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 511 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3622 "parser_bison.c"
	break;
      case 374: /* "tcp_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 511 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3631 "parser_bison.c"
	break;
      case 376: /* "dccp_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 514 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3640 "parser_bison.c"
	break;
      case 378: /* "sctp_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 514 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3649 "parser_bison.c"
	break;
      case 380: /* "exthdr_expr" */

/* Line 1391 of yacc.c  */
#line 518 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3658 "parser_bison.c"
	break;
      case 381: /* "hbh_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 520 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3667 "parser_bison.c"
	break;
      case 383: /* "rt_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 523 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3676 "parser_bison.c"
	break;
      case 385: /* "rt0_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 523 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3685 "parser_bison.c"
	break;
      case 387: /* "rt2_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 523 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3694 "parser_bison.c"
	break;
      case 389: /* "frag_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 520 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3703 "parser_bison.c"
	break;
      case 391: /* "dst_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 520 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3712 "parser_bison.c"
	break;
      case 393: /* "mh_hdr_expr" */

/* Line 1391 of yacc.c  */
#line 526 "parser_bison.y"
	{ expr_free((yyvaluep->expr)); };

/* Line 1391 of yacc.c  */
#line 3721 "parser_bison.c"
	break;

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void *scanner, struct parser_state *state);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *scanner, struct parser_state *state)
#else
int
yyparse (scanner, state)
    void *scanner;
    struct parser_state *state;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

/* User initialization code.  */

/* Line 1590 of yacc.c  */
#line 112 "parser_bison.y"
{
	location_init(scanner, state, &yylloc);
#ifdef DEBUG
	if (debug_level & DEBUG_SCANNER)
		nft_set_debug(1, scanner);
	if (debug_level & DEBUG_PARSER)
		yydebug = 1;
#endif
}

/* Line 1590 of yacc.c  */
#line 3881 "parser_bison.c"

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:

/* Line 1806 of yacc.c  */
#line 546 "parser_bison.y"
    {
				if ((yyvsp[(2) - (2)].cmd) != NULL) {
					LIST_HEAD(list);

					(yyvsp[(2) - (2)].cmd)->location = (yylsp[(2) - (2)]);

					list_add_tail(&(yyvsp[(2) - (2)].cmd)->list, &list);
					if (cmd_evaluate(&state->ectx, (yyvsp[(2) - (2)].cmd)) < 0) {
						if (++state->nerrs == max_errors)
							YYABORT;
					} else
						list_splice_tail(&list, &state->cmds);
				}
			}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 571 "parser_bison.y"
    {
				if (scanner_include_file(scanner, (yyvsp[(2) - (3)].string), &(yyloc)) < 0) {
					xfree((yyvsp[(2) - (3)].string));
					YYERROR;
				}
				xfree((yyvsp[(2) - (3)].string));
			}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 579 "parser_bison.y"
    {
				struct scope *scope = current_scope(state);

				if (symbol_lookup(scope, (yyvsp[(2) - (5)].string)) != NULL) {
					erec_queue(error(&(yylsp[(2) - (5)]), "redfinition of symbol '%s'", (yyvsp[(2) - (5)].string)),
						   state->msgs);
					YYERROR;
				}

				symbol_bind(scope, (yyvsp[(2) - (5)].string), (yyvsp[(4) - (5)].expr));
				xfree((yyvsp[(2) - (5)].string));
			}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 592 "parser_bison.y"
    {
				if (++state->nerrs == max_errors)
					YYABORT;
				yyerrok;
			}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 599 "parser_bison.y"
    { (yyval.cmd) = NULL; }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 600 "parser_bison.y"
    { (yyval.cmd) = NULL; }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 601 "parser_bison.y"
    { (yyval.cmd) = (yyvsp[(1) - (2)].cmd); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 603 "parser_bison.y"
    {
				/*
				 * Very hackish workaround for bison >= 2.4: previous versions
				 * terminated parsing after EOF, 2.4+ tries to get further input
				 * in 'input' and calls the scanner again, causing a crash when
				 * the final input buffer has been popped. Terminate manually to
				 * avoid this. The correct fix should be to adjust the grammar
				 * to accept EOF in input, but for unknown reasons it does not
				 * work.
				 */
				if ((yyvsp[(1) - (2)].cmd) != NULL) {
					LIST_HEAD(list);

					(yyvsp[(1) - (2)].cmd)->location = (yylsp[(1) - (2)]);

					list_add_tail(&(yyvsp[(1) - (2)].cmd)->list, &list);
					if (cmd_evaluate(&state->ectx, (yyvsp[(1) - (2)].cmd)) < 0) {
						if (++state->nerrs == max_errors)
							YYABORT;
					} else
						list_splice_tail(&list, &state->cmds);
				}
				(yyval.cmd) = NULL;

				YYACCEPT;
			}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 631 "parser_bison.y"
    { (yyval.cmd) = (yyvsp[(1) - (1)].cmd); }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 632 "parser_bison.y"
    { (yyval.cmd) = (yyvsp[(2) - (2)].cmd); }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 633 "parser_bison.y"
    { (yyval.cmd) = (yyvsp[(2) - (2)].cmd); }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 634 "parser_bison.y"
    { (yyval.cmd) = (yyvsp[(2) - (2)].cmd); }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 635 "parser_bison.y"
    { (yyval.cmd) = (yyvsp[(2) - (2)].cmd); }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 636 "parser_bison.y"
    { (yyval.cmd) = (yyvsp[(2) - (2)].cmd); }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 637 "parser_bison.y"
    { (yyval.cmd) = (yyvsp[(2) - (2)].cmd); }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 638 "parser_bison.y"
    { (yyval.cmd) = (yyvsp[(2) - (2)].cmd); }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 639 "parser_bison.y"
    { (yyval.cmd) = (yyvsp[(2) - (2)].cmd); }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 640 "parser_bison.y"
    { (yyval.cmd) = (yyvsp[(2) - (2)].cmd); }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 641 "parser_bison.y"
    { (yyval.cmd) = (yyvsp[(2) - (2)].cmd); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 645 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 650 "parser_bison.y"
    {
				handle_merge(&(yyvsp[(3) - (6)].table)->handle, &(yyvsp[(2) - (6)].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_TABLE, &(yyvsp[(2) - (6)].handle), &(yyloc), (yyvsp[(5) - (6)].table));
			}
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 656 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 661 "parser_bison.y"
    {
				(yyvsp[(5) - (6)].chain)->location = (yylsp[(5) - (6)]);
				handle_merge(&(yyvsp[(3) - (6)].chain)->handle, &(yyvsp[(2) - (6)].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_CHAIN, &(yyvsp[(2) - (6)].handle), &(yyloc), (yyvsp[(5) - (6)].chain));
			}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 668 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[(2) - (3)].handle), &(yyloc), (yyvsp[(3) - (3)].rule));
			}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 672 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_RULE, &(yyvsp[(1) - (2)].handle), &(yyloc), (yyvsp[(2) - (2)].rule));
			}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 677 "parser_bison.y"
    {
				(yyvsp[(5) - (6)].set)->location = (yylsp[(5) - (6)]);
				handle_merge(&(yyvsp[(3) - (6)].set)->handle, &(yyvsp[(2) - (6)].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[(2) - (6)].handle), &(yyloc), (yyvsp[(5) - (6)].set));
			}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 684 "parser_bison.y"
    {
				(yyvsp[(5) - (6)].set)->location = (yylsp[(5) - (6)]);
				handle_merge(&(yyvsp[(3) - (6)].set)->handle, &(yyvsp[(2) - (6)].handle));
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SET, &(yyvsp[(2) - (6)].handle), &(yyloc), (yyvsp[(5) - (6)].set));
			}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 690 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_ADD, CMD_OBJ_SETELEM, &(yyvsp[(2) - (3)].handle), &(yyloc), (yyvsp[(3) - (3)].expr));
			}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 696 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 701 "parser_bison.y"
    {
				handle_merge(&(yyvsp[(3) - (6)].table)->handle, &(yyvsp[(2) - (6)].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_TABLE, &(yyvsp[(2) - (6)].handle), &(yyloc), (yyvsp[(5) - (6)].table));
			}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 707 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 712 "parser_bison.y"
    {
				(yyvsp[(5) - (6)].chain)->location = (yylsp[(5) - (6)]);
				handle_merge(&(yyvsp[(3) - (6)].chain)->handle, &(yyvsp[(2) - (6)].handle));
				close_scope(state);
				(yyval.cmd) = cmd_alloc(CMD_CREATE, CMD_OBJ_CHAIN, &(yyvsp[(2) - (6)].handle), &(yyloc), (yyvsp[(5) - (6)].chain));
			}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 721 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_INSERT, CMD_OBJ_RULE, &(yyvsp[(2) - (3)].handle), &(yyloc), (yyvsp[(3) - (3)].rule));
			}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 727 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_TABLE, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 731 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_CHAIN, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 735 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_RULE, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 739 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 743 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SET, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 747 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_DELETE, CMD_OBJ_SETELEM, &(yyvsp[(2) - (3)].handle), &(yyloc), (yyvsp[(3) - (3)].expr));
			}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 753 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 757 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_TABLE, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 761 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_CHAIN, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 765 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SETS, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 769 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_SET, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 773 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_LIST, CMD_OBJ_RULESET, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 779 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_TABLE, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 783 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_CHAIN, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 787 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_SET, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 791 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_FLUSH, CMD_OBJ_RULESET, &(yyvsp[(2) - (2)].handle), &(yyloc), NULL);
			}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 797 "parser_bison.y"
    {
				(yyval.cmd) = cmd_alloc(CMD_RENAME, CMD_OBJ_CHAIN, &(yyvsp[(2) - (3)].handle), &(yyloc), NULL);
				(yyval.cmd)->arg = (yyvsp[(3) - (3)].string);
			}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 804 "parser_bison.y"
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct export *export = export_alloc((yyvsp[(1) - (1)].val));
				(yyval.cmd) = cmd_alloc(CMD_EXPORT, CMD_OBJ_EXPORT, &h, &(yyloc), export);
			}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 812 "parser_bison.y"
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				struct monitor *m = monitor_alloc((yyvsp[(3) - (3)].val), (yyvsp[(2) - (3)].val), (yyvsp[(1) - (3)].string));
				m->location = (yylsp[(1) - (3)]);
				(yyval.cmd) = cmd_alloc(CMD_MONITOR, CMD_OBJ_MONITOR, &h, &(yyloc), m);
			}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 820 "parser_bison.y"
    { (yyval.string) = NULL; }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 821 "parser_bison.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 824 "parser_bison.y"
    { (yyval.val) = CMD_MONITOR_OBJ_ANY; }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 825 "parser_bison.y"
    { (yyval.val) = CMD_MONITOR_OBJ_TABLES; }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 826 "parser_bison.y"
    { (yyval.val) = CMD_MONITOR_OBJ_CHAINS; }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 827 "parser_bison.y"
    { (yyval.val) = CMD_MONITOR_OBJ_SETS; }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 828 "parser_bison.y"
    { (yyval.val) = CMD_MONITOR_OBJ_RULES; }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 829 "parser_bison.y"
    { (yyval.val) = CMD_MONITOR_OBJ_ELEMS; }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 832 "parser_bison.y"
    { (yyval.val) = NFT_OUTPUT_DEFAULT; }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 836 "parser_bison.y"
    { (yyval.val) = NFT_OUTPUT_XML; }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 837 "parser_bison.y"
    { (yyval.val) = NFT_OUTPUT_JSON; }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 841 "parser_bison.y"
    {
				struct handle h = { .family = NFPROTO_UNSPEC };
				(yyval.cmd) = cmd_alloc(CMD_DESCRIBE, CMD_OBJ_EXPR, &h, &(yyloc), NULL);
				(yyval.cmd)->expr = (yyvsp[(1) - (1)].expr);
			}
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 849 "parser_bison.y"
    {
				(yyval.table) = table_alloc();
				open_scope(state, &(yyval.table)->scope);
			}
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 855 "parser_bison.y"
    { (yyval.table) = (yyvsp[(-1) - (0)].table); }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 861 "parser_bison.y"
    {
				(yyvsp[(4) - (8)].chain)->location = (yylsp[(3) - (8)]);
				handle_merge(&(yyvsp[(4) - (8)].chain)->handle, &(yyvsp[(3) - (8)].handle));
				handle_free(&(yyvsp[(3) - (8)].handle));
				close_scope(state);
				list_add_tail(&(yyvsp[(4) - (8)].chain)->list, &(yyvsp[(1) - (8)].table)->chains);
				(yyval.table) = (yyvsp[(1) - (8)].table);
			}
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 872 "parser_bison.y"
    {
				(yyvsp[(4) - (8)].set)->location = (yylsp[(3) - (8)]);
				handle_merge(&(yyvsp[(4) - (8)].set)->handle, &(yyvsp[(3) - (8)].handle));
				handle_free(&(yyvsp[(3) - (8)].handle));
				list_add_tail(&(yyvsp[(4) - (8)].set)->list, &(yyvsp[(1) - (8)].table)->sets);
				(yyval.table) = (yyvsp[(1) - (8)].table);
			}
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 882 "parser_bison.y"
    {
				(yyvsp[(4) - (8)].set)->location = (yylsp[(3) - (8)]);
				handle_merge(&(yyvsp[(4) - (8)].set)->handle, &(yyvsp[(3) - (8)].handle));
				handle_free(&(yyvsp[(3) - (8)].handle));
				list_add_tail(&(yyvsp[(4) - (8)].set)->list, &(yyvsp[(1) - (8)].table)->sets);
				(yyval.table) = (yyvsp[(1) - (8)].table);
			}
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 892 "parser_bison.y"
    {
				(yyval.chain) = chain_alloc(NULL);
				open_scope(state, &(yyval.chain)->scope);
			}
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 898 "parser_bison.y"
    { (yyval.chain) = (yyvsp[(-1) - (0)].chain); }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 903 "parser_bison.y"
    {
				list_add_tail(&(yyvsp[(2) - (3)].rule)->list, &(yyvsp[(1) - (3)].chain)->rules);
				(yyval.chain) = (yyvsp[(1) - (3)].chain);
			}
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 910 "parser_bison.y"
    {
				(yyval.set) = set_alloc(NULL);
			}
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 915 "parser_bison.y"
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 919 "parser_bison.y"
    {
				(yyvsp[(1) - (4)].set)->keytype = datatype_lookup_byname((yyvsp[(3) - (4)].string));
				if ((yyvsp[(1) - (4)].set)->keytype == NULL) {
					erec_queue(error(&(yylsp[(3) - (4)]), "unknown datatype %s", (yyvsp[(3) - (4)].string)),
						   state->msgs);
					YYERROR;
				}
				(yyval.set) = (yyvsp[(1) - (4)].set);
			}
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 929 "parser_bison.y"
    {
				(yyvsp[(1) - (4)].set)->flags = (yyvsp[(3) - (4)].val);
				(yyval.set) = (yyvsp[(1) - (4)].set);
			}
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 934 "parser_bison.y"
    {
				(yyvsp[(1) - (4)].set)->init = (yyvsp[(4) - (4)].expr);
				(yyval.set) = (yyvsp[(1) - (4)].set);
			}
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 942 "parser_bison.y"
    {
				(yyval.val) = (yyvsp[(1) - (3)].val) | (yyvsp[(3) - (3)].val);
			}
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 948 "parser_bison.y"
    { (yyval.val) = SET_F_CONSTANT; }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 949 "parser_bison.y"
    { (yyval.val) = SET_F_INTERVAL; }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 953 "parser_bison.y"
    {
				(yyval.set) = set_alloc(NULL);
				(yyval.set)->flags |= NFT_SET_MAP;
			}
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 959 "parser_bison.y"
    { (yyval.set) = (yyvsp[(-1) - (0)].set); }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 965 "parser_bison.y"
    {
				(yyvsp[(1) - (6)].set)->keytype = datatype_lookup_byname((yyvsp[(3) - (6)].string));
				if ((yyvsp[(1) - (6)].set)->keytype == NULL) {
					erec_queue(error(&(yylsp[(3) - (6)]), "unknown datatype %s", (yyvsp[(3) - (6)].string)),
						   state->msgs);
					YYERROR;
				}

				(yyvsp[(1) - (6)].set)->datatype = datatype_lookup_byname((yyvsp[(5) - (6)].string));
				if ((yyvsp[(1) - (6)].set)->datatype == NULL) {
					erec_queue(error(&(yylsp[(5) - (6)]), "unknown datatype %s", (yyvsp[(5) - (6)].string)),
						   state->msgs);
					YYERROR;
				}

				(yyval.set) = (yyvsp[(1) - (6)].set);
			}
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 983 "parser_bison.y"
    {
				(yyvsp[(1) - (4)].set)->flags = (yyvsp[(3) - (4)].val);
				(yyval.set) = (yyvsp[(1) - (4)].set);
			}
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 988 "parser_bison.y"
    {
				(yyvsp[(1) - (4)].set)->init = (yyvsp[(4) - (4)].expr);
				(yyval.set) = (yyvsp[(1) - (4)].set);
			}
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 996 "parser_bison.y"
    {
				(yyvsp[(0) - (2)].set)->policy = (yyvsp[(2) - (2)].val);
			}
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 1000 "parser_bison.y"
    {
				(yyvsp[(0) - (2)].set)->desc.size = (yyvsp[(2) - (2)].val);
			}
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 1005 "parser_bison.y"
    { (yyval.val) = NFT_SET_POL_PERFORMANCE; }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 1006 "parser_bison.y"
    { (yyval.val) = NFT_SET_POL_MEMORY; }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 1010 "parser_bison.y"
    {
				(yyvsp[(0) - (6)].chain)->type		= chain_type_name_lookup((yyvsp[(2) - (6)].string));
				if ((yyvsp[(0) - (6)].chain)->type == NULL) {
					erec_queue(error(&(yylsp[(2) - (6)]), "unknown chain type %s", (yyvsp[(2) - (6)].string)),
						   state->msgs);
					YYERROR;
				}
				(yyvsp[(0) - (6)].chain)->hookstr	= chain_hookname_lookup((yyvsp[(4) - (6)].string));
				if ((yyvsp[(0) - (6)].chain)->hookstr == NULL) {
					erec_queue(error(&(yylsp[(4) - (6)]), "unknown chain hook %s", (yyvsp[(4) - (6)].string)),
						   state->msgs);
					YYERROR;
				}
				(yyvsp[(0) - (6)].chain)->priority	= (yyvsp[(6) - (6)].val);
				(yyvsp[(0) - (6)].chain)->flags	|= CHAIN_F_BASECHAIN;
			}
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 1027 "parser_bison.y"
    {
				(yyvsp[(0) - (7)].chain)->type		= chain_type_name_lookup((yyvsp[(2) - (7)].string));
				if ((yyvsp[(0) - (7)].chain)->type == NULL) {
					erec_queue(error(&(yylsp[(2) - (7)]), "unknown type name %s", (yyvsp[(2) - (7)].string)),
						   state->msgs);
					YYERROR;
				}
				(yyvsp[(0) - (7)].chain)->hookstr	= chain_hookname_lookup((yyvsp[(4) - (7)].string));
				if ((yyvsp[(0) - (7)].chain)->hookstr == NULL) {
					erec_queue(error(&(yylsp[(4) - (7)]), "unknown hook name %s", (yyvsp[(4) - (7)].string)),
						   state->msgs);
					YYERROR;
				}
				(yyvsp[(0) - (7)].chain)->priority	= -(yyvsp[(7) - (7)].val);
				(yyvsp[(0) - (7)].chain)->flags	|= CHAIN_F_BASECHAIN;
			}
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 1052 "parser_bison.y"
    { (yyval.val) = NFPROTO_IPV4; }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 1056 "parser_bison.y"
    { (yyval.val) = NFPROTO_IPV4; }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 1057 "parser_bison.y"
    { (yyval.val) = NFPROTO_IPV6; }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 1058 "parser_bison.y"
    { (yyval.val) = NFPROTO_INET; }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 1059 "parser_bison.y"
    { (yyval.val) = NFPROTO_ARP; }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 1060 "parser_bison.y"
    { (yyval.val) = NFPROTO_BRIDGE; }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 1064 "parser_bison.y"
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[(1) - (2)].val);
				(yyval.handle).table	= (yyvsp[(2) - (2)].string);
			}
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 1072 "parser_bison.y"
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[(1) - (1)].val);
				(yyval.handle).table	= NULL;
			}
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 1080 "parser_bison.y"
    {
				(yyval.handle)		= (yyvsp[(1) - (2)].handle);
				(yyval.handle).chain	= (yyvsp[(2) - (2)].string);
			}
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 1087 "parser_bison.y"
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).chain	= (yyvsp[(1) - (1)].string);
			}
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 1094 "parser_bison.y"
    {
				(yyval.handle)		= (yyvsp[(1) - (2)].handle);
				(yyval.handle).set		= (yyvsp[(2) - (2)].string);
			}
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 1101 "parser_bison.y"
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).set		= (yyvsp[(1) - (1)].string);
			}
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 1108 "parser_bison.y"
    {
				(yyval.val) = 0;
			}
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 1112 "parser_bison.y"
    {
				(yyval.val) = (yyvsp[(2) - (2)].val);
			}
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 1118 "parser_bison.y"
    {
				(yyval.val) = 0;
			}
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 1122 "parser_bison.y"
    {
				(yyval.val) = (yyvsp[(2) - (2)].val);
			}
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 1128 "parser_bison.y"
    {
				(yyval.handle)		= (yyvsp[(1) - (3)].handle);
				(yyval.handle).handle	= (yyvsp[(2) - (3)].val);
				(yyval.handle).position	= (yyvsp[(3) - (3)].val);
			}
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 1136 "parser_bison.y"
    {
				(yyval.string) = NULL;
			}
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 1140 "parser_bison.y"
    {
				(yyval.string) = (yyvsp[(2) - (2)].string);
			}
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 1146 "parser_bison.y"
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= NFPROTO_UNSPEC;
			}
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 1151 "parser_bison.y"
    {
				memset(&(yyval.handle), 0, sizeof((yyval.handle)));
				(yyval.handle).family	= (yyvsp[(1) - (1)].val);
			}
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 1158 "parser_bison.y"
    {
				struct stmt *i;

				(yyval.rule) = rule_alloc(&(yyloc), NULL);
				(yyval.rule)->handle.comment = (yyvsp[(2) - (2)].string);
				list_for_each_entry(i, (yyvsp[(1) - (2)].list), list)
					(yyval.rule)->num_stmts++;
				list_splice_tail((yyvsp[(1) - (2)].list), &(yyval.rule)->stmts);
				xfree((yyvsp[(1) - (2)].list));
			}
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 1171 "parser_bison.y"
    {
				(yyval.list) = xmalloc(sizeof(*(yyval.list)));
				init_list_head((yyval.list));
				list_add_tail(&(yyvsp[(1) - (1)].stmt)->list, (yyval.list));
			}
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 1177 "parser_bison.y"
    {
				(yyval.list) = (yyvsp[(1) - (2)].list);
				list_add_tail(&(yyvsp[(2) - (2)].stmt)->list, (yyvsp[(1) - (2)].list));
			}
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 1198 "parser_bison.y"
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[(1) - (1)].expr));
			}
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 1202 "parser_bison.y"
    {
				(yyval.stmt) = verdict_stmt_alloc(&(yyloc), (yyvsp[(1) - (1)].expr));
			}
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 1208 "parser_bison.y"
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
			}
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 1214 "parser_bison.y"
    {
				(yyvsp[(2) - (3)].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[(2) - (3)].expr);
			}
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 1219 "parser_bison.y"
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[(2) - (2)].string));
				xfree((yyvsp[(2) - (2)].string));
			}
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 1228 "parser_bison.y"
    {
				(yyval.expr) = set_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[(1) - (1)].expr));
			}
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 1233 "parser_bison.y"
    {
				compound_expr_add((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
				(yyval.expr) = (yyvsp[(1) - (3)].expr);
			}
    break;

  case 159:

/* Line 1806 of yacc.c  */
#line 1241 "parser_bison.y"
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[(2) - (5)].expr), (yyvsp[(4) - (5)].expr));
			}
    break;

  case 162:

/* Line 1806 of yacc.c  */
#line 1251 "parser_bison.y"
    {
				(yyval.stmt) = counter_stmt_alloc(&(yyloc));
			}
    break;

  case 163:

/* Line 1806 of yacc.c  */
#line 1257 "parser_bison.y"
    {
				(yyval.stmt)	= (yyvsp[(0) - (1)].stmt);
			}
    break;

  case 165:

/* Line 1806 of yacc.c  */
#line 1264 "parser_bison.y"
    {
				(yyvsp[(0) - (2)].stmt)->counter.packets = (yyvsp[(2) - (2)].val);
			}
    break;

  case 166:

/* Line 1806 of yacc.c  */
#line 1268 "parser_bison.y"
    {
				(yyvsp[(0) - (2)].stmt)->counter.bytes	 = (yyvsp[(2) - (2)].val);
			}
    break;

  case 169:

/* Line 1806 of yacc.c  */
#line 1278 "parser_bison.y"
    {
				(yyval.stmt) = log_stmt_alloc(&(yyloc));
			}
    break;

  case 170:

/* Line 1806 of yacc.c  */
#line 1284 "parser_bison.y"
    {
				(yyval.stmt)	= (yyvsp[(0) - (1)].stmt);
			}
    break;

  case 172:

/* Line 1806 of yacc.c  */
#line 1291 "parser_bison.y"
    {
				(yyvsp[(0) - (2)].stmt)->log.prefix	 = (yyvsp[(2) - (2)].string);
				(yyvsp[(0) - (2)].stmt)->log.flags 	|= STMT_LOG_PREFIX;
			}
    break;

  case 173:

/* Line 1806 of yacc.c  */
#line 1296 "parser_bison.y"
    {
				(yyvsp[(0) - (2)].stmt)->log.group	 = (yyvsp[(2) - (2)].val);
				(yyvsp[(0) - (2)].stmt)->log.flags 	|= STMT_LOG_GROUP;
			}
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 1301 "parser_bison.y"
    {
				(yyvsp[(0) - (2)].stmt)->log.snaplen	 = (yyvsp[(2) - (2)].val);
				(yyvsp[(0) - (2)].stmt)->log.flags 	|= STMT_LOG_SNAPLEN;
			}
    break;

  case 175:

/* Line 1806 of yacc.c  */
#line 1306 "parser_bison.y"
    {
				(yyvsp[(0) - (2)].stmt)->log.qthreshold = (yyvsp[(2) - (2)].val);
				(yyvsp[(0) - (2)].stmt)->log.flags 	|= STMT_LOG_QTHRESHOLD;
			}
    break;

  case 176:

/* Line 1806 of yacc.c  */
#line 1311 "parser_bison.y"
    {
				(yyvsp[(0) - (2)].stmt)->log.level	= (yyvsp[(2) - (2)].val);
				(yyvsp[(0) - (2)].stmt)->log.flags 	|= STMT_LOG_LEVEL;
			}
    break;

  case 177:

/* Line 1806 of yacc.c  */
#line 1317 "parser_bison.y"
    { (yyval.val) = LOG_EMERG; }
    break;

  case 178:

/* Line 1806 of yacc.c  */
#line 1318 "parser_bison.y"
    { (yyval.val) = LOG_ALERT; }
    break;

  case 179:

/* Line 1806 of yacc.c  */
#line 1319 "parser_bison.y"
    { (yyval.val) = LOG_CRIT; }
    break;

  case 180:

/* Line 1806 of yacc.c  */
#line 1320 "parser_bison.y"
    { (yyval.val) = LOG_ERR; }
    break;

  case 181:

/* Line 1806 of yacc.c  */
#line 1321 "parser_bison.y"
    { (yyval.val) = LOG_WARNING; }
    break;

  case 182:

/* Line 1806 of yacc.c  */
#line 1322 "parser_bison.y"
    { (yyval.val) = LOG_NOTICE; }
    break;

  case 183:

/* Line 1806 of yacc.c  */
#line 1323 "parser_bison.y"
    { (yyval.val) = LOG_INFO; }
    break;

  case 184:

/* Line 1806 of yacc.c  */
#line 1324 "parser_bison.y"
    { (yyval.val) = LOG_DEBUG; }
    break;

  case 185:

/* Line 1806 of yacc.c  */
#line 1328 "parser_bison.y"
    {
				(yyval.stmt) = limit_stmt_alloc(&(yyloc));
				(yyval.stmt)->limit.rate	= (yyvsp[(3) - (5)].val);
				(yyval.stmt)->limit.unit	= (yyvsp[(5) - (5)].val);
			}
    break;

  case 186:

/* Line 1806 of yacc.c  */
#line 1335 "parser_bison.y"
    { (yyval.val) = 1ULL; }
    break;

  case 187:

/* Line 1806 of yacc.c  */
#line 1336 "parser_bison.y"
    { (yyval.val) = 1ULL * 60; }
    break;

  case 188:

/* Line 1806 of yacc.c  */
#line 1337 "parser_bison.y"
    { (yyval.val) = 1ULL * 60 * 60; }
    break;

  case 189:

/* Line 1806 of yacc.c  */
#line 1338 "parser_bison.y"
    { (yyval.val) = 1ULL * 60 * 60 * 24; }
    break;

  case 190:

/* Line 1806 of yacc.c  */
#line 1339 "parser_bison.y"
    { (yyval.val) = 1ULL * 60 * 60 * 24 * 7; }
    break;

  case 192:

/* Line 1806 of yacc.c  */
#line 1346 "parser_bison.y"
    {
				(yyval.stmt) = reject_stmt_alloc(&(yyloc));
			}
    break;

  case 193:

/* Line 1806 of yacc.c  */
#line 1352 "parser_bison.y"
    {
				(yyvsp[(0) - (0)].stmt)->reject.type = -1;
				(yyvsp[(0) - (0)].stmt)->reject.icmp_code = -1;
			}
    break;

  case 194:

/* Line 1806 of yacc.c  */
#line 1357 "parser_bison.y"
    {
				(yyvsp[(0) - (4)].stmt)->reject.family = NFPROTO_IPV4;
				(yyvsp[(0) - (4)].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[(0) - (4)].stmt)->reject.expr =
					symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
							  current_scope(state),
							  (yyvsp[(4) - (4)].string));
				(yyvsp[(0) - (4)].stmt)->reject.expr->dtype = &icmp_code_type;
			}
    break;

  case 195:

/* Line 1806 of yacc.c  */
#line 1367 "parser_bison.y"
    {
				(yyvsp[(0) - (4)].stmt)->reject.family = NFPROTO_IPV6;
				(yyvsp[(0) - (4)].stmt)->reject.type = NFT_REJECT_ICMP_UNREACH;
				(yyvsp[(0) - (4)].stmt)->reject.expr =
					symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
							  current_scope(state),
							  (yyvsp[(4) - (4)].string));
				(yyvsp[(0) - (4)].stmt)->reject.expr->dtype = &icmpv6_code_type;
			}
    break;

  case 196:

/* Line 1806 of yacc.c  */
#line 1377 "parser_bison.y"
    {
				(yyvsp[(0) - (4)].stmt)->reject.type = NFT_REJECT_ICMPX_UNREACH;
				(yyvsp[(0) - (4)].stmt)->reject.expr =
					symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
							  current_scope(state),
							  (yyvsp[(4) - (4)].string));
				(yyvsp[(0) - (4)].stmt)->reject.expr->dtype = &icmpx_code_type;
			}
    break;

  case 197:

/* Line 1806 of yacc.c  */
#line 1386 "parser_bison.y"
    {
				(yyvsp[(0) - (3)].stmt)->reject.type = NFT_REJECT_TCP_RST;
			}
    break;

  case 199:

/* Line 1806 of yacc.c  */
#line 1395 "parser_bison.y"
    {
				(yyval.stmt) = nat_stmt_alloc(&(yyloc));
				(yyval.stmt)->nat.type = NFT_NAT_SNAT;
			}
    break;

  case 200:

/* Line 1806 of yacc.c  */
#line 1400 "parser_bison.y"
    {
				(yyval.stmt) = nat_stmt_alloc(&(yyloc));
				(yyval.stmt)->nat.type = NFT_NAT_DNAT;
			}
    break;

  case 201:

/* Line 1806 of yacc.c  */
#line 1407 "parser_bison.y"
    {
				(yyvsp[(0) - (1)].stmt)->nat.addr = (yyvsp[(1) - (1)].expr);
			}
    break;

  case 202:

/* Line 1806 of yacc.c  */
#line 1411 "parser_bison.y"
    {
				(yyvsp[(0) - (3)].stmt)->nat.addr = (yyvsp[(1) - (3)].expr);
				(yyvsp[(0) - (3)].stmt)->nat.proto = (yyvsp[(3) - (3)].expr);
			}
    break;

  case 203:

/* Line 1806 of yacc.c  */
#line 1416 "parser_bison.y"
    {
				(yyvsp[(0) - (2)].stmt)->nat.proto = (yyvsp[(2) - (2)].expr);
			}
    break;

  case 204:

/* Line 1806 of yacc.c  */
#line 1420 "parser_bison.y"
    {
				(yyvsp[(0) - (2)].stmt)->nat.flags = (yyvsp[(2) - (2)].val);
			}
    break;

  case 206:

/* Line 1806 of yacc.c  */
#line 1427 "parser_bison.y"
    {
				(yyval.stmt) = (yyvsp[(1) - (2)].stmt);
				(yyval.stmt)->masq.flags = (yyvsp[(2) - (2)].val);
			}
    break;

  case 207:

/* Line 1806 of yacc.c  */
#line 1433 "parser_bison.y"
    { (yyval.stmt) = masq_stmt_alloc(&(yyloc)); }
    break;

  case 210:

/* Line 1806 of yacc.c  */
#line 1440 "parser_bison.y"
    { (yyval.stmt) = redir_stmt_alloc(&(yyloc)); }
    break;

  case 211:

/* Line 1806 of yacc.c  */
#line 1444 "parser_bison.y"
    {
				(yyvsp[(0) - (2)].stmt)->redir.proto = (yyvsp[(2) - (2)].expr);
			}
    break;

  case 212:

/* Line 1806 of yacc.c  */
#line 1448 "parser_bison.y"
    {
				(yyvsp[(0) - (1)].stmt)->redir.flags = (yyvsp[(1) - (1)].val);
			}
    break;

  case 213:

/* Line 1806 of yacc.c  */
#line 1452 "parser_bison.y"
    {
				(yyvsp[(0) - (3)].stmt)->redir.proto = (yyvsp[(2) - (3)].expr);
				(yyvsp[(0) - (3)].stmt)->redir.flags = (yyvsp[(3) - (3)].val);
			}
    break;

  case 215:

/* Line 1806 of yacc.c  */
#line 1460 "parser_bison.y"
    {
				(yyval.val) = (yyvsp[(1) - (3)].val) | (yyvsp[(3) - (3)].val);
			}
    break;

  case 216:

/* Line 1806 of yacc.c  */
#line 1465 "parser_bison.y"
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM; }
    break;

  case 217:

/* Line 1806 of yacc.c  */
#line 1466 "parser_bison.y"
    { (yyval.val) = NF_NAT_RANGE_PROTO_RANDOM_FULLY; }
    break;

  case 218:

/* Line 1806 of yacc.c  */
#line 1467 "parser_bison.y"
    { (yyval.val) = NF_NAT_RANGE_PERSISTENT; }
    break;

  case 221:

/* Line 1806 of yacc.c  */
#line 1475 "parser_bison.y"
    {
				(yyval.stmt) = queue_stmt_alloc(&(yyloc));
			}
    break;

  case 222:

/* Line 1806 of yacc.c  */
#line 1481 "parser_bison.y"
    {
				(yyval.stmt)	= (yyvsp[(0) - (1)].stmt);
			}
    break;

  case 224:

/* Line 1806 of yacc.c  */
#line 1488 "parser_bison.y"
    {
				(yyvsp[(0) - (2)].stmt)->queue.queue = (yyvsp[(2) - (2)].expr);
			}
    break;

  case 225:

/* Line 1806 of yacc.c  */
#line 1492 "parser_bison.y"
    {
				(yyvsp[(0) - (1)].stmt)->queue.flags |= (yyvsp[(1) - (1)].val);
			}
    break;

  case 227:

/* Line 1806 of yacc.c  */
#line 1499 "parser_bison.y"
    {
				(yyval.val) = (yyvsp[(1) - (3)].val) | (yyvsp[(3) - (3)].val);
			}
    break;

  case 228:

/* Line 1806 of yacc.c  */
#line 1504 "parser_bison.y"
    { (yyval.val) = NFT_QUEUE_FLAG_BYPASS; }
    break;

  case 229:

/* Line 1806 of yacc.c  */
#line 1505 "parser_bison.y"
    { (yyval.val) = NFT_QUEUE_FLAG_CPU_FANOUT; }
    break;

  case 230:

/* Line 1806 of yacc.c  */
#line 1509 "parser_bison.y"
    {
				(yyval.stmt) = expr_stmt_alloc(&(yyloc), (yyvsp[(1) - (1)].expr));
			}
    break;

  case 231:

/* Line 1806 of yacc.c  */
#line 1515 "parser_bison.y"
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       (yyvsp[(1) - (1)].string));
				xfree((yyvsp[(1) - (1)].string));
			}
    break;

  case 232:

/* Line 1806 of yacc.c  */
#line 1522 "parser_bison.y"
    {
				struct scope *scope = current_scope(state);

				if (symbol_lookup(scope, (yyvsp[(2) - (2)].string)) == NULL) {
					erec_queue(error(&(yylsp[(2) - (2)]), "unknown identifier '%s'", (yyvsp[(2) - (2)].string)),
						   state->msgs);
					YYERROR;
				}

				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_DEFINE,
						       scope, (yyvsp[(2) - (2)].string));
				xfree((yyvsp[(2) - (2)].string));
			}
    break;

  case 233:

/* Line 1806 of yacc.c  */
#line 1536 "parser_bison.y"
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_SET,
						       current_scope(state),
						       (yyvsp[(2) - (2)].string));
				xfree((yyvsp[(2) - (2)].string));
			}
    break;

  case 234:

/* Line 1806 of yacc.c  */
#line 1545 "parser_bison.y"
    {
				char str[64];

				snprintf(str, sizeof(str), "%" PRIu64, (yyvsp[(1) - (1)].val));
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       str);
			}
    break;

  case 235:

/* Line 1806 of yacc.c  */
#line 1555 "parser_bison.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 236:

/* Line 1806 of yacc.c  */
#line 1556 "parser_bison.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 237:

/* Line 1806 of yacc.c  */
#line 1557 "parser_bison.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 238:

/* Line 1806 of yacc.c  */
#line 1558 "parser_bison.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 239:

/* Line 1806 of yacc.c  */
#line 1559 "parser_bison.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 240:

/* Line 1806 of yacc.c  */
#line 1560 "parser_bison.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); }
    break;

  case 241:

/* Line 1806 of yacc.c  */
#line 1561 "parser_bison.y"
    { (yyval.expr) = (yyvsp[(2) - (3)].expr); }
    break;

  case 243:

/* Line 1806 of yacc.c  */
#line 1566 "parser_bison.y"
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_LSHIFT, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
			}
    break;

  case 244:

/* Line 1806 of yacc.c  */
#line 1570 "parser_bison.y"
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_RSHIFT, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
			}
    break;

  case 246:

/* Line 1806 of yacc.c  */
#line 1577 "parser_bison.y"
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_AND, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
			}
    break;

  case 248:

/* Line 1806 of yacc.c  */
#line 1584 "parser_bison.y"
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_XOR, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
			}
    break;

  case 250:

/* Line 1806 of yacc.c  */
#line 1591 "parser_bison.y"
    {
				(yyval.expr) = binop_expr_alloc(&(yyloc), OP_OR, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
			}
    break;

  case 253:

/* Line 1806 of yacc.c  */
#line 1601 "parser_bison.y"
    {
				if ((yyval.expr)->ops->type != EXPR_CONCAT) {
					(yyval.expr) = concat_expr_alloc(&(yyloc));
					compound_expr_add((yyval.expr), (yyvsp[(1) - (3)].expr));
				} else {
					struct location rhs[] = {
						[1]	= (yylsp[(2) - (3)]),
						[2]	= (yylsp[(3) - (3)]),
					};
					location_update(&(yyvsp[(3) - (3)].expr)->location, rhs, 2);

					(yyval.expr) = (yyvsp[(1) - (3)].expr);
					(yyval.expr)->location = (yyloc);
				}
				compound_expr_add((yyval.expr), (yyvsp[(3) - (3)].expr));
			}
    break;

  case 254:

/* Line 1806 of yacc.c  */
#line 1620 "parser_bison.y"
    {
				(yyval.expr) = list_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[(1) - (3)].expr));
				compound_expr_add((yyval.expr), (yyvsp[(3) - (3)].expr));
			}
    break;

  case 255:

/* Line 1806 of yacc.c  */
#line 1626 "parser_bison.y"
    {
				(yyvsp[(1) - (3)].expr)->location = (yyloc);
				compound_expr_add((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
				(yyval.expr) = (yyvsp[(1) - (3)].expr);
			}
    break;

  case 256:

/* Line 1806 of yacc.c  */
#line 1634 "parser_bison.y"
    {
				(yyval.expr) = prefix_expr_alloc(&(yyloc), (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].val));
			}
    break;

  case 257:

/* Line 1806 of yacc.c  */
#line 1640 "parser_bison.y"
    {
				(yyval.expr) = range_expr_alloc(&(yyloc), (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
			}
    break;

  case 258:

/* Line 1806 of yacc.c  */
#line 1646 "parser_bison.y"
    {
				struct expr *expr;

				expr = constant_expr_alloc(&(yyloc), &integer_type,
							   BYTEORDER_HOST_ENDIAN,
							   0, NULL);
				(yyval.expr) = prefix_expr_alloc(&(yyloc), expr, 0);
			}
    break;

  case 264:

/* Line 1806 of yacc.c  */
#line 1666 "parser_bison.y"
    {
				(yyval.expr) = map_expr_alloc(&(yyloc), (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
			}
    break;

  case 270:

/* Line 1806 of yacc.c  */
#line 1679 "parser_bison.y"
    {
				(yyval.expr) = NULL;
				erec_queue(error(&(yylsp[(1) - (1)]), "bad value '%s'", (yyvsp[(1) - (1)].string)),
					   state->msgs);
				YYERROR;
			}
    break;

  case 271:

/* Line 1806 of yacc.c  */
#line 1688 "parser_bison.y"
    {
				(yyvsp[(2) - (3)].expr)->location = (yyloc);
				(yyval.expr) = (yyvsp[(2) - (3)].expr);
			}
    break;

  case 272:

/* Line 1806 of yacc.c  */
#line 1695 "parser_bison.y"
    {
				(yyval.expr) = set_expr_alloc(&(yyloc));
				compound_expr_add((yyval.expr), (yyvsp[(1) - (1)].expr));
			}
    break;

  case 273:

/* Line 1806 of yacc.c  */
#line 1700 "parser_bison.y"
    {
				compound_expr_add((yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
				(yyval.expr) = (yyvsp[(1) - (3)].expr);
			}
    break;

  case 275:

/* Line 1806 of yacc.c  */
#line 1708 "parser_bison.y"
    {
				(yyval.expr) = (yyvsp[(2) - (3)].expr);
			}
    break;

  case 276:

/* Line 1806 of yacc.c  */
#line 1712 "parser_bison.y"
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[(2) - (5)].expr), (yyvsp[(4) - (5)].expr));
			}
    break;

  case 277:

/* Line 1806 of yacc.c  */
#line 1716 "parser_bison.y"
    {
				(yyval.expr) = mapping_expr_alloc(&(yyloc), (yyvsp[(2) - (5)].expr), (yyvsp[(4) - (5)].expr));
			}
    break;

  case 280:

/* Line 1806 of yacc.c  */
#line 1726 "parser_bison.y"
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_IMPLICIT, (yyvsp[(1) - (2)].expr), (yyvsp[(2) - (2)].expr));
			}
    break;

  case 281:

/* Line 1806 of yacc.c  */
#line 1730 "parser_bison.y"
    {
				(yyval.expr) = relational_expr_alloc(&(yyloc), OP_FLAGCMP, (yyvsp[(1) - (2)].expr), (yyvsp[(2) - (2)].expr));
			}
    break;

  case 282:

/* Line 1806 of yacc.c  */
#line 1734 "parser_bison.y"
    {
				(yyval.expr) = relational_expr_alloc(&(yylsp[(2) - (3)]), (yyvsp[(2) - (3)].val), (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr));
			}
    break;

  case 283:

/* Line 1806 of yacc.c  */
#line 1739 "parser_bison.y"
    { (yyval.val) = OP_EQ; }
    break;

  case 284:

/* Line 1806 of yacc.c  */
#line 1740 "parser_bison.y"
    { (yyval.val) = OP_NEQ; }
    break;

  case 285:

/* Line 1806 of yacc.c  */
#line 1741 "parser_bison.y"
    { (yyval.val) = OP_LT; }
    break;

  case 286:

/* Line 1806 of yacc.c  */
#line 1742 "parser_bison.y"
    { (yyval.val) = OP_GT; }
    break;

  case 287:

/* Line 1806 of yacc.c  */
#line 1743 "parser_bison.y"
    { (yyval.val) = OP_GTE; }
    break;

  case 288:

/* Line 1806 of yacc.c  */
#line 1744 "parser_bison.y"
    { (yyval.val) = OP_LTE; }
    break;

  case 289:

/* Line 1806 of yacc.c  */
#line 1748 "parser_bison.y"
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_ACCEPT, NULL);
			}
    break;

  case 290:

/* Line 1806 of yacc.c  */
#line 1752 "parser_bison.y"
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NF_DROP, NULL);
			}
    break;

  case 291:

/* Line 1806 of yacc.c  */
#line 1756 "parser_bison.y"
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_CONTINUE, NULL);
			}
    break;

  case 292:

/* Line 1806 of yacc.c  */
#line 1760 "parser_bison.y"
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_JUMP, (yyvsp[(2) - (2)].string));
			}
    break;

  case 293:

/* Line 1806 of yacc.c  */
#line 1764 "parser_bison.y"
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_GOTO, (yyvsp[(2) - (2)].string));
			}
    break;

  case 294:

/* Line 1806 of yacc.c  */
#line 1768 "parser_bison.y"
    {
				(yyval.expr) = verdict_expr_alloc(&(yyloc), NFT_RETURN, NULL);
			}
    break;

  case 295:

/* Line 1806 of yacc.c  */
#line 1774 "parser_bison.y"
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[(2) - (2)].val));
			}
    break;

  case 296:

/* Line 1806 of yacc.c  */
#line 1778 "parser_bison.y"
    {
				(yyval.expr) = meta_expr_alloc(&(yyloc), (yyvsp[(1) - (1)].val));
			}
    break;

  case 299:

/* Line 1806 of yacc.c  */
#line 1787 "parser_bison.y"
    { (yyval.val) = NFT_META_LEN; }
    break;

  case 300:

/* Line 1806 of yacc.c  */
#line 1788 "parser_bison.y"
    { (yyval.val) = NFT_META_NFPROTO; }
    break;

  case 301:

/* Line 1806 of yacc.c  */
#line 1789 "parser_bison.y"
    { (yyval.val) = NFT_META_L4PROTO; }
    break;

  case 302:

/* Line 1806 of yacc.c  */
#line 1790 "parser_bison.y"
    { (yyval.val) = NFT_META_PROTOCOL; }
    break;

  case 303:

/* Line 1806 of yacc.c  */
#line 1791 "parser_bison.y"
    { (yyval.val) = NFT_META_PRIORITY; }
    break;

  case 304:

/* Line 1806 of yacc.c  */
#line 1794 "parser_bison.y"
    { (yyval.val) = NFT_META_MARK; }
    break;

  case 305:

/* Line 1806 of yacc.c  */
#line 1795 "parser_bison.y"
    { (yyval.val) = NFT_META_IIF; }
    break;

  case 306:

/* Line 1806 of yacc.c  */
#line 1796 "parser_bison.y"
    { (yyval.val) = NFT_META_IIFNAME; }
    break;

  case 307:

/* Line 1806 of yacc.c  */
#line 1797 "parser_bison.y"
    { (yyval.val) = NFT_META_IIFTYPE; }
    break;

  case 308:

/* Line 1806 of yacc.c  */
#line 1798 "parser_bison.y"
    { (yyval.val) = NFT_META_OIF; }
    break;

  case 309:

/* Line 1806 of yacc.c  */
#line 1799 "parser_bison.y"
    { (yyval.val) = NFT_META_OIFNAME; }
    break;

  case 310:

/* Line 1806 of yacc.c  */
#line 1800 "parser_bison.y"
    { (yyval.val) = NFT_META_OIFTYPE; }
    break;

  case 311:

/* Line 1806 of yacc.c  */
#line 1801 "parser_bison.y"
    { (yyval.val) = NFT_META_SKUID; }
    break;

  case 312:

/* Line 1806 of yacc.c  */
#line 1802 "parser_bison.y"
    { (yyval.val) = NFT_META_SKGID; }
    break;

  case 313:

/* Line 1806 of yacc.c  */
#line 1803 "parser_bison.y"
    { (yyval.val) = NFT_META_NFTRACE; }
    break;

  case 314:

/* Line 1806 of yacc.c  */
#line 1804 "parser_bison.y"
    { (yyval.val) = NFT_META_RTCLASSID; }
    break;

  case 315:

/* Line 1806 of yacc.c  */
#line 1805 "parser_bison.y"
    { (yyval.val) = NFT_META_BRI_IIFNAME; }
    break;

  case 316:

/* Line 1806 of yacc.c  */
#line 1806 "parser_bison.y"
    { (yyval.val) = NFT_META_BRI_OIFNAME; }
    break;

  case 317:

/* Line 1806 of yacc.c  */
#line 1807 "parser_bison.y"
    { (yyval.val) = NFT_META_PKTTYPE; }
    break;

  case 318:

/* Line 1806 of yacc.c  */
#line 1808 "parser_bison.y"
    { (yyval.val) = NFT_META_CPU; }
    break;

  case 319:

/* Line 1806 of yacc.c  */
#line 1809 "parser_bison.y"
    { (yyval.val) = NFT_META_IIFGROUP; }
    break;

  case 320:

/* Line 1806 of yacc.c  */
#line 1810 "parser_bison.y"
    { (yyval.val) = NFT_META_OIFGROUP; }
    break;

  case 321:

/* Line 1806 of yacc.c  */
#line 1811 "parser_bison.y"
    { (yyval.val) = NFT_META_CGROUP; }
    break;

  case 322:

/* Line 1806 of yacc.c  */
#line 1815 "parser_bison.y"
    {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[(2) - (4)].val), (yyvsp[(4) - (4)].expr));
			}
    break;

  case 323:

/* Line 1806 of yacc.c  */
#line 1819 "parser_bison.y"
    {
				(yyval.stmt) = meta_stmt_alloc(&(yyloc), (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].expr));
			}
    break;

  case 324:

/* Line 1806 of yacc.c  */
#line 1825 "parser_bison.y"
    {
				(yyval.expr) = ct_expr_alloc(&(yyloc), (yyvsp[(2) - (2)].val));
			}
    break;

  case 325:

/* Line 1806 of yacc.c  */
#line 1830 "parser_bison.y"
    { (yyval.val) = NFT_CT_STATE; }
    break;

  case 326:

/* Line 1806 of yacc.c  */
#line 1831 "parser_bison.y"
    { (yyval.val) = NFT_CT_DIRECTION; }
    break;

  case 327:

/* Line 1806 of yacc.c  */
#line 1832 "parser_bison.y"
    { (yyval.val) = NFT_CT_STATUS; }
    break;

  case 328:

/* Line 1806 of yacc.c  */
#line 1833 "parser_bison.y"
    { (yyval.val) = NFT_CT_MARK; }
    break;

  case 329:

/* Line 1806 of yacc.c  */
#line 1834 "parser_bison.y"
    { (yyval.val) = NFT_CT_EXPIRATION; }
    break;

  case 330:

/* Line 1806 of yacc.c  */
#line 1835 "parser_bison.y"
    { (yyval.val) = NFT_CT_HELPER; }
    break;

  case 331:

/* Line 1806 of yacc.c  */
#line 1836 "parser_bison.y"
    { (yyval.val) = NFT_CT_L3PROTOCOL; }
    break;

  case 332:

/* Line 1806 of yacc.c  */
#line 1837 "parser_bison.y"
    { (yyval.val) = NFT_CT_SRC; }
    break;

  case 333:

/* Line 1806 of yacc.c  */
#line 1838 "parser_bison.y"
    { (yyval.val) = NFT_CT_DST; }
    break;

  case 334:

/* Line 1806 of yacc.c  */
#line 1839 "parser_bison.y"
    { (yyval.val) = NFT_CT_PROTOCOL; }
    break;

  case 335:

/* Line 1806 of yacc.c  */
#line 1840 "parser_bison.y"
    { (yyval.val) = NFT_CT_PROTO_SRC; }
    break;

  case 336:

/* Line 1806 of yacc.c  */
#line 1841 "parser_bison.y"
    { (yyval.val) = NFT_CT_PROTO_DST; }
    break;

  case 337:

/* Line 1806 of yacc.c  */
#line 1842 "parser_bison.y"
    { (yyval.val) = NFT_CT_LABELS; }
    break;

  case 338:

/* Line 1806 of yacc.c  */
#line 1846 "parser_bison.y"
    {
				(yyval.stmt) = ct_stmt_alloc(&(yyloc), (yyvsp[(2) - (4)].val), (yyvsp[(4) - (4)].expr));
			}
    break;

  case 355:

/* Line 1806 of yacc.c  */
#line 1870 "parser_bison.y"
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), NULL, 0);
				(yyval.expr)->payload.base	= (yyvsp[(2) - (6)].val);
				(yyval.expr)->payload.offset	= (yyvsp[(4) - (6)].val);
				(yyval.expr)->len			= (yyvsp[(6) - (6)].val);
				(yyval.expr)->dtype		= &integer_type;
			}
    break;

  case 356:

/* Line 1806 of yacc.c  */
#line 1879 "parser_bison.y"
    { (yyval.val) = PROTO_BASE_LL_HDR; }
    break;

  case 357:

/* Line 1806 of yacc.c  */
#line 1880 "parser_bison.y"
    { (yyval.val) = PROTO_BASE_NETWORK_HDR; }
    break;

  case 358:

/* Line 1806 of yacc.c  */
#line 1881 "parser_bison.y"
    { (yyval.val) = PROTO_BASE_TRANSPORT_HDR; }
    break;

  case 359:

/* Line 1806 of yacc.c  */
#line 1885 "parser_bison.y"
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_eth, (yyvsp[(2) - (2)].val));
			}
    break;

  case 360:

/* Line 1806 of yacc.c  */
#line 1889 "parser_bison.y"
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       "ether");
			}
    break;

  case 361:

/* Line 1806 of yacc.c  */
#line 1896 "parser_bison.y"
    { (yyval.val) = ETHHDR_SADDR; }
    break;

  case 362:

/* Line 1806 of yacc.c  */
#line 1897 "parser_bison.y"
    { (yyval.val) = ETHHDR_DADDR; }
    break;

  case 363:

/* Line 1806 of yacc.c  */
#line 1898 "parser_bison.y"
    { (yyval.val) = ETHHDR_TYPE; }
    break;

  case 364:

/* Line 1806 of yacc.c  */
#line 1902 "parser_bison.y"
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_vlan, (yyvsp[(2) - (2)].val));
			}
    break;

  case 365:

/* Line 1806 of yacc.c  */
#line 1906 "parser_bison.y"
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       "vlan");
			}
    break;

  case 366:

/* Line 1806 of yacc.c  */
#line 1913 "parser_bison.y"
    { (yyval.val) = VLANHDR_VID; }
    break;

  case 367:

/* Line 1806 of yacc.c  */
#line 1914 "parser_bison.y"
    { (yyval.val) = VLANHDR_CFI; }
    break;

  case 368:

/* Line 1806 of yacc.c  */
#line 1915 "parser_bison.y"
    { (yyval.val) = VLANHDR_PCP; }
    break;

  case 369:

/* Line 1806 of yacc.c  */
#line 1916 "parser_bison.y"
    { (yyval.val) = VLANHDR_TYPE; }
    break;

  case 370:

/* Line 1806 of yacc.c  */
#line 1920 "parser_bison.y"
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_arp, (yyvsp[(2) - (2)].val));
			}
    break;

  case 371:

/* Line 1806 of yacc.c  */
#line 1924 "parser_bison.y"
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       "arp");
			}
    break;

  case 372:

/* Line 1806 of yacc.c  */
#line 1931 "parser_bison.y"
    { (yyval.val) = ARPHDR_HRD; }
    break;

  case 373:

/* Line 1806 of yacc.c  */
#line 1932 "parser_bison.y"
    { (yyval.val) = ARPHDR_PRO; }
    break;

  case 374:

/* Line 1806 of yacc.c  */
#line 1933 "parser_bison.y"
    { (yyval.val) = ARPHDR_HLN; }
    break;

  case 375:

/* Line 1806 of yacc.c  */
#line 1934 "parser_bison.y"
    { (yyval.val) = ARPHDR_PLN; }
    break;

  case 376:

/* Line 1806 of yacc.c  */
#line 1935 "parser_bison.y"
    { (yyval.val) = ARPHDR_OP; }
    break;

  case 377:

/* Line 1806 of yacc.c  */
#line 1939 "parser_bison.y"
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip, (yyvsp[(2) - (2)].val));
			}
    break;

  case 378:

/* Line 1806 of yacc.c  */
#line 1943 "parser_bison.y"
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       "ip");
			}
    break;

  case 379:

/* Line 1806 of yacc.c  */
#line 1950 "parser_bison.y"
    { (yyval.val) = IPHDR_VERSION; }
    break;

  case 380:

/* Line 1806 of yacc.c  */
#line 1951 "parser_bison.y"
    { (yyval.val) = IPHDR_HDRLENGTH; }
    break;

  case 381:

/* Line 1806 of yacc.c  */
#line 1952 "parser_bison.y"
    { (yyval.val) = IPHDR_TOS; }
    break;

  case 382:

/* Line 1806 of yacc.c  */
#line 1953 "parser_bison.y"
    { (yyval.val) = IPHDR_LENGTH; }
    break;

  case 383:

/* Line 1806 of yacc.c  */
#line 1954 "parser_bison.y"
    { (yyval.val) = IPHDR_ID; }
    break;

  case 384:

/* Line 1806 of yacc.c  */
#line 1955 "parser_bison.y"
    { (yyval.val) = IPHDR_FRAG_OFF; }
    break;

  case 385:

/* Line 1806 of yacc.c  */
#line 1956 "parser_bison.y"
    { (yyval.val) = IPHDR_TTL; }
    break;

  case 386:

/* Line 1806 of yacc.c  */
#line 1957 "parser_bison.y"
    { (yyval.val) = IPHDR_PROTOCOL; }
    break;

  case 387:

/* Line 1806 of yacc.c  */
#line 1958 "parser_bison.y"
    { (yyval.val) = IPHDR_CHECKSUM; }
    break;

  case 388:

/* Line 1806 of yacc.c  */
#line 1959 "parser_bison.y"
    { (yyval.val) = IPHDR_SADDR; }
    break;

  case 389:

/* Line 1806 of yacc.c  */
#line 1960 "parser_bison.y"
    { (yyval.val) = IPHDR_DADDR; }
    break;

  case 390:

/* Line 1806 of yacc.c  */
#line 1964 "parser_bison.y"
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp, (yyvsp[(2) - (2)].val));
			}
    break;

  case 391:

/* Line 1806 of yacc.c  */
#line 1968 "parser_bison.y"
    {
				uint8_t data = IPPROTO_ICMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
    break;

  case 392:

/* Line 1806 of yacc.c  */
#line 1976 "parser_bison.y"
    { (yyval.val) = ICMPHDR_TYPE; }
    break;

  case 393:

/* Line 1806 of yacc.c  */
#line 1977 "parser_bison.y"
    { (yyval.val) = ICMPHDR_CODE; }
    break;

  case 394:

/* Line 1806 of yacc.c  */
#line 1978 "parser_bison.y"
    { (yyval.val) = ICMPHDR_CHECKSUM; }
    break;

  case 395:

/* Line 1806 of yacc.c  */
#line 1979 "parser_bison.y"
    { (yyval.val) = ICMPHDR_ID; }
    break;

  case 396:

/* Line 1806 of yacc.c  */
#line 1980 "parser_bison.y"
    { (yyval.val) = ICMPHDR_SEQ; }
    break;

  case 397:

/* Line 1806 of yacc.c  */
#line 1981 "parser_bison.y"
    { (yyval.val) = ICMPHDR_GATEWAY; }
    break;

  case 398:

/* Line 1806 of yacc.c  */
#line 1982 "parser_bison.y"
    { (yyval.val) = ICMPHDR_MTU; }
    break;

  case 399:

/* Line 1806 of yacc.c  */
#line 1986 "parser_bison.y"
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ip6, (yyvsp[(2) - (2)].val));
			}
    break;

  case 400:

/* Line 1806 of yacc.c  */
#line 1990 "parser_bison.y"
    {
				(yyval.expr) = symbol_expr_alloc(&(yyloc), SYMBOL_VALUE,
						       current_scope(state),
						       "ip6");
			}
    break;

  case 401:

/* Line 1806 of yacc.c  */
#line 1997 "parser_bison.y"
    { (yyval.val) = IP6HDR_VERSION; }
    break;

  case 402:

/* Line 1806 of yacc.c  */
#line 1998 "parser_bison.y"
    { (yyval.val) = IP6HDR_PRIORITY; }
    break;

  case 403:

/* Line 1806 of yacc.c  */
#line 1999 "parser_bison.y"
    { (yyval.val) = IP6HDR_FLOWLABEL; }
    break;

  case 404:

/* Line 1806 of yacc.c  */
#line 2000 "parser_bison.y"
    { (yyval.val) = IP6HDR_LENGTH; }
    break;

  case 405:

/* Line 1806 of yacc.c  */
#line 2001 "parser_bison.y"
    { (yyval.val) = IP6HDR_NEXTHDR; }
    break;

  case 406:

/* Line 1806 of yacc.c  */
#line 2002 "parser_bison.y"
    { (yyval.val) = IP6HDR_HOPLIMIT; }
    break;

  case 407:

/* Line 1806 of yacc.c  */
#line 2003 "parser_bison.y"
    { (yyval.val) = IP6HDR_SADDR; }
    break;

  case 408:

/* Line 1806 of yacc.c  */
#line 2004 "parser_bison.y"
    { (yyval.val) = IP6HDR_DADDR; }
    break;

  case 409:

/* Line 1806 of yacc.c  */
#line 2007 "parser_bison.y"
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_icmp6, (yyvsp[(2) - (2)].val));
			}
    break;

  case 410:

/* Line 1806 of yacc.c  */
#line 2011 "parser_bison.y"
    {
				uint8_t data = IPPROTO_ICMPV6;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
    break;

  case 411:

/* Line 1806 of yacc.c  */
#line 2019 "parser_bison.y"
    { (yyval.val) = ICMP6HDR_TYPE; }
    break;

  case 412:

/* Line 1806 of yacc.c  */
#line 2020 "parser_bison.y"
    { (yyval.val) = ICMP6HDR_CODE; }
    break;

  case 413:

/* Line 1806 of yacc.c  */
#line 2021 "parser_bison.y"
    { (yyval.val) = ICMP6HDR_CHECKSUM; }
    break;

  case 414:

/* Line 1806 of yacc.c  */
#line 2022 "parser_bison.y"
    { (yyval.val) = ICMP6HDR_PPTR; }
    break;

  case 415:

/* Line 1806 of yacc.c  */
#line 2023 "parser_bison.y"
    { (yyval.val) = ICMP6HDR_MTU; }
    break;

  case 416:

/* Line 1806 of yacc.c  */
#line 2024 "parser_bison.y"
    { (yyval.val) = ICMP6HDR_ID; }
    break;

  case 417:

/* Line 1806 of yacc.c  */
#line 2025 "parser_bison.y"
    { (yyval.val) = ICMP6HDR_SEQ; }
    break;

  case 418:

/* Line 1806 of yacc.c  */
#line 2026 "parser_bison.y"
    { (yyval.val) = ICMP6HDR_MAXDELAY; }
    break;

  case 419:

/* Line 1806 of yacc.c  */
#line 2030 "parser_bison.y"
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_ah, (yyvsp[(2) - (2)].val));
			}
    break;

  case 420:

/* Line 1806 of yacc.c  */
#line 2034 "parser_bison.y"
    {
				uint8_t data = IPPROTO_AH;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
    break;

  case 421:

/* Line 1806 of yacc.c  */
#line 2042 "parser_bison.y"
    { (yyval.val) = AHHDR_NEXTHDR; }
    break;

  case 422:

/* Line 1806 of yacc.c  */
#line 2043 "parser_bison.y"
    { (yyval.val) = AHHDR_HDRLENGTH; }
    break;

  case 423:

/* Line 1806 of yacc.c  */
#line 2044 "parser_bison.y"
    { (yyval.val) = AHHDR_RESERVED; }
    break;

  case 424:

/* Line 1806 of yacc.c  */
#line 2045 "parser_bison.y"
    { (yyval.val) = AHHDR_SPI; }
    break;

  case 425:

/* Line 1806 of yacc.c  */
#line 2046 "parser_bison.y"
    { (yyval.val) = AHHDR_SEQUENCE; }
    break;

  case 426:

/* Line 1806 of yacc.c  */
#line 2050 "parser_bison.y"
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_esp, (yyvsp[(2) - (2)].val));
			}
    break;

  case 427:

/* Line 1806 of yacc.c  */
#line 2054 "parser_bison.y"
    {
				uint8_t data = IPPROTO_ESP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
    break;

  case 428:

/* Line 1806 of yacc.c  */
#line 2062 "parser_bison.y"
    { (yyval.val) = ESPHDR_SPI; }
    break;

  case 429:

/* Line 1806 of yacc.c  */
#line 2063 "parser_bison.y"
    { (yyval.val) = ESPHDR_SEQUENCE; }
    break;

  case 430:

/* Line 1806 of yacc.c  */
#line 2067 "parser_bison.y"
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_comp, (yyvsp[(2) - (2)].val));
			}
    break;

  case 431:

/* Line 1806 of yacc.c  */
#line 2071 "parser_bison.y"
    {
				uint8_t data = IPPROTO_COMP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
    break;

  case 432:

/* Line 1806 of yacc.c  */
#line 2079 "parser_bison.y"
    { (yyval.val) = COMPHDR_NEXTHDR; }
    break;

  case 433:

/* Line 1806 of yacc.c  */
#line 2080 "parser_bison.y"
    { (yyval.val) = COMPHDR_FLAGS; }
    break;

  case 434:

/* Line 1806 of yacc.c  */
#line 2081 "parser_bison.y"
    { (yyval.val) = COMPHDR_CPI; }
    break;

  case 435:

/* Line 1806 of yacc.c  */
#line 2085 "parser_bison.y"
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udp, (yyvsp[(2) - (2)].val));
			}
    break;

  case 436:

/* Line 1806 of yacc.c  */
#line 2089 "parser_bison.y"
    {
				uint8_t data = IPPROTO_UDP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
    break;

  case 437:

/* Line 1806 of yacc.c  */
#line 2097 "parser_bison.y"
    { (yyval.val) = UDPHDR_SPORT; }
    break;

  case 438:

/* Line 1806 of yacc.c  */
#line 2098 "parser_bison.y"
    { (yyval.val) = UDPHDR_DPORT; }
    break;

  case 439:

/* Line 1806 of yacc.c  */
#line 2099 "parser_bison.y"
    { (yyval.val) = UDPHDR_LENGTH; }
    break;

  case 440:

/* Line 1806 of yacc.c  */
#line 2100 "parser_bison.y"
    { (yyval.val) = UDPHDR_CHECKSUM; }
    break;

  case 441:

/* Line 1806 of yacc.c  */
#line 2104 "parser_bison.y"
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_udplite, (yyvsp[(2) - (2)].val));
			}
    break;

  case 442:

/* Line 1806 of yacc.c  */
#line 2108 "parser_bison.y"
    {
				uint8_t data = IPPROTO_UDPLITE;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
    break;

  case 443:

/* Line 1806 of yacc.c  */
#line 2116 "parser_bison.y"
    { (yyval.val) = UDPHDR_SPORT; }
    break;

  case 444:

/* Line 1806 of yacc.c  */
#line 2117 "parser_bison.y"
    { (yyval.val) = UDPHDR_DPORT; }
    break;

  case 445:

/* Line 1806 of yacc.c  */
#line 2118 "parser_bison.y"
    { (yyval.val) = UDPHDR_LENGTH; }
    break;

  case 446:

/* Line 1806 of yacc.c  */
#line 2119 "parser_bison.y"
    { (yyval.val) = UDPHDR_CHECKSUM; }
    break;

  case 447:

/* Line 1806 of yacc.c  */
#line 2123 "parser_bison.y"
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_tcp, (yyvsp[(2) - (2)].val));
			}
    break;

  case 448:

/* Line 1806 of yacc.c  */
#line 2127 "parser_bison.y"
    {
				uint8_t data = IPPROTO_TCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
    break;

  case 449:

/* Line 1806 of yacc.c  */
#line 2135 "parser_bison.y"
    { (yyval.val) = TCPHDR_SPORT; }
    break;

  case 450:

/* Line 1806 of yacc.c  */
#line 2136 "parser_bison.y"
    { (yyval.val) = TCPHDR_DPORT; }
    break;

  case 451:

/* Line 1806 of yacc.c  */
#line 2137 "parser_bison.y"
    { (yyval.val) = TCPHDR_SEQ; }
    break;

  case 452:

/* Line 1806 of yacc.c  */
#line 2138 "parser_bison.y"
    { (yyval.val) = TCPHDR_ACKSEQ; }
    break;

  case 453:

/* Line 1806 of yacc.c  */
#line 2139 "parser_bison.y"
    { (yyval.val) = TCPHDR_DOFF; }
    break;

  case 454:

/* Line 1806 of yacc.c  */
#line 2140 "parser_bison.y"
    { (yyval.val) = TCPHDR_RESERVED; }
    break;

  case 455:

/* Line 1806 of yacc.c  */
#line 2141 "parser_bison.y"
    { (yyval.val) = TCPHDR_FLAGS; }
    break;

  case 456:

/* Line 1806 of yacc.c  */
#line 2142 "parser_bison.y"
    { (yyval.val) = TCPHDR_WINDOW; }
    break;

  case 457:

/* Line 1806 of yacc.c  */
#line 2143 "parser_bison.y"
    { (yyval.val) = TCPHDR_CHECKSUM; }
    break;

  case 458:

/* Line 1806 of yacc.c  */
#line 2144 "parser_bison.y"
    { (yyval.val) = TCPHDR_URGPTR; }
    break;

  case 459:

/* Line 1806 of yacc.c  */
#line 2148 "parser_bison.y"
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_dccp, (yyvsp[(2) - (2)].val));
			}
    break;

  case 460:

/* Line 1806 of yacc.c  */
#line 2152 "parser_bison.y"
    {
				uint8_t data = IPPROTO_DCCP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
    break;

  case 461:

/* Line 1806 of yacc.c  */
#line 2160 "parser_bison.y"
    { (yyval.val) = DCCPHDR_SPORT; }
    break;

  case 462:

/* Line 1806 of yacc.c  */
#line 2161 "parser_bison.y"
    { (yyval.val) = DCCPHDR_DPORT; }
    break;

  case 463:

/* Line 1806 of yacc.c  */
#line 2162 "parser_bison.y"
    { (yyval.val) = DCCPHDR_TYPE; }
    break;

  case 464:

/* Line 1806 of yacc.c  */
#line 2166 "parser_bison.y"
    {
				(yyval.expr) = payload_expr_alloc(&(yyloc), &proto_sctp, (yyvsp[(2) - (2)].val));
			}
    break;

  case 465:

/* Line 1806 of yacc.c  */
#line 2170 "parser_bison.y"
    {
				uint8_t data = IPPROTO_SCTP;
				(yyval.expr) = constant_expr_alloc(&(yyloc), &inet_protocol_type,
							 BYTEORDER_HOST_ENDIAN,
							 sizeof(data) * BITS_PER_BYTE, &data);
			}
    break;

  case 466:

/* Line 1806 of yacc.c  */
#line 2178 "parser_bison.y"
    { (yyval.val) = SCTPHDR_SPORT; }
    break;

  case 467:

/* Line 1806 of yacc.c  */
#line 2179 "parser_bison.y"
    { (yyval.val) = SCTPHDR_DPORT; }
    break;

  case 468:

/* Line 1806 of yacc.c  */
#line 2180 "parser_bison.y"
    { (yyval.val) = SCTPHDR_VTAG; }
    break;

  case 469:

/* Line 1806 of yacc.c  */
#line 2181 "parser_bison.y"
    { (yyval.val) = SCTPHDR_CHECKSUM; }
    break;

  case 477:

/* Line 1806 of yacc.c  */
#line 2194 "parser_bison.y"
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_hbh, (yyvsp[(2) - (2)].val));
			}
    break;

  case 478:

/* Line 1806 of yacc.c  */
#line 2199 "parser_bison.y"
    { (yyval.val) = HBHHDR_NEXTHDR; }
    break;

  case 479:

/* Line 1806 of yacc.c  */
#line 2200 "parser_bison.y"
    { (yyval.val) = HBHHDR_HDRLENGTH; }
    break;

  case 480:

/* Line 1806 of yacc.c  */
#line 2204 "parser_bison.y"
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt, (yyvsp[(2) - (2)].val));
			}
    break;

  case 481:

/* Line 1806 of yacc.c  */
#line 2209 "parser_bison.y"
    { (yyval.val) = RTHDR_NEXTHDR; }
    break;

  case 482:

/* Line 1806 of yacc.c  */
#line 2210 "parser_bison.y"
    { (yyval.val) = RTHDR_HDRLENGTH; }
    break;

  case 483:

/* Line 1806 of yacc.c  */
#line 2211 "parser_bison.y"
    { (yyval.val) = RTHDR_TYPE; }
    break;

  case 484:

/* Line 1806 of yacc.c  */
#line 2212 "parser_bison.y"
    { (yyval.val) = RTHDR_SEG_LEFT; }
    break;

  case 485:

/* Line 1806 of yacc.c  */
#line 2216 "parser_bison.y"
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt0, (yyvsp[(2) - (2)].val));
			}
    break;

  case 486:

/* Line 1806 of yacc.c  */
#line 2222 "parser_bison.y"
    {
				(yyval.val) = RT0HDR_ADDR_1 + (yyvsp[(3) - (4)].val) - 1;
			}
    break;

  case 487:

/* Line 1806 of yacc.c  */
#line 2228 "parser_bison.y"
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_rt2, (yyvsp[(2) - (2)].val));
			}
    break;

  case 488:

/* Line 1806 of yacc.c  */
#line 2233 "parser_bison.y"
    { (yyval.val) = RT2HDR_ADDR; }
    break;

  case 489:

/* Line 1806 of yacc.c  */
#line 2237 "parser_bison.y"
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_frag, (yyvsp[(2) - (2)].val));
			}
    break;

  case 490:

/* Line 1806 of yacc.c  */
#line 2242 "parser_bison.y"
    { (yyval.val) = FRAGHDR_NEXTHDR; }
    break;

  case 491:

/* Line 1806 of yacc.c  */
#line 2243 "parser_bison.y"
    { (yyval.val) = FRAGHDR_RESERVED; }
    break;

  case 492:

/* Line 1806 of yacc.c  */
#line 2244 "parser_bison.y"
    { (yyval.val) = FRAGHDR_FRAG_OFF; }
    break;

  case 493:

/* Line 1806 of yacc.c  */
#line 2245 "parser_bison.y"
    { (yyval.val) = FRAGHDR_RESERVED2; }
    break;

  case 494:

/* Line 1806 of yacc.c  */
#line 2246 "parser_bison.y"
    { (yyval.val) = FRAGHDR_MFRAGS; }
    break;

  case 495:

/* Line 1806 of yacc.c  */
#line 2247 "parser_bison.y"
    { (yyval.val) = FRAGHDR_ID; }
    break;

  case 496:

/* Line 1806 of yacc.c  */
#line 2251 "parser_bison.y"
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_dst, (yyvsp[(2) - (2)].val));
			}
    break;

  case 497:

/* Line 1806 of yacc.c  */
#line 2256 "parser_bison.y"
    { (yyval.val) = DSTHDR_NEXTHDR; }
    break;

  case 498:

/* Line 1806 of yacc.c  */
#line 2257 "parser_bison.y"
    { (yyval.val) = DSTHDR_HDRLENGTH; }
    break;

  case 499:

/* Line 1806 of yacc.c  */
#line 2261 "parser_bison.y"
    {
				(yyval.expr) = exthdr_expr_alloc(&(yyloc), &exthdr_mh, (yyvsp[(2) - (2)].val));
			}
    break;

  case 500:

/* Line 1806 of yacc.c  */
#line 2266 "parser_bison.y"
    { (yyval.val) = MHHDR_NEXTHDR; }
    break;

  case 501:

/* Line 1806 of yacc.c  */
#line 2267 "parser_bison.y"
    { (yyval.val) = MHHDR_HDRLENGTH; }
    break;

  case 502:

/* Line 1806 of yacc.c  */
#line 2268 "parser_bison.y"
    { (yyval.val) = MHHDR_TYPE; }
    break;

  case 503:

/* Line 1806 of yacc.c  */
#line 2269 "parser_bison.y"
    { (yyval.val) = MHHDR_RESERVED; }
    break;

  case 504:

/* Line 1806 of yacc.c  */
#line 2270 "parser_bison.y"
    { (yyval.val) = MHHDR_CHECKSUM; }
    break;



/* Line 1806 of yacc.c  */
#line 7605 "parser_bison.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, scanner, state, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (&yylloc, scanner, state, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc, scanner, state);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp, scanner, state);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, scanner, state, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, scanner, state);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp, scanner, state);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 2273 "parser_bison.y"


