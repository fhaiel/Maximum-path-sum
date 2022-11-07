#include <stdio.h>

// Global variables
int lastRow [100] = {0};
int currentRow [100] = {0};
void processRow(int count){
        int idx, left, right;
for (idx = 0; idx <= count; idx++) {
    if (idx == 0) { // start of row of numbers (leftmost)
        currentRow[idx] += lastRow[idx];
    } else if (idx == count) { // end of row of numbers (rightmost)
        currentRow[idx] += lastRow[idx - 1];
    } else { // in middle of row, compare to 'parents' in previous row
        left = currentRow[idx] + lastRow[idx - 1];
        right = currentRow[idx] + lastRow[idx];
        currentRow[idx] = (left > right) ? left : right;
    }
    }
// copy current row to last row
    for (idx = 0; idx <= count; idx++) {
        lastRow[idx] = currentRow[idx];
    }
}
int main (void){
  
int maxSum = 0;
int temp = 0;
int rowIdx = 0;
int i;
char c;
FILE *fp;
// open file for reading
fp = fopen("text.txt", "r");
while ((c = fgetc (fp)) != EOF) {
    if (c == '\n') {
        currentRow[rowIdx] = temp;
        temp = 0; // reset temp for next number
        processRow(rowIdx); // process current row, copy to last [] row
        rowIdx = 0; // reset row 'counter' for next row of numbers
    } else if (c == ' ') {
        currentRow[rowIdx] = temp; // adding temp to the current row
        temp = 0; // reset temp for next number
        rowIdx++; // increment row 'counter' for next number
    } else {
        temp *= 10;
        temp += (c - '0'); // convert ascit char to integer
    }
}
// process final row, put into lastRow[]
    currentRow[rowIdx] = temp;
    processRow (rowIdx); // process current row, copy to last[] row
// get max sum from final row
    for (i = 0; i <= rowIdx; i++) {
    if (maxSum < lastRow[i]) maxSum = lastRow[i];}
    printf("\nMax sum: %d\n", maxSum);
    fclose(fp);
    return 0;
}