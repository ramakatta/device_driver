Objective:
    To understand the basic functioning of the GDB debugger.
    Using the gdb version 7.1-ubuntu

Instructions:
=============
1. Compile the Program (test_cout.c)
	host$ make

2. Run the gdb on the compiled binary (test_out) :
	host$ gdb test_out (Running gdb for the binary name, here test_out)

----------------------
Source code listing
----------------------

Start running the program again on gdb.

1.(gdb)l add_func(List by function name)
2.(gdb)l 54 (List by line number)
3.(gdb)l (lists the current context code)


----------------------
Breakpoints
----------------------

1.Setting the breakpoints by line number
	(can use b or break)

Start running the program again on gdb.
	
	(gdb)l      (list the code to figure out where you want to set a breakpoint)
	(gdb)b 56   (set break point at line 56)
	(gdb)r      (run program) 
	(gdb)s      (can step through the code to see any specifics)

2. Setting the breakpoints by function name
	(gdb)b add_func
	(gdb)c

3. Information on the breakpoints
	(gdb)info b 

	( Lists the breakpoint associated info like the line number 
	  or func name and the associated id of the breakpoint,
	  status(enabled/disabled), if hit the breakpoint 
	  anytime )
	
4. Disabling the breakpoints
	(gdb)disable b <break_pt_id>

	( break_pt_id is obtained from step-3 )

5. Deleting the breakpoints

	(gdb)delete breakpoints 1
	
	( Obtained from the info b command) 
	( Indicates the number of the breakpoint)
	
Quit from gdb
(gdb)q

6. Setting condition:

Specify breakpoint number N to break only if COND is true.
Usage is `condition N COND', where N is an integer and COND is an
expression to be evaluated whenever breakpoint N is reached.

Start running the program again on gdb.
	(gdb)b 131
	(gdb)info b
	( figure out the id of the breakpoint just set )

	(gdb)condition <break_pt_id> (i==10)
	(gdb)r

	On hitting the condition, programs breaks.
	(gdb)print i
         
Quit from gdb
(gdb)q


-------------------------
Variables and Expressions
------------------------

Start running the program again on gdb.

1. Information on arguments:

	(gdb)b add_func
	(gdb)r
	(gdb)s
	(gdb)info args (used in functions where input arguements are available)

2. Information on locals:
	(gdb)info locals

3. Display command in GDB:
	
	gen syntax: display/format expr
	
	format:
		o->octal
		d->decimal
		b->binary
		x->hex

	(gdb)display/x i
	(gdb)b 131
	(gdb)c
	(gdb)c
	(gdb)c
	(gdb)c
	
	Note: Can monitor the value of i when the breakpoint is hit continuously.	
	
	Disabling/deleting display:
	--------------------------

	(gdb)info display (Figure out the display id corresponding to the display variable i)
	(gdb)disable display <display_id>
	(gdb)delete display <display_id>

5. Catch:
	(gdb)catch syscall sync
	(gdb)c

Catches the system call sync when encountered when the program runs.

Quit from gdb
(gdb)q


-------------------------
Backtrace
-------------------------

Start running the program again on gdb.

1. Info on frames leading to the current frame/mem locations
    (gdb)b add_func
	(gdb)r
	(gdb)bt
    (gdb)bt 1 
		( lists the innermost 1 frame,
		  number can be anything depending on the user's discretion,here 1 )
    (gdb)bt -1 
		( lists the outermost 1 frame,
		  number can be anything depending on the user's discretion,here 1)

Quit from gdb
(gdb)q

-------------------------
Stack Analysis
-------------------------

NOTE: The innermost frames numer/id is always zero
	
1. Information on the stack ( Backtrace of the stack, or innermost COUNT frames)

Start running the program again on gdb.
	
	(gdb)b add_func
	(gdb)r
	(gdb)info stack

Quit from gdb
	(gdb)q

2. Examinig specific memories of stack
	
	General Syntax : x/nfu address of the variable
	 	n->no. of elements
		f->display format:
			o->octal
			d->decimal
			b->binary
			x->hex
		u->b/h/w/g
			b->byte
			h->half word(2 bytes)
			w->word(4 bytes)
			g->giant words(8 bytes)
	
Start running the program again on gdb.
	(gdb)b 45
	(gdb)r
	(gdb)s
	(gdb)print &elem1
	(gdb)x/10 <addr of the elem1>

3.Information on the frame
	(gdb)info frame (Lists the frame info for main)

4.Switching to frames
	(gdb)b add_func
	(gdb)c
	(gdb)s
	(gdb)bt (Lists the functions that have led to the current context)

	(gdb)frame 1 (frame no. is the frame no. you wanna switch to) here switch to frame 1,main's frame)

	(gdb)info frame
	(gdb)print res 
	(shows the variable value of res,which is zero since not yet computed)

	(gdb)frame 0
	(gdb)c (Run through the code)

5.Moving up and down the frames

Start running the program again on gdb.

	(gdb)b add_func
	(gdb)r
	(gdb)s
	(gdb)bt
	(gdb)up   (Takes you to main's frame)
	(gdb)down (Takes you to add_func's frame)
	
Quit from gdb
(gdb)q


-------------------------
Registers
-------------------------

Start running the program again on gdb.
	(gdb)b main
	(gdb)r
	(gdb)info registers (Shows the register values for the current context)
	(gdb)info register eip (Shows specific value of Instruction pointer register)
	(gdb)info register esp
	(gdb)b add_func
	(gdb)c
	(gdb)info registers (Shows the register values for the current context)
	(gdb)info register eip (Shows specific value of Instruction pointer register)
	(gdb)info register esp

	
Quit from gdb
(gdb)q


-------------------------
Disassembly
-------------------------

Lists the assembly language instructions

Start running the program again on gdb.
	(gdb)b 109
	(gdb)r
	(gdb)disassemble

Quit from gdb
(gdb)q


-------------------------
Watchpoints
-------------------------

NOTE: 	Only 4 watchpoints can be set.
		Watchpoints show up only when the specified variable's value changes listing the old and new values of the set watchpoint.

Start running the program again on gdb.
(gdb)b add_func
(gdb)r
(gdb)watch i
(gdb)c
(gdb)c
(gdb)c


Quit from gdb
(gdb)q


-------------------------
Threads
-------------------------

Start running the program again on gdb.

switching between threads:
(gdb)b thrd_func
(gdb)r
(gdb)info thread
(gdb)thread <thread_id> (thread id of main to switch to it)
(gdb)info registers
(gdb)info thread
(gdb)thread <thread_id>(thread id of thrd_func to switch to it)

Quit from gdb
(gdb)q

(gdb) set var oper='s'

-------------------------
Signal
-------------------------

Start running the program again on gdb.
(gdb) info signal (Lists the signals supported)

Handling signals:
gen syntax:handle signal_name action

(gdb) handle SIGSEGV print (Instructing gdb to print whenever SIGSEGV is encountered)

	
-------------------------
Crash analysis
-------------------------
(gdb)bt
(gdb)where (gives the current context of crash like line number listing)
