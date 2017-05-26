void MutatePopulation(INDIVIDUAL * ppltn, unsigned short * newInds, unsigned short nCrossed);
void Mutation(INDIVIDUAL * ind);

void MutatePopulation(INDIVIDUAL * ppltn, unsigned short * newInds, unsigned short nCrossed) {
  unsigned short i;

  for(i=0; i<nCrossed; i++) {
    Mutation(ppltn+newInds[i]);
  }
}

void Mutation(INDIVIDUAL * ind) {
  unsigned short i;

  for(i=0; i<ind->ncbits; i++) {
    if( rand()/(double)RAND_MAX <= P_MUTATION) {
      ind->chromosome[i] = (ind->chromosome[i])? 0 : 1 ;
    }
  }
}
