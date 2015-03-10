/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
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

/* Line 2068 of yacc.c  */
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



/* Line 2068 of yacc.c  */
#line 501 "parser_bison.h"
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



