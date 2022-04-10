#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN 64
#define MAXLINES 128
#define MAXSTEPS 40

struct proto_rules {
    char leftside[2];
    char rightside;
}
rules[MAXLINES];

int rulecount;
unsigned long long alphabet[26];

void do_pair(char a, char b, int count) {
    count++;
    if (count > MAXSTEPS) return;

    for (int i = 0; i < rulecount; i++)
        if (rules[i].leftside[0] == a)
            if (rules[i].leftside[1] == b) {
                alphabet[rules[i].rightside - 'A']++;
                do_pair(a, rules[i].rightside, count);
                do_pair(rules[i].rightside, b, count);
            }
    return;
}

int main() {
    char line[LEN];
    char original_string[LEN];
    fgets(original_string, LEN, stdin);
    fgets(line, LEN, stdin); // empty line

    while (fgets(line, LEN, stdin) != NULL) {
        if (strlen(line) < 2) continue;

        rules[rulecount].leftside[0] = line[0];
        rules[rulecount].leftside[1] = line[1];
        rules[rulecount].rightside = line[6];

        rulecount++;
    }


    
    int len = strlen(original_string);
    original_string[len-1]=0;
    len--;
    for (int i = 0; i < len; i++)
        alphabet[original_string[i] - 'A']++;

        
    for (int i = 0; i < len - 1; i++)
        do_pair(original_string[i], original_string[i + 1], 0);

    unsigned long long max = 0;
    unsigned long long min = 0 - 1;

    for (int i = 0; i < 26; i++) 
        if(alphabet[i])
        {
            if (max < alphabet[i])
                max = alphabet[i];
            if (min > alphabet[i])
                min = alphabet[i];
        }
    

    printf("%llu\n", max - min);

    return 0;
}
