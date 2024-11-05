#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_FRAMES 3    
#define K 4            

typedef struct {
    int pageNum;
    int rBit;
    int mBit;    
    int time;   
} PageFrame;

int main() {
    PageFrame memory[NUM_FRAMES];
    int pageReferences[] = {0, 1, 1, 2, 3, 0, 4, 1, 2, 5, 3, 4, 6}; 
    int numReferences = sizeof(pageReferences) / sizeof(pageReferences[0]);
    int t, k;  
        

    
    for (int i = 0; i < NUM_FRAMES; i++) {
        memory[i].pageNum = -1; 
        memory[i].rBit = 0;
        memory[i].mBit = 0; 
        memory[i].time = -1; 
    }

    
    for (int i = 0; i < numReferences; i++) {
        int pageReferenced = pageReferences[i];
        bool pageFound = false;


        t++;

        
        for (int j = 0; j < NUM_FRAMES; j++) {
            if (memory[j].pageNum == pageReferenced) {
                memory[j].rBit = 1; 
                memory[j].time = t; 
                pageFound = true;
                printf("Página %d já está referenciada na memória\n", pageReferenced);
                break;
            }
        }

 
        if (!pageFound) {
     
            while (1) {
                if (memory[k].rBit == 0 &&  (t - memory[k].time) > K) {
               
                    if (memory[k].mBit == 1) {
                        printf("Escrevendo página %d de volta ao disco\n", memory[k].pageNum);
                    }
                   
                    printf("Substituiu página %d\n", memory[k].pageNum);
                    memory[k].pageNum = pageReferenced;
                    memory[k].rBit = 1;
                    memory[k].mBit = 0; 
                    memory[k].time = t;
                    break;
                } else {
            
                    memory[k].rBit = 0;
                }
                
                
                k = (k + 1) % NUM_FRAMES;
            }
        }

      
        if (pageReferenced == memory[k].pageNum) {
            memory[k].mBit = 1; 
        }

       
        printf("Estado da memória após referência %d: ", pageReferenced);
        for (int j = 0; j < NUM_FRAMES; j++) {
            if (memory[j].pageNum == -1)
                printf("[ - ] ");
            else
                printf("[ %d ] ", memory[j].pageNum);
        }
        printf("\n");
    }

    return 0;
}
