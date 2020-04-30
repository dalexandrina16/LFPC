#include <iostream>
#include <fstream>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

using namespace std;

int Keyword(char str[]){
    char keywords[32][10] = {
        "int",
        "char",
        "double",
        "float",
        "return",
        "print",
        "else",
        "if",
        "for",
        "while",
        "do",
        "true",
        "false"
    };

    for(int i = 0; i < 10; i++){
        if(strcmp(keywords[i], str) == 0) {
            return 1;
            break;
        }
    }
    return 0;
}

bool Variable(char str[]) {
    switch (str[0]) {
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'L':
        case 'M':
        case 'N':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        case 'V':
        case 'W':
        case 'X':
        case 'Y':
        case 'Z':
            return true;
    }
   return false;
}

bool Separator(char str) {
    switch (str) {
        case ' ':
        case ';':
        case ',':
        case '.':
        case ')':
        case '(':
        case '}':
        case '{':
            return true;
    }
    return false;
}

bool Delimiter (char str) {
    return str == '"';
}

bool Operator(char str) {
    switch (str) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '=':
        case '<':
        case '>':
            return true;
    }
    return false;

}

bool Digit(char str[]) {
    switch (str[0]) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        return true;
    }
    return false;
}


bool Variable_value(char str[]) {
    int len = strlen(str);
    if (len <= 1) {
        return false;
    }
    for (int i = 0; i < len; i++) {
        if (str[i] != '`' && str[len] != '`') {
            return true;
        }
    }
    return false;
}

char* subString(char* str, int left, int right)
{
    char* subStr = (char*)malloc(
        sizeof(char) * (right - left + 2));
    for (int i = left; i <= right; i++) {
        subStr[i - left] = str[i];
    }
    subStr[right - left + 1] = '\0';
    return subStr;
}

void parse(char* str) {
    int left = 0, right = 0;
    int len = strlen(str);
    while (right <= len && left <= right) {
        if (!Separator(str[right]))
            right++;

        if (Separator(str[right]) && left == right) {
            if (Operator(str[left]))
                printf("'%c' is an operator\n", str[right]);

            right++;
            left = right;
        }

        else if (Separator(str[right]) && left != right || (right == len && left != right)) {
            char* subStr = subString(str, left, right - 1);

            if (Keyword(subStr)) {
                printf("'%s' - KEYWORD\n", subStr);
            }
            else if (Operator(str[left])) {
                printf("'%s' - OPERATOR\n", subStr);
            }
            else if (Variable_value(subStr)) {
                printf("'%s' - STRING VALUE\n", subStr);
            }
            else if (Digit(subStr)) {
                printf("'%s' - DIGIT\n", subStr);
            }
            else if (Variable(subStr) && !Separator(str[right - 1])) {
                printf("'%s' - VARIABLE\n", subStr);
            }
            else if (!Variable(subStr) && !Separator(str[right - 1])) {
                printf("'%s' - INVALID INPUT\n", subStr);
            }
            left = right;
        }
    }
}

int main() {
	ifstream codefile;
	char str[256], file_path[20];
	cout<<"Open a file containing a code syntax\nEnter file path: ";
	cin>>file_path;
	codefile.open(file_path);
	if(!codefile) {
		cout<<"Error. Check if you wrote correct file path.";
		getch();
		exit(0);
	}
	while(!codefile.eof()) {
        codefile>>str;
        parse(str);

	}
    return 0;
}
