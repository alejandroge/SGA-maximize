unsigned char initPopulation(INDIVIDUAL * ppltn); // Iterates over each Individual in the population
INDIVIDUAL * allocPopulation();                   // Allocate each Individual in the population
void showPopulation(INDIVIDUAL * ppltn);

unsigned char initPopulation(INDIVIDUAL * ppltn) {
  unsigned short i;

  for(i=0; i<NIND; i++) {
    if( initIndividual(ppltn+i) == 1 ) {
      printf("Cannot initialize Individual n. %u\n", i);
      return 1;
    }
  } // printf("Population initialized\n");

  return 0;
}

INDIVIDUAL * allocPopulation() {
  unsigned short i;
  INDIVIDUAL *ppltn;
  ppltn = (INDIVIDUAL*)malloc(NIND*sizeof(INDIVIDUAL));

  // Allocate bitsPerGene and Genes arrays for each individual
  for(i=0; i<NIND; i++) {
    (ppltn+i)->gene = (unsigned char **)malloc(NPARAMS*sizeof(unsigned char*));
    (ppltn+i)->bitsPerGene = (unsigned short*)malloc(NPARAMS*sizeof(unsigned short));
    (ppltn+i)->value = (double *)malloc(NPARAMS*sizeof(double));

    if((ppltn+i)->gene == NULL || (ppltn+i)->bitsPerGene == NULL || (ppltn+i)->value == NULL){
      printf("Failed trying to allocate memory for Genes and bitsPerGene arrays\n");
      return NULL;
    }
  } // printf("Population allocated\n");

  return ppltn;
}

void showPopulation(INDIVIDUAL * ppltn) {
  unsigned short i;

  for(i=0; i<NIND; i++) {
    showChromosome(ppltn+i);
    printf("\tIndividual %u\n", i+1);
    showGenes(ppltn+i);
    showFitness(ppltn+i);
  }
}
