#include "semantics.hh"

std::vector<std::string> doSemantics(const std::vector<common_list> &ast)
{
  std::vector<std::string> error_list;
  for (auto &n : ast)
  {
    if (n.isFunc) //
    {
      auto &f = n.f;

      type_name ret = f.ret_type;
      for (auto &stmt : f.code.params)
      {
        try
        {
          // if it returns, do semantics on it
          if (stmt.type == node_type::ret)
          {
            // check return type of function
            if (ret == type_name::VOID && stmt.params.size() > 0)
            {
              // error
            }
            else if (ret != type_name::VOID && stmt.params.size() == 0)
            {
              // error
            }
            else if (ret != type_name::VOID && stmt.params.size() > 0)
            {
              if (ret != doSemantics(stmt.params[0]))
              {
                // error
              }
            }
          }
          else
          {
            doSemantics(stmt);
          }
        }
        catch (Exception& e)
        {
          std::cerr << e.loc.begin.line <<":" << e.loc.begin.column << " error: " << e.msg << std::endl;
        }
      }
    }
    else
    {
      // declaration type should match rhs
    }
  }
  return error_list;
}

type_name doSemantics(const node &n)
{
  switch (n.type)
  {
  case node_type::number:
    return type_name::INT;

  case node_type::double_const:
    return type_name::FLOAT;

  case node_type::string:
    return type_name::STRING;

  case node_type::identifier:
    return n.ident.v_type;

  case node_type::add:
    if (doSemantics(n.params[0]) != doSemantics(n.params[1]))
    {
      throw Exception(n.loc, "Adding different types");
    }
    break;

  default:
    break;
  }
  return type_name::INT;
}