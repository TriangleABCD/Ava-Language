
#include "Token.h"


Token::Token() {
}

Token::Token(TokenType type, int line, std::string value) {
	this->type = type;
	this->line = line;
	this->value = value;
}

Token::Token(const Token& token) {
	this->type = token.type;
	this->line = token.line;
	this->value = token.value;
}

Token::~Token() {
}

std::string Token::toJSON() {
	std::string res = "{\"line\": ";
	res += std::to_string(this->line);
	res += ", \"type\": \"";
	switch(this->type) {
		case KEYWORD:
			res += "KEYWORD";
			break;
		case IDENTIFIER:
			res += "IDENTIFIER";
			break;
		case VALUE:
			res += "VALUE";
			break;
		case SEGMENT:
			res += "SEGMENT";
			break;
		case OPERATOR:
			res += "OPERATOR";
			break;
		case ERROR:
			res += "ERROR";
			break;
		case OTHERS:
			res += "OTHERS";
			break;
	}
	res += "\", \"value\": \"";
	res += this->value;
	res += "\"}";
	return res;
}


std::string Token::toString() {
	std::string res = "";
	res += std::to_string(this->line);
	res += " ";
	switch(this->type) {
		case KEYWORD:
			res += "KEYWORD";
			break;
		case IDENTIFIER:
			res += "IDENTIFIER";
			break;
		case VALUE:
			res += "VALUE";
			break;
		case SEGMENT:
			res += "SEGMENT";
			break;
		case OPERATOR:
			res += "OPERATOR";
			break;
		case ERROR:
			res += "ERROR";
			break;
		case OTHERS:
			res += "OTHERS";
			break;
	}
	res += " ";
	res += this->value;
	res += "";
	return res;
}