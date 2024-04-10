# Unit 2 project: music player

**This README will hold all documentation related to the final Unit 2 project**

## Objective:

**The controller must be able to:**
1. make a variable available or unavailable.
2. change the speed at which it is changed.
3. change the value at the beginning.
4. Keep the led working.


**the graphic interface must be able to**

1. Have visual forms of interaction for all three variables.
2. Set the three variables: initial value, speed, if it's available, wether it's increasing or decreasing.
3. To activate or deactivate.
4. Be creative and have a god aesthetic.


## Project overview:

We're trying to incorporate the necessary parts asked in a music player

Our three variables are:

Song (number in a playlist)

Volume (from 0 to 20)

Minute (Where is the song right now in a 3:50 minute long song)

Our initial design of it's interface is this:

![alt text](IMG_6187(2).PNG)

More on the interface can be read about below in it's own section


## status diagram:

This was the first idea for a status diagram we thought of:

![alt text](IMG_6188(2).PNG)



## Graphic interface:

We begun with the design we wanted to have for the project:

![alt text](IMG_6187(2).PNG)

This design is subject to change


## Microcontroller:

The start of the project is actually here, we must first try to make this project work

First we must try to emulate how only one of the variables would work on the controller.

It's also a good way to check the led is always working.

Firstly an array will be made, it'll have all the possible values of the variable, in this case 0 thru 20

