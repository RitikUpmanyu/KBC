### This is a C based QnA type game (KBC/Who Wants to Be a Millionaire?) made as an assignment

# How to run the code and play the game:
1. The main file is called **kbc.c** . It is a console Application. Please maximize your console to full screen.
2. The input files are ->
```
1) questions.txt used for reading questions and options.
2) features.c used for displaying questions, options, money and implementing lifelines. 
3) formatting.c used for displaying boxes around questions, options and money.
```
*THESE 3 FILES SHOULD BE IN SAME DIRECTORY AS **kbc.c** for the code to compile properly.*
3. Compilation-
   * To compile the code on Linux/mac, just go to the directory and run```gcc kbc.c``` and then```./a.out```
   * To compile and run in Windows, again go to the directory and run```gcc kbc.c``` and then```a.exe```
4. *count.txt* will automatically be generated when you compile the code for the first time,
   it will keep track of how many times the game has been played. So that, we can display different questions based on the count.
   *To test this you can try to play again after losing or quitting.*
5. When you compile and run *kbc.c*, it will display the welcome screen, press *ENTER* to start the game, or *q/Q* to quit.
6. When you press *ENTER* on the welcome screen, the first question will be displayed on the screen.
   Along with your lifelines and a money board.
7. For the first **4** questions, You will only have **30** seconds to answer.
8. You can press *a/A/b/B/c/C/d/D* and then **ENTER** to choose an option or you can take lifeline *(if they are still remaining)*-
    * Press *l/L + ENTER* for **50-50**.
    * Press *f/F + ENTER* for **Flip-the-question**.
9. After choosing an option, you can lock it by entering *y/Y* or go back to choosing again by entering anything else.
10. You can even quit at any point by entering *q/Q*. After you lose the game you can play again by entering *p/P*.

#### Known limitation:

* If the width of the console is too small, everything can become disoriented. *So, please use maximum width*.
