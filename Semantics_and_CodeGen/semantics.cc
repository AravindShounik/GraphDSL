#include "semantics.hh"

std::vector<std::string> doSemantics(std::vector<common_list> &ast)
{
  std::vector<std::string> error_list;
  for (auto &cn : ast)
  {
    if (cn.isFunc) //
    {
      auto &f = cn.f;
      func_map[f.name] = &f;
      type_name ret = f.ret_type;
      bool hasRetStmt = false;
      for (auto &stmt : f.code.params)
      {
        try
        {
          // if it returns, do semantics on it
          if (stmt.type == node_type::ret)
          {
            hasRetStmt = true;
            // check return type of function
            if (ret == type_name::VOID && stmt.params.size() > 0)
            {
              throw Exception("Unexpected return statement.");
            }
            else if (ret != type_name::VOID && stmt.params.size() == 0)
            {
              throw Exception("Return statement doesn't return anything.");
            }
            else if (ret != type_name::VOID && stmt.params.size() > 0)
            {
              if (ret != doSemantics(stmt.params[0]))
              {
                throw Exception("Return types don't match.");
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
      if (ret != type_name::VOID && !hasRetStmt)
      {
        try
        {
          throw Exception("Expected return statement.");
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
      try
      {
        doSemantics(cn.n);
      }
      catch (Exception &e)
      {
        std::cerr << e.loc.begin.line << ":" << e.loc.begin.column << " error: " << e.msg << std::endl;
      }
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
    return type_name::INT;

  case node_type::double_const:
    return type_name::FLOAT;

  case node_type::string:
    return type_name::STRING;

  case node_type::identifier:
    return n.ident.v_type;

  case node_type::add:
    if ((ret1 = doSemantics(n.params[0])) != (ret2 = doSemantics(n.params[1])))
    {
      throw Exception(n.loc, "+ of different types");
    }
    break;

  case node_type::neg:
    return doSemantics(n.params[0]);

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
      throw Exception(n.loc, "% of non-integers");
    }
    ret1 = type_name::INT;
    break;

  case node_type::eq:
    if ((ret1 = doSemantics(n.params[0])) != (ret2 = doSemantics(n.params[1])))
    {
      throw Exception(n.loc, "== of different types");
    }
    ret1 = type_name::BOOL;
    break;

  case node_type::cor:
    if ((ret1 = doSemantics(n.params[0])) != (ret2 = doSemantics(n.params[1])))
    {
      throw Exception(n.loc, "|| different types");
    }
    ret1 = type_name::BOOL;
    break;

  case node_type::cand:
    if ((ret1 = doSemantics(n.params[0])) != (ret2 = doSemantics(n.params[1])))
    {
      throw Exception(n.loc, "&& different types");
    }
    ret1 = type_name::BOOL;
    break;

  case node_type::ret:
    if (n.params.size() > 0)
      ret1 = doSemantics(n.params[0]);
    break;

  case node_type::copy:
  {
    if ((ret1 = doSemantics(n.params[0])) != (ret2 = doSemantics(n.params[1])))
    {
      throw Exception(n.loc, "= different types");
    }
    return type_name::VOID;
  }

  case node_type::vardec:
    for (auto &inits : n.params)
    {
      ret1 = doSemantics(inits);
    }
    return type_name::VOID;

  case node_type::br:
    return type_name::VOID;

  case node_type::cont:
    return type_name::VOID;

  case node_type::fcall:
  {
    if (n.params[0].ident.type != id_type::function)
    {
      throw Exception(n.loc, "Expected a function name.");
    }
    auto f = func_map[n.params[0].ident.name];

    if (n.params[1].params.size() > f->num_params)
    {
      throw Exception(n.loc, "Expected fewer arguments.");
    }
    else if (n.params[1].params.size() < f->num_params)
    {
      throw Exception(n.loc, "Too few arguments.");
    }

    unsigned i = 0;
    for (i = 0; i < f->num_params; i++)
    {
      if (doSemantics(n.params[1].params[i]) != f->param_types[i])
      {
        throw Exception(n.loc, "Expected argument of type " + toString(f->param_types[i]));
      }
    }
    return f->ret_type;
  }

  case node_type::init_list:
  {
    auto prev = node_type::nop;
    unsigned size = 0;
    for (auto &p : n.params)
    {
      doSemantics(p);
      if (prev == node_type::nop)
      {
        prev = p.type;
        size = p.params.size();
      }
      else
      {
        if (p.type != prev)
        {
          throw Exception(n.loc, "Expected init list of same types.");
        }
        if (p.params.size() != size)
        {
          throw Exception(n.loc, "Expected init lists of same sizes.");
        }
      }
    }
    /*
    pending:
    recursive type check also for children
    */
    return type_name::INT;
  }

  default:
    break;
  }
  return ret1;
}
/* not required for conditional stmts, loops */
