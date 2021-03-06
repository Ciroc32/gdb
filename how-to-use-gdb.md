# HOW TO USE GDB
<...> : Replace with something (don't write the "<>")

## {Basics} :
	- Run GDB (installed with MinGW) :
		gdb <program.ext>

	- Run the program in gdb :
		run

	- Stop the program in gdb :
		kill
		//or : stop

	- Stop gdb :
		q
		//or : quit

## {Memory}
	- set the value of a memory adress :
		set {int}<adress>=<value>	
	
	- get the value of a memory adress :
		print (<type>) *<adress>
		//<type> : int, float...

	- Print the memory stack :
		x/48wx $esp
		//The value "48" can be changed, it's not the same depending of memory size
		//The value 'x' can be changed, it can be 's' to print string 'd' for decimal...

	Information :
		<adress> : 0x...

## {Instructions} :
	- Next assembly/binary instruction (if there is breakpoint) :
		ni
		//OR : ni <number of instructions to forward>

	- Print next NUMBER_OF_NEXT_INSTRUCTIONS_TO_PRINT instructions :
		x/<NUMBER_OF_NEXT_INSTRUCTIONS_TO_PRINT>i $eip

## {Advanced} https://youtu.be/VroEiMOJPm8?list=PLhixgUqwRTjxglIswKp9mpkfPNfHkzyeN :
	(Disassembly)
	- Disassemble the program (get the asm code) :
		disassemble
	
	- Disassemble the main function :
		disassemble main
	
	- Set intel synthax :
		set disassembly-flavor intel
	-+ Copy paste
		set disassembly-flavor intel
		disassemble main
	
	(Breakpoints) The program will pause if it founds a breakpoint, then, that's how you can apply modifications to it
	- Set a breakpoint on a specific program adress (can be found at disassembly) (ex : 0x004014a3):
		break *<program adress>

	- Set breakpoint to main (at each instruction of main() function, it will pause the program) :
		break *main

	- Continue the execution of the subprogram till we reach any breakpoint :
		continue

	(Register) :
		- Show register info :
			info registers

		- Change a register value :
			set $<register>=<value>
## {Env}
The env offset in gdb is 61 
To don't have any problem with the stack addresses in gdb to get the same environment as we're not using GDB we could unset LINES and COLUMNS

(gdb)
unset env LINES
unset env COLUMNS
(/gdb)

## {Registers (C language usage)} :
	{EAX} :
	- C funtions return (0, 1 or any) -> eax register
	----------------------------------------------------------
	C code :

	int getAnumber()
	{
		return 4;
	}

	int main()
	{
		int var = getAnumber();
		...
	}

	~Assembly code :
	main:
		call <getAnumber> //return -> eax
		mov <var>, eax //set var to eax
		...
	----------------------------------------------------------

	You can set a breakpoint to the adress where the functions is executed to change the return with set $eax=...

	{EIP} :
	- EIP (Instruction pointer) is the Instruction pointer, it points to the next instruction adress
	  To change it :
		set $eip=<adress or func name>
		/*
			Examples :
				set $eip=*main
				set $eip=*<function>
				set $eip=*<function>+<+offset>
				//offset 4 by 4
		*/

	{ESP} (Important one) :
	You're looking for a variable value in the memory ? Then ESP register is useful for this usage

	- ESP (Stack pointer) is the current stack address pointer, at each time, it's added by 4
	  To find esp+<offset> expression-adrress, you can disassemble the program

	  - Find the value of the stack pointer offset : address+<offset> of ESP :
		x/s $esp+0x<offset>

	  - Find the address the stack pointer offset :
		print $esp+0x<offset>
		//To find the value, consider <x> as the output of previous command (similar to "0x61ff1c") and then : print *<x>

	ESP is the current stack pointer. EBP is the base pointer for the current stack frame. When you call a function, typically space is reserved on the stack for local variables. ... So EBP will point to the top of your stack for this frame, and ESP will point to the next available byte on the stack.

	{Stack} :
	Each time you create a variable, it's value is added to the memory stack which is extensible :
		C CODE :
		----------
		int i1 = 3 
		int i2 = 2
		int i3 = 1
		----------
		MEMORY :
		[------------]
		i1 : 0x61ff1c //ESP+18
		i2 : 0x61ff14 //ESP+14
		i3 : 0x61ff10 //ESP+10
		[------------]
	  	- Each time a variable is created, it's value is added in the top of the stack and that's why it has an address which is below 		  the address of the variable which is under it

		- Each time a variable is created, it has a new address which is the address of the variable which is under it +4	

## Offsets :
	- Offset in envs (61-64)
	- Offset in stack (96)
	
	
