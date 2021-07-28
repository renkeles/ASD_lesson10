#include <iostream>

#define T size_t

typedef struct Node{
    T dat;
    Node *next;
} Node;

typedef struct {
    Node *head;
    size_t size;
} List;

void initList(List *lst){
    lst->head = nullptr;
    lst->size = 0;
}

bool push(List *stack, T value){
    Node *tmp = new Node;
    if(tmp == nullptr){
        std::cout << "Stack overflow" << std::endl;
        return 0;
    }
    tmp->dat = value;
    tmp->next = stack->head;

    stack->head = tmp;
    stack->size++;
}

T pop(List *stack){
    if(stack->size == 0){
        std::cout << "Stack is empty" << std::endl;
        return -1;
    }
    Node *tmp = stack->head;
    T data = stack->head->dat;
    stack->head = stack->head->next;
    delete tmp;
    stack->size--;
    return data;
}

size_t bracesCheck(char* exp){
    const size_t TYPES = 3;
    char braces[][2] = {{'(', ')'}, {'{', '}'}, {'[', ']'}};
    List *st = new List;
    initList(st);
    size_t countIndex = 0;
    while(*exp != '\0'){
        for(size_t i = 0; i < TYPES; i++){
            if(*exp == braces[i][0]){
                push(st, i);
            }
        }
        for(size_t i = 0; i < TYPES; i++){
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

void printNode(Node* node){
    if(node == nullptr){
        std::cout << "[]";
        return;
    }
    std::cout << "[" << node->dat << "]";
}

void printList(List* lst){
    Node* current = lst->head;
    if(current == nullptr){
        printNode(current);
    }else{
        do{
            printNode(current);
            current = current->next;
        } while (current != nullptr);
    }
    std::cout << " Size: " << lst->size << std::endl;
}

void copyList(List* from, List* to){
    int size = from->size;
    Node* current = from->head;
    while(size != 0){
        for(size_t i = 0; i < size - 1; i++){
            current = current->next;
        }
        push(to, current->dat);
        size--;
        current = from->head;
    }
}

bool isSorted(List *lst){
    Node* current = lst->head;
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

    List* first = new List;
    initList(first);
    List* second = new List;
    initList(second);
    for(size_t i = 0; i < 9; i++){
        push(first, i);
    }
    printList(first);
    copyList(first, second);
    printList(second);

    std::cout << ((isSorted(first)) ? "True" : "False") << std::endl;
    List* third = new List;
    initList(third);
    for(size_t i = 9; i > 0; i--){
        push(third, i);
    }
    printList(third);
    std::cout << ((isSorted(third)) ? "True" : "False") << std::endl;

    return 0;
}
