#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "station.h"

// Helping functions------------------------------------
#define MAX 1000

int length_car(TrainCar *train) {
    int lenght = 0;
    TrainCar *aux = train;
    while (aux != NULL) {
        lenght++;
        aux = aux->next;
    }
    return lenght;
}

void print_car(TrainCar *train) {
    TrainCar *aux = train;
    while (aux != NULL) {
        printf("-|%d|",aux->weight);
        aux = aux->next;
    }
    printf("\n");
    return;
}

int train_cars_weight(TrainCar* train) {
    TrainCar* aux = train;
    int weight = 0;
    while (aux != NULL) {
        weight += aux->weight;
        aux = aux->next;
    }
    return weight;
}
//--------------------------------------------------


/* Creeaza o gara cu un numar fix de peroane.
 * 
 * platforms_no: numarul de peroane ale garii
 *
 * return: gara creata
 */
TrainStation* open_train_station(int platforms_no) {
    // Error check
    if (platforms_no <= 0) return NULL;
    
    // Train station allocation
    TrainStation *tr_st = malloc(sizeof(TrainStation));
    // Pointer validation
    if (tr_st) {
        tr_st->platforms_no = platforms_no;
        tr_st->platforms = malloc(sizeof(TrainCar *) * platforms_no);
        // Pointer validation
        if (tr_st->platforms) {
            for (int i = 0; i < platforms_no; i++) {
                tr_st->platforms[i] = NULL;
            }
        } 
    }  
    return tr_st;
}


/* Elibereaza memoria alocata pentru gara.
 *
 * station: gara existenta
 */
void close_train_station(TrainStation *station) {
    // Error check
    if ((station == NULL) || (station->platforms == NULL)) return;

    // Frees train station
    for (int i = 0; i < station->platforms_no; i++) {
        if (station->platforms[i] != NULL) {
            if (station->platforms[i]->train_cars != NULL) {
                TrainCar* aux = station->platforms[i]->train_cars, *aux_free;
                while (aux != NULL) {
                    aux_free = aux;
                    aux=aux->next;
                    free(aux_free);
                }
            }
            free(station->platforms[i]);
        }
    }
    free(station->platforms);
    free(station);
    return;
}


/* Afiseaza trenurile stationate in gara.
 *
 * station: gara existenta
 * f: fisierul in care se face afisarea
 */
void show_existing_trains(TrainStation *station, FILE *f) {
    // Error check
    if (station != NULL && f != NULL && station->platforms != NULL) { 
        for (int i = 0; i < station->platforms_no; i++){
            // Nr of the gate
            fprintf(f,"%d: ",i);
            if (station->platforms[i] == NULL) {
                // No train
                fprintf(f,"\n");
            } else {
                // Train exists
                fprintf(f,"(%d)",station->platforms[i]->locomotive_power);
                TrainCar *aux = station->platforms[i]->train_cars;
                // Train cars
                while (aux != NULL) {
                    fprintf(f,"-|%d|",aux->weight);
                    aux = aux->next;
                }
                fprintf(f,"\n");
            }
        }
    }
    return;
}


/* Adauga o locomotiva pe un peron.
 * 
 * station: gara existenta
 * platform: peronul pe care se adauga locomotiva
 * locomotive_power: puterea de tractiune a locomotivei
 */
void arrive_train(TrainStation *station, int platform, int locomotive_power) {
    // Error check
    if ((platform >= station->platforms_no) || (platform < 0)|| (station == NULL) || 
    station->platforms[platform] != NULL) return;
    // Train arrives
    station->platforms[platform] = malloc(sizeof(Train));
    station->platforms[platform]->locomotive_power = locomotive_power;
    station->platforms[platform]->train_cars = NULL;
    return;
}


/* Elibereaza un peron.
 * 
 * station: gara existenta
 * platform: peronul de pe care pleaca trenul
 */
void leave_train(TrainStation *station, int platform) {
    // Error check
    if ((station == NULL) || (platform >= station->platforms_no) || (platform < 0) || 
        (station->platforms == NULL) || (station->platforms[platform] == NULL)) return;    
    // Free train
    TrainCar *aux = station->platforms[platform]->train_cars, *aux_free = NULL;
    while (aux != NULL) {
        aux_free = aux;
        aux = aux->next;
        free(aux_free);
    }
    free(station->platforms[platform]);
    station->platforms[platform] = NULL;
    return;
}


/* Adauga un vagon la capatul unui tren.
 * 
 * station: gara existenta
 * platform: peronul pe care se afla trenul
 * weight: greutatea vagonului adaugat
 */
void add_train_car(TrainStation *station, int platform, int weight) {
    // Error check
    if ((station == NULL) || (platform >= station->platforms_no) || (platform < 0) || 
        (station->platforms == NULL) || (station->platforms[platform] == NULL) || (weight < 0)) return;
    // TrainCar creation
    TrainCar *new_car = malloc(sizeof(TrainCar));
    new_car->weight = weight;
    new_car->next = NULL;
    // No car yet 
    if (station->platforms[platform]->train_cars == NULL) {
        station->platforms[platform]->train_cars = new_car;
    } else {
    // At least one car exists
        TrainCar *aux = station->platforms[platform]->train_cars;
        while (aux->next != NULL){
            aux = aux->next;
        }
        aux->next = new_car;
    }
    return;
}


/* Scoate vagoanele de o anumita greutate dintr-un tren.
 * 
 * station: gara existenta
 * platform: peronul pe care se afla trenul
 * weight: greutatea vagonului scos
 */
void remove_train_cars(TrainStation *station, int platform, int weight) {
    // Error check
    if ((station == NULL) || (platform >= station->platforms_no) || (platform < 0) || 
        (station->platforms == NULL) || (station->platforms[platform] == NULL) || (weight < 0)) return;
    
    TrainCar *aux = station->platforms[platform]->train_cars;

    while (aux != NULL) {
        // Case weight first
        if ((aux->weight == weight) && (aux == station->platforms[platform]->train_cars)) {
            // Only train car or not
            if (aux->next != NULL) {
                TrainCar * new_begin = aux->next;
                free(aux);
                aux = new_begin;
                station->platforms[platform]->train_cars = new_begin;
                continue;
            } else {
                free(aux);
                station->platforms[platform]->train_cars = NULL;
                return;
            }
        }
        // Rest of the cases
        if (aux->next != NULL) {
            if (aux->next->weight == weight) {
                TrainCar *new_car = aux->next->next;
                free(aux->next);
                aux->next = new_car;
                if ((new_car != NULL) && (new_car->weight == weight)) {
                    continue; // case multiple cars connected 
                }
            }
        }
        aux = aux->next;
    }
    return;
}


/* Muta o secventa de vagoane dintr-un tren in altul.
 * 
 * station: gara existenta
 * platform_a: peronul pe care se afla trenul de unde se scot vagoanele
 * pos_a: pozitia primului vagon din secventa
 * cars_no: lungimea secventei
 * platform_b: peronul pe care se afla trenul unde se adauga vagoanele
 * pos_b: pozitia unde se adauga secventa de vagoane
 */
void move_train_cars(TrainStation *station, int platform_a, int pos_a, 
                                int cars_no, int platform_b, int pos_b) {
// Error check and useless input check
    if ((platform_a >= station->platforms_no) || (platform_a < 0) ||
        (pos_a <= 0) || (pos_a > length_car(station->platforms[platform_a]->train_cars)) ||
        (platform_b >= station->platforms_no) || (platform_b < 0) ||
        (pos_b <= 0) || (pos_b > length_car(station->platforms[platform_b]->train_cars)+1) ||
        ((cars_no + pos_a - 1) > length_car(station->platforms[platform_a]->train_cars)) ||
        (cars_no > length_car(station->platforms[platform_a]->train_cars)) || (cars_no == 0)) return;
    
    TrainCar * car_moved = NULL, *aux = station->platforms[platform_a]->train_cars,
                *base = NULL, *old_pointer = NULL, *last_point_cars_moved = NULL;
    
// Cut phase
    if (pos_a == 1) {
        // First position (needs to replace pointer in the Train)
        car_moved = aux;
        for (int i = 0; i < cars_no; i++) {
            old_pointer = aux;
            aux = aux->next;
        }
        station->platforms[platform_a]->train_cars = aux;
        last_point_cars_moved = old_pointer;    // pointer to the lst postion of the sequence
        old_pointer->next = NULL;
    } else {
        int i = 0;
        while (((i+1) != pos_a) && (aux->next != NULL)) {
            base = aux;
            aux=aux->next;
            i++;
        }
        car_moved = aux;
        for(int i = 0; i < cars_no; i++) {
            if (aux == NULL) break;
            old_pointer = aux;
            aux = aux->next;
        }
        last_point_cars_moved = old_pointer;
        old_pointer->next = NULL;
        base->next= aux;
    }  // car_moved result
// Paste phase
    if (pos_b == 1) {
        aux = station->platforms[platform_b]->train_cars;
        station->platforms[platform_b]->train_cars = car_moved;
        last_point_cars_moved->next = aux;
    } else if (pos_b == length_car(station->platforms[platform_b]->train_cars) + 1) {
        aux = station->platforms[platform_b]->train_cars;
        while (aux->next != NULL){
            aux = aux->next;
        }
        aux->next = car_moved;    
    } else {
        aux = station->platforms[platform_b]->train_cars;
        for (int i = 1; i < length_car(station->platforms[platform_b]->train_cars); i++) {
            if (i + 1 == pos_b) {
                last_point_cars_moved ->next= aux->next;
                aux->next = car_moved;
                break;
            }
            aux = aux->next;
        }
    }
    return;
}
 

/* Gaseste trenul cel mai rapid.
 * 
 * station: gara existenta
 *
 * return: peronul pe care se afla trenul
 */
int find_express_train(TrainStation *station) {
    int max = station->platforms[0]->locomotive_power - 
                train_cars_weight(station->platforms[0]->train_cars),
        gate = 0;
    for (int i = 0; i < station->platforms_no; i++) {
        if (station->platforms[i] != NULL) {
            int compare = station->platforms[i]->locomotive_power -
                            train_cars_weight(station->platforms[i]->train_cars);
            if (compare > max) {
                max = compare;
                gate = i;
            }
        }
    }
    return gate;
}


/* Gaseste trenul supraincarcat.
 * 
 * station: gara existenta
 *
 * return: peronul pe care se afla trenul
 */
int find_overload_train(TrainStation *station) {
    for (int i = 0; i < station->platforms_no; i++) {
        if (station->platforms[i] != NULL) {
            int max = train_cars_weight(station->platforms[i]->train_cars) -
                        station->platforms[i]->locomotive_power;
            if (max > 0) {
                return i;
            }
        }
    }
    return -1;
}


/* Gaseste trenul cu incarcatura optima.
 * 
 * station: gara existenta
 *
 * return: peronul pe care se afla trenul
 */
int find_optimal_train(TrainStation *station) {
    int min = MAX, // Defalute value
        gate = 0;
    for (int i = 0; i < station->platforms_no; i++) {
        if (station->platforms[i] != NULL) {
            int compare = station->platforms[i]->locomotive_power -
                            train_cars_weight(station->platforms[i]->train_cars);
            if ((compare < min) && (compare > 0)) {
                min = compare;
                gate = i;
            }
        }
    }
    return gate;
}


/* Gaseste trenul cu incarcatura nedistribuita bine.
 * 
 * station: gara existenta
 * cars_no: lungimea secventei de vagoane
 *
 * return: peronul pe care se afla trenul
 */
int find_heaviest_sequence_train(TrainStation *station, int cars_no, TrainCar **start_car) {
    *(start_car) = NULL;
    int max = 0, pos_to_return = -1;
    
    for(int i = 0; i < station->platforms_no; i++) {
        // Error check
        if (station->platforms[i] != NULL && station->platforms[i]->train_cars != NULL) {
            if (length_car(station->platforms[i]->train_cars) >= cars_no && cars_no > 0) {
                // Traveling car by car troughout the train
                TrainCar *moving_pointer = station->platforms[i]->train_cars;
                int length = length_car(station->platforms[i]->train_cars);
                // Train parse
                for (int j = 0; j < (length - cars_no + 1); j++) {
                    int k = 1, weight = 0;
                    TrainCar *aux = moving_pointer; 
                    // Sequence check
                    while (aux != NULL) {
                        weight += aux->weight;
                        if (k == cars_no) {
                            break;
                        }
                        k++;
                        aux = aux->next;
                    }
                    // The heaviest sequence
                    if (weight > max) {
                        max = weight;
                        pos_to_return = i;
                        *(start_car) = moving_pointer;
                    }
                    moving_pointer = moving_pointer->next;
                }
            }
        }
    }
    return pos_to_return;
}


/* Ordoneaza vagoanele dintr-un tren in ordinea descrescatoare a greutatilor.
 * 
 * station: gara existenta
 * platform: peronul pe care se afla trenul
 */
void order_train(TrainStation *station, int platform) {
    int to_do = 1;
    // Bubble sort train
    while (to_do) {
        TrainCar *aux = station->platforms[platform]->train_cars;
        to_do = 0;
        while (aux->next != NULL) {
            if (aux->weight < aux->next->weight) { 
                to_do = 1;
                int temp = aux->next->weight;
                aux->next->weight = aux->weight;
                aux->weight = temp;
            }
            aux = aux->next;
        }
    }
}


/* Scoate un vagon din trenul supraincarcat.
 * 
 * station: gara existenta
 */
void fix_overload_train(TrainStation *station) {
    // Overload train find;
    int pos = find_overload_train(station);
    if (pos < 0) return;
    // Creating secondary station (copy train for possiblity check)
    TrainStation *im_station = open_train_station(length_car(station->platforms[pos]->train_cars));
    for (int i = 0; i < length_car(station->platforms[pos]->train_cars); i++) {
        arrive_train(im_station, i, station->platforms[pos]->locomotive_power);
        TrainCar *aux = station->platforms[pos]->train_cars;
        while(aux != NULL) {
            add_train_car(im_station, i, aux->weight);
            aux = aux->next;
        }
    }
    // Remove a train car for every case 
    TrainCar *aux = station->platforms[pos]->train_cars;
    for (int i = 0; i < length_car(station->platforms[pos]->train_cars); i++) {
        remove_train_cars(im_station,i,aux->weight);
        aux = aux->next;
    }
    // Checking the train that has the most optimal weight
    int max = 0;
    for (int i = 0; i < im_station->platforms_no; i++) {
        if ((train_cars_weight(im_station->platforms[i]->train_cars) <= im_station->platforms[i]->locomotive_power) &&
        (train_cars_weight(im_station->platforms[i]->train_cars) > max)) {
            max = train_cars_weight(im_station->platforms[i]->train_cars);
            
            aux = im_station->platforms[i]->train_cars;
            im_station->platforms[i]->train_cars = station->platforms[pos]->train_cars;
            station->platforms[pos]->train_cars = aux;
        }
    }
    close_train_station(im_station);
    return;
}
