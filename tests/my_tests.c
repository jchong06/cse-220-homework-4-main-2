#include <criterion/criterion.h>
#include <string.h>

#include "caesar.h"
#include "strPtr.h"

/*
 * Part 1: String utility functions
 */

//////////////////////
// strgLen Tests (10)
//////////////////////
Test(strgLen, normal_strings) {
    cr_assert_eq(strgLen("Stony Brook"), 11);
    cr_assert_eq(strgLen("CSE 220"), 7);
}
Test(strgLen, single_chars) {
    cr_assert_eq(strgLen("C"), 1);
    cr_assert_eq(strgLen("1"), 1);
}
Test(strgLen, empty_and_null) {
    cr_assert_eq(strgLen(""), 0);
    cr_assert_eq(strgLen(NULL), -1);
}
Test(strgLen, spaces_and_symbols) {
    cr_assert_eq(strgLen("   "), 3);
    cr_assert_eq(strgLen("!@#"), 3);
}
Test(strgLen, longer_phrase) {
    cr_assert_eq(strgLen("System Fundamental"), 18);
    cr_assert_eq(strgLen("abcdefghijklmnopqrstuvwxyz"), 26);
}

//////////////////////
// strgCopy Tests (10)
//////////////////////
Test(strgCopy, normal_copy) {
    char d[32] = {0};
    strgCopy(d, "Computer Science");
    cr_assert_str_eq(d, "Computer Science");
}
Test(strgCopy, empty_source) {
    char d[8] = "xxx";
    strgCopy(d, "");
    cr_assert_str_eq(d, "");
}
Test(strgCopy, null_dest) {
    strgCopy(NULL, "foo"); // should do nothing
}
Test(strgCopy, null_src) {
    char d[16] = "UNCHANGED";
    strgCopy(d, NULL);
    cr_assert_str_eq(d, "UNCHANGED");
}
Test(strgCopy, overwrite) {
    char d[16] = "AAAA";
    strgCopy(d, "B");
    cr_assert_str_eq(d, "B");
}
Test(strgCopy, numbers) {
    char d[16];
    strgCopy(d, "12345");
    cr_assert_str_eq(d, "12345");
}
Test(strgCopy, whitespace) {
    char d[16];
    strgCopy(d, "   ");
    cr_assert_str_eq(d, "   ");
}
Test(strgCopy, symbols) {
    char d[16];
    strgCopy(d, "@@@");
    cr_assert_str_eq(d, "@@@");
}
Test(strgCopy, repeated) {
    char d[16];
    strgCopy(d, "first");
    strgCopy(d, "second");
    cr_assert_str_eq(d, "second");
}
Test(strgCopy, exact_fit) {
    char d[6] = {0};
    strgCopy(d, "five");
    cr_assert_str_eq(d, "five");
}

////////////////////////////
// strgChangeCase Tests (10)
////////////////////////////
Test(strgChangeCase, simple) {
    char s[] = "Stony Brook";
    strgChangeCase(s);
    cr_assert_str_eq(s, "sTONY bROOK");
}
Test(strgChangeCase, digits_only) {
    char s[] = "12345";
    strgChangeCase(s);
    cr_assert_str_eq(s, "12345");
}
Test(strgChangeCase, mix_with_digits) {
    char s[] = "CSE220";
    strgChangeCase(s);
    cr_assert_str_eq(s, "csE220");
}
Test(strgChangeCase, single_letter) {
    char s[] = "a";
    strgChangeCase(s);
    cr_assert_str_eq(s, "A");
}
Test(strgChangeCase, upper_single) {
    char s[] = "Z";
    strgChangeCase(s);
    cr_assert_str_eq(s, "z");
}
Test(strgChangeCase, adjacent_digits) {
    char s[] = "a1b";
    strgChangeCase(s);
    cr_assert_str_eq(s, "a1b");
}
Test(strgChangeCase, special_chars) {
    char s[] = "_X_";
    strgChangeCase(s);
    cr_assert_str_eq(s, "_x_");
}
Test(strgChangeCase, already_upper) {
    char s[] = "ABC";
    strgChangeCase(s);
    cr_assert_str_eq(s, "abc");
}
Test(strgChangeCase, already_lower) {
    char s[] = "def";
    strgChangeCase(s);
    cr_assert_str_eq(s, "DEF");
}
Test(strgChangeCase, empty) {
    char s[] = "";
    strgChangeCase(s);
    cr_assert_str_eq(s, "");
}

//////////////////////
// strgDiff Tests (10)
//////////////////////
Test(strgDiff, identical) {
    cr_assert_eq(strgDiff("Hello", "Hello"), -1);
}
Test(strgDiff, middle_diff) {
    cr_assert_eq(strgDiff("CSE-220","CSE220"), 3);
}
Test(strgDiff, prefix_diff) {
    cr_assert_eq(strgDiff("CSE220","SE220"), 0);
}
Test(strgDiff, both_empty) {
    cr_assert_eq(strgDiff("", ""), -1);
}
Test(strgDiff, null_inputs) {
    cr_assert_eq(strgDiff(NULL, "foo"), -2);
    cr_assert_eq(strgDiff("foo", NULL), -2);
}
Test(strgDiff, suffix_diff) {
    cr_assert_eq(strgDiff("short","shorter"), 5);
}
Test(strgDiff, case_diff) {
    cr_assert_eq(strgDiff("abc","Abc"), 0);
}
Test(strgDiff, numeric_diff) {
    cr_assert_eq(strgDiff("123","124"), 2);
}
Test(strgDiff, partial_match) {
    cr_assert_eq(strgDiff("abc","abz"), 2);
}
Test(strgDiff, long_vs_short) {
    cr_assert_eq(strgDiff("abcdef","abc"), 3);
}

/////////////////////////////
// strgInterleave Tests (10)
/////////////////////////////
Test(strgInterleave, equal_length) {
    char d[16];
    strgInterleave("abc","123", d);
    cr_assert_str_eq(d,"a1b2c3");
}
Test(strgInterleave, longer_first) {
    char d[16];
    strgInterleave("abcdef","123", d);
    cr_assert_str_eq(d,"a1b2c3def");
}
Test(strgInterleave, longer_second) {
    char d[16];
    strgInterleave("cse","12345", d);
    cr_assert_str_eq(d,"c1s2e345");
}
Test(strgInterleave, second_short) {
    char d[16];
    strgInterleave("1234","cs", d);
    cr_assert_str_eq(d,"1c2s34");
}
Test(strgInterleave, both_empty) {
    char d[4];
    strgInterleave("","",d);
    cr_assert_str_eq(d,"");
}
Test(strgInterleave, first_empty) {
    char d[8];
    strgInterleave("","123",d);
    cr_assert_str_eq(d,"123");
}
Test(strgInterleave, second_empty) {
    char d[8];
    strgInterleave("abc","",d);
    cr_assert_str_eq(d,"abc");
}
Test(strgInterleave, symbols) {
    char d[16];
    strgInterleave("$$$","***",d);
    cr_assert_str_eq(d,"$*$*$*"); 
}
Test(strgInterleave, uneven) {
    char d[16];
    strgInterleave("a","123",d);
    cr_assert_str_eq(d,"a123");
}
Test(strgInterleave, whitespace) {
    char d[16];
    strgInterleave("a b","12",d);
    cr_assert_str_eq(d,"a1 2b");
}

//////////////////////////////////
// strgReverseLetters Tests (10)
//////////////////////////////////
Test(strgReverseLetters, word) {
    char s[]="hello";
    strgReverseLetters(s);
    cr_assert_str_eq(s,"olleh");
}
Test(strgReverseLetters, sentence) {
    char s[]="hello world";
    strgReverseLetters(s);
    cr_assert_str_eq(s,"dlrow olleh");
}
Test(strgReverseLetters, with_dash) {
    char s[]="ab-cd";
    strgReverseLetters(s);
    cr_assert_str_eq(s,"dc-ba");
}
Test(strgReverseLetters, with_digit) {
    char s[]="e1f!";
    strgReverseLetters(s);
    cr_assert_str_eq(s,"f1e!");
}
Test(strgReverseLetters, unchanged_symbols) {
    char s[]="_X_";
    strgReverseLetters(s);
    cr_assert_str_eq(s,"_X_");
}
Test(strgReverseLetters, empty) {
    char s[]="";
    strgReverseLetters(s);
    cr_assert_str_eq(s,"");
}
Test(strgReverseLetters, uppercase) {
    char s[]="ABC";
    strgReverseLetters(s);
    cr_assert_str_eq(s,"CBA");
}
Test(strgReverseLetters, numbers_inside) {
    char s[]="ab12cd";
    strgReverseLetters(s);
    cr_assert_str_eq(s,"dc12ba");
}
Test(strgReverseLetters, palindrome) {
    char s[]="madam";
    strgReverseLetters(s);
    cr_assert_str_eq(s,"madam");
}
Test(strgReverseLetters, mixed) {
    char s[]="Mix3d";
    strgReverseLetters(s);
    cr_assert_str_eq(s,"dxi3M");
}

/*
 * Part 2: Caesar cipher
 */

//////////////////////////////
// encryptCaesar Tests (10)
//////////////////////////////
Test(encryptCaesar, basics) {
    char out[64];
    cr_assert_eq(encryptCaesar("abc",out,2),3);
    cr_assert_str_eq(out,"ceg__EOM__");
}
Test(encryptCaesar, uppercase) {
    char out[64];
    encryptCaesar("Ayb",out,3);
    cr_assert_str_eq(out,"Dcg__EOM__");
}
Test(encryptCaesar, alnum) {
    char out[64];
    encryptCaesar("Cse220",out,1);
    cr_assert_str_eq(out,"Duh911__EOM__");
}
Test(encryptCaesar, zero_key) {
    char out[64];
    encryptCaesar("CS",out,0);
    cr_assert_str_eq(out,"CT__EOM__");
}
Test(encryptCaesar, long) {
    char out[64];
    encryptCaesar("System Fundamentals",out,1);
    cr_assert_str_eq(out,"Tavxjs Ndxomzscjrdl__EOM__");
}
Test(encryptCaesar, empty) {
    char out[64];
    cr_assert_eq(encryptCaesar("",out,5),0);
    cr_assert_str_eq(out,"undefined__EOM__");
}
Test(encryptCaesar, null_args) {
    char out[16];
    cr_assert_eq(encryptCaesar(NULL,out,1),-2);
    cr_assert_eq(encryptCaesar("hi",NULL,1),-2);
}
Test(encryptCaesar, numeric_only) {
    char out[16];
    encryptCaesar("123",out,2);
    cr_assert(out[0]); // just check produced something
}
Test(encryptCaesar, symbols) {
    char out[16];
    encryptCaesar("!@#",out,1);
    cr_assert(out[0]);
}
Test(encryptCaesar, space) {
    char out[16];
    encryptCaesar("a b",out,2);
    cr_assert(out[1]==' ');
}

//////////////////////////////
// decryptCaesar Tests (10)
//////////////////////////////
Test(decryptCaesar, basics) {
    char out[64];
    decryptCaesar("ceg__EOM__",out,2);
    cr_assert_str_eq(out,"abc");
}
Test(decryptCaesar, uppercase) {
    char out[64];
    decryptCaesar("Dcg__EOM__",out,3);
    cr_assert_str_eq(out,"Ayb");
}
Test(decryptCaesar, alnum) {
    char out[64];
    decryptCaesar("Duh911__EOM__",out,1);
    cr_assert_str_eq(out,"Cse220");
}
Test(decryptCaesar, zero_key) {
    char out[64];
    decryptCaesar("CT__EOM__",out,0);
    cr_assert_str_eq(out,"CS");
}
Test(decryptCaesar, long) {
    char out[64];
    decryptCaesar("Tavxjs Ndxomzscjrdl__EOM__",out,1);
    cr_assert_str_eq(out,"System Fundamentals");
}
Test(decryptCaesar, empty_marker) {
    char out[32];
    decryptCaesar("undefined__EOM__",out,7);
    cr_assert_str_eq(out,"undefined");
}
Test(decryptCaesar, zero_len_plain) {
    char p[1] = "";
    cr_assert_eq(decryptCaesar("ceg__EOM__",p,2),0);
    cr_assert_str_eq(p,"");
}
Test(decryptCaesar, missing_marker) {
    char buf[32];
    strcpy(buf,"no marker here");
    cr_assert_eq(decryptCaesar("no marker here",buf,1),-1);
    cr_assert_str_eq(buf,"no marker here");
}
Test(decryptCaesar, null_args) {
    char out[16];
    cr_assert_eq(decryptCaesar(NULL,out,1),-2);
    cr_assert_eq(decryptCaesar("abc__EOM__",NULL,1),-2);
}
Test(decryptCaesar, digits) {
    char out[16];
    cr_assert_eq(decryptCaesar("456__EOM__", out, 3), 3);
    cr_assert_str_eq(out, "109");
}