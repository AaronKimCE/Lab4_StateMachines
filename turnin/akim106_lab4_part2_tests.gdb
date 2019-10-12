# Test file for Lab4_StateMachines


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

# Add tests below
test "No Input => PORTC: 7"
set Cnt_State = Wait
continue 5
expectPORTC 7
expect Cnt_State Wait
checkResult 

test "One B1 Press => PORTC: 8"
set Cnt_State = Wait
continue 5
setPINA 0x01
continue 5
setPINA 0x00
continue 5
expectPORTC 8
expect Cnt_State Wait
checkResult

test "One B2 Press => PORTC: 6"
set Cnt_State = Wait
set TickFct_Cnt::Output = 7
continue 5
setPINA 0x02
continue 5
setPINA 0x00
continue 5
expectPORTC 6
expect Cnt_State Wait
checkResult

test "Two B1 Presses => PORTC: 9"
set Cnt_State = Wait
set TickFct_Cnt::Output = 7
continue 5
setPINA 0x01
continue 5
setPINA 0x00
continue 5
setPINA 0x01
continue 5
setPINA 0x00
continue 5
expectPORTC 9
expect Cnt_State Wait
checkResult

test "Two B2 Presses => PORTC: 5"
set Cnt_State = Wait
set TickFct_Cnt::Output = 7
continue 5
setPINA 0x02
continue 5
setPINA 0x00
continue 5
setPINA 0x02
continue 5
setPINA 0x00
continue 5
expectPORTC 5
expect Cnt_State Wait
checkResult

test "Reset Press => PORTC: 0"
set Cnt_State = Wait
set TickFct_Cnt::Output = 7
continue 5
setPINA 0x03
continue 5
setPINA 0x00
continue 5
expectPORTC 0
expect Cnt_State Wait
checkResult

test "Reset Press & B1 Press => PORTC: 1"
set Cnt_State = Wait
set TickFct_Cnt::Output = 7
continue 5
setPINA 0x03
continue 5
setPINA 0x00
continue 5
setPINA 0x01
continue 5
setPINA 0x00
continue 5
expectPORTC 1
expect Cnt_State Wait
checkResult

test "Hold B1 then Both => PORTC: 0"
set Cnt_State = Wait
set TickFct_Cnt::Output = 7
continue 5
setPINA 0x01
continue 5
setPINA 0x03
continue 5
expectPORTC 0
expect Cnt_State Reset
checkResult

test "Hold B2 then Both => PORTC: 0"
set Cnt_State = Wait
set TickFct_Cnt::Output = 7
continue 5
setPINA 0x02
continue 5
setPINA 0x03
continue 5
expectPORTC 0
expect Cnt_State Reset
checkResult

test "Hold B1 => State: Press_1"
set Cnt_State = Wait
set TickFct_Cnt::Output = 7
continue 5
setPINA 0x01
continue 5
expect Cnt_State Press_1
checkResult

test "Hold B2 => State: Press_2"
set Cnt_State = Wait
set TickFct_Cnt::Output = 7
continue 5
setPINA 0x02
continue 5
expect Cnt_State Press_2
checkResult

test "Hold B1 & B2 => State: Reset"
set Cnt_State = Wait
set TickFct_Cnt::Output = 7
continue 5
setPINA 0x03
continue 5
expect Cnt_State Reset
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
