# Stack Implementations and Applications

This directory contains various implementations of stack data structure and its applications in C programming language.

## 1. Stack Array Implementation (StackArray.c)
A basic implementation of stack using arrays with the following features:
- Fixed size implementation (SIZE = 10)
- Basic operations: push, pop, peek, isEmpty, isFull
- Stack overflow and underflow handling
- Display function to show stack contents
- Time Complexity: O(1) for all operations

## 2. Stack Linked List Implementation (StackLinkedList.c)
A dynamic implementation of stack using linked list with:
- Dynamic memory allocation for nodes
- No size limitation (except system memory)
- Operations: push, pop, peek, isEmpty
- Memory management with proper freeing of nodes
- Time Complexity: O(1) for all operations

## 3. Postfix Expression Evaluation (PostfixEvaluation.c)
Program to evaluate postfix expressions:
- Handles numeric operands and basic operators (+, -, *, /, ^)
- Uses stack to store intermediate results
- Converts character digits to integers for calculation
- Supports power operation using math.h
- Time Complexity: O(n) where n is length of expression

## 4. Parenthesis Matching (ParenthesisMatching.c)
Validates balanced parentheses in expressions:
- Supports multiple types of brackets: (), {}, []
- Checks for proper nesting of brackets
- Returns "Balanced" or "Not Balanced"
- Handles invalid cases:
  - Mismatched brackets: (}
  - Incomplete brackets: ({)
- Time Complexity: O(n) where n is length of expression

## 5. Infix to Prefix Conversion (InfixToPrefix.c)
Converts infix expressions to prefix notation:
- Algorithm:
  1. Reverse the infix expression
  2. Convert reversed expression to postfix
  3. Reverse the result
- Handles operators: +, -, *, /, ^
- Supports parentheses
- Time Complexity: O(n) where n is length of expression

## 6. Infix to Postfix Conversion (InfixToPostfix.c)
Converts infix expressions to postfix notation:
- Implements operator precedence
- Handles parentheses correctly
- Supports basic arithmetic operators
- Validates expression correctness
- Time Complexity: O(n) where n is length of expression

## Common Stack Operations Time Complexity
- Push: O(1)
- Pop: O(1)
- Peek: O(1)
- isEmpty: O(1)
- isFull: O(1)

## Algorithms

### Stack Array Implementation Algorithm
1. Initialize:
   - Create array of fixed size
   - Set top = -1
2. Push Operation:
   ```
   if (top == SIZE-1)
      return overflow
   else
      top++
      stack[top] = element
   ```
3. Pop Operation:
   ```
   if (top == -1)
      return underflow
   else
      element = stack[top]
      top--
      return element
   ```

### Stack Linked List Implementation Algorithm
1. Initialize:
   - Create empty node pointer for top
2. Push Operation:
   ```
   newNode = create node with data
   newNode->next = top
   top = newNode
   ```
3. Pop Operation:
   ```
   if (top == NULL)
      return underflow
   temp = top
   top = top->next
   return temp
   ```

### Postfix Evaluation Algorithm
1. Scan expression from left to right
2. For each element:
   ```
   if element is operand
      push to stack
   if element is operator
      pop two operands
      perform operation
      push result back
   ```
3. Final answer is top of stack

### Parenthesis Matching Algorithm
1. Initialize empty stack
2. For each character in expression:
   ```
   if char is opening bracket ('(', '{', '[')
      push to stack
   if char is closing bracket (')', '}', ']')
      if stack is empty
         return unbalanced
      if top matches current bracket
         pop stack
      else
         return unbalanced
   ```
3. Return balanced if stack is empty, else unbalanced

### Infix to Prefix Algorithm
1. Reverse input string
2. For each character from left to right:
   ```
   if char is operand
      add to output
   if char is operator
      while (stack not empty AND precedence(stack_top) >= precedence(char))
         pop and add to output
      push char to stack
   if char is ')'
      push to stack
   if char is '('
      pop and output until ')' is found
      pop ')'
   ```
3. Pop and output all remaining operators
4. Reverse final string

### Infix to Postfix Algorithm
1. Initialize empty stack and output string
2. For each character from left to right:
   ```
   if char is operand
      add to output
   if char is operator
      while (stack not empty AND precedence(stack_top) >= precedence(char))
         pop and add to output
      push char to stack
   if char is '('
      push to stack
   if char is ')'
      pop and output until '(' is found
      pop '('
   ```
3. Pop and output all remaining operators
