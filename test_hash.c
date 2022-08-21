/*
    - XXX Debug 
    - XXX Länka olika filer
    - Cmake
    - XXX Build configurations
*/

/*  Idéer till TODO
    - Ordentlig free
    - Hasha olika nycklar, strängar?
    - Copy, move
    - Dynamic resize (hitta bra occupancy för när detta ska göras),
    - Timade test, jämföra med färdiga implementationer.s
    - X Ta bort objekt från listan
*/

#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"

// Test the distribution of the hash function.
// Changing one bit of the input should change 50% of the bits in the output.
// The distributions of bits should be be 50-50.
void test_hash(){

  int* cnt_bit_scewness = calloc(32, sizeof(int));
  double avg_bit_diff = 0;
  int num_values = 10000;
  for(int i = 0;i < num_values; i++){
    unsigned int x = rand();
    unsigned int rand_bit = 0b1 << rand()%31;
    
    //Flip the bit in postion rand_bit
    unsigned int x_mod = (x & ~rand_bit) | ~(x & rand_bit);

    unsigned int x_hashed = hash(x);
    unsigned int x_mod_hashed = hash(x_mod);

    //Count bit distributions in x and how many bits have changed
    int bit_diff = 0;
    for(int b = 0; b<32; b++){
      if((x_hashed & 0b1<<b) ^ (x_mod_hashed & 0b1<<b)){
        bit_diff++;
      }
      if(x_hashed & 0b1<<b)
        cnt_bit_scewness[b]++;
      else
        cnt_bit_scewness[b]--;
    }
    avg_bit_diff+=bit_diff;

  }

  avg_bit_diff = avg_bit_diff/num_values;
  printf("The average bit difference is %f\n", avg_bit_diff);
  printf("The bit scewness is [");
  double bit_scewness = 0;
  for(int b = 0; b<32; b++){
    if(b!=31)
      printf("%d, ", cnt_bit_scewness[b]);
    else
      printf("%d]\n", cnt_bit_scewness[b]);
    bit_scewness+=cnt_bit_scewness[b];
  }
  bit_scewness = bit_scewness/32.;
  printf("Average bit scewness %f\n", bit_scewness);

  free(cnt_bit_scewness);
}

void test_operators(){
  printf("%x", 1<<3);
  const int x = 0b110 ^ 0b101; // 0b011, ^ is XOR
  const int y = 0b110 & 0b101; // 0b100, & is AND
  const int z = 0b110 | 0b101; // 0b111, | is OR
  const unsigned int a = ~0b110;  // ~ seems to invert  

}

void test_sizes(){
  int x = 0;
  printf("An int is %d bytes long\n", sizeof(x));
  printf("A pointer is %d bytes long\n", sizeof(&x));
}

void test_hashmap(){
  srand(2);
  struct HashMap map = hash_map(1024);
  int save_vals[2000]; 

  for(unsigned int i = 0; i<2000; i++){
    int* val = malloc(sizeof(int));
    *val = rand();
    hm_add(i, val, map);
    save_vals[i] = *val;
  }

  int false_negatives = 0;
  int nulls = 0; 
  for(unsigned int i = 0; i<2000; i++){
    int* val = hm_get(i,map);
    if(val != NULL){
      if(*val != save_vals[i]){
        false_negatives++;
      }
    }else{
      nulls++;
    }
  }

  printf("%d entries.\n",*map.num_entries);
  
  for(unsigned int i = 0; i<500; i++){
    hm_remove(2000-i,map);
  }

  for(unsigned int i = 50; i<2000; i++){
    hm_remove(i,map);
  }

  hm_print(map);

  printf("%d false negatives, %d nulls when using actual keys.\n", false_negatives, nulls);
  printf("%d entries, size %d.\n",*map.num_entries, map.size);
  hm_free(map);
}

int main() {
  test_hashmap();
}
