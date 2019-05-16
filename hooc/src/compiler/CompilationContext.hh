//
// Created by benoy on 12/21/2018.
//

#ifndef PARSECONTEXT_HH
#define PARSECONTEXT_HH

#include "antlr4-runtime.h"
#include "HooParser.h"
#include "HooLexer.h"
#include "compiler/CompilationUnit.hh"

#include <string>
#include <memory>

namespace hooc {
    namespace compiler {
        class CompilationContext {
        private:
            antlr4::ANTLRInputStream *stream = nullptr;
            HooLexer *lexer = nullptr;
            antlr4::CommonTokenStream *tokens = nullptr;
            HooParser *parser = nullptr;
            HooParser::UnitContext *unitContext = nullptr;
            CompilationUnit *unit = nullptr;

        public:
            CompilationContext(std::string source_code);

        public:
            ~CompilationContext();

        public:
            void AddErrorListener(antlr4::ANTLRErrorListener *errorListener);

            HooParser::UnitContext *GetUnitContext();
        };
    }
}

#endif //PROJECT_PARSECONTEXT_HH
