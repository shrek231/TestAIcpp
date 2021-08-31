#include <iostream>
#include <valarray>
struct AI {
    int INneurons[50-1];
    int IN_L1weight[50*50-1]; //INneurons * L1Nneurons
    int L1Nneurons[50-1];
    int L1_L2weight[50*50-1]; //L1Nneurons * L2Nneurons
    int L2Nneurons[50-1];
    int L2_OPweight[50*5-1]; //L2Nneurons * OPNneurons
    int OPNneurons[5-1];
    int Train(int ShouldOutput[5-1],int trainLoops,int weghtLoops){//train loops is how many times it trains, weght loops is how many times it remakes the weghts after all the train loops, set to 0 by default, should output is what it should output
        int OPcost[trainLoops];
        int AvrCost[weghtLoops];
        for (int wl = 0;wl != weghtLoops;wl++) {
            //set weghts
            for (int i = 0; i != trainLoops; i++) {
                //set inputs and run the AI

                //calc cost
                for (int outp = 0; outp <= 5 - 1; outp++) {
                    OPcost[trainLoops - 4 + outp] += pow(OPNneurons[outp] - ShouldOutput[outp], 2);
                }
                //backwards propagation on output
                for (int i = 0;i <= 50*5-1 ;i++){
                    
                }
            }
            //calc advrage cost and graph it with the weghtLoops variable mabey
            int addedCost = 0;
            for (int i = 0;i != trainLoops;i++) {
                addedCost += OPcost[i];

            } AvrCost[wl] = addedCost / trainLoops;
        }
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
    return 0;
}
