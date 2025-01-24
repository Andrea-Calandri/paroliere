# Paroliere
Paroliere is a thrilling word search game that challenges your vocabulary and sharpens your mind. 
Set in a 4x4 grid of letters, your task is to form valid words (at least four letters) by connecting adjacent letters.
The longer the word, the more points you earn!

The score table is as follows (length -> score):

- 4 ->  1
- 5 ->  2
- 6 ->  3
- 7 ->  5
- 8 ->  8
- 9 ->  10
- 10 -> 12
- 11 -> 14
- 12 -> 16
- 13 -> 18
- 14 -> 20
- 15 -> 22
- 16 -> 24

### The Internal Dictionary 

The internal dictionary (`dictionary.txt`) used by the algorithm to find all the words in Paroliere contains approximately 60,000 words - but there are many more out there! You’ve still got a shot at conquering the game!

### How It Works
1. **Input your letters**: Enter a series of letters into the 4x4 grid to start the game
2. **Search for words**: Form words by navigating through adjacent letters
3. **Maximize your score**: Challenge yourself to find as many valid words as possible and aim for the highest score!
4. **Did You Manage To Beat The Program?**


### Instructions For Use
This guide provides a simple and straightforward explanation on how to clone, compile, and run the project. 
It is intended for users who are using Git and GCC on a Windows system via the command prompt.

**Follow these steps**:

1. **Open the Command Prompt**
2. **Navigate to the desired folder**: use the *cd* command to change to the directory where you want to clone the repository
3. **Clone the repository**:
```
   git clone https://github.com/Andrea-Calandri/paroliere.git
```
4. **Navigate to the project folder**:
```
   cd paroliere
```
5. **Compile the project**:
```
   gcc -o paroliere src/main.c src/paroliere.c -I src/
```
6. **Run the program**:
```
     paroliere.exe
```
7. **Time To Play**

