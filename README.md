# Flowers-game
This is a program that plays the Flowers and Bees word guessing game.

#### Concepts:
* C Strings
* 2D arrays
* Loading information from plain text files


Here's how one round of the game works:
1.	The computer picks a mystery word of 4 to 6 letters and tells the player how many letters are in the word. 
2.	The player then tries to guess the mystery word by presenting the computer with a series of trial words, with each trial word being a 4 to 6 letter word.
3.	If the trial word is the mystery word, the player wins. Otherwise, the computer will respond to the trial word with two integers:
    1. The number of flowers
    2. And the number of bees
    
A __Flower__ is a paring of a letter in the trial word and the same letter in the mystery word, in the same position. 

E.g. EGRET & AGATE, there is one flower, as the Gs in both words are in the same position

A __Bee__ is a pairing between a letter in the trial word and the same letter in the mystery word, but not in the same position as in the trial word, provided that neither of the two letters are involved in a flower or another bee.

E.g. EGRET and AGATE, the Ts form a bee, since they are the same letter but they are not in the same position (i.e. index 4 in EGRET and index 3 in AGATE). The E in AGATE can then be paired with one of the Es in EGRET. If we pair it with the first letter, then the second letter in EGRET would not be part of a bee, as there are no other Es to pair it to, and vice versa if we paired the E in AGATE to the second E in EGRET.

The player’s score for each round is the number of trial words needed to determine the correct word (counting the trial word that matched the mystery word).

The program asks the player how many rounds to play, and then plays that many rounds of the game.

After each round, the program displays some statistics about how well the player has played the rounds so far:
1.  The average score
2.  The minimum score
3.  The maximum score

Here is an example of this interaction:

<img src="https://user-images.githubusercontent.com/56947176/94780424-fdd16d00-03fa-11eb-915f-5035b18bd7c6.png" alt="drawing" width="379.5" height="603">

Unknown words (that are not included in words.txt) and trial strings that do not consist of between 4 to 6 words, inclusive, do not count towards the number of tries in a round.

## Notable Obstacles
I didn’t encounter very many programming specific obstacles over the course of developing this program, but encountered more mental obstacles, as well as ones that were brought about by careless mistakes.

I have noticed I tend to think too much about the specific design of my program before I actually begin the development process. To combat this, I would sketch out a brief flowchart of some simple algorithms written in Pseudocode that I could see achieving the goal of the program, and then move to incrementally developing the program in my IDE. I found that taking a more simplistic approach to the initial design, and then focusing on the specifics as I write the code, allowed me to make the program development process much more manageable for myself, and this is something I will continue in the future as my projects become more and more complex.

Occasionally, I will get stuck on a compilation error for a longer period of time than usual, and this is usually down to some very nuanced careless mistake that I have made. Unfortunately, I don’t think that there is any quick-fix solution for this right now, but is something that will be ironed out as I continue to improve my programming skills by developing more programs.

## Program Design
The design of this program is fairly simplistic. The main routine initialises the necessary variables to keep track of all the information in a set of rounds, also calculating statistics based off of the value of these variables, and playOneRound contains the proceedings necessary for playing one round, and utilises another function findFlowersAndBees.

### main()
```
import list of words from text file
ask user how many rounds they want to play
repeatedly, for the number of rounds the user wants to play
  select a random number to select a random word later
  play a round
  work out statistics
  give the user their statistics
```

### playOneRound()
```
select a random mystery word
while the user hasn’t correctly guessed the mystery word, repeatedly
  get trial word from user
  if they guess the word correctly
    user wins the round
  else check for number of flowers and bees
    tell the user how many flowers and bees were in their trial word
the number of tries they took to guess the word is their score
```

### findFlowersAndBees()
```
for the entire length of the mystery word and the trial word
  if found characters in the same positions
    there is a flower
    reflect in some way that this letter has been used to make a flower
for the entire length of the mystery word and the trial word
  if found two of the same character
    if these characters had already been used to find a flower/bee
      no bee
    else there is a bee
      reflect in some way that this letter has been used to make a bee
```
