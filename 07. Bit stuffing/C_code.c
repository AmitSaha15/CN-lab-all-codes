#include <stdio.h>
#include <string.h>
 
void bit_stuff(char *input, char *output) {
    int count = 0;
    int j = 0;
 
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] == '1') {
            count++;
        } else {
            count = 0;
        }
        output[j++] = input[i];
 
        if (count == 5) {
            output[j++] = '0';
            count = 0;
        }
    }
    output[j] = '\0';
}
 
int main() {
    char input[100], output[200];
 
    printf("Enter bit stream: ");
    scanf("%s", input);
 
    bit_stuff(input, output);
 
    printf("Stuffed bit stream: %s\n", output);
 
    return 0;
}
