#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum TokenType {KEYWORD, IDENTIFIER, VALUE, SEGMENT, OPERATOR, ERROR, OTHERS};

typedef struct Token {
	TokenType type;
	int line;
	std::string value;

	Token();

	Token(TokenType type, int line, std::string value);

	Token(const Token& token);

	virtual ~Token();

	std::string toJSON();
	std::string toString();

} Token_t;

#endif