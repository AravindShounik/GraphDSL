#include "semantics.hh"

std::vector<std::string> doSemantics(const std::vector<common_list> &ast)
{
  std::vector<std::string> error_list;
  for (auto &cn : ast)
  {
    if (cn.isFunc) //
    {
      auto &f = cn.f;

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
        catch (Exception &e)
        {
          std::cerr << e.loc.begin.line << ":" << e.loc.begin.column << " error: " << e.msg << std::endl;
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
  type_name ret1, ret2;
  ret1 = ret2 = type_name::VOID;
  switch (n.type)
  {
  case node_type::number:
    ret1 = type_name::INT;
    break;

  case node_type::double_const:
    ret1 = type_name::FLOAT;
    break;

  case node_type::string:
    ret1 = type_name::STRING;
    break;

  case node_type::identifier:
    ret1 = n.ident.v_type;
    break;

  case node_type::add:
    if ((ret1 = doSemantics(n.params[0])) != (ret2 = doSemantics(n.params[1])))
    {
      throw Exception(n.loc, "+ of different types");
    }
    break;

  case node_type::mul:
    if ((ret1 = doSemantics(n.params[0])) != (ret2 = doSemantics(n.params[1])))
    {
      throw Exception(n.loc, "* of different types");
    }
    break;

  case node_type::div:
    if ((ret1 = doSemantics(n.params[0])) != (ret2 = doSemantics(n.params[1])))
    {
      throw Exception(n.loc, "/ of different types");
    }
    break;

  case node_type::mod:
    if ((doSemantics(n.params[0]) != type_name::INT) || (doSemantics(n.params[1]) != type_name::INT))
    {
      throw Exception(n.loc, "\% of non-integers");
    }
    ret1 = type_name::INT;
    break;

  case node_type::neg:
    ret1 = doSemantics(n.params[0]);
    break;

  case node_type::eq:
    if ((ret1 = doSemantics(n.params[0])) != (ret2 = doSemantics(n.params[1])))
    {
      throw Exception(n.loc, "== of different types");
    }
    break;

  case node_type::cor:
    if ((ret1 = doSemantics(n.params[0])) != (ret2 = doSemantics(n.params[1])))
    {
      throw Exception(n.loc, "|| different types");
    }
    break;

  case node_type::cand:
    if ((ret1 = doSemantics(n.params[0])) != (ret2 = doSemantics(n.params[1])))
    {
      throw Exception(n.loc, "&& different types");
    }
    break;

  case node_type::ret:
    if(n.params.size() > 0)
      ret1 = doSemantics(n.params[0]);
    break;
  
  default:
    break;
  }
  return ret1;
}