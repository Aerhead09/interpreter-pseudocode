 #ifndef TOKEN_H
 #define TOKEN_H

 #include <string>

 enum class TokenType {
    IDENTIFIER,
    INT_LITERAL,
    TRUE_LITERAL,
    FALSE_LITERAL,

    ASSIGN,
    EQUALS,
    LESS_THAN,
    GREATER_THAN,
    LESS_THAN_EQUALS,
    GREATER_THAN_EQUALS,
    PLUS,
    MINUS,
    STAR,
    SLASH,
    MOD,
    COMMA,
    COLON,
    LPAREN,
    RPAREN,

    PROGRAM,
    ENDPROGRAM,
    TYPE_INT,
    INPUT,
    OUTPUT,

    FOR,
    TO,
    DO,
    ENDFOR,
    WHILE,
    ENDWHILE,
    
    IF,
    THEN,
    ELSE,
    ENDIF,

    AND,
    OR,

    END_OF_FILE
 };

struct Token {
    TokenType type;
    std::string literal;
};

 #endif