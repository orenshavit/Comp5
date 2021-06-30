/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.ypp"

	#include <iostream>
	#include "output.hpp"
	#include "SymbolsTable.hpp"
	#include "ManageIR.hpp"
	#include "bp.hpp"
	#include <stdlib.h>
	#include <assert.h>
	#include <bits/stdc++.h>
	using namespace std;
	
	#define P(s) cout << s << endl
	#define MISMATCH {output::errorMismatch(yylineno); exit(0);}
	#define NOT_NUMERIC(x) ((x) != "INT" && (x) != "BYTE") 
	#define HANDLE_BINOP(first, second, lval, op) check_numeric(first, second);\
	 										lval = new Node();\
	 										lval->type = get_type_of_binop(first->type, second->type);\
	  										ir.binop(op, first, second, lval);

	extern int yylex();
	extern int yylineno;
	extern char* yytext;

	void yyerror(const char*);
	void new_var(const string& id, const string& ltype, Node* pNode, const string& rtype);
	void new_formal(const string& id, int offset, const string& type);
	void new_table();
	void new_func(const string& id, const string& retType, vector<string>& argTypes);
	void remove_table();
	void end_of_scope_operations();
	string check_var_return_type(const string& id);
	string check_func_return_type(const string& id);
	void check_numeric(Node* x, Node* y);
	string get_type_of_binop(string x, string y);
	TableEntry* get_entry(const string& id);
	int get_offset(const string& id);

	stack<SymbolsTable*> tables_stack;
	stack<int> offset_stack;

	FunctionDecl current_func;
	stack<string> called_arg_types;
	stack<Node*> called_exps;

	unordered_map<string, TableEntry*> hash_ids;
	unordered_map<string, FuncTypes> hash_funcs;
	stack<bool> in_while;
	stack<bool> in_switch;

	CodeBuffer& cbr = CodeBuffer::instance();
	ManageIR ir;

	vector<pair<int,BranchLabelIndex>> while_list = {};
	vector<pair<int,BranchLabelIndex>> global_next_list = {};

	stack<vector<pair<int,BranchLabelIndex>>> cont_lists_stack = {};
	stack<vector<pair<int,BranchLabelIndex>>> brk_lists_stack = {};



#line 131 "parser.tab.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSER_TAB_HPP_INCLUDED
# define YY_YY_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    VOID = 258,
    INT = 259,
    BYTE = 260,
    B = 261,
    BOOL = 262,
    OR = 263,
    AND = 264,
    RETURN = 265,
    WHILE = 266,
    BREAK = 267,
    CONTINUE = 268,
    SWITCH = 269,
    CASE = 270,
    DEFAULT = 271,
    SC = 272,
    COMMA = 273,
    COLON = 274,
    ASSIGN = 275,
    ID = 276,
    STRING = 277,
    ILLEGAL = 278,
    LPAREN = 279,
    RPAREN = 280,
    LBRACE = 281,
    RBRACE = 282,
    IF = 283,
    ELSE = 284,
    TRUE = 285,
    FALSE = 286,
    NUM = 287,
    EQUALITY = 288,
    RELATION = 289,
    NOT = 290,
    ADD = 291,
    SUB = 292,
    MUL = 293,
    DIV = 294
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_HPP_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   214

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  64
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  133

#define YYUNDEFTOK  2
#define YYMAXUTOK   294


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    96,    96,    99,   107,   111,   118,   119,   122,   123,
     125,   126,   128,   129,   131,   139,   143,   149,   154,   160,
     173,   185,   187,   190,   200,   206,   213,   223,   231,   238,
     246,   248,   252,   258,   262,   265,   268,   269,   281,   295,
     301,   308,   312,   316,   322,   335,   336,   337,   338,   339,
     347,   353,   360,   370,   375,   388,   401,   409,   414,   421,
     428,   437,   448,   452,   457
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "VOID", "INT", "BYTE", "B", "BOOL", "OR",
  "AND", "RETURN", "WHILE", "BREAK", "CONTINUE", "SWITCH", "CASE",
  "DEFAULT", "SC", "COMMA", "COLON", "ASSIGN", "ID", "STRING", "ILLEGAL",
  "LPAREN", "RPAREN", "LBRACE", "RBRACE", "IF", "ELSE", "TRUE", "FALSE",
  "NUM", "EQUALITY", "RELATION", "NOT", "ADD", "SUB", "MUL", "DIV",
  "$accept", "Program", "FuncDecl", "MarkerID", "MarkerLBRACE", "Funcs",
  "RetType", "Formals", "FormalsList", "FormalDecl", "Statements",
  "Statement", "M", "N", "MarkerWhile", "MarkerSwitch", "MarkerNumericExp",
  "MarkerBoolExp", "MarkerELSE", "Call", "ExpList", "Type", "Exp",
  "CaseDecl", "CaseList", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294
};
# endif

#define YYPACT_NINF (-90)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-65)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      69,   -90,   -90,   -90,   -90,     2,    69,   -90,   -14,   -90,
     -90,   -90,   -90,   -12,    16,   -11,   -90,    12,    28,    10,
      16,   -90,   -90,   176,   -90,    35,   -90,    34,    41,   -90,
      -7,   176,    37,    51,   -90,    62,    60,   -90,    63,   -90,
      64,   -90,   -90,    84,    64,   -90,    75,    82,   -90,   -90,
      86,    64,    96,    66,    64,   -90,   176,   -90,    11,     1,
     -90,   132,   -90,   -90,   -90,    64,    64,    64,    64,    64,
      64,   -90,    64,   107,   -90,    94,   114,   -90,   100,   128,
     -90,   -90,    64,   -90,    64,    64,   169,   175,    15,    15,
     -90,   -90,   -90,   -90,   128,   -90,   -90,    64,   -90,   121,
     140,   162,    64,   108,   -90,   176,   -90,   109,   113,   106,
     -90,    53,   -90,   -90,   176,   110,   137,    53,   136,   -90,
     -90,   153,   -90,   -90,   -90,   176,   -90,   176,   -90,   -90,
     176,   148,     0
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       6,     9,    41,    42,    43,     0,     6,     2,     0,     8,
       1,     7,     4,     0,    11,     0,    10,    12,     0,     0,
       0,    14,     5,     0,    13,     0,    32,     0,     0,    33,
       0,     0,     0,    30,    15,     0,     0,    22,    54,    57,
       0,    58,    59,    53,     0,    55,     0,     0,    27,    28,
       0,     0,     0,    30,     0,     3,     0,    21,     0,     0,
      56,    60,    30,    30,    23,     0,     0,     0,     0,     0,
       0,    31,     0,     0,    38,     0,    39,    17,     0,    35,
      16,    18,     0,    44,     0,     0,    50,    49,    47,    48,
      45,    46,    30,    31,    34,    20,    37,     0,    30,     0,
      52,    51,     0,     0,    40,     0,    19,     0,     0,    25,
      30,     0,    36,    31,     0,     0,     0,    63,     0,    30,
      26,     0,    30,    62,    30,     0,    30,     0,    29,    24,
       0,    30,    30
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -90,   -90,   -90,   -90,   -90,   178,   -90,   -90,   165,   -90,
     -30,   -50,   -21,   -89,   -90,   -90,   -90,    80,   -90,   -23,
      95,     5,   -22,   -90,    74
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     5,     6,    13,    23,     7,     8,    15,    16,    17,
      33,    34,    56,    92,    47,    50,    93,    78,   113,    45,
      75,    36,    76,   117,   118
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      35,    53,    10,    46,   103,     9,    80,    12,    35,    62,
      63,     9,    14,    51,    19,   -61,   -61,    52,    59,    18,
       2,     3,    61,     4,   119,    18,    83,   -61,    81,    73,
      20,    82,    79,    35,    65,    66,    22,    67,    68,    69,
      70,    84,    85,    86,    87,    88,    89,    90,    91,    21,
      94,    48,    37,    69,    70,   109,    38,    39,    49,    40,
      99,    54,   100,   101,   120,    41,    42,    43,   115,   116,
      44,   102,     1,     2,     3,   129,     4,   105,    55,    57,
      79,    58,    35,    62,    63,    38,    39,    52,    40,   114,
      60,    35,    64,    77,    41,    42,    43,   131,   125,    44,
     132,   127,    35,   128,    35,   130,    71,    35,    65,    66,
      72,    67,    68,    69,    70,    62,    63,    38,    39,    96,
      40,    74,    62,    63,    95,    98,    41,    42,    43,    62,
      63,    44,    97,   108,   110,   112,    62,    63,   106,   111,
      65,    66,   121,    67,    68,    69,    70,    65,    66,    63,
      67,    68,    69,    70,    65,    66,   122,    67,    68,    69,
      70,    65,    66,   124,    67,    68,    69,    70,    67,    68,
      69,    70,   126,    65,    66,   -64,    67,    68,    69,    70,
       2,     3,   107,     4,    11,    24,    25,    26,    27,    28,
      29,   123,   104,     0,     0,    65,    66,    30,    67,    68,
      69,    70,    31,    66,    32,    67,    68,    69,    70,   -65,
       0,    67,    68,    69,    70
};

static const yytype_int16 yycheck[] =
{
      23,    31,     0,    25,    93,     0,    56,    21,    31,     8,
       9,     6,    24,    20,    25,    15,    16,    24,    40,    14,
       4,     5,    44,     7,   113,    20,    25,    27,    17,    51,
      18,    20,    54,    56,    33,    34,    26,    36,    37,    38,
      39,    62,    63,    65,    66,    67,    68,    69,    70,    21,
      72,    17,    17,    38,    39,   105,    21,    22,    17,    24,
      82,    24,    84,    85,   114,    30,    31,    32,    15,    16,
      35,    92,     3,     4,     5,   125,     7,    98,    27,    17,
     102,    21,   105,     8,     9,    21,    22,    24,    24,   110,
       6,   114,    17,    27,    30,    31,    32,   127,   119,    35,
     130,   122,   125,   124,   127,   126,    24,   130,    33,    34,
      24,    36,    37,    38,    39,     8,     9,    21,    22,    25,
      24,    25,     8,     9,    17,    25,    30,    31,    32,     8,
       9,    35,    18,    25,    25,    29,     8,     9,    17,    26,
      33,    34,    32,    36,    37,    38,    39,    33,    34,     9,
      36,    37,    38,    39,    33,    34,    19,    36,    37,    38,
      39,    33,    34,    27,    36,    37,    38,    39,    36,    37,
      38,    39,    19,    33,    34,    27,    36,    37,    38,    39,
       4,     5,   102,     7,     6,    20,    10,    11,    12,    13,
      14,   117,    97,    -1,    -1,    33,    34,    21,    36,    37,
      38,    39,    26,    34,    28,    36,    37,    38,    39,    34,
      -1,    36,    37,    38,    39
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     7,    41,    42,    45,    46,    61,
       0,    45,    21,    43,    24,    47,    48,    49,    61,    25,
      18,    21,    26,    44,    48,    10,    11,    12,    13,    14,
      21,    26,    28,    50,    51,    59,    61,    17,    21,    22,
      24,    30,    31,    32,    35,    59,    62,    54,    17,    17,
      55,    20,    24,    50,    24,    27,    52,    17,    21,    62,
       6,    62,     8,     9,    17,    33,    34,    36,    37,    38,
      39,    24,    24,    62,    25,    60,    62,    27,    57,    62,
      51,    17,    20,    25,    52,    52,    62,    62,    62,    62,
      62,    62,    53,    56,    62,    17,    25,    18,    25,    62,
      62,    62,    52,    53,    60,    52,    17,    57,    25,    51,
      25,    26,    29,    58,    52,    15,    16,    63,    64,    53,
      51,    32,    19,    64,    27,    52,    19,    52,    52,    51,
      52,    50,    50
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    42,    43,    44,    45,    45,    46,    46,
      47,    47,    48,    48,    49,    50,    50,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    59,    60,
      60,    61,    61,    61,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    63,    64,    64,    64
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     8,     1,     1,     0,     2,     1,     1,
       1,     0,     1,     3,     2,     1,     3,     3,     3,     5,
       4,     2,     2,     3,    10,     6,     9,     2,     2,    10,
       0,     0,     0,     0,     1,     1,     1,     4,     3,     1,
       3,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     4,     4,     1,     1,     1,     2,     1,     1,     1,
       2,     5,     2,     1,     4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

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
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
      yychar = yylex ();
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 96 "parser.ypp"
                {}
#line 1498 "parser.tab.cpp"
    break;

  case 3:
#line 99 "parser.ypp"
                                                                                 {
	if (current_func.ret_type == "VOID") {cbr.popCmd();}
	ir.end_func(current_func.ret_type, yyvsp[-1]);
	current_func = FunctionDecl();
	end_of_scope_operations();
																	}
#line 1509 "parser.tab.cpp"
    break;

  case 4:
#line 107 "parser.ypp"
              {
		current_func.id = yyvsp[0]->id;
		}
#line 1517 "parser.tab.cpp"
    break;

  case 5:
#line 111 "parser.ypp"
                      {
		offset_stack.push(0);
		assert(!tables_stack.empty());
		for (uint i = 0; i < current_func.arg_names.size(); i++) {
				new_formal(current_func.arg_names.at(i), -i-1, current_func.arg_types.at(i)); 
		}
		current_func.arg_types = vector<string>();}
#line 1529 "parser.tab.cpp"
    break;

  case 6:
#line 118 "parser.ypp"
        {}
#line 1535 "parser.tab.cpp"
    break;

  case 7:
#line 119 "parser.ypp"
                                 {}
#line 1541 "parser.tab.cpp"
    break;

  case 8:
#line 122 "parser.ypp"
               { current_func.ret_type = yyvsp[0]->type;}
#line 1547 "parser.tab.cpp"
    break;

  case 9:
#line 123 "parser.ypp"
                        {current_func.ret_type = "VOID";}
#line 1553 "parser.tab.cpp"
    break;

  case 10:
#line 125 "parser.ypp"
                        { new_func(current_func.id, current_func.ret_type, current_func.arg_types);	}
#line 1559 "parser.tab.cpp"
    break;

  case 11:
#line 126 "parser.ypp"
                  {new_func(current_func.id, current_func.ret_type, current_func.arg_types);}
#line 1565 "parser.tab.cpp"
    break;

  case 12:
#line 128 "parser.ypp"
                          {}
#line 1571 "parser.tab.cpp"
    break;

  case 13:
#line 129 "parser.ypp"
                                                       {}
#line 1577 "parser.tab.cpp"
    break;

  case 14:
#line 131 "parser.ypp"
                      {
		if (current_func.id == yyvsp[0]->id) {
			output::errorDef(yylineno, yyvsp[0]->id);
			exit(0);
		}
		current_func.arg_types.push_back(yyvsp[-1]->type);
		current_func.arg_names.push_back(yyvsp[0]->id);}
#line 1589 "parser.tab.cpp"
    break;

  case 15:
#line 139 "parser.ypp"
                       { 
						yyval = new Node();
						yyval->next_list = cbr.merge(yyval->next_list, yyvsp[0]->next_list);
						}
#line 1598 "parser.tab.cpp"
    break;

  case 16:
#line 143 "parser.ypp"
                                                 {
				cbr.bpatch(yyvsp[-2]->next_list, dynamic_cast<M*>(yyvsp[-1])->label);
				yyval = new Node();
				yyval->next_list = cbr.merge(yyval->next_list, yyvsp[0]->next_list);
			}
#line 1608 "parser.tab.cpp"
    break;

  case 17:
#line 149 "parser.ypp"
                                     {
				end_of_scope_operations();
				ir.goto_next_of_s(yyval);
				yyval->next_list = cbr.merge(yyval->next_list, yyvsp[-1]->next_list);
				}
#line 1618 "parser.tab.cpp"
    break;

  case 18:
#line 154 "parser.ypp"
                                      {

				ir.assign_reg(ir.to_llvm_type(yyvsp[-2]->type), 0, yyvsp[-1]);
				new_var(yyvsp[-1]->id, yyvsp[-2]->type, yyvsp[-1], yyvsp[-2]->type);
				ir.goto_next_of_s(yyval);
				}
#line 1629 "parser.tab.cpp"
    break;

  case 19:
#line 160 "parser.ypp"
                                                {
			    cbr.emit("; S->Type ID ASSIGN Exp SC");
                string ltype = yyvsp[-4]->type;
                string rtype = yyvsp[-1]->type;
                if (ltype != rtype) {
                    if (!(ltype == "INT" && rtype == "BYTE")) MISMATCH
                }
                if (ltype == "BOOL") {
                    yyvsp[-3]->reg_num = ir.get_bool_into_reg(dynamic_cast<BiNode*>(yyvsp[-1]));
                }
                new_var(yyvsp[-3]->id, ltype, yyvsp[-3], rtype);
				ir.goto_next_of_s(yyval);
				}
#line 1647 "parser.tab.cpp"
    break;

  case 20:
#line 173 "parser.ypp"
                                           {  
				string ltype = check_var_return_type(yyvsp[-3]->id);
				string rtype = yyvsp[-1]->type;
				if (ltype != rtype) {
					if (!(ltype == "INT" && rtype == "BYTE")) MISMATCH 
				}
				if (ltype == "BOOL") {
                    yyvsp[-2]->reg_num = ir.get_bool_into_reg(dynamic_cast<BiNode*>(yyvsp[-1]));
                }
                ir.store_local_var(get_offset(yyvsp[-3]->id), ltype, yyvsp[-3], rtype);
				ir.goto_next_of_s(yyval);
				}
#line 1664 "parser.tab.cpp"
    break;

  case 21:
#line 185 "parser.ypp"
                                  {
				ir.goto_next_of_s(yyval);}
#line 1671 "parser.tab.cpp"
    break;

  case 22:
#line 187 "parser.ypp"
                                    {
				if (current_func.ret_type != "VOID") MISMATCH}
#line 1678 "parser.tab.cpp"
    break;

  case 23:
#line 190 "parser.ypp"
                                        {
				if (current_func.ret_type == "VOID") MISMATCH
				if (current_func.ret_type != yyvsp[-1]->type && !(current_func.ret_type == "INT" && yyvsp[-1]->type == "BYTE")) MISMATCH
				if (yyvsp[-1]->type == "BOOL") {
					int bool_reg_num = ir.get_bool_into_reg(dynamic_cast<BiNode*>(yyvsp[-1]));
					yyvsp[-1]->reg_num = bool_reg_num;
				}
				ir.return_exp(yyvsp[-1], yyvsp[-1]->type);
				// ? goto_next_of_s ?
			}
#line 1693 "parser.tab.cpp"
    break;

  case 24:
#line 200 "parser.ypp"
                                                                                              {

				ir.bpatch_if_else_statement(yyval, yyvsp[-2], dynamic_cast<BiNode*>(yyvsp[-7]), (dynamic_cast<M*>(yyvsp[-5]))->label, (dynamic_cast<M*>(yyvsp[-1]))->label, yyvsp[-4], yyvsp[0]);
				end_of_scope_operations();
				ir.goto_next_of_s(yyval);
				}
#line 1704 "parser.tab.cpp"
    break;

  case 25:
#line 206 "parser.ypp"
                                                                     {
				    yyval = new Node();
			        ir.bpatch_if_statement(yyval, dynamic_cast<BiNode*>(yyvsp[-3]), (dynamic_cast<M*>(yyvsp[-1]))->label, yyvsp[0]);
					ir.goto_next_of_s(yyval);
					end_of_scope_operations();
					}
#line 1715 "parser.tab.cpp"
    break;

  case 26:
#line 213 "parser.ypp"
                                                                                        {
				string m1_label =  (dynamic_cast<M*>(yyvsp[-4]))->label;
				ir.bpatch_while(yyval, m1_label, dynamic_cast<BiNode*>(yyvsp[-3]), (dynamic_cast<M*>(yyvsp[-1]))->label, yyvsp[0],
				brk_lists_stack.top(), cont_lists_stack.top(), yyvsp[-5]);
				cont_lists_stack.pop();
				brk_lists_stack.pop();
				in_while.pop();
				end_of_scope_operations();
				ir.goto_next_of_s(yyval);
				}
#line 1730 "parser.tab.cpp"
    break;

  case 27:
#line 223 "parser.ypp"
                                   {
				if (in_while.empty() && in_switch.empty()) {
					output::errorUnexpectedBreak(yylineno);
					exit(0);
				}
				//ir.goto_specific_list(global_next_list);
				ir.goto_specific_list(brk_lists_stack.top());
			}
#line 1743 "parser.tab.cpp"
    break;

  case 28:
#line 231 "parser.ypp"
                                      { 
				if (in_while.empty()) {
					output::errorUnexpectedContinue(yylineno);
					exit(0);
				}		
				ir.goto_specific_list(cont_lists_stack.top());
			}
#line 1755 "parser.tab.cpp"
    break;

  case 29:
#line 238 "parser.ypp"
                                                                                                        {
				ir.emit_switch(yyval, yyvsp[-6], yyvsp[-5], yyvsp[-2], yyvsp[0], brk_lists_stack.top());
				in_switch.pop();
				brk_lists_stack.pop();
				end_of_scope_operations();
				ir.goto_next_of_s(yyval);
			}
#line 1767 "parser.tab.cpp"
    break;

  case 30:
#line 246 "parser.ypp"
    {
	yyval = new M();}
#line 1774 "parser.tab.cpp"
    break;

  case 31:
#line 248 "parser.ypp"
    {
	yyval = new Node();
	int loc = cbr.emit("\tbr label @");
	yyval->next_list = cbr.makelist(pair<int,BranchLabelIndex>(loc, FIRST));}
#line 1783 "parser.tab.cpp"
    break;

  case 32:
#line 252 "parser.ypp"
              {
	in_while.push(true);
	cont_lists_stack.push({});
	brk_lists_stack.push({});
 }
#line 1793 "parser.tab.cpp"
    break;

  case 33:
#line 258 "parser.ypp"
               {
	in_switch.push(true);
	brk_lists_stack.push({});
	}
#line 1802 "parser.tab.cpp"
    break;

  case 34:
#line 262 "parser.ypp"
                       {
	if (NOT_NUMERIC(yyvsp[0]->type)) MISMATCH
	}
#line 1810 "parser.tab.cpp"
    break;

  case 35:
#line 265 "parser.ypp"
                    {
	if (yyvsp[0]->type != "BOOL") MISMATCH}
#line 1817 "parser.tab.cpp"
    break;

  case 36:
#line 268 "parser.ypp"
                  {end_of_scope_operations();}
#line 1823 "parser.tab.cpp"
    break;

  case 37:
#line 269 "parser.ypp"
                                {
                                cbr.emit("; Call : ID LPAREN ExpList RPAREN");
                                const string& type =  check_func_return_type(yyvsp[-3]->id);
                                if (type == "BOOL") {
                                    yyval = new BiNode();
                                }
                                yyval->type = type;
                                yyval->reg_num = ir.call_func(yyvsp[-3]->id, yyval->type, called_exps);
                                if (type == "BOOL") {
                                    ir.icmp_bool_var((BiNode*)yyval, yyval);
                                }
	}
#line 1840 "parser.tab.cpp"
    break;

  case 38:
#line 281 "parser.ypp"
                                   {
		                        cbr.emit("; Call->ID...");
								const string& type =  check_func_return_type(yyvsp[-2]->id);
                                if (type == "BOOL") {
                                    yyval = new BiNode();
                                }
                                yyval->type = type;
                                yyval->reg_num = ir.call_func(yyvsp[-2]->id, yyval->type, called_exps);
                                if (type == "BOOL") {
                                    ir.icmp_bool_var((BiNode*)yyval, yyval);
                                }
							}
#line 1857 "parser.tab.cpp"
    break;

  case 39:
#line 295 "parser.ypp"
               {
            cbr.emit("; ExpList : Exp");
			called_arg_types.push(yyvsp[0]->type);
		    yyvsp[0]->reg_num = ir.get_called_bool_exps(yyvsp[0]);
			called_exps.push(yyvsp[0]);
			}
#line 1868 "parser.tab.cpp"
    break;

  case 40:
#line 301 "parser.ypp"
                                    {
		    cbr.emit("; ExpList : Exp COMMA ExpList ");
			called_arg_types.push(yyvsp[-2]->type);
			yyvsp[-2]->reg_num = ir.get_called_bool_exps(yyvsp[-2]);
			called_exps.push(yyvsp[-2]);
			}
#line 1879 "parser.tab.cpp"
    break;

  case 41:
#line 308 "parser.ypp"
           { 
		yyval = new Node();
		yyval->type = "INT";
		}
#line 1888 "parser.tab.cpp"
    break;

  case 42:
#line 312 "parser.ypp"
                        {
				yyval = new Node();
				yyval->type = "BYTE";
				}
#line 1897 "parser.tab.cpp"
    break;

  case 43:
#line 316 "parser.ypp"
                        {
				yyval = new Node();
				yyval->type = "BOOL";
				}
#line 1906 "parser.tab.cpp"
    break;

  case 44:
#line 322 "parser.ypp"
                                  {
			BiNode* p_binode = dynamic_cast<BiNode*>(yyvsp[-1]);
			if (p_binode) {
				yyval = new BiNode();
				yyval->type = "BOOL";
				dynamic_cast<BiNode*>(yyval)->true_list = p_binode->true_list;
				dynamic_cast<BiNode*>(yyval)->false_list = p_binode->false_list;
			}
			else {
				yyval = new Node();
				yyval->type = yyvsp[-1]->type;
				yyval->reg_num = yyvsp[-1]->reg_num;
			}}
#line 1924 "parser.tab.cpp"
    break;

  case 45:
#line 335 "parser.ypp"
                              {HANDLE_BINOP(yyvsp[-2], yyvsp[0], yyval, "MUL")}
#line 1930 "parser.tab.cpp"
    break;

  case 46:
#line 336 "parser.ypp"
                              {HANDLE_BINOP(yyvsp[-2], yyvsp[0], yyval, "DIV")}
#line 1936 "parser.tab.cpp"
    break;

  case 47:
#line 337 "parser.ypp"
                              {HANDLE_BINOP(yyvsp[-2], yyvsp[0], yyval, "ADD")}
#line 1942 "parser.tab.cpp"
    break;

  case 48:
#line 338 "parser.ypp"
                              {HANDLE_BINOP(yyvsp[-2], yyvsp[0], yyval, "SUB")}
#line 1948 "parser.tab.cpp"
    break;

  case 49:
#line 339 "parser.ypp"
                                   {
		    cbr.emit("; Exp: Exp RELATION Exp");
			check_numeric(yyvsp[-2], yyvsp[0]);
			yyval = new BiNode();
			yyval->type = "BOOL";
			ir.relop((BiNode*)yyval, yyvsp[-1]->type, yyvsp[-2], yyvsp[0]);

			}
#line 1961 "parser.tab.cpp"
    break;

  case 50:
#line 347 "parser.ypp"
                                   {
				check_numeric(yyvsp[-2], yyvsp[0]);
				yyval = new BiNode();
				yyval->type = "BOOL";
				ir.relop((BiNode*)yyval, yyvsp[-1]->type, yyvsp[-2], yyvsp[0]);
				}
#line 1972 "parser.tab.cpp"
    break;

  case 51:
#line 353 "parser.ypp"
                                {if (yyvsp[-3]->type != "BOOL" || yyvsp[0]->type != "BOOL") MISMATCH
				yyval = new BiNode();
				dynamic_cast<BiNode*>(yyval)->type = "BOOL";
				cbr.bpatch(dynamic_cast<BiNode*>(yyvsp[-3])->true_list, dynamic_cast<M*>(yyvsp[-1])->label);
				dynamic_cast<BiNode*>(yyval)->true_list = dynamic_cast<BiNode*>(yyvsp[0])->true_list;
				dynamic_cast<BiNode*>(yyval)->false_list = cbr.merge(dynamic_cast<BiNode*>(yyvsp[-3])->false_list, dynamic_cast<BiNode*>(yyvsp[0])->false_list);
				}
#line 1984 "parser.tab.cpp"
    break;

  case 52:
#line 360 "parser.ypp"
                               {
				if (yyvsp[-3]->type != "BOOL" || yyvsp[0]->type != "BOOL") MISMATCH

				yyval = new BiNode();
				dynamic_cast<BiNode*>(yyval)->type = "BOOL";
				cbr.bpatch(dynamic_cast<BiNode*>(yyvsp[-3])->false_list, dynamic_cast<M*>(yyvsp[-1])->label);
				dynamic_cast<BiNode*>(yyval)->true_list = cbr.merge(dynamic_cast<BiNode*>(yyvsp[-3])->true_list, dynamic_cast<BiNode*>(yyvsp[0])->true_list);
				dynamic_cast<BiNode*>(yyval)->false_list = dynamic_cast<BiNode*>(yyvsp[0])->false_list;

		}
#line 1999 "parser.tab.cpp"
    break;

  case 53:
#line 370 "parser.ypp"
                      {
				//$$ = new Node();
				yyval->type = "INT";
				ir.assign_reg("i32", yyval->value, yyval);
				}
#line 2009 "parser.tab.cpp"
    break;

  case 54:
#line 375 "parser.ypp"
                     {
		    cbr.emit("; Exp : ID");
			const string& ty = check_var_return_type(yyvsp[0]->id);
			if (ty == "BOOL") 
				yyval = new BiNode();
			else
				yyval = new Node();
			
			yyval->type = ty;
			ir.load_local_var(get_offset(yyvsp[0]->id), yyval->type, yyval);
			if (ty == "BOOL") 
				ir.icmp_bool_var((BiNode*)yyval, yyval);
		 }
#line 2027 "parser.tab.cpp"
    break;

  case 55:
#line 388 "parser.ypp"
                       {
            cbr.emit("; Exp->Call");
			if (yyvsp[0]->type == "BOOL") {
				yyval = new BiNode();
				dynamic_cast<BiNode*>(yyval)->true_list = dynamic_cast<BiNode*>(yyvsp[0])->true_list;
				dynamic_cast<BiNode*>(yyval)->false_list = dynamic_cast<BiNode*>(yyvsp[0])->false_list;
			}
			else {
				yyval = new Node();
			}
			yyval->next_list = yyvsp[0]->next_list;
			yyval->reg_num = yyvsp[0]->reg_num;
			yyval->type = yyvsp[0]->type; }
#line 2045 "parser.tab.cpp"
    break;

  case 56:
#line 401 "parser.ypp"
                        {
			if (yyvsp[-1]->value > 255) {
				output::errorByteTooLarge(yylineno, to_string(yyvsp[-1]->value));
				exit(0);
			} 
			yyval->type = "BYTE";
			ir.assign_reg("i8", yyval->value, yyval);
			}
#line 2058 "parser.tab.cpp"
    break;

  case 57:
#line 409 "parser.ypp"
                         {
				yyval->type = "STRING";
				ir.push_string_to_emitGlobal(yyval->id, yyval->type);
				ir.assign_reg("i8", yyval->value, yyval);
				}
#line 2068 "parser.tab.cpp"
    break;

  case 58:
#line 414 "parser.ypp"
                       { 
				yyval = new BiNode();
				yyval->type = "BOOL";
				yyval->value = 1;
				int loc = cbr.emit("\tbr label @");
    			dynamic_cast<BiNode*>(yyval)->true_list = cbr.makelist({loc, FIRST});
				}
#line 2080 "parser.tab.cpp"
    break;

  case 59:
#line 421 "parser.ypp"
                        {yyval = new BiNode();
				yyval->type = "BOOL";
				yyval->value = 0;
				int loc = cbr.emit("\tbr label @");
				dynamic_cast<BiNode*>(yyval)->false_list = cbr.makelist({loc, FIRST});
				
				}
#line 2092 "parser.tab.cpp"
    break;

  case 60:
#line 428 "parser.ypp"
                          {
				if (yyvsp[0]->type != "BOOL") MISMATCH
				yyval = new BiNode();
				yyval->type = "BOOL";
				dynamic_cast<BiNode*>(yyval)->true_list = dynamic_cast<BiNode*>(yyvsp[0])->false_list;
				dynamic_cast<BiNode*>(yyval)->false_list = dynamic_cast<BiNode*>(yyvsp[0])->true_list;
		}
#line 2104 "parser.tab.cpp"
    break;

  case 61:
#line 437 "parser.ypp"
                                       {
	ir.dbg_list(yyvsp[0]);
	string quad = dynamic_cast<M*>(yyvsp[-1])->label;
	yyval = new C();
	dynamic_cast<C*>(yyval)->quad = quad;
	dynamic_cast<C*>(yyval)->value = yyvsp[-3]->value;
	dynamic_cast<C*>(yyval)->next_list = yyvsp[0]->next_list;
	
}
#line 2118 "parser.tab.cpp"
    break;

  case 62:
#line 448 "parser.ypp"
                             {
			yyval = new CL();
			ir.cl_c_cl_rule(dynamic_cast<CL*>(yyval), yyvsp[-1], dynamic_cast<CL*>(yyvsp[0]));
			}
#line 2127 "parser.tab.cpp"
    break;

  case 63:
#line 452 "parser.ypp"
                           {
		    yyval = new CL();
			ir.cl_c_rule(dynamic_cast<CL*>(yyval), yyvsp[0]);
			
		}
#line 2137 "parser.tab.cpp"
    break;

  case 64:
#line 457 "parser.ypp"
                                             {
			string quad = dynamic_cast<M*>(yyvsp[-1])->label;
			yyval = new CL();
			dynamic_cast<CL*>(yyval)->quad_list.push(quad);
			dynamic_cast<CL*>(yyval)->default_label = quad;
			dynamic_cast<CL*>(yyval)->next_list = yyvsp[0]->next_list;
		}
#line 2149 "parser.tab.cpp"
    break;


#line 2153 "parser.tab.cpp"

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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



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
                      yytoken, &yylval);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
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
  return yyresult;
}
#line 466 "parser.ypp"


void yyerror(const char* c) {
	if (string(c) == "syntax error")
		output::errorSyn(yylineno);
	else
		output::errorLex(yylineno); 
	exit(0);
}

void check_numeric(Node* x, Node* y) {
	if (NOT_NUMERIC(x->type) || NOT_NUMERIC(y->type)) MISMATCH
}

TableEntry* get_entry(const string& id) {
	return hash_ids.find(id)->second;
}

int get_offset(const string& id) {
    return get_entry(id)->offset;
}

string get_type_of_binop(string x, string y) {
	if (x == "INT" || y == "INT") return "INT";
	return "BYTE";
}

string check_var_return_type(const string& id) {
	if (hash_ids.find(id) == hash_ids.end() || hash_funcs.find(id) != hash_funcs.end()) {
		output::errorUndef(yylineno, id);
		exit(0);
	}
	return hash_ids[id]->type;
}

string check_func_return_type(const string& id) {
	// 1. Checks that identifier was defined.
	// 2. Checks that the identifier is a function.
	if (hash_ids.find(id) == hash_ids.end() || hash_funcs.find(id) == hash_funcs.end()) {
		output::errorUndefFunc(yylineno, id);
		exit(0);
	}
	vector<string> exp_func_args = hash_funcs[id].arg_types;
	if (exp_func_args.size() != called_arg_types.size()) {
		output::errorPrototypeMismatch(yylineno, id, exp_func_args);
		exit(0);
	}
	for (uint i = 0; i < exp_func_args.size(); i++) {
		string exp_type = exp_func_args.at(i);
		string called_type = called_arg_types.top();
		called_arg_types.pop();
		if (exp_type != called_type) {
			if (!(exp_type == "INT" && called_type == "BYTE")) {

				output::errorPrototypeMismatch(yylineno, id, exp_func_args);
				exit(0);
			}
		}
	}
	called_arg_types = stack<string>();
	return hash_funcs[id].ret_type;
}

static void check_id_def(const string& id) {
	if (hash_ids.find(id) != hash_ids.end()) {
			output::errorDef(yylineno, id);
			exit(0);
	}
}

static void add_id_to_ids(const string& id, TableEntry* p_entry) {
	hash_ids[id] = p_entry;
}

static void add_func_to_hash(const string& id, const string& ret_type, vector<string>& arg_types) {
		FuncTypes f(ret_type, arg_types);
		hash_funcs[id] = f;
}

void new_formal(const string& id, int offset, const string& type) {
	check_id_def(id);
	TableEntry* p_entry = tables_stack.top()->insert(id, offset, type);
	add_id_to_ids(id, p_entry);
}

void new_var(const string& id, const string& ltype, Node* pNode, const string& rtype) {
	check_id_def(id);
	TableEntry* p_entry = tables_stack.top()->insert(id, offset_stack.top(), ltype);
	ir.store_local_var(offset_stack.top(), ltype, pNode, rtype);
	offset_stack.top()++;
	add_id_to_ids(id, p_entry);
}

void new_func(const string& id, const string& ret_type, vector<string>& arg_types) {
	check_id_def(id);
	add_id_to_ids(id, nullptr);
	add_func_to_hash(id, ret_type, arg_types);
	tables_stack.top()->insert(id, 0, output::makeFunctionType(ret_type, arg_types));
	ir.def_func(id, ret_type, arg_types);
}

void new_table() {
		SymbolsTable* parent;
		if (!tables_stack.empty())
				parent = tables_stack.top();
		else
				parent = nullptr;
		SymbolsTable* symbol_table = new SymbolsTable(parent);
		tables_stack.push(symbol_table);
		assert(!offset_stack.empty());
		offset_stack.push(offset_stack.top());
}

void remove_table() {
		if (tables_stack.empty()) {
				cout << "Tables Stack is empty!" << endl;
				return;
		}
		auto ptr = tables_stack.top();
		for (auto entry : ptr->entries) {
				hash_ids.erase(entry->id);
				delete entry;
		}
		tables_stack.pop();
		delete ptr;
}

void end_of_scope_operations() {
		// output::endScope();
		// tables_stack.top()->print_ids();
		remove_table();
		if (!offset_stack.empty()) {
				offset_stack.pop();
		}
}

int main() {
		offset_stack.push(0);
		new_table();
		vector<string> print_args = {"STRING"};
		new_func("print", "VOID", print_args);
		vector<string> printi_args = {"INT"};
		new_func("printi", "VOID", printi_args);
		yyparse();

		ir.emit_print_functions();
		SymbolsTable* global_symbol_table = tables_stack.top();
		bool found = false;
		for (TableEntry* entry : global_symbol_table->entries) {
			if (entry->id == "main" && entry->type == "()->VOID")
				found = true;
		}
		if (not found) {
			output::errorMainMissing();
			exit(0);
		}
		end_of_scope_operations();
		
		cbr.printCodeBuffer();

}

