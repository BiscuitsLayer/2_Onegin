// документация
//valgrind
//поставить линукс (etcher/rufus)
//Страуструп

#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <locale.h>
#include <cassert>
#include <sys/stat.h>

const char INPUTFILE [] = "input.txt";
const char OUTPUTFILE [] = "output.txt";

enum { LESS, EQUAL, GREATER };

struct string {
    int len = 0;
    char *line = nullptr;
};

//int GetLine (struct string *str, char *BufIdx, FILE *readfile);
//void GetText (struct string *Text, int *TextIdx, FILE *readfile);
//void GetText_v2 (struct string *Text, unsigned int *TextIdx, FILE *readfile);
int GetTextSize (FILE *readfile, char **TextStart, int *TextSize);
void GetText_v3 (struct string *Text, char *TextStart, int TextSize, unsigned int *TextIdx, FILE *readfile);
void PrintText (const struct string *Text, unsigned int TextIdx, FILE *writefile);

int CharCmp (char a, char b);
int StrCmpStraight (struct string a, struct string b);
int StrCmpReversed (struct string a, struct string b);
int StrCmpOriginal (struct string a, struct string b);

void Swap (struct string *Text, int i, int j);
void Sort (struct string *Text, int left, int right, int (*Cmp) (struct string s1, struct string s2));

int main () {
    _wsetlocale(LC_ALL, L"Russian");
    setlocale(LC_ALL, "Russian");

    FILE *readfile = fopen (INPUTFILE, "rb");
    assert (readfile != nullptr);

    char *TextStart = nullptr;
    int TextSize = 0;

    unsigned int TextIdx = GetTextSize(readfile, &TextStart, &TextSize);
    struct string *Text = (struct string *) calloc (TextIdx + 1, sizeof (struct string));
    GetText_v3(Text, TextStart, TextSize, &TextIdx, readfile);

    fclose (readfile);

    FILE *writefile  = fopen(OUTPUTFILE, "w");
    assert (writefile != nullptr);

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
    free(Text[0].line);
    free(Text);
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
    stat (INPUTFILE, &file_info);
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

void GetText_v2 (struct string *Text, unsigned int *TextIdx, FILE *readfile) {
    assert (Text != nullptr);
    assert (TextIdx != nullptr);
    assert (readfile != nullptr);

    struct stat file_info = {};
    stat (INPUTFILE, &file_info);

    char *BufIdx = (char *) calloc (file_info.st_size, sizeof (char));
    fread (BufIdx, sizeof (char), file_info.st_size, readfile);

    int i = 0;
    while ( isspace (*(BufIdx + i)) )
        ++i;

    Text[*TextIdx].line = BufIdx;
    for (; i < file_info.st_size; ++i) {
        if (*(BufIdx + i) == '\n') {
            *(BufIdx + i) =  '\0';

            Text[*TextIdx].len = (BufIdx + i) - Text[*TextIdx].line;
            ++*TextIdx, ++i;

            while (isspace (* (BufIdx + i)))
                ++i;

            Text[*TextIdx].line = (BufIdx + i);
        }
    }
}
 */

int GetTextSize (FILE *readfile, char **TextStart, int *TextSize) {
    struct stat file_info = {};
    stat (INPUTFILE, &file_info);

    char *BufIdx = (char *) calloc (file_info.st_size + 1, sizeof (char));
    *(BufIdx + file_info.st_size + 2) = '\0';
    *TextStart = BufIdx;
    *TextSize = file_info.st_size;

    fread (BufIdx, sizeof (char), file_info.st_size, readfile);

    int i = 0;
    while (isspace (* (BufIdx + i)) || *(BufIdx + i) == '\n' || *(BufIdx + i) == '\0' || *(BufIdx + i) == '\r')
        ++i;

    unsigned int TextIdx = 0;
    for (; i < file_info.st_size; ++i) {
        if (*(BufIdx + i) == '\n' || *(BufIdx + i) == '\r') {
            *(BufIdx + i) = '\0';
            ++TextIdx;

            while (isspace (* (BufIdx + i)) || *(BufIdx + i) == '\n' || *(BufIdx + i) == '\0' || *(BufIdx + i) == '\r') {
                ++i;
            }
        }
    }

    return TextIdx;
}

void GetText_v3 (struct string *Text, char *TextStart, int TextSize, unsigned int *TextIdx, FILE *readfile) {
    assert (Text != nullptr);
    assert (TextIdx != nullptr);
    assert (readfile != nullptr);

    char *BufIdx = TextStart;
    *TextIdx = 0;

    int i = 0;
    while (isspace (* (BufIdx + i)) || *(BufIdx + i) == '\n' || *(BufIdx + i) == '\0' || *(BufIdx + i) == '\r')
        ++i;

    Text[*TextIdx].line = (BufIdx + i);
    for (; i < TextSize; ++i) {
        if (*(BufIdx + i) == '\0') {

            Text[*TextIdx].len = (BufIdx + i) - Text[*TextIdx].line;
            ++*TextIdx, ++i;

            while (isspace (* (BufIdx + i)) || *(BufIdx + i) == '\n' || *(BufIdx + i) == '\0' || *(BufIdx + i) == '\r')
                ++i;

            Text[*TextIdx].line = (BufIdx + i);
        }
    }
}

void PrintText (const struct string *Text, unsigned int TextIdx, FILE *writefile) {
    assert (Text != nullptr);
    assert (writefile != nullptr);

    for (int i = 0; i < TextIdx; ++i)
        fprintf(writefile, "%s\n", Text[i].line);
}

int CharCmp (char a, char b){
    return (toupper (a) - toupper (b) == 0 ? EQUAL : toupper (a) - toupper (b) > 0 ? GREATER : LESS);
}

int StrCmpStraight (struct string a, struct string b) {
    assert (a.len != 0);
    assert (b.len != 0);
    assert (a.line != nullptr);
    assert (b.line != nullptr);

    while (CharCmp (*a.line, *b.line) == EQUAL) {
        if (*a.line == '\0')
            return EQUAL;
        ++a.line, ++b.line;
    }

    return CharCmp (*a.line, *b.line);
}

int StrCmpReversed (struct string a, struct string b) {
    assert (a.len != 0);
    assert (b.len != 0);
    assert (a.line != nullptr);
    assert (b.line != nullptr);

    a.line += a.len - 1;
    b.line += b.len - 1;

    while (CharCmp (*a.line, *b.line) == EQUAL) {
        while (a.len-- && !isalnum (*a.line)) a.line--;
        while (b.len-- && !isalnum (*b.line)) b.line--;

        if (*a.line == '\0')
            return EQUAL;
        --a.line, --b.line;
    }

    return CharCmp (*a.line, *b.line);
}

int StrCmpOriginal (struct string a, struct string b) {
    assert (a.len != 0);
    assert (b.len != 0);
    assert (a.line != nullptr);
    assert (b.line != nullptr);

    return a.line > b.line;
}

void Swap (struct string *Text, int i, int j) {
    assert (Text != nullptr);

    struct string temp = Text[i];
    Text[i] = Text[j];
    Text[j] = temp;
}

void Sort (struct string *Text, int left, int right, int (* Cmp) (struct string s1, struct string s2)) {
    assert (Text != nullptr);
    assert (Cmp != nullptr);

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