#include <stdio.h>
#include <stdlib.h>


typedef int DATA;
struct node{
    DATA d;
    struct node*left;
    struct node*right;
};

typedef struct node NODE;
typedef NODE  *BTREE;


void  inorder(BTREE root)
{
    if(root!=NULL){
        inorder(root->left);
        printf("%d\t",root->d);
        inorder(root->right);
        
    }
}

BTREE new_node(void)
{return(malloc(sizeof(NODE)));}

BTREE init_node(DATA d1,BTREE p1, BTREE p2)
{
    BTREE t;
    t= new_node();
    t->d=d1;
    t->left=p1;
    t->right=p2;
    return t;
}

BTREE create_tree(DATA a[],int i , int size){

    if(i>=size)
     return NULL;
    else
     return (init_node(a[i],
             create_tree(a,2*i+1,size),
             create_tree(a,2*i+2,size)));

}

int main() {
    BTREE b;
    FILE *inputFile, *outputFile;
    int size, *data, i, sum = 0, max = INT_MIN;

    // Open the file for reading
    inputFile = fopen("rata.txt", "r");
    if (inputFile == NULL) {
        perror("Error opening the file");
        return 1;
    }

    // Read the size of the array
    fscanf(inputFile, "%d", &size);

    // Dynamically allocate memory for the array
    data = (int *)malloc(size * sizeof(int));
    if (data == NULL) {
        perror("Memory allocation failed");
        fclose(inputFile);
        return 1;
    }

    // Read integers into the array and compute sum and max
    for (i = 0; i < size; ++i) {
        fscanf(inputFile, "%d", &data[i]);
        sum += data[i];

        if (data[i] > max) {
            max = data[i];
        }
    }

    // Close the input file
    fclose(inputFile);

    // Compute the average
    double average = (double)sum / size;

    // Print results to the screen
    printf("Array values:\n");
    for (i = 0; i < size; ++i) {
        printf("%d ", data[i]);
    }

    printf("\n\n");
    printf("Average: %.2f\n", average);
    printf("Max: %d\n", max);

    // Open the output file for writing
    outputFile = fopen("answer-hw3.txt", "w");
    if (outputFile == NULL) {
        perror("Error opening the output file");
        free(data);
        return 1;
    }

    // Print results to the output file
    fprintf(outputFile, "Array values:\n");
    for (i = 0; i < size; ++i) {
        fprintf(outputFile, "%d ", data[i]);
    }

    fprintf(outputFile, "\n\n");
    fprintf(outputFile, "Average: %.2f\n", average);
    fprintf(outputFile, "Max: %d\n", max);





    // Close the output file
    fclose(outputFile);

    b=create_tree(data,0,size);
    inorder(b);
    printf("\n\n");

    // Free dynamically allocated memory
    free(data);

    return 0;
}