#define MAXSTRLEN 10
#define MAXCATS 500
#define MAXJUDGES 3
#define MAXLETTERS 26

struct cat
{
    int cat_ID;
    char catName[MAXSTRLEN + 1];
    int score1;
    int score2;
    int score3;
    float average;
};

struct KeyValuePair // creating struct for a key value pair system
{
    const char *key;
    int value;
    float percentage;
};

void readData(struct cat *cats, int *c, int *count);
int getCutestCat(struct cat *s, int n);
void findLetterUsage(struct cat *c, int *n, struct KeyValuePair *letters);
void printData(int *n, int cutestCatIndex);
