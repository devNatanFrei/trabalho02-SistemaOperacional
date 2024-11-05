#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_FRAMES 8
#define K 5 

typedef struct {
    int mBit;       
    int rBit;       
    int lastTime;   
    int pageNum;    
} PageFrame;

int pointer = 0;  
PageFrame memory[NUM_FRAMES];  

void initMemory() {
    for (int i = 0; i < NUM_FRAMES; i++) {
        memory[i].mBit = 0;
        memory[i].rBit = 0;
        memory[i].lastTime = 0;
        memory[i].pageNum = -1; 
    }
}

void updateMemory(int pageNum, int time) {
    int found = 0;

   
    for (int i = 0; i < NUM_FRAMES; i++) {
        if (memory[i].pageNum == pageNum) {
            memory[i].rBit = 1; 
            memory[i].lastTime = time;
            found = 1;
            printf("Pagina %d ja esta na memoria\n", pageNum);
            return;
        }
    }

    if (!found) {

        int start = pointer;
        while (1) {
            PageFrame *frame = &memory[pointer];

   
            if (frame->rBit == 1) {
                frame->rBit = 0; 
                pointer = (pointer + 1) % NUM_FRAMES; 
            }
         
            else if (time - frame->lastTime > K) {
                if (frame->mBit == 1) {
               
                    printf("Escrevendo pagina %d de volta para o disco\n", frame->pageNum);
                }
                printf("Substituindo pagina %d por %d\n", frame->pageNum, pageNum);
                frame->pageNum = pageNum;
                frame->mBit = rand() % 2;
                frame->rBit = 1;
                frame->lastTime = time;
                pointer = (pointer + 1) % NUM_FRAMES; 
                break;
            }
           
            pointer = (pointer + 1) % NUM_FRAMES;

       
            if (pointer == start) {
                printf("Nenhuma pagina fora do conjunto de trabalho substituindo pagina %d\n", memory[pointer].pageNum);
                memory[pointer].pageNum = pageNum;
                memory[pointer].mBit = rand() % 2;
                memory[pointer].rBit = 1;
                memory[pointer].lastTime = time;
                pointer = (pointer + 1) % NUM_FRAMES;
                break;
            }
        }
    }
}

int main() {
    initMemory();

    int pageReferences[] = {0, 1, 1, 2, 3, 0, 4, 1, 2, 5, 3, 4, 6};
    int numReferences = sizeof(pageReferences) / sizeof(pageReferences[0]);
    int time = 0;

    for (int i = 0; i < numReferences; i++) {
        time++;
        updateMemory(pageReferences[i], time);
    }

    printf("\nEstado da memoria apos as referencias\n");
    for (int i = 0; i < NUM_FRAMES; i++) {
        printf("Memory %d Page = %d mBit = %d rBit = %d lastTime = %d\n", 
                i, memory[i].pageNum, memory[i].mBit, memory[i].rBit, memory[i].lastTime);
    }

    return 0;
}
