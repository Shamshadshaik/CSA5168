#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT_LENGTH 1000

void frequencyAnalysis(const char *text, int freq[256]) {
    int len = strlen(text);
    for (int i = 0; i < len; i++) {
        if (isprint(text[i])) {
            freq[(unsigned char)text[i]]++;
        }
    }
}

void printFrequency(int freq[256]) {
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            printf("%c: %d\n", i, freq[i]);
        }
    }
}

void substitute(char *text, char from, char to) {
    while (*text) {
        if (*text == from) {
            *text = to;
        }
        text++;
    }
}

int main() {
    char ciphertext[MAX_TEXT_LENGTH] = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83(88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8*;4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81 (‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";
    int freq[256] = {0};

    frequencyAnalysis(ciphertext, freq);

    printf("Character frequencies:\n");
    printFrequency(freq);

    
    substitute(ciphertext, '‡', 'e'); 
    substitute(ciphertext, '†', 't'); 
    
    printf("Partially decrypted text:\n%s\n", ciphertext);

    return 0;
}

