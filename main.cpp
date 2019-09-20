// документация
// ассерты

#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <sys/stat.h>

const int MASSIZE = 1e5;

enum { LESS, EQUAL, GREATER };
enum { ERROR, EMPTY, OK };

struct string {
    int len = 0;
    char *line = nullptr;
};

//int GetLine (struct string *str, char *BufIdx, FILE *readfile);
//void GetText (struct string *Text, int *TextIdx, FILE *readfile);
void GetText_v2 (struct string *Text, int *TextIdx, FILE *readfile);
void PrintText (struct string *Text, int TextIdx, FILE *writefile);

int CharCmp (char a, char b);
int StrCmpStraight (struct string a, struct string b);
int StrCmpReversed (struct string a, struct string b);
int StrCmpOriginal (struct string a, struct string b);

void Swap (struct string *Text, int i, int j);
void Sort (struct string *Text, int left, int right, int (*Cmp) (struct string s1, struct string s2));

int main () {
    struct string *Text = (struct string *) calloc (MASSIZE, sizeof (struct string));
    int TextIdx = 0;

    FILE *readfile = fopen ("input.txt", "r");
    //GetText (Text, &TextIdx, readfile);
    GetText_v2 (Text, &TextIdx, readfile);
    fclose (readfile);

    FILE *writefile = fopen("output.txt", "w");
    Sort (Text, 0, TextIdx - 1, StrCmpStraight);
    fprintf (writefile, "____________________\nStraight Sorted Text:\n____________________\n");
    PrintText (Text, TextIdx, writefile);

    Sort (Text, 0, TextIdx - 1, StrCmpReversed);
    fprintf (writefile, "____________________\nReverse Sorted Text:\n____________________\n");
    PrintText (Text, TextIdx, writefile);

    Sort (Text, 0, TextIdx - 1, StrCmpOriginal);
    fprintf (writefile, "____________________\nUnsorted Text:\n____________________\n");
    PrintText (Text, TextIdx, writefile);
    fclose (writefile);

}

/*
int GetLine (struct string *str, char *BufIdx, FILE *readfile) {
    char c = EOF;
    str->line = BufIdx;
    while (isspace (c = fgetc (readfile))) ;
    if (c == EOF)
        return ERROR;
    else if (c == '\n')
        return EMPTY;
    else
        *BufIdx++ = c, str->len++;
    while ( (c = fgetc (readfile)) != EOF && c != '\n') {
        *BufIdx++ = c, str->len++;
    }
    *BufIdx++ = '\0';
    return (c == EOF ? ERROR : str->len == 0 ? EMPTY : OK);
}

void GetText (struct string *Text, int *TextIdx, FILE *readfile) {
    struct stat file_info;
    stat ("input.txt", &file_info);
    assert (readfile != nullptr);
    char *BufIdx = (char *) calloc (file_info.st_size, sizeof (char));
    int res = ERROR;
    struct string str;
    do {
        res = GetLine (&str, BufIdx, readfile);
        BufIdx += str.len + 1;
        if (res != EMPTY)
            Text[*TextIdx] = str, ++*TextIdx;
        str.line = BufIdx, str.len = 0;
    } while (res != ERROR);
}
*/

void GetText_v2 (struct string *Text, int *TextIdx, FILE *readfile) {
    struct stat file_info;
    stat ("input.txt", &file_info);
    char *BufIdx = (char *) calloc (file_info.st_size, sizeof (char));
    fread (BufIdx, sizeof (char), file_info.st_size, readfile);
    int i = 0;
    while ( isspace (*(BufIdx + i)) )
        ++i;
    Text[*TextIdx].line = BufIdx;
    for (; i < file_info.st_size; ++i) {
        if (*(BufIdx + i) == '\n') {
            *(BufIdx + i) = '\0';
            Text[*TextIdx].len = (BufIdx + i) - Text[*TextIdx].line;
            ++*TextIdx, ++i;
            while (isspace (* (BufIdx + i)))
                ++i;
            Text[*TextIdx].line = (BufIdx + i);
        }
    }
}

void PrintText (struct string *Text, int TextIdx, FILE *writefile) {
    for (int i = 0; i < TextIdx; ++i)
        fprintf(writefile, "%s\n", Text[i].line);
}

int CharCmp (char a, char b){
    return (toupper (a) - toupper (b) == 0 ? EQUAL : toupper (a) - toupper (b) > 0 ? GREATER : LESS);
}

int StrCmpStraight (struct string a, struct string b) {
    while (CharCmp (*a.line, *b.line) == EQUAL) {
        if (*a.line == '\0')
            return EQUAL;
        ++a.line, ++b.line;
    }
    return CharCmp (*a.line, *b.line);
}

int StrCmpReversed (struct string a, struct string b) {
    a.line += a.len - 1;
    b.line += b.len - 1;
    while (CharCmp (*a.line, *b.line) == EQUAL) {
        if (*a.line == '\0')
            return EQUAL;
        --a.line, --b.line;
    }
    return CharCmp (*a.line, *b.line);
}

int StrCmpOriginal (struct string a, struct string b) {
    return a.line > b.line;
}

void Swap (struct string *Text, int i, int j) {
    struct string temp = Text[i];
    Text[i] = Text[j];
    Text[j] = temp;
}

void Sort (struct string *Text, int left, int right, int (* Cmp) (struct string s1, struct string s2)) {
    int last = left;
    if (left >= right)
        return;
    Swap (Text, left, left + (right - left) / 2);
    for (int k = left + 1; k <= right; ++k)
        if ( (* Cmp) (Text[k], Text[left]) == LESS)
            Swap (Text, ++last, k);
    Swap (Text, left, last);
    Sort (Text, left, last - 1, Cmp);
    Sort (Text, last + 1, right, Cmp);
}