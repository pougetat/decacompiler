#include <fstream>
#include "lexer.h"

Lexer::Lexer(string input_file)
{
	// reading input file to string
	ifstream input_stream(input_file);
	m_content = string(
		(istreambuf_iterator<char>(input_stream)),
		istreambuf_iterator<char>()
	);
	m_cur_char_index = 0;
}

vector<Token> Lexer::tokenize()
{
	vector<Token> tokens;
	Token token = nextToken();
	tokens.push_back(token);

	while (token.m_token_type != TOKEN_EOF)
	{
		token = nextToken();
		tokens.push_back(token);
	}
	return tokens;
}

Token Lexer::nextToken()
{
	while (m_cur_char_index != m_content.length())
	{
		char cur_char = m_content[m_cur_char_index];
		switch(cur_char)
		{
			case ' ': case '\t': case '\n': case '\r':
			{
				whitespace();
				break;
			}

			// recognizing identifier token
			case 'A' ... 'Z': case 'a' ... 'z': case '_': case '$':
			{
				string ident = get_ident();

				if (keyword_map.find(ident) != keyword_map.end()) {
					return Token(keyword_map[ident], ident);
				}

				return Token(TOKEN_IDENT, ident);
			}

			// recognizing operator tokens
			case '<':
			{
				consume();
				if (match('=')) {
					consume();
					return Token(TOKEN_COMP_LESSEQ, "<=");
				}
				return Token(TOKEN_COMP_LESS, "<");
			}
			case '>':
			{
				consume();
				if (match('=')) {
					consume();
					return Token(TOKEN_COMP_MOREEQ, ">=");
				}
				return Token(TOKEN_COMP_MORE, ">");
			}
			case '+':
			{
				consume();
				return Token(TOKEN_OP_PLUS, "+");
			}
			case '-':
			{
				consume();
				return Token(TOKEN_OP_MINUS, "-");
			}
			case '*':
			{
				consume();
				return Token(TOKEN_OP_MULT, "*");
			}
			case '/':
			{
				consume();
				return Token(TOKEN_OP_DIV, "/");
			}
			case '%':
			{
				consume();
				return Token(TOKEN_OP_MOD, "%");
			}
			case '.':
			{
				consume();
				return Token(TOKEN_OP_DOT, ".");
			}
			case '!':
			{
				consume();
				if (match('=')) {
					consume();
					return Token(TOKEN_COMP_NEQ, "!=");
				}
				return Token(TOKEN_NOT, "!");
			}
			case '=':
			{
				consume();
				if (match('=')) {
					consume();
					return Token(TOKEN_COMP_EQ, "==");
				}
				return Token(TOKEN_OP_ASSIGN, "=");
			}
			case '&':
			{
				consume();
				if (match('&')) {
					consume();
					return Token(TOKEN_AND, "&&");
				}
				throw runtime_error("EXPECTED &");
			}
			case '|':
			{
				consume();
				if (match('|')) {
					consume();
					return Token(TOKEN_OR, "||");
				}
				throw runtime_error("EXPECTED |");
			}

			// recognizing seperator tokens
			case ',':
			{
				consume();
				return Token(TOKEN_COMMA, ",");
			}
			case '(':
			{
				consume();
				return Token(TOKEN_OPARENT, "(");
			}
			case ')':
			{
				consume();
				return Token(TOKEN_CPARENT, ")");
			}
			case '{':
			{
				consume();
				return Token(TOKEN_OBRACE, "{");
			}
			case '}':
			{
				consume();
				return Token(TOKEN_CBRACE, "}");
			}
			case ';':
			{
				consume();
				return Token(TOKEN_SEMICOLON, ";");
			}

			// recognizing literal tokens
			case '0':
			{
				consume();
				return Token(TOKEN_LITERAL_INT, "0");
			}
			case '1'...'9':
			{
				string literal_int = get_literal_int();
				return Token(TOKEN_LITERAL_INT, literal_int);
			}
			case '"':
			{
				string literal_string = get_literal_string();
				return Token(TOKEN_LITERAL_STRING, literal_string);
			}

			default:
				cout << "LEXING ERROR" << endl;
				m_cur_char_index = m_content.length();

		}
	}
	return Token(TOKEN_EOF, "EOF");
}

void Lexer::whitespace()
{
	while (m_content[m_cur_char_index] == ' ' ||
			m_content[m_cur_char_index] == '\t' ||
			m_content[m_cur_char_index] == '\n' ||
			m_content[m_cur_char_index] == '\r')
	{
		consume();
	}
}

void Lexer::consume()
{
	m_cur_char_index++;
}

bool Lexer::match(char symbol)
{
	if (m_cur_char_index < m_content.length() &&
		m_content[m_cur_char_index] == symbol)
	{
		return true;
	}
	return false;
}

bool Lexer::is_letter(char symbol)
{
	return (
		(symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z')
	);
}

bool Lexer::is_digit(char symbol)
{
	return (
		(symbol >= '0' && symbol <= '9')
	);
}

string Lexer::get_ident()
{
	string ident(1, m_content[m_cur_char_index]);
	consume();

	while (
		m_cur_char_index < m_content.length()
			&&
		(
			is_letter(m_content[m_cur_char_index]) ||
			is_digit(m_content[m_cur_char_index]) ||
			m_content[m_cur_char_index] == '_' ||
			m_content[m_cur_char_index] == '$')
		)
	{
		ident += string(1, m_content[m_cur_char_index]);
		consume();
	}

	return ident;
}

string Lexer::get_literal_int()
{
	string literal_int(1, m_content[m_cur_char_index]);
	consume();

	while (is_digit(m_content[m_cur_char_index]))
	{
		literal_int += string(1, m_content[m_cur_char_index]);
		consume();
	}

	return literal_int;
}

string Lexer::get_literal_string()
{
	consume();
	string literal_string("");

	while (!match('"') && m_cur_char_index < m_content.length())
	{
		literal_string += string(1, m_content[m_cur_char_index]);
		consume();
	}
	if (m_cur_char_index == m_content.length())
	{
		throw runtime_error("YOU FORGOT TO CLOSE THE LITERAL STRING");
	}

	consume();

	return literal_string;

}