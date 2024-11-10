#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

// Define register indices for syscall purposes
#define REG_SYS_CALL 2  // $v0 register for syscall number
#define REG_ARG 4       // $a0 register for syscall argument

// Define syscall numbers
#define SYS_CALL_PRINT_INT 1
#define SYS_CALL_EXIT 10
#define SYS_CALL_PRINT_CHAR 11

// Instruction opcodes and function codes
#define OPCODE_ADDI 0x08
#define OPCODE_SYSCALL 0x0C
#define FUNC_ADD 0x20
#define OPCODE_ORI 0x0D
#define OPCODE_LUI 0x0F

// Error messages
#define ERR_INVALID_SYSCALL "IMPS error: invalid syscall number\n"
#define ERR_INVALID_INSTRUCTION "IMPS error: invalid instruction "
#define ERR_EXECUTION_PAST_END "IMPS error: execution past the end of instructions\n"

// Define the structure representing an IMPS file
struct imps_file {
    uint32_t instruction_count;  // Total number of instructions
    uint32_t entry_point;        // Starting point for execution
    uint32_t *instructions;      // Array holding instructions
    uint32_t *debug_offsets;     // Array holding debug info
    uint16_t memory_size;        // Size of memory
    uint8_t *initial_data;       // Initial data for memory
};

// Function prototypes
void load_imps_file(char *path, struct imps_file *executable);
void run_imps(struct imps_file *executable, int trace_mode, char *path);
void display_uint32_in_hex(FILE *stream, uint32_t value);
void display_int32_in_decimal(FILE *stream, int32_t value);

int main(int argc, char *argv[]) {
    // Ensure appropriate usage with optional trace mode
    char *filepath;
    int trace_mode = 0;

    if (argc == 2) {
        filepath = argv[1];
    } else if (argc == 3 && strcmp(argv[1], "-t") == 0) {
        trace_mode = 1;
        filepath = argv[2];
    } else {
        fprintf(stderr, "Usage: imps [-t] <executable>\n");
        exit(1);
    }

    struct imps_file executable = {0};
    load_imps_file(filepath, &executable);
    run_imps(&executable, trace_mode, filepath);

    // Free dynamically allocated memory
    free(executable.debug_offsets);
    free(executable.instructions);
    free(executable.initial_data);

    return 0;
}

// Load an IMPS executable file
void load_imps_file(char *path, struct imps_file *executable) {
    FILE *file = fopen(path, "rb");
    if (!file) {
        perror(path);  
        exit(EXIT_FAILURE);
    }

    // Verify magic number "IMPS" (49 4D 50 53)
    unsigned char magic_number[4];
    fread(magic_number, sizeof(unsigned char), 4, file);
    if (magic_number[0] != 0x49 || magic_number[1] != 0x4D || magic_number[2] != 0x50 || magic_number[3] != 0x53) {
        fclose(file);
        fprintf(stderr, "Invalid IMPS file\n");
        exit(EXIT_FAILURE);
    }

    uint32_t count_inst = 0, start_point = 0;
    uint16_t mem_size = 0;
    uint32_t *inst_arr = NULL, *debug_arr = NULL;
    uint8_t *init_data = NULL;

    // Read instruction count and entry point
    fread(&count_inst, sizeof(uint32_t), 1, file);
    fread(&start_point, sizeof(uint32_t), 1, file);

    // Allocate memory for instructions and debug information
    inst_arr = malloc(count_inst * sizeof(uint32_t));
    debug_arr = malloc(count_inst * sizeof(uint32_t));
    if (!inst_arr || !debug_arr) {
        free(inst_arr);
        free(debug_arr);
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Read instructions
    for (uint32_t i = 0; i < count_inst; ++i) {
        fread(&inst_arr[i], sizeof(uint32_t), 1, file);
    }

    // Read debug offsets
    for (uint32_t i = 0; i < count_inst; ++i) {
        fread(&debug_arr[i], sizeof(uint32_t), 1, file);
    }

    // Read memory size and allocate initial data
    fread(&mem_size, sizeof(uint16_t), 1, file);
    init_data = malloc(mem_size);
    if (!init_data) {
        free(inst_arr);
        free(debug_arr);
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fread(init_data, sizeof(uint8_t), mem_size, file);
    fclose(file);

    // Populate executable structure fields
    executable->instruction_count = count_inst;
    executable->entry_point = start_point;
    executable->memory_size = mem_size;
    executable->instructions = inst_arr;
    executable->debug_offsets = debug_arr;
    executable->initial_data = init_data;
}

// Execute an IMPS program
void run_imps(struct imps_file *executable, int trace_mode, char *path) {
    uint32_t *inst_arr = executable->instructions;
    uint32_t pc = executable->entry_point;
    uint32_t inst_count = executable->instruction_count;
    int32_t regs[32] = {0};  // Initialize 32 registers
    bool is_running = true;

    while (is_running) {
        // Ensure the program counter (PC) is within bounds
        if (pc >= inst_count) {
            fprintf(stderr, ERR_EXECUTION_PAST_END);
            exit(1);
        }

        uint32_t curr_inst = inst_arr[pc++];
        uint32_t opcode = (curr_inst >> 26) & 0x3F;

        if (opcode == 0x00) {  // R-type instruction
            uint32_t func_code = curr_inst & 0x3F;
            if (func_code == FUNC_ADD) {  // ADD instruction
                uint32_t rs = (curr_inst >> 21) & 0x1F;
                uint32_t rt = (curr_inst >> 16) & 0x1F;
                uint32_t rd = (curr_inst >> 11) & 0x1F;
                regs[rd] = regs[rs] + regs[rt];
            } else if (func_code == OPCODE_SYSCALL) {  // SYSCALL
                uint32_t syscall_number = regs[REG_SYS_CALL];
                if (syscall_number == SYS_CALL_PRINT_INT) {
                    printf("%d", regs[REG_ARG]);
                } else if (syscall_number == SYS_CALL_EXIT) {
                    exit(0);
                } else if (syscall_number == SYS_CALL_PRINT_CHAR) {
                    putchar(regs[REG_ARG] & 0xFF);
                } else {
                    fprintf(stderr, ERR_INVALID_SYSCALL);
                    exit(1);
                }
            } else {
                fprintf(stderr, ERR_INVALID_INSTRUCTION);
                display_uint32_in_hex(stderr, curr_inst);
                exit(1);
            }
        } else {  // I-type instruction
            uint32_t rs = (curr_inst >> 21) & 0x1F;
            uint32_t rt = (curr_inst >> 16) & 0x1F;
            int32_t imm = (int16_t)(curr_inst & 0xFFFF);  // Sign-extend

            switch (opcode) {
                case OPCODE_ADDI:
                    regs[rt] = regs[rs] + imm;
                    break;
                case OPCODE_ORI:
                    regs[rt] = regs[rs] | (uint32_t)(imm & 0xFFFF);
                    break;
                case OPCODE_LUI:
                    regs[rt] = (uint32_t)imm << 16;
                    break;
                default:
                    fprintf(stderr, ERR_INVALID_INSTRUCTION);
                    display_uint32_in_hex(stderr, curr_inst);
                    exit(1);
            }
        }

        // Keep register zero set to zero
        regs[0] = 0;
    }
}

// Display a 32-bit integer in hexadecimal
void display_uint32_in_hex(FILE *stream, uint32_t value) {
    fprintf(stream, "0x%08" PRIx32, value);
}

// Display a signed 32-bit integer in decimal
void display_int32_in_decimal(FILE *stream, int32_t value) {
    fprintf(stream, "%" PRIi32, value);
}
