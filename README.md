# ArdboxComTest
A simple firmware to receive commands to control the input and outputs of the ArdBox via the built-in USB serial port
## Examples
Default baud rate 115200
### Digital Write (DW)
```
DW13:1<newline> // sets pin 13 to High
``` 
RETURNS 13:1 as an acknowledgement
### Digital Status (DS)
```
DS13:0 //get status of pin 13
```
RETURNS 13:1 (if the value of 13 is HIGH)
### Analog Status (AS)
```
AS18:0 //get status of analog pin (0 - 1023)
```
RETURNS 18:581 (assuming the value is 581)