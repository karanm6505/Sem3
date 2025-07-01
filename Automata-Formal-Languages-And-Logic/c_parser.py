import ply.yacc as yacc
from c_lexer import tokens, lexer

class Parser:
    tokens = tokens  

    def __init__(self):
        self.success = True
        self.parser = None
        self.variables = set()

    def p_program(self, p):
        '''program : statement_list'''
        p[0] = ('program', p[1])

    def p_statement_list(self, p):
        '''statement_list : statement_list statement
                        | statement'''
        if len(p) == 3:
            if p[1] is None:
                p[0] = [p[2]]
            else:
                p[0] = p[1] + [p[2]]
        else:
            p[0] = [p[1]]

    def p_statement(self, p):
        '''statement : assignment_statement
                    | if_statement
                    | loop_statement
                    | include_statement'''
        p[0] = p[1]

    def p_include_statement(self, p):
        '''include_statement : POUND INCLUDE LESS HEADER GREATER
                           | POUND INCLUDE LESS ID GREATER
                           | POUND INCLUDE QUOTE HEADER QUOTE
                           | POUND INCLUDE QUOTE ID QUOTE
                           '''
        p[0] = ('include', p[4])

    def p_assignment_statement(self, p):
        '''assignment_statement : ID ASSIGN expression SEMICOLON'''
        self.variables.add(p[1])
        p[0] = ('assign', p[1], p[3])

    def p_if_statement(self, p):
        '''if_statement : IF LPAREN condition RPAREN compound_statement
                       | IF LPAREN condition RPAREN compound_statement ELSE compound_statement'''
        if len(p) == 6:
            p[0] = ('if', p[3], p[5])
        else:
            p[0] = ('if_else', p[3], p[5], p[7])

    def p_loop_statement(self, p):
        '''loop_statement : while_loop
                        | for_loop
                        | do_while_loop'''
        p[0] = p[1]

    def p_while_loop(self, p):
        '''while_loop : WHILE LPAREN condition RPAREN compound_statement'''
        p[0] = ('while', p[3], p[5])

    def p_for_loop(self, p):
        '''for_loop : FOR LPAREN assignment_statement condition SEMICOLON expression RPAREN compound_statement'''
        p[0] = ('for', p[3], p[4], p[6], p[8])

    def p_do_while_loop(self, p):
        '''do_while_loop : DO compound_statement WHILE LPAREN condition RPAREN SEMICOLON'''
        p[0] = ('do_while', p[2], p[5])

    def p_compound_statement(self, p):
        '''compound_statement : LBRACE statement_list RBRACE
                            | LBRACE RBRACE'''
        if len(p) == 4:
            p[0] = ('compound', p[2])
        else:
            p[0] = ('compound', [])

    def p_condition(self, p):
        '''condition : expression LESS expression
                    | expression GREATER expression
                    | expression EQUALS expression'''
        p[0] = ('condition', p[2], p[1], p[3])

    def p_expression(self, p):
        '''expression : expression PLUS expression
                     | expression MINUS expression
                     | LPAREN expression RPAREN
                     | ID
                     | NUMBER'''
        if len(p) == 4:
            if p[1] == '(':
                p[0] = p[2]
            else:
                p[0] = ('binary_op', p[2], p[1], p[3])
        else:
            p[0] = p[1]

    def p_error(self, p):
        if p:
            print(f"Syntax error at '{p.value}', line {p.lineno}")
        else:
            print("Syntax error at EOF")
        self.success = False

    def build(self):
        self.parser = yacc.yacc(module=self)
        return self.parser

    def parse(self, data):
        if self.parser is None:
            self.build()
        self.success = True
        result = self.parser.parse(data, lexer=lexer)
        return result, self.success, self.variables

def test_parser():
    parser = Parser()
    
    test_code = """
    #include <stdio.h>
    #include "myheader.h"
    x = 10;
    if (x > 5) {
        y = 20;
    } else {
        y = 0;
    }
    while (x < 1) {
        x = x - 1;
    }
    """
    
    print("Testing Lexer:")
    lexer.input(test_code)
    for tok in lexer:
        print(tok)
        
    print("\nTesting Parser:")
    result, success, variables = parser.parse(test_code)
    
    print("Parse Tree:", result)
    print("Parsing Success:", success)
    print("Variables:", variables)

if __name__ == "__main__":
    test_parser()