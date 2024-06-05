#include <stdio.h>
#include <string.h>
 
void xorOperation(char *dividend, char *divisor, int start) {
    for (int i = 0; i < strlen(divisor); i++) {
        dividend[start + i] = (dividend[start + i] == divisor[i]) ? '0' : '1';
    }
}
 
void crc(char *dataword, char *divisor, char *remainder) {
    int datawordLen = strlen(dataword);
    int divisorLen = strlen(divisor);
 
    // Append zeros to the dataword
    for (int i = 0; i < divisorLen - 1; i++) {
        dataword[datawordLen + i] = '0';
    }
    dataword[datawordLen + divisorLen - 1] = '\0';
 
    char dividend[datawordLen + divisorLen];
    strcpy(dividend, dataword);
 
    for (int i = 0; i <= datawordLen; i++) {
        if (dividend[i] == '1') {
            xorOperation(dividend, divisor, i);
        }
    }
 
    strncpy(remainder, &dividend[datawordLen], divisorLen - 1);
    remainder[divisorLen - 1] = '\0';
}
 
int main() {
    char dataword[100], divisor[100], remainder[100];
 
    printf("Enter the data word: ");
    scanf("%s", dataword);
    
    printf("Enter the divisor: ");
    scanf("%s", divisor);
 
    crc(dataword, divisor, remainder);
 
    printf("CRC code: %s\n", remainder);
 
    return 0;
}
