//栈C语言列出 中缀表达式转换等价后缀表达式
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

// 定义栈结构
typedef struct {
    char items[MAX_SIZE];
    int top;
} Stack;

// 初始化栈
void init(Stack* s) {
    s->top = -1;
}

// 判断栈是否为空
int isEmpty(Stack* s) {
    return s->top == -1;
}

// 获取栈顶元素
char peek(Stack* s) {
    return s->items[s->top];
}

// 元素入栈
void push(Stack* s, char value) {
    if (s->top == MAX_SIZE - 1) {
        printf("Stack is full\n");
        return;
    }
    s->items[++(s->top)] = value;
}

// 元素出栈
char pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack is empty\n");
        return '\0';
    }
    return s->items[(s->top)--];
}

// 判断字符是否为操作数
int isOperand(char c) {
    return isalnum(c);
}

// 返回运算符的优先级
int precedence(char c) {
    if (c == '^')
        return 3;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return 0;
}

// 将中缀表达式转换为后缀表达式
void infixToPostfix(char* infixExpression) {
    Stack operatorStack;
    init(&operatorStack);
    char postfixExpression[MAX_SIZE] = "";
    int j = 0;

    for (int i = 0; i < strlen(infixExpression); i++) {
        char c = infixExpression[i];
        if (isOperand(c)) {
            postfixExpression[j++] = c;
        }
        else if (c == '(') {
            push(&operatorStack, c); // 左括号入栈
        }
        else if (c == ')') {
            while (!isEmpty(&operatorStack) && peek(&operatorStack) != '(') {
                postfixExpression[j++] = pop(&operatorStack); // 弹出并加入后缀表达式，直到遇到匹配的左括号
            }
            if (!isEmpty(&operatorStack) && peek(&operatorStack) != '(') { // 括号不匹配
                printf("Invalid expression\n");
                return;
            }
            else {
                pop(&operatorStack); // 弹出左括号
            }
        }
        else { // Operator
            while (!isEmpty(&operatorStack) && precedence(peek(&operatorStack)) >= precedence(c)) {
                postfixExpression[j++] = pop(&operatorStack); // 弹出并加入后缀表达式，直到栈顶运算符优先级小于当前运算符
            }
            push(&operatorStack, c); // 当前运算符入栈
        }
    }

    while (!isEmpty(&operatorStack)) {
        if (peek(&operatorStack) == '(') {
            printf("Invalid expression\n");
            return;
        }
        postfixExpression[j++] = pop(&operatorStack); // 弹出并加入后缀表达式，直到栈为空
    }
    postfixExpression[j] = '\0';

    printf("Infix Expression: %s\n", infixExpression);
    printf("Postfix Expression: %s\n", postfixExpression);
}

int main() {
    char infixExpression[] = "3 + 4 * 2 / (1 - 5)^2";
    infixToPostfix(infixExpression);

    return 0;
}
