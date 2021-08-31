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
        for (int wl = 0;wl != weghtLoops;wl++) {
            //set weghts
            for (int i = 0; i != trainLoops; i++) {
                //set ShouldOutput to what it should output

                //set inputs and run the AI

                GetOutp();
                //calc cost
                printf("Calculating cost\n");
                for (int outp = 0; outp <= 4; outp++) {
                    OPcost[ i + outp] += pow(OPNneurons[outp] - ShouldOutput[outp], 2);//trainLoops - 4 becuse 5 outputs
                    L1_L2cost[i + outp] += pow(L2Nneurons[outp] - ShouldOutput[outp], 2);
                    IN_L1cost[i + outp] += pow(L1Nneurons[outp] - ShouldOutput[outp], 2);
                }//backwards propagation on output
                int BPGbias = 4;
                printf("backwards propagation on output\n");
                for (int i_ = 0;i_ <= 50*5-1 ;i_++){
                    if (OPcost[i_] >= BPGbias){
                        L2_OPweight[i_] *= .25;
                    }
                }//backwards propagation on layer 2 neurons
                printf("backwards propagation on layer 2 neurons\n");
                for (int i__ = 0;i__ <= 50*50-1 ;i__++){
                    if (L1_L2cost[i__] >= BPGbias){
                        L1_L2weight[i__] *= .25;
                    }
                }//backwards propagation on layer 1 neurons
                printf("backwards propagation on layer 1 neurons\n");
                for (int i___ = 0;i___ <= 50*5-1 ;i___++){
                    if (IN_L1cost[i___] >= BPGbias){
                        IN_L1weight[i___] *= .25;
                    }
                }
                int percent = i/trainLoops*100;
                printf("Training: %d%s\n",i,"%");
            }
            //calc advrage cost and graph it with the weghtLoops variable mabey
            int addedCost = 0;
            for (int i_ = 0;i_ != 50*5+50*50+50*5+trainLoops;i_++) {
                addedCost += OPcost[i_];
                addedCost += L1_L2cost[i_];
                addedCost += IN_L1cost[i_];
            } AvrCost[wl] = addedCost / trainLoops * 2 + 8;
            //save weghts;
        }
        //save best weghts
    }
    int GetOutp(){ //loop the function
        //calculate Neurons values
        for(int inW = 0;inW <= 50*5-1;inW++){
            for (int connectEachN = 0;connectEachN <= 50-1;connectEachN++){
                L1Nneurons[inW] = 1 / (1 + std::exp(-INneurons[connectEachN]*IN_L1weight[connectEachN] - 10));//bias 10
            }
        }
        for(int l1W = 0;l1W <= 50*50-1;l1W++){
            for (int connectEachN = 0;connectEachN <= 50-1;connectEachN++){
                L2Nneurons[l1W] = 1 / (1 + std::exp(-L1Nneurons[connectEachN]*L1_L2weight[connectEachN] - 10));
            }
        }
        for(int l2W = 0;l2W <= 50*5-1;l2W++){
            for (int connectEachN = 0;connectEachN <= 50-1;connectEachN++){
                OPNneurons[l2W] = 1 / (1 + std::exp(-L2Nneurons[connectEachN]*L2_OPweight[connectEachN] - 10));
            }
        }
    }
};
int main() {
    AI* ai = new AI;
    ai->Train(50,1);
    return 0;
}
