# Train Station
                 <!-- _-====-__-======-__-=======-___-========-_____-============-__
               _(                                                             _)
            OO(      Application that keeps the records of a train staion.    )_
           0  (  Easily finds the information and solutions to given problems. _)
         o0     (_                                                           _)
        o         '=-___-===-_____-=======-__-=======-___________-====-dwb-='
      .o                                
     . ______ ________ ______________  ____________ _____________
   _()_||__|| |      | |            |  |          | |           |
  (         | |      | |            |  |          | |           |
 /-OO----OO""="OO--OO"="OO--------OO"="OO-------OO"="OO-------OO"=P
##################################################################### -->
# 1. Operation :
1. arrive_train :
    1. initializes a train.
2. leave_train : 
    1. Removing the train cars and after that the train from the memory.
3. add_train_car:
    1. Adding the train car at the end of the train.
4. remove_train_cars :
    1. The first train_car is equal to the weigth.
    2. Every other train_car.
5. move_train_cars :
    1. Cut phase :
        1. First position check.
        2. Remembering the node before the cut.
        3. Remembering the last node in the sequence.
    2. Paste phase :
        1. First position check.
        2. After the train position check.
        3. Middle position.
# 2. Finding
1. find_express_train :
    1. Biggest difference between locomotive power and train cars weight.
2. find_overload_train :
    1. Finding the train that has the weight of the train cars bigger than the locomotive power.
3. find_optimal_train :
    1. Smallest difference between locomotive power and train cars weight.
4. find_heaviest_sequence_train :
    1. Looping throughout the whole station.
    2. Checking the sequence from every possible train car.
    3. Constantly changing the heaviest sequence.

# 3. Oragnization
1. order_train :
    1. Bubble Sort the train in descending order until on the last loop nothing has chanced.
2. fix_overload_train :
    1. Find the overloaded train.
    2. Copying the train in an imaginary station for how many train cars it has.
    3. Removing a different train car for every scenario
    4. Checking every case scenario for finding the train which has the closest weight to the train locomotive power.
    5. Deleting the imaginary train station.

