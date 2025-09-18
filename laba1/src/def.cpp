#include "../include/def.h"


int SearchN(int devider,int bound){
    if ((bound > 0) && (devider != 0)){
        for (int i = bound; i > 0; i--){
            if ((i % devider == 0)){
                return i;
            }
        }
    }
    return 0;

}