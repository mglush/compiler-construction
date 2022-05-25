/* A Bison parser, made by GNU Bison 3.7.4.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    t_print = 258,                 /* t_print  */
    t_return = 259,                /* t_return  */
    t_if = 260,                    /* t_if  */
    t_else = 261,                  /* t_else  */
    t_while = 262,                 /* t_while  */
    t_new = 263,                   /* t_new  */
    t_equals = 264,                /* t_equals  */
    t_and = 265,                   /* t_and  */
    t_or = 266,                    /* t_or  */
    t_not = 267,                   /* t_not  */
    t_extends = 268,               /* t_extends  */
    t_do = 269,                    /* t_do  */
    t_true = 270,                  /* t_true  */
    t_false = 271,                 /* t_false  */
    t_arrow = 272,                 /* t_arrow  */
    t_geq = 273,                   /* t_geq  */
    unary_minus = 274,             /* unary_minus  */
    t_id = 275,                    /* t_id  */
    t_int_type = 276,              /* t_int_type  */
    t_bool_type = 277,             /* t_bool_type  */
    t_none_type = 278,             /* t_none_type  */
    t_number = 279                 /* t_number  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
