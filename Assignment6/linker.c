#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* symbol table linked-list */
typedef struct nament {
    char name[26];
    int addr;
    struct nament *next;
} SYMTABENTRY;

int get_sym_val(char*);
void add_symbol(char*, int);
void print_first_pass(void);
void append_table(void);
void generate_code(void);

SYMTABENTRY *symtab = NULL;
FILE *p1, *p2;
char cstr_12[13];

int main(int argc, char *argv[]) {
    int i, start, pc_offset = 0, pc = 0;
    int linum = 0, object_file = 0;
    int line_number, new_pc;
    char instruction[18];
    char symbol[26];

    // check for -o option
    if (argc > 1 && (strcmp(argv[1], "-o") == 0)) { object_file = 1; }
    
    // set index for first object file argument
    if (object_file) { start = 2; }
    else { start = 1; }

    p1 = fopen("/tmp/passone", "w+");
    unlink("/tmp/passone");

    // read each of the object files
    for (i = start; i < argc; ++i) {
        if ((p2 = fopen(argv[i], "r")) == NULL) {
            printf("ERROR: cannot open file %s\n", argv[i]);
            exit(6);
        }
        // scan in each object file's instructions
        while (fscanf(p2, "%d %s", &pc, instruction) != EOF) {
            if (pc == 4096) { break; }  // end of available mic1 memory space
            new_pc = pc + pc_offset;
            symbol[0] = '\0';
            if (instruction[0] == 'U') {
                fscanf(p2, "%s", symbol);
            }
            // build single consolidated file
            fprintf(p1, "  %d  %s  %s\n", new_pc, instruction, symbol);
        }
        // add new symbol to symbol table
        while (fscanf(p2, "%s %d", symbol, &line_number) != EOF) {
            add_symbol(symbol, line_number + pc_offset);
        }
        pc_offset = new_pc + 1;     // adjust pc offset for next object file
        fclose(p2);
    }

    // -o option creates an unresolved consolidated object file
    if (object_file) {
        print_first_pass();
        append_table();
        return 0;
    }
    generate_code();
    return 0;
}

/* returns the value (address) of the given symbol */
int get_sym_val(char *symbol) {
    int i, j;
    struct nament *element, *list;

    for (list = symtab; list != (struct nament *)0; list = list->next) {
        if (strcmp(list->name, symbol) == 0) {
            return (list->addr);
        }
    }
    return -1;
}

/* adds a symbol to the symbol table */
void add_symbol(char *symbol, int addr) {
    struct nament *element = malloc(sizeof(struct nament));
    strcpy(element->name, symbol);
    element->addr = addr;
    element->next = symtab;
    symtab = element;
}

/* prints the contents scanned from each object file */
void print_first_pass(void) {
    char inbuf[81];

    rewind(p1);
    while (fgets(inbuf, 80, p1) != NULL) {
        printf("  %s", inbuf);
    }
}

/* prints the symbol table for all object files */
void append_table(void) {
    struct nament *list;

    printf("  %d %s\n", 4096, "x");
    for (list = symtab; list != NULL; list = list->next) {
        printf("    %-25s %4d\n", list->name, list->addr);
    }
}

/* generates the code for a fully resolved, single executable file */
void generate_code(void) {
    char instruction[18];
    int old_pc = 0;
    int pc, mask, sym_val, i, j, diff;
    char symbol[26];

    rewind(p1);

    while(fscanf(p1, "%d %s", &pc, instruction) != EOF) {
        if ((diff = pc - old_pc) > 1) {
            for (j = 1; j < diff; j++) {
                printf("1111111111111111\n");
            }
        }
        old_pc = pc;

        if (instruction[0] == 'U') {
            fscanf(p1, "%s", symbol);
            if ((sym_val = get_sym_val(symbol)) == -1) {
                fprintf(stderr, "no symbol in symbol table: %s\n", symbol);
                exit(27);
            }

            for (i = 0; i < 12; i++) {
                cstr_12[i] = '0';
            }
            cstr_12[12] = '\0';

            mask = 2048;
            for (i = 0; i < 12; i++) {
                if (sym_val & mask) {
                    cstr_12[i] = '1';
                }
                mask >>= 1;
            }
            for (i = 0; i < 12; i++) {
                instruction[i+5] = cstr_12[i];
            }
            printf("%s\n", &instruction[1]);
        } else {
            printf("%s\n", instruction);
        }
    }
    fclose(p1);
}
