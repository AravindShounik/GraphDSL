// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

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

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "parser.tab.hh"


// Unqualified %code blocks.
#line 41 "parser.yy"

#include "driver.hh"
#define yylex driver.lexer.yylex

#define ctx driver.ctx
#define M(x) std::move(x)
#define C(x) node(x)

#line 55 "parser.tab.cc"


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

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


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
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
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
#line 147 "parser.tab.cc"

  /// Build a parser object.
  parser::parser (Driver& driver_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      driver (driver_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



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

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_DOUBLE_CONST: // "double_const"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declarations: // declarations
      case symbol_kind::S_declaration: // declaration
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_expression_stmt: // expression_stmt
      case symbol_kind::S_jump_stmt: // jump_stmt
      case symbol_kind::S_empty_stmt: // empty_stmt
      case symbol_kind::S_vardec_stmt: // vardec_stmt
      case symbol_kind::S_initializer: // initializer
      case symbol_kind::S_initializer_list: // initializer_list
      case symbol_kind::S_edge: // edge
      case symbol_kind::S_compound_stmt: // compound_stmt
      case symbol_kind::S_selection_stmt: // selection_stmt
      case symbol_kind::S_iteration_stmt: // iteration_stmt
      case symbol_kind::S_p_expr: // p_expr
      case symbol_kind::S_exprs: // exprs
      case symbol_kind::S_expr: // expr
        value.YY_MOVE_OR_COPY< node > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
      case symbol_kind::S_identifier: // identifier
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_typename: // typename
        value.YY_MOVE_OR_COPY< type_name > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_DOUBLE_CONST: // "double_const"
        value.move< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declarations: // declarations
      case symbol_kind::S_declaration: // declaration
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_expression_stmt: // expression_stmt
      case symbol_kind::S_jump_stmt: // jump_stmt
      case symbol_kind::S_empty_stmt: // empty_stmt
      case symbol_kind::S_vardec_stmt: // vardec_stmt
      case symbol_kind::S_initializer: // initializer
      case symbol_kind::S_initializer_list: // initializer_list
      case symbol_kind::S_edge: // edge
      case symbol_kind::S_compound_stmt: // compound_stmt
      case symbol_kind::S_selection_stmt: // selection_stmt
      case symbol_kind::S_iteration_stmt: // iteration_stmt
      case symbol_kind::S_p_expr: // p_expr
      case symbol_kind::S_exprs: // exprs
      case symbol_kind::S_expr: // expr
        value.move< node > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
      case symbol_kind::S_identifier: // identifier
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_typename: // typename
        value.move< type_name > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_DOUBLE_CONST: // "double_const"
        value.copy< double > (that.value);
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_declarations: // declarations
      case symbol_kind::S_declaration: // declaration
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_expression_stmt: // expression_stmt
      case symbol_kind::S_jump_stmt: // jump_stmt
      case symbol_kind::S_empty_stmt: // empty_stmt
      case symbol_kind::S_vardec_stmt: // vardec_stmt
      case symbol_kind::S_initializer: // initializer
      case symbol_kind::S_initializer_list: // initializer_list
      case symbol_kind::S_edge: // edge
      case symbol_kind::S_compound_stmt: // compound_stmt
      case symbol_kind::S_selection_stmt: // selection_stmt
      case symbol_kind::S_iteration_stmt: // iteration_stmt
      case symbol_kind::S_p_expr: // p_expr
      case symbol_kind::S_exprs: // exprs
      case symbol_kind::S_expr: // expr
        value.copy< node > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
      case symbol_kind::S_identifier: // identifier
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_typename: // typename
        value.copy< type_name > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_DOUBLE_CONST: // "double_const"
        value.move< double > (that.value);
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.move< int > (that.value);
        break;

      case symbol_kind::S_declarations: // declarations
      case symbol_kind::S_declaration: // declaration
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_expression_stmt: // expression_stmt
      case symbol_kind::S_jump_stmt: // jump_stmt
      case symbol_kind::S_empty_stmt: // empty_stmt
      case symbol_kind::S_vardec_stmt: // vardec_stmt
      case symbol_kind::S_initializer: // initializer
      case symbol_kind::S_initializer_list: // initializer_list
      case symbol_kind::S_edge: // edge
      case symbol_kind::S_compound_stmt: // compound_stmt
      case symbol_kind::S_selection_stmt: // selection_stmt
      case symbol_kind::S_iteration_stmt: // iteration_stmt
      case symbol_kind::S_p_expr: // p_expr
      case symbol_kind::S_exprs: // exprs
      case symbol_kind::S_expr: // expr
        value.move< node > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
      case symbol_kind::S_identifier: // identifier
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_typename: // typename
        value.move< type_name > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
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
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
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
  parser::yypop_ (int n) YY_NOEXCEPT
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
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
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

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    // User initialization code.
#line 30 "parser.yy"
{
    // Initialize the initial location.
    yyla.location.begin.filename = yyla.location.end.filename = &driver.file;
}

#line 561 "parser.tab.cc"


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
    YY_STACK_PRINT ();

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
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (driver));
            yyla.move (yylookahead);
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

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
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
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_DOUBLE_CONST: // "double_const"
        yylhs.value.emplace< double > ();
        break;

      case symbol_kind::S_NUMBER: // "number"
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_declarations: // declarations
      case symbol_kind::S_declaration: // declaration
      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_expression_stmt: // expression_stmt
      case symbol_kind::S_jump_stmt: // jump_stmt
      case symbol_kind::S_empty_stmt: // empty_stmt
      case symbol_kind::S_vardec_stmt: // vardec_stmt
      case symbol_kind::S_initializer: // initializer
      case symbol_kind::S_initializer_list: // initializer_list
      case symbol_kind::S_edge: // edge
      case symbol_kind::S_compound_stmt: // compound_stmt
      case symbol_kind::S_selection_stmt: // selection_stmt
      case symbol_kind::S_iteration_stmt: // iteration_stmt
      case symbol_kind::S_p_expr: // p_expr
      case symbol_kind::S_exprs: // exprs
      case symbol_kind::S_expr: // expr
        yylhs.value.emplace< node > ();
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
      case symbol_kind::S_identifier: // identifier
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_typename: // typename
        yylhs.value.emplace< type_name > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // $@1: %empty
#line 147 "parser.yy"
         { ++ctx; }
#line 736 "parser.tab.cc"
    break;

  case 3: // program: $@1 declarations
#line 147 "parser.yy"
                                 { --ctx; ctx.dump_ast(); }
#line 742 "parser.tab.cc"
    break;

  case 4: // declarations: declarations declaration
#line 148 "parser.yy"
                                       { }
#line 748 "parser.tab.cc"
    break;

  case 7: // declaration: vardec_stmt SEMI_COLON
#line 152 "parser.yy"
                                    { yylhs.value.as < node > () = yystack_[1].value.as < node > (); }
#line 754 "parser.tab.cc"
    break;

  case 8: // $@2: %empty
#line 155 "parser.yy"
                              { ctx.defun(yystack_[0].value.as < std::string > ()); ++ctx; }
#line 760 "parser.tab.cc"
    break;

  case 9: // function: typename identifier $@2 LPAREN paramdecls RPAREN compound_stmt RBRACE
#line 155 "parser.yy"
                                                                                                      { ctx.add_function(M(yystack_[6].value.as < std::string > ()), M(yystack_[1].value.as < node > ()), yystack_[7].value.as < type_name > ()); --ctx; }
#line 766 "parser.tab.cc"
    break;

  case 12: // paramdecl: paramdecl COMMA typename identifier
#line 160 "parser.yy"
                                                { ctx.defparam(yystack_[0].value.as < std::string > (), yystack_[1].value.as < type_name > ()); }
#line 772 "parser.tab.cc"
    break;

  case 13: // paramdecl: typename identifier
#line 161 "parser.yy"
                                { ctx.defparam(yystack_[0].value.as < std::string > (), yystack_[1].value.as < type_name > ()); }
#line 778 "parser.tab.cc"
    break;

  case 14: // typename: "void"
#line 163 "parser.yy"
               { yylhs.value.as < type_name > () = type_name::VOID; }
#line 784 "parser.tab.cc"
    break;

  case 15: // typename: "int"
#line 164 "parser.yy"
              { yylhs.value.as < type_name > () = type_name::INT; }
#line 790 "parser.tab.cc"
    break;

  case 16: // typename: "bool"
#line 165 "parser.yy"
               { yylhs.value.as < type_name > () = type_name::BOOL; }
#line 796 "parser.tab.cc"
    break;

  case 17: // typename: "char"
#line 166 "parser.yy"
               { yylhs.value.as < type_name > () = type_name::CHAR; }
#line 802 "parser.tab.cc"
    break;

  case 18: // typename: "float"
#line 167 "parser.yy"
                { yylhs.value.as < type_name > () = type_name::FLOAT; }
#line 808 "parser.tab.cc"
    break;

  case 19: // typename: "string"
#line 168 "parser.yy"
                 { yylhs.value.as < type_name > () = type_name::STRING; }
#line 814 "parser.tab.cc"
    break;

  case 20: // typename: "graph"
#line 169 "parser.yy"
                { yylhs.value.as < type_name > () = type_name::GRAPH; }
#line 820 "parser.tab.cc"
    break;

  case 21: // typename: "dgraph"
#line 170 "parser.yy"
                 { yylhs.value.as < type_name > () = type_name::DGRAPH; }
#line 826 "parser.tab.cc"
    break;

  case 28: // stmt: compound_stmt RBRACE
#line 179 "parser.yy"
                           { yylhs.value.as < node > () = M(yystack_[1].value.as < node > ()); --ctx; }
#line 832 "parser.tab.cc"
    break;

  case 29: // stmt: selection_stmt
#line 180 "parser.yy"
      { yylhs.value.as < node > () = yystack_[0].value.as < node > (); }
#line 838 "parser.tab.cc"
    break;

  case 30: // stmt: jump_stmt
#line 181 "parser.yy"
      { yylhs.value.as < node > () = yystack_[0].value.as < node > (); }
#line 844 "parser.tab.cc"
    break;

  case 31: // stmt: expression_stmt
#line 182 "parser.yy"
      { yylhs.value.as < node > () = yystack_[0].value.as < node > (); }
#line 850 "parser.tab.cc"
    break;

  case 32: // stmt: empty_stmt
#line 183 "parser.yy"
      { yylhs.value.as < node > () = yystack_[0].value.as < node > (); }
#line 856 "parser.tab.cc"
    break;

  case 33: // stmt: vardec_stmt SEMI_COLON
#line 184 "parser.yy"
                             { yylhs.value.as < node > () = yystack_[1].value.as < node > (); }
#line 862 "parser.tab.cc"
    break;

  case 34: // stmt: iteration_stmt
#line 185 "parser.yy"
      { yylhs.value.as < node > () = yystack_[0].value.as < node > (); }
#line 868 "parser.tab.cc"
    break;

  case 35: // expression_stmt: exprs SEMI_COLON
#line 187 "parser.yy"
                                  { yylhs.value.as < node > () = M(yystack_[1].value.as < node > ()); }
#line 874 "parser.tab.cc"
    break;

  case 36: // jump_stmt: "continue" SEMI_COLON
#line 189 "parser.yy"
                               { yylhs.value.as < node > () = n_cont(); }
#line 880 "parser.tab.cc"
    break;

  case 37: // jump_stmt: "break" SEMI_COLON
#line 190 "parser.yy"
                             { yylhs.value.as < node > () = n_br(); }
#line 886 "parser.tab.cc"
    break;

  case 38: // jump_stmt: "return" SEMI_COLON
#line 191 "parser.yy"
                              { yylhs.value.as < node > () = n_ret(); }
#line 892 "parser.tab.cc"
    break;

  case 39: // jump_stmt: "return" expr SEMI_COLON
#line 192 "parser.yy"
                                                   { yylhs.value.as < node > () = n_ret(M(yystack_[1].value.as < node > ()));         }
#line 898 "parser.tab.cc"
    break;

  case 41: // vardec_stmt: typename identifier ASSIGN initializer
#line 196 "parser.yy"
                                                    { ctx.temptype = yystack_[3].value.as < type_name > ();  yylhs.value.as < node > () = n_comma(M(ctx.def(yystack_[2].value.as < std::string > ()) %= M(yystack_[0].value.as < node > ()))); }
#line 904 "parser.tab.cc"
    break;

  case 42: // vardec_stmt: typename identifier
#line 197 "parser.yy"
                                 { ctx.temptype = yystack_[1].value.as < type_name > (); yylhs.value.as < node > () = n_comma(M(ctx.def(yystack_[0].value.as < std::string > ()) %= 0)); }
#line 910 "parser.tab.cc"
    break;

  case 43: // vardec_stmt: vardec_stmt COMMA identifier ASSIGN initializer
#line 198 "parser.yy"
                                                             { yylhs.value.as < node > () = M(yystack_[4].value.as < node > ()); yylhs.value.as < node > ().params.push_back(M(ctx.def(yystack_[2].value.as < std::string > ()) %= M(yystack_[0].value.as < node > ()))); }
#line 916 "parser.tab.cc"
    break;

  case 44: // vardec_stmt: vardec_stmt COMMA identifier
#line 199 "parser.yy"
                                          { yylhs.value.as < node > () = M(yystack_[2].value.as < node > ()); yylhs.value.as < node > ().params.push_back(M(ctx.def(yystack_[0].value.as < std::string > ()) %= 0)); }
#line 922 "parser.tab.cc"
    break;

  case 45: // initializer: expr
#line 210 "parser.yy"
             { yylhs.value.as < node > () = yystack_[0].value.as < node > (); }
#line 928 "parser.tab.cc"
    break;

  case 46: // initializer: edge
#line 211 "parser.yy"
             { yylhs.value.as < node > () = yystack_[0].value.as < node > (); }
#line 934 "parser.tab.cc"
    break;

  case 47: // initializer: LBRACE initializer_list RBRACE
#line 212 "parser.yy"
                                            { yylhs.value.as < node > () = M(yystack_[1].value.as < node > ()); }
#line 940 "parser.tab.cc"
    break;

  case 48: // initializer_list: initializer
#line 214 "parser.yy"
                              { yylhs.value.as < node > () = n_init_list(M(yystack_[0].value.as < node > ())); }
#line 946 "parser.tab.cc"
    break;

  case 49: // initializer_list: initializer_list COMMA initializer
#line 215 "parser.yy"
                                                     { yylhs.value.as < node > () = M(yystack_[2].value.as < node > ()); yylhs.value.as < node > ().params.push_back(yystack_[0].value.as < node > ()); }
#line 952 "parser.tab.cc"
    break;

  case 50: // edge: "number" COLON "number"
#line 217 "parser.yy"
                          { yylhs.value.as < node > () = n_edge(yystack_[2].value.as < int > (), yystack_[0].value.as < int > ()); }
#line 958 "parser.tab.cc"
    break;

  case 51: // compound_stmt: LBRACE
#line 220 "parser.yy"
                       { yylhs.value.as < node > () = n_comma(); ++ctx; }
#line 964 "parser.tab.cc"
    break;

  case 52: // compound_stmt: compound_stmt stmt
#line 221 "parser.yy"
                                   { yylhs.value.as < node > () = M(yystack_[1].value.as < node > ()); yylhs.value.as < node > ().params.push_back(M(yystack_[0].value.as < node > ())); }
#line 970 "parser.tab.cc"
    break;

  case 53: // selection_stmt: "if" p_expr stmt
#line 223 "parser.yy"
                                                      { yylhs.value.as < node > () = n_cand(M(yystack_[1].value.as < node > ()), M(yystack_[0].value.as < node > ())); }
#line 976 "parser.tab.cc"
    break;

  case 55: // iteration_stmt: "while" p_expr stmt
#line 226 "parser.yy"
                                           { yylhs.value.as < node > () = n_loop(M(yystack_[1].value.as < node > ()), M(yystack_[0].value.as < node > ())); }
#line 982 "parser.tab.cc"
    break;

  case 56: // iteration_stmt: "for" LPAREN expr SEMI_COLON expr SEMI_COLON expr RPAREN stmt
#line 227 "parser.yy"
                                                                            { yylhs.value.as < node > () = n_loop(M(yystack_[6].value.as < node > ()), M(yystack_[4].value.as < node > ()), M(yystack_[2].value.as < node > ()), M(yystack_[0].value.as < node > ())); }
#line 988 "parser.tab.cc"
    break;

  case 57: // iteration_stmt: "for" LPAREN typename identifier COLON identifier RPAREN stmt
#line 228 "parser.yy"
                                                                            { yylhs.value.as < node > () = n_loop(M(yystack_[0].value.as < node > ())); }
#line 994 "parser.tab.cc"
    break;

  case 58: // iteration_stmt: "BFS" LPAREN typename identifier COLON identifier RPAREN stmt
#line 229 "parser.yy"
                                                                            { yylhs.value.as < node > () = n_loop(M(yystack_[0].value.as < node > ())); }
#line 1000 "parser.tab.cc"
    break;

  case 59: // iteration_stmt: "DFS" LPAREN typename identifier COLON identifier RPAREN stmt
#line 230 "parser.yy"
                                                                            { yylhs.value.as < node > () = n_loop(M(yystack_[0].value.as < node > ())); }
#line 1006 "parser.tab.cc"
    break;

  case 60: // p_expr: LPAREN expr RPAREN
#line 232 "parser.yy"
                           { yylhs.value.as < node > () = M(yystack_[1].value.as < node > ()); }
#line 1012 "parser.tab.cc"
    break;

  case 61: // exprs: expr
#line 234 "parser.yy"
                                { yylhs.value.as < node > () = M(yystack_[0].value.as < node > ()); }
#line 1018 "parser.tab.cc"
    break;

  case 62: // exprs: exprs COMMA expr
#line 235 "parser.yy"
                                { yylhs.value.as < node > () = M(yystack_[2].value.as < node > ()); yylhs.value.as < node > ().params.push_back(M(yystack_[0].value.as < node > ())); }
#line 1024 "parser.tab.cc"
    break;

  case 63: // expr: "number"
#line 238 "parser.yy"
                                { yylhs.value.as < node > () = yystack_[0].value.as < int > ();    }
#line 1030 "parser.tab.cc"
    break;

  case 64: // expr: STRING_LITERAL
#line 239 "parser.yy"
                                { yylhs.value.as < node > () = M(yystack_[0].value.as < std::string > ()); }
#line 1036 "parser.tab.cc"
    break;

  case 65: // expr: identifier
#line 240 "parser.yy"
                                { yylhs.value.as < node > () = ctx.use(yystack_[0].value.as < std::string > ());   }
#line 1042 "parser.tab.cc"
    break;

  case 66: // expr: LPAREN exprs RPAREN
#line 241 "parser.yy"
                                      { yylhs.value.as < node > () = M(yystack_[1].value.as < node > ()); }
#line 1048 "parser.tab.cc"
    break;

  case 67: // expr: expr LSB exprs RSB
#line 242 "parser.yy"
                              { yylhs.value.as < node > () = n_deref(n_add(M(yystack_[3].value.as < node > ()), M(yystack_[1].value.as < node > ()))); }
#line 1054 "parser.tab.cc"
    break;

  case 68: // expr: expr LPAREN RPAREN
#line 243 "parser.yy"
                                      { yylhs.value.as < node > () = n_fcall(M(yystack_[2].value.as < node > ())); }
#line 1060 "parser.tab.cc"
    break;

  case 69: // expr: expr LPAREN exprs RPAREN
#line 244 "parser.yy"
      { yylhs.value.as < node > () = yystack_[3].value.as < node > (); }
#line 1066 "parser.tab.cc"
    break;

  case 70: // expr: expr ASSIGN expr
#line 245 "parser.yy"
                                   { yylhs.value.as < node > () = M(yystack_[2].value.as < node > ()) %= M(yystack_[0].value.as < node > ()); }
#line 1072 "parser.tab.cc"
    break;

  case 71: // expr: expr PLUS expr
#line 246 "parser.yy"
                                 { yylhs.value.as < node > () = n_add( M(yystack_[2].value.as < node > ()), M(yystack_[0].value.as < node > ())); }
#line 1078 "parser.tab.cc"
    break;

  case 72: // expr: expr MINUS expr
#line 247 "parser.yy"
                                   { yylhs.value.as < node > () = n_add( M(yystack_[2].value.as < node > ()), n_neg(M(yystack_[0].value.as < node > ()))); }
#line 1084 "parser.tab.cc"
    break;

  case 73: // expr: expr STAR expr
#line 248 "parser.yy"
                                 { yylhs.value.as < node > () = n_mul( M(yystack_[2].value.as < node > ()), M(yystack_[0].value.as < node > ())); }
#line 1090 "parser.tab.cc"
    break;

  case 74: // expr: expr SLASH expr
#line 249 "parser.yy"
                                   { yylhs.value.as < node > () = n_div( M(yystack_[2].value.as < node > ()), M(yystack_[0].value.as < node > ())); }
#line 1096 "parser.tab.cc"
    break;

  case 75: // expr: expr MOD expr
#line 250 "parser.yy"
                                { yylhs.value.as < node > () = n_mod( M(yystack_[2].value.as < node > ()), M(yystack_[0].value.as < node > ()));}
#line 1102 "parser.tab.cc"
    break;

  case 76: // expr: expr "+=" expr
#line 251 "parser.yy"
      { yylhs.value.as < node > () = yystack_[2].value.as < node > (); }
#line 1108 "parser.tab.cc"
    break;

  case 77: // expr: expr "-=" expr
#line 252 "parser.yy"
      { yylhs.value.as < node > () = yystack_[2].value.as < node > (); }
#line 1114 "parser.tab.cc"
    break;

  case 80: // expr: expr "++"
#line 255 "parser.yy"
      { yylhs.value.as < node > () = yystack_[1].value.as < node > (); }
#line 1120 "parser.tab.cc"
    break;

  case 81: // expr: expr "--"
#line 256 "parser.yy"
      { yylhs.value.as < node > () = yystack_[1].value.as < node > (); }
#line 1126 "parser.tab.cc"
    break;

  case 82: // expr: expr "||" expr
#line 257 "parser.yy"
                              { yylhs.value.as < node > () = n_cor( M(yystack_[2].value.as < node > ()), M(yystack_[0].value.as < node > ())); }
#line 1132 "parser.tab.cc"
    break;

  case 83: // expr: expr "&&" expr
#line 258 "parser.yy"
                               { yylhs.value.as < node > () = n_cand(M(yystack_[2].value.as < node > ()), M(yystack_[0].value.as < node > ())); }
#line 1138 "parser.tab.cc"
    break;

  case 84: // expr: expr "==" expr
#line 259 "parser.yy"
                              { yylhs.value.as < node > () = n_eq(  M(yystack_[2].value.as < node > ()), M(yystack_[0].value.as < node > ())); }
#line 1144 "parser.tab.cc"
    break;

  case 85: // expr: expr "!=" expr
#line 260 "parser.yy"
                            { yylhs.value.as < node > () = n_eq(n_eq(M(yystack_[2].value.as < node > ()), M(yystack_[0].value.as < node > ())), 0); }
#line 1150 "parser.tab.cc"
    break;

  case 86: // expr: AMPERSAND expr
#line 261 "parser.yy"
                                      { yylhs.value.as < node > () = n_addrof(M(yystack_[0].value.as < node > ())); }
#line 1156 "parser.tab.cc"
    break;

  case 87: // expr: STAR expr
#line 262 "parser.yy"
                                       { yylhs.value.as < node > () = n_deref(M(yystack_[0].value.as < node > ()));  }
#line 1162 "parser.tab.cc"
    break;

  case 88: // expr: MINUS expr
#line 263 "parser.yy"
                                        { yylhs.value.as < node > () = n_neg(M(yystack_[0].value.as < node > ()));    }
#line 1168 "parser.tab.cc"
    break;

  case 89: // expr: '!' expr
#line 264 "parser.yy"
                                      { yylhs.value.as < node > () = n_eq(M(yystack_[0].value.as < node > ()), 0); }
#line 1174 "parser.tab.cc"
    break;

  case 90: // expr: expr '?' expr COLON expr
#line 265 "parser.yy"
      { yylhs.value.as < node > () = yystack_[4].value.as < node > (); }
#line 1180 "parser.tab.cc"
    break;

  case 91: // identifier: "identifier"
#line 268 "parser.yy"
                                     { yylhs.value.as < std::string > () = M(yystack_[0].value.as < std::string > ()); }
#line 1186 "parser.tab.cc"
    break;


#line 1190 "parser.tab.cc"

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
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
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
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

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
    YY_STACK_PRINT ();
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
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
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
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // parser::context.
  parser::context::context (const parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -61;

  const signed char parser::yytable_ninf_ = -9;

  const short
  parser::yypact_[] =
  {
     -61,    14,   -61,   -61,   681,   -61,   -61,   -61,   -61,   -61,
     -61,   -61,   -61,   -60,   -51,   -40,   -39,   -36,   -32,   -61,
     -61,   -25,   -12,   -25,   -25,   -25,   -25,   -25,   -25,   -61,
       6,   -25,   -61,   -24,   -10,    -6,    -2,    -1,     9,     7,
      49,    88,   -61,   -61,   -61,   -61,   -61,   -61,    10,    10,
      10,    10,     7,    10,    10,   -61,    65,    10,   -61,   -61,
     635,   -61,   681,     7,   -61,    66,    66,    66,    20,   635,
     -61,    11,    66,    66,    15,    66,    10,    10,    10,    10,
      10,   340,    10,    10,    10,    10,   -61,   -61,    10,    10,
      10,    10,    10,    83,    78,   -25,   -61,   -61,    10,     7,
     -61,   -61,   635,   193,   193,    66,    66,   -61,    55,    66,
      16,   692,   648,   635,   635,   695,   695,   425,    73,   681,
     -61,   635,   -61,   -61,   -61,    10,   -61,   113,   -25,   635,
     -61,   -61,    79,    84,   345,    93,    93,    95,    96,    98,
     -25,   -61,   -61,   -61,   -61,    48,   185,   -61,   -61,    57,
     -61,   -61,   -61,   -61,   471,    10,   257,   257,   329,   681,
     681,   111,   -61,   -61,   -61,   -61,   484,    62,   -61,   -25,
     530,   -25,   -25,   -61,   257,    94,    10,    97,   100,   -61,
     -25,   576,   -25,   -25,   103,    10,   106,   108,   257,   589,
     257,   257,   -61,   257,   -61,   -61,   -61
  };

  const signed char
  parser::yydefact_[] =
  {
       2,     0,     5,     1,     3,    14,    15,    16,    18,    17,
      19,    20,    21,     0,     0,     0,     0,     0,     0,     4,
       6,     0,     0,     0,     0,     0,     0,     0,     0,    91,
      42,     0,     7,     0,     0,     0,     0,     0,     0,     0,
       0,    44,    23,    24,    22,    25,    26,    27,     0,     0,
       0,     0,     0,     0,     0,    64,    63,     0,    41,    46,
      45,    65,    11,     0,    63,    88,    87,    86,     0,    61,
      48,     0,    78,    79,     0,    89,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    80,    81,     0,     0,
       0,     0,     0,     0,    10,     0,    43,    66,     0,     0,
      47,    50,    70,    72,    71,    73,    74,    68,     0,    75,
       0,    83,    82,    76,    77,    85,    84,     0,     0,     0,
      13,    62,    49,    69,    67,     0,    51,     0,     0,    90,
      40,     9,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    52,    31,    30,    32,     0,     0,    29,    34,     0,
      12,    37,    36,    38,     0,     0,     0,     0,     0,     0,
       0,    42,    33,    28,    35,    39,     0,    53,    55,     0,
       0,     0,     0,    60,     0,     0,     0,     0,     0,    54,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    57,     0,    58,    59,    56
  };

  const signed char
  parser::yypgoto_[] =
  {
     -61,   -61,   -61,   -61,   -61,   -61,   -61,   -61,   -61,    -3,
     -59,   -61,   -61,   -61,   126,   -34,   -61,   -61,    17,   -61,
     -61,     1,   -43,   -22,   -21
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,     1,     2,     4,    19,    20,    40,    93,    94,   140,
     141,   142,   143,   144,   145,    58,    71,    59,   146,   147,
     148,   156,   149,    69,    61
  };

  const short
  parser::yytable_[] =
  {
      30,    21,    33,    34,    35,    36,    37,    38,    68,    39,
      41,    31,    48,    32,     3,    48,    49,    60,    70,    49,
      50,    -8,    51,    50,    23,    51,    65,    66,    67,    96,
      60,    72,    73,    24,    99,    75,    52,    97,   108,    98,
     110,    60,   100,    98,    25,    26,    53,    54,    27,    53,
      54,   124,    28,    29,   102,   103,   104,   105,   106,    95,
     109,    42,   111,   112,    62,   122,   113,   114,   115,   116,
     117,    31,   123,   162,   120,    43,   121,    60,    98,    44,
      98,    81,   164,    45,    46,    29,    55,    56,    29,    55,
      64,    63,    74,    57,    47,   101,    57,   167,   168,    83,
     118,   119,   126,   129,   151,    86,    87,   150,   155,   152,
     158,   159,   154,   160,    39,   179,   128,   174,    48,   161,
     188,   180,    49,   190,   182,   191,    50,   183,    51,   192,
      22,   194,   195,   166,   196,   127,   170,   157,   130,     0,
       0,     0,   126,     0,   131,     0,     0,     0,   175,     0,
     177,   178,    53,    54,   181,   169,   171,   172,     0,   184,
       0,   186,   187,   189,   132,   133,   134,   135,     0,   136,
     137,   138,   139,     5,     6,     7,     8,     9,    10,    11,
      12,     0,    13,    14,    15,    16,    17,    18,     0,     0,
      48,    29,    55,    64,    49,     0,     0,     0,    50,    57,
      51,     0,    79,     0,    80,     0,     0,     0,    81,     0,
     130,     0,    82,     0,   126,     0,   163,     0,     0,     0,
       0,     0,     0,     0,    53,    54,    83,     0,     0,     0,
       0,     0,    86,    87,     0,     0,   132,   133,   134,   135,
       0,   136,   137,   138,   139,     5,     6,     7,     8,     9,
      10,    11,    12,     0,    13,    14,    15,    16,    17,    18,
       0,     0,    48,    29,    55,    64,    49,     0,     0,     0,
      50,    57,    51,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   130,     0,     0,     0,   126,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    53,    54,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   132,   133,
     134,   135,     0,   136,   137,   138,   139,     5,     6,     7,
       8,     9,    10,    11,    12,     0,    13,    14,    15,    16,
      17,    18,     0,     0,    48,    29,    55,    64,    49,     0,
       0,     0,    50,    57,    51,    48,     0,     0,     0,    49,
      48,     0,     0,    50,    49,    51,     0,   107,    50,     0,
      51,     0,     0,     0,     0,     0,     0,     0,    53,    54,
     153,     0,     0,     0,     0,     0,     0,     0,     0,    53,
      54,     0,     0,     0,    53,    54,     0,     0,     0,     5,
       6,     7,     8,     9,    10,    11,    12,     0,    13,    14,
      15,    16,    17,    18,     0,     0,     0,    29,    55,    64,
       0,     0,     0,     0,     0,    57,     0,     0,    29,    55,
      64,     0,     0,    29,    55,    64,    57,     0,    76,     0,
      77,    57,    78,     0,    79,     0,    80,     0,     0,     0,
      81,     0,     0,     0,    82,     0,     0,     0,     0,     0,
       0,     0,   125,     0,     0,     0,     0,     0,    83,     0,
       0,     0,    84,    85,    86,    87,    88,    89,     0,     0,
       0,     0,    90,    91,    76,     0,    77,     0,    78,     0,
      79,     0,    80,     0,     0,     0,    81,    76,     0,    77,
      82,    78,     0,    79,     0,    80,   165,     0,     0,    81,
       0,   173,     0,    82,    83,     0,     0,    92,    84,    85,
      86,    87,    88,    89,     0,     0,     0,    83,    90,    91,
       0,    84,    85,    86,    87,    88,    89,     0,     0,     0,
       0,    90,    91,    76,     0,    77,     0,    78,     0,    79,
       0,    80,     0,     0,     0,    81,     0,     0,     0,    82,
       0,     0,     0,    92,     0,   176,     0,     0,     0,     0,
       0,     0,     0,    83,     0,     0,    92,    84,    85,    86,
      87,    88,    89,     0,     0,     0,     0,    90,    91,    76,
       0,    77,     0,    78,     0,    79,     0,    80,     0,     0,
       0,    81,    76,     0,    77,    82,    78,     0,    79,     0,
      80,   185,     0,     0,    81,     0,   193,     0,    82,    83,
       0,     0,    92,    84,    85,    86,    87,    88,    89,     0,
       0,     0,    83,    90,    91,     0,    84,    85,    86,    87,
      88,    89,     0,     0,     0,     0,    90,    91,    76,     0,
      77,     0,    78,     0,    79,     0,    80,     0,     0,     0,
      81,     0,     0,    77,    82,    78,     0,    79,    92,    80,
       0,     0,     0,    81,     0,     0,     0,    82,    83,     0,
       0,    92,    84,    85,    86,    87,    88,    89,     0,     0,
       0,    83,    90,    91,     0,    84,     0,    86,    87,     0,
       0,     0,     0,     0,     0,    90,    91,    77,     0,    78,
      77,    79,    78,    80,    79,     0,    80,    81,     0,     0,
      81,    82,     0,     0,    82,     0,     0,    92,     0,     0,
       0,     0,     0,     0,     0,    83,     0,     0,    83,     0,
       0,    86,    87,     0,    86,    87,     0,     0,     0,    90,
      91,     5,     6,     7,     8,     9,    10,    11,    12,     0,
      13,    14,    15,    16,    17,    18
  };

  const short
  parser::yycheck_[] =
  {
      21,     4,    23,    24,    25,    26,    27,    28,    51,     3,
      31,    23,     5,    25,     0,     5,     9,    39,    52,     9,
      13,    15,    15,    13,    84,    15,    48,    49,    50,    63,
      52,    53,    54,    84,    23,    57,    29,    17,    81,    23,
      83,    63,    31,    23,    84,    84,    39,    40,    84,    39,
      40,    35,    84,    78,    76,    77,    78,    79,    80,    62,
      82,    85,    84,    85,    15,    99,    88,    89,    90,    91,
      92,    23,    17,    25,    95,    85,    98,    99,    23,    85,
      23,    15,    25,    85,    85,    78,    79,    80,    78,    79,
      80,     3,    27,    86,    85,    80,    86,   156,   157,    33,
      17,    23,    29,   125,    25,    39,    40,   128,    15,    25,
      15,    15,   134,    15,     3,   174,   119,    55,     5,   140,
      17,    27,     9,    17,    27,    17,    13,    27,    15,   188,
       4,   190,   191,   155,   193,   118,   158,   136,    25,    -1,
      -1,    -1,    29,    -1,    31,    -1,    -1,    -1,   169,    -1,
     171,   172,    39,    40,   176,   158,   159,   160,    -1,   180,
      -1,   182,   183,   185,    51,    52,    53,    54,    -1,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    -1,    69,    70,    71,    72,    73,    74,    -1,    -1,
       5,    78,    79,    80,     9,    -1,    -1,    -1,    13,    86,
      15,    -1,     9,    -1,    11,    -1,    -1,    -1,    15,    -1,
      25,    -1,    19,    -1,    29,    -1,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    40,    33,    -1,    -1,    -1,
      -1,    -1,    39,    40,    -1,    -1,    51,    52,    53,    54,
      -1,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    -1,    69,    70,    71,    72,    73,    74,
      -1,    -1,     5,    78,    79,    80,     9,    -1,    -1,    -1,
      13,    86,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    -1,    -1,    29,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    40,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    52,
      53,    54,    -1,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    -1,    69,    70,    71,    72,
      73,    74,    -1,    -1,     5,    78,    79,    80,     9,    -1,
      -1,    -1,    13,    86,    15,     5,    -1,    -1,    -1,     9,
       5,    -1,    -1,    13,     9,    15,    -1,    17,    13,    -1,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    40,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      40,    -1,    -1,    -1,    39,    40,    -1,    -1,    -1,    60,
      61,    62,    63,    64,    65,    66,    67,    -1,    69,    70,
      71,    72,    73,    74,    -1,    -1,    -1,    78,    79,    80,
      -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,    78,    79,
      80,    -1,    -1,    78,    79,    80,    86,    -1,     3,    -1,
       5,    86,     7,    -1,     9,    -1,    11,    -1,    -1,    -1,
      15,    -1,    -1,    -1,    19,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,    33,    -1,
      -1,    -1,    37,    38,    39,    40,    41,    42,    -1,    -1,
      -1,    -1,    47,    48,     3,    -1,     5,    -1,     7,    -1,
       9,    -1,    11,    -1,    -1,    -1,    15,     3,    -1,     5,
      19,     7,    -1,     9,    -1,    11,    25,    -1,    -1,    15,
      -1,    17,    -1,    19,    33,    -1,    -1,    82,    37,    38,
      39,    40,    41,    42,    -1,    -1,    -1,    33,    47,    48,
      -1,    37,    38,    39,    40,    41,    42,    -1,    -1,    -1,
      -1,    47,    48,     3,    -1,     5,    -1,     7,    -1,     9,
      -1,    11,    -1,    -1,    -1,    15,    -1,    -1,    -1,    19,
      -1,    -1,    -1,    82,    -1,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    33,    -1,    -1,    82,    37,    38,    39,
      40,    41,    42,    -1,    -1,    -1,    -1,    47,    48,     3,
      -1,     5,    -1,     7,    -1,     9,    -1,    11,    -1,    -1,
      -1,    15,     3,    -1,     5,    19,     7,    -1,     9,    -1,
      11,    25,    -1,    -1,    15,    -1,    17,    -1,    19,    33,
      -1,    -1,    82,    37,    38,    39,    40,    41,    42,    -1,
      -1,    -1,    33,    47,    48,    -1,    37,    38,    39,    40,
      41,    42,    -1,    -1,    -1,    -1,    47,    48,     3,    -1,
       5,    -1,     7,    -1,     9,    -1,    11,    -1,    -1,    -1,
      15,    -1,    -1,     5,    19,     7,    -1,     9,    82,    11,
      -1,    -1,    -1,    15,    -1,    -1,    -1,    19,    33,    -1,
      -1,    82,    37,    38,    39,    40,    41,    42,    -1,    -1,
      -1,    33,    47,    48,    -1,    37,    -1,    39,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    48,     5,    -1,     7,
       5,     9,     7,    11,     9,    -1,    11,    15,    -1,    -1,
      15,    19,    -1,    -1,    19,    -1,    -1,    82,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    -1,    -1,    33,    -1,
      -1,    39,    40,    -1,    39,    40,    -1,    -1,    -1,    47,
      48,    60,    61,    62,    63,    64,    65,    66,    67,    -1,
      69,    70,    71,    72,    73,    74
  };

  const signed char
  parser::yystos_[] =
  {
       0,    88,    89,     0,    90,    60,    61,    62,    63,    64,
      65,    66,    67,    69,    70,    71,    72,    73,    74,    91,
      92,    96,   101,    84,    84,    84,    84,    84,    84,    78,
     111,    23,    25,   111,   111,   111,   111,   111,   111,     3,
      93,   111,    85,    85,    85,    85,    85,    85,     5,     9,
      13,    15,    29,    39,    40,    79,    80,    86,   102,   104,
     110,   111,    15,     3,    80,   110,   110,   110,   109,   110,
     102,   103,   110,   110,    27,   110,     3,     5,     7,     9,
      11,    15,    19,    33,    37,    38,    39,    40,    41,    42,
      47,    48,    82,    94,    95,    96,   102,    17,    23,    23,
      31,    80,   110,   110,   110,   110,   110,    17,   109,   110,
     109,   110,   110,   110,   110,   110,   110,   110,    17,    23,
     111,   110,   102,    17,    35,    27,    29,   105,    96,   110,
      25,    31,    51,    52,    53,    54,    56,    57,    58,    59,
      96,    97,    98,    99,   100,   101,   105,   106,   107,   109,
     111,    25,    25,    25,   110,    15,   108,   108,    15,    15,
      15,   111,    25,    31,    25,    25,   110,    97,    97,    96,
     110,    96,    96,    17,    55,   111,    25,   111,   111,    97,
      27,   110,    27,    27,   111,    25,   111,   111,    17,   110,
      17,    17,    97,    17,    97,    97,    97
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    87,    89,    88,    90,    90,    91,    91,    93,    92,
      94,    94,    95,    95,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    97,    97,
      97,    97,    97,    97,    97,    98,    99,    99,    99,    99,
     100,   101,   101,   101,   101,   102,   102,   102,   103,   103,
     104,   105,   105,   106,   106,   107,   107,   107,   107,   107,
     108,   109,   109,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   111
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     0,     2,     2,     0,     1,     2,     0,     8,
       1,     0,     4,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     4,     4,     4,     4,     4,     4,     2,     1,
       1,     1,     1,     2,     1,     2,     2,     2,     2,     3,
       1,     4,     2,     5,     3,     1,     1,     3,     1,     3,
       3,     1,     2,     3,     5,     3,     9,     8,     8,     8,
       3,     1,     3,     1,     1,     1,     3,     4,     3,     4,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       2,     2,     3,     3,     3,     3,     2,     2,     2,     2,
       5,     1
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "ASSIGN", "'='",
  "MINUS", "'-'", "PLUS", "'+'", "STAR", "'*'", "SLASH", "'/'",
  "AMPERSAND", "'&'", "LPAREN", "'('", "RPAREN", "')'", "MOD", "'%'",
  "B_OR", "'|'", "COMMA", "','", "SEMI_COLON", "';'", "COLON", "':'",
  "LBRACE", "'{'", "RBRACE", "'}'", "LSB", "'['", "RSB", "']'", "\"&&\"",
  "\"||\"", "\"++\"", "\"--\"", "\"+=\"", "\"-=\"", "\"*=\"", "\"/=\"",
  "\"<\"", "\">\"", "\"!=\"", "\"==\"", "\">=\"", "\"<=\"", "\"break\"",
  "\"continue\"", "\"return\"", "\"if\"", "\"else\"", "\"while\"",
  "\"for\"", "\"BFS\"", "\"DFS\"", "\"void\"", "\"int\"", "\"bool\"",
  "\"float\"", "\"char\"", "\"string\"", "\"graph\"", "\"dgraph\"",
  "\"node\"", "\"node_set\"", "\"node_seq\"", "\"node_prop\"",
  "\"edge_prop\"", "\"edge_set\"", "\"edge_seq\"", "\"nodes\"",
  "\"levels\"", "\"neighbours\"", "\"identifier\"", "STRING_LITERAL",
  "\"number\"", "\"double_const\"", "'?'", "LOWER_THAN_ELSE", "'<'", "'>'",
  "'!'", "$accept", "program", "$@1", "declarations", "declaration",
  "function", "$@2", "paramdecls", "paramdecl", "typename", "stmt",
  "expression_stmt", "jump_stmt", "empty_stmt", "vardec_stmt",
  "initializer", "initializer_list", "edge", "compound_stmt",
  "selection_stmt", "iteration_stmt", "p_expr", "exprs", "expr",
  "identifier", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   147,   147,   147,   148,   149,   151,   152,   155,   155,
     157,   158,   160,   161,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   179,   180,
     181,   182,   183,   184,   185,   187,   189,   190,   191,   192,
     194,   196,   197,   198,   199,   210,   211,   212,   214,   215,
     217,   220,   221,   223,   224,   226,   227,   228,   229,   230,
     232,   234,   235,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   268
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
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


} // yy
#line 1905 "parser.tab.cc"

#line 270 "parser.yy"


// Register errors to the driver:
void yy::parser::error (const location_type& l,
                          const std::string& m)
{
    driver.error(l, m);
}
