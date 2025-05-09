///\file
///\brief This main file is operations with stack
#include "stack.h"

//TODO add tests with next struct...
struct Page {
    int id;
    char buf[256];
};

void my_print(FILE* file, Page *el) {
    fprintf (file, "id = %d, buf = %s", el->id, el->buf);
} 

int main()
{
    stack_type stk = {};
    // SetPrinterFunc(&stk, my_print); // TODO add printer func
    int* err = NULL;
    elem_t k = 5; // TODO rename
    elem_t d = 7;
    elem_t l = 8;
    elem_t* test = NULL;
    elem_t value = 3;
    stackCreator_(&stk, 1);
    stackPush(&stk, &k);
    
    
    stackPush(&stk, &l);
    stackPush(&stk, &d);
    stackPush(&stk, &d);
    stackPush(&stk, &d);
    int sum_of_errors = stackError(&stk);
    stackDump(&stk, NULL, (stk.name), __LINE__, __PRETTY_FUNCTION__, __FILE__);
    return 0;
}

//=========================================================================================

