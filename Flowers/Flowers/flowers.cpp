//
//  main.cpp
//  Flowers
//
//  Created by Mitchell McLinton on 8/11/19.
//  Copyright © 2019 Mitchell McLinton. All rights reserved.
//

#include "utilities.h"
#include <iostream>
#include <cstring>
#include <cctype>
#include <climits>
using namespace std;

const char WORDFILENAME[] = "/Users/mmclinton/Google Drive/UCLA/@Fall 19/COM SCI 31/Programming Assignments/Assignment 5/Flowers/Flowers/words.txt";
const int MAXWORDS = 10'000;

int playOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordNum);
void findFlowersAndBees(char mysteryWordForComparison[MAXWORDLEN+1], char trialWord[MAXWORDLEN+1], int& nFlowers, int& nBees);

int main() {
    char wordList[MAXWORDS][MAXWORDLEN+1];
    int nWordsLoaded = getWords(wordList, MAXWORDS, WORDFILENAME);
    cerr << "getWords: " << nWordsLoaded << " words loaded into C string array words." << endl;
    if (nWordsLoaded < 1 ) {
        cout << "No words were loaded, so I can't play the game." << endl;
        exit(1);
    }
    
    cout.setf(ios_base::fixed); //this and next line set double printing precision to 2 d.p.
    cout.precision(2);
    
    cout << "How many rounds do you want to play? ";
    int nRoundsToPlay;
    cin >> nRoundsToPlay;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');    //numeric_limits<streamsize>::max() represents the maximum number of chars the cin stream can hold
    
    if (nRoundsToPlay < 0) {
        cout << "The number of rounds must be positive." << endl;
        exit(99);
    }
    
    if(nRoundsToPlay == 0) {
        exit(0);
    }
    
    int roundScore;
    int totalScore = 0;
    int minScore = INT_MAX;
    int maxScore = 0;
    double averageScore;
    
    int wordNum;
    
    for (int i=1; i <= nRoundsToPlay; i++) {
        wordNum = randInt(0, nWordsLoaded-1);
        
        cout << endl << "Round " << i << endl;
        cout << "The mystery word is " << strlen(wordList[wordNum]) << " letters long." << endl;
        
        roundScore = playOneRound(wordList, nWordsLoaded, wordNum);
        
        if (roundScore == -1) { //This block of code should never be executed, as playOneRound should never be called with invalid nWordsLoaded or wordNum
            cerr << "playOneRound returned -1. This shouldn't be happening." << endl;
            exit(99);
        }
        
        if (roundScore == 1) {
            cout << "You got it in 1 try." << endl;
        } else {
            cout << "You got it in " << roundScore << " tries." << endl;
        }
        totalScore += roundScore;
        
        if (roundScore < minScore) {
            minScore = roundScore;
        }
        
        if (roundScore > maxScore) {
            maxScore = roundScore;
        }
        
        averageScore = static_cast<double>(totalScore) / i;
        cout << "Average: " << averageScore << ", minimum: " << minScore << ", maximum: " << maxScore << endl;
    }
}

int playOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordNum) {
    if (nWords < 0) {
        cerr << "playOneRound: nWords is not positive." << endl;
        return -1;
    }
    
    if (wordNum < 0 || wordNum >= nWords) {
        cerr << "playOneRound: wordNum is less than zero, or it is greater than or equal to nWords." << endl;
        return -1;
    }
    
    char mysteryWord[MAXWORDLEN+1] = "tiger";
//    strcpy(mysteryWord, words[wordNum]);
    
    char mysteryWordForComparison[MAXWORDLEN+1];
    strcpy(mysteryWordForComparison, mysteryWord); //copying mystery word into an array that will be modified for flower and bee finding
    
    int nTries = 0;
    bool correctGuess = false;
    
    char trialWord[100];
    
    int nFlowers;
    int nBees;
    
    cerr << mysteryWord << endl;
    
    while (!correctGuess) {
        //Resetting the number of flowers and bees from any previous tries
        nFlowers = 0;
        nBees = 0;
        
        //Resetting the C string for comparison to be equal to mysteryWord
        strcpy(mysteryWordForComparison, mysteryWord);
        
        cout << "Trial word: ";
        cin.getline(trialWord, 99, '\n');
        
        //Validating whether the trial word is between 4 to 6 letters, inclusive
        if (strlen(trialWord) < 4 || strlen(trialWord) > 6) {
            cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;
            continue;
        }
        
        //Validating whether the trial word consists of only lowercase letters
        bool allLowercase = true;
        for (int i=0; i < strlen(trialWord); i++) {
            if (!islower(trialWord[i])) {
                cerr << "playOneRound: trial word failed lowercase validation." << endl;
                allLowercase = false;
                break;
            }
        }
        if (!allLowercase) {
            cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;
            continue;
        }
        
        //Validating whether the trial word is one of the words in the array of valid words
        bool foundWord = false;
        for (int i=0; i < nWords; i++) {
            if (strcmp(words[i], trialWord) == 0) {
                foundWord = true;
            }
        }
        if (!foundWord) {
            cout << "I don't know that word." << endl;
            continue;
        }
        
        //We reach this point if the trial word has been successfully validated, so the try is valid, so increment the number of tries by 1
        nTries++;
        
        //First, we'll check if the trial word is equal to the mystery word
        if (strcmp(mysteryWord, trialWord) == 0) {
            correctGuess = true;
            break;
        }
        
        findFlowersAndBees(mysteryWordForComparison, trialWord, nFlowers, nBees);
        
        cout << "Flowers: " << nFlowers << ", Bees: " << nBees << endl;
        continue;
    }
    //If we reach this point, the user has guessed correctly what the word is, we'll now return their score
    return nTries;
}

void findFlowersAndBees(char mysteryWordForComparison[MAXWORDLEN+1], char trialWord[MAXWORDLEN+1], int& nFlowers, int& nBees) {
    //Figure out number of flowers
    for (int i=0; mysteryWordForComparison[i] != '\0' || trialWord[i] != '\0'; i++) {
        if (mysteryWordForComparison[i] == trialWord[i]) {
            nFlowers++;
            mysteryWordForComparison[i] = ' ';  //change char at index i to ' ' (empty char), avoids future involvement of the character that was there in bee finding
            trialWord[i] = ' ';
        }
    }
    
    //Figure out number of bees
    for (int i=0; mysteryWordForComparison[i] != '\0'; i++) {
        if (mysteryWordForComparison[i] == ' ') {   //abandon current loop if empty character is found; the character here has already been used in a flower/bee
            continue;
        } else for (int j=0; trialWord[j] != '\0'; j++) {
            if (trialWord[j] == ' ') {  //abandon current loop if empty character is found; the character here has already been used in a flower/bee
                continue;
            } else if (mysteryWordForComparison[i] == trialWord[j]) {
                nBees++;
                mysteryWordForComparison[i] = ' ';    //change char at index i to ' ' (empty char), avoids future involvement of the character that was there in bee finding
                trialWord[j] = ' ';
            }
        }
    }
}
    
