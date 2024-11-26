# Sagrada

This repository contains a C program that emulates the board game Sagrada.
Sagrada is a game in which colored dies are rollend and placed in the players "windows" that have different restrictions.
This project developed my skills in multi-dimensionals arrays, pointers 

## Prerequisites

To compile and run the program, you'll need:

- A C compiler (e.g., GCC)

## Game rules

Game start: You will be asked to input the no. of players and choose a "window" for each, private goals will be shared ,giving extra points for using a specific color for each player, togheter with the public goals allowing player to perform various actions at the price of helper gems, afterwards the round begins.
Windows have various dificulties, higher dificulty windows provide more helper gems used for the public goals.
Each round a no. of dies is rolled, each player gets to choose 2 dies/round in a certain order. Players may take a dice and place it or just pass.
Public 

   -Fisrt dice must be placed in a corner and all following dies must be placent adjacent to another.
   -Dies with same color and number may not be place adjacent to eachother (diagonals dont count).
   -After each round the leftover dies are discarded and drawn new ones

Game end: After the last round the points of the dies are talied up on each row/column added with private objective points and remaining helper gems, most points win. In case of a tie I too am curious.

### **Using GCC**
1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/your-repo.git
   cd your-repo
