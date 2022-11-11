
#ifndef TYPES_H
#define TYPES_H
#pragma once
#include <string>
#include "location.hh"

extern yy::location loc;
struct node;
typedef std::vector<struct node> node_vec;
struct identifier;
struct function;
struct common_list;

yy::location getLoc();

/**
 * @brief We are defining an enum for identifiers
 *
 */
#define ENUM_id_type(f) \
  f(function)           \
      f(parameter)      \
          f(variable)

/**
 * @brief We are defining an enum for nodes
 *
 */
#define ENUM_node_type(f)                                 \
  f(identifier) f(string) f(number) f(double_const)       \
      f(add) f(neg) f(mul) f(div) f(mod) f(eq)            \
          f(cor) f(cand) f(cond) f(loop)                  \
              f(addrof) f(deref)                          \
                  f(fcall)                                \
                      f(copy)                             \
                          f(comma) f(init_list) f(vardec) \
                              f(ret) f(br) f(cont) f(nop) \
                                  f(edge)

/**
 * @brief We are defining an enum for type names
 *
 */
#define ENUM_type_name(f)                           \
  f(INT) f(BOOL) f(FLOAT) f(CHAR) f(VOID) f(STRING) \
      f(GRAPH) f(DGRAPH) f(FUNC)                    \
          f(NODE_SET) f(NODE_PROP) f(NODE_SEQ)      \
              f(EDGE_SET) f(EDGE_PROP) f(EDGE_SEQ)

/**
 * @brief Here, we are defining enums for type names, identifier types, node types according to which token is returned
 *
 */
#define f(n) n,
enum class type_name
{
  ENUM_type_name(f)
};
enum class id_type
{
  ENUM_id_type(f)
};
enum class node_type
{
  ENUM_node_type(f)
};
#undef f

/**
 * @brief This is a struct for identifiers, Each Identifier is stored here, and the enum value which we get using enum class id_type and  is
 *
 */
struct identifier
{
  id_type type;
  type_name v_type;
  std::size_t index = 0;
  std::string name;
  identifier() {}
  identifier(id_type _type, type_name _v_type, std::size_t _index, std::string _name) : type(_type), v_type(_v_type), index(_index), name(_name) {}
};

/**
 * @brief This is a node in the AST
 *
 */
struct node
{
  yy::location loc;
  node_type type;
  identifier ident = {};
  std::string strvalue{};
  int numvalue{};
  double doublevalue{};
  node_vec params;
  // define constructor and required functions
  template <typename... T>
  node(node_type t, T &&...args) : loc(getLoc()), type(t), params{std::forward<T>(args)...} {}

  node() : type(node_type::nop) {}
  node(const identifier &i) : type(node_type::identifier), ident(i) {}
  node(identifier &&i) : type(node_type::string), ident(std::move(i)) {}
  node(int v) : type(node_type::number), numvalue(v) {}
  node(double v) : type(node_type::double_const), doublevalue(v) {}
  node(std::string &&v) : type(node_type::string), strvalue(std::move(v)) {}

  node operator%=(node &&b) && { return node(node_type::copy, std::move(b), std::move(*this)); }
};

/**
 * @brief This is the function struct
 *
 */
struct function
{
  std::string name;
  type_name ret_type;
  unsigned num_params = 0;
  unsigned num_vars = 0;
  std::vector<type_name> param_types;
  std::vector<std::string> param_names;
  node code;
  function() {}
};

/**
 * @brief This is the list of functions and variables
 *
 */
struct common_list
{
  node n;
  function f;
  bool isFunc = true;
  common_list(node &&_n) : n(_n) {}
  common_list(function &&_f) : f(_f) {}
};

/**
 * @brief This fixes the identifier type when it encounters an identifier
 *
 */
#define f(p) \
  inline bool is_##p(const identifier &i) { return i.type == id_type::p; }
ENUM_id_type(f)
#undef f

/**
 * @brief This calls the required functions when we get a token
 *
 */
#define f(p)                                                           \
  inline bool is_##p(const node &n) { return n.type == node_type::p; } \
  template <typename... T>                                             \
  inline node n_##p(T &&...args) { return node(node_type::p, std::forward<T>(args)...); }
    ENUM_node_type(f)
#undef f

/* Printing ENUMS */

#define h(WHICH_ENUM)                                               \
  inline std::string toString(WHICH_ENUM inp)                       \
  {                                                                 \
    switch (inp)                                                    \
    {                                                               \
      ENUM_##WHICH_ENUM(g)                                          \
    }                                                               \
    return "";                                                      \
  }                                                                 \
  inline std::ostream &operator<<(std::ostream &os, WHICH_ENUM inp) \
  {                                                                 \
    os << toString(inp);                                            \
    return os;                                                      \
  }

#define g(n)       \
  case id_type::n: \
    return #n;
        h(id_type)
#undef g

#define g(n)         \
  case type_name::n: \
    return #n;
            h(type_name)
#undef g

#define g(n)         \
  case node_type::n: \
    return #n;
                h(node_type)
#undef g

    // python like print
    inline void print()
{
  std::cout << '\n';
}

template <typename T, typename... TAIL>
inline void print(const T &t, TAIL... tail)
{
  std::cout << t << ' ';
  print(tail...);
}
#undef h

#endif