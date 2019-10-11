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
test "No Input => PORTB: 0"
set Door_State = Locked
continue 5
expectPORTB 0
expect Door_State Locked
checkResult 

test "PA2 press > PA1 press (Correct Order) => PORTB: 1"
set Door_State = Locked
continue 5
setPINA 0x04
continue 5
setPINA 0x00
continue 5
setPINA 0x02
continue 5
setPINA 0x00
continue 5
expectPORTB 1
expect Door_State Unlocked
checkResult

test "PA2 press > PA1 press > PA7 press (Correct Order & Lock) => PORTB: 0"
set Door_State = Locked
continue 5
setPINA 0x04
continue 5
setPINA 0x00
continue 5
setPINA 0x02
continue 5
setPINA 0x00
continue 5
setPINA 0x80
continue 5
expectPORTB 0
expect Door_State Locked
checkResult

test "PA2 press > PA2 press (Wrong Order) => PORTB: 0"
set Door_State = Locked
continue 5
setPINA 0x04
continue 5
setPINA 0x00
continue 5
setPINA 0x04
continue 5
setPINA 0x00
continue 5
expectPORTB 0
expect Door_State Release_1
checkResult

test "All press > All press (Pressing all 3 buttons) => PORTB: 0"
set Door_State = Locked
continue 5
setPINA 0x07
continue 5
setPINA 0x00
continue 5
setPINA 0x07
continue 5
setPINA 0x00
continue 5
expectPORTB 0
expect Door_State Locked
checkResult

test "PA2 press > PA1 hold > PA0 press (Double button press) => PORTB: 0"
set Door_State = Locked
continue 5
setPINA 0x04
continue 5
setPINA 0x00
continue 5
setPINA 0x04
continue 5
setPINA 0x05
continue 5
expectPORTB 0
expect Door_State Locked
checkResult

test "PA0 press > PA2 press > PA1 press (Wrong then Correct Order) => PORTB: 1"
set Door_State = Locked
setPINA 0x01
continue 5
setPINA 0x00
continue 5
setPINA 0x04
continue 5
setPINA 0x00
continue 5
setPINA 0x02
continue 5
setPINA 0x00
continue 5
expectPORTB 1
expect Door_State Unlocked
checkResult

test "PA2 hold > PA1 hold (Correct Order w/out releasing button) => PORTB: 0"
set Door_State = Locked
setPINA 0x04
continue 5
setPINA 0x06
continue 5
expectPORTB 0
expect Door_State Locked
checkResult


# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
