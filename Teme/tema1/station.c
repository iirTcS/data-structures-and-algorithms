#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "station.h"


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
    station->platforms[platform] = NULL; // Fii atent la intoarcerea null dupa alocare (posibila eroare)
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
            }
        }
        aux = aux->next;
    }
    return;
}

//--------------------------------------------------------------- Okay pana aici


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
}


/* Gaseste trenul cel mai rapid.
 * 
 * station: gara existenta
 *
 * return: peronul pe care se afla trenul
 */
int find_express_train(TrainStation *station) {
    return -1;
}


/* Gaseste trenul supraincarcat.
 * 
 * station: gara existenta
 *
 * return: peronul pe care se afla trenul
 */
int find_overload_train(TrainStation *station) {
    return -1;
}


/* Gaseste trenul cu incarcatura optima.
 * 
 * station: gara existenta
 *
 * return: peronul pe care se afla trenul
 */
int find_optimal_train(TrainStation *station) {
    return -1;
}


/* Gaseste trenul cu incarcatura nedistribuita bine.
 * 
 * station: gara existenta
 * cars_no: lungimea secventei de vagoane
 *
 * return: peronul pe care se afla trenul
 */
int find_heaviest_sequence_train(TrainStation *station, int cars_no, TrainCar **start_car) {
    return -1;
}


/* Ordoneaza vagoanele dintr-un tren in ordinea descrescatoare a greutatilor.
 * 
 * station: gara existenta
 * platform: peronul pe care se afla trenul
 */
void order_train(TrainStation *station, int platform) {
}


/* Scoate un vagon din trenul supraincarcat.
 * 
 * station: gara existenta
 */
void fix_overload_train(TrainStation *station) {
}
