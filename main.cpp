#define SDL_MAIN_HANDLED
#include <iostream>
#include <valarray>
#include <SDL2/SDL.h>
#include <thread>
SDL_Renderer* rend;

struct AI {
    float INneurons[5];
    float IN_L1weight[50*5]; //INneurons * L1Nneurons
    float L1Nneurons[50];
    float L1_L2weight[50*50]; //L1Nneurons * L2Nneurons
    float L2Nneurons[50];
    float L2_OPweight[50*5]; //L2Nneurons * OPNneurons
    float OPNneurons[5];

    float ShouldOutput[5];
    float OPcost[5];
    float L1_L2cost[50];
    float IN_L1cost[5];
    int Train(int trainLoops,int weghtLoops){//train loops is how many times it trains, weght loops is how many times it remakes the weghts after all the train loops, set to 1 by default\786
        printf("Training Started\n");
        float AvrCost[weghtLoops];
        for (int wl = 0;wl <= weghtLoops - 1;wl++) {
            //set weghts 0,10 becuse 10 is our bias
            for(int RandW = 0; RandW <= 50*5-1; RandW++){
                IN_L1weight[RandW] = (float)(rand() % 20 - 10);
            }for(int RandW = 0; RandW <= 50*50-1; RandW++){
                L1_L2weight[RandW] = (float)(rand() % 20 - 10);
            }for(int RandW = 0; RandW <= 50*5-1; RandW++){
                L2_OPweight[RandW] = (float)(rand() % 20 - 10);
            }
            for (int i = 0; i <= trainLoops - 1; i++) {
                //set ShouldOutput to what it should output
                ShouldOutput[4] = 1;
                //set inputs and run the AI
                INneurons[4] = 1;
                GetOutp();
                //calc cost
                printf("Calculating cost\n");
                /*for (int outp = 0; outp <= 5-1; outp++) {
                    OPcost[outp] += pow(OPNneurons[outp] - ShouldOutput[outp], 2);
                }*/
                int w = 0;
                for (int opn = 0; opn <= 5 - 1; opn++,w++) {
                    for (int outp = 0; outp <= 5 - 1; outp++) {
                        OPcost[w] += (float)pow(OPNneurons[outp] - ShouldOutput[opn],2);
                    }
                }w = 0;
                for (int opn = 0; opn <= 5 -1; opn++,w++) {
                    for (int outp = 0; outp <= 50 - 1; outp++) {
                        L1_L2cost[w] += (float)pow(L2Nneurons[outp] - OPNneurons[opn],2);
                    }
                }w = 0;
                for (int opn = 0; opn <= 50 - 1; opn++,w++) {
                    for (int outp = 0; outp <= 50 - 1; outp++) {
                        IN_L1cost[w] += (float)pow(L1Nneurons[outp] - L2Nneurons[opn],2);
                    }
                }
                //backwards propagation on output
                printf("backwards propagation on output\n");
                for (int i_ = 0;i_ <= 50*5-1 ;i_++){
                    if (OPcost[i_] <= 3.5){ //if the cost is below 3.5, increase
                        L2_OPweight[i_] += .15;
                    } else {
                        L2_OPweight[i_] -= .15;
                    }
                }//backwards propagation on layer 2 neurons
                printf("backwards propagation on layer 2 neurons\n");
                for (int i__ = 0;i__ <= 50*50-1 ;i__++){
                    if (L1_L2cost[i__] <= 3.5){
                        L1_L2weight[i__] += .15;
                    } else {
                        L1_L2weight[i__] -= .15;
                    }
                }//backwards propagation on layer 1 neurons
                printf("backwards propagation on layer 1 neurons\n");
                for (int i___ = 0;i___ <= 50*5-1 ;i___++){
                    if (IN_L1cost[i___] <= 3.5){
                        IN_L1weight[i___] += .15;
                    } else {
                        IN_L1weight[i___] -= .15;
                    }
                }
                //calc advrage cost and graph it with the weghtLoops variable mabey
                printf("Calculating adv cost\n");
                float addedCost = 0;
                long Loops = 0;
                for (int i_ = 0;i_ <= 50*5+trainLoops-1;i_++) {
                    Loops++;
                    addedCost += (float)IN_L1cost[i_];
                }for (int i_ = 0;i_ <= 50*50+trainLoops-1;i_++) {
                    Loops++;
                    addedCost += (float)L1_L2cost[i_];
                }for (int i_ = 0;i_ <= 50*5+trainLoops-1;i_++) {
                    Loops++;
                    addedCost += (float)OPcost[i_];
                } AvrCost[wl] = addedCost / Loops;
                printf("Averages added %f\n",addedCost);
                printf("Average Cost %f\n",AvrCost[0]);
                float percent = (float)i/trainLoops*100;
                printf("Training: %f%s\n",percent,"% ");
                //reset
                for (int loop = 0; loop <= 50*5; loop++){
                    OPcost[loop] = 0;
                }for (int loop = 0; loop <= 50*50; loop++){
                    L1_L2cost[loop] = 0;
                }for (int loop = 0; loop <= 50*5; loop++){
                    IN_L1cost[loop] = 0;
                }
            }
            //save weghts
        }
        //save best weghts
        printf("Finished Training\n");
    }
    int GetOutp(){ //loop the function
        //calculate Neurons values
        //printf("Starting\n");
        int connectEachW = 0;
        for (int i = 0; i <= 5-1; i++) {
            for (int i_loop = 0; i_loop <= 50 - 1; i_loop++,connectEachW++) {
                L1Nneurons[i_loop] = 1 / (1 + std::exp(-INneurons[i] * IN_L1weight[connectEachW] - 10));//bias 10
            }
        }
        connectEachW = 0;
        for (int i = 0; i <= 5-1; i++) {
            for (int i_loop = 0; i_loop <= 50 - 1; i_loop++,connectEachW++) {
                L2Nneurons[i_loop] = 1 / (1 + std::exp(-L1Nneurons[i] * L1_L2weight[connectEachW] - 10));//bias 10
            }
        }
        connectEachW = 0;
        for (int i = 0; i <= 5-1; i++) {
            for (int i_loop = 0; i_loop <= 50 - 1; i_loop++,connectEachW++) {
                OPNneurons[i_loop] = 1 / (1 + std::exp(-L2Nneurons[i] * L2_OPweight[connectEachW] - 10));//bias 10
            }
        }
    }
};
SDL_Renderer* GLoop(){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("Ai Test", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, 300, 200, SDL_WINDOW_SHOWN);
    rend = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(rend, 155, 155, 155, 255);
    //Clear the renderer with the draw color
    SDL_RenderClear(rend);
    while (true){
        //update renderer
        SDL_RenderPresent(rend);
    }
}
int main(int argc, char *argv[]) {
    std::thread Graphics (GLoop);
    AI* ai = new AI;
    ai->Train(50,1);
    ai->INneurons[0] = 0;
    ai->INneurons[1] = 0;
    ai->INneurons[2] = 0;
    ai->INneurons[3] = 0;
    ai->INneurons[4] = 1; //10 is max on
    ai->GetOutp();
    for(int i = 0;i <= 4;i++){
        printf("%f\n",ai->OPNneurons[i]);
    }
    printf("Done\n");
    return 0;
}