#include "semantics.hh"

void doSemantics(const std::vector<common_list>& ast)
{
  for(auto& n : ast)
  {
    if(n.isFunc) // 
    {
      // 1. if it returns, check for return statement
      auto& f = n.f;

      doSemantics(f.code);

    }
    else
    {
      // declaration type should match rhs
    }
  }
}

void doSemantics(const node& n)
{
  switch (n.type)
  {
  case node_type::add:
    
    break;
  case node_type::string:
  
  default:
    break;
  }
}