#include <iostream>
#include <valarray>
struct AI {
    int INneurons[5];
    int IN_L1weight[50*5]; //INneurons * L1Nneurons
    int L1Nneurons[50];
    int L1_L2weight[50*50]; //L1Nneurons * L2Nneurons
    int L2Nneurons[50];
    int L2_OPweight[50*5]; //L2Nneurons * OPNneurons
    int OPNneurons[5];
    int Train(int trainLoops,int weghtLoops){//train loops is how many times it trains, weght loops is how many times it remakes the weghts after all the train loops, set to 1 by default\786
        printf("Training Started\n");
        int ShouldOutput[5];
        int OPcost[50*5];
        int L1_L2cost[50*50];
        int AvrCost[weghtLoops];
        int IN_L1cost[50*5];
        for (int wl = 0;wl <= weghtLoops - 1;wl++) {
            //set weghts 0,10 becuse 10 is our bias
            for(int RandW = 0; RandW <= 50*5+50*50+50*5-1; RandW++){
                IN_L1weight[RandW] = rand() % 10;
                L1_L2weight[RandW] = rand() % 10;
                L2_OPweight[RandW] = rand() % 10;
            }
            for (int i = 0; i <= trainLoops - 1; i++) {
                float R = (rand() % 5)/5;
                //set ShouldOutput to what it should output
                ShouldOutput[(int)R*5] = R;
                //set inputs and run the AI
                INneurons[(int)R*5] = R;
                GetOutp();
                //calc cost
                //printf("Calculating cost\n");
                for (int outp = 0; outp <= 5-1; outp++) {
                    OPcost[ i + outp] += pow(OPNneurons[outp] - ShouldOutput[outp], 2);//trainLoops - 4 becuse 5 outputs
                    L1_L2cost[i + outp] += pow(L2Nneurons[outp] - ShouldOutput[outp], 2);
                    IN_L1cost[i + outp] += pow(L1Nneurons[outp] - ShouldOutput[outp], 2);
                }//backwards propagation on output
                int BPGbias = 4;
                //printf("backwards propagation on output\n");
                for (int i_ = 0;i_ <= 50*5-1 ;i_++){
                    if (OPcost[i_] >= BPGbias){
                        L2_OPweight[i_] *= .25;
                    } else {
                        L2_OPweight[i_] *= -.25;
                    }
                }//backwards propagation on layer 2 neurons
                //printf("backwards propagation on layer 2 neurons\n");
                for (int i__ = 0;i__ <= 50*50-1 ;i__++){
                    if (L1_L2cost[i__] >= BPGbias){
                        L1_L2weight[i__] *= .25;
                    } else {
                        L1_L2weight[i__] *= -.25;
                    }
                }//backwards propagation on layer 1 neurons
                //printf("backwards propagation on layer 1 neurons\n");
                for (int i___ = 0;i___ <= 50*5-1 ;i___++){
                    if (IN_L1cost[i___] >= BPGbias){
                        IN_L1weight[i___] *= .25;
                    } else {
                        IN_L1weight[i___] *= -.25;
                    }
                }
                long percent = i/trainLoops*100;
                printf("Training: %d%s\n",percent,"% ");
            }
            //calc advrage cost and graph it with the weghtLoops variable mabey
            printf("Calculating adv cost\n");
            long addedCost = 0;
            long Loops = 0;
            for (int i_ = 0;i_ <= 50*5+trainLoops-1;i_++) {
                Loops++;
                addedCost += IN_L1cost[i_];
            }for (int i_ = 0;i_ <= 50*50+trainLoops-1;i_++) {
                Loops++;
                addedCost += L1_L2cost[i_];
            }for (int i_ = 0;i_ <= 50*5+trainLoops-1;i_++) {
                Loops++;
                addedCost += OPcost[i_];
            } AvrCost[wl] = addedCost / Loops;
            printf("Averages added %d\n",addedCost);
            printf("Average Cost %d\n",AvrCost[0]);
            //save weghts;
        }
        //save best weghts
        printf("Finished Training\n");
    }
    int GetOutp(){ //loop the function
        //calculate Neurons values
        //printf("Starting\n");
        for(int inW = 0;inW <= 50*5-1;inW++){
            for (int connectEachN = 0;connectEachN <= 50*5-1;connectEachN++){
                L1Nneurons[inW] = 1 / (1 + std::exp(-INneurons[connectEachN]*IN_L1weight[connectEachN] - 10));//bias 10
            }
        }
        //printf("Got Output L1\n");
        for(int l1W = 0;l1W <= 50*50-1;l1W++){
            for (int connectEachN = 0;connectEachN <= 50*50-1;connectEachN++){
                L2Nneurons[l1W] = 1 / (1 + std::exp(-L1Nneurons[connectEachN]*L1_L2weight[connectEachN] - 10));
            }
        }
        //printf("Got Output L2\n");
        for(int l2W = 0;l2W <= 50*5-1;l2W++){
            for (int connectEachN = 0;connectEachN <= 50*5-1;connectEachN++){
                OPNneurons[l2W] = 1 / (1 + std::exp(-L2Nneurons[connectEachN]*L2_OPweight[connectEachN] - 10));
            }
        }
        //printf("Got Output\n");
    }
};
int main() {
    AI* ai = new AI;
    ai->Train(50,1);
    printf("Done\n");
    return 0;
}
