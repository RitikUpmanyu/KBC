#############################################################
ReadMe for assignment submitted by 2019B3PS0517P
Practical section number: P3
Asignment question attempted: 1
#############################################################
Team:
1. 2019B3PS0517P Ritik Upmanyu
2. 2019B1PS1040P Kush Gambhir
#############################################################
Description of how to run the code and observe the output:
1. The main file is called 2019B3PS0517_P3.c . It is a console Application. Please maximize your console to full screen. 
2. The input files are -> 1. questions.txt used for reading questions and options
		    			  2. features.c used for displaying questions, options, money and implementing lifelines.
		    			  3. formatting.c used for displaying boxes around questions, options and money. 
	THESE 3 FILES SHOULD BE IN SAME DIRECTORY for the code to compile.
3. count.txt will automatically be generated when you compile the code for the first time, 
	it will keep track of how many times the game has been played. So that, we can display alternate questions based on count. 
4. When you run the the compiled 2019B#2019B3PS0517_P3.c, it will display the welcome screen, press ENTER to start the game, or [q]/[Q]to quit.
5. When you press ENTER on the welcome screen, the first question will be displayed on the screen. along with your lifelines and a money board.
6. For the first 4 questions, You will only have 30 seconds to answer.
7. You can enter a/A/b/B/c/C/d/D to choose a option or you can take lifeline if they are still remaining-
	1. Enter l/L for 50-50.
	2. Enter f/F for Flip-the-question.
8. You can even quit at any point by entering q/Q. After you loose the game you can play again by entering p/P.

############################################################
Known limitations of the code (if you have not been able to completely/fully implement certain features that were asked):
1. If width of console is too small, everything can become disoreinting. So, please use maximum width.
2. Code is a little too big.
#############################################################
Contributions of the team members:
Ritik Upmanyu did reading, fomatting and displaying questions, options and money and testing.
Kush Gambhir did Both lifelines and also worked on taking User-Input and also helped in testing.
#############################################################