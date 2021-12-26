//Bucket sort in C

#include <stdio.h>
#include <stdlib.h>

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

  // Create buckets and allocate memory size
  buckets = (struct Node **)malloc(sizeof(struct Node *) * nbuckets);

  // Initalize empty buckets
  for (i = 0; i < nbuckets; ++i) {
    buckets[i] = NULL;
  }

  // Fill the buckets with respective elements
  for (i = 0; i < size; ++i) {
    struct Node *current;
    int pos = getBucketIndex(arr[i]);
    current = (struct Node *)malloc(sizeof(struct Node));
    current->data = arr[i];
    current->next = buckets[pos];
    buckets[pos] = current;
  }

  // Print the buckets along with their elements
  for (i = 0; i < nbuckets; i++) {
    printf("Bucket[%d]: ", i);
    printBuckets(buckets[i]);
    printf("\n");
  }

  // Sort the elements of each bucket
  for (i = 0; i < nbuckets; ++i) {
    buckets[i] = InsertionSort(buckets[i]);
  }

  printf("-------------\n");
  printf("Bucktets after sorting\n");
  for (i = 0; i < nbuckets; i++) {
    printf("Bucket[%d]: ", i);
    printBuckets(buckets[i]);
    printf("\n");
  }

  // Put sorted elements on arr
  for (j = 0, i = 0; i < nbuckets; ++i) {
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
  int *array;
  if(argc > 2){
        int size = atoi(argv[1]);
        printf("Size: %d\n",size);
        array = malloc(size*sizeof(int));
        for(int i=2,j=0; i<argc; i++,j++){
                //printf("arg %d: %s\n",i,argv[i]);
                array[j] = atoi(argv[i]);
                printf("Index %d: %d\n",j,array[j]);
        }
        int nbuckets = getNumOfBuckets(array,size);
        printf("Initial array: ");
        print(array,size);
        printf("-------------\n");

        BucketSort(array,size,nbuckets);
        printf("-------------\n");
        printf("Sorted array: ");
        print(array,size);
        return 0;
  }
  else{
        printf("Insufficent arguments\n");
        return 0;
  }

}