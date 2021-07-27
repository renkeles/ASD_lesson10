#include <iostream>

const int SIZE_ST = 1000;

#define T char
T Stack[SIZE_ST];
int cursor = -1;

bool push(T data){
    if(cursor < SIZE_ST){
        Stack[++cursor] = data;
        return true;
    }else{
        std::cout << "(push) Stack overflow" << std::endl;
        return false;
    }
}

T pop(){
    if(cursor != -1){
        return Stack[cursor--];
    }else{
        std::cout << "(pop) Stack overflow" << std::endl;
        return false;
    }
}

int main() {
    char str[] = "[2/{5*(4+7)}]";

    int i = 0;
    while(str[i] != '\0'){
        if(str[i] == '('){
            push(str[i]);
            i++;
        }else if(str[i] == ')' && cursor != -1){
            pop();
        }
    }
    std::cout << (cursor == -1) ? 1:0;
    return 0;
}
