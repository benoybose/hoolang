//
// Created by benoy on 12/21/2018.
//

#ifndef PARSECONTEXT_HH
#define PARSECONTEXT_HH

#include "antlr4-runtime.h"
#include "HooParser.h"
#include "HooLexer.h"
#include "CompilationUnit.hh"

#include <string>
#include <memory>

namespace hooc {

    typedef std::shared_ptr<HooParser::UnitContext> UnitContext;
    class ParseContext {
    private:
        antlr4::ANTLRInputStream *stream = nullptr;
        HooLexer *lexer = nullptr;
        antlr4::CommonTokenStream *tokens = nullptr;
        HooParser *parser = nullptr;
        UnitContext unitContext;
        CompilationUnit *unit = nullptr;

    public:
        ParseContext(std::string source_code);

    public:
        ~ParseContext();

    public:
        void AddErrorListener(antlr4::ANTLRErrorListener *errorListener);

        UnitContext GetUnitContext();
    };
}

#endif //PROJECT_PARSECONTEXT_HH
