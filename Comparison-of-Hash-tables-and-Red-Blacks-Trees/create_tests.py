#!/usr/bin/env python3
# Author: Rotari Corneliu
import random
import math

def insert(number, number2):
    return str("0 " + str(number) + '\n')

def delete(number, number2):
    return str("1 " + str(number) + '\n')

def contains(number, number2):
    return str("2 " + str(number) + '\n')

def swap(number1, number2):
    return str("3 " + str(number1) + " "+ str(number2) + '\n')

def printAll(number1, number2):
    return str("4" + '\n')


def writeToFile(output, file_path):
    fd = open(file_path, 'w');
    fd.write(str(len(output)) + "\n")
    for i in output:
        fd.write(i)
    
    fd.close()
    return

def creat_random_set():
    multime = set([])
    for i in range(nr_of_elements):
        multime.add(math.floor(random.uniform(1, nr_of_elements)))
    lista = list(multime)
    lista.sort()
    multime = set(lista)
    return multime

# -----------------------------------------------------------------------------------------------------------------------------------------
nr_of_op = 100_000
nr_of_elements = 1_000_000

nr_of_insert = 20_000
nr_of_delete = 20_000
# nr_of_contains = 20_000
# nr_of_swaps = 20_000
# nr_of_print = 5_000

# nr_operations_to_make = [nr_of_insert, nr_of_delete, nr_of_contains, nr_of_swaps, nr_of_print]
operations = [insert, delete, contains, swap, printAll]






def descending(file_counter, nr_of_oper):
    lisa = list(creat_random_set())
    lisa.sort(reverse = True)

    output = []
    numbers_added = []
    nr_made_insert = 0

    for i in sorted(lisa, reverse=True):
        if (nr_made_insert < nr_of_insert / nr_of_oper) :
            output.append(insert(i, 0))
            nr_made_insert += 1
            numbers_added.append(i)
        else:
            break
        if (nr_made_insert == 50_000):
            break

    
    until_print = 0
    for i in numbers_added:
        seconde_number = random.randint(i, numbers_added[0] + 1)
        if (until_print < 25):
            output.append(operations[random.randint(1,3)](i, seconde_number))
            until_print += 1
        else :
            output.append(operations[4](0,0))
            until_print = 0
    
    writeToFile(output, str("./in/test" + str(file_counter)+ ".in"))
    return

# def rand():

def ascending(file_counter, nr_of_oper):
    output = []
    numbers_added = []
    nr_made_insert = 0

    for i in creat_random_set():
        if (nr_made_insert < nr_of_insert / nr_of_oper) :
            output.append(insert(i, 0))
            nr_made_insert += 1
            numbers_added.append(i)
        else:
            break
        if (nr_made_insert == 50_000):
            break

    until_print = 0

    for i in numbers_added:
        if (until_print < 25):
            output.append(operations[random.randint(1,3)](i, random.randint(1, i)))
            until_print += 1
        else :
            output.append(operations[4](0,0))
            until_print = 0
    
    writeToFile(output, str("./in/test" + str(file_counter)+ ".in"))
    return

    
def default(file_counter, nr_of_oper, revBool):
    output = []
    numbers_added = list(creat_random_set())
    numbers_added.sort(reverse=revBool)
    maxL = max(numbers_added) + 1

    nr_op = 0
    for i in numbers_added:
        output.append(insert(i, 0))
        nr_op +=1
        if (nr_op == nr_of_insert / nr_of_oper):
            break

    output.append(printAll(0,0))

    until_print = 0
    nr_op = 0
    for i in numbers_added:
        if (until_print < 20):
            output.append(operations[random.randint(2,3)](i, random.randint(1, maxL)))
            if (random.randint(0,5) == 3) :
                output.append(operations[random.randint(0,1)](i, random.randint(1, maxL)))
            
            until_print += 1
        else :
            output.append(printAll(0,0))
            until_print = 0
        nr_op +=1
        if (nr_op == (nr_of_insert / nr_of_oper)):
            break


    output.append(printAll(0,0))

    nr_op = 0
    for i in numbers_added:
        output.append(delete(i, 0))
        nr_op +=1
        if (nr_op == nr_of_delete / nr_of_oper):
            break

    writeToFile(output, str("./in/test" + str(file_counter)+ ".in"))
    return

def randomInput(file_counter, nr_of_iter):

    maxL = nr_of_elements
    output = []

    list_of_elem = list(creat_random_set())
    random.shuffle(list_of_elem)
    op_made = 0
    for j in list_of_elem:
        output.append(operations[random.randint(0,1)](j, random.randint(0, maxL)))
        op_made+=1
        if (j == random.randint(1,nr_of_elements) or op_made == nr_of_op) :
            break


    writeToFile(output, str("./in/test" + str(file_counter)+ ".in"))
    return


def main():
    file_counter = 6
    numbers_to_dived = [50,25,10,5,1]

    # for i in range(5):
    #     default(file_counter, numbers_to_dived[i], False)
    #     file_counter += 1

    for i in range(5):
        ascending(file_counter, numbers_to_dived[i]/10)
        file_counter += 1

    for i in range(5):
        descending(file_counter, numbers_to_dived[i])
        file_counter += 1

    # for i in range(5):
    #     randomInput(file_counter, numbers_to_dived[i])
    #     file_counter += 1






    # format_input(creat_random_set())
    # rand()



if __name__ == '__main__' :
    main()