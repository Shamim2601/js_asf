#include <stdlib.h>

#include <stdint.h>

#include <stdio.h>

#include <inttypes.h>

#include <limits.h>

#include <stdbool.h>

#include <string.h>





// Do not rename or modify this struct! It's directly used

// by the subset 1 autotests.



// defines

#define REG_V0 2

#define REG_A0 4


#define SYSCALL_PRINT_INT 1

#define SYSCALL_EXIT 10

#define SYSCALL_PRINT_CHAR 11


#define OPCODE_ADDI 0x08

#define OPCODE_SYSCALL 0x0C

#define OPCODE_ADD 0x20

#define OPCODE_ORI 0x0D

#define OPCODE_LUI 0x0F

#define OPCODE_CLO 0x51

#define OPCODE_CLZ 0x50

#define OPCODE_ADDU 0x21

#define OPCODE_ADDIU 0x09

#define OPCODE_SPECIAL2 0x1C  // Opcode for special2 instructions

#define FUNCT_MUL 0x02        // Funct code for MUL


#define ERROR_BAD_SYSCALL "IMPS error: bad syscall number\n"

#define ERROR_BAD_INSTRUCTION "IMPS error: bad instruction "

#define ERROR_EXECUTION_PAST_END "IMPS error: execution past the end of instructions\n"



struct imps_file {

    uint32_t num_instructions;

    uint32_t entry_point;

    uint32_t *instructions;

    uint32_t *debug_offsets;

    uint16_t memory_size;

    uint8_t *initial_data;

};



void read_imps_file(char *path, struct imps_file *executable);

void execute_imps(struct imps_file *executable, int trace_mode, char *path);

void print_uint32_in_hexadecimal(FILE *stream, uint32_t value);

void print_int32_in_decimal(FILE *stream, int32_t value);



int main(int argc, char *argv[]) {



    // Do NOT CHANGE this function

    // put your code in read_imps_file, execute_imps and your own functions



    char *pathname;

    int trace_mode = 0;



    if (argc == 2) {

        pathname = argv[1];

    } else if (argc == 3 && strcmp(argv[1], "-t") == 0) {

        trace_mode = 1;

        pathname = argv[2];

    } else {

        fprintf(stderr, "Usage: imps [-t] <executable>\n");

        exit(1);

    }



    struct imps_file executable = {0};

    read_imps_file(pathname, &executable);



    execute_imps(&executable, trace_mode, pathname);



    free(executable.debug_offsets);

    free(executable.instructions);

    free(executable.initial_data);



    return 0;

}



void read_imps_file(char *path, struct imps_file *executable) {


    FILE *file = fopen(path, "rb");

    if (!file) {

        perror(path);  

        exit(EXIT_FAILURE);

    }



    // Verify magic number

    unsigned char magic_number[4];

    fread(magic_number, sizeof(unsigned char), 4, file);

    if (magic_number[0] != 0x49 || magic_number[1] != 0x4D || magic_number[2] != 0x50 || magic_number[3] != 0x53) {

        fclose(file);

        fprintf(stderr, "Invalid IMPS file\n");

        exit(EXIT_FAILURE);

    }


    // Local temporary storage variables

    uint32_t ins_cnt = 0, start_point = 0;

    uint16_t mem_size = 0;

    uint32_t *instruction = NULL, *debug_marker = NULL;

    uint8_t *data_init = NULL;



    // Read num_instructions (32-bit)

    fread(&ins_cnt, sizeof(uint32_t), 1, file);



    // Read entry_point (32-bit)

    fread(&start_point, sizeof(uint32_t), 1, file);



    // Allocate arrays for instructions and debug_offsets

    instruction = malloc(ins_cnt * sizeof(uint32_t));

    debug_marker = malloc(ins_cnt * sizeof(uint32_t));

    if (!instruction || !debug_marker) {

        free(instruction);

        free(debug_marker);

        fclose(file);

        exit(EXIT_FAILURE);

    }



    // Read instructions

    for (uint32_t i = 0; i < ins_cnt; ++i) {

        instruction[i] = 0;

        fread(&instruction[i], sizeof(uint32_t), 1, file);

    }



    // Read debug_offsets

    for (uint32_t i = 0; i < ins_cnt; ++i) {

        debug_marker[i] = 0;

        fread(&debug_marker[i], sizeof(uint32_t), 1, file);

    }



    // Read memory_size (16-bit)

    fread(&mem_size, sizeof(uint16_t), 1, file);



    // Allocate initial_data

    data_init = malloc(mem_size);

    if (!data_init) {

        free(instruction);

        free(debug_marker);

        fclose(file);

        exit(EXIT_FAILURE);

    }



    fread(data_init, sizeof(uint8_t), mem_size, file);



    // Set values in executable

    fclose(file);

    executable->num_instructions = ins_cnt;

    executable->entry_point = start_point;

    executable->memory_size = mem_size;

    executable->instructions = instruction;

    executable->debug_offsets = debug_marker;

    executable->initial_data = data_init;





    // Hints:

    // * Open the file with fopen (using path)

    //      * Check that the file succesfully opened

    // * Read in the first 4 bytes (e.g. using fgetc)

    //     checking that they are  0x49, 0x4d, 0x50, 0x53

    // * Read in num_instructions (see last hint)

    // * Read in entry_point  (see last hint)

    //  malloc space for an array of uint32_t's with length num_instructions

    // * Loop num_instructions times, reading in an instruction

    //     and placing the result in your instructions array

    // * Allocate and read in the debug_offsets in the same way as the

    //     instructions

    // * Read in the memory_size (be careful, it's only 2 bytes)

    // * Allocate and read in the initial_data based on memory_size

    // * Close the file

    //

    // * Don't forget to store value in all 6 fields of the executable struct

    //

    // * We recommend you write a function which reads in a single little

    //   endian 32 bit integer from a file. One way to do this is to call fgetc

    //   four times, and then assemble the bytes together using << and |

}


int count_leading_ones(uint32_t value) {
    int count = 0;
    for (int i = 31; i >= 0; --i) {
        if ((value & (1 << i)) == 0) break;
        count++;
    }
    return count;
}

int count_leading_zeros(uint32_t value) {
    int count = 0;
    for (int i = 31; i >= 0; --i) {
        if ((value & (1 << i)) != 0) break;
        count++;
    }
    return count;
}



// Executa an IMPS program

void execute_imps(struct imps_file *executable, int trace_mode, char *path) {



    // Put your code here

    uint32_t *instructions = executable->instructions;

    uint32_t pc = executable->entry_point;

    uint32_t num_instructions = executable->num_instructions;

    int32_t registers[32] = {0};  // Initialize 32 registers to 0

    bool running = true;



    while (running) {

        // Check if the PC is out of bounds

        if (pc >= num_instructions) {

            fprintf(stderr, ERROR_EXECUTION_PAST_END);

            exit(1);

        }



        // Fetch instruction

        uint32_t instruction = instructions[pc++];



        // Decode the instruction

        uint32_t opcode = (instruction >> 26) & 0x3F;



        if (opcode == 0x00) {  // R-type instruction

            uint32_t funct = instruction & 0x3F;

            uint32_t rs = (instruction >> 21) & 0x1F;

            uint32_t rt = (instruction >> 16) & 0x1F;

            uint32_t rd = (instruction >> 11) & 0x1F;

            if (funct == OPCODE_ADD) {  // ADD instruction

                registers[rd] = registers[rs] + registers[rt];

            }
            else if (funct == OPCODE_ADDU) {
                registers[rd] = (uint32_t)registers[rs] + (uint32_t)registers[rt];
            }
             else if (funct == OPCODE_SYSCALL) {  // SYSCALL

                uint32_t syscall_num = registers[REG_V0];

                if (syscall_num == SYSCALL_PRINT_INT) {

                    printf("%d", registers[REG_A0]);

                } else if (syscall_num == SYSCALL_EXIT) {

                    exit(0);

                } else if (syscall_num == SYSCALL_PRINT_CHAR) {

                    putchar(registers[REG_A0] & 0xFF);

                } else {

                    fprintf(stderr, ERROR_BAD_SYSCALL);

                    exit(1);

                }
            }
            else if (funct == OPCODE_CLO) {

                registers[rd] = count_leading_ones(registers[rs]);
            } 
            else if (funct == OPCODE_CLZ) {

                registers[rd] = count_leading_zeros(registers[rs]);
            }else {

                fprintf(stderr, ERROR_BAD_INSTRUCTION);

                fprintf(stderr, "0x%08x\n", instruction);

                exit(1);
            }

        }else if (opcode == OPCODE_SPECIAL2) {  // special2 opcode
            uint32_t rs = (instruction >> 21) & 0x1F;
            uint32_t rt = (instruction >> 16) & 0x1F;
            uint32_t rd = (instruction >> 11) & 0x1F;
            uint32_t funct = instruction & 0x3F;

            if (funct == FUNCT_MUL) {  // MUL instruction
                registers[rd] = registers[rs] * registers[rt];  // Perform the multiplication
            }
        }
         else {  // I-type instruction

            uint32_t rs = (instruction >> 21) & 0x1F;

            uint32_t rt = (instruction >> 16) & 0x1F;

            int32_t imm = (int16_t)(instruction & 0xFFFF);  // Sign-extend immediate



            switch (opcode) {

                case OPCODE_ADDI:

                    registers[rt] = registers[rs] + imm;

                    break;

                case OPCODE_ADDIU:

                    registers[rt] = registers[rs] + (uint32_t)imm;

                    break;

                case OPCODE_ORI:

                    registers[rt] = registers[rs] | (uint32_t)(imm & 0xFFFF);

                    break;

                case OPCODE_LUI:

                    registers[rt] = (uint32_t)imm << 16;

                    break;

                default:

                    fprintf(stderr, ERROR_BAD_INSTRUCTION);

                    fprintf(stderr, "0x%08x\n", instruction);

                    exit(1);

            }

        }



        // Ensure $zero register remains 0

        registers[0] = 0;

    }



    // Note: you won't need to use the trace_mode or path arguments

    //       until you get to subset 4.

}





//

// Put your functions here

//

// Count leading zeros







// Printing out exact-width integers in a portable way is slightly tricky,

// since we can't assume that a uint32_t is an unsigned int or that a

// int32_t is an int. So we can't just use %x or %d. A solution is to use

// printf format specifiers from the <inttypes.h> header. The following two

// functions are provided for your convenience so that you just call them

// without worring about <inttypes.h>, although you don't have to use use them.



// Print out a 32 bit integer in hexadecimal, including the leading 0x.

//

// @param stream The file stream to output to.

// @param value The 32 bit integer to output.

void print_uint32_in_hexadecimal(FILE *stream, uint32_t value) {

    fprintf(stream, "0x%08" PRIx32, value);

}



// Print out a signed 32 bit integer in decimal.

//

// @param stream The file stream to output to.

// @param value The 32 bit integer to output.

void print_int32_in_decimal(FILE *stream, int32_t value) {

    fprintf(stream, "%" PRIi32, value);

}
