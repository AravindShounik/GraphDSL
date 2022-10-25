
#ifndef TYPES_H
#define TYPES_H

enum class id_type {
  function,
  parameter,
  variable
};

enum class type_name {
  INT,
  BOOL,
  FLOAT,
  CHAR,
  VOID,
  STRING,
  GRAPH,
  DGRAPH,
  NODE_SET,
  NODE_PROP,
  NODE_SEQ,
  EDGE_SET,
  EDGE_PROP,
  EDGE_SEQ,
  FUNC // for function type_name
};
struct identifier {
  id_type type;
  type_name v_type;
  std::size_t index = 0;
  std::string name;
  identifier() { }
  identifier(id_type _type, type_name _v_type, std::size_t _index, std::string _name) : type(_type), v_type(_v_type), index(_index), name(_name) { }
};

#define ENUM_NODES(f) \
  f(identifier) f(string) f(number) f(double_const) \
  f(add) f(neg) f(eq) \
  f(cor) f(cand) f(loop) \
  f(addrof) f(deref) \
  f(fcall) \
  f(copy) \
  f(comma) f(init_list) \
  f(mul) f(div) f(mod) \
  f(ret) f(br) f(cont) f(nop) \
  f(edge)


#define f(n) n,
enum class node_type { ENUM_NODES(f) };
#undef f

struct node;
typedef std::vector<struct node> node_vec; 
struct node
{
  node_type type;
  identifier ident = {};
  std::string strvalue{};
  int numvalue{};
  double doublevalue{};
  node_vec params;
  // define constructor and required functions
  template<typename... T>
  node(node_type t, T&&... args) : type(t), params{ std::forward<T>(args)... } {}

  node()  : type(node_type::nop)  {}
  node(const identifier& i) : type(node_type::identifier), ident(i)  {}
  node(identifier&& i)  : type(node_type::string), ident(std::move(i))  {}
  node(int v) : type(node_type::number), numvalue(v) {}
  node(double v) : type(node_type::double_const), doublevalue(v) {}
  node(std::string&& v) : type(node_type::string), strvalue(std::move(v)) {}

  node operator%=(node&& b) && {return node(node_type::copy, std::move(b), std::move(*this));}

};

#define f(p) \
template<typename ...T> \
inline node n_##p(T&& ...args) { return node(node_type::p, std::forward<T>(args)...);} 
ENUM_NODES(f)
#undef f

struct function 
{
  std::string name;
  type_name ret_type;
  unsigned num_params = 0;
  unsigned num_vars = 0;
  std::vector<type_name> param_types;
  node code;
  function(){}
};
#endif