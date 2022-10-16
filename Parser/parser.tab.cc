// A Bison parser, made by GNU Bison 3.5.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.



// First part of user prologue.
#line 10 "parser.y"

#  include <stdio.h>
#  include <stdlib.h>
#  include "funcs.h"

#line 46 "parser.tab.cc"


#include "parser.tab.hh"




#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 123 "parser.tab.cc"


  /// Build a parser object.
  parser::parser ()
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr)
#else

#endif
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/

  // basic_symbol.
#if 201103L <= YY_CPLUSPLUS
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (basic_symbol&& that)
    : Base (std::move (that))
    , value (std::move (that.value))
  {}
#endif

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t)
    : Base (t)
    , value ()
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (semantic_type) v)
    : Base (t)
    , value (YY_MOVE (v))
  {}

  template <typename Base>
  bool
  parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
  }

  // by_type.
  parser::by_type::by_type ()
    : type (empty_symbol)
  {}

#if 201103L <= YY_CPLUSPLUS
  parser::by_type::by_type (by_type&& that)
    : type (that.type)
  {
    that.clear ();
  }
#endif

  parser::by_type::by_type (const by_type& that)
    : type (that.type)
  {}

  parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  void
  parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  void
  parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  int
  parser::by_type::type_get () const YY_NOEXCEPT
  {
    return type;
  }


  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_number_type
  parser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[+state];
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value))
  {
    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.type_get ());
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " (";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.type = yytranslate_ (yylex (&yyla.value));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;


      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 57 "parser.y"
                                            { (yylhs.value.a) = newflow('W', (yystack_[2].value.a), (yystack_[0].value.a), NULL); }
#line 560 "parser.tab.cc"
    break;

  case 3:
#line 58 "parser.y"
                                          { (yylhs.value.a) = newfor('R',(yystack_[6].value.a),(yystack_[4].value.a),(yystack_[2].value.a),(yystack_[0].value.a));}
#line 566 "parser.tab.cc"
    break;

  case 4:
#line 59 "parser.y"
                                         { (yylhs.value.a) = rangefor('B', (yystack_[5].value.fn), (yystack_[4].value.s), (yystack_[2].value.s), (yystack_[0].value.a));}
#line 572 "parser.tab.cc"
    break;

  case 5:
#line 62 "parser.y"
                                                       { (yylhs.value.a) = newflow('I', (yystack_[2].value.a), (yystack_[0].value.a), NULL); }
#line 578 "parser.tab.cc"
    break;

  case 6:
#line 63 "parser.y"
                                    { (yylhs.value.a) = newflow('I', (yystack_[4].value.a), (yystack_[2].value.a), (yystack_[0].value.a)); }
#line 584 "parser.tab.cc"
    break;

  case 7:
#line 66 "parser.y"
                                 { (yylhs.value.a) = newinit((yystack_[4].value.fn),(yystack_[3].value.s),(yystack_[1].value.a));}
#line 590 "parser.tab.cc"
    break;

  case 8:
#line 67 "parser.y"
                      {  (yylhs.value.a) = settype((yystack_[2].value.fn), (yystack_[1].value.sl));}
#line 596 "parser.tab.cc"
    break;

  case 9:
#line 68 "parser.y"
                                        {(yylhs.value.a) = newginit((yystack_[7].value.fn),(yystack_[5].value.s),(yystack_[3].value.s),(yystack_[1].value.a));}
#line 602 "parser.tab.cc"
    break;

  case 10:
#line 77 "parser.y"
      { (yylhs.value.a) = (yystack_[0].value.a); }
#line 608 "parser.tab.cc"
    break;

  case 11:
#line 78 "parser.y"
     { (yylhs.value.a) = (yystack_[0].value.a); }
#line 614 "parser.tab.cc"
    break;

  case 12:
#line 79 "parser.y"
     { (yylhs.value.a) = (yystack_[0].value.a); }
#line 620 "parser.tab.cc"
    break;

  case 13:
#line 80 "parser.y"
                                                  { (yylhs.value.a) = bfs(16, (yystack_[7].value.fn), (yystack_[6].value.s), (yystack_[4].value.s), (yystack_[2].value.s), (yystack_[0].value.a)); }
#line 626 "parser.tab.cc"
    break;

  case 14:
#line 81 "parser.y"
                                                  { (yylhs.value.a) = dfs(17, (yystack_[7].value.fn), (yystack_[6].value.s), (yystack_[4].value.s), (yystack_[2].value.s), (yystack_[0].value.a)); }
#line 632 "parser.tab.cc"
    break;

  case 15:
#line 82 "parser.y"
     { (yylhs.value.a) = (yystack_[1].value.a); }
#line 638 "parser.tab.cc"
    break;

  case 16:
#line 83 "parser.y"
                   { (yylhs.value.a) = (yystack_[1].value.a); }
#line 644 "parser.tab.cc"
    break;

  case 17:
#line 87 "parser.y"
           { (yylhs.value.a) = newast('L',(yystack_[0].value.a),NULL); }
#line 650 "parser.tab.cc"
    break;

  case 18:
#line 88 "parser.y"
               { (yylhs.value.a) = newast('L', (yystack_[1].value.a), (yystack_[0].value.a));}
#line 656 "parser.tab.cc"
    break;

  case 19:
#line 91 "parser.y"
                          { (yylhs.value.a) = newedge((yystack_[2].value.i),(yystack_[0].value.i));}
#line 662 "parser.tab.cc"
    break;

  case 20:
#line 94 "parser.y"
         { (yylhs.value.a) = (yystack_[0].value.a); }
#line 668 "parser.tab.cc"
    break;

  case 21:
#line 95 "parser.y"
                          { (yylhs.value.a) = newdouble((yystack_[0].value.d)); }
#line 674 "parser.tab.cc"
    break;

  case 22:
#line 96 "parser.y"
                          { (yylhs.value.a) = newint((yystack_[0].value.i)); }
#line 680 "parser.tab.cc"
    break;

  case 23:
#line 97 "parser.y"
                          { (yylhs.value.a) = newstr((yystack_[0].value.str)); }
#line 686 "parser.tab.cc"
    break;

  case 24:
#line 100 "parser.y"
              { (yylhs.value.a) = (yystack_[0].value.a); }
#line 692 "parser.tab.cc"
    break;

  case 25:
#line 101 "parser.y"
                           { (yylhs.value.a) = newast('L', (yystack_[2].value.a), (yystack_[0].value.a)); }
#line 698 "parser.tab.cc"
    break;

  case 26:
#line 103 "parser.y"
                            {(yylhs.value.a) = newarray((yystack_[1].value.a));}
#line 704 "parser.tab.cc"
    break;

  case 27:
#line 105 "parser.y"
                          { (yylhs.value.a) = newcmp((yystack_[1].value.fn), (yystack_[2].value.a), (yystack_[0].value.a)); }
#line 710 "parser.tab.cc"
    break;

  case 28:
#line 106 "parser.y"
                          { (yylhs.value.a) = newast(1000, (yystack_[2].value.a),(yystack_[0].value.a));}
#line 716 "parser.tab.cc"
    break;

  case 29:
#line 107 "parser.y"
                          { (yylhs.value.a) = newast(1001, (yystack_[2].value.a),(yystack_[0].value.a));}
#line 722 "parser.tab.cc"
    break;

  case 30:
#line 108 "parser.y"
                          { (yylhs.value.a) = newast('+', (yystack_[2].value.a),(yystack_[0].value.a)); }
#line 728 "parser.tab.cc"
    break;

  case 31:
#line 109 "parser.y"
                          { (yylhs.value.a) = newast('-', (yystack_[2].value.a),(yystack_[0].value.a)); }
#line 734 "parser.tab.cc"
    break;

  case 32:
#line 110 "parser.y"
                          { (yylhs.value.a) = newast('*', (yystack_[2].value.a),(yystack_[0].value.a)); }
#line 740 "parser.tab.cc"
    break;

  case 33:
#line 111 "parser.y"
                          { (yylhs.value.a) = newast('/', (yystack_[2].value.a),(yystack_[0].value.a)); }
#line 746 "parser.tab.cc"
    break;

  case 34:
#line 112 "parser.y"
                          { (yylhs.value.a) = newast('%', (yystack_[2].value.a),(yystack_[0].value.a)); }
#line 752 "parser.tab.cc"
    break;

  case 35:
#line 113 "parser.y"
                          { (yylhs.value.a) = newast('|', (yystack_[0].value.a), NULL); }
#line 758 "parser.tab.cc"
    break;

  case 36:
#line 114 "parser.y"
                          { (yylhs.value.a) = (yystack_[1].value.a); }
#line 764 "parser.tab.cc"
    break;

  case 37:
#line 115 "parser.y"
                          { (yylhs.value.a) = newast('M', (yystack_[0].value.a), NULL); }
#line 770 "parser.tab.cc"
    break;

  case 38:
#line 116 "parser.y"
     { (yylhs.value.a) = (yystack_[0].value.a); }
#line 776 "parser.tab.cc"
    break;

  case 39:
#line 117 "parser.y"
     { (yylhs.value.a) = (yystack_[0].value.a); }
#line 782 "parser.tab.cc"
    break;

  case 40:
#line 118 "parser.y"
                          { (yylhs.value.a) = newfunc((yystack_[3].value.fn), (yystack_[1].value.a)); }
#line 788 "parser.tab.cc"
    break;

  case 41:
#line 119 "parser.y"
                          { (yylhs.value.a) = newref((yystack_[0].value.s)); }
#line 794 "parser.tab.cc"
    break;

  case 42:
#line 120 "parser.y"
                          { (yylhs.value.a) = newasgn((yystack_[2].value.s), (yystack_[0].value.a)); }
#line 800 "parser.tab.cc"
    break;

  case 43:
#line 121 "parser.y"
                          { (yylhs.value.a) = newcall((yystack_[3].value.s), (yystack_[1].value.a)); }
#line 806 "parser.tab.cc"
    break;

  case 44:
#line 122 "parser.y"
                         { (yylhs.value.a) =  newasgn_ops((yystack_[1].value.fn),(yystack_[2].value.s),(yystack_[0].value.a)); }
#line 812 "parser.tab.cc"
    break;

  case 45:
#line 125 "parser.y"
         { (yylhs.value.a) = (yystack_[0].value.a); }
#line 818 "parser.tab.cc"
    break;

  case 46:
#line 126 "parser.y"
                    { (yylhs.value.a) = newast('L', (yystack_[2].value.a), (yystack_[0].value.a)); }
#line 824 "parser.tab.cc"
    break;

  case 47:
#line 129 "parser.y"
               { (yylhs.value.s) = (yystack_[0].value.s);(yystack_[0].value.s)->type = TYPE;}
#line 830 "parser.tab.cc"
    break;

  case 48:
#line 132 "parser.y"
                    { (yylhs.value.sl) = newsymlist((yystack_[0].value.s),NULL); }
#line 836 "parser.tab.cc"
    break;

  case 49:
#line 133 "parser.y"
                    { (yylhs.value.sl) = newsymlist((yystack_[2].value.s),(yystack_[0].value.sl)); }
#line 842 "parser.tab.cc"
    break;

  case 50:
#line 136 "parser.y"
                    { (yylhs.value.sl) = newsymlist((yystack_[0].value.s), NULL); }
#line 848 "parser.tab.cc"
    break;

  case 51:
#line 137 "parser.y"
                    { (yylhs.value.sl) = newsymlist((yystack_[2].value.s), (yystack_[0].value.sl)); }
#line 854 "parser.tab.cc"
    break;

  case 52:
#line 140 "parser.y"
                       {(yylhs.value.a)=(yystack_[0].value.a);}
#line 860 "parser.tab.cc"
    break;

  case 53:
#line 141 "parser.y"
                                           {
                            dodef((yystack_[7].value.fn),(yystack_[6].value.s), (yystack_[4].value.sl), (yystack_[1].value.a));
                            (yylhs.value.a)= newdef((yystack_[6].value.s));
                      //  printf("Defined %s\n> ", $2->name); 
                      }
#line 870 "parser.tab.cc"
    break;

  case 54:
#line 146 "parser.y"
          {}
#line 876 "parser.tab.cc"
    break;

  case 55:
#line 148 "parser.y"
                   { (yylhs.value.a) = (yystack_[0].value.a); }
#line 882 "parser.tab.cc"
    break;

  case 56:
#line 149 "parser.y"
                                      { (yylhs.value.a) = newast('T', (yystack_[1].value.a), (yystack_[0].value.a)); }
#line 888 "parser.tab.cc"
    break;

  case 57:
#line 151 "parser.y"
                              { dumpast((yystack_[0].value.a),0);}
#line 894 "parser.tab.cc"
    break;


#line 898 "parser.tab.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yysyntax_error_ (yystack_[0].state, yyla));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[+yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yy_error_token_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yy_error_token_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }


      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
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


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type, const symbol_type&) const
  {
    return YY_("syntax error");
  }


  const signed char parser::yypact_ninf_ = -46;

  const signed char parser::yytable_ninf_ = -58;

  const short
  parser::yypact_[] =
  {
     159,   -46,   -46,   -23,   -46,    26,   -14,    -3,    -2,    -1,
       2,    16,    29,    33,    33,    33,   174,   -46,   -46,   -46,
     -46,   -46,   -46,   -46,    72,   -46,   123,    68,    66,    33,
      33,    33,    33,    36,    71,    37,    33,    33,    49,    73,
      75,   116,   -46,   -46,   227,     1,   174,    35,    28,    40,
      33,    33,    33,    33,    33,    33,    33,    33,   -46,   -46,
     -46,   -46,    84,    84,   -12,    51,    52,    33,    88,   102,
      82,   -46,   237,   247,   103,   187,   111,   129,    85,   -46,
     -13,   -46,   -46,   116,   -46,   276,    62,   267,   113,   113,
     -46,   -46,   -46,    33,   -46,   -46,   197,   133,   109,   114,
     110,   -46,   143,   174,   174,   115,    33,   117,   119,   -46,
     -46,   -46,   -46,    88,   120,   127,   147,   -46,   153,   207,
     163,   165,   -46,   174,    33,   174,   141,    33,   139,   154,
     145,   217,   -46,   174,   257,   188,   189,   -46,   -46,   -46,
     174,   162,   164,   -46,   174,   174,   -46,   -46
  };

  const signed char
  parser::yydefact_[] =
  {
       0,    54,    21,    22,    23,    41,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    11,    10,    12,
      52,    20,    38,    39,     0,    55,     0,     0,     0,     0,
       0,     0,     0,    50,     0,     0,     0,     0,     0,     0,
       0,     0,    37,    35,     0,     0,    17,     0,    38,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    15,    56,
       1,    19,    44,    42,    45,     0,     0,     0,     0,     0,
       0,     8,     0,     0,     0,     0,     0,     0,    24,    36,
      50,    18,    16,     0,    26,    28,    29,    27,    30,    31,
      32,    33,    34,     0,    43,    40,     0,     0,    48,     0,
      50,    51,     0,     0,     0,     0,     0,     0,     0,    25,
      46,     7,    47,     0,     0,     0,     5,     2,     0,     0,
       0,     0,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     6,     0,     0,     0,     0,    53,     9,     4,
       0,     0,     0,     3,     0,     0,    13,    14
  };

  const short
  parser::yypgoto_[] =
  {
     -46,   -46,   -46,   -46,     0,   -45,   -46,    -8,   121,   -46,
      -9,   -30,   -46,    80,   130,   176,   -46,   -46
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,    17,    18,    19,    46,    47,    21,    22,    49,    23,
      24,    65,    98,    99,    35,    25,    26,    27
  };

  const short
  parser::yytable_[] =
  {
      20,    81,    66,    33,    42,    43,    44,    80,    48,    50,
      51,    52,    67,    28,    53,    54,    55,    56,    57,    32,
      62,    63,    64,    64,    69,    93,    20,    72,    73,    75,
      34,    36,    37,    78,    34,    38,     2,     3,     4,     5,
       6,    85,    86,    87,    88,    89,    90,    91,    92,    39,
      29,    30,     2,     3,     4,     5,     6,    74,    96,    31,
      13,    67,    40,   110,    14,    83,    15,   -24,    60,    68,
      61,    41,    71,    69,    82,    78,    13,    70,   130,    84,
      14,    76,    15,    77,    64,    94,    95,    41,    53,    54,
      55,    56,    57,    50,    51,    52,    97,   119,    53,    54,
      55,    56,    57,   116,   117,    50,    51,    58,   100,   105,
      53,    54,    55,    56,    57,   131,   102,   107,   134,     2,
       3,     4,    83,   -57,     1,   132,     2,     3,     4,     5,
       6,     7,     8,   139,     9,   108,    10,    11,    12,   112,
     143,    55,    56,    57,   146,   147,   113,    69,   114,   115,
      13,   118,   124,   120,    14,   121,    15,   125,   123,   126,
       1,    16,     2,     3,     4,     5,     6,     7,     8,   128,
       9,   129,    10,    11,    12,   133,   135,     2,     3,     4,
       5,     6,    45,     8,   137,     9,    13,    10,    11,    12,
      14,   136,    15,   122,   141,   142,   144,    16,   145,   101,
       0,    13,    59,     0,   109,    14,     0,    15,    50,    51,
      52,     0,    16,    53,    54,    55,    56,    57,    50,    51,
      52,     0,   106,    53,    54,    55,    56,    57,    50,    51,
      52,     0,   111,    53,    54,    55,    56,    57,    50,    51,
      52,     0,   127,    53,    54,    55,    56,    57,    50,    51,
      52,     0,   138,    53,    54,    55,    56,    57,    50,    51,
      52,    79,     0,    53,    54,    55,    56,    57,    50,    51,
      52,   103,     0,    53,    54,    55,    56,    57,    50,    51,
      52,   104,     0,    53,    54,    55,    56,    57,    50,    51,
     -58,   140,     0,    53,    54,    55,    56,    57,    51,     0,
       0,     0,    53,    54,    55,    56,    57
  };

  const short
  parser::yycheck_[] =
  {
       0,    46,    32,     6,    13,    14,    15,     6,    16,    21,
      22,    23,    25,    36,    26,    27,    28,    29,    30,    33,
      29,    30,    31,    32,    37,    37,    26,    36,    37,    38,
      33,    33,    33,    41,    33,    33,     3,     4,     5,     6,
       7,    50,    51,    52,    53,    54,    55,    56,    57,    33,
      24,    25,     3,     4,     5,     6,     7,     8,    67,    33,
      27,    25,    33,    93,    31,    37,    33,    39,     0,    33,
       4,    38,    35,    37,    39,    83,    27,     6,   123,    39,
      31,     8,    33,     8,    93,    34,    34,    38,    26,    27,
      28,    29,    30,    21,    22,    23,     8,   106,    26,    27,
      28,    29,    30,   103,   104,    21,    22,    35,     6,     6,
      26,    27,    28,    29,    30,   124,    34,     6,   127,     3,
       4,     5,    37,     0,     1,   125,     3,     4,     5,     6,
       7,     8,     9,   133,    11,     6,    13,    14,    15,     6,
     140,    28,    29,    30,   144,   145,    37,    37,    34,     6,
      27,    36,    25,    36,    31,    36,    33,    10,    38,     6,
       1,    38,     3,     4,     5,     6,     7,     8,     9,     6,
      11,     6,    13,    14,    15,    34,    37,     3,     4,     5,
       6,     7,     8,     9,    39,    11,    27,    13,    14,    15,
      31,    37,    33,   113,     6,     6,    34,    38,    34,    69,
      -1,    27,    26,    -1,    83,    31,    -1,    33,    21,    22,
      23,    -1,    38,    26,    27,    28,    29,    30,    21,    22,
      23,    -1,    35,    26,    27,    28,    29,    30,    21,    22,
      23,    -1,    35,    26,    27,    28,    29,    30,    21,    22,
      23,    -1,    35,    26,    27,    28,    29,    30,    21,    22,
      23,    -1,    35,    26,    27,    28,    29,    30,    21,    22,
      23,    34,    -1,    26,    27,    28,    29,    30,    21,    22,
      23,    34,    -1,    26,    27,    28,    29,    30,    21,    22,
      23,    34,    -1,    26,    27,    28,    29,    30,    21,    22,
      23,    34,    -1,    26,    27,    28,    29,    30,    22,    -1,
      -1,    -1,    26,    27,    28,    29,    30
  };

  const signed char
  parser::yystos_[] =
  {
       0,     1,     3,     4,     5,     6,     7,     8,     9,    11,
      13,    14,    15,    27,    31,    33,    38,    41,    42,    43,
      44,    46,    47,    49,    50,    55,    56,    57,    36,    24,
      25,    33,    33,     6,    33,    54,    33,    33,    33,    33,
      33,    38,    50,    50,    50,     8,    44,    45,    47,    48,
      21,    22,    23,    26,    27,    28,    29,    30,    35,    55,
       0,     4,    50,    50,    50,    51,    51,    25,    33,    37,
       6,    35,    50,    50,     8,    50,     8,     8,    47,    34,
       6,    45,    39,    37,    39,    50,    50,    50,    50,    50,
      50,    50,    50,    37,    34,    34,    50,     8,    52,    53,
       6,    54,    34,    34,    34,     6,    35,     6,     6,    48,
      51,    35,     6,    37,    34,     6,    44,    44,    36,    50,
      36,    36,    53,    38,    25,    10,     6,    35,     6,     6,
      45,    50,    44,    34,    50,    37,    37,    39,    35,    44,
      34,     6,     6,    44,    34,    34,    44,    44
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    40,    41,    41,    41,    42,    42,    43,    43,    43,
      44,    44,    44,    44,    44,    44,    44,    45,    45,    46,
      47,    47,    47,    47,    48,    48,    49,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    51,    51,    52,    53,    53,
      54,    54,    55,    55,    55,    56,    56,    57
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     5,     9,     8,     5,     7,     5,     3,     8,
       1,     1,     1,    10,    10,     2,     3,     1,     2,     3,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     3,     2,     1,     1,
       4,     1,     3,     4,     3,     1,     3,     2,     1,     3,
       1,     3,     1,     8,     1,     1,     2,     1
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "$end", "error", "$undefined", "DOUBLE", "INT", "STRING", "NAME",
  "FUNC", "TYPE", "IF", "ELSE", "WHILE", "LOWER_THAN_ELSE", "FOR", "BFS",
  "DFS", "NODES", "LEVELS", "NEIGHBOURS", "INC", "DEC", "LOG_OR",
  "LOG_AND", "CMP", "ASGN", "'='", "'+'", "'-'", "'*'", "'/'", "'%'",
  "'|'", "UMINUS", "'('", "')'", "';'", "':'", "','", "'{'", "'}'",
  "$accept", "iterstmt", "condstmt", "initstmt", "stmt", "list", "edge",
  "literal", "literal_list", "array", "exp", "explist", "arg", "arglist",
  "symlist", "translation_unit", "translation_list", "start_unit", YY_NULLPTR
  };


  const unsigned char
  parser::yyrline_[] =
  {
       0,    57,    57,    58,    59,    62,    63,    66,    67,    68,
      77,    78,    79,    80,    81,    82,    83,    87,    88,    91,
      94,    95,    96,    97,   100,   101,   103,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   125,   126,   129,   132,   133,
     136,   137,   140,   141,   146,   148,   149,   151
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  parser::token_number_type
  parser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const token_number_type
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    30,     2,     2,
      33,    34,    28,    26,    37,    27,     2,    29,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    36,    35,
       2,    25,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    38,    31,    39,     2,     2,     2,     2,
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
      32
    };
    const int user_token_number_max_ = 280;

    if (t <= 0)
      return yyeof_;
    else if (t <= user_token_number_max_)
      return translate_table[t];
    else
      return yy_undef_token_;
  }

} // yy
#line 1355 "parser.tab.cc"

#line 152 "parser.y"

