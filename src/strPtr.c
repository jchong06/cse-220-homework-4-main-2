//Justin Chong 116143020
#include <stdlib.h>
#include "strPtr.h"

#include <stdlib.h>
#include "strPtr.h"

int strgLen(const char *s) {
    int len = 0;
    if (s == NULL) {
        return -1;
    }
    while (s[len] != '\0') {
        len++;
    }
    return len;
}

void strgCopy(char *dest, char *src) {
    if (src == NULL || dest == NULL) {
        return;
    }
    while (*src != '\0'){
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    
    (void)dest;
    (void)src;
}

void strgChangeCase(char *s) {
    if (s == NULL) {
        return;
    }
    for (int i = 0; s[i] != '\0'; i++) {
        int left_is_digit  = (i > 0 && (s[i-1] >= '0' && s[i-1] <= '9'));
        int right_is_digit = (s[i+1] != '\0' && (s[i+1] >= '0' && s[i+1] <= '9'));
        if (left_is_digit || right_is_digit) {
            continue;
        }
        if (s[i] >= 'a' && s[i] <= 'z') {
            s[i] = s[i] - ('a' - 'A');  
        }
        else if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] = s[i] + ('a' - 'A');  
        }
    }
    (void)s;
}

int strgDiff(char *s1, char *s2) {
    int count = 0;
    if (s1 == NULL || s2 == NULL){
        return -2;
    }
    while (s1 != NULL && s2 != NULL && *s1 != '\0' && *s2 != '\0'){
        if (*s1 != *s2) {
            return count;
        }
        count++;
        s1++;
        s2++;
    }
    if (*s1 != '\0' ||  *s2 != '\0') {
        return count;
    }
    
    (void)s1;
    (void)s2;
    return -1;
}

void strgInterleave(char *s1, char *s2, char *d) {
    if (s1 == NULL || s2 == NULL || d == NULL) {
        return;
    }
    while (*s1 != '\0' && *s2 != '\0') {
        *d++ = *s1++;
        *d++ = *s2++;
    }
    while (*s1 != '\0') {
        *d++ = *s1++;
    }
    while (*s2 != '\0') {
        *d++ = *s2++;
    }
    *d = '\0';
}


void strgReverseLetters(char *s) {
    // TODO: implement
    int l = 0;
    int r = strgLen(s) - 1;
    while (l < r) {
        if (!((s[l] >= 'A' && s[l] <= 'Z') || (s[l] >= 'a' && s[l] <= 'z'))) {
            l++;
        } else if (!((s[r] >= 'A' && s[r] <= 'Z') || (s[r] >= 'a' && s[r] <= 'z'))) {
            r--;
        } else {
            char temp = s[l];
            s[l] = s[r];
            s[r] = temp;
            l++;
            r--;
        }
    }
    (void)s;
}



/**
 * Create all test cases inside of the main function below.
 * Run the test cases by first compiling with "make" and then 
 * running "./bin/strPtr"
 * 
 * Before submmiting your assignment, please comment out your 
 * test cases for the TAs. 
 * Comment out if using criterion to test.
 */
// int main(int argc, char* argv[]){
// 	(void)argc;
// 	(void)argv;
//     /* ---------- strgLen ---------- */
//     printf("Testing strgLen:\n");
//     printf("Length of 'Hello': %d\n", strgLen("Hello"));    // 5
//     printf("Length of '': %d\n", strgLen(""));              // 0
//     printf("Length of NULL: %d\n", strgLen(NULL));          // 0

//     /* ---------- strgCopy ---------- */
//     char buf[20];
//     printf("\nTesting strgCopy:\n");
//     strgCopy(buf, "Computer");
//     printf("Copied string: %s\n", buf);                     // Computer
//     strgCopy(buf, "");
//     printf("Copied empty string: '%s'\n", buf);            // ''

//     /* ---------- strgChangeCase ---------- */
//     char s1[] = "AbCz";           // letters only
//     char s2[] = "A1b2C";          // letters adjacent to digits
//     char s3[] = "Hello World!";   // letters with spaces and punctuation

//     printf("\nTesting strgChangeCase:\n");
//     strgChangeCase(s1);
//     printf("Toggled s1: %s\n", s1);   // should toggle all: aBcZ

//     strgChangeCase(s2);
//     printf("Toggled s2: %s\n", s2);   // letters next to digits should stay same

//     strgChangeCase(s3);
//     printf("Toggled s3: %s\n", s3);   // toggle letters not next to digits

//     /* ---------- strgDiff ---------- */
//     printf("\nTesting strgDiff:\n");
//     printf("Diff 'abc' vs 'abc': %d\n", strgDiff("abc", "abc"));     // -1
//     printf("Diff 'abcd' vs 'abXd': %d\n", strgDiff("abcd", "abXd")); // 2
//     printf("Diff 'abc' vs 'abcd': %d\n", strgDiff("abc", "abcd"));   // 3
//     printf("Diff NULL vs 'abc': %d\n", strgDiff(NULL, "abc"));       // -2 or 0 based on your implementation

//     /* ---------- strgInterleave ---------- */
//     char d1[20];
//     printf("\nTesting strgInterleave:\n");
//     strgInterleave("abc", "123", d1);
//     printf("Interleave 'abc' & '123': %s\n", d1);   // a1b2c3

//     strgInterleave("abcdef", "123", d1);
//     printf("Interleave 'abcdef' & '123': %s\n", d1); // a1b2c3def

//     strgInterleave("12", "abcd", d1);
//     printf("Interleave '12' & 'abcd': %s\n", d1);    // 1a2bcd

//     /* ---------- strgReverseLetters ---------- */
//     char r1[] = "abc-def";
//     char r2[] = "a1b2c3";
//     char r3[] = "a1b2c";

//     printf("\nTesting strgReverseLetters:\n");
//     strgReverseLetters(r1);
//     printf("Reverse letters r1: %s\n", r1);  // fed-cba

//     strgReverseLetters(r2);
//     printf("Reverse letters r2: %s\n", r2);  // c3b2a1

//     strgReverseLetters(r3);
//     printf("Reverse letters r3: %s\n", r3);  // dlroW, olleH!

//     return 0;
// }