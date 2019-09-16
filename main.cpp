#include <cstdio>
#include <cctype>
#include <cstdlib>

#define STRSIZE 8000

#define LESS -1
#define GREATER 1
#define EQUAL 0

#define ERROR -1
#define EMPTY 0
#define OK 1

#define STRAIGHT 1
#define REVERSED -1

char Buffer[STRSIZE];
int BufIdx = EMPTY;

char *ptr;
char *Text[STRSIZE];
char *TextUnsorted[STRSIZE];
int TextIdx = EMPTY;

int BufEmpty(void);
void PutBuf(const char c);
char GetBuf(void);

int GetLine(char *line, int *len);

void GetText(void);
void PrintText(char *Text[], int TextSize);

void StrCpy(char *a, char *b);
int StrLen(char *a);
int CharCmp(char a, char b);
int StrCmpStraight(char *a, char *b);
int StrCmpReversed(char *a, char *b);
void Swap(char *Text[], int i, int j);

void Sort(int l, int r, int type);

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    GetText();
    Sort(0, TextIdx - 1, STRAIGHT);
    printf("\nStraight Sorted Text:\n");
    PrintText(Text, TextIdx);
    Sort(0, TextIdx - 1, REVERSED);
    printf("\nReverse Sorted Text:\n");
    PrintText(Text, TextIdx);
    printf("\nUnsorted Text:\n");
    PrintText(TextUnsorted, TextIdx);
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

int GetLine(char *line, int *len) {
    char c;
    while (isspace(c = getchar()) && c != '\n' && c != EOF);
    if (c == EOF)
        return ERROR;
    PutBuf(c);
    if (BufEmpty()) {
        *line = '\0', *len = 0;
        return OK;
    }
    while ((c = getchar()) != EOF && c != '\n' || !BufEmpty()) {
        while (!BufEmpty())
            *line++ = GetBuf(), ++*len;
        if (c != EOF && c != '\n')
            *line++ = c, ++*len;
        else
            break;
    }
    *line = '\0', ++*len;
    return OK;
}

void GetText() {
    int len = EMPTY;
    char line[STRSIZE];
    while(GetLine(line, &len) != ERROR) {
        if (len > EMPTY) {
            ptr = (char *)malloc(len);
            len = 0;
            StrCpy(line, ptr);
            Text[TextIdx] = ptr;
            TextUnsorted[TextIdx++] = ptr;
        }
    }
}

void PrintText(char *Text[], int TextSize) {
    for (int i = 0; i < TextSize; ++i)
        printf("%d: %s\n", i + 1, *(Text + i));
    printf("\n");
}

void StrCpy(char *a, char *b) {
    while(*b++ = *a++);
    *b = '\0';
}

int StrLen(char *a) {
    char *a0 = a;
    while (*a++);
    return a - a0 - 1;
}

int CharCmp(char a, char b) {
    if (a >= 'A' && a <= 'Z')
        a += ('a' - 'A');
    if (b >= 'A' && b <= 'Z')
        b += ('a' - 'A');
    return ( a > b ? 1 : a == b ? 0 : -1 );
}

int StrCmpStraight(char *a, char *b) {
    while (CharCmp(*a, *b) == 0) {
        if (*a == '\0')
            return EQUAL;
        ++a, ++b;
    }
    return (CharCmp(*a, *b) == -1 ? LESS : GREATER);
}

int StrCmpReversed(char *a, char *b) {
    a += StrLen(a) - 1;
    b += StrLen(b) - 1;
    while (CharCmp(*a, *b) == 0) {
        if (*a == '\0')
            return EQUAL;
        --a, --b;
    }
    return (CharCmp(*a, *b) == -1 ? LESS : GREATER);
}

void Swap(char *Text[], int i, int j) {
    char *temp = Text[i];
    Text[i] = Text[j];
    Text[j] = temp;
}

void Sort(int l, int r, int type) {
    int last = l;
    if (l >= r)
        return;
    Swap(Text, l, l + (r - l) / 2);
    for (int k = l + 1; k <= r; ++k)
        if (type == STRAIGHT) {
            if (StrCmpStraight(Text[k], Text[l]) == -1)
                Swap(Text, ++last, k);
        } else if (type == REVERSED) {
            if (StrCmpReversed(Text[k], Text[l]) == -1)
                Swap(Text, ++last, k);
        }
    Swap(Text, l, last);
    Sort(l, last - 1, type);
    Sort(last + 1, r, type);
}