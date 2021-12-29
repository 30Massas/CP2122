//Bucket sort in C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

//#define NARRAY 10   // Array size
//#define NBUCKET 5  // Number of buckets
#define INTERVAL 10  // Each bucket capacity

struct Node {
  int data;
  struct Node *next;
};

void BucketSort(int arr[],int size,int nbuckets);
struct Node *InsertionSort(struct Node *list);
void print(int arr[],int size);
void printBuckets(struct Node *list);
int getBucketIndex(int value);
int getNumOfBuckets(int arr[],int size);

void BucketSort(int arr[], int size, int nbuckets){
  int i, j;
  struct Node **buckets;
  int n = nbuckets/omp_get_num_threads();

  // Create buckets and allocate memory size
  buckets = (struct Node **)malloc(sizeof(struct Node *) * nbuckets);

  // Initalize empty buckets
  // Pode ser paralelizado
  #pragma omp parallel
  #pragma omp for
  for (i = 0; i < nbuckets; ++i) {
    buckets[i] = NULL;
  }

  // Fill the buckets with respective elements
  // Poder ser paralelizado
  //#pragma omp parallel
  //#pragma omp for schedule(static,n)
  for (i = 0; i < size; ++i) {
    struct Node *current;
    int pos = getBucketIndex(arr[i]);
    current = (struct Node *)malloc(sizeof(struct Node));
    current->data = arr[i];
    current->next = buckets[pos];
    buckets[pos] = current;
  }

  // Print the buckets along with their elements
  // Poder ser paralelizado mas por ordem
  //#pragma omp parallel
  //#pragma omp for ordered
  //for (i = 0; i < nbuckets; i++) {
    //printf("Bucket[%d]: ", i);
    //printBuckets(buckets[i]);
    //printf("\n");
  //}

  // Sort the elements of each bucket
  // Pode ser parelelizado
  #pragma omp parallel
  #pragma omp for
  for (i = 0; i < nbuckets; ++i) {
    buckets[i] = InsertionSort(buckets[i]);
  }

  //printf("-------------\n");
  //printf("Bucktets after sorting\n");
  // Paralelizado mas por ordem
  //#pragma omp parallel
  //#pragma omp for ordered
  //for (i = 0; i < nbuckets; i++) {
    //printf("Bucket[%d]: ", i);
    //printBuckets(buckets[i]);
    //printf("\n");
    //#pragma omp barrier
  //}

  // Put sorted elements on arr
  // Paralelizado?
  j=0;
  //#pragma omp parallel
  //#pragma omp for
  for (i = 0; i < nbuckets; i++) {
    struct Node *node;
    node = buckets[i];
    while (node) {
      arr[j++] = node->data;
      node = node->next;
    }
  }

  return;
}

// Function to sort the elements of each bucket
struct Node *InsertionSort(struct Node *list) {
  struct Node *k, *nodeList;
  if (list == 0 || list->next == 0) {
    return list;
  }

  nodeList = list;
  k = list->next;
  nodeList->next = 0;
  while (k != 0) {
    struct Node *ptr;
    if (nodeList->data > k->data) {
      struct Node *tmp;
      tmp = k;
      k = k->next;
      tmp->next = nodeList;
      nodeList = tmp;
      continue;
    }

    for (ptr = nodeList; ptr->next != 0; ptr = ptr->next) {
      if (ptr->next->data > k->data)
        break;
    }

    if (ptr->next != 0) {
      struct Node *tmp;
      tmp = k;
      k = k->next;
      tmp->next = ptr->next;
      ptr->next = tmp;
      continue;
    } else {
      ptr->next = k;
      k = k->next;
      ptr->next->next = 0;
      continue;
    }
  }
  return nodeList;
}

int getBucketIndex(int value) {
  return value / INTERVAL;
}

void print(int ar[],int size) {
  int i;
  for (i = 0; i < size; ++i) {
    printf("%d ", ar[i]);
  }
  printf("\n");
}

void printBuckets(struct Node *list) {
  struct Node *cur = list;
  while (cur) {
    printf("%d ", cur->data);
    cur = cur->next;
  }
}

int getNumOfBuckets(int ar[],int size){
   int max = 0;
   // Possivel paralelizacao cuidado com RaW
   for(int i=0; i<size; i++){
        if(max < ar[i])
                max = ar[i];
   }
   int n = (int) max / INTERVAL;
   printf("NBUCKETS: %d\n",n+1);
   return n+1;
}

int main(int argc, char** argv) {
  //int array[NARRAY] = {42, 32, 33, 52, 2, 37, 47, 15, 51, 20};

  if(argc > 1){
        FILE *f = NULL;
        f = fopen(argv[1],"r");

        if(f){
                int *array;
                char num[50];
                char* t;
                int first=1,size=0,i=0;
                while(fgets(num,50,f)){
                        t = strtok(num,"\r\n");
                        int a = atoi(t);
                        //printf("%d\n",a);
                        if(first){
                                size=a;
                                first=0;
                                array = malloc(size*sizeof(int));
                        }
                        else{
                                array[i]=a;
                        //      printf("Index %d: %d\n",i,array[i]);
                                i++;
                        }
                }
                printf("Size: %d\n",size);


                int nbuckets = getNumOfBuckets(array,size);

                printf("Initial array: ");
                print(array,size);
                printf("-------------\n");

                BucketSort(array,size,nbuckets);
                printf("-------------\n");
                printf("Sorted array: ");
                print(array,size);
                printf("Size: %d\n",size);
                printf("NBuckets: %d\n",nbuckets);
                printf("Bucket Range: %d\n" ,INTERVAL);
                return 0;
        }else{
                printf("File Not Found!\n");
        }
  }
  else{
        printf("Insufficent arguments\n");
        return 0;
  }

}