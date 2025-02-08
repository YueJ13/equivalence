#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define SIZE 6
#define TOTAL_NUMBERS 56
#define ROWS 484477
#define COLS 5
#define LINE_LENGTH 50


void save_representatives_to_file(int *representatives, int representative_count, const char *filename) {
    FILE *file = fopen(filename, "w"); 
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < representative_count; i++) {
        fprintf(file, "%d", representatives[i]); 
        if (i < representative_count - 1) {
            fprintf(file, "\n"); 
        }
    }

    fclose(file); 
}

// check the equivalence of two arrays
int arraysNotEqual(int a[], int b[], int size) {
    for (int i = 0; i < size; i++) {
        if (a[i] != b[i]) return 1; 
    }
    return 0; 
}


// check the equivalence of matrices
int matricesAreEqual(int x[3][5], int y[3][5]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            if (x[i][j] != y[i][j]) {
                return 0; 
            }
        }
    }
    return 1;
}

// check the equivalence of row vectors
int rowsAreEqual(int x[5], int y[5]) {
    for (int i = 0; i < 5; i++) {
        if (x[i] != y[i]) {
            return 0; 
        }
    }
    return 1; 
}


// minus
void minusf(int x[5], int y[5], int ans[5]){
    for (int i = 0; i<5; i++){
        ans[i] = x[i] - y[i];
    }
}

// plus
void plusf(int x[5], int y[5], int ans[5]){
    for (int i = 0; i<5; i++){
        ans[i] = x[i] + y[i];
    }
}

// multiply
void paramultif(int a, int y[5], int ans[5]){
    for (int i = 0; i<5; i++){
        ans[i] = a* y[i];
    }
}

// Function to sort array
void sort_array(int *array, int size) {
    int temp;
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (array[i] > array[j]) {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}


//change row order
void changerow(int x[2][3][5], int lrow[3], int x_copy[2][3][5]) {
    for (int k = 0; k < 2; k++) {
        for (int row = 0; row < 3; row++){    
            for (int col = 0; col < 5; col++) {
                x_copy[k][row][col] = x[k][lrow[row]][col]; 
            }
        }
    }  
}


//equivalence
int equalfun(int x[2][3][5], int y[2][3][5]) { 
    int indl3[5];
    int indl4[5];
    int indl5[5];
    int indl6[5];
    int indl7[5];
    int indl8[5];
    int indl9[5];
    int indl10[5];

    int ind4;
    int ind5;
    int ind6;

    int flag1=0;
    int flag2=0;
    int flag3=0;

    int lcoe[5]={-2,-1,0,1,2};
    for (int i = 0; i < 5 && flag1+flag2+flag3<3; i++){
        for (int j = 0; j < 5 && flag1+flag2+flag3<3; j++){
            for (int k = 0; k < 5 && flag1+flag2+flag3<3; k++){
                paramultif(lcoe[i], x[1][0], indl3);
                paramultif(lcoe[j], x[1][1], indl4);
                paramultif(lcoe[k], x[1][2], indl5);
                plusf(indl3,indl4,indl6);
                plusf(indl6, indl5, indl7);
                if (flag1==0){
                    paramultif(2,y[1][0], indl8);
                    ind4 = rowsAreEqual(indl7, indl8);
                    if (ind4 == 1){
                        flag1=1;
                    }
                }
                if (flag2==0){
                    paramultif(2,y[1][1], indl9);
                    ind5 = rowsAreEqual(indl7, indl9);
                    if (ind5 == 1){
                        flag2=1;
                    }
                }
                if (flag3==0){
                    paramultif(2,y[1][2], indl10);
                    ind6 = rowsAreEqual(indl7, indl10);
                    if (ind6 == 1){
                        flag3=1;
                    }
                }
            }
        }   
    }
    if (flag1 + flag2 + flag3 == 3) return 1;        
    return 0; 
}

//chang row of matrix Y
int lemmafunctionEqual(int x[2][3][5], int y[2][3][5]) {
    int ind1;
    int xnew[2][3][5];
    int lrow[6][3]={{0,1,2}, {1,2,0},{2,0,1},{0,2,1},{1,0,2},{2,1,0}};
    int flag = 1;
    int con2=0;
    for (int i = 0; i < 6&&flag; i++){
        changerow(x, lrow[i], xnew);
        ind1 = matricesAreEqual(xnew[0], y[0]);
        if (ind1==1){
            flag=0;
        }
        else{
            con2=con2+1;
        }
    }
    if (con2==6&&flag==1) return 0;

    if (equalfun(xnew, y)==1 && equalfun(y, xnew)==1) return 1;

    return 0;
}

void generatealphaN(int alphabeta[5][6], int lalphaN[2][3][5]){
    int lalpha[3][5];
    int lbeta[3][5]; 
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 3; j++){
            lalpha[j][i] = alphabeta[i][j];
        
            lbeta[j][i] = alphabeta[i][j + 3];
            lalphaN[1][j][i] = lbeta[j][i] - lalpha[j][i];
        }
    }

    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 3; j++){
            lalphaN[0][j][i] = lalpha[j][i];
        }
    }
}


int parent[ROWS];  


void init_union_find(int size) {
    for (int i = 0; i < size; i++) {
        parent[i] = i;  
    }
}


int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);  
    }
    return parent[x];
}


void union_elements(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        if (rootX < rootY) {
            parent[rootY] = rootX;
        } else {
            parent[rootX] = rootY;
        }
    }
}


int main() {
    clock_t start = clock();
    int **data0 = malloc(TOTAL_NUMBERS * sizeof(int *)); 
    for (int i = 0; i < TOTAL_NUMBERS; i++) {
        data0[i] = malloc(SIZE * sizeof(int));
    }

    FILE *file0 = fopen("C://Users//56573//Desktop//crealphabeta.txt", "r");
    if (file0 == NULL) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    char line0[LINE_LENGTH];
    for (int i = 0; i < TOTAL_NUMBERS; i++) {
        if (fgets(line0, sizeof(line0), file0) != NULL) {
            if (sscanf(line0, "{%d,%d,%d,%d,%d,%d}", 
                       &data0[i][0], &data0[i][1], &data0[i][2], 
                       &data0[i][3], &data0[i][4], &data0[i][5]) != 6) {
                fprintf(stderr, "Error reading line %d\n", i + 1);
                break;
            }
        } else {
            break; 
        }
    }

    fclose(file0);

    int **data = malloc(ROWS * sizeof(int *)); 
    for (int i = 0; i < ROWS; i++) {
        data[i] = malloc(COLS * sizeof(int));
    }

    FILE *file = fopen("C://Users//56573//Desktop//indices1.txt", "r");
    if (file == NULL) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    char line[LINE_LENGTH];
    for (int i = 0; i < ROWS; i++) {
        if (fgets(line, sizeof(line), file) != NULL) {
            if (sscanf(line, "{%d,%d,%d,%d,%d}", 
                       &data[i][0], &data[i][1], &data[i][2], 
                       &data[i][3], &data[i][4]) != 5) {
                fprintf(stderr, "Error reading line %d\n", i + 1);
                break; 
            }
        } else {
            break;
        }
    }


    fclose(file);
    bool to_delete[ROWS] = { false }; 
    
    int con=ROWS;
    int po1[56]={2, 1, 3, 4, 6, 5, 7, 15, 16, 17, 18, 20, 19, 21, 8, 9, 10, 11, 13, 12, 14, 22, 24, 23, 25, 27, 26, 28, 29, 31, 30, 32, 34, 33, 35, 43, 45, 44, 46, 47, 48, 49, 36, 38, 37, 39, 40, 41, 42, 50, 52, 51, 53, 54, 56, 55};
    int po2[56]={1, 4, 5, 2, 3, 6, 7, 8, 11, 12, 9, 10, 13, 14, 29, 30, 33, 31, 32, 34, 35, 36, 37, 40, 38, 39, 41, 42, 15, 16, 18, 19, 17, 20, 21, 22, 23, 25, 26, 24, 27, 28, 43, 44, 47, 48, 45, 46, 49, 50, 51, 54, 55, 52, 53, 56};
    int po3[56]={2, 4, 6, 1, 3, 5, 7, 15, 18, 20, 16, 17, 19, 21, 29, 31, 34, 30, 32, 33, 35, 43, 45, 47, 44, 46, 48, 49, 8, 9, 11, 13, 10, 12, 14, 22, 24, 25, 27, 23, 26, 28, 36, 38, 40, 41, 37, 39, 42, 50, 52, 54, 56, 51, 53, 55};
    int po4[56]={4, 1, 5, 2, 6, 3, 7, 29, 30, 33, 31, 34, 32, 35, 8, 11, 12, 9, 13, 10, 14, 36, 40, 37, 38, 41, 39, 42, 15, 18, 16, 19, 20, 17, 21, 43, 47, 44, 48, 45, 46, 49, 22, 25, 23, 26, 24, 27, 28, 50, 54, 51, 55, 52, 56, 53};
    int po5[56]={4, 2, 6, 1, 5, 3, 7, 29, 31, 34, 30, 33, 32, 35, 15, 18, 20, 16, 19, 17, 21, 43, 47, 45, 44, 48, 46, 49, 8, 11, 9, 13, 12, 10, 14, 36, 40, 38, 41, 37, 39, 42, 22, 25, 24, 27, 23, 26, 28, 50, 54, 52, 56, 51, 55, 53};
    int vt1[5];
    int vt2[5];
    int vt3[5];
    int vt4[5];
    int vt5[5];
    int v0[5]={0,0,0,0,0};
    for (int i = 0; i < ROWS; i++){
        if (to_delete[i]) continue;
        
        for (int j = 0; j < 5; j++){
            vt1[j] = po1[data[i][j]-1];
            vt2[j] = po2[data[i][j]-1];
            vt3[j] = po3[data[i][j]-1];
            vt4[j] = po4[data[i][j]-1];
            vt5[j] = po5[data[i][j]-1];
        }
        sort_array(vt1, 5);
        sort_array(vt2, 5);
        sort_array(vt3, 5);
        sort_array(vt4, 5);
        sort_array(vt5, 5);
        int va1 = -1;
        int va2 = -1;
        int va3 = -1;
        int va4 = -1;
        int va5 = -1;
        for (int j = 0; j < ROWS; j++){
            if (to_delete[j]) continue;
            if (data[j][0] <= vt1[0] && va1 == -1 && rowsAreEqual(data[j], vt1) == 1){
                con=con-1;
                to_delete[j] = true; 
                va1 = 0;
            }
            if (data[j][0] <= vt2[0] && va2 == -1 && rowsAreEqual(data[j], vt2) == 1){
                con=con-1;
                to_delete[j] = true; 
                va2 = 0;
            }
            if ( data[j][0] <= vt3[0] && va3 == -1 && rowsAreEqual(data[j], vt3) == 1){
                con=con-1;
                to_delete[j] = true; 
                va3 = 0;
            }
            if (data[j][0] <= vt4[0] && va4 == -1 && rowsAreEqual(data[j], vt4) == 1){
                con=con-1;
                to_delete[j] = true; 
                va4 = 0;
            }
            if (data[j][0] <= vt5[0] && va5 == -1 && rowsAreEqual(data[j], vt5) == 1){
                con=con-1;
                to_delete[j] = true; 
                va5 = 0;
            }
            if (va1 == 0 && va2==0 && va3==0 && va4==0 && va5==0) break;
        }
           
    }
    printf("%d\n", con);

    int datalist[con];
    
    int con1 = 0;
    for (int i = 0; i < ROWS; i++){
        if (to_delete[i] == false){
            datalist[con1]=i;
            con1++;          
        }
    }

    init_union_find(con);
    
    for (int i = 0; i < con; i++) {
        for (int j = i + 1; j < con; j++) {
            int in1=datalist[i];
            int alphabeta1[5][6];
            int l2[5];
            for (int k = 0; k < 5; k++) {
                l2[k] = data[in1][k];
            }
            for (int k = 0; k < 5; k++) {
                for (int p = 0; p < 6; p++) {
                    alphabeta1[k][p]=data0[l2[k]-1][p];
                } 
            }
            int alphan1[2][3][5];                     
            generatealphaN(alphabeta1, alphan1);

            int in2=datalist[j];
            int alphabeta2[5][6];
            int l3[5];
            for (int k = 0; k < 5; k++) {
                l3[k] = data[in2][k];
            }
            for (int k = 0; k < 5; k++) {
                for (int p = 0; p < 6; p++) {
                    alphabeta2[k][p]=data0[l3[k]-1][p];
                } 
            }
            int alphan2[2][3][5];
            generatealphaN(alphabeta2, alphan2);

            int ans1 = lemmafunctionEqual(alphan1, alphan2);
            if (ans1==1) {
                union_elements(i, j);
            }
        }
    }

    for (int i = 0; i < TOTAL_NUMBERS; i++) {
        free(data0[i]);
    }
    free(data0);
    for (int i = 0; i < ROWS; i++) {
        free(data[i]);
    }
    free(data);

    int *representatives = malloc(con * sizeof(int));
    int representative_count = 0;
    
    for (int i = 0; i < con; i++) {
        if (find(i) == i) {  
            representatives[representative_count++] = datalist[i];
        }
    }


    printf("%d\n", representative_count);
    save_representatives_to_file(representatives, representative_count, "C://Users//56573//Desktop//ansc.txt");
    free(representatives);
    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", time_spent);
    return 0;
}
