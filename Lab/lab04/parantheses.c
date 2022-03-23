#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 256

typedef char Item;
#include "Stack.h"

int isBalanced(const char *str, int length){

  /* TODO: Cerinta 3
   * Implementation must use a stack.
   * Do NOT forget to deallocate the memory you use.
   */
  int ret = 1;
  if (str[0] == '{' || str[0] == '(' || str[0] == '[') {
    Stack *stack = createStack();   
      for (int i = 0; i < length; i++) {
        if (str[i] == '{' || str[i] == '(' || str[i] == '[') {
          push(stack, str[i]);
        } else {
          if (isStackEmpty(stack)) {
            ret = 0;
            break;
          } else {
            Item elem1 = top(stack);
            pop(stack);
            if (elem1 == '{' && str[i] == '}') continue;
            if (elem1 == '(' && str[i] == ')') continue;
            if (elem1 == '[' && str[i] == ']') continue;
            ret = 0;
            break;
          }
        }
      }
      if (!isStackEmpty(stack)) {
            ret = 0;
      }
      destroyStack(stack);
  }
    return ret;
      
}

int main(){
    int len;
    char buffer[MAX_INPUT_LEN];
    FILE* inputFile = fopen("input-parantheses.txt","r");
    if(inputFile == NULL) return 1;


    while(fgets(buffer, MAX_INPUT_LEN, inputFile) != NULL){
      buffer[strcspn(buffer, "\r\n")] = 0;
      len = strlen(buffer);
      if(len == 0) break;

      if(isBalanced(buffer, len))
        printf("%s ---> is balanced.\n", buffer);
      else
        printf("%s ---> not balanced.\n", buffer);
    }

    fclose(inputFile);

    return 0;
}
