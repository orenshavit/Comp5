/* A Bison parser, made by GNU Bison 3.7.6.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30706

/* Bison version string.  */
#define YYBISON_VERSION "3.7.6"

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
	  										ir.binop(op, &(first->reg_num), &(second->reg_num), first->type, second->type, lval);

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
	stack<pair<string, int>> called_exps; // <type of Exp : string, number of register that hols the Exp : int>

	unordered_map<string, TableEntry*> hash_ids;
	unordered_map<string, FuncTypes> hash_funcs;
	stack<bool> in_while;
	stack<bool> in_switch;

	CodeBuffer& cbr = CodeBuffer::instance();
	ManageIR ir;

	vector<pair<int,BranchLabelIndex>> while_list = {};


#line 127 "parser.tab.cpp"

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

#include "parser.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_VOID = 3,                       /* VOID  */
  YYSYMBOL_INT = 4,                        /* INT  */
  YYSYMBOL_BYTE = 5,                       /* BYTE  */
  YYSYMBOL_B = 6,                          /* B  */
  YYSYMBOL_BOOL = 7,                       /* BOOL  */
  YYSYMBOL_OR = 8,                         /* OR  */
  YYSYMBOL_AND = 9,                        /* AND  */
  YYSYMBOL_RETURN = 10,                    /* RETURN  */
  YYSYMBOL_WHILE = 11,                     /* WHILE  */
  YYSYMBOL_BREAK = 12,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 13,                  /* CONTINUE  */
  YYSYMBOL_SWITCH = 14,                    /* SWITCH  */
  YYSYMBOL_CASE = 15,                      /* CASE  */
  YYSYMBOL_DEFAULT = 16,                   /* DEFAULT  */
  YYSYMBOL_SC = 17,                        /* SC  */
  YYSYMBOL_COMMA = 18,                     /* COMMA  */
  YYSYMBOL_COLON = 19,                     /* COLON  */
  YYSYMBOL_ASSIGN = 20,                    /* ASSIGN  */
  YYSYMBOL_ID = 21,                        /* ID  */
  YYSYMBOL_STRING = 22,                    /* STRING  */
  YYSYMBOL_ILLEGAL = 23,                   /* ILLEGAL  */
  YYSYMBOL_LPAREN = 24,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 25,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 26,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 27,                    /* RBRACE  */
  YYSYMBOL_IF = 28,                        /* IF  */
  YYSYMBOL_ELSE = 29,                      /* ELSE  */
  YYSYMBOL_TRUE = 30,                      /* TRUE  */
  YYSYMBOL_FALSE = 31,                     /* FALSE  */
  YYSYMBOL_NUM = 32,                       /* NUM  */
  YYSYMBOL_EQUALITY = 33,                  /* EQUALITY  */
  YYSYMBOL_RELATION = 34,                  /* RELATION  */
  YYSYMBOL_NOT = 35,                       /* NOT  */
  YYSYMBOL_ADD = 36,                       /* ADD  */
  YYSYMBOL_SUB = 37,                       /* SUB  */
  YYSYMBOL_MUL = 38,                       /* MUL  */
  YYSYMBOL_DIV = 39,                       /* DIV  */
  YYSYMBOL_YYACCEPT = 40,                  /* $accept  */
  YYSYMBOL_Program = 41,                   /* Program  */
  YYSYMBOL_FuncDecl = 42,                  /* FuncDecl  */
  YYSYMBOL_MarkerID = 43,                  /* MarkerID  */
  YYSYMBOL_MarkerLBRACE = 44,              /* MarkerLBRACE  */
  YYSYMBOL_Funcs = 45,                     /* Funcs  */
  YYSYMBOL_RetType = 46,                   /* RetType  */
  YYSYMBOL_Formals = 47,                   /* Formals  */
  YYSYMBOL_FormalsList = 48,               /* FormalsList  */
  YYSYMBOL_FormalDecl = 49,                /* FormalDecl  */
  YYSYMBOL_Statements = 50,                /* Statements  */
  YYSYMBOL_Statement = 51,                 /* Statement  */
  YYSYMBOL_M = 52,                         /* M  */
  YYSYMBOL_N = 53,                         /* N  */
  YYSYMBOL_MarkerWhile = 54,               /* MarkerWhile  */
  YYSYMBOL_MarkerSwitch = 55,              /* MarkerSwitch  */
  YYSYMBOL_MarkerNumericExp = 56,          /* MarkerNumericExp  */
  YYSYMBOL_MarkerBoolExp = 57,             /* MarkerBoolExp  */
  YYSYMBOL_MarkerELSE = 58,                /* MarkerELSE  */
  YYSYMBOL_Call = 59,                      /* Call  */
  YYSYMBOL_ExpList = 60,                   /* ExpList  */
  YYSYMBOL_Type = 61,                      /* Type  */
  YYSYMBOL_Exp = 62,                       /* Exp  */
  YYSYMBOL_CaseDecl = 63,                  /* CaseDecl  */
  YYSYMBOL_CaseList = 64                   /* CaseList  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYLAST   240

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  64
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  135

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   294


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

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
       0,    91,    91,    94,   101,   105,   114,   115,   118,   119,
     121,   122,   124,   125,   127,   136,   140,   148,   152,   160,
     175,   190,   193,   197,   206,   211,   217,   226,   233,   242,
     251,   255,   261,   264,   266,   271,   275,   277,   289,   303,
     307,   312,   316,   320,   326,   339,   340,   341,   342,   343,
     350,   356,   363,   373,   378,   390,   403,   411,   413,   420,
     427,   436,   445,   455,   462
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "VOID", "INT", "BYTE",
  "B", "BOOL", "OR", "AND", "RETURN", "WHILE", "BREAK", "CONTINUE",
  "SWITCH", "CASE", "DEFAULT", "SC", "COMMA", "COLON", "ASSIGN", "ID",
  "STRING", "ILLEGAL", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "IF",
  "ELSE", "TRUE", "FALSE", "NUM", "EQUALITY", "RELATION", "NOT", "ADD",
  "SUB", "MUL", "DIV", "$accept", "Program", "FuncDecl", "MarkerID",
  "MarkerLBRACE", "Funcs", "RetType", "Formals", "FormalsList",
  "FormalDecl", "Statements", "Statement", "M", "N", "MarkerWhile",
  "MarkerSwitch", "MarkerNumericExp", "MarkerBoolExp", "MarkerELSE",
  "Call", "ExpList", "Type", "Exp", "CaseDecl", "CaseList", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294
};
#endif

#define YYPACT_NINF (-80)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-32)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      23,   -80,   -80,   -80,   -80,     2,    23,   -80,    -4,   -80,
     -80,   -80,   -80,   -11,    69,   -10,   -80,    13,    -1,    10,
      69,   -80,   -80,   185,   -80,    37,   -80,    32,    34,   -80,
      -8,   185,    42,    38,   -80,    53,    57,   -80,    55,   -80,
     205,   -80,   -80,    84,   205,   -80,    75,    71,   -80,   -80,
      72,   205,   193,    54,   205,   -80,   185,   -80,   -13,    85,
     -80,    49,   -80,   -80,   -80,   205,   205,   205,   205,   205,
     205,   -80,   205,   108,   -80,    74,   118,   -80,    81,   140,
     -80,   -80,   205,   -80,   205,   205,     1,    94,   -15,   -15,
     -80,   -80,   -80,   -80,   140,   -80,   -80,   205,   -80,   126,
     149,   133,   205,    90,   -80,   185,   -80,    95,   103,   109,
     -80,    41,   -80,   -80,   185,   105,   120,    41,   113,   -80,
     -80,   131,   -80,   -80,   -80,   185,   -80,   185,   -80,   -80,
     185,   134,    -6,   -80,   -80
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
       0,    30,    30,    64,    61
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -80,   -80,   -80,   -80,   -80,   147,   -80,   -80,   148,   -80,
     -30,   -50,   -21,   -79,   -80,   -80,   -80,    73,   -80,   -23,
      83,     5,   -22,   -80,    64
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     5,     6,    13,    23,     7,     8,    15,    16,    17,
      33,    34,    56,    92,    47,    50,    93,    78,   113,    45,
      75,    36,    76,   117,   118
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      35,    53,    10,    46,    81,     9,    80,    82,    35,   -31,
     -31,     9,    51,    14,   103,    19,    52,    12,    59,    18,
      21,   -31,    61,    69,    70,    18,     1,     2,     3,    73,
       4,    20,    79,    35,   119,    66,    22,    67,    68,    69,
      70,    84,    85,    86,    87,    88,    89,    90,    91,    48,
      94,    49,   133,   134,    37,   109,   115,   116,    38,    39,
      99,    40,   100,   101,   120,    55,    54,    41,    42,    43,
      57,   102,    44,     2,     3,   129,     4,   105,    58,    52,
      79,    77,    35,    62,    63,    67,    68,    69,    70,   114,
      60,    35,    64,    62,    63,    71,    72,   131,   125,    96,
     132,   127,    35,   128,    35,   130,    98,    35,    65,    66,
      83,    67,    68,    69,    70,   108,    62,    63,    65,    66,
     110,    67,    68,    69,    70,    95,    62,    63,   -32,   111,
      67,    68,    69,    70,    62,    63,    97,   121,   112,   122,
     124,    65,    66,   106,    67,    68,    69,    70,    62,    63,
     126,    65,    66,    11,    67,    68,    69,    70,    63,    65,
      66,   -31,    67,    68,    69,    70,    65,    66,    24,    67,
      68,    69,    70,    65,    66,   107,    67,    68,    69,    70,
     104,   123,    65,    66,     0,    67,    68,    69,    70,     2,
       3,     0,     4,     0,     0,    25,    26,    27,    28,    29,
       0,     0,     0,     0,     0,     0,    30,     0,     0,     0,
       0,    31,     0,    32,    38,    39,     0,    40,    74,     0,
       0,     0,     0,    41,    42,    43,    38,    39,    44,    40,
       0,     0,     0,     0,     0,    41,    42,    43,     0,     0,
      44
};

static const yytype_int16 yycheck[] =
{
      23,    31,     0,    25,    17,     0,    56,    20,    31,    15,
      16,     6,    20,    24,    93,    25,    24,    21,    40,    14,
      21,    27,    44,    38,    39,    20,     3,     4,     5,    51,
       7,    18,    54,    56,   113,    34,    26,    36,    37,    38,
      39,    62,    63,    65,    66,    67,    68,    69,    70,    17,
      72,    17,   131,   132,    17,   105,    15,    16,    21,    22,
      82,    24,    84,    85,   114,    27,    24,    30,    31,    32,
      17,    92,    35,     4,     5,   125,     7,    98,    21,    24,
     102,    27,   105,     8,     9,    36,    37,    38,    39,   110,
       6,   114,    17,     8,     9,    24,    24,   127,   119,    25,
     130,   122,   125,   124,   127,   126,    25,   130,    33,    34,
      25,    36,    37,    38,    39,    25,     8,     9,    33,    34,
      25,    36,    37,    38,    39,    17,     8,     9,    34,    26,
      36,    37,    38,    39,     8,     9,    18,    32,    29,    19,
      27,    33,    34,    17,    36,    37,    38,    39,     8,     9,
      19,    33,    34,     6,    36,    37,    38,    39,     9,    33,
      34,    27,    36,    37,    38,    39,    33,    34,    20,    36,
      37,    38,    39,    33,    34,   102,    36,    37,    38,    39,
      97,   117,    33,    34,    -1,    36,    37,    38,    39,     4,
       5,    -1,     7,    -1,    -1,    10,    11,    12,    13,    14,
      -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    -1,    -1,
      -1,    26,    -1,    28,    21,    22,    -1,    24,    25,    -1,
      -1,    -1,    -1,    30,    31,    32,    21,    22,    35,    24,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    -1,    -1,
      35
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
      52,    50,    50,    53,    53
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
       2,     6,     2,     1,     5
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

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
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  case 2: /* Program: Funcs  */
#line 91 "parser.ypp"
                {}
#line 1295 "parser.tab.cpp"
    break;

  case 3: /* FuncDecl: RetType MarkerID LPAREN Formals RPAREN MarkerLBRACE Statements RBRACE  */
#line 94 "parser.ypp"
                                                                                 {
																	ir.end_func(current_func.ret_type, yyvsp[-1]);
																	current_func = FunctionDecl();
																	end_of_scope_operations();
																	}
#line 1305 "parser.tab.cpp"
    break;

  case 4: /* MarkerID: ID  */
#line 101 "parser.ypp"
              {
		current_func.id = yyvsp[0]->id;
		}
#line 1313 "parser.tab.cpp"
    break;

  case 5: /* MarkerLBRACE: LBRACE  */
#line 105 "parser.ypp"
                      {
		offset_stack.push(0);
		assert(!tables_stack.empty());
		for (uint i = 0; i < current_func.arg_names.size(); i++) {
				new_formal(current_func.arg_names.at(i), -i-1, current_func.arg_types.at(i)); 
		}
		current_func.arg_types = vector<string>();
}
#line 1326 "parser.tab.cpp"
    break;

  case 6: /* Funcs: %empty  */
#line 114 "parser.ypp"
        {}
#line 1332 "parser.tab.cpp"
    break;

  case 7: /* Funcs: FuncDecl Funcs  */
#line 115 "parser.ypp"
                                 {}
#line 1338 "parser.tab.cpp"
    break;

  case 8: /* RetType: Type  */
#line 118 "parser.ypp"
               { current_func.ret_type = yyvsp[0]->type;}
#line 1344 "parser.tab.cpp"
    break;

  case 9: /* RetType: VOID  */
#line 119 "parser.ypp"
                        {current_func.ret_type = "VOID";}
#line 1350 "parser.tab.cpp"
    break;

  case 10: /* Formals: FormalsList  */
#line 121 "parser.ypp"
                        { new_func(current_func.id, current_func.ret_type, current_func.arg_types);	}
#line 1356 "parser.tab.cpp"
    break;

  case 11: /* Formals: %empty  */
#line 122 "parser.ypp"
                  {new_func(current_func.id, current_func.ret_type, current_func.arg_types);}
#line 1362 "parser.tab.cpp"
    break;

  case 12: /* FormalsList: FormalDecl  */
#line 124 "parser.ypp"
                          {}
#line 1368 "parser.tab.cpp"
    break;

  case 13: /* FormalsList: FormalDecl COMMA FormalsList  */
#line 125 "parser.ypp"
                                                       {}
#line 1374 "parser.tab.cpp"
    break;

  case 14: /* FormalDecl: Type ID  */
#line 127 "parser.ypp"
                      {
		if (current_func.id == yyvsp[0]->id) {
			output::errorDef(yylineno, yyvsp[0]->id);
			exit(0);
		}
		current_func.arg_types.push_back(yyvsp[-1]->type);
		current_func.arg_names.push_back(yyvsp[0]->id);
}
#line 1387 "parser.tab.cpp"
    break;

  case 15: /* Statements: Statement  */
#line 136 "parser.ypp"
                       { 
						yyval = new Node();
						yyval->next_list = yyvsp[0]->next_list;
						}
#line 1396 "parser.tab.cpp"
    break;

  case 16: /* Statements: Statements M Statement  */
#line 140 "parser.ypp"
                                                 {
				cbr.bpatch(yyvsp[-2]->next_list, dynamic_cast<M*>(yyvsp[-1])->label);
				//cbr.bpatch($2->next_list, dynamic_cast<M*>($3)->label);
				yyval = new Node();
				yyval->next_list = yyvsp[0]->next_list;
				cbr.emit("");
			}
#line 1408 "parser.tab.cpp"
    break;

  case 17: /* Statement: LBRACE Statements RBRACE  */
#line 148 "parser.ypp"
                                     {
				end_of_scope_operations();
				ir.empty_goto(yyval);
				}
#line 1417 "parser.tab.cpp"
    break;

  case 18: /* Statement: Type ID SC  */
#line 152 "parser.ypp"
                                      {

				ir.assign_reg(ir.to_llvm_type(yyvsp[-2]->type), 0, yyvsp[-1]);
				new_var(yyvsp[-1]->id, yyvsp[-2]->type, yyvsp[-1], yyvsp[-2]->type);
				ir.empty_goto(yyval);
				}
#line 1428 "parser.tab.cpp"
    break;

  case 19: /* Statement: Type ID ASSIGN Exp SC  */
#line 160 "parser.ypp"
                                                {
			    cbr.emit("; S->Type ID ASSIGN Exp SC");
                string ltype = yyvsp[-4]->type;
                string rtype = yyvsp[-1]->type;
                if (ltype != rtype) {
                    if (!(ltype == "INT" && rtype == "BYTE")) MISMATCH
                }
                if (ltype == "BOOL") {
                    yyvsp[-3]->reg_num = ir.get_bool(dynamic_cast<BiNode*>(yyvsp[-1]));
                }
                new_var(yyvsp[-3]->id, ltype, yyvsp[-3], rtype);
				ir.empty_goto(yyval);
				}
#line 1446 "parser.tab.cpp"
    break;

  case 20: /* Statement: ID ASSIGN Exp SC  */
#line 175 "parser.ypp"
                                           {  
				string ltype = check_var_return_type(yyvsp[-3]->id);
				string rtype = yyvsp[-1]->type;
				if (ltype != rtype) {
					if (!(ltype == "INT" && rtype == "BYTE")) MISMATCH 
				}
				if (ltype == "BOOL") {
                    yyvsp[-2]->reg_num = ir.get_bool(dynamic_cast<BiNode*>(yyvsp[-1]));
                }
                ir.store_local_var(get_offset(yyvsp[-3]->id), ltype, yyvsp[-3], rtype);
				ir.empty_goto(yyval);
				}
#line 1463 "parser.tab.cpp"
    break;

  case 21: /* Statement: Call SC  */
#line 190 "parser.ypp"
                                  {
				ir.empty_goto(yyval);
			}
#line 1471 "parser.tab.cpp"
    break;

  case 22: /* Statement: RETURN SC  */
#line 193 "parser.ypp"
                                    {
				if (current_func.ret_type != "VOID") MISMATCH
				// ? empty_goto ?
			}
#line 1480 "parser.tab.cpp"
    break;

  case 23: /* Statement: RETURN Exp SC  */
#line 197 "parser.ypp"
                                        {
				if (current_func.ret_type != yyvsp[-1]->type || current_func.ret_type == "VOID") MISMATCH
				if (yyvsp[-1]->type == "BOOL") {
					int bool_reg_num = ir.get_bool(dynamic_cast<BiNode*>(yyvsp[-1]));
					yyvsp[-1]->reg_num = bool_reg_num;
				}
				ir.return_exp(yyvsp[-1]->reg_num, yyvsp[-1]->type);
				// ? empty_goto ?
			}
#line 1494 "parser.tab.cpp"
    break;

  case 24: /* Statement: IF LPAREN MarkerBoolExp RPAREN M Statement MarkerELSE N M Statement  */
#line 206 "parser.ypp"
                                                                                              {
				ir.bpatch_if_else_statement(yyval, yyvsp[-2], dynamic_cast<BiNode*>(yyvsp[-7]), (dynamic_cast<M*>(yyvsp[-5]))->label, (dynamic_cast<M*>(yyvsp[-1]))->label, yyvsp[-4], yyvsp[0]);
				end_of_scope_operations();
				ir.empty_goto(yyval);
				}
#line 1504 "parser.tab.cpp"
    break;

  case 25: /* Statement: IF LPAREN MarkerBoolExp RPAREN M Statement  */
#line 211 "parser.ypp"
                                                                     {
			        ir.bpatch_if_statement(yyval, dynamic_cast<BiNode*>(yyvsp[-3]), (dynamic_cast<M*>(yyvsp[-1]))->label, yyvsp[0]);
					ir.empty_goto(yyval);
					end_of_scope_operations();
					}
#line 1514 "parser.tab.cpp"
    break;

  case 26: /* Statement: WHILE MarkerWhile LPAREN N M MarkerBoolExp RPAREN M Statement  */
#line 217 "parser.ypp"
                                                                                        {
				string m1_label = (dynamic_cast<M*>(yyvsp[-4]))->label;
				cbr.bpatch(while_list, m1_label);
				cbr.bpatch(yyvsp[-5]->next_list, m1_label);
				ir.bpatch_while(yyval, m1_label, dynamic_cast<BiNode*>(yyvsp[-3]), (dynamic_cast<M*>(yyvsp[-1]))->label, yyvsp[0]);
				in_while.pop();
				end_of_scope_operations();
				ir.empty_goto(yyval);
				}
#line 1528 "parser.tab.cpp"
    break;

  case 27: /* Statement: BREAK SC  */
#line 226 "parser.ypp"
                                   {
				if (in_while.empty() && in_switch.empty()) {
					output::errorUnexpectedBreak(yylineno);
					exit(0);
				}
				// ir.empty_goto($$); ?
			}
#line 1540 "parser.tab.cpp"
    break;

  case 28: /* Statement: CONTINUE SC  */
#line 233 "parser.ypp"
                                      { 
				if (in_while.empty()) {
					output::errorUnexpectedContinue(yylineno);
					exit(0);
				}
				int loc = cbr.emit("\tbr label @");
				while_list = cbr.makelist(pair<int,BranchLabelIndex>(loc, FIRST));

			}
#line 1554 "parser.tab.cpp"
    break;

  case 29: /* Statement: SWITCH MarkerSwitch LPAREN MarkerNumericExp N RPAREN LBRACE CaseList RBRACE M  */
#line 242 "parser.ypp"
                                                                                                        {
				ir.emit_switch(yyval, yyvsp[-6], yyvsp[-5], yyvsp[-2], yyvsp[0]);
				in_switch.pop();
				end_of_scope_operations();
				ir.empty_goto(yyval);
				 }
#line 1565 "parser.tab.cpp"
    break;

  case 30: /* M: %empty  */
#line 251 "parser.ypp"
    {
	yyval = new M();
}
#line 1573 "parser.tab.cpp"
    break;

  case 31: /* N: %empty  */
#line 255 "parser.ypp"
    {
	yyval = new Node();
	int loc = cbr.emit("\tbr label @");
	yyval->next_list = cbr.makelist(pair<int,BranchLabelIndex>(loc, FIRST));
}
#line 1583 "parser.tab.cpp"
    break;

  case 32: /* MarkerWhile: %empty  */
#line 261 "parser.ypp"
              { in_while.push(true);
 }
#line 1590 "parser.tab.cpp"
    break;

  case 33: /* MarkerSwitch: %empty  */
#line 264 "parser.ypp"
               { in_switch.push(true); }
#line 1596 "parser.tab.cpp"
    break;

  case 34: /* MarkerNumericExp: Exp  */
#line 266 "parser.ypp"
                       {
	if (NOT_NUMERIC(yyvsp[0]->type)) MISMATCH
	
}
#line 1605 "parser.tab.cpp"
    break;

  case 35: /* MarkerBoolExp: Exp  */
#line 271 "parser.ypp"
                    {
	if (yyvsp[0]->type != "BOOL") MISMATCH
}
#line 1613 "parser.tab.cpp"
    break;

  case 36: /* MarkerELSE: ELSE  */
#line 275 "parser.ypp"
                  {end_of_scope_operations();}
#line 1619 "parser.tab.cpp"
    break;

  case 37: /* Call: ID LPAREN ExpList RPAREN  */
#line 277 "parser.ypp"
                                { 
								cbr.emit("; Call->ID...");
                                const string& type =  check_func_return_type(yyvsp[-3]->id);
                                if (type == "BOOL") {
                                    yyval = new BiNode();
                                }
                                yyval->type = type;
                                yyval->reg_num = ir.call_func(yyvsp[-3]->id, yyval->type, called_exps);
                                if (type == "BOOL") {
                                    ir.icmp_bool_var((BiNode*)yyval, yyval->reg_num);
                                }
	}
#line 1636 "parser.tab.cpp"
    break;

  case 38: /* Call: ID LPAREN RPAREN  */
#line 289 "parser.ypp"
                                   {
		                        cbr.emit("; Call->ID...");
								const string& type =  check_func_return_type(yyvsp[-2]->id);
                                if (type == "BOOL") {
                                    yyval = new BiNode();
                                }
                                yyval->type = type;
                                yyval->reg_num = ir.call_func(yyvsp[-2]->id, yyval->type, called_exps);
                                if (type == "BOOL") {
                                    ir.icmp_bool_var((BiNode*)yyval, yyval->reg_num);
                                }
							}
#line 1653 "parser.tab.cpp"
    break;

  case 39: /* ExpList: Exp  */
#line 303 "parser.ypp"
               {
			called_arg_types.push(yyvsp[0]->type);
			called_exps.push(pair<string, int>(yyvsp[0]->type, yyvsp[0]->reg_num));
			}
#line 1662 "parser.tab.cpp"
    break;

  case 40: /* ExpList: Exp COMMA ExpList  */
#line 307 "parser.ypp"
                                    {
			called_arg_types.push(yyvsp[-2]->type);
			called_exps.push(pair<string, int>(yyvsp[-2]->type, yyvsp[-2]->reg_num));
			}
#line 1671 "parser.tab.cpp"
    break;

  case 41: /* Type: INT  */
#line 312 "parser.ypp"
           { 
		yyval = new Node();
		yyval->type = "INT";
		}
#line 1680 "parser.tab.cpp"
    break;

  case 42: /* Type: BYTE  */
#line 316 "parser.ypp"
                        {
				yyval = new Node();
				yyval->type = "BYTE";
				}
#line 1689 "parser.tab.cpp"
    break;

  case 43: /* Type: BOOL  */
#line 320 "parser.ypp"
                        {
				yyval = new Node();
				yyval->type = "BOOL";
				}
#line 1698 "parser.tab.cpp"
    break;

  case 44: /* Exp: LPAREN Exp RPAREN  */
#line 326 "parser.ypp"
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
#line 1716 "parser.tab.cpp"
    break;

  case 45: /* Exp: Exp MUL Exp  */
#line 339 "parser.ypp"
                              {HANDLE_BINOP(yyvsp[-2], yyvsp[0], yyval, "MUL")}
#line 1722 "parser.tab.cpp"
    break;

  case 46: /* Exp: Exp DIV Exp  */
#line 340 "parser.ypp"
                              {HANDLE_BINOP(yyvsp[-2], yyvsp[0], yyval, "DIV")}
#line 1728 "parser.tab.cpp"
    break;

  case 47: /* Exp: Exp ADD Exp  */
#line 341 "parser.ypp"
                              {HANDLE_BINOP(yyvsp[-2], yyvsp[0], yyval, "ADD")}
#line 1734 "parser.tab.cpp"
    break;

  case 48: /* Exp: Exp SUB Exp  */
#line 342 "parser.ypp"
                              {HANDLE_BINOP(yyvsp[-2], yyvsp[0], yyval, "SUB")}
#line 1740 "parser.tab.cpp"
    break;

  case 49: /* Exp: Exp RELATION Exp  */
#line 343 "parser.ypp"
                                   {
			check_numeric(yyvsp[-2], yyvsp[0]);
			yyval = new BiNode();
			yyval->type = "BOOL";
			ir.relop((BiNode*)yyval, &(yyvsp[-2]->reg_num), &(yyvsp[0]->reg_num), yyvsp[-1]->type, yyvsp[-2]->type, yyvsp[0]->type);

			}
#line 1752 "parser.tab.cpp"
    break;

  case 50: /* Exp: Exp EQUALITY Exp  */
#line 350 "parser.ypp"
                                   {
				check_numeric(yyvsp[-2], yyvsp[0]);
				yyval = new BiNode();
				yyval->type = "BOOL";
				ir.relop((BiNode*)yyval, &(yyvsp[-2]->reg_num), &(yyvsp[0]->reg_num), yyvsp[-1]->type, yyvsp[-2]->type, yyvsp[0]->type);
				}
#line 1763 "parser.tab.cpp"
    break;

  case 51: /* Exp: Exp AND M Exp  */
#line 356 "parser.ypp"
                                {if (yyvsp[-3]->type != "BOOL" || yyvsp[0]->type != "BOOL") MISMATCH
				yyval = new BiNode();
				dynamic_cast<BiNode*>(yyval)->type = "BOOL";
				cbr.bpatch(dynamic_cast<BiNode*>(yyvsp[-3])->true_list, dynamic_cast<M*>(yyvsp[-1])->label);
				dynamic_cast<BiNode*>(yyval)->true_list = dynamic_cast<BiNode*>(yyvsp[0])->true_list;
				dynamic_cast<BiNode*>(yyval)->false_list = cbr.merge(dynamic_cast<BiNode*>(yyvsp[-3])->false_list, dynamic_cast<BiNode*>(yyvsp[0])->false_list);
				}
#line 1775 "parser.tab.cpp"
    break;

  case 52: /* Exp: Exp OR M Exp  */
#line 363 "parser.ypp"
                               {
				if (yyvsp[-3]->type != "BOOL" || yyvsp[0]->type != "BOOL") MISMATCH

				yyval = new BiNode();
				dynamic_cast<BiNode*>(yyval)->type = "BOOL";
				cbr.bpatch(dynamic_cast<BiNode*>(yyvsp[-3])->false_list, dynamic_cast<M*>(yyvsp[-1])->label);
				dynamic_cast<BiNode*>(yyval)->true_list = cbr.merge(dynamic_cast<BiNode*>(yyvsp[-3])->true_list, dynamic_cast<BiNode*>(yyvsp[0])->true_list);
				dynamic_cast<BiNode*>(yyval)->false_list = dynamic_cast<BiNode*>(yyvsp[0])->false_list;

		}
#line 1790 "parser.tab.cpp"
    break;

  case 53: /* Exp: NUM  */
#line 373 "parser.ypp"
                      {
				//$$ = new Node();
				yyval->type = "INT";
				ir.assign_reg("i32", yyval->value, yyval);
				}
#line 1800 "parser.tab.cpp"
    break;

  case 54: /* Exp: ID  */
#line 378 "parser.ypp"
                     { 
			const string& ty = check_var_return_type(yyvsp[0]->id);
			if (ty == "BOOL") 
				yyval = new BiNode();
			else
				yyval = new Node();
			
			yyval->type = ty;
			ir.load_local_var(get_entry(yyvsp[0]->id)->offset, yyval->type, yyval);
			if (ty == "BOOL") 
				ir.icmp_bool_var((BiNode*)yyval, yyval->reg_num);
		 }
#line 1817 "parser.tab.cpp"
    break;

  case 55: /* Exp: Call  */
#line 390 "parser.ypp"
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
#line 1835 "parser.tab.cpp"
    break;

  case 56: /* Exp: NUM B  */
#line 403 "parser.ypp"
                        {
			if (yyvsp[-1]->value > 255) {
				output::errorByteTooLarge(yylineno, to_string(yyvsp[-1]->value));
				exit(0);
			} 
			yyval->type = "BYTE";
			ir.assign_reg("i8", yyval->value, yyval);
			}
#line 1848 "parser.tab.cpp"
    break;

  case 57: /* Exp: STRING  */
#line 411 "parser.ypp"
                         {yyval = new Node();
				yyval->type = "STRING";}
#line 1855 "parser.tab.cpp"
    break;

  case 58: /* Exp: TRUE  */
#line 413 "parser.ypp"
                       { 
				yyval = new BiNode();
				yyval->type = "BOOL";
				yyval->value = 1;
				int loc = cbr.emit("\tbr label @");
    			dynamic_cast<BiNode*>(yyval)->true_list = cbr.makelist({loc, FIRST});
				}
#line 1867 "parser.tab.cpp"
    break;

  case 59: /* Exp: FALSE  */
#line 420 "parser.ypp"
                        {yyval = new BiNode();
				yyval->type = "BOOL";
				yyval->value = 0;
				int loc = cbr.emit("\tbr label @");
				dynamic_cast<BiNode*>(yyval)->false_list = cbr.makelist({loc, FIRST});
				
				}
#line 1879 "parser.tab.cpp"
    break;

  case 60: /* Exp: NOT Exp  */
#line 427 "parser.ypp"
                          {
				if (yyvsp[0]->type != "BOOL") MISMATCH
				yyval = new BiNode();
				yyval->type = "BOOL";
				dynamic_cast<BiNode*>(yyval)->true_list = dynamic_cast<BiNode*>(yyvsp[0])->false_list;
				dynamic_cast<BiNode*>(yyval)->false_list = dynamic_cast<BiNode*>(yyvsp[0])->true_list;
		}
#line 1891 "parser.tab.cpp"
    break;

  case 61: /* CaseDecl: CASE NUM COLON M Statements N  */
#line 436 "parser.ypp"
                                         {
	string quad = dynamic_cast<M*>(yyvsp[-2])->label;
	yyval = new C();
	dynamic_cast<C*>(yyval)->quad = quad;
	dynamic_cast<C*>(yyval)->value = yyvsp[-4]->value;
	dynamic_cast<C*>(yyval)->next_list = yyvsp[0]->next_list;
}
#line 1903 "parser.tab.cpp"
    break;

  case 62: /* CaseList: CaseDecl CaseList  */
#line 445 "parser.ypp"
                             {
	yyval = new CL();
	auto cl1 = dynamic_cast<CL*>(yyvsp[0]);
	auto c = dynamic_cast<C*>(yyvsp[-1]);
	dynamic_cast<CL*>(yyval)->quad_list = cl1->quad_list;
	dynamic_cast<CL*>(yyval)->quad_list.push(c->quad);
	dynamic_cast<CL*>(yyval)->value_list = cl1->value_list;
	dynamic_cast<CL*>(yyval)->value_list.push(c->value);
	dynamic_cast<CL*>(yyval)->next_list = cbr.merge(cl1->next_list, c->next_list);
	dynamic_cast<CL*>(yyval)->default_label = cl1->default_label;}
#line 1918 "parser.tab.cpp"
    break;

  case 63: /* CaseList: CaseDecl  */
#line 455 "parser.ypp"
                           {
			yyval = new CL();
			auto c = dynamic_cast<C*>(yyvsp[0]);
			dynamic_cast<CL*>(yyval)->quad_list.push(c->quad);
			dynamic_cast<CL*>(yyval)->value_list.push(c->value);
			dynamic_cast<CL*>(yyval)->next_list = c->next_list;
		}
#line 1930 "parser.tab.cpp"
    break;

  case 64: /* CaseList: DEFAULT COLON M Statements N  */
#line 462 "parser.ypp"
                                               {
			string quad = dynamic_cast<M*>(yyvsp[-2])->label;
			yyval = new CL();
			dynamic_cast<CL*>(yyval)->default_label = quad;
			dynamic_cast<CL*>(yyval)->next_list = yyvsp[0]->next_list;
		}
#line 1941 "parser.tab.cpp"
    break;


#line 1945 "parser.tab.cpp"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

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


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 470 "parser.ypp"


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
		ir.emit_print_functions();
		yyparse();
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

