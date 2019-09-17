// работа с файлами
// документация
// ассерты
// убрать глобальный буфер

#include <cstdio>
#include <cctype>
#include <cstdlib>

const int STRSIZE = 8000;
const int MASSIZE = 1e3;
const int TEXTSIZE = 1e5;

enum { LESS, EQUAL, GREATER };
enum { ERROR, EMPTY, OK };

char *BufStart = (char *)calloc(TEXTSIZE, sizeof(char));
char *BufIdx = BufStart;

struct string {
    int len = 0;
    char *line = BufIdx;
};

int GetLine (struct string *str);

void GetText (struct string *Text, struct string *TextUnsorted, int TextIdx);
void PrintText (struct string *Text, int TextIdx);

int StrLen (char *a);
int CharCmp (char a, char b);
int StrCmpStraight (char *a, char *b);
int StrCmpReversed (char *a, char *b);
void Swap (struct string *Text, int i, int j);

void Sort (struct string *Text, int left, int right, int (*Cmp) (char *s1, char *s2));

int main () {
    freopen ("input_test.txt", "r", stdin);
    freopen ("output.txt", "w", stdout);

    struct string *Text = (struct string *) calloc (MASSIZE, sizeof (struct string));
    struct string *TextUnsorted = (struct string *) calloc (MASSIZE, sizeof (struct string));
    int TextIdx = 0;

    GetText (Text, TextUnsorted, TextIdx);
    PrintText (Text, TextIdx);
    /*
    Sort (Text, 0, TextIdx - 1, StrCmpStraight);
    printf("\nStraight Sorted Text:\n");
    PrintText (Text, TextIdx);

    Sort (Text, 0, TextIdx - 1, StrCmpReversed);
    printf ("\nReverse Sorted Text:\n");
    PrintText (Text, TextIdx);

    printf ("\nUnsorted Text:\n");
    PrintText (TextUnsorted, TextIdx);
     */
}

int GetLine (struct string *str) {
    char c = EOF;
    *str->line = *BufIdx;
    while ( (c = getchar ()) != EOF && c != '\n') {
        *BufIdx++ = c, str->len++;
    }
    *BufIdx++ = '\0';
    return (str->len == 0 ? EMPTY : c == EOF ? ERROR : OK);
}

void GetText (struct string *Text, struct string *TextUnsorted, int TextIdx) {
    int res = ERROR;
    struct string str;
    do {
        res = GetLine (&str);
        if (res != EMPTY)
            Text[TextIdx] = str, TextUnsorted[TextIdx] = str, ++TextIdx;
        str.line = BufIdx, str.len = 0;
    } while (res != ERROR);
}

void PrintText (struct string *Text, int TextIdx) {
    for (int i = 0; i < TextIdx; ++i)
        printf ("%s\n", Text[i].line);
}

int StrLen (char *a) {
    char *a0 = a;
    while (*a++) ;
    return a - a0 - 1;
}

int CharCmp (char a, char b){
    return toupper (a) - toupper (b);
}

int StrCmpStraight (char *a, char *b) {
    while (CharCmp (*a, *b) == 0) {
        if (*a == '\0')
            return EQUAL;
        ++a, ++b;
    }
    return (CharCmp (*a, *b) == -1 ? LESS : GREATER);
}

int StrCmpReversed (char *a, char *b) {
    a += StrLen (a) - 1;
    b += StrLen (b) - 1;
    while (CharCmp (*a, *b) == 0) {
        if (*a == '\0')
            return EQUAL;
        --a, --b;
    }
    return (CharCmp (*a, *b) == -1 ? LESS : GREATER);
}

void Swap (struct string *Text, int i, int j) {
    struct string temp = Text[i];
    Text[i] = Text[j];
    Text[j] = temp;
}

void Sort (struct string *Text, int left, int right, int (* Cmp) (char *s1, char *s2)) {
    int last = left;
    if (left >= right)
        return;
    Swap (Text, left, left + (right - left) / 2);
    for (int k = left + 1; k <= right; ++k)
            if ((* Cmp)(Text[k].line, Text[left].line) == -1)
                Swap (Text, ++last, k);
    Swap (Text, left, last);
    Sort (Text, left, last - 1, Cmp);
    Sort (Text, last + 1, right, Cmp);
}
