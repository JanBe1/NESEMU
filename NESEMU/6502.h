#pragma once
#include <cstdint>
//TODO: Meminit
/*
* The Nintendo Entertainment System has the following components:

2A03 CPU IC made by Ricoh
CPU based on the MOS Technology 6502 8-bit microprocessor
serial input for game controllers
audio output comprising four tone generators and a delta modulation playback device
2 KiB of RAM for use by the CPU
2C02 PPU (picture processing unit)
tile-based background image
64 sprites (individually moving objects)
25 colors out of 53
256x240 pixel progressive picture generator
NTSC color encoder
2 KiB of RAM for use by the PPU
Cartridges have the following components:

16 KiB or more PRG ROM, for use by the CPU
8 KiB or more CHR ROM or CHR RAM, for use by the PPU (and in some cases by the CPU)
(optional) Bank switching hardware for the ROMs
(optional) Logic to generate interrupts
*/
#pragma region Global Const Expressions
static constexpr int MAX_MEMORY = 0xFFFF;
static constexpr int TWO_KILOBYTES = 0x0800;

#pragma endregion

#pragma region Structures

/// <summary>
/// This structure is responsible for emulation of 6502 CPU.
/// Refer to: https://www.nesdev.org/obelisk-6502-guide/
/// </summary>
struct CPU {

	/// <summary>
	/// The program counter. 16 bit register which points to the next instruction to be executed. The value of program counter is modified automatically as instructions are executed.
	/// </summary>
	uint16_t PC;

	/// <summary>
	/// The Stack Pointer. The processor supports a 256 byte stack located between $0100 and $01FF. The stack pointer is an 8 bit register and holds the low 8 bits of the next free location on the stack. 
	/// The location of the stack is fixed and cannot be moved.
	/// </summary>
	uint8_t SP;

	/// <summary>
	/// The Accumulator. The 8 bit accumulator is used all arithmetic and logical operations (with the exception of increments and decrements).
	/// The contents of the accumulator can be stored and retrieved either from memory or the stack.
	/// </summary>
	uint8_t ACC;

	/// <summary>
	/// The X register.
	/// </summary>
	uint8_t X;

	/// <summary>
	/// The Y register.
	/// </summary>
	uint8_t Y;

	PSReg PS;
	/// <summary>
	/// The reset function. Sets all flags to 0, PC to 0xFFFE (IRQ), 
	/// </summary>
	void reset() {
		PC = 0xFFFC;
		SP = 0x0100;
		X, Y, PS.C, PS.Z, PS.I, PS.D, PS.B, PS.O, PS.N = 0;
	}
};

/// <summary>
/// The memory of the controller. NES system has 2 KiB of RAM for use by the CPU. Refer to:
/// https://www.nesdev.org/wiki/CPU_memory_map
/// </summary>
struct Memory {
	uint8_t Data[TWO_KILOBYTES];
};

/// <summary>
/// A Processor Status. One of status registers of CPU. As instructions are executed a set of processor flags are set or clear to record the results of the operation.
///  This flags and some additional control flags are held in a special status register. Each flag has a single bit within the register.
/// </summary>
struct PSReg {
	/// <summary>
	/// Carry Flag. 
	/// The carry flag is set if the last operation caused an overflow from bit 7 of the result or an underflow from bit 0. This condition is set during arithmetic, comparison and during logical shifts.
	///  It can be explicitly set using the 'Set Carry Flag' (SEC) instruction and cleared with 'Clear Carry Flag' (CLC).
	/// </summary>
	uint8_t C : 1;

	/// <summary>
	/// The Zero Flag.
	/// The zero flag is set if the result of the last operation as was zero.
	/// </summary>
	uint8_t Z : 1;

	/// <summary>
	/// The Interrupt Disable.
	/// The interrupt disable flag is set if the program has executed a 'Set Interrupt Disable' (SEI) instruction. 
	/// While this flag is set the processor will not respond to interrupts from devices until it is cleared by a 'Clear Interrupt Disable' (CLI) instruction.
	/// </summary>
	uint8_t I : 1;

	/// <summary>
	/// Decimal Mode.
	/// While the decimal mode flag is set the processor will obey the rules of Binary Coded Decimal (BCD) arithmetic during addition and subtraction.
	///  The flag can be explicitly set using 'Set Decimal Flag' (SED) and cleared with 'Clear Decimal Flag' (CLD).
	/// </summary>
	uint8_t D : 1;

	/// <summary>
	/// The Break Command. The break command bit is set when a BRK instruction has been executed and an interrupt has been generated to process it.
	/// </summary>
	uint8_t B : 1;

	/// <summary>
	/// The Overflow Flag. 
	/// The overflow flag is set during arithmetic operations if the result has yielded an invalid 2's complement result (e.g. adding to positive numbers and ending up with a negative result: 64 + 64 => -128). 
	/// It is determined by looking at the carry between bits 6 and 7 and between bit 7 and the carry flag.
	/// </summary>
	uint8_t O : 1;

	/// <summary>
	/// The Negative Flag. The negative flag is set if the result of the last operation had bit 7 set to a one.
	/// </summary>
	uint8_t N : 1;

};
#pragma endregion


