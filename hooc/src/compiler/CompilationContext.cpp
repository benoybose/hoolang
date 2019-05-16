//
// Created by benoy on 12/21/2018.
//

#include "CompilationContext.hh"

#include "CompilationContext.hh"

namespace hooc {
    namespace compiler {
        CompilationContext::CompilationContext(std::string source_code) {
            stream = new antlr4::ANTLRInputStream(source_code);
            lexer = new HooLexer(stream);
            tokens = new antlr4::CommonTokenStream(lexer);
            parser = new HooParser(tokens);
            auto errorHandler = std::shared_ptr<antlr4::ANTLRErrorStrategy>(new antlr4::DefaultErrorStrategy());
            parser->setErrorHandler(errorHandler);
        }

        CompilationContext::~CompilationContext() {
            if (nullptr != this->parser) {
                delete this->parser;
            }

            if (nullptr != this->tokens) {
                delete this->tokens;
            }

            if (nullptr != this->lexer) {
                delete this->lexer;
            }

            if (nullptr != this->stream) {
                delete this->stream;
            }
        }

        void CompilationContext::AddErrorListener(antlr4::ANTLRErrorListener *errorListener) {
            this->parser->addErrorListener(errorListener);
        }

        HooParser::UnitContext* CompilationContext::GetUnitContext() {
            this->parser->unit();
        }
    }
}
