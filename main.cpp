#include <iostream>

#define T int

typedef struct OneLinkNode{
    T dat;
    OneLinkNode *next;
} OneLinkNode;

typedef struct {
    OneLinkNode *head;
    int size;
} OneLinkList;

void initOneLinkList(OneLinkList *lst){
    lst->head = nullptr;
    lst->size = 0;
}

bool push(OneLinkList *stack, T value){
    OneLinkNode *tmp = new OneLinkNode;
    if(tmp == nullptr){
        std::cout << "Stack overflow" << std::endl;
        return 0;
    }
    tmp->dat = value;
    tmp->next = stack->head;

    stack->head = tmp;
    stack->size++;
}

T pop(OneLinkList *stack){
    if(stack->size == 0){
        std::cout << "Stack is empty" << std::endl;
        return -1;
    }
    OneLinkNode *tmp = stack->head;
    T data = stack->head->dat;
    stack->head = stack->head->next;
    delete tmp;
    stack->size--;
    return data;

}

int bracesCheck(char* exp){
    const int TYPES = 3;
    char braces[][2] = {{'(', ')'}, {'{', '}'}, {'[', ']'}};
    OneLinkList *st = new OneLinkList;
    initOneLinkList(st);
    int countIndex = 0;
    while(*exp != '\0'){
        for(int i = 0; i < TYPES; i++){
            if(*exp == braces[i][0]){
                push(st, i);
            }
        }
        for(int i = 0; i < TYPES; i++){
            if(*exp == braces[i][1]){
                if(st->size == 0){
                    return countIndex;
                }
                if(i == st->head->dat){
                    pop(st);
                }else{
                    return countIndex;
                }
            }
        }
        exp++;
        countIndex++;
    }
}

void printBC(int n){
    std::cout << ((n == 0) ? "True" : "False") << std::endl;
}

void printOneLinkNode(OneLinkNode* node){
    if(node == nullptr){
        std::cout << "[]";
        return;
    }
    std::cout << "[" << node->dat << "]";
}

void printOneLinkList(OneLinkList* lst){
    OneLinkNode* current = lst->head;
    if(current == nullptr){
        printOneLinkNode(current);
    }else{
        do{
            printOneLinkNode(current);
            current = current->next;
        } while (current != nullptr);
    }
    std::cout << " Size: " << lst->size << std::endl;
}

void copyList(OneLinkList* from, OneLinkList* to){
    int size = from->size;
    OneLinkNode* current = from->head;
    while(size != 0){
        for(int i = 0; i < size - 1; i++){
            current = current->next;
        }
        push(to, current->dat);
        size--;
        current = from->head;
    }
}

bool isSorted(OneLinkList *lst){
    OneLinkNode* current = lst->head;
    while(current->next != nullptr){
        if(current->dat > current->next->dat){
            return 0;
        }
        current = current->next;
    }
    return 1;
}

int main() {

    printBC(bracesCheck("[]"));
    printBC(bracesCheck("[]]"));
    printBC(bracesCheck("{}(]"));
    printBC(bracesCheck("{ ( [ {} [] () ] ( }"));
    printBC(bracesCheck("[2/{5*(4+7)}]"));

    OneLinkList* first = new OneLinkList;
    initOneLinkList(first);
    OneLinkList* second = new OneLinkList;
    initOneLinkList(second);
    for(int i = 0; i < 9; i++){
        push(first, i);
    }
    printOneLinkList(first);
    copyList(first, second);
    printOneLinkList(second);

    std::cout << ((isSorted(first)) ? "True" : "False") << std::endl;
    OneLinkList* third = new OneLinkList;
    initOneLinkList(third);
    for(int i = 9; i > 0; i--){
        push(third, i);
    }
    printOneLinkList(third);
    std::cout << ((isSorted(third)) ? "True" : "False") << std::endl;

    return 0;
}
