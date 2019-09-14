#include <cstdio>
#include <cctype>
#include <cstdlib>

#define MASSIZE 1000
#define STRSIZE 1000

#define LESS -1
#define GREATER 1
#define EQUAL 0

#define ERROR -1
#define EMPTY 0
#define OK 1

char Buffer[STRSIZE];
int BufIdx = EMPTY;

char Text[MASSIZE][STRSIZE];
int TextIdx = EMPTY;

int BufEmpty(void);
void PutBuf(const char c);
char GetBuf(void);

int GetLine(char *line);

void GetText(void);
void PrintText(void);

void StrCpy(char *a, char *b);
int StrCmp(char *a, char *b);
void Swap(char *a, char *b);

void Sort(int l, int r);

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    GetText();
    PrintText();
    Sort(0, TextIdx - 1);
    PrintText();
}

int BufEmpty() {
    return !BufIdx;
}

void PutBuf(const char c) {
    if (!isspace(c))
        Buffer[BufIdx++] = c;
}

char GetBuf() {
    return Buffer[--BufIdx];
}

int GetLine(char *line) {
    char c;
    while (isspace(c = getchar()) && c != '\n' && c != EOF);
    if (c == EOF)
        return ERROR;
    PutBuf(c);
    if (BufEmpty()) {
        *line = '\0';
        return EMPTY;
    }
    while ((c = getchar()) != EOF && c != '\n' || !BufEmpty()) {
        while (!BufEmpty())
            *line++ = GetBuf();
        if (c != EOF && c != '\n')
            *line++ = c;
        else
            break;
    }
    *line = '\0';
    return OK;
}

void GetText() {
    int res = EMPTY;
    while((res = GetLine(Text[TextIdx])) != ERROR) {
        if (res == OK)
            ++TextIdx;
    }
}

void PrintText() {
    for (int i = 0; i < TextIdx; ++i)
        printf("%d: %s\n", i + 1, Text[i]);
    printf("\n");
}

void StrCpy(char *a, char *b) {
    while(*b++ = *a++);
    *b = '\0';
}

int StrCmp (char *a, char *b) {
    while (*a == *b) {
        if (*a == '\0')
            return EQUAL;
        ++a, ++b;
    }
    return (*a < *b ? LESS : GREATER);
}

void Swap(char *a, char *b) {
    char *temp = (char *)malloc(STRSIZE);
    StrCpy(a, temp);
    StrCpy(b, a);
    StrCpy(temp, b);
}

void Sort(int l, int r) {
    int i = l, j = r, m = i + (j - i) / 2;
    while (i < j) {
        while (StrCmp(Text[i], Text[m]) == LESS)
            ++i;
        while (StrCmp(Text[j], Text[m]) == GREATER)
            --j;
        if (i <= j)
            Swap(Text[i], Text[j]);
    }
    if (l < j)
        Sort(l, j);
    if (i > r)
        Sort(i, r);
}

