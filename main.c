#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "head.h"

#define MAX_LEN 1024
#define BUF_SIZE 100
/*
int main(int arg, char **argv)
{
    FILE *f;
    while(*++argv != NULL)
    {
        f = fopen(*argv, "a");
        if (f == NULL)
        {
            perror(*argv);
            getchar();
            continue;
        }
        fputc('a', f);
        if (fclose(f) != 0)
        {
            perror("fclose");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}*/

int main(int arg, char **argv)
{
    char *faddr;
    char *fwaddr;
    faddr = "d:\\a.jpg";
    fwaddr = "d:\\b.jpg";
    FILE *output = fopen(faddr, "rb");
    FILE *input = fopen(fwaddr, "wb");

    char buffer[BUFSIZ];

    setvbuf(output, buffer, _IOFBF, BUFSIZ);
    if ( output == NULL )
    {
        perror(faddr);
        exit(EXIT_FAILURE);
    }
    if (input == NULL)
    {
        printf("file input doesn't exits");
    }
    copy_file_binary(output, input);

    if (fclose(input) != 0 || fclose(output) != 0)
    {
        perror("fclose");
        exit(EXIT_FAILURE);
    }
    rename("d:\\b.jpg", "d:\\c.jpg");
    printf("write the file success!!!\n");
    return EXIT_SUCCESS;
}

int read_int()
{
    int value = 0;
    int ch;
    while((ch = getchar()) != EOF && isdigit(ch))
    {
        value *= 10;
        value += ch - '0';
    }
    ungetc(ch, stdin);
    return value;
}

void print_file(char *addr)
{
    FILE *f;
    f = fopen(addr, "a");
    if (f == NULL)
    {
        perror(addr);
        exit(EXIT_FAILURE);
    }
//    char *c = malloc(sizeof (int));
    char *c = "abc\ndef\n";
//    fgets(c, 100, f);
//    printf("%s", c);

    fputs(c, f);
    printf("success write");

//    while (fgets(c, 3, f) != NULL)
//    {
//        printf("%s", c);
//    }
    free(c);
}


void file_copy(char *from, char *to)
{
    FILE *f = fopen(from, "r");
    FILE *t = fopen(to, "w");
    if (f == NULL || t == NULL)
    {
        printf("from : %s, to : %s", from, to);
        exit(EXIT_FAILURE);
    }
    char *c = malloc(sizeof (int));
    while (fgets(c, MAX_LEN, f) != NULL)
    {
        fputs(c, t);
    }
    printf("success write!!");
    if (fclose(f) != 0 || fclose(t) != 0)
    {
        perror("file close fail");
        exit(EXIT_FAILURE);
    }
    free(c);
}

void function(FILE *f)
{
    int a, b, c, d, e;
    char buffer[BUF_SIZE];
    while( fgets(buffer, BUF_SIZE, f) != NULL )
    {
        if (sscanf(buffer, "%d %d %d %d %d", &a, &b, &c, &d, &e) != 5)
        {
            fprintf(stderr, "bad input skipped: %s", buffer);
            continue;
        }
        printf("%d %d %d %d %d", a, b, c, d, e);
    }
}

void copy_file_binary(FILE *output, FILE *input)
{
    char *buffer = malloc(sizeof(char) * MAX_LEN);
//    char *buffer[MAX_LEN];  或者以这种形式
    size_t value;
    while(( value = fread(buffer, sizeof(char), MAX_LEN, output)) != 0)
    {
        fwrite(buffer, sizeof(char), value, input);
        fflush(input);
    }
    free(buffer);
}
