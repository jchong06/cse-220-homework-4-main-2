//Justin Chong 116143020
#include <stdlib.h>
#include "caesar.h" 
#include "strPtr.h"

/**
 *  Feel free to use the functions that you made in strPtr.c
*/ 

int encryptCaesar(const char *plaintext, char *ciphertext, int key) {
	if (plaintext == NULL || ciphertext == NULL) return -2;
    if (strgLen(plaintext) == 0) {
        strgCopy(ciphertext, "undefined__EOM__");
        return 0;
    }
    int len = strgLen(plaintext);
    int count = len;
    for (int i = 0; i < len; i++) {
        char c = plaintext[i];
        if (c >= 'A' && c <= 'Z') {
            ciphertext[i] = ((c - 'A' + key + i) % 26) + 'A';
              }      
        else if (c >= 'a' && c <= 'z') {
            ciphertext[i] = ((c - 'a' + key + i) % 26) + 'a';
        }
        else if (c >= '0' && c <= '9') {
            ciphertext[i] = ((c - '0' + key + 2*i) % 10) + '0';
        }
        else {
            ciphertext[i] = c;
            count--;
        }
    }
    
    strgCopy(ciphertext + len, "__EOM__");

    (void)plaintext;
    (void)ciphertext;
    (void)key;
    return count;
}

int decryptCaesar(const char *ciphertext, char *plaintext, int key) {
	if (ciphertext == NULL || plaintext == NULL) return -2;
    if (strgLen(plaintext) == 0) return 0;
    if (strgDiff((char *) ciphertext, "undefined__EOM__") == -1){
        strgCopy(plaintext, "undefined");
        return 0;
    }
    int len = strgLen(ciphertext);
    if (len < 7) return -1; 
    if (strgDiff((char *)ciphertext + strgLen((char *)ciphertext) - 7, "__EOM__") != -1) {
        return -1; 
    }
    int editLen = len - 7;
    int count = editLen;
    for (int i = 0; i < editLen; i++) {
        char c = ciphertext[i];
        if (c >= 'A' && c <= 'Z') {
            plaintext[i] = ((c - 'A' - key - i + 26) % 26) + 'A';
              }      
        else if (c >= 'a' && c <= 'z') {
            plaintext[i] = ((c - 'a' - key - i + 26) % 26) + 'a';
        }
        else if (c >= '0' && c <= '9') {
            plaintext[i] = ((c - '0' - key - 2*i + 10) % 10) + '0';
        }
        else {
            plaintext[i] = c;
            count--;
        }
    }
    plaintext[editLen] = '\0';
    (void)ciphertext;
    (void)plaintext;
    (void)key;
    return count;
}


/**
 * Create all test cases inside of the main function below.
 * Run the test cases by first compiling with "make" and then 
 * running "./bin/caesar"
 * 
 * Before submmiting your assignment, please comment out your 
 * test cases for the TAs. 
 * Comment out if using criterion to test.
 */
// int main(void) {
//     const char *plaintext = "CS";
//     int key = 1;

//     char ciphertext[27] = {0};        
//     char decrypted[27]  = {0};

//     printf("Plain : \"%s\"\n", plaintext);
//     printf("Key   : %d\n", key);

//     /* --- Encrypt --- */
//     int enc_len = encryptCaesar(plaintext, ciphertext, key);
//     printf("Encrypted (returned len=%d): \"%s\"\n", enc_len, ciphertext);

//     /* --- Decrypt --- */
//     int dec_len = decryptCaesar(ciphertext, decrypted, key);
//     printf("Decrypted (returned len=%d): \"%s\"\n", dec_len, decrypted);

//     if (strgDiff((char *)plaintext, decrypted) == -1) {
//         printf("SUCCESS: Decrypted text matches original.\n");
//     } else {
//         printf("FAIL   : Decrypted text does not match.\n");
//     }

//     return 0;
// }
