/* A Bison parser, made by GNU Bison 3.8.2.  */

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
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 14 "c99.y"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
void yyerror(const char *msg);

#line 79 "c99.tab.c"

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

#include "c99.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_CONSTANT = 4,                   /* CONSTANT  */
  YYSYMBOL_DCONSTANT = 5,                  /* DCONSTANT  */
  YYSYMBOL_PTR_OP = 6,                     /* PTR_OP  */
  YYSYMBOL_INC_OP = 7,                     /* INC_OP  */
  YYSYMBOL_DEC_OP = 8,                     /* DEC_OP  */
  YYSYMBOL_LEFT_OP = 9,                    /* LEFT_OP  */
  YYSYMBOL_RIGHT_OP = 10,                  /* RIGHT_OP  */
  YYSYMBOL_LE_OP = 11,                     /* LE_OP  */
  YYSYMBOL_GE_OP = 12,                     /* GE_OP  */
  YYSYMBOL_EQ_OP = 13,                     /* EQ_OP  */
  YYSYMBOL_NE_OP = 14,                     /* NE_OP  */
  YYSYMBOL_AND_OP = 15,                    /* AND_OP  */
  YYSYMBOL_OR_OP = 16,                     /* OR_OP  */
  YYSYMBOL_INT = 17,                       /* INT  */
  YYSYMBOL_DOUBLE = 18,                    /* DOUBLE  */
  YYSYMBOL_VOID = 19,                      /* VOID  */
  YYSYMBOL_IF = 20,                        /* IF  */
  YYSYMBOL_ELSE = 21,                      /* ELSE  */
  YYSYMBOL_WHILE = 22,                     /* WHILE  */
  YYSYMBOL_DO = 23,                        /* DO  */
  YYSYMBOL_FOR = 24,                       /* FOR  */
  YYSYMBOL_CONTINUE = 25,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 26,                     /* BREAK  */
  YYSYMBOL_RETURN = 27,                    /* RETURN  */
  YYSYMBOL_28_ = 28,                       /* '('  */
  YYSYMBOL_29_ = 29,                       /* ')'  */
  YYSYMBOL_30_ = 30,                       /* '['  */
  YYSYMBOL_31_ = 31,                       /* ']'  */
  YYSYMBOL_32_ = 32,                       /* '.'  */
  YYSYMBOL_33_ = 33,                       /* ','  */
  YYSYMBOL_34_ = 34,                       /* '&'  */
  YYSYMBOL_35_ = 35,                       /* '*'  */
  YYSYMBOL_36_ = 36,                       /* '+'  */
  YYSYMBOL_37_ = 37,                       /* '-'  */
  YYSYMBOL_38_ = 38,                       /* '~'  */
  YYSYMBOL_39_ = 39,                       /* '!'  */
  YYSYMBOL_40_ = 40,                       /* '/'  */
  YYSYMBOL_41_ = 41,                       /* '%'  */
  YYSYMBOL_42_ = 42,                       /* '<'  */
  YYSYMBOL_43_ = 43,                       /* '>'  */
  YYSYMBOL_44_ = 44,                       /* '^'  */
  YYSYMBOL_45_ = 45,                       /* '|'  */
  YYSYMBOL_46_ = 46,                       /* '='  */
  YYSYMBOL_47_ = 47,                       /* ';'  */
  YYSYMBOL_48_ = 48,                       /* '{'  */
  YYSYMBOL_49_ = 49,                       /* '}'  */
  YYSYMBOL_50_ = 50,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 51,                  /* $accept  */
  YYSYMBOL_primary_expression = 52,        /* primary_expression  */
  YYSYMBOL_postfix_expression = 53,        /* postfix_expression  */
  YYSYMBOL_argument_expression_list = 54,  /* argument_expression_list  */
  YYSYMBOL_unary_expression = 55,          /* unary_expression  */
  YYSYMBOL_cast_expression = 56,           /* cast_expression  */
  YYSYMBOL_multiplicative_expression = 57, /* multiplicative_expression  */
  YYSYMBOL_additive_expression = 58,       /* additive_expression  */
  YYSYMBOL_shift_expression = 59,          /* shift_expression  */
  YYSYMBOL_relational_expression = 60,     /* relational_expression  */
  YYSYMBOL_equality_expression = 61,       /* equality_expression  */
  YYSYMBOL_and_expression = 62,            /* and_expression  */
  YYSYMBOL_exclusive_or_expression = 63,   /* exclusive_or_expression  */
  YYSYMBOL_inclusive_or_expression = 64,   /* inclusive_or_expression  */
  YYSYMBOL_logical_and_expression = 65,    /* logical_and_expression  */
  YYSYMBOL_logical_or_expression = 66,     /* logical_or_expression  */
  YYSYMBOL_conditional_expression = 67,    /* conditional_expression  */
  YYSYMBOL_assignment_expression = 68,     /* assignment_expression  */
  YYSYMBOL_expression = 69,                /* expression  */
  YYSYMBOL_declaration = 70,               /* declaration  */
  YYSYMBOL_declaration_specifiers = 71,    /* declaration_specifiers  */
  YYSYMBOL_init_declarator_list = 72,      /* init_declarator_list  */
  YYSYMBOL_init_declarator = 73,           /* init_declarator  */
  YYSYMBOL_type_specifier = 74,            /* type_specifier  */
  YYSYMBOL_declarator = 75,                /* declarator  */
  YYSYMBOL_direct_declarator = 76,         /* direct_declarator  */
  YYSYMBOL_parameter_type_list = 77,       /* parameter_type_list  */
  YYSYMBOL_parameter_list = 78,            /* parameter_list  */
  YYSYMBOL_parameter_declaration = 79,     /* parameter_declaration  */
  YYSYMBOL_identifier_list = 80,           /* identifier_list  */
  YYSYMBOL_abstract_declarator = 81,       /* abstract_declarator  */
  YYSYMBOL_direct_abstract_declarator = 82, /* direct_abstract_declarator  */
  YYSYMBOL_initializer = 83,               /* initializer  */
  YYSYMBOL_initializer_list = 84,          /* initializer_list  */
  YYSYMBOL_statement = 85,                 /* statement  */
  YYSYMBOL_compound_statement = 86,        /* compound_statement  */
  YYSYMBOL_block_item_list = 87,           /* block_item_list  */
  YYSYMBOL_block_item = 88,                /* block_item  */
  YYSYMBOL_expression_statement = 89,      /* expression_statement  */
  YYSYMBOL_selection_statement = 90,       /* selection_statement  */
  YYSYMBOL_iteration_statement = 91,       /* iteration_statement  */
  YYSYMBOL_jump_statement = 92,            /* jump_statement  */
  YYSYMBOL_external_declaration = 93,      /* external_declaration  */
  YYSYMBOL_function_definition = 94,       /* function_definition  */
  YYSYMBOL_translation_unit = 95           /* translation_unit  */
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

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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
#define YYFINAL  19
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   715

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  137
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  244

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   282


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
       2,     2,     2,    39,     2,     2,     2,    41,    34,     2,
      28,    29,    35,    36,    33,    37,    32,    40,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    50,    47,
      42,    46,    43,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    30,     2,    31,    44,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    48,    45,    49,    38,     2,     2,     2,
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
      25,    26,    27
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    73,    73,    75,    77,    79,    84,    86,    88,    90,
      96,    98,   100,   102,   111,   117,   133,   135,   137,   139,
     141,   143,   145,   147,   149,   154,   159,   161,   163,   165,
     170,   172,   174,   179,   181,   183,   188,   190,   192,   194,
     196,   201,   203,   205,   210,   212,   217,   219,   224,   226,
     231,   233,   238,   240,   245,   254,   256,   261,   263,   275,
     279,   289,   295,   306,   312,   322,   324,   330,   331,   332,
     337,   339,   344,   346,   348,   350,   352,   357,   359,   361,
     366,   374,   380,   390,   392,   394,   400,   406,   417,   419,
     421,   426,   428,   430,   432,   434,   436,   438,   440,   442,
     444,   446,   452,   454,   456,   461,   467,   478,   479,   480,
     481,   482,   483,   487,   488,   492,   498,   507,   508,   512,
     513,   517,   519,   524,   526,   528,   530,   532,   534,   539,
     540,   541,   542,   547,   548,   552,   566,   572
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
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER",
  "CONSTANT", "DCONSTANT", "PTR_OP", "INC_OP", "DEC_OP", "LEFT_OP",
  "RIGHT_OP", "LE_OP", "GE_OP", "EQ_OP", "NE_OP", "AND_OP", "OR_OP", "INT",
  "DOUBLE", "VOID", "IF", "ELSE", "WHILE", "DO", "FOR", "CONTINUE",
  "BREAK", "RETURN", "'('", "')'", "'['", "']'", "'.'", "','", "'&'",
  "'*'", "'+'", "'-'", "'~'", "'!'", "'/'", "'%'", "'<'", "'>'", "'^'",
  "'|'", "'='", "';'", "'{'", "'}'", "':'", "$accept",
  "primary_expression", "postfix_expression", "argument_expression_list",
  "unary_expression", "cast_expression", "multiplicative_expression",
  "additive_expression", "shift_expression", "relational_expression",
  "equality_expression", "and_expression", "exclusive_or_expression",
  "inclusive_or_expression", "logical_and_expression",
  "logical_or_expression", "conditional_expression",
  "assignment_expression", "expression", "declaration",
  "declaration_specifiers", "init_declarator_list", "init_declarator",
  "type_specifier", "declarator", "direct_declarator",
  "parameter_type_list", "parameter_list", "parameter_declaration",
  "identifier_list", "abstract_declarator", "direct_abstract_declarator",
  "initializer", "initializer_list", "statement", "compound_statement",
  "block_item_list", "block_item", "expression_statement",
  "selection_statement", "iteration_statement", "jump_statement",
  "external_declaration", "function_definition", "translation_unit", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-135)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     169,  -135,  -135,  -135,  -135,   103,  -135,  -135,  -135,   115,
    -135,    14,    14,  -135,    -6,  -135,  -135,    -8,    88,  -135,
    -135,    -9,  -135,    14,  -135,   338,   190,  -135,   122,   443,
    -135,  -135,   -31,  -135,  -135,  -135,   676,   676,   676,   676,
     676,   676,   676,   676,   676,   338,  -135,    44,     2,  -135,
      68,   100,   191,     1,   206,    11,    12,    16,    49,    57,
    -135,  -135,  -135,    27,    77,    96,   301,   101,   102,   112,
     392,  -135,  -135,  -135,    -1,  -135,   103,  -135,  -135,   227,
    -135,  -135,  -135,  -135,  -135,  -135,  -135,   388,   148,   151,
    -135,    26,  -135,   480,   168,  -135,  -135,    38,  -135,  -135,
    -135,  -135,  -135,  -135,  -135,  -135,   -14,   189,  -135,  -135,
     492,   676,   199,   676,   676,   676,   676,   676,   676,   676,
     676,   676,   676,   676,   676,   676,   676,   676,   676,   676,
     676,   676,   301,   676,   676,   201,   375,  -135,  -135,  -135,
       6,   676,  -135,  -135,  -135,   125,   529,    30,  -135,  -135,
     161,  -135,   169,  -135,   208,  -135,  -135,  -135,   264,  -135,
    -135,  -135,    81,  -135,   136,  -135,  -135,  -135,  -135,  -135,
      68,    68,   100,   100,   191,   191,   191,   191,     1,     1,
     206,    11,    12,    16,    49,  -135,    84,   119,   205,   429,
     429,  -135,  -135,  -135,   207,   219,  -135,   541,   225,   161,
     139,   578,  -135,  -135,  -135,  -135,  -135,   676,  -135,   301,
     301,   676,   590,   627,  -135,  -135,  -135,  -135,  -135,   228,
    -135,   639,   229,  -135,   237,  -135,   133,   301,   143,   301,
     145,  -135,  -135,  -135,   301,   212,  -135,   301,  -135,   301,
    -135,  -135,  -135,  -135
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    68,    69,    67,   134,     0,    61,   136,   133,     0,
      79,     0,     0,    59,     0,    63,    62,    65,    71,     1,
     137,     0,    70,     0,    60,     0,     0,   135,     0,     0,
      72,    64,    65,     2,     3,     4,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     6,    16,    25,    26,
      30,    33,    36,    41,    44,    46,    48,    50,    52,    54,
      55,   102,    66,     2,     0,     0,     0,     0,     0,     0,
       0,   119,   113,    57,     0,   117,     0,   118,   108,     0,
     115,   109,   110,   111,   112,    86,    78,    85,     0,    80,
      81,     0,    75,     0,     0,    17,    18,     0,    25,    19,
      20,    21,    22,    23,    24,   105,     0,     0,    12,    13,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   129,   130,   131,
       0,     0,   120,   114,   116,     0,     0,    88,    83,    84,
      89,    76,     0,    77,     0,    74,    73,     5,     0,   103,
      11,     8,     0,    14,     0,    10,    56,    27,    28,    29,
      31,    32,    34,    35,    39,    40,    37,    38,    42,    43,
      45,    47,    49,    51,    53,   107,     0,     0,     0,     0,
       0,   132,    58,    98,     0,     0,    92,     0,     0,    90,
       0,     0,    82,    87,   104,   106,     9,     0,     7,     0,
       0,     0,     0,     0,    99,    91,    96,    93,   100,     0,
      94,     0,     0,    15,   121,   123,     0,     0,     0,     0,
       0,   101,    97,    95,     0,     0,   127,     0,   125,     0,
     122,   124,   128,   126
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -135,  -135,  -135,  -135,   -36,   -18,   104,   121,    59,   117,
     146,   142,   149,   147,   150,  -135,  -135,   -11,    -7,   -17,
      28,  -135,   256,    25,    24,  -135,  -134,  -135,   128,  -135,
     137,   138,   -35,  -135,   -64,   266,  -135,   209,  -120,  -135,
    -135,  -135,   275,  -135,  -135
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    46,    47,   162,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    73,    74,     4,
      87,    14,    15,     6,    21,    18,    88,    89,    90,    91,
     149,   150,    62,   106,    77,    78,    79,    80,    81,    82,
      83,    84,     7,     8,     9
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      95,    96,   135,    98,    98,    98,    98,    98,    98,    75,
     105,   194,   121,   122,    61,    25,   190,    10,    94,   158,
      30,    99,   100,   101,   102,   103,   104,    23,     5,    17,
      16,    97,   141,    10,    61,   159,    22,     5,    25,   141,
      26,    24,    11,   123,   124,   127,   142,    32,   113,    12,
     107,   108,   109,   191,    76,   153,   128,    98,   145,   154,
     146,   129,    75,   140,   130,    12,   219,   157,   185,   212,
     213,   141,   110,   131,   111,   100,   112,   132,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,   167,   168,   169,   163,
      32,    16,   166,   114,   164,   133,    10,    76,   115,   116,
     206,   148,    16,   209,   207,    19,    28,   141,    29,   189,
       1,     2,     3,   205,   134,    85,   186,   187,    10,   136,
     192,    11,     1,     2,     3,   198,   117,   118,    12,     1,
       2,     3,     1,     2,     3,   224,   225,    61,   210,   137,
      13,    86,   141,   145,   193,   146,     1,     2,     3,   138,
     147,    98,   235,   236,    76,   238,   141,   208,   218,   141,
     240,    22,   237,   242,   239,   243,   141,   151,   141,   100,
     174,   175,   176,   177,   152,    98,     1,     2,     3,   200,
     222,   201,   160,    63,    34,    35,   223,    36,    37,   156,
     119,   120,   165,   100,   226,   228,   230,     1,     2,     3,
      64,   203,    65,    66,    67,    68,    69,    70,    38,   125,
     126,   170,   171,   188,    39,    40,    41,    42,    43,    44,
      63,    34,    35,   211,    36,    37,   214,    71,    26,    72,
     172,   173,   178,   179,     1,     2,     3,    64,   215,    65,
      66,    67,    68,    69,    70,    38,   217,   231,   234,   241,
     233,    39,    40,    41,    42,    43,    44,    33,    34,    35,
     181,    36,    37,   180,    71,    26,   143,   183,   182,    31,
     202,   184,   195,    27,    20,   199,     0,     0,   144,     0,
       0,     0,    38,     0,     0,     0,     0,     0,    39,    40,
      41,    42,    43,    44,    63,    34,    35,     0,    36,    37,
       0,     0,    45,   204,     0,     0,     0,     0,     0,     0,
       0,    64,     0,    65,    66,    67,    68,    69,    70,    38,
       0,     0,     0,     0,     0,    39,    40,    41,    42,    43,
      44,    33,    34,    35,     0,    36,    37,     0,    71,    26,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    38,     0,     0,     0,
       0,     0,    39,    40,    41,    42,    43,    44,    33,    34,
      35,     0,    36,    37,     0,     0,    45,     0,     0,     0,
       0,    10,     1,     2,     3,    33,    34,    35,     0,    36,
      37,     0,     0,    38,     0,     1,     2,     3,     0,    39,
      40,    41,    42,    43,    44,     0,   145,     0,   146,     0,
      38,     0,    71,   147,     0,     0,    39,    40,    41,    42,
      43,    44,    33,    34,    35,     0,    36,    37,     0,   139,
       0,     0,     0,     0,     0,     0,    33,    34,    35,     0,
      36,    37,     0,     0,     0,     0,     0,    38,     0,     0,
       0,     0,     0,    39,    40,    41,    42,    43,    44,     0,
       0,    38,     0,     0,    92,     0,    71,    39,    93,    41,
      42,    43,    44,    33,    34,    35,     0,    36,    37,     0,
       0,     0,     0,     0,     0,    33,    34,    35,     0,    36,
      37,     0,     0,     0,     0,     0,     0,     0,    38,     0,
       0,   155,     0,     0,    39,    40,    41,    42,    43,    44,
      38,   161,     0,     0,     0,     0,    39,    40,    41,    42,
      43,    44,    33,    34,    35,     0,    36,    37,     0,     0,
       0,     0,     0,     0,    33,    34,    35,     0,    36,    37,
       0,     0,     0,     0,     0,     0,     0,    38,     0,     0,
     196,     0,     0,    39,   197,    41,    42,    43,    44,    38,
       0,     0,   216,     0,     0,    39,    40,    41,    42,    43,
      44,    33,    34,    35,     0,    36,    37,     0,     0,     0,
       0,     0,     0,    33,    34,    35,     0,    36,    37,     0,
       0,     0,     0,     0,     0,     0,    38,     0,     0,   220,
       0,     0,    39,   221,    41,    42,    43,    44,    38,   227,
       0,     0,     0,     0,    39,    40,    41,    42,    43,    44,
      33,    34,    35,     0,    36,    37,     0,     0,     0,     0,
       0,     0,    33,    34,    35,     0,    36,    37,     0,     0,
       0,     0,     0,     0,     0,    38,   229,     0,     0,     0,
       0,    39,    40,    41,    42,    43,    44,    38,     0,     0,
     232,     0,     0,    39,    40,    41,    42,    43,    44,    33,
      34,    35,     0,    36,    37,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    38,     0,     0,     0,     0,     0,
      39,    40,    41,    42,    43,    44
};

static const yytype_int16 yycheck[] =
{
      36,    37,    66,    39,    40,    41,    42,    43,    44,    26,
      45,   145,    11,    12,    25,    46,   136,     3,    29,    33,
      29,    39,    40,    41,    42,    43,    44,    33,     0,     5,
       5,    38,    33,     3,    45,    49,    12,     9,    46,    33,
      48,    47,    28,    42,    43,    34,    47,    23,    46,    35,
       6,     7,     8,    47,    26,    29,    44,    93,    28,    33,
      30,    45,    79,    70,    15,    35,   200,    29,   132,   189,
     190,    33,    28,    16,    30,    93,    32,    50,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   114,   115,   116,   110,
      76,    76,   113,    35,   111,    28,     3,    79,    40,    41,
      29,    87,    87,    29,    33,     0,    28,    33,    30,   136,
      17,    18,    19,   158,    28,     3,   133,   134,     3,    28,
     141,    28,    17,    18,    19,   146,    36,    37,    35,    17,
      18,    19,    17,    18,    19,   209,   210,   158,    29,    47,
      47,    29,    33,    28,    29,    30,    17,    18,    19,    47,
      35,   197,    29,   227,   136,   229,    33,    31,    29,    33,
     234,   147,    29,   237,    29,   239,    33,    29,    33,   197,
     121,   122,   123,   124,    33,   221,    17,    18,    19,    28,
     201,    30,     3,     3,     4,     5,   207,     7,     8,    31,
       9,    10,     3,   221,   211,   212,   213,    17,    18,    19,
      20,     3,    22,    23,    24,    25,    26,    27,    28,    13,
      14,   117,   118,    22,    34,    35,    36,    37,    38,    39,
       3,     4,     5,    28,     7,     8,    29,    47,    48,    49,
     119,   120,   125,   126,    17,    18,    19,    20,    29,    22,
      23,    24,    25,    26,    27,    28,    31,    29,    21,    47,
      31,    34,    35,    36,    37,    38,    39,     3,     4,     5,
     128,     7,     8,   127,    47,    48,    49,   130,   129,    23,
     152,   131,   145,    17,     9,   147,    -1,    -1,    79,    -1,
      -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    34,    35,
      36,    37,    38,    39,     3,     4,     5,    -1,     7,     8,
      -1,    -1,    48,    49,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    20,    -1,    22,    23,    24,    25,    26,    27,    28,
      -1,    -1,    -1,    -1,    -1,    34,    35,    36,    37,    38,
      39,     3,     4,     5,    -1,     7,     8,    -1,    47,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,
      -1,    -1,    34,    35,    36,    37,    38,    39,     3,     4,
       5,    -1,     7,     8,    -1,    -1,    48,    -1,    -1,    -1,
      -1,     3,    17,    18,    19,     3,     4,     5,    -1,     7,
       8,    -1,    -1,    28,    -1,    17,    18,    19,    -1,    34,
      35,    36,    37,    38,    39,    -1,    28,    -1,    30,    -1,
      28,    -1,    47,    35,    -1,    -1,    34,    35,    36,    37,
      38,    39,     3,     4,     5,    -1,     7,     8,    -1,    47,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,
       7,     8,    -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,
      -1,    -1,    -1,    34,    35,    36,    37,    38,    39,    -1,
      -1,    28,    -1,    -1,    31,    -1,    47,    34,    35,    36,
      37,    38,    39,     3,     4,     5,    -1,     7,     8,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,
       8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,
      -1,    31,    -1,    -1,    34,    35,    36,    37,    38,    39,
      28,    29,    -1,    -1,    -1,    -1,    34,    35,    36,    37,
      38,    39,     3,     4,     5,    -1,     7,     8,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,     8,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,
      31,    -1,    -1,    34,    35,    36,    37,    38,    39,    28,
      -1,    -1,    31,    -1,    -1,    34,    35,    36,    37,    38,
      39,     3,     4,     5,    -1,     7,     8,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,    -1,     7,     8,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,    31,
      -1,    -1,    34,    35,    36,    37,    38,    39,    28,    29,
      -1,    -1,    -1,    -1,    34,    35,    36,    37,    38,    39,
       3,     4,     5,    -1,     7,     8,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,    -1,     7,     8,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    29,    -1,    -1,    -1,
      -1,    34,    35,    36,    37,    38,    39,    28,    -1,    -1,
      31,    -1,    -1,    34,    35,    36,    37,    38,    39,     3,
       4,     5,    -1,     7,     8,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,
      34,    35,    36,    37,    38,    39
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    17,    18,    19,    70,    71,    74,    93,    94,    95,
       3,    28,    35,    47,    72,    73,    74,    75,    76,     0,
      93,    75,    75,    33,    47,    46,    48,    86,    28,    30,
      29,    73,    75,     3,     4,     5,     7,     8,    28,    34,
      35,    36,    37,    38,    39,    48,    52,    53,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    83,     3,    20,    22,    23,    24,    25,    26,
      27,    47,    49,    68,    69,    70,    71,    85,    86,    87,
      88,    89,    90,    91,    92,     3,    29,    71,    77,    78,
      79,    80,    31,    35,    68,    55,    55,    69,    55,    56,
      56,    56,    56,    56,    56,    83,    84,     6,     7,     8,
      28,    30,    32,    46,    35,    40,    41,    36,    37,     9,
      10,    11,    12,    42,    43,    13,    14,    34,    44,    45,
      15,    16,    50,    28,    28,    85,    28,    47,    47,    47,
      69,    33,    47,    49,    88,    28,    30,    35,    75,    81,
      82,    29,    33,    29,    33,    31,    31,    29,    33,    49,
       3,    29,    54,    68,    69,     3,    68,    56,    56,    56,
      57,    57,    58,    58,    59,    59,    59,    59,    60,    60,
      61,    62,    63,    64,    65,    85,    69,    69,    22,    70,
      89,    47,    68,    29,    77,    81,    31,    35,    68,    82,
      28,    30,    79,     3,    49,    83,    29,    33,    31,    29,
      29,    28,    89,    89,    29,    29,    31,    31,    29,    77,
      31,    35,    68,    68,    85,    85,    69,    29,    69,    29,
      69,    29,    31,    31,    21,    29,    85,    29,    85,    29,
      85,    47,    85,    85
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    51,    52,    52,    52,    52,    53,    53,    53,    53,
      53,    53,    53,    53,    54,    54,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    56,    57,    57,    57,    57,
      58,    58,    58,    59,    59,    59,    60,    60,    60,    60,
      60,    61,    61,    61,    62,    62,    63,    63,    64,    64,
      65,    65,    66,    66,    67,    68,    68,    69,    69,    70,
      70,    71,    71,    72,    72,    73,    73,    74,    74,    74,
      75,    75,    76,    76,    76,    76,    76,    76,    76,    76,
      77,    78,    78,    79,    79,    79,    80,    80,    81,    81,
      81,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    83,    83,    83,    84,    84,    85,    85,    85,
      85,    85,    85,    86,    86,    87,    87,    88,    88,    89,
      89,    90,    90,    91,    91,    91,    91,    91,    91,    92,
      92,    92,    92,    93,    93,    94,    95,    95
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     3,     1,     4,     3,     4,
       3,     3,     2,     2,     1,     3,     1,     2,     2,     2,
       2,     2,     2,     2,     2,     1,     1,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     1,     3,     1,     3,     2,
       3,     1,     2,     1,     3,     1,     3,     1,     1,     1,
       2,     1,     3,     4,     4,     3,     4,     4,     3,     1,
       1,     1,     3,     2,     2,     1,     1,     3,     1,     1,
       2,     3,     2,     3,     3,     4,     3,     4,     2,     3,
       3,     4,     1,     3,     4,     1,     3,     3,     1,     1,
       1,     1,     1,     2,     3,     1,     2,     1,     1,     1,
       2,     5,     7,     5,     7,     6,     7,     6,     7,     2,
       2,     2,     3,     1,     1,     3,     1,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
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
  case 2: /* primary_expression: IDENTIFIER  */
#line 74 "c99.y"
        { (yyval.ast) = ast_var((yyvsp[0].id)); }
#line 1701 "c99.tab.c"
    break;

  case 3: /* primary_expression: CONSTANT  */
#line 76 "c99.y"
        { (yyval.ast) = ast_int((yyvsp[0].intval)); }
#line 1707 "c99.tab.c"
    break;

  case 4: /* primary_expression: DCONSTANT  */
#line 78 "c99.y"
        { (yyval.ast) = ast_double((yyvsp[0].fval)); }
#line 1713 "c99.tab.c"
    break;

  case 5: /* primary_expression: '(' expression ')'  */
#line 80 "c99.y"
        { (yyval.ast) = (yyvsp[-1].ast); }
#line 1719 "c99.tab.c"
    break;

  case 6: /* postfix_expression: primary_expression  */
#line 85 "c99.y"
        { (yyval.ast) = (yyvsp[0].ast); }
#line 1725 "c99.tab.c"
    break;

  case 7: /* postfix_expression: postfix_expression '[' expression ']'  */
#line 87 "c99.y"
        { (yyval.ast) = ast_binop('[', (yyvsp[-3].ast), (yyvsp[-1].ast)); }
#line 1731 "c99.tab.c"
    break;

  case 8: /* postfix_expression: postfix_expression '(' ')'  */
#line 89 "c99.y"
        { (yyval.ast) = ast_call((yyvsp[-2].ast)->varname.c_str(), NULL, 0); }
#line 1737 "c99.tab.c"
    break;

  case 9: /* postfix_expression: postfix_expression '(' argument_expression_list ')'  */
#line 91 "c99.y"
        {
            (yyval.ast) = ast_call((yyvsp[-3].ast)->varname.c_str(),
                          (yyvsp[-1].list).items,
                          (yyvsp[-1].list).count);
        }
#line 1747 "c99.tab.c"
    break;

  case 10: /* postfix_expression: postfix_expression '.' IDENTIFIER  */
#line 97 "c99.y"
        { (yyval.ast) = ast_binop('.', (yyvsp[-2].ast), ast_var((yyvsp[0].id))); }
#line 1753 "c99.tab.c"
    break;

  case 11: /* postfix_expression: postfix_expression PTR_OP IDENTIFIER  */
#line 99 "c99.y"
        { (yyval.ast) = ast_binop('>', (yyvsp[-2].ast), ast_var((yyvsp[0].id))); }
#line 1759 "c99.tab.c"
    break;

  case 12: /* postfix_expression: postfix_expression INC_OP  */
#line 101 "c99.y"
        { (yyval.ast) = ast_unop('+', (yyvsp[-1].ast)); }
#line 1765 "c99.tab.c"
    break;

  case 13: /* postfix_expression: postfix_expression DEC_OP  */
#line 103 "c99.y"
        { (yyval.ast) = ast_unop('-', (yyvsp[-1].ast)); }
#line 1771 "c99.tab.c"
    break;

  case 14: /* argument_expression_list: assignment_expression  */
#line 112 "c99.y"
        {
            (yyval.list).items = malloc(sizeof(ASTNode*));
            (yyval.list).items[0] = (yyvsp[0].ast);
            (yyval.list).count    = 1;
        }
#line 1781 "c99.tab.c"
    break;

  case 15: /* argument_expression_list: argument_expression_list ',' assignment_expression  */
#line 118 "c99.y"
        {
            /* $1 是 ASTList */
            (yyvsp[-2].list).items = realloc((yyvsp[-2].list).items,
                               sizeof(ASTNode*) * ((yyvsp[-2].list).count + 1));
            (yyvsp[-2].list).items[(yyvsp[-2].list).count] = (yyvsp[0].ast);
            (yyvsp[-2].list).count++;
            (yyval.list) = (yyvsp[-2].list);
        }
#line 1794 "c99.tab.c"
    break;

  case 16: /* unary_expression: postfix_expression  */
#line 134 "c99.y"
        { (yyval.ast) = (yyvsp[0].ast); }
#line 1800 "c99.tab.c"
    break;

  case 17: /* unary_expression: INC_OP unary_expression  */
#line 136 "c99.y"
        { (yyval.ast) = ast_unop('+', (yyvsp[0].ast)); }
#line 1806 "c99.tab.c"
    break;

  case 18: /* unary_expression: DEC_OP unary_expression  */
#line 138 "c99.y"
        { (yyval.ast) = ast_unop('-', (yyvsp[0].ast)); }
#line 1812 "c99.tab.c"
    break;

  case 19: /* unary_expression: '&' cast_expression  */
#line 140 "c99.y"
        { (yyval.ast) = ast_unop('&', (yyvsp[0].ast)); }
#line 1818 "c99.tab.c"
    break;

  case 20: /* unary_expression: '*' cast_expression  */
#line 142 "c99.y"
        { (yyval.ast) = ast_pointer((yyvsp[0].ast)); }
#line 1824 "c99.tab.c"
    break;

  case 21: /* unary_expression: '+' cast_expression  */
#line 144 "c99.y"
        { (yyval.ast) = (yyvsp[0].ast); }
#line 1830 "c99.tab.c"
    break;

  case 22: /* unary_expression: '-' cast_expression  */
#line 146 "c99.y"
        { (yyval.ast) = ast_unop('-', (yyvsp[0].ast)); }
#line 1836 "c99.tab.c"
    break;

  case 23: /* unary_expression: '~' cast_expression  */
#line 148 "c99.y"
        { (yyval.ast) = ast_unop('~', (yyvsp[0].ast)); }
#line 1842 "c99.tab.c"
    break;

  case 24: /* unary_expression: '!' cast_expression  */
#line 150 "c99.y"
        { (yyval.ast) = ast_unop('!', (yyvsp[0].ast)); }
#line 1848 "c99.tab.c"
    break;

  case 25: /* cast_expression: unary_expression  */
#line 155 "c99.y"
        { (yyval.ast) = (yyvsp[0].ast); }
#line 1854 "c99.tab.c"
    break;

  case 26: /* multiplicative_expression: cast_expression  */
#line 160 "c99.y"
        { (yyval.ast) = (yyvsp[0].ast); }
#line 1860 "c99.tab.c"
    break;

  case 27: /* multiplicative_expression: multiplicative_expression '*' cast_expression  */
#line 162 "c99.y"
        { (yyval.ast) = ast_binop('*', (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1866 "c99.tab.c"
    break;

  case 28: /* multiplicative_expression: multiplicative_expression '/' cast_expression  */
#line 164 "c99.y"
        { (yyval.ast) = ast_binop('/', (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1872 "c99.tab.c"
    break;

  case 29: /* multiplicative_expression: multiplicative_expression '%' cast_expression  */
#line 166 "c99.y"
        { (yyval.ast) = ast_binop('%', (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1878 "c99.tab.c"
    break;

  case 30: /* additive_expression: multiplicative_expression  */
#line 171 "c99.y"
        { (yyval.ast) = (yyvsp[0].ast); }
#line 1884 "c99.tab.c"
    break;

  case 31: /* additive_expression: additive_expression '+' multiplicative_expression  */
#line 173 "c99.y"
        { (yyval.ast) = ast_binop('+', (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1890 "c99.tab.c"
    break;

  case 32: /* additive_expression: additive_expression '-' multiplicative_expression  */
#line 175 "c99.y"
        { (yyval.ast) = ast_binop('-', (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1896 "c99.tab.c"
    break;

  case 33: /* shift_expression: additive_expression  */
#line 180 "c99.y"
        { (yyval.ast) = (yyvsp[0].ast); }
#line 1902 "c99.tab.c"
    break;

  case 34: /* shift_expression: shift_expression LEFT_OP additive_expression  */
#line 182 "c99.y"
        { (yyval.ast) = ast_binop('<', (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1908 "c99.tab.c"
    break;

  case 35: /* shift_expression: shift_expression RIGHT_OP additive_expression  */
#line 184 "c99.y"
        { (yyval.ast) = ast_binop('>', (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1914 "c99.tab.c"
    break;

  case 36: /* relational_expression: shift_expression  */
#line 189 "c99.y"
        { (yyval.ast) = (yyvsp[0].ast); }
#line 1920 "c99.tab.c"
    break;

  case 37: /* relational_expression: relational_expression '<' shift_expression  */
#line 191 "c99.y"
        { (yyval.ast) = ast_binop('<', (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1926 "c99.tab.c"
    break;

  case 38: /* relational_expression: relational_expression '>' shift_expression  */
#line 193 "c99.y"
        { (yyval.ast) = ast_binop('>', (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1932 "c99.tab.c"
    break;

  case 39: /* relational_expression: relational_expression LE_OP shift_expression  */
#line 195 "c99.y"
        { (yyval.ast) = ast_binop('l', (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1938 "c99.tab.c"
    break;

  case 40: /* relational_expression: relational_expression GE_OP shift_expression  */
#line 197 "c99.y"
        { (yyval.ast) = ast_binop('g', (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1944 "c99.tab.c"
    break;

  case 41: /* equality_expression: relational_expression  */
#line 202 "c99.y"
        { (yyval.ast) = (yyvsp[0].ast); }
#line 1950 "c99.tab.c"
    break;

  case 42: /* equality_expression: equality_expression EQ_OP relational_expression  */
#line 204 "c99.y"
        { (yyval.ast) = ast_binop('e', (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1956 "c99.tab.c"
    break;

  case 43: /* equality_expression: equality_expression NE_OP relational_expression  */
#line 206 "c99.y"
        { (yyval.ast) = ast_binop('!', (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1962 "c99.tab.c"
    break;

  case 44: /* and_expression: equality_expression  */
#line 211 "c99.y"
        { (yyval.ast) = (yyvsp[0].ast); }
#line 1968 "c99.tab.c"
    break;

  case 45: /* and_expression: and_expression '&' equality_expression  */
#line 213 "c99.y"
        { (yyval.ast) = ast_binop('&', (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1974 "c99.tab.c"
    break;

  case 46: /* exclusive_or_expression: and_expression  */
#line 218 "c99.y"
        { (yyval.ast) = (yyvsp[0].ast); }
#line 1980 "c99.tab.c"
    break;

  case 47: /* exclusive_or_expression: exclusive_or_expression '^' and_expression  */
#line 220 "c99.y"
        { (yyval.ast) = ast_binop('^', (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1986 "c99.tab.c"
    break;

  case 48: /* inclusive_or_expression: exclusive_or_expression  */
#line 225 "c99.y"
        { (yyval.ast) = (yyvsp[0].ast); }
#line 1992 "c99.tab.c"
    break;

  case 49: /* inclusive_or_expression: inclusive_or_expression '|' exclusive_or_expression  */
#line 227 "c99.y"
        { (yyval.ast) = ast_binop('|', (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1998 "c99.tab.c"
    break;

  case 50: /* logical_and_expression: inclusive_or_expression  */
#line 232 "c99.y"
        { (yyval.ast) = (yyvsp[0].ast); }
#line 2004 "c99.tab.c"
    break;

  case 51: /* logical_and_expression: logical_and_expression AND_OP inclusive_or_expression  */
#line 234 "c99.y"
        { (yyval.ast) = ast_binop('&', (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 2010 "c99.tab.c"
    break;

  case 52: /* logical_or_expression: logical_and_expression  */
#line 239 "c99.y"
        { (yyval.ast) = (yyvsp[0].ast); }
#line 2016 "c99.tab.c"
    break;

  case 53: /* logical_or_expression: logical_or_expression OR_OP logical_and_expression  */
#line 241 "c99.y"
        { (yyval.ast) = ast_binop('|', (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 2022 "c99.tab.c"
    break;

  case 54: /* conditional_expression: logical_or_expression  */
#line 246 "c99.y"
        { (yyval.ast) = (yyvsp[0].ast); }
#line 2028 "c99.tab.c"
    break;

  case 55: /* assignment_expression: conditional_expression  */
#line 255 "c99.y"
        { (yyval.ast) = (yyvsp[0].ast); }
#line 2034 "c99.tab.c"
    break;

  case 56: /* assignment_expression: unary_expression '=' assignment_expression  */
#line 257 "c99.y"
        { (yyval.ast) = ast_assign((yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 2040 "c99.tab.c"
    break;

  case 57: /* expression: assignment_expression  */
#line 262 "c99.y"
        { (yyval.ast) = (yyvsp[0].ast); }
#line 2046 "c99.tab.c"
    break;

  case 58: /* expression: expression ',' assignment_expression  */
#line 264 "c99.y"
        {
            ASTNode *arr[2] = { (yyvsp[-2].ast), (yyvsp[0].ast) };
            (yyval.ast) = ast_compound(arr, 2);
        }
#line 2055 "c99.tab.c"
    break;

  case 59: /* declaration: declaration_specifiers ';'  */
#line 276 "c99.y"
        {
            (yyval.ast) = ast_decl((yyvsp[-1].ast)->ds.specs, (yyvsp[-1].ast)->ds.scount, NULL, 0);
        }
#line 2063 "c99.tab.c"
    break;

  case 60: /* declaration: declaration_specifiers init_declarator_list ';'  */
#line 280 "c99.y"
        {
            (yyval.ast) = ast_decl((yyvsp[-2].ast)->ds.specs,
                          (yyvsp[-2].ast)->ds.scount,
                          (yyvsp[-1].list).items,
                          (yyvsp[-1].list).count);
        }
#line 2074 "c99.tab.c"
    break;

  case 61: /* declaration_specifiers: type_specifier  */
#line 290 "c99.y"
        {
            ASTNode **a = malloc(sizeof(ASTNode*));
            a[0] = (yyvsp[0].ast);
            (yyval.ast) = ast_decl_spec(a, 1);
        }
#line 2084 "c99.tab.c"
    break;

  case 62: /* declaration_specifiers: declaration_specifiers type_specifier  */
#line 296 "c99.y"
        {
            (yyvsp[-1].ast)->ds.specs = realloc((yyvsp[-1].ast)->ds.specs,
                                   sizeof(ASTNode*) * ((yyvsp[-1].ast)->ds.scount + 1));
            (yyvsp[-1].ast)->ds.specs[(yyvsp[-1].ast)->ds.scount++] = (yyvsp[0].ast);
            (yyval.ast) = (yyvsp[-1].ast);
        }
#line 2095 "c99.tab.c"
    break;

  case 63: /* init_declarator_list: init_declarator  */
#line 307 "c99.y"
        {
            (yyval.list).items = malloc(sizeof(ASTNode*));
            (yyval.list).items[0] = (yyvsp[0].ast);
            (yyval.list).count    = 1;
        }
#line 2105 "c99.tab.c"
    break;

  case 64: /* init_declarator_list: init_declarator_list ',' init_declarator  */
#line 313 "c99.y"
        {
            (yyvsp[-2].list).items = realloc((yyvsp[-2].list).items,
                               sizeof(ASTNode*) * ((yyvsp[-2].list).count + 1));
            (yyvsp[-2].list).items[(yyvsp[-2].list).count++] = (yyvsp[0].ast);
            (yyval.list) = (yyvsp[-2].list);
        }
#line 2116 "c99.tab.c"
    break;

  case 65: /* init_declarator: declarator  */
#line 323 "c99.y"
        { (yyval.ast) = ast_init_decl((yyvsp[0].ast), NULL); }
#line 2122 "c99.tab.c"
    break;

  case 66: /* init_declarator: declarator '=' initializer  */
#line 325 "c99.y"
        { (yyval.ast) = ast_init_decl((yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 2128 "c99.tab.c"
    break;

  case 67: /* type_specifier: VOID  */
#line 330 "c99.y"
              { (yyval.ast) = ast_type_name("void"); }
#line 2134 "c99.tab.c"
    break;

  case 68: /* type_specifier: INT  */
#line 331 "c99.y"
              { (yyval.ast) = ast_type_name("int"); }
#line 2140 "c99.tab.c"
    break;

  case 69: /* type_specifier: DOUBLE  */
#line 332 "c99.y"
              { (yyval.ast) = ast_type_name("double"); }
#line 2146 "c99.tab.c"
    break;

  case 70: /* declarator: '*' declarator  */
#line 338 "c99.y"
        { (yyval.ast) = ast_pointer((yyvsp[0].ast)); }
#line 2152 "c99.tab.c"
    break;

  case 71: /* declarator: direct_declarator  */
#line 340 "c99.y"
        { (yyval.ast) = (yyvsp[0].ast); }
#line 2158 "c99.tab.c"
    break;

  case 72: /* direct_declarator: '(' declarator ')'  */
#line 345 "c99.y"
        { (yyval.ast) = (yyvsp[-1].ast); }
#line 2164 "c99.tab.c"
    break;

  case 73: /* direct_declarator: direct_declarator '[' assignment_expression ']'  */
#line 347 "c99.y"
        { (yyval.ast) = ast_array((yyvsp[-3].ast), (yyvsp[-1].ast)); }
#line 2170 "c99.tab.c"
    break;

  case 74: /* direct_declarator: direct_declarator '[' '*' ']'  */
#line 349 "c99.y"
        { (yyval.ast) = ast_array((yyvsp[-3].ast), NULL); }
#line 2176 "c99.tab.c"
    break;

  case 75: /* direct_declarator: direct_declarator '[' ']'  */
#line 351 "c99.y"
        { (yyval.ast) = ast_array((yyvsp[-2].ast), NULL); }
#line 2182 "c99.tab.c"
    break;

  case 76: /* direct_declarator: direct_declarator '(' parameter_type_list ')'  */
#line 353 "c99.y"
        {
            ASTNode *plist = ast_param_list((yyvsp[-1].list).items, (yyvsp[-1].list).count);
            (yyval.ast) = ast_func_type((yyvsp[-3].ast)->varname.c_str(), plist, NULL, NULL);
        }
#line 2191 "c99.tab.c"
    break;

  case 77: /* direct_declarator: direct_declarator '(' identifier_list ')'  */
#line 358 "c99.y"
        { (yyval.ast) = ast_func_type((yyvsp[-3].ast)->varname.c_str(), NULL, NULL, NULL); }
#line 2197 "c99.tab.c"
    break;

  case 78: /* direct_declarator: direct_declarator '(' ')'  */
#line 360 "c99.y"
        { (yyval.ast) = ast_func_type((yyvsp[-2].ast)->varname.c_str(), NULL, NULL, NULL); }
#line 2203 "c99.tab.c"
    break;

  case 79: /* direct_declarator: IDENTIFIER  */
#line 362 "c99.y"
        { (yyval.ast) = ast_var((yyvsp[0].id)); }
#line 2209 "c99.tab.c"
    break;

  case 80: /* parameter_type_list: parameter_list  */
#line 367 "c99.y"
        { 
			(yyval.list).items = (yyvsp[0].list).items;
			(yyval.list).count = (yyvsp[0].list).count;
		}
#line 2218 "c99.tab.c"
    break;

  case 81: /* parameter_list: parameter_declaration  */
#line 375 "c99.y"
        {
            (yyval.list).items = malloc(sizeof(ASTNode*));
            (yyval.list).items[0] = (yyvsp[0].ast);
            (yyval.list).count    = 1;
        }
#line 2228 "c99.tab.c"
    break;

  case 82: /* parameter_list: parameter_list ',' parameter_declaration  */
#line 381 "c99.y"
        {
            (yyvsp[-2].list).items = realloc((yyvsp[-2].list).items,
                               sizeof(ASTNode*) * ((yyvsp[-2].list).count + 1));
            (yyvsp[-2].list).items[(yyvsp[-2].list).count++] = (yyvsp[0].ast);
            (yyval.list) = (yyvsp[-2].list);
        }
#line 2239 "c99.tab.c"
    break;

  case 83: /* parameter_declaration: declaration_specifiers declarator  */
#line 391 "c99.y"
        { (yyval.ast) = ast_param((yyvsp[-1].ast)->ds.specs, (yyvsp[-1].ast)->ds.scount, (yyvsp[0].ast)); }
#line 2245 "c99.tab.c"
    break;

  case 84: /* parameter_declaration: declaration_specifiers abstract_declarator  */
#line 393 "c99.y"
        { (yyval.ast) = ast_param((yyvsp[-1].ast)->ds.specs, (yyvsp[-1].ast)->ds.scount, (yyvsp[0].ast)); }
#line 2251 "c99.tab.c"
    break;

  case 85: /* parameter_declaration: declaration_specifiers  */
#line 395 "c99.y"
        { (yyval.ast) = ast_param((yyvsp[0].ast)->ds.specs, (yyvsp[0].ast)->ds.scount, NULL); }
#line 2257 "c99.tab.c"
    break;

  case 86: /* identifier_list: IDENTIFIER  */
#line 401 "c99.y"
        {
            (yyval.list).items = malloc(sizeof(ASTNode*));
            (yyval.list).items[0] = ast_var((yyvsp[0].id));
            (yyval.list).count    = 1;
        }
#line 2267 "c99.tab.c"
    break;

  case 87: /* identifier_list: identifier_list ',' IDENTIFIER  */
#line 407 "c99.y"
        {
            (yyvsp[-2].list).items = realloc((yyvsp[-2].list).items,
                               sizeof(ASTNode*) * ((yyvsp[-2].list).count + 1));
            (yyvsp[-2].list).items[(yyvsp[-2].list).count++] = ast_var((yyvsp[0].id));
            (yyval.list) = (yyvsp[-2].list);
        }
#line 2278 "c99.tab.c"
    break;

  case 88: /* abstract_declarator: '*'  */
#line 418 "c99.y"
        { (yyval.ast) = ast_pointer(NULL); }
#line 2284 "c99.tab.c"
    break;

  case 89: /* abstract_declarator: direct_abstract_declarator  */
#line 420 "c99.y"
        { (yyval.ast) = (yyvsp[0].ast); }
#line 2290 "c99.tab.c"
    break;

  case 90: /* abstract_declarator: '*' direct_abstract_declarator  */
#line 422 "c99.y"
        { (yyval.ast) = ast_pointer((yyvsp[0].ast)); }
#line 2296 "c99.tab.c"
    break;

  case 91: /* direct_abstract_declarator: '(' abstract_declarator ')'  */
#line 427 "c99.y"
        { (yyval.ast) = (yyvsp[-1].ast); }
#line 2302 "c99.tab.c"
    break;

  case 92: /* direct_abstract_declarator: '[' ']'  */
#line 429 "c99.y"
        { (yyval.ast) = ast_array(NULL, NULL); }
#line 2308 "c99.tab.c"
    break;

  case 93: /* direct_abstract_declarator: '[' assignment_expression ']'  */
#line 431 "c99.y"
        { (yyval.ast) = ast_array(NULL, (yyvsp[-1].ast)); }
#line 2314 "c99.tab.c"
    break;

  case 94: /* direct_abstract_declarator: direct_abstract_declarator '[' ']'  */
#line 433 "c99.y"
        { (yyval.ast) = ast_array((yyvsp[-2].ast), NULL); }
#line 2320 "c99.tab.c"
    break;

  case 95: /* direct_abstract_declarator: direct_abstract_declarator '[' assignment_expression ']'  */
#line 435 "c99.y"
        { (yyval.ast) = ast_array((yyvsp[-3].ast), (yyvsp[-1].ast)); }
#line 2326 "c99.tab.c"
    break;

  case 96: /* direct_abstract_declarator: '[' '*' ']'  */
#line 437 "c99.y"
        { (yyval.ast) = ast_array(NULL, NULL); }
#line 2332 "c99.tab.c"
    break;

  case 97: /* direct_abstract_declarator: direct_abstract_declarator '[' '*' ']'  */
#line 439 "c99.y"
        { (yyval.ast) = ast_array((yyvsp[-3].ast), NULL); }
#line 2338 "c99.tab.c"
    break;

  case 98: /* direct_abstract_declarator: '(' ')'  */
#line 441 "c99.y"
        { (yyval.ast) = ast_func_type(NULL, NULL, NULL, NULL); }
#line 2344 "c99.tab.c"
    break;

  case 99: /* direct_abstract_declarator: '(' parameter_type_list ')'  */
#line 443 "c99.y"
        { (yyval.ast) = ast_func_type(NULL, ast_param_list((yyvsp[-1].list).items, (yyvsp[-1].list).count), NULL, NULL); }
#line 2350 "c99.tab.c"
    break;

  case 100: /* direct_abstract_declarator: direct_abstract_declarator '(' ')'  */
#line 445 "c99.y"
        { (yyval.ast) = ast_func_type(NULL, NULL, NULL, NULL); }
#line 2356 "c99.tab.c"
    break;

  case 101: /* direct_abstract_declarator: direct_abstract_declarator '(' parameter_type_list ')'  */
#line 447 "c99.y"
        { (yyval.ast) = ast_func_type(NULL, ast_param_list((yyvsp[-1].list).items, (yyvsp[-1].list).count), NULL, NULL); }
#line 2362 "c99.tab.c"
    break;

  case 102: /* initializer: assignment_expression  */
#line 453 "c99.y"
        { (yyval.ast) = (yyvsp[0].ast); }
#line 2368 "c99.tab.c"
    break;

  case 103: /* initializer: '{' initializer_list '}'  */
#line 455 "c99.y"
        { (yyval.ast) = ast_init_list((yyvsp[-1].list).items, (yyvsp[-1].list).count); }
#line 2374 "c99.tab.c"
    break;

  case 104: /* initializer: '{' initializer_list ',' '}'  */
#line 457 "c99.y"
        { (yyval.ast) = ast_init_list((yyvsp[-2].list).items, (yyvsp[-2].list).count); }
#line 2380 "c99.tab.c"
    break;

  case 105: /* initializer_list: initializer  */
#line 462 "c99.y"
        {
            (yyval.list).items = malloc(sizeof(ASTNode*));
            (yyval.list).items[0] = (yyvsp[0].ast);
            (yyval.list).count    = 1;
        }
#line 2390 "c99.tab.c"
    break;

  case 106: /* initializer_list: initializer_list ',' initializer  */
#line 468 "c99.y"
        {
            (yyvsp[-2].list).items = realloc((yyvsp[-2].list).items,
                               sizeof(ASTNode*) * ((yyvsp[-2].list).count + 1));
            (yyvsp[-2].list).items[(yyvsp[-2].list).count++] = (yyvsp[0].ast);
            (yyval.list) = (yyvsp[-2].list);
        }
#line 2401 "c99.tab.c"
    break;

  case 107: /* statement: IDENTIFIER ':' statement  */
#line 478 "c99.y"
                                   { (yyval.ast) = ast_expr_stmt(NULL); }
#line 2407 "c99.tab.c"
    break;

  case 108: /* statement: compound_statement  */
#line 479 "c99.y"
                                   { (yyval.ast) = (yyvsp[0].ast); }
#line 2413 "c99.tab.c"
    break;

  case 109: /* statement: expression_statement  */
#line 480 "c99.y"
                                   { (yyval.ast) = (yyvsp[0].ast); }
#line 2419 "c99.tab.c"
    break;

  case 110: /* statement: selection_statement  */
#line 481 "c99.y"
                                   { (yyval.ast) = (yyvsp[0].ast); }
#line 2425 "c99.tab.c"
    break;

  case 111: /* statement: iteration_statement  */
#line 482 "c99.y"
                                   { (yyval.ast) = (yyvsp[0].ast); }
#line 2431 "c99.tab.c"
    break;

  case 112: /* statement: jump_statement  */
#line 483 "c99.y"
                                   { (yyval.ast) = (yyvsp[0].ast); }
#line 2437 "c99.tab.c"
    break;

  case 113: /* compound_statement: '{' '}'  */
#line 487 "c99.y"
                                   { (yyval.ast) = ast_compound(NULL, 0); }
#line 2443 "c99.tab.c"
    break;

  case 114: /* compound_statement: '{' block_item_list '}'  */
#line 488 "c99.y"
                                   { (yyval.ast) = ast_compound((yyvsp[-1].list).items, (yyvsp[-1].list).count); }
#line 2449 "c99.tab.c"
    break;

  case 115: /* block_item_list: block_item  */
#line 493 "c99.y"
        {
            (yyval.list).items = malloc(sizeof(ASTNode*));
            (yyval.list).items[0] = (yyvsp[0].ast);
            (yyval.list).count    = 1;
        }
#line 2459 "c99.tab.c"
    break;

  case 116: /* block_item_list: block_item_list block_item  */
#line 499 "c99.y"
        {
            (yyvsp[-1].list).items = realloc((yyvsp[-1].list).items, sizeof(ASTNode*) * ((yyvsp[-1].list).count + 1));
            (yyvsp[-1].list).items[(yyvsp[-1].list).count++] = (yyvsp[0].ast);
            (yyval.list) = (yyvsp[-1].list);
        }
#line 2469 "c99.tab.c"
    break;

  case 117: /* block_item: declaration  */
#line 507 "c99.y"
                                    { (yyval.ast) = (yyvsp[0].ast); }
#line 2475 "c99.tab.c"
    break;

  case 118: /* block_item: statement  */
#line 508 "c99.y"
                                    { (yyval.ast) = (yyvsp[0].ast); }
#line 2481 "c99.tab.c"
    break;

  case 119: /* expression_statement: ';'  */
#line 512 "c99.y"
                                    { (yyval.ast) = ast_expr_stmt(NULL); }
#line 2487 "c99.tab.c"
    break;

  case 120: /* expression_statement: expression ';'  */
#line 513 "c99.y"
                                    { (yyval.ast) = ast_expr_stmt((yyvsp[-1].ast)); }
#line 2493 "c99.tab.c"
    break;

  case 121: /* selection_statement: IF '(' expression ')' statement  */
#line 518 "c99.y"
        { (yyval.ast) = ast_if((yyvsp[-2].ast), (yyvsp[0].ast), NULL); }
#line 2499 "c99.tab.c"
    break;

  case 122: /* selection_statement: IF '(' expression ')' statement ELSE statement  */
#line 520 "c99.y"
        { (yyval.ast) = ast_if((yyvsp[-4].ast), (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 2505 "c99.tab.c"
    break;

  case 123: /* iteration_statement: WHILE '(' expression ')' statement  */
#line 525 "c99.y"
        { (yyval.ast) = ast_while((yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 2511 "c99.tab.c"
    break;

  case 124: /* iteration_statement: DO statement WHILE '(' expression ')' ';'  */
#line 527 "c99.y"
        { (yyval.ast) = ast_do_while((yyvsp[-5].ast), (yyvsp[-2].ast)); }
#line 2517 "c99.tab.c"
    break;

  case 125: /* iteration_statement: FOR '(' expression_statement expression_statement ')' statement  */
#line 529 "c99.y"
        { (yyval.ast) = ast_for((yyvsp[-3].ast), (yyvsp[-2].ast), NULL, (yyvsp[0].ast)); }
#line 2523 "c99.tab.c"
    break;

  case 126: /* iteration_statement: FOR '(' expression_statement expression_statement expression ')' statement  */
#line 531 "c99.y"
        { (yyval.ast) = ast_for((yyvsp[-4].ast), (yyvsp[-3].ast), (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 2529 "c99.tab.c"
    break;

  case 127: /* iteration_statement: FOR '(' declaration expression_statement ')' statement  */
#line 533 "c99.y"
        { (yyval.ast) = ast_for(ast_ext_decl((yyvsp[-3].ast)), (yyvsp[-2].ast), NULL, (yyvsp[0].ast)); }
#line 2535 "c99.tab.c"
    break;

  case 128: /* iteration_statement: FOR '(' declaration expression_statement expression ')' statement  */
#line 535 "c99.y"
        { (yyval.ast) = ast_for(ast_ext_decl((yyvsp[-4].ast)), (yyvsp[-3].ast), (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 2541 "c99.tab.c"
    break;

  case 129: /* jump_statement: CONTINUE ';'  */
#line 539 "c99.y"
                                    { (yyval.ast) = ast_continue(); }
#line 2547 "c99.tab.c"
    break;

  case 130: /* jump_statement: BREAK ';'  */
#line 540 "c99.y"
                                    { (yyval.ast) = ast_break(); }
#line 2553 "c99.tab.c"
    break;

  case 131: /* jump_statement: RETURN ';'  */
#line 541 "c99.y"
                                    { (yyval.ast) = ast_return(NULL); }
#line 2559 "c99.tab.c"
    break;

  case 132: /* jump_statement: RETURN expression ';'  */
#line 542 "c99.y"
                                    { (yyval.ast) = ast_return((yyvsp[-1].ast)); }
#line 2565 "c99.tab.c"
    break;

  case 133: /* external_declaration: function_definition  */
#line 547 "c99.y"
                                    { (yyval.ast) = ast_ext_decl((yyvsp[0].ast)); }
#line 2571 "c99.tab.c"
    break;

  case 134: /* external_declaration: declaration  */
#line 548 "c99.y"
                                    { (yyval.ast) = ast_ext_decl((yyvsp[0].ast)); }
#line 2577 "c99.tab.c"
    break;

  case 135: /* function_definition: declaration_specifiers declarator compound_statement  */
#line 553 "c99.y"
        {
            if ((yyvsp[-1].ast)->type == AST_FUNC_TYPE) {
                (yyvsp[-1].ast)->ft.ret_type = (yyvsp[-2].ast)->ds.specs[0];
                (yyvsp[-1].ast)->ft.body = (yyvsp[0].ast);
                (yyval.ast) = (yyvsp[-1].ast);
            } else {
                yyerror("Expected function declarator");
                (yyval.ast) = NULL;
            }
        }
#line 2592 "c99.tab.c"
    break;

  case 136: /* translation_unit: external_declaration  */
#line 567 "c99.y"
        {
            ASTNode **a = malloc(sizeof(ASTNode*));
            a[0] = (yyvsp[0].ast);
            ast_root = ast_trans_unit(a, 1);
        }
#line 2602 "c99.tab.c"
    break;

  case 137: /* translation_unit: translation_unit external_declaration  */
#line 573 "c99.y"
        {
            int old = ast_root->seq.count;
            ast_root->seq.list = realloc(ast_root->seq.list,
                                         sizeof(ASTNode*) * (old + 1));
            ast_root->seq.list[old] = (yyvsp[0].ast);
            ast_root->seq.count++;
        }
#line 2614 "c99.tab.c"
    break;


#line 2618 "c99.tab.c"

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
          YYNOMEM;
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
  ++yynerrs;

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
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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

#line 582 "c99.y"

/* Error handling & main */
extern int yylineno;
void yyerror(const char *msg) {
    fprintf(stderr, "Error at line %d: %s\n", yylineno, msg);
}
