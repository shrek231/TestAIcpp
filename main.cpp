#include <iostream>
#include <valarray>
struct AI {
    int INneurons[5-1];
    int IN_L1weight[50*5-1]; //INneurons * L1Nneurons
    int L1Nneurons[50-1];
    int L1_L2weight[50*50-1]; //L1Nneurons * L2Nneurons
    int L2Nneurons[50-1];
    int L2_OPweight[50*5-1]; //L2Nneurons * OPNneurons
    int OPNneurons[5-1];
    int Train(int trainLoops,int weghtLoops){//train loops is how many times it trains, weght loops is how many times it remakes the weghts after all the train loops, set to 0 by default, should output is what it should output
        int ShouldOutput[5-1];
        int OPcost[trainLoops];
        int L1_L2cost[trainLoops];
        int AvrCost[weghtLoops];
        int IN_L1cost[weghtLoops];
        for (int wl = 0;wl != weghtLoops;wl++) {
            //set weghts
            for (int i = 0; i != trainLoops; i++) {
                //set ShouldOutput to what it should output

                //set inputs and run the AI

                GetOutp();
                //calc cost
                for (int outp = 0; outp <= 5 - 1; outp++) {
                    OPcost[trainLoops - 5 - 1 + outp] += pow(OPNneurons[outp] - ShouldOutput[outp], 2);//trainLoops - 4 becuse 5 outputs
                    L1_L2cost[trainLoops - 2500 - 1 - 5 - 1 + outp] += pow(L2Nneurons[outp] - ShouldOutput[outp], 2);
                    IN_L1cost[trainLoops - 2500 - 1 - 2500 - 1 - 5 - 1 + outp] += pow(L1Nneurons[outp] - ShouldOutput[outp], 2);
                }
                //backwards propagation on output
                for (int i = 0;i <= 50*5-1 ;i++){
                    int BPGbias = 4;
                    if (OPcost[trainLoops - 4 + i] >= BPGbias){
                        L2_OPweight[i] *= .25;
                    }
                }//backwards propagation on layer 2 neurons
                for (int i = 0;i <= 50*50-1 ;i++){
                    int BPGbias = 4;
                    if (L1_L2cost[trainLoops - 4 + i] >= BPGbias){
                        L1_L2weight[i] *= .25;
                    }
                }//backwards propagation on layer 1 neurons
                for (int i = 0;i <= 50*50-1 ;i++){
                    int BPGbias = 4;
                    if (IN_L1cost[trainLoops - 4 + i] >= BPGbias){
                        IN_L1weight[i] *= .25;
                    }
                }
            }
            //calc advrage cost and graph it with the weghtLoops variable mabey
            int addedCost = 0;
            for (int i = 0;i != trainLoops;i++) {
                addedCost += OPcost[i];
                addedCost += L1_L2cost[i];
                addedCost += IN_L1cost[i];
            } AvrCost[wl] = addedCost / trainLoops * 2 + 8;
            //save weghts;
        }
        //save best weghts
    }
    int GetOutp(){ //loop the function
        int AllLoops = 0;
        //calculate Neurons values
        for(int inW = 0;inW <= 50*50-1;inW++){
            for (int connectEachN = 0;connectEachN <= 50-1;connectEachN++){
                AllLoops++;
                L1Nneurons[inW] = 1 / (1 + std::exp(-INneurons[connectEachN]*IN_L1weight[connectEachN] - 10));//bias 10
            }
        }
        printf("%d%s\n",AllLoops/262500*100,"%"); //262500 is the max amount of loops
        for(int l1W = 0;l1W <= 50*50-1;l1W++){
            for (int connectEachN = 0;connectEachN <= 50-1;connectEachN++){
                AllLoops++;
                L2Nneurons[l1W] = 1 / (1 + std::exp(-L1Nneurons[connectEachN]*L1_L2weight[connectEachN] - 10));
            }
        }
        printf("%d%s\n",AllLoops/262500*100,"%");
        for(int l2W = 0;l2W <= 50*5-1;l2W++){
            for (int connectEachN = 0;connectEachN <= 50-1;connectEachN++){
                AllLoops++;
                OPNneurons[l2W] = 1 / (1 + std::exp(-L2Nneurons[connectEachN]*L2_OPweight[connectEachN] - 10));
            }
        }
        printf("%d%s\n",AllLoops/262500*100,"%");
    }
};
int main() {
    AI* ai = new AI;
    ai->Train(50,0);
    return 0;
}
