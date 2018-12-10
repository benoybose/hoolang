/*
 * Copyright 2018 Benoy Bose
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <Lexer.hh>

#include "Lexer.hh"

namespace hooc {
    Lexer::Lexer(std::istringstream &stream):
        _text(""),
        _stream(stream),
        _position(0),
        _line_number(0),
        _column_number(0) {
    }

    bool Lexer::Tokenize(LexerError &error, Token &token) {
        bool found_match = false;
        char character = 0;

        while(!this->_stream.eof()) {
            if(!this->_text.empty()) {
                const std::string& text = this->_text;
                TokenDescriptor matched_token_descriptor;

                std::for_each(this->_descriptors.begin(), this->_descriptors.end(), [text,&matched_token_descriptor, &found_match](const TokenDescriptor& desc) {
                    if(boost::regex_match(text.begin(), text.end(), desc.GetPattern())) {
                        if((-1 == matched_token_descriptor.GetTokenId()) ||
                            (matched_token_descriptor.GetTokenId() > desc.GetTokenId())) {
                            found_match = true;
                            matched_token_descriptor = desc;
                        }
                    }
                });
            }

            char character = 0;
            this->_stream.get(character);
            if(0 != character) {
                // todo: handle null character
            } else {
                this->_text += character;
            }
            
        }
        return false;
    }

    void Lexer::Add(int token_id, std::string pattern) {
        TokenDescriptor descriptor(token_id, boost::regex(pattern));
        this->_descriptors.push_back(descriptor);
    }

    const std::list<hooc::TokenDescriptor> &Lexer::GetDescriptors() const {
        return this->_descriptors;
    }
}


