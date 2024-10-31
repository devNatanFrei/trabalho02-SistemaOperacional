#include <stdio.h>
#include <stdlib.h>

#define NUM_FRAMES 8 


typedef struct {
    int mBit;   
    int rBit;    
    int time;   
} PageFrame;

int pont = 0;  
PageFrame memory[NUM_FRAMES];  


void verif(int mBit, int time) {
    int i = 0;

    while (i < NUM_FRAMES) {
        PageFrame *frame = &memory[pont];  

        if (frame->rBit == 1) {
            frame->rBit = 0;  
        } else if (frame->rBit == 0 && time > frame->time) {
                frame->mBit = mBit;
                frame->rBit = 1;
                frame->time = time;
                break;
            }
    
     pont = (pont + 1) % NUM_FRAMES;
        i++;

    
    }
         
}



void updateMemory(int mBit, int time) {
    verif(mBit, time);
}


void initMemory() {
    PageFrame list[NUM_FRAMES] = {
        {0, 0, 1620},
        {0, 1, 2032},
        {0, 1, 2020},
        {0, 1, 2014},
        {0, 0, 1213},
        {0, 1, 1980},
        {0, 1, 2003},
        {0, 1, 2084},
    };

    for (int i = 0; i < NUM_FRAMES; i++) {
        memory[i] = list[i];
    }
}


int main() {
    int mBit = 0;
 
    initMemory();
    
    updateMemory(mBit, 1216);
    updateMemory(mBit, 2204);

    for (int i = 0; i < NUM_FRAMES; i++) {
        printf("Memory %d: mBit = %d, rBit = %d, time = %d\n", i, memory[i].mBit, memory[i].rBit, memory[i].time);
    }

    return 0;
}
