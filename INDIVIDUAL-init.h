typedef struct {
  unsigned char * chromosome;   // The whole genetic information
  unsigned short ncbits;        // Total number of bits in chromosome
  unsigned short * bitsPerGene; // bitsPerGene, it can be different for each gene
  unsigned char ** gene;        // array of pointers to the beginning of each gene
  double * value;               // array of real values for each gene
  double fitness;               // result of the evaluation of the function for the ind
}INDIVIDUAL;

///////////////////// Functions declarations
unsigned char initIndividual(INDIVIDUAL * ind);
INDIVIDUAL * allocIndividual();
void initBitsPerGene(INDIVIDUAL * ind);
void showGenesSize(INDIVIDUAL * ind);
unsigned char * allocChromosome(unsigned short ncbits);
void initChromosome(INDIVIDUAL * ind);
void showChromosome(INDIVIDUAL * ind);
void initGenes(INDIVIDUAL * ind);
void computeRealValues(INDIVIDUAL * ind);
unsigned int binaryPower(unsigned short n);
void showGenes(INDIVIDUAL * ind);
void showFitness(INDIVIDUAL * ind);

///////////////////// Functions implementations
unsigned char initIndividual(INDIVIDUAL * ind) {
  unsigned short i;
  ind->ncbits = 0;

  initBitsPerGene(ind);
  // showGenesSize(ind);

  ind->chromosome = allocChromosome(ind->ncbits);
  if(ind->chromosome == NULL) return 1;
  initChromosome(ind);
  //showChromosome(ind);

  initGenes(ind);
  //showGenes(ind);

  ind->fitness = 0;
  return 0;
}

INDIVIDUAL * allocIndividual() {
  INDIVIDUAL *ind;
  ind = (INDIVIDUAL*)malloc(sizeof(INDIVIDUAL));
  // Allocate bitsPerGene and Genes arrays
  ind->gene = (unsigned char **)malloc(NPARAMS*sizeof(unsigned char*));
  ind->bitsPerGene = (unsigned short*)malloc(NPARAMS*sizeof(unsigned short));
  ind->value = (double *)malloc(NPARAMS*sizeof(double));

  if(ind->gene == NULL || ind->bitsPerGene == NULL || ind->value == NULL){
    printf("Failed trying to allocate memory for Genes and bitsPerGene arrays\n");
    return NULL;
  } // printf("Individual allocated\n");

  return ind;
}

void initBitsPerGene(INDIVIDUAL * ind) {
  unsigned short i;

  // Initialize bitsPerGene array, with the values from the const array
  // counts number of bits in the chromosome, saves it to ncbits
  for(i=0; i<NPARAMS; i++) {
    ind->bitsPerGene[i] = NBITS[i];
    ind->ncbits += NBITS[i];
  } // printf("bitsPerGene array initialized\n");
}

void showGenesSize(INDIVIDUAL * ind) {
  unsigned short i;

  for(i=0; i<NPARAMS; i++){
    printf("bitsPerGene[%u]= %u\n", i, ind->bitsPerGene[i]);
  }
}

unsigned char * allocChromosome(unsigned short ncbits) {
  unsigned char * chromosome;

  // Allocate the exact space needed for chromosome array
  chromosome = (unsigned char *)malloc(ncbits*sizeof(unsigned char));
  if(chromosome == NULL) {
    printf("Failed to allocate chromosome array\n");
  }
  return chromosome;
}

void initChromosome(INDIVIDUAL * ind) {
  unsigned short i;

  // Initialize randomly chromosome array
  for(i=0; i<ind->ncbits; i++) {
    ind->chromosome[i] = rand()/(double)RAND_MAX > 0.5 ? 1 : 0;
  } // printf("Chromosome randomly initialized\n");
}

void showChromosome(INDIVIDUAL * ind) {
  unsigned short i;

  for(i=0; i<ind->ncbits; i++){
    printf("%u", ind->chromosome[i]);
  } printf("\n");
}

void initGenes(INDIVIDUAL * ind) {
  unsigned short i, j;

  // Point array of pointers to head of genes in the chromosome
  for( i=0 , j=0 ; i < NPARAMS ; j += ind->bitsPerGene[i] , i++) {
    ind->gene[i] = ind->chromosome+j;
  } // printf("Genes initialized\n");
  computeRealValues(ind);
}

void computeRealValues(INDIVIDUAL * ind) {
  unsigned short i, j, k;
  unsigned int dValue;

  // Compute realValues for each gene
  for(i=0; i<NPARAMS; i++) {
    // Following for cycle converts raw binary to decimal values
    dValue = 0;
    for(j = ind->bitsPerGene[i]-1, k=0 ; k<ind->bitsPerGene[i]; j--, k++) {
      if( ind->gene[i][j] == 1) dValue += binaryPower(k);
    }
    // Real Value its compute based on lower and upper limits, and decimal value
    ind->value[i] = ((double)dValue/binaryPower(ind->bitsPerGene[i])*RANGE)+LLIMIT;
  }
}

unsigned int binaryPower(unsigned short n) {
  if(n == 0) return 1;
  else return 2*binaryPower(n-1);
}

void showGenes(INDIVIDUAL * ind) {
  unsigned short i, j;

  for( i=0 ; i < NPARAMS ; i++ ) {
    printf("Gene[%u] = ", i);
    for( j=0 ; j < ind->bitsPerGene[i] ; j++) {
      printf("%u", ind->gene[i][j]);
    } printf("\tReal Value = %g\n", ind->value[i]);
  }
}

void showFitness(INDIVIDUAL * ind) {
  printf("Fitness: %g\n", ind->fitness);
}
