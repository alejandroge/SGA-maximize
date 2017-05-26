#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char FLAG = 0;
const unsigned short NPARAMS = 2;
const unsigned short NIND = 100;
const unsigned short NBITS[] = {10, 10};
const float P_MUTATION = 0.01;
const float CROSSPROB = 0.8;
#define LLIMIT -2.048
#define ULIMIT 2.048
double RANGE = ULIMIT - LLIMIT;
#define GLIMIT 100
#define ERROR 0.001

#include "INDIVIDUAL-init.h"
#include "POPULATION-init.h"
#include "POPULATION-eval.h"
#include "SELECTION.h"
#include "CROSSING.h"
#include "MUTATION.h"

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  INDIVIDUAL * ppltn, * newPpltn, * bestInd;
  unsigned short nGeneration = 1, i, nCrossed;
  unsigned short ** Crosstable, * newInds;
  int x, y;

  newInds = (unsigned short *)malloc(NIND*sizeof(unsigned short));

  ppltn = allocPopulation();
  newPpltn = allocPopulation();
  if(ppltn == NULL || newPpltn == NULL) return 1;

  // Initialize Population
  if( initPopulation(ppltn) == 1 || initPopulation(newPpltn) == 1){
    printf("Cannot initialize individual properly\n");
    return 1;
  }

  // EvaluatePopulation returns a pointer to the better individual of the population
  bestInd = EvaluatePopulation(ppltn);
  //showPopulation(ppltn);
  // Stop condition
  while(/*nGeneration < GLIMIT && */bestInd->fitness > ERROR) {

    Crosstable=rouletteSelection(ppltn, Crosstable);
    // printf("Cross table computed\n");
    nCrossed = crossPopulation(ppltn, newPpltn, Crosstable, newInds);
    // printf("Population crossed\n");
    MutatePopulation(ppltn, newInds, nCrossed);
    bestInd = EvaluatePopulation(ppltn);
    // showPopulation(ppltn);
    nGeneration++;

  }
  printf("\nBest Individual, generation %u\n", nGeneration-1);
  showGenes(bestInd);
  showFitness(bestInd);

  //showPopulation(ppltn);

  return 0;
}
