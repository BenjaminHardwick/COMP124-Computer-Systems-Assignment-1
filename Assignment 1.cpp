﻿// STUDENT NAME: Benjamin J. Hardwick

// BRIEF: To create a basic input/output and to create an understanding on how x86 Assembly Code.
// works within the Visual Studio IDE, and to understand what is precisley going on.
// In this task I get to see how assembly code works and how the stack is performing tasks, etc.
#include <iostream>

int main(void)
{ // Creating the inputs.
	char age1[] = "Enter your age:\n";
	char msg0[] = "You are entitled to $100.\n";
	char msg1[] = "You are entitled to $120.\n";
	char msg2[] = "You are not entitled to a pension.\n";
	char msg3[] = "End of program.\n";
	char msg4[] = "A total of $%d has been paid out to %d people.\n";
	char fmt[] = "%d";
	int age = 0; //Defining the variables.
	int eighty = 120;
	int sixtyFive = 100;
	int underAge = 0;
	int total = 0;
	int moneyOut = 0;


	_asm
	{
		while1 : //Creating the while loop for the program to jump back to when called.

			lea eax, age1  //creating the first message which will be pushed onto the stack.
			push eax    // Creating the stack on EAX.
			call printf //Calling the print function so the message outputs.
			add esp, 8 // Adding 8bytes to the stack.
			lea eax, age //adding the integer 'age'.
			push eax   //Pushing it onto the stack.
			lea eax, fmt  // putting the format onto the stack.
			push eax   //pushing it onto the stack.
			call scanf  // scanning the users input.
			add esp, 8 // adding another 8bytes to to the stack, as each integer is 4 bytes.
			pop eax // popping out the stack.

			mov eax, age // moving age onto the stack.
			cmp eax, 0  // comparing it with 0
			jl notEligible // if its not greater than  0, then it will jump to noteligible.
			cmp eax, 80 // if its larger than 0, it will move to here, and be checked if the
			jge second // .. integer is larger than 80, if so it will jump to second(variable)
			cmp eax, 65	// ifnot it will continue to check if its greater than 65. 
			jge third // if so it wil jump to the third.
		
		notEligible:      // If the user is not eligble the message will display and the 
			cmp eax, -1  // program will detect if their  input is greater or lessthan -1, if less it will end the program.
			jle first
			lea eax, msg2
			push eax
			call printf
			pop eax
			jmp while1

		first:				// This will display how the amount of money will increase and total amount of users will increase when used.
			lea eax, msg4
			push eax    // pushing msg4 onto the stack.
			push total // pushing the total onto the stack.
			push moneyOut // pushing moneyout onto the stack.
			lea eax, msg2  //  Giving the message how much they are eligble too.
			push eax
			call printf
			jmp end_while
		
			
		second:
			lea eax, msg1
			push eax
			call printf
			pop eax
			add total, 1
			add moneyOut, 120
			jmp while1

		third:
			lea eax, msg0
			push eax
			call printf
			pop eax // clearing the stack for the next user.
			add total, 1
			add moneyOut, 100
			jmp while1 // jumping back to the original question for users' input.

		end_while :
			push total // Outputting the total.
			push moneyOut // outputting the total amount of money owed  out.
			lea eax, msg4
			push eax
			call printf // Here the message is printed once  its been pushed onto the stack.
			pop eax // clearing the stack.
			lea eax, msg3
			push eax
			call printf
			pop eax

	}
	return 0;
}
