unsigned short crossPopulation(INDIVIDUAL * ppltn, INDIVIDUAL * newPpltn, unsigned short **Crosstable, unsigned short * newInds );
void crossInds(unsigned short * row, INDIVIDUAL * ppltn, INDIVIDUAL * newPpltn);
void copyPpltn(INDIVIDUAL * ppltn1, INDIVIDUAL * ppltn2);

unsigned short crossPopulation(INDIVIDUAL * ppltn, INDIVIDUAL * newPpltn, unsigned short **Crosstable, unsigned short * newInds) {
  unsigned short count = 0, i;
  int j;

  copyPpltn(ppltn, newPpltn);
  //printf("Population copied to newPpltn\n");

  for(i=0; i<NIND/2; i++) {
    if(rand()/(double)RAND_MAX <= CROSSPROB) {
      newInds[count] = Crosstable[i][0];
      newInds[count+1] = Crosstable[i][1];
      count+=2;
      crossInds(Crosstable[i], ppltn, newPpltn);
    }
  } //printf("Population crossed, saved into newPpltn\n");
  copyPpltn(newPpltn, ppltn);
  //printf("new Population copied to ppltn\n");
  return count;
}

void crossInds(unsigned short * row, INDIVIDUAL * ppltn, INDIVIDUAL * newPpltn) {
  unsigned short Px = (rand()/(double)RAND_MAX)*((ppltn[0].ncbits-2)-2)+2;
  unsigned short i;

  for(i=0; i<Px; i++) {
    newPpltn[row[0]].chromosome[i] = ppltn[row[0]].chromosome[i];
    newPpltn[row[1]].chromosome[i] = ppltn[row[1]].chromosome[i];
  }
  for(i=Px; i<ppltn[0].ncbits; i++) {
    newPpltn[row[0]].chromosome[i] = ppltn[row[1]].chromosome[i];
    newPpltn[row[1]].chromosome[i] = ppltn[row[0]].chromosome[i];
  }
}

void copyPpltn(INDIVIDUAL * ppltn1, INDIVIDUAL * ppltn2) {
  unsigned short i, j;

  for(i=0 ; i<NIND; i++) {
    for(j=0; j<ppltn1[0].ncbits; j++) {
      ppltn2[i].chromosome[j] = ppltn1[i].chromosome[j];
    }
  }
}
