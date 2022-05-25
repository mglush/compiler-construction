/* A Bison parser, made by GNU Bison 3.7.4.  */

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
#define YYBISON 30704

/* Bison version string.  */
#define YYBISON_VERSION "3.7.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

    #include <stdio.h>
    #include <stdlib.h>
    #include <iostream>

    #include "ast.hpp"
    
    #define YYDEBUG 1
    #define YYINITDEPTH 10000

    int yylex(void);
    void yyerror(const char *);
    
    extern ASTNode* astRoot;
    

#line 88 "parser.cpp"

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

#include "parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_t_print = 3,                    /* t_print  */
  YYSYMBOL_t_return = 4,                   /* t_return  */
  YYSYMBOL_t_if = 5,                       /* t_if  */
  YYSYMBOL_t_else = 6,                     /* t_else  */
  YYSYMBOL_t_while = 7,                    /* t_while  */
  YYSYMBOL_t_new = 8,                      /* t_new  */
  YYSYMBOL_t_equals = 9,                   /* t_equals  */
  YYSYMBOL_t_and = 10,                     /* t_and  */
  YYSYMBOL_t_or = 11,                      /* t_or  */
  YYSYMBOL_t_not = 12,                     /* t_not  */
  YYSYMBOL_t_extends = 13,                 /* t_extends  */
  YYSYMBOL_t_do = 14,                      /* t_do  */
  YYSYMBOL_t_true = 15,                    /* t_true  */
  YYSYMBOL_t_false = 16,                   /* t_false  */
  YYSYMBOL_17_ = 17,                       /* ';'  */
  YYSYMBOL_18_ = 18,                       /* ','  */
  YYSYMBOL_t_arrow = 19,                   /* t_arrow  */
  YYSYMBOL_20_ = 20,                       /* '{'  */
  YYSYMBOL_21_ = 21,                       /* '}'  */
  YYSYMBOL_22_ = 22,                       /* '('  */
  YYSYMBOL_23_ = 23,                       /* ')'  */
  YYSYMBOL_24_ = 24,                       /* '+'  */
  YYSYMBOL_25_ = 25,                       /* '-'  */
  YYSYMBOL_26_ = 26,                       /* '*'  */
  YYSYMBOL_27_ = 27,                       /* '/'  */
  YYSYMBOL_t_geq = 28,                     /* t_geq  */
  YYSYMBOL_29_ = 29,                       /* '>'  */
  YYSYMBOL_30_ = 30,                       /* '='  */
  YYSYMBOL_unary_minus = 31,               /* unary_minus  */
  YYSYMBOL_t_id = 32,                      /* t_id  */
  YYSYMBOL_t_int_type = 33,                /* t_int_type  */
  YYSYMBOL_t_bool_type = 34,               /* t_bool_type  */
  YYSYMBOL_t_none_type = 35,               /* t_none_type  */
  YYSYMBOL_t_number = 36,                  /* t_number  */
  YYSYMBOL_37_ = 37,                       /* '.'  */
  YYSYMBOL_YYACCEPT = 38,                  /* $accept  */
  YYSYMBOL_Start = 39,                     /* Start  */
  YYSYMBOL_ClassList = 40,                 /* ClassList  */
  YYSYMBOL_Class = 41,                     /* Class  */
  YYSYMBOL_DeclarationList = 42,           /* DeclarationList  */
  YYSYMBOL_MethodList = 43,                /* MethodList  */
  YYSYMBOL_MemberNames = 44,               /* MemberNames  */
  YYSYMBOL_NesMethodName = 45,             /* NesMethodName  */
  YYSYMBOL_Parameters = 46,                /* Parameters  */
  YYSYMBOL_ParametersRest = 47,            /* ParametersRest  */
  YYSYMBOL_Parameter = 48,                 /* Parameter  */
  YYSYMBOL_Type = 49,                      /* Type  */
  YYSYMBOL_MethodBodyList = 50,            /* MethodBodyList  */
  YYSYMBOL_MethodBodyReturn = 51,          /* MethodBodyReturn  */
  YYSYMBOL_Statement = 52,                 /* Statement  */
  YYSYMBOL_MethodCallInputs = 53,          /* MethodCallInputs  */
  YYSYMBOL_MethodCallInputsRest = 54,      /* MethodCallInputsRest  */
  YYSYMBOL_MethodCallInput = 55,           /* MethodCallInput  */
  YYSYMBOL_Block = 56,                     /* Block  */
  YYSYMBOL_Expression = 57,                /* Expression  */
  YYSYMBOL_MethodCall = 58,                /* MethodCall  */
  YYSYMBOL_ClassName = 59,                 /* ClassName  */
  YYSYMBOL_MemberName = 60,                /* MemberName  */
  YYSYMBOL_MethodName = 61,                /* MethodName  */
  YYSYMBOL_first_id = 62                   /* first_id  */
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

#if 1

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
#endif /* 1 */

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   515

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  89
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  202

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   279


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
      22,    23,    26,    24,    18,    25,    37,    27,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    17,
       2,    30,    29,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    20,     2,    21,     2,     2,     2,     2,
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
      15,    16,    19,    28,    31,    32,    33,    34,    35,    36
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    90,    90,    95,    97,   101,   103,   105,   107,   109,
     111,   113,   115,   119,   121,   125,   127,   129,   131,   133,
     135,   137,   139,   141,   143,   145,   147,   149,   151,   153,
     155,   159,   161,   165,   167,   171,   173,   177,   179,   183,
     187,   189,   191,   193,   197,   199,   203,   207,   209,   211,
     213,   215,   217,   219,   221,   223,   227,   229,   233,   235,
     239,   242,   244,   248,   250,   252,   254,   256,   258,   260,
     262,   264,   266,   268,   270,   272,   274,   276,   278,   280,
     282,   284,   286,   288,   292,   294,   298,   301,   304,   307
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "t_print", "t_return",
  "t_if", "t_else", "t_while", "t_new", "t_equals", "t_and", "t_or",
  "t_not", "t_extends", "t_do", "t_true", "t_false", "';'", "','",
  "t_arrow", "'{'", "'}'", "'('", "')'", "'+'", "'-'", "'*'", "'/'",
  "t_geq", "'>'", "'='", "unary_minus", "t_id", "t_int_type",
  "t_bool_type", "t_none_type", "t_number", "'.'", "$accept", "Start",
  "ClassList", "Class", "DeclarationList", "MethodList", "MemberNames",
  "NesMethodName", "Parameters", "ParametersRest", "Parameter", "Type",
  "MethodBodyList", "MethodBodyReturn", "Statement", "MethodCallInputs",
  "MethodCallInputsRest", "MethodCallInput", "Block", "Expression",
  "MethodCall", "ClassName", "MemberName", "MethodName", "first_id", YY_NULLPTR
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
     265,   266,   267,   268,   269,   270,   271,    59,    44,   272,
     123,   125,    40,    41,    43,    45,    42,    47,   273,    62,
      61,   274,   275,   276,   277,   278,   279,    46
};
#endif

#define YYPACT_NINF (-158)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-89)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -158,     3,     0,  -158,  -158,     5,    11,  -158,     0,   106,
      19,  -158,  -158,  -158,  -158,   232,    69,     0,    22,    23,
     260,  -158,    71,     0,  -158,    29,  -158,     7,  -158,   150,
    -158,   327,    77,  -158,     7,   150,     0,    37,    33,    50,
       0,  -158,  -158,    86,  -158,    53,    49,     7,  -158,    66,
     150,  -158,  -158,  -158,  -158,    80,  -158,   150,    50,   150,
      92,  -158,    96,   121,   228,   309,   309,   309,   309,    97,
    -158,   236,    99,    79,    81,  -158,   102,   101,   159,  -158,
     270,   275,   110,     0,   309,  -158,  -158,   309,   309,  -158,
     326,  -158,    27,   347,   357,   369,   183,  -158,   294,   116,
     309,  -158,   122,  -158,   -14,  -158,  -158,   309,     0,   309,
       0,  -158,   306,   130,  -158,   131,  -158,   138,  -158,   381,
    -158,   309,   309,   309,  -158,   309,   309,   309,   309,   309,
     309,     0,     0,  -158,   183,   183,   183,  -158,   140,  -158,
     139,   149,   474,  -158,   145,   157,   402,   164,  -158,   151,
    -158,  -158,   309,  -158,   220,   486,   465,   -15,   -15,  -158,
    -158,   220,   220,   153,   158,   183,   183,   183,   177,  -158,
    -158,   309,  -158,  -158,   309,  -158,   309,  -158,   156,   179,
     181,  -158,   199,   149,   423,   444,  -158,   210,  -158,   195,
    -158,  -158,  -158,   198,   309,   183,   453,   183,   206,   203,
    -158,  -158
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     1,    89,     2,     0,    86,     0,     0,
       0,    12,    40,    41,    42,     0,     0,     0,     0,    43,
       0,     8,     0,     0,    10,     0,    88,    32,    87,    36,
      11,     0,     0,     6,    32,    36,     0,     0,     0,    38,
       0,    43,     7,     0,     9,     0,     0,    32,    14,     0,
       0,    35,    39,     5,    13,     0,    31,     0,    38,     0,
       0,    37,     0,     0,     0,     0,     0,     0,     0,     0,
      30,     0,     0,     0,     0,    45,     0,     0,    43,    29,
       0,     0,     0,     0,     0,    80,    81,     0,     0,    79,
       0,    77,    74,     0,     0,     0,     0,    24,     0,     0,
      57,    26,     0,    44,    88,    28,    50,    57,     0,     0,
       0,    23,     0,     0,    25,     0,    27,    82,    72,     0,
      73,     0,     0,     0,    55,     0,     0,     0,     0,     0,
       0,     0,     0,    46,     0,     0,    62,    22,     0,    20,
       0,    59,    60,    18,     0,    34,     0,    33,    21,     0,
      19,    17,    57,    78,    69,    70,    71,    63,    64,    65,
      66,    68,    67,    76,    75,    62,    62,    62,     0,    16,
      85,     0,    56,    84,     0,    47,     0,    15,     0,     0,
       0,    61,     0,    59,     0,     0,    83,    51,    53,     0,
      58,    49,    48,     0,     0,     0,     0,    62,     0,     0,
      54,    52
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -158,  -158,  -158,  -158,     2,    43,   -30,  -158,   191,   170,
     180,   142,     9,   -45,    24,  -105,    46,    63,  -157,    82,
     -21,    -7,   215,   205,    -2
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     5,    15,    16,    37,    72,    38,    51,
      39,    17,    73,    74,   167,   140,   172,   141,   168,   142,
      91,     6,    27,    77,    92
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       7,    10,   144,     3,    45,   108,     7,    19,   179,   180,
     181,   127,   128,    19,    26,    28,   109,    56,    19,    82,
      26,    28,    31,   110,     8,    36,    99,    41,   102,    19,
      26,     9,     4,    41,    47,   113,   115,    -3,    52,    20,
     199,    26,    76,    76,    29,   -88,   131,   178,    41,   -88,
      76,    35,    76,   138,    48,    41,    49,    41,    22,    76,
      76,    78,    78,    32,   132,    71,    80,   149,    50,    78,
      54,   104,    55,    81,    43,    76,   117,    76,    78,   104,
      98,     7,    65,    66,    67,    57,    68,    75,    75,   112,
      24,    76,    33,    69,   104,    75,   104,   103,    44,    59,
     101,     4,   105,     4,    75,   103,   145,    53,   147,     4,
     104,     4,    63,    76,    76,    76,    64,    96,     4,   106,
     136,   100,   103,   107,    65,    66,    67,    11,    68,   163,
     164,   116,   104,   104,   104,    69,   103,   139,     4,    12,
      13,    14,    70,   143,    76,    76,    76,    90,    93,    94,
      95,   150,   151,     4,    12,    13,    14,    23,   165,   166,
     152,   169,   170,   104,   104,   104,   118,   171,   173,   119,
     120,    40,   177,    23,    76,   -34,    76,    40,   108,   186,
     -33,   -88,     4,    12,    13,    14,    65,   174,    67,   109,
      68,   146,    40,   104,   176,   104,   110,    69,   182,    60,
     187,    62,   188,   154,   155,   156,   189,   157,   158,   159,
     160,   161,   162,    23,    18,     4,   193,   194,   195,   197,
      18,    25,    23,   200,   201,    18,    46,    25,    61,   190,
      58,    65,    66,    67,   183,    68,    18,    25,    34,    65,
      66,    67,    69,    68,   125,   126,   127,   128,    25,    79,
      69,     0,     0,    21,     0,     0,   184,    97,   185,     0,
       4,    12,    13,    14,     4,    12,    13,    14,     4,    12,
      13,    14,     0,    65,    66,    67,   196,    68,    65,    66,
      67,    30,    68,     0,    69,     0,     0,     0,     0,    69,
       0,   111,     4,    12,    13,    14,   114,    65,    66,    67,
       0,    68,     4,    12,    13,    14,     0,     4,    69,    65,
      66,    67,     0,    68,     0,   137,     0,    83,     0,     0,
      69,    84,     0,     0,    85,    86,     4,   148,     0,     0,
       0,    87,     0,     0,    88,   121,   122,   123,     4,     0,
       0,     4,     0,   124,     0,    89,     0,     0,    42,     0,
     125,   126,   127,   128,   129,   130,   121,   122,   123,     4,
      12,    13,    14,     0,   133,     0,   121,   122,   123,     0,
       0,   125,   126,   127,   128,   129,   130,   134,   121,   122,
     123,   125,   126,   127,   128,   129,   130,     0,     0,   135,
     121,   122,   123,   125,   126,   127,   128,   129,   130,     0,
       0,     0,     0,     0,   153,   125,   126,   127,   128,   129,
     130,   121,   122,   123,     0,     0,     0,     0,     0,   175,
       0,     0,     0,     0,     0,     0,   125,   126,   127,   128,
     129,   130,   121,   122,   123,     0,     0,     0,     0,     0,
     191,     0,     0,     0,     0,     0,     0,   125,   126,   127,
     128,   129,   130,   121,   122,   123,     0,     0,     0,     0,
       0,   192,   121,   122,   123,     0,     0,     0,   125,   126,
     127,   128,   129,   130,   121,   122,   198,   125,   126,   127,
     128,   129,   130,   121,   122,   123,     0,     0,     0,   125,
     126,   127,   128,   129,   130,   121,     0,     0,   125,   126,
     127,   128,   129,   130,     0,     0,     0,     0,     0,     0,
     125,   126,   127,   128,   129,   130
};

static const yytype_int16 yycheck[] =
{
       2,     8,   107,     0,    34,    19,     8,     9,   165,   166,
     167,    26,    27,    15,    16,    17,    30,    47,    20,    64,
      22,    23,    20,    37,    13,    18,    71,    29,    73,    31,
      32,    20,    32,    35,    36,    80,    81,    32,    40,    20,
     197,    43,    63,    64,    22,    22,    19,   152,    50,    22,
      71,    22,    73,    98,    17,    57,    23,    59,    15,    80,
      81,    63,    64,    20,    37,    63,    64,   112,    18,    71,
      17,    73,    23,    64,    31,    96,    83,    98,    80,    81,
      71,    83,     3,     4,     5,    19,     7,    63,    64,    80,
      21,   112,    21,    14,    96,    71,    98,    73,    21,    19,
      21,    32,    21,    32,    80,    81,   108,    21,   110,    32,
     112,    32,    20,   134,   135,   136,    20,    20,    32,    17,
      96,    22,    98,    22,     3,     4,     5,    21,     7,   131,
     132,    21,   134,   135,   136,    14,   112,    21,    32,    33,
      34,    35,    21,    21,   165,   166,   167,    65,    66,    67,
      68,    21,    21,    32,    33,    34,    35,    15,   134,   135,
      22,    21,    23,   165,   166,   167,    84,    18,    23,    87,
      88,    29,    21,    31,   195,    22,   197,    35,    19,    23,
      22,    22,    32,    33,    34,    35,     3,    30,     5,    30,
       7,   109,    50,   195,    30,   197,    37,    14,    21,    57,
      21,    59,    21,   121,   122,   123,     7,   125,   126,   127,
     128,   129,   130,    71,     9,    32,     6,    22,    20,   195,
      15,    16,    80,    17,    21,    20,    35,    22,    58,   183,
      50,     3,     4,     5,   171,     7,    31,    32,    23,     3,
       4,     5,    14,     7,    24,    25,    26,    27,    43,    21,
      14,    -1,    -1,    21,    -1,    -1,   174,    21,   176,    -1,
      32,    33,    34,    35,    32,    33,    34,    35,    32,    33,
      34,    35,    -1,     3,     4,     5,   194,     7,     3,     4,
       5,    21,     7,    -1,    14,    -1,    -1,    -1,    -1,    14,
      -1,    21,    32,    33,    34,    35,    21,     3,     4,     5,
      -1,     7,    32,    33,    34,    35,    -1,    32,    14,     3,
       4,     5,    -1,     7,    -1,    21,    -1,     8,    -1,    -1,
      14,    12,    -1,    -1,    15,    16,    32,    21,    -1,    -1,
      -1,    22,    -1,    -1,    25,     9,    10,    11,    32,    -1,
      -1,    32,    -1,    17,    -1,    36,    -1,    -1,    21,    -1,
      24,    25,    26,    27,    28,    29,     9,    10,    11,    32,
      33,    34,    35,    -1,    17,    -1,     9,    10,    11,    -1,
      -1,    24,    25,    26,    27,    28,    29,    20,     9,    10,
      11,    24,    25,    26,    27,    28,    29,    -1,    -1,    20,
       9,    10,    11,    24,    25,    26,    27,    28,    29,    -1,
      -1,    -1,    -1,    -1,    23,    24,    25,    26,    27,    28,
      29,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,    17,
      -1,    -1,    -1,    -1,    -1,    -1,    24,    25,    26,    27,
      28,    29,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,
      17,    -1,    -1,    -1,    -1,    -1,    -1,    24,    25,    26,
      27,    28,    29,     9,    10,    11,    -1,    -1,    -1,    -1,
      -1,    17,     9,    10,    11,    -1,    -1,    -1,    24,    25,
      26,    27,    28,    29,     9,    10,    23,    24,    25,    26,
      27,    28,    29,     9,    10,    11,    -1,    -1,    -1,    24,
      25,    26,    27,    28,    29,     9,    -1,    -1,    24,    25,
      26,    27,    28,    29,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    25,    26,    27,    28,    29
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    39,    40,     0,    32,    41,    59,    62,    13,    20,
      59,    21,    33,    34,    35,    42,    43,    49,    61,    62,
      20,    21,    43,    49,    21,    61,    62,    60,    62,    22,
      21,    42,    43,    21,    60,    22,    18,    44,    46,    48,
      49,    62,    21,    43,    21,    44,    46,    62,    17,    23,
      18,    47,    62,    21,    17,    23,    44,    19,    48,    19,
      49,    47,    49,    20,    20,     3,     4,     5,     7,    14,
      21,    42,    45,    50,    51,    52,    58,    61,    62,    21,
      42,    50,    51,     8,    12,    15,    16,    22,    25,    36,
      57,    58,    62,    57,    57,    57,    20,    21,    50,    51,
      22,    21,    51,    52,    62,    21,    17,    22,    19,    30,
      37,    21,    50,    51,    21,    51,    21,    59,    57,    57,
      57,     9,    10,    11,    17,    24,    25,    26,    27,    28,
      29,    19,    37,    17,    20,    20,    52,    21,    51,    21,
      53,    55,    57,    21,    53,    62,    57,    62,    21,    51,
      21,    21,    22,    23,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    62,    62,    52,    52,    52,    56,    21,
      23,    18,    54,    23,    30,    17,    30,    21,    53,    56,
      56,    56,    21,    55,    57,    57,    23,    21,    21,     7,
      54,    17,    17,     6,    22,    20,    57,    52,    23,    56,
      17,    21
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    38,    39,    40,    40,    41,    41,    41,    41,    41,
      41,    41,    41,    42,    42,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    44,    44,    45,    45,    46,    46,    47,    47,    48,
      49,    49,    49,    49,    50,    50,    51,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    53,    53,    54,    54,
      55,    56,    56,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    58,    58,    59,    60,    61,    62
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     0,     7,     5,     6,     4,     6,
       4,     5,     3,     5,     4,    12,    11,    11,    10,    11,
      10,    11,    10,    10,     9,    10,     9,    10,     9,     9,
       8,     3,     0,     3,     3,     2,     0,     3,     0,     2,
       1,     1,     1,     1,     2,     1,     3,     4,     6,     6,
       2,     6,    11,     6,    10,     3,     2,     0,     3,     0,
       1,     2,     0,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     1,     3,     3,     1,     3,     1,
       1,     1,     2,     5,     4,     4,     1,     1,     1,     1
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
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
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
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
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
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
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


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
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

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

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
  case 2: /* Start: ClassList Class  */
#line 91 "parser.y"
                          { (yyvsp[-1].class_list_ptr)->push_back((yyvsp[0].class_ptr)); (yyval.program_ptr) = new ProgramNode((yyvsp[-1].class_list_ptr)); astRoot = (yyval.program_ptr); }
#line 1592 "parser.cpp"
    break;

  case 3: /* ClassList: ClassList Class  */
#line 96 "parser.y"
                          { (yyval.class_list_ptr) = (yyvsp[-1].class_list_ptr); (yyval.class_list_ptr)->push_back((yyvsp[0].class_ptr)); }
#line 1598 "parser.cpp"
    break;

  case 4: /* ClassList: %empty  */
#line 98 "parser.y"
                          { (yyval.class_list_ptr) = new std::list<ClassNode*>(); }
#line 1604 "parser.cpp"
    break;

  case 5: /* Class: ClassName t_extends ClassName '{' DeclarationList MethodList '}'  */
#line 102 "parser.y"
                          { (yyval.class_ptr) = new ClassNode((yyvsp[-6].identifier_ptr), (yyvsp[-4].identifier_ptr), (yyvsp[-2].declaration_list_ptr), (yyvsp[-1].method_list_ptr)); }
#line 1610 "parser.cpp"
    break;

  case 6: /* Class: ClassName '{' DeclarationList MethodList '}'  */
#line 104 "parser.y"
                          { (yyval.class_ptr) = new ClassNode((yyvsp[-4].identifier_ptr), NULL, (yyvsp[-2].declaration_list_ptr), (yyvsp[-1].method_list_ptr)); }
#line 1616 "parser.cpp"
    break;

  case 7: /* Class: ClassName t_extends ClassName '{' DeclarationList '}'  */
#line 106 "parser.y"
                          { (yyval.class_ptr) = new ClassNode((yyvsp[-5].identifier_ptr), (yyvsp[-3].identifier_ptr), (yyvsp[-1].declaration_list_ptr), NULL); }
#line 1622 "parser.cpp"
    break;

  case 8: /* Class: ClassName '{' DeclarationList '}'  */
#line 108 "parser.y"
                          { (yyval.class_ptr) = new ClassNode((yyvsp[-3].identifier_ptr), NULL, (yyvsp[-1].declaration_list_ptr), NULL); }
#line 1628 "parser.cpp"
    break;

  case 9: /* Class: ClassName t_extends ClassName '{' MethodList '}'  */
#line 110 "parser.y"
                          { (yyval.class_ptr) = new ClassNode((yyvsp[-5].identifier_ptr), (yyvsp[-3].identifier_ptr), NULL, (yyvsp[-1].method_list_ptr)); }
#line 1634 "parser.cpp"
    break;

  case 10: /* Class: ClassName '{' MethodList '}'  */
#line 112 "parser.y"
                          { (yyval.class_ptr) = new ClassNode((yyvsp[-3].identifier_ptr), NULL, NULL, (yyvsp[-1].method_list_ptr)); }
#line 1640 "parser.cpp"
    break;

  case 11: /* Class: ClassName t_extends ClassName '{' '}'  */
#line 114 "parser.y"
                          { (yyval.class_ptr) = new ClassNode((yyvsp[-4].identifier_ptr), (yyvsp[-2].identifier_ptr), NULL, NULL); }
#line 1646 "parser.cpp"
    break;

  case 12: /* Class: ClassName '{' '}'  */
#line 116 "parser.y"
                          { (yyval.class_ptr) = new ClassNode((yyvsp[-2].identifier_ptr), NULL, NULL, NULL); }
#line 1652 "parser.cpp"
    break;

  case 13: /* DeclarationList: DeclarationList Type MemberName MemberNames ';'  */
#line 120 "parser.y"
                          { (yyval.declaration_list_ptr) = (yyvsp[-4].declaration_list_ptr); (yyvsp[-1].identifier_list_ptr)->push_front((yyvsp[-2].identifier_ptr)); (yyval.declaration_list_ptr)->push_back(new DeclarationNode((yyvsp[-3].type_ptr), (yyvsp[-1].identifier_list_ptr))); }
#line 1658 "parser.cpp"
    break;

  case 14: /* DeclarationList: Type MemberName MemberNames ';'  */
#line 122 "parser.y"
                          { (yyval.declaration_list_ptr) = new std::list<DeclarationNode*>(); (yyvsp[-1].identifier_list_ptr)->push_front((yyvsp[-2].identifier_ptr)); (yyval.declaration_list_ptr)->push_back(new DeclarationNode((yyvsp[-3].type_ptr), (yyvsp[-1].identifier_list_ptr))); }
#line 1664 "parser.cpp"
    break;

  case 15: /* MethodList: MethodList MethodName '(' Parameters ')' t_arrow Type '{' DeclarationList MethodBodyList MethodBodyReturn '}'  */
#line 126 "parser.y"
                          { (yyval.method_list_ptr) = (yyvsp[-11].method_list_ptr); (yyval.method_list_ptr)->push_back(new MethodNode((yyvsp[-10].identifier_ptr), (yyvsp[-8].parameter_list_ptr), (yyvsp[-5].type_ptr), new MethodBodyNode((yyvsp[-3].declaration_list_ptr), (yyvsp[-2].statement_list_ptr), (yyvsp[-1].returnstatement_ptr)))); }
#line 1670 "parser.cpp"
    break;

  case 16: /* MethodList: MethodName '(' Parameters ')' t_arrow Type '{' DeclarationList MethodBodyList MethodBodyReturn '}'  */
#line 128 "parser.y"
                          { (yyval.method_list_ptr) = new std::list<MethodNode*>(); (yyval.method_list_ptr)->push_back(new MethodNode((yyvsp[-10].identifier_ptr), (yyvsp[-8].parameter_list_ptr), (yyvsp[-5].type_ptr), new MethodBodyNode((yyvsp[-3].declaration_list_ptr), (yyvsp[-2].statement_list_ptr), (yyvsp[-1].returnstatement_ptr)))); }
#line 1676 "parser.cpp"
    break;

  case 17: /* MethodList: MethodList MethodName '(' Parameters ')' t_arrow Type '{' MethodBodyList MethodBodyReturn '}'  */
#line 130 "parser.y"
                          { (yyval.method_list_ptr) = (yyvsp[-10].method_list_ptr); (yyval.method_list_ptr)->push_back(new MethodNode((yyvsp[-9].identifier_ptr), (yyvsp[-7].parameter_list_ptr), (yyvsp[-4].type_ptr), new MethodBodyNode(NULL, (yyvsp[-2].statement_list_ptr), (yyvsp[-1].returnstatement_ptr)))); }
#line 1682 "parser.cpp"
    break;

  case 18: /* MethodList: MethodName '(' Parameters ')' t_arrow Type '{' MethodBodyList MethodBodyReturn '}'  */
#line 132 "parser.y"
                          { (yyval.method_list_ptr) = new std::list<MethodNode*>(); (yyval.method_list_ptr)->push_back(new MethodNode((yyvsp[-9].identifier_ptr), (yyvsp[-7].parameter_list_ptr), (yyvsp[-4].type_ptr), new MethodBodyNode(NULL, (yyvsp[-2].statement_list_ptr), (yyvsp[-1].returnstatement_ptr)))); }
#line 1688 "parser.cpp"
    break;

  case 19: /* MethodList: MethodList MethodName '(' Parameters ')' t_arrow Type '{' DeclarationList MethodBodyReturn '}'  */
#line 134 "parser.y"
                          { (yyval.method_list_ptr) = (yyvsp[-10].method_list_ptr); (yyval.method_list_ptr)->push_back(new MethodNode((yyvsp[-9].identifier_ptr), (yyvsp[-7].parameter_list_ptr), (yyvsp[-4].type_ptr), new MethodBodyNode((yyvsp[-2].declaration_list_ptr), NULL, (yyvsp[-1].returnstatement_ptr)))); }
#line 1694 "parser.cpp"
    break;

  case 20: /* MethodList: MethodName '(' Parameters ')' t_arrow Type '{' DeclarationList MethodBodyReturn '}'  */
#line 136 "parser.y"
                          { (yyval.method_list_ptr) = new std::list<MethodNode*>(); (yyval.method_list_ptr)->push_back(new MethodNode((yyvsp[-9].identifier_ptr), (yyvsp[-7].parameter_list_ptr), (yyvsp[-4].type_ptr), new MethodBodyNode((yyvsp[-2].declaration_list_ptr), NULL, (yyvsp[-1].returnstatement_ptr)))); }
#line 1700 "parser.cpp"
    break;

  case 21: /* MethodList: MethodList MethodName '(' Parameters ')' t_arrow Type '{' DeclarationList MethodBodyList '}'  */
#line 138 "parser.y"
                          { (yyval.method_list_ptr) = (yyvsp[-10].method_list_ptr); (yyval.method_list_ptr)->push_back(new MethodNode((yyvsp[-9].identifier_ptr), (yyvsp[-7].parameter_list_ptr), (yyvsp[-4].type_ptr), new MethodBodyNode((yyvsp[-2].declaration_list_ptr), (yyvsp[-1].statement_list_ptr), NULL))); }
#line 1706 "parser.cpp"
    break;

  case 22: /* MethodList: MethodName '(' Parameters ')' t_arrow Type '{' DeclarationList MethodBodyList '}'  */
#line 140 "parser.y"
                          { (yyval.method_list_ptr) = new std::list<MethodNode*>(); (yyval.method_list_ptr)->push_back(new MethodNode((yyvsp[-9].identifier_ptr), (yyvsp[-7].parameter_list_ptr), (yyvsp[-4].type_ptr), new MethodBodyNode((yyvsp[-2].declaration_list_ptr), (yyvsp[-1].statement_list_ptr), NULL))); }
#line 1712 "parser.cpp"
    break;

  case 23: /* MethodList: MethodList MethodName '(' Parameters ')' t_arrow Type '{' DeclarationList '}'  */
#line 142 "parser.y"
                          { (yyval.method_list_ptr) = (yyvsp[-9].method_list_ptr); (yyval.method_list_ptr)->push_back(new MethodNode((yyvsp[-8].identifier_ptr), (yyvsp[-6].parameter_list_ptr), (yyvsp[-3].type_ptr), new MethodBodyNode((yyvsp[-1].declaration_list_ptr), NULL, NULL))); }
#line 1718 "parser.cpp"
    break;

  case 24: /* MethodList: MethodName '(' Parameters ')' t_arrow Type '{' DeclarationList '}'  */
#line 144 "parser.y"
                          { (yyval.method_list_ptr) = new std::list<MethodNode*>(); (yyval.method_list_ptr)->push_back(new MethodNode((yyvsp[-8].identifier_ptr), (yyvsp[-6].parameter_list_ptr), (yyvsp[-3].type_ptr), new MethodBodyNode((yyvsp[-1].declaration_list_ptr), NULL, NULL))); }
#line 1724 "parser.cpp"
    break;

  case 25: /* MethodList: MethodList MethodName '(' Parameters ')' t_arrow Type '{' MethodBodyList '}'  */
#line 146 "parser.y"
                          { (yyval.method_list_ptr) = (yyvsp[-9].method_list_ptr); (yyval.method_list_ptr)->push_back(new MethodNode((yyvsp[-8].identifier_ptr), (yyvsp[-6].parameter_list_ptr), (yyvsp[-3].type_ptr), new MethodBodyNode(NULL, (yyvsp[-1].statement_list_ptr), NULL))); }
#line 1730 "parser.cpp"
    break;

  case 26: /* MethodList: MethodName '(' Parameters ')' t_arrow Type '{' MethodBodyList '}'  */
#line 148 "parser.y"
                          { (yyval.method_list_ptr) = new std::list<MethodNode*>(); (yyval.method_list_ptr)->push_back(new MethodNode((yyvsp[-8].identifier_ptr), (yyvsp[-6].parameter_list_ptr), (yyvsp[-3].type_ptr), new MethodBodyNode(NULL, (yyvsp[-1].statement_list_ptr), NULL))); }
#line 1736 "parser.cpp"
    break;

  case 27: /* MethodList: MethodList MethodName '(' Parameters ')' t_arrow Type '{' MethodBodyReturn '}'  */
#line 150 "parser.y"
                          { (yyval.method_list_ptr) = (yyvsp[-9].method_list_ptr); (yyval.method_list_ptr)->push_back(new MethodNode((yyvsp[-8].identifier_ptr), (yyvsp[-6].parameter_list_ptr), (yyvsp[-3].type_ptr), new MethodBodyNode(NULL, NULL, (yyvsp[-1].returnstatement_ptr)))); }
#line 1742 "parser.cpp"
    break;

  case 28: /* MethodList: MethodName '(' Parameters ')' t_arrow Type '{' MethodBodyReturn '}'  */
#line 152 "parser.y"
                          { (yyval.method_list_ptr) = new std::list<MethodNode*>(); (yyval.method_list_ptr)->push_back(new MethodNode((yyvsp[-8].identifier_ptr), (yyvsp[-6].parameter_list_ptr), (yyvsp[-3].type_ptr), new MethodBodyNode(NULL, NULL, (yyvsp[-1].returnstatement_ptr)))); }
#line 1748 "parser.cpp"
    break;

  case 29: /* MethodList: MethodList MethodName '(' Parameters ')' t_arrow Type '{' '}'  */
#line 154 "parser.y"
                          { (yyval.method_list_ptr) = (yyvsp[-8].method_list_ptr); (yyval.method_list_ptr)->push_back(new MethodNode((yyvsp[-7].identifier_ptr), (yyvsp[-5].parameter_list_ptr), (yyvsp[-2].type_ptr), new MethodBodyNode(NULL, NULL, NULL))); }
#line 1754 "parser.cpp"
    break;

  case 30: /* MethodList: MethodName '(' Parameters ')' t_arrow Type '{' '}'  */
#line 156 "parser.y"
                          { (yyval.method_list_ptr) = new std::list<MethodNode*>(); (yyval.method_list_ptr)->push_back(new MethodNode((yyvsp[-7].identifier_ptr), (yyvsp[-5].parameter_list_ptr), (yyvsp[-2].type_ptr), new MethodBodyNode(NULL, NULL, NULL))); }
#line 1760 "parser.cpp"
    break;

  case 31: /* MemberNames: ',' first_id MemberNames  */
#line 160 "parser.y"
                          { (yyval.identifier_list_ptr) = (yyvsp[0].identifier_list_ptr); (yyval.identifier_list_ptr)->push_front((yyvsp[-1].identifier_ptr)); }
#line 1766 "parser.cpp"
    break;

  case 32: /* MemberNames: %empty  */
#line 162 "parser.y"
                          { (yyval.identifier_list_ptr) = new std::list<IdentifierNode*>(); }
#line 1772 "parser.cpp"
    break;

  case 33: /* NesMethodName: first_id '.' first_id  */
#line 166 "parser.y"
                          { (yyval.identifier_list_ptr) = new std::list<IdentifierNode*>(); (yyval.identifier_list_ptr)->push_back((yyvsp[-2].identifier_ptr)); (yyval.identifier_list_ptr)->push_back((yyvsp[0].identifier_ptr)); }
#line 1778 "parser.cpp"
    break;

  case 34: /* NesMethodName: first_id t_arrow first_id  */
#line 168 "parser.y"
                          { (yyval.identifier_list_ptr) = new std::list<IdentifierNode*>(); (yyval.identifier_list_ptr)->push_back((yyvsp[-2].identifier_ptr)); (yyval.identifier_list_ptr)->push_back((yyvsp[0].identifier_ptr)); }
#line 1784 "parser.cpp"
    break;

  case 35: /* Parameters: Parameter ParametersRest  */
#line 172 "parser.y"
                          { (yyval.parameter_list_ptr) = (yyvsp[0].parameter_list_ptr); (yyval.parameter_list_ptr)->push_front((yyvsp[-1].parameter_ptr)); }
#line 1790 "parser.cpp"
    break;

  case 36: /* Parameters: %empty  */
#line 174 "parser.y"
                          { (yyval.parameter_list_ptr) = new std::list<ParameterNode*>(); }
#line 1796 "parser.cpp"
    break;

  case 37: /* ParametersRest: ',' Parameter ParametersRest  */
#line 178 "parser.y"
                          { (yyval.parameter_list_ptr) = (yyvsp[0].parameter_list_ptr); (yyval.parameter_list_ptr)->push_front((yyvsp[-1].parameter_ptr)); }
#line 1802 "parser.cpp"
    break;

  case 38: /* ParametersRest: %empty  */
#line 180 "parser.y"
                          { (yyval.parameter_list_ptr) = new std::list<ParameterNode*>(); }
#line 1808 "parser.cpp"
    break;

  case 39: /* Parameter: Type first_id  */
#line 184 "parser.y"
                          { (yyval.parameter_ptr) = new ParameterNode((yyvsp[-1].type_ptr), (yyvsp[0].identifier_ptr)); }
#line 1814 "parser.cpp"
    break;

  case 40: /* Type: t_int_type  */
#line 188 "parser.y"
                          { (yyval.type_ptr) = new IntegerTypeNode(); }
#line 1820 "parser.cpp"
    break;

  case 41: /* Type: t_bool_type  */
#line 190 "parser.y"
                          { (yyval.type_ptr) = new BooleanTypeNode(); }
#line 1826 "parser.cpp"
    break;

  case 42: /* Type: t_none_type  */
#line 192 "parser.y"
                          { (yyval.type_ptr) = new NoneNode(); }
#line 1832 "parser.cpp"
    break;

  case 43: /* Type: first_id  */
#line 194 "parser.y"
                          { (yyval.type_ptr) = new ObjectTypeNode((yyvsp[0].identifier_ptr)); }
#line 1838 "parser.cpp"
    break;

  case 44: /* MethodBodyList: MethodBodyList Statement  */
#line 198 "parser.y"
                          { (yyval.statement_list_ptr) = (yyvsp[-1].statement_list_ptr); (yyval.statement_list_ptr)->push_back((yyvsp[0].statement_ptr)); }
#line 1844 "parser.cpp"
    break;

  case 45: /* MethodBodyList: Statement  */
#line 200 "parser.y"
                          { (yyval.statement_list_ptr) = new std::list<StatementNode*>(); (yyval.statement_list_ptr)->push_back((yyvsp[0].statement_ptr)); }
#line 1850 "parser.cpp"
    break;

  case 46: /* MethodBodyReturn: t_return Expression ';'  */
#line 204 "parser.y"
                          { (yyval.returnstatement_ptr) = new ReturnStatementNode((yyvsp[-1].expression_ptr)); }
#line 1856 "parser.cpp"
    break;

  case 47: /* Statement: first_id '=' Expression ';'  */
#line 208 "parser.y"
                          { (yyval.statement_ptr) = new AssignmentNode((yyvsp[-3].identifier_ptr), NULL, (yyvsp[-1].expression_ptr)); }
#line 1862 "parser.cpp"
    break;

  case 48: /* Statement: first_id '.' first_id '=' Expression ';'  */
#line 210 "parser.y"
                          { (yyval.statement_ptr) = new AssignmentNode((yyvsp[-5].identifier_ptr), (yyvsp[-3].identifier_ptr), (yyvsp[-1].expression_ptr)); }
#line 1868 "parser.cpp"
    break;

  case 49: /* Statement: first_id t_arrow first_id '=' Expression ';'  */
#line 212 "parser.y"
                          { (yyval.statement_ptr) = new AssignmentNode((yyvsp[-5].identifier_ptr), (yyvsp[-3].identifier_ptr), (yyvsp[-1].expression_ptr)); }
#line 1874 "parser.cpp"
    break;

  case 50: /* Statement: MethodCall ';'  */
#line 214 "parser.y"
                          { (yyval.statement_ptr) = new CallNode((yyvsp[-1].methodcall_ptr)); }
#line 1880 "parser.cpp"
    break;

  case 51: /* Statement: t_if Expression '{' Statement Block '}'  */
#line 216 "parser.y"
                          { (yyvsp[-1].statement_list_ptr)->push_front((yyvsp[-2].statement_ptr)); (yyval.statement_ptr) = new IfElseNode((yyvsp[-4].expression_ptr), (yyvsp[-1].statement_list_ptr), NULL); }
#line 1886 "parser.cpp"
    break;

  case 52: /* Statement: t_if Expression '{' Statement Block '}' t_else '{' Statement Block '}'  */
#line 218 "parser.y"
                          { (yyvsp[-6].statement_list_ptr)->push_front((yyvsp[-7].statement_ptr)); (yyvsp[-1].statement_list_ptr)->push_front((yyvsp[-2].statement_ptr)); (yyval.statement_ptr) = new IfElseNode((yyvsp[-9].expression_ptr), (yyvsp[-6].statement_list_ptr), (yyvsp[-1].statement_list_ptr)); }
#line 1892 "parser.cpp"
    break;

  case 53: /* Statement: t_while Expression '{' Statement Block '}'  */
#line 220 "parser.y"
                          { (yyvsp[-1].statement_list_ptr)->push_front((yyvsp[-2].statement_ptr)); (yyval.statement_ptr) = new WhileNode((yyvsp[-4].expression_ptr), (yyvsp[-1].statement_list_ptr)); }
#line 1898 "parser.cpp"
    break;

  case 54: /* Statement: t_do '{' Statement Block '}' t_while '(' Expression ')' ';'  */
#line 222 "parser.y"
                          { (yyvsp[-6].statement_list_ptr)->push_front((yyvsp[-7].statement_ptr)); (yyval.statement_ptr) = new DoWhileNode((yyvsp[-6].statement_list_ptr), (yyvsp[-2].expression_ptr)); }
#line 1904 "parser.cpp"
    break;

  case 55: /* Statement: t_print Expression ';'  */
#line 224 "parser.y"
                          { (yyval.statement_ptr) = new PrintNode((yyvsp[-1].expression_ptr)); }
#line 1910 "parser.cpp"
    break;

  case 56: /* MethodCallInputs: MethodCallInput MethodCallInputsRest  */
#line 228 "parser.y"
                          { (yyval.expression_list_ptr) = (yyvsp[0].expression_list_ptr); (yyval.expression_list_ptr)->push_front((yyvsp[-1].expression_ptr)); }
#line 1916 "parser.cpp"
    break;

  case 57: /* MethodCallInputs: %empty  */
#line 230 "parser.y"
                          { (yyval.expression_list_ptr) = new std::list<ExpressionNode*>(); }
#line 1922 "parser.cpp"
    break;

  case 58: /* MethodCallInputsRest: ',' MethodCallInput MethodCallInputsRest  */
#line 234 "parser.y"
                          { (yyval.expression_list_ptr) = (yyvsp[0].expression_list_ptr); (yyval.expression_list_ptr)->push_front((yyvsp[-1].expression_ptr)); }
#line 1928 "parser.cpp"
    break;

  case 59: /* MethodCallInputsRest: %empty  */
#line 236 "parser.y"
                          { (yyval.expression_list_ptr) = new std::list<ExpressionNode*>(); }
#line 1934 "parser.cpp"
    break;

  case 60: /* MethodCallInput: Expression  */
#line 239 "parser.y"
                                          { (yyval.expression_ptr) = (yyvsp[0].expression_ptr); }
#line 1940 "parser.cpp"
    break;

  case 61: /* Block: Statement Block  */
#line 243 "parser.y"
                            { (yyval.statement_list_ptr) = (yyvsp[0].statement_list_ptr); (yyval.statement_list_ptr)->push_front((yyvsp[-1].statement_ptr)); }
#line 1946 "parser.cpp"
    break;

  case 62: /* Block: %empty  */
#line 245 "parser.y"
                            { (yyval.statement_list_ptr) = new std::list<StatementNode*>(); }
#line 1952 "parser.cpp"
    break;

  case 63: /* Expression: Expression '+' Expression  */
#line 249 "parser.y"
                          { (yyval.expression_ptr) = new PlusNode((yyvsp[-2].expression_ptr), (yyvsp[0].expression_ptr)); }
#line 1958 "parser.cpp"
    break;

  case 64: /* Expression: Expression '-' Expression  */
#line 251 "parser.y"
                          { (yyval.expression_ptr) = new MinusNode((yyvsp[-2].expression_ptr), (yyvsp[0].expression_ptr)); }
#line 1964 "parser.cpp"
    break;

  case 65: /* Expression: Expression '*' Expression  */
#line 253 "parser.y"
                          { (yyval.expression_ptr) = new TimesNode((yyvsp[-2].expression_ptr), (yyvsp[0].expression_ptr)); }
#line 1970 "parser.cpp"
    break;

  case 66: /* Expression: Expression '/' Expression  */
#line 255 "parser.y"
                          { (yyval.expression_ptr) = new DivideNode((yyvsp[-2].expression_ptr), (yyvsp[0].expression_ptr)); }
#line 1976 "parser.cpp"
    break;

  case 67: /* Expression: Expression '>' Expression  */
#line 257 "parser.y"
                          { (yyval.expression_ptr) = new GreaterNode((yyvsp[-2].expression_ptr), (yyvsp[0].expression_ptr)); }
#line 1982 "parser.cpp"
    break;

  case 68: /* Expression: Expression t_geq Expression  */
#line 259 "parser.y"
                          { (yyval.expression_ptr) = new GreaterEqualNode((yyvsp[-2].expression_ptr), (yyvsp[0].expression_ptr)); }
#line 1988 "parser.cpp"
    break;

  case 69: /* Expression: Expression t_equals Expression  */
#line 261 "parser.y"
                          { (yyval.expression_ptr) = new EqualNode((yyvsp[-2].expression_ptr), (yyvsp[0].expression_ptr)); }
#line 1994 "parser.cpp"
    break;

  case 70: /* Expression: Expression t_and Expression  */
#line 263 "parser.y"
                          { (yyval.expression_ptr) = new AndNode((yyvsp[-2].expression_ptr), (yyvsp[0].expression_ptr)); }
#line 2000 "parser.cpp"
    break;

  case 71: /* Expression: Expression t_or Expression  */
#line 265 "parser.y"
                          { (yyval.expression_ptr) = new OrNode((yyvsp[-2].expression_ptr), (yyvsp[0].expression_ptr)); }
#line 2006 "parser.cpp"
    break;

  case 72: /* Expression: t_not Expression  */
#line 267 "parser.y"
                          { (yyval.expression_ptr) = new NotNode((yyvsp[0].expression_ptr)); }
#line 2012 "parser.cpp"
    break;

  case 73: /* Expression: '-' Expression  */
#line 269 "parser.y"
                          { (yyval.expression_ptr) = new NegationNode((yyvsp[0].expression_ptr)); }
#line 2018 "parser.cpp"
    break;

  case 74: /* Expression: first_id  */
#line 271 "parser.y"
                          { (yyval.expression_ptr) = new VariableNode((yyvsp[0].identifier_ptr)); }
#line 2024 "parser.cpp"
    break;

  case 75: /* Expression: first_id '.' first_id  */
#line 273 "parser.y"
                          { (yyval.expression_ptr) = new MemberAccessNode((yyvsp[-2].identifier_ptr), (yyvsp[0].identifier_ptr)); }
#line 2030 "parser.cpp"
    break;

  case 76: /* Expression: first_id t_arrow first_id  */
#line 275 "parser.y"
                          { (yyval.expression_ptr) = new MemberAccessNode((yyvsp[-2].identifier_ptr), (yyvsp[0].identifier_ptr)); }
#line 2036 "parser.cpp"
    break;

  case 77: /* Expression: MethodCall  */
#line 277 "parser.y"
                          { (yyval.expression_ptr) = (yyvsp[0].methodcall_ptr); }
#line 2042 "parser.cpp"
    break;

  case 78: /* Expression: '(' Expression ')'  */
#line 279 "parser.y"
                          { (yyval.expression_ptr) = (yyvsp[-1].expression_ptr); }
#line 2048 "parser.cpp"
    break;

  case 79: /* Expression: t_number  */
#line 281 "parser.y"
                          { (yyval.expression_ptr) = new IntegerLiteralNode(new IntegerNode(yylval.base_int)); }
#line 2054 "parser.cpp"
    break;

  case 80: /* Expression: t_true  */
#line 283 "parser.y"
                          { (yyval.expression_ptr) = new BooleanLiteralNode(new IntegerNode(1)); }
#line 2060 "parser.cpp"
    break;

  case 81: /* Expression: t_false  */
#line 285 "parser.y"
                          { (yyval.expression_ptr) = new BooleanLiteralNode(new IntegerNode(0)); }
#line 2066 "parser.cpp"
    break;

  case 82: /* Expression: t_new ClassName  */
#line 287 "parser.y"
                          { (yyval.expression_ptr) = new NewNode((yyvsp[0].identifier_ptr), NULL); }
#line 2072 "parser.cpp"
    break;

  case 83: /* Expression: t_new ClassName '(' MethodCallInputs ')'  */
#line 289 "parser.y"
                          { (yyval.expression_ptr) = new NewNode((yyvsp[-3].identifier_ptr), (yyvsp[-1].expression_list_ptr)); }
#line 2078 "parser.cpp"
    break;

  case 84: /* MethodCall: MethodName '(' MethodCallInputs ')'  */
#line 293 "parser.y"
                          { (yyval.methodcall_ptr) = new MethodCallNode((yyvsp[-3].identifier_ptr), NULL, (yyvsp[-1].expression_list_ptr)); }
#line 2084 "parser.cpp"
    break;

  case 85: /* MethodCall: NesMethodName '(' MethodCallInputs ')'  */
#line 295 "parser.y"
                          { (yyval.methodcall_ptr) = new MethodCallNode((yyvsp[-3].identifier_list_ptr)->front(), (yyvsp[-3].identifier_list_ptr)->back(), (yyvsp[-1].expression_list_ptr)); }
#line 2090 "parser.cpp"
    break;

  case 86: /* ClassName: first_id  */
#line 298 "parser.y"
                                      { (yyval.identifier_ptr) = (yyvsp[0].identifier_ptr); }
#line 2096 "parser.cpp"
    break;

  case 87: /* MemberName: first_id  */
#line 301 "parser.y"
                                      { (yyval.identifier_ptr) = (yyvsp[0].identifier_ptr); }
#line 2102 "parser.cpp"
    break;

  case 88: /* MethodName: first_id  */
#line 304 "parser.y"
                                      { (yyval.identifier_ptr) = (yyvsp[0].identifier_ptr); }
#line 2108 "parser.cpp"
    break;

  case 89: /* first_id: t_id  */
#line 308 "parser.y"
                          { (yyval.identifier_ptr) = new IdentifierNode(yylval.base_char_ptr); }
#line 2114 "parser.cpp"
    break;


#line 2118 "parser.cpp"

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          goto yyexhaustedlab;
      }
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


#if 1
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
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 310 "parser.y"


extern int yylineno;

void yyerror(const char *s) {
  fprintf(stderr, "%s at line %d\n", s, yylineno);
  exit(1);
}
