
#ifndef TYPES_H
#define TYPES_H

struct node;
typedef std::vector<struct node> node_vec; 
struct identifier;
struct function;
struct common_list;


#define ENUM_IDENTIFIERS(f) \
  f(function) \
  f(parameter) \
  f(variable) 

#define ENUM_NODES(f) \
  f(identifier) f(string) f(number) f(double_const) \
  f(add) f(neg) f(eq) \
  f(cor) f(cand) f(cond) f(loop) \
  f(addrof) f(deref) \
  f(fcall) \
  f(copy) \
  f(comma) f(init_list) f(vardec)\
  f(mul) f(div) f(mod) \
  f(ret) f(br) f(cont) f(nop) \
  f(edge)

#define ENUM_TYPE_NAMES(f) \
  f(INT) f(BOOL) f(FLOAT) f(CHAR) f(VOID) f(STRING)\
   f(GRAPH) f(DGRAPH) f(FUNC) \
   f(NODE_SET) f(NODE_PROP) f(NODE_SEQ) \
   f(EDGE_SET) f(EDGE_PROP) f(EDGE_SEQ) 

#define f(n) n,
enum class type_name { ENUM_TYPE_NAMES(f) }; \
enum class id_type { ENUM_IDENTIFIERS(f) }; \
enum class node_type { ENUM_NODES(f) };
#undef f


struct identifier{
  id_type type;
  type_name v_type;
  std::size_t index = 0;
  std::string name;
  identifier() { }
  identifier(id_type _type, type_name _v_type, std::size_t _index, std::string _name) : type(_type), v_type(_v_type), index(_index), name(_name) { }
};

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

struct common_list{
  node n;
  function f;
  bool isFunc = true;
  common_list(node&& _n) : n(_n) {}
  common_list(function&& _f) : f(_f) {}
};


#define f(p) \
inline bool is_##p(const identifier& i) { return i.type == id_type::p; }
ENUM_IDENTIFIERS(f)
#undef f

#define f(p) \
inline bool is_##p(const node& n) {  return n.type == node_type::p; } \
template<typename ...T> \
inline node n_##p(T&& ...args) { return node(node_type::p, std::forward<T>(args)...);} 
ENUM_NODES(f)
#undef f
#endif