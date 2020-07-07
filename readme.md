# Description of how to run the code and play the game:
1. The main file is called kbc.c . It is a console Application. Please maximize your console to full screen.
2. The input files are -> 1. questions.txt used for reading questions and options 
                          2. features.c used for displaying questions, options, money and implementing lifelines. 
                          3. formatting.c used for displaying boxes around questions, options and money.
   *THESE 3 FILES SHOULD BE IN SAME DIRECTORY AS THE kbc.c for the code to compile properly.
3. count.txt will automatically be generated when you compile the code for the first time,
   it will keep track of how many times the game has been played. So that, we can display different questions based on count.
   To test this you can try to play again after losing or quitting.
4. When you compile and run kbc.c, it will display the welcome screen, press ENTER to start the game, or [q]/[Q]to quit.
5. When you press ENTER on the welcome screen, the first question will be displayed on the screen.
   Along with your lifelines and a money board.
6. For the first 4 questions, You will only have 30 seconds to answer.
7. You can press a/A/b/B/c/C/d/D and then ENTER to choose a option or you can take lifeline if they are still remaining-
    1. Press l/L + ENTER for 50-50.
    2. Press f/F + ENTER for Flip-the-question.
8. After choosing a option, you can lock it by entering y/Y or go back to choosing again by entering anthing else.
9. You can even quit at any point by entering q/Q. After you loose the game you can play again by entering p/P.

### Known limitations of the code:

1. If width of console is too small, everything can become disoreinted. So, please use maximum width.

