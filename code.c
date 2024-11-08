#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_FRAMES 3
#define K 5 

typedef struct {
    int mBit;
    int rBit;
    int lastTime;
    int pageNum;
} PageFrame;

int pont = 0;
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
        int start = pont;
        bool r = false;

        while (pont != start) {
            PageFrame *frame = &memory[pont];

            if (frame->rBit == 0 && (time - frame->lastTime > K)) {
                if (frame->mBit == 1) {
                    printf("Escrevendo pagina %d de volta para o disco\n", frame->pageNum);
                }
                printf("Substituindo pagina %d por %d\n", frame->pageNum, pageNum);
                frame->pageNum = pageNum;
                frame->mBit = rand() % 2;
                frame->rBit = 1;
                frame->lastTime = time;
                pont = (pont + 1) % NUM_FRAMES;
                r = true;
                break;
            } else if (frame->rBit == 1) {
                frame->rBit = 0;
            }

            pont = (pont + 1) % NUM_FRAMES;
        } 

        if (!r) {
            PageFrame *frame = &memory[pont];
            if (frame->mBit == 1) {
                printf("Escrevendo pagina %d de volta para o disco\n", frame->pageNum);
            }
            printf("Substituindo pagina %d por %d\n", frame->pageNum, pageNum);
            frame->pageNum = pageNum;
            frame->mBit = rand() % 2;
            frame->rBit = 1;
            frame->lastTime = time;
            pont = (pont + 1) % NUM_FRAMES;
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
        
        printf("Estado da memoria apos referencia %d: ", pageReferences[i]);
        for (int j = 0; j < NUM_FRAMES; j++) {
            if (memory[j].pageNum == -1)
                printf("[ - ] ");
            else
                printf("[ %d | bit r:%d ] ", memory[j].pageNum, memory[j].rBit);
        }
        printf("\n");
    }

    return 0;
}
