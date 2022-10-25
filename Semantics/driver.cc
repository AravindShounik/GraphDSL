#include "driver.hh"
#include "parser.hh"

Driver::Driver ()
    : trace_scanning (false), trace_parsing (false)
{
  
}

Driver::~Driver ()
{
}


int Driver::parse (const std::string &f)
{
    file = f;
    scan_begin ();
    yy::parser parser (*this);
    parser.set_debug_level (trace_parsing);
    int res = parser.parse ();
    scan_end ();
    return res;
}

void Driver::error (const yy::location& l, const std::string& m)
{
    std::cerr << l.begin.line <<":" << l.begin.column << " error: " << m << std::endl;
}

void Driver::error (const std::string& m)
{
    std::cerr << m << std::endl;
}

// CHANGE: functions moved from the bottom of `calc++-scanner.ll`

void Driver::scan_begin()
{
    lexer.set_debug( trace_scanning );

    // Try to open the file:
    instream.open(file);

    if( instream.good() ) {
        lexer.switch_streams(&instream, 0);
    } else if( file == "-" ) {
        lexer.switch_streams(&std::cin, 0);
    } else {
        error ("Cannot open file '" + file + "'.");
        exit (EXIT_FAILURE);
    }
}

void Driver::scan_end ()
{
    instream.close();
}
