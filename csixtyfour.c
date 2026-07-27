#include <stdio.h>
#include <stdint.h>

// RAM AND ROM 
#define ROM_SIZE 20480
#define RAM_SIZE 65536

// FLOPPY DISK SUPPORT 
#define SECTOR_COUNT 683
#define SECTOR_SIZE 256
#define ERROR_INFO_SIZE 1

// CPU CLOCK
int machine_cycle_counter = 0;
// CPU CLOCK 

// REGISTERS
uint8_t processor_status_register = 0;
// REGISTERS


// FULL OF INSTRUCTION TABLE

enum OpcodeTable {
	OPCODE_BRK = 0x00, // 1 bytes, 7 cycles 
	OPCODE_NOP = 0xEA, // 1 bytes, 2 cycles 
	OPCODE_BPL = 0x10, // 2 bytes, 2 cycles 
	OPCODE_JSR = 0x20, // 3 bytes, 6 cycles
	OPCODE_BMI = 0x30, // 2 bytes, 2 cycles 
	OPCODE_RTI = 0x40, // 1 bytes, 6 cycles 
	OPCODE_BVC = 0x50, // 2 bytes, 2 cycl
	OPCODE_RTS = 0x60, // 1 bytes, 6 cycles 
	OPCODE_BVS = 0x70, // 2 bytes, 2 cycles 
	OPCODE_BCC = 0x90, // 2 bytes, 2 cycles 
	OPCODE_CLC = 0x18, // 1 bytes 2 cycles
	OPCODE_PLP = 0x28, // 1 bytes 4 cycles
	OPCODE_SEC = 0x38, // 1 bytes 2 cycles
	OPCODE_PHA = 0x48, // 1 bytes 3 cycles
	OPCODE_CLI = 0x58, // 1 bytes 2 cycles 
	OPCODE_PLA = 0x68, // 1 bytes 4 cycles
	OPCODE_SEI = 0x78, // 1 bytes 2 cycles 
	OPCODE_DEY = 0x88, // 1 bytes 2 cycles 
	OPCODE_TYA = 0x98, // 1 bytes 2 cycles
	OPCODE_TXA = 0x8A, // 1 bytes 2 cycles
	OPCODE_TAY = 0xA8, // 1 bytes 2 cycles
	OPCODE_TAX = 0xAA, // 1 bytes 2 cycles
	OPCODE_TSX = 0xBA, // 1 bytes 2 cycles 
	OPCODE_DEX = 0xCA, // 1 bytes 2 cycles
	OPCODE_ARR = 0x6B, // 2 bytes 2 cycles
	OPCODE_CLV = 0xB8, // 1 bytes 2 cycles
	OPCODE_INY = 0xC8, // 1 bytes 2 cycles
	OPCODE_CLD = 0xD8, // 1 bytes 2 cycles 
	OPCODE_INX = 0xE8, // 1 bytes 2 cycles 
	OPCODE_SED = 0xF8, // 1 bytes 2 cycles 
	OPCODE_BEQ = 0xF0, // 2 bytes, 2 cycles
	OPCODE_PHP = 0x08, // 1 bytes, 3 cycles
	OPCODE_SBX = 0xCB, // 2 bytes 2 cycles
	OPCODE_TXS = 0x94, // 1 bytes 2 cycles
	

	// JMP
	OPCODE_JMP_ABS = 0x4C, // 3 bytes 3 cycles
	OPCODE_JMP_IND = 0x6C, // 3 bytes 5 cycles
	// JMP

		
	//LDY 
	OPCODE_LDY_IMM = 0xA0, // 2 bytes, 2 cycles 
	OPCODE_LDY_ABS = 0xAC, // 3 bytes, 4 cycles
	OPCODE_LDY_ABSX = 0xBC, // 3 bytes, 4 cycles 
	OPCODE_LDY_ZP = 0xA4, // 2 bytes, 3 cycles 
	OPCODE_LDY_ZPX = 0xB4, // 2 bytes, 4 cycles 
	//LDY
	OPCODE_BCS = 0xB0, // 2 bytes, 2 cycles 
	//CPY
	OPCODE_CPY_IMM = 0xC0, // 2 bytes, 2 cycles 
	OPCODE_CPY_ABS = 0xCC, // 3 bytes, 4 cycles 
	OPCODE_CPY_ZP = 0xC4, // 2 bytes, 3 cycles
	//CPY
	OPCODE_BNE = 0xD0, // 2 bytes, 2 cycles 
	//CPX
	OPCODE_CPX_IMM = 0xE0, // 2 bytes, 2 cycles 
	OPCODE_CPX_ABS = 0xEC, // 3 bytes, 4 cycles 
	OPCODE_CPX_ZP = 0xE4, // 2 bytes, 3 cycles
	//CPX

	// INC 
	OPCODE_INC_ABS = 0xEE, // 3 bytes, 6 cycles 
	OPCODE_INC_ABSX = 0xFE, // 3 bytes, 7 cycles 
	OPCODE_INC_ZP = 0xE6, // 2 bytes, 5 cycles
	OPCODE_INC_ZPX = 0xF6,// 2 bytes, 6 cycles 
	// INC

	// STY
	OPCODE_STY_ABS = 0x84, // 2 bytes, 3 cycles 
	OPCODE_STY_ZP = 0x94, // 2 bytes, 4 cycles
	OPCODE_STY_ZPX = 0x8C,// 3 bytes, 4 cycles 
	// STY

	// DEC 
	OPCODE_DEC_ABS = 0xCE, // 3 bytes, 6 cycles 
	OPCODE_DEC_ABSX = 0xDE, // 3 bytes, 7 cycles 
	OPCODE_DEC_ZP = 0xC6, // 2 bytes, 5 cycles
	OPCODE_DEC_ZPX = 0xD6,// 2 bytes, 6 cycles 
	// DEC
	
	// STX
	OPCODE_STX_ABS = 0x8E, // 3 bytes, 4 cycles 
	OPCODE_STX_ZP = 0x86, // 2 bytes, 3 cycles 
	OPCODE_STX_ZPY = 0x96, // 2 bytes, 4 cycles
	// STX
	
	// SAX
	OPCODE_SAX_ABS = 0x8F, // 3 bytes 4 cycles
	OPCODE_SAX_ZP = 0x87, // 2 bytes 3 cycles 
	OPCODE_SAX_ZPY = 0x97, // 2 bytes 4 cycles
	OPCODE_SAX_INX = 0x83, // 2 bytes 6 cycles
	// SAX
	
	// LDX
	OPCODE_LDX_IMM = 0xA2, // 2 bytes, 2 cycles 
	OPCODE_LDX_ABS = 0xA6, // 2 bytes, 3 cycles 
	OPCODE_LDX_ABSY = 0xB6, // 3 bytes, 4 cycles
	OPCODE_LDX_ZP = 0xAE, // 3 bytes, 4 cycles 
	OPCODE_LDX_ZPY = 0xBE, // 3 bytes, 4 cycles 
	// LDX


	// GROUP OF BIG INSTRUCTIONS
	
	// ORA
	OPCODE_ORA_IMM = 0x09, // 2 bytes, 2 cycles 
	OPCODE_ORA_ABS = 0x0D, // 3 bytes, 4 cycles 
	OPCODE_ORA_ABSX = 0x1D, // 3 bytes, 4 cycles
	OPCODE_ORA_ABSY = 0x19, // 3 bytes, 4 cycles
	OPCODE_ORA_ZP = 0x05, // 2 bytes, 3 cycles 
	OPCODE_ORA_ZPX = 0x15, // 2 bytes, 4 cycles 
	OPCODE_ORA_INX = 0x01, // 2 bytes, 6 cycles 
	OPCODE_ORA_IXY = 0x11, // 2 bytes, 5 cycles 
	
	
	// AND 
	OPCODE_AND_IMM = 0x29, // 2 bytes, 2 cycles 
	OPCODE_AND_ABS = 0x2D, // 3 bytes, 4 cycles 
	OPCODE_AND_ABSX = 0x3D, // 3 bytes, 4 cycles
	OPCODE_AND_ABSY = 0x39, // 3 bytes, 4 cycles
	OPCODE_AND_ZP = 0x25, // 2 bytes, 3 cycles 
	OPCODE_AND_ZPX = 0x35, // 2 bytes, 4 cycles 
	OPCODE_AND_INX = 0x21, // 2 bytes, 6 cycles 
	OPCODE_AND_IXY = 0x31, // 2 bytes, 5 cycles 

	// ADC 
	OPCODE_ADC_IMM = 0x69, // 2 bytes, 2 cycles 
	OPCODE_ADC_ABS = 0x6D, // 3 bytes, 4 cycles 
	OPCODE_ADC_ABSX = 0x7D, // 3 bytes, 4 cycles
	OPCODE_ADC_ABSY = 0x79, // 3 bytes, 4 cycles
	OPCODE_ADC_ZP = 0x65, // 2 bytes, 3 cycles 
	OPCODE_ADC_ZPX = 0x75, // 2 bytes, 4 cycles 
	OPCODE_ADC_INX = 0x61, // 2 bytes, 6 cycles 
	OPCODE_ADC_IXY = 0x71, // 2 bytes, 5 cycles 
	
	//ASL
	OPCODE_ASL_ACC = 0x0A, // 1 bytes, 2 cycles 
	OPCODE_ASL_ABS = 0x06, // 2 bytes, 5 cycles 
	OPCODE_ASL_ABSX = 0x16, // 2 bytes, 6 cycles
	OPCODE_ASL_ZP = 0x0E	, // 3 bytes, 6 cycles 
	OPCODE_ASL_ZPX = 0x1E, // 3 bytes, 7 cycles 
	
	//LSR
	OPCODE_LSR_ACC = 0x4A, // 1 bytes, 2 cycles 
	OPCODE_LSR_ABS = 0x46, // 2 bytes, 5 cycles 
	OPCODE_LSR_ABSX = 0x56, // 2 bytes, 6 cycles
	OPCODE_LSR_ZP = 0x4E	, // 3 bytes, 6 cycles 
	OPCODE_LSR_ZPX = 0x5E, // 3 bytes, 7 cycles 

	//ROL
	OPCODE_ROL_ACC = 0x2A, // 1 bytes, 2 cycles 
	OPCODE_ROL_ABS = 0x26, // 2 bytes, 5 cycles 
	OPCODE_ROL_ABSX = 0x36, // 2 bytes, 6 cycles
	OPCODE_ROL_ZP = 0x2E	, // 3 bytes, 6 cycles 
	OPCODE_ROL_ZPX = 0x3E, // 3 bytes, 7 cycles 
	
	//ROR
	OPCODE_ROR_ACC = 0x6A, // 1 bytes, 2 cycles 
	OPCODE_ROR_ABS = 0x66, // 2 bytes, 5 cycles 
	OPCODE_ROR_ABSX = 0x76, // 2 bytes, 6 cycles
	OPCODE_ROR_ZP = 0x6E	, // 3 bytes, 6 cycles 
	OPCODE_ROR_ZPX = 0x7E, // 3 bytes, 7 cycles 
	

	
	// EOR
	OPCODE_EOR_IMM = 0x49, // 2 bytes, 2 cycles 
	OPCODE_EOR_ABS = 0x4D, // 3 bytes, 4 cycles 
	OPCODE_EOR_ABSX = 0x5D, // 3 bytes, 4 cycles
	OPCODE_EOR_ABSY = 0x59, // 3 bytes, 4 cycles
	OPCODE_EOR_ZP = 0x45, // 2 bytes, 3 cycles 
	OPCODE_EOR_ZPX = 0x55, // 2 bytes, 4 cycles 
	OPCODE_EOR_INX = 0x41, // 2 bytes, 6 cycles 
	OPCODE_EOR_IXY = 0x51, // 2 bytes, 5 cycles 
	
	// LDA
	OPCODE_LDA_IMM = 0xA9, // 2 bytes, 2 cycles 
	OPCODE_LDA_ABS = 0xAD, // 3 bytes, 4 cycles 
	OPCODE_LDA_ABSX = 0xBD, // 3 bytes, 4 cycles
	OPCODE_LDA_ABSY = 0xB9, // 3 bytes, 4 cycles
	OPCODE_LDA_ZP = 0xA5, // 2 bytes, 3 cycles 
	OPCODE_LDA_ZPX = 0xB5, // 2 bytes, 4 cycles 
	OPCODE_LDA_INX = 0xA1, // 2 bytes, 6 cycles 
	OPCODE_LDA_IXY = 0xB1, // 2 bytes, 5 cycles 
	
	// STA
	OPCODE_STA_ABS = 0x8D, // 3 bytes, 4 cycles 
	OPCODE_STA_ABSX = 0x9D, // 3 bytes, 5 cycles
	OPCODE_STA_ABSY = 0x99, // 3 bytes, 5 cycles
	OPCODE_STA_ZP = 0x85, // 2 bytes, 3 cycles 
	OPCODE_STA_ZPX = 0x95, // 2 bytes, 4 cycles 
	OPCODE_STA_INX = 0x81, // 2 bytes, 6 cycles 
	OPCODE_STA_IXY = 0x91, // 2 bytes, 6 cycles 
	
	// CMP
	OPCODE_CMP_IMM = 0xC9, // 2 bytes, 2 cycles 
	OPCODE_CMP_ABS = 0xCD, // 3 bytes, 4 cycles 
	OPCODE_CMP_ABSX = 0xDD, // 3 bytes, 4 cycles
	OPCODE_CMP_ABSY = 0xD9, // 3 bytes, 4 cycles
	OPCODE_CMP_ZP = 0xC5, // 2 bytes, 3 cycles 
	OPCODE_CMP_ZPX = 0xD5, // 2 bytes, 4 cycles 
	OPCODE_CMP_INX = 0xC1, // 2 bytes, 6 cycles 
	OPCODE_CMP_IXY = 0xD1, // 2 bytes, 5 cycles 
	
	// SBC
	OPCODE_SBC_IMM = 0xE9, // 2 bytes, 2 cycles 
	OPCODE_SBC_IMMt = 0xEB, // 2 bytes, 2 cycles 
	OPCODE_SBC_ABS = 0xED, // 3 bytes, 4 cycles 
	OPCODE_SBC_ABSX = 0xFD, // 3 bytes, 4 cycles
	OPCODE_SBC_ABSY = 0xF9, // 3 bytes, 4 cycles
	OPCODE_SBC_ZP = 0xE5, // 2 bytes, 3 cycles 
	OPCODE_SBC_ZPX = 0xF5, // 2 bytes, 4 cycles 
	OPCODE_SBC_INX = 0xE1, // 2 bytes, 6 cycles 
	OPCODE_SBC_IXY = 0xF1, // 2 bytes, 5 cycles 
	
	// RRA
	OPCODE_RRA_ABS = 0x6F, // 3 bytes, 6 cycles 
	OPCODE_RRA_ABSX = 0x7F, // 3 bytes, 7 cycles
	OPCODE_RRA_ABSY = 0x7B, // 3 bytes, 7 cycles
	OPCODE_RRA_ZP = 0x67, // 2 bytes, 5 cycles 
	OPCODE_RRA_ZPX = 0x77, // 2 bytes, 6 cycles 
	OPCODE_RRA_INX = 0x63, // 2 bytes, 8 cycles 
	OPCODE_RRA_IXY = 0x73, // 2 bytes, 8 cycles 

	// ISC
	OPCODE_ISC_ABS = 0xEF, // 3 bytes, 6 cycles 
	OPCODE_ISC_ABSX = 0xFF, // 3 bytes, 7 cycles
	OPCODE_ISC_ABSY = 0xFB, // 3 bytes, 7 cycles
	OPCODE_ISC_ZP = 0xE7, // 2 bytes, 5 cycles 
	OPCODE_ISC_ZPX = 0xF7, // 2 bytes, 6 cycles 
	OPCODE_ISC_INX = 0xE3, // 2 bytes, 8 cycles 
	OPCODE_ISC_IXY = 0xF3, // 2 bytes, 8 cycles 

	// DCP
	OPCODE_DCP_ABS = 0xCF, // 3 bytes, 6 cycles 
	OPCODE_DCP_ABSX = 0xDF, // 3 bytes, 7 cycles
	OPCODE_DCP_ABSY = 0xDB, // 3 bytes, 7 cycles
	OPCODE_DCP_ZP = 0xC7, // 2 bytes, 5 cycles 
	OPCODE_DCP_ZPX = 0xD7, // 2 bytes, 6 cycles 
	OPCODE_DCP_INX = 0xC3, // 2 bytes, 8 cycles 
	OPCODE_DCP_IXY = 0xD3, // 2 bytes, 8 cycles 

	// LAX
	OPCODE_LAX_IMM = 0xAB, // 2 bytes, 2 cycles 
	OPCODE_LAX_ABS = 0xAF, // 3 bytes, 4 cycles 
	OPCODE_LAX_ABSY = 0xBF, // 3 bytes, 4 cycles
	OPCODE_LAX_ZP = 0xA7, // 2 bytes, 3 cycles 
	OPCODE_LAX_ZPY = 0xB7, // 2 bytes, 4 cycles 
	OPCODE_LAX_INX = 0xA3, // 2 bytes, 6 cycles 
	OPCODE_LAX_IXY = 0xB3, // 2 bytes, 5 cycles 

	// GROUP OF BIG INSTRUCTIONS
};


// INSTRUCTION
struct instruction {
	enum OpcodeTable opcode;
	uint8_t bytes;
	uint8_t cycles;
	uint8_t relative;
	uint8_t imm;
	uint8_t acc;
	uint16_t abs;
	uint16_t absx;
	uint16_t absy;
	uint8_t zp;
	uint8_t zpx;
	uint8_t zpy;
	uint8_t inx;
	uint8_t ixy;
	uint8_t ind;
};
// INSTRUCTION


struct instruction decode_6510_opcode(uint8_t byte) {
	struct instruction ret_val = {0};
	switch (byte) {
		case OPCODE_NOP:
			printf("FOUND NOP");
			ret_val.opcode = OPCODE_NOP;
			ret_val.bytes = 1; 
			ret_val.cycles = 2;
			break;
		default:
			break;
	}
	return ret_val;
}


int run_6510_cpu(uint8_t *bytes) {
	int program_counter = 0;
	while (program_counter < ROM_SIZE) {
		struct instruction instrc = decode_6510_opcode(bytes[program_counter]);
		switch (instrc.opcode) {
		case OPCODE_NOP:
			printf("FOUND NOP!");
			program_counter += instrc.bytes;
			break;
		default:
			fprintf(stderr, "Undefined INSTRUCTION!\n");
			return -1;
		}
	}
	return 0;
}

// FLOPPY DISK SUPPORT
// SIZE OF SECTORS BY EACH ONE = 256 BYTE 
struct D64_File {
	char disk_image[SECTOR_COUNT][SECTOR_SIZE]; // EACH SECTOR IS 256 BYTE 
	char error_info[SECTOR_COUNT]; // ERROR INFO IS 1 BYTE FOR EACH SECTOR.
};
// FLOPPY DISK SUPPORT 

// RAM AND ROM DECLARATION 
uint8_t ROM[ROM_SIZE]; // 20 KB ROM 
uint8_t RAM[RAM_SIZE]; // 64 KB RAM
// RAM AND ROM DECLARATION

int main(int argc, char**argv) {
	if (argv[1] == NULL) {
		fprintf(stderr, "Please specify a binary for emulate: %s <binary format file>", argv[0]);
		return 1;
	}
	
	struct D64_File f;
	
	FILE* file = fopen(argv[1], "rb");
	if (file == NULL) {
		perror("File open failed on csixtyfour: ");
		return -1;
	}
	
	size_t n = fread(ROM, 1, ROM_SIZE, file);
	run_6510_cpu(ROM);

	fclose(file);
	
	return 0;
}
