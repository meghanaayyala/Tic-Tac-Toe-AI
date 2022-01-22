#include<bits/stdc++.h> 
#include<iostream>
using namespace std; 

#define AI 1 
#define HUMAN 2 

#define AIMOVE 'O' 
//AI Symbol is 'O'
#define HUMANMOVE 'X'   
//Human Symbol is 'X'

// A function to print the current Tic Tac Toe Board
void showBoard(char board[][3]) 
{ 
	
/*
  Indices of Tic Tac Toe Board for your reference
  [0][0] | [0][1] | [0][2]
  ------------------------
  [1][0] | [1][1] | [1][2]
  ------------------------
  [2][0] | [2][1] | [2][2]
*/
	printf("\t\t\t %c | %c | %c \n", board[0][0], board[0][1], board[0][2]); 
	printf("\t\t\t-----------\n"); 
	printf("\t\t\t %c | %c | %c \n", board[1][0], board[1][1], board[1][2]); 
	printf("\t\t\t-----------\n"); 
	printf("\t\t\t %c | %c | %c \n\n", board[2][0], board[2][1], board[2][2]);  
} 

// A function to show the instructions
//Basically show the naming system in our program
//We name each position as 1,2,3,4...so on
void showInstructions() 
{ 
	printf("\nChoose a cell numbered from 1 to 9 as below and play\n\n"); 
	
	printf("\t\t\t 1 | 2 | 3 \n"); 
	printf("\t\t\t-----------\n"); 
	printf("\t\t\t 4 | 5 | 6 \n"); 
	printf("\t\t\t-----------\n"); 
	printf("\t\t\t 7 | 8 | 9 \n\n"); 
} 


// A function to initialise the game, that is set up blank characters in the board array
//' ' denotes that the character present in that particular position is empty
void initialise(char board[][3]) 
{	
	// Initially the board is empty 
	for (int i=0; i<3; i++) 
	{ 
		for (int j=0; j<3; j++) 
			board[i][j] = ' '; //setting up each and every character in the board to ' '
	} 
} 

// A function to declare the winner of the game 
void declareWinner(int whoseTurn) 
{ 
	if (whoseTurn == AI) //if the last turn on putting the winning symbol was of the AI then it is declared as the winner
		cout<<"AI is the winner!"<<endl; 
	else //else it is declared that the human is the winner
    cout<<"HUMAN is the winner!"<<endl;
} 

//A function to check if any of the rows are crossed i.e. if any of the rows have the same symbol(equal) and they are all not equal to ' ' (empty)
bool rowCrossed(char board[][3]) 
{ 
	for (int i=0; i<3; i++) 
	{ 
		if (board[i][0] == board[i][1] && 
			board[i][1] == board[i][2] && 
			board[i][0] != ' ') 
			return (true); 
	} 
	return(false); 
} 
//A function to check if any of the columns are crossed i.e. if any of the columns have the same symbol(equal) and they are all not equal to ' ' (empty) 
bool columnCrossed(char board[][3]) 
{ 
	for (int i=0; i<3; i++) 
	{ 
		if (board[0][i] == board[1][i] && 
			board[1][i] == board[2][i] && 
			board[0][i] != ' ') 
			return (true); 
	} 
	return(false); 
} 

//A function to check if any of the diagonals are crossed i.e. if any of the diagonals have the same symbol(equal) and they are all not equal to ' ' (empty)
bool diagonalCrossed(char board[][3]) 
{ 
	if (board[0][0] == board[1][1] && 
		board[1][1] == board[2][2] && 
		board[0][0] != ' ') 
		return(true); 
		
	if (board[0][2] == board[1][1] && 
		board[1][1] == board[2][0] && 
		board[0][2] != ' ') 
		return(true); 

	return(false); 
} 

// A function which returns true if any of the rows or columns or diagonals are crossed
//Else it returns false
bool gameOver(char board[][3]) 
{ 
  // || symbol means or. basic operator if any one of the conditions is true it returns true else returns false
	return(rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board) ); 
}

// Minimax Algorithm taking arguments as depth and a boolean variable isAI
//depth denotes essentially the number of recursive calls, so the different levels in our tree diagram would be called different depths, and the maximum depth would be 8
//isAI is a boolean variable, which is very important in determining whether we want to maximize or minimize our board
//if isAI is true then we will maximize as we want our AI to win, else if it is false then we will minimize
int minimax(char board[][3], int depth, bool isAI)
{
	int score = 0;   //to determine our intermediate score that is in between recursion calls
	int bestScore = 0; //as name indicates to determine the bestScore

  //base condition or terminating condition
  //if gameOver function returns a true value then we can end our minimax algorithm
	if (gameOver(board) == true)
	{
		if (isAI == true)
			return -1;  //returns -1 to show that AI has won
		if (isAI == false)
			return +1;  //else return 1 to show HUMAN has won
	}


  //recursive call function 
	else
	{
		if(depth < 9) //our depth shouldn't increase by 9 any time
		{
			if(isAI == true)    //if isAI is true, we would like to maximize our board or score
			{
				bestScore = -100; //arbitrary value of our bestScore
				for(int i=0; i<3; i++)
				{
					for(int j=0; j<3; j++)
					{
						if (board[i][j] == ' ')
						{
							board[i][j] = AIMOVE; //iterate through each and every element in our board and place the computer move
              //then we call the minimax function again recursively for this particular game position
							score = minimax(board, depth + 1, false); 
              //observe that we increasing the depth by 1, and also we are placing the isAI boolean as false, this means that we are calling the next minimax function with the intention to minimize
							board[i][j] = ' '; //once minimax algorithm is called for each square we just go back to the original state
							if(score > bestScore) 
              //since we are maximizing, if the score we got we got was greater than our bestScore in this case -100, we put that as the new bestScore
							{
								bestScore = score; 
                //updating bestScore with the new score value
							}
						}
					}
				}
				return bestScore;
			}
			else
			{
        //if we want to actually perform minimizing and not maximizing 
				bestScore = 100;
        //we initially set it to a high value because in further recursion calls we are going to get a number always less than bestScore since we are minimizing
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
            //iterate through each and every square in the board

						if (board[i][j] == ' ')
						{
              //if a position is empty, that is there is an empty square we place the humanmove symbol and then call the minimax function again, but this time with the intent of maximizing
							board[i][j] = HUMANMOVE;
							score = minimax(board, depth + 1, true);

							board[i][j] = ' '; //after minimax is called and score is obtained the board returns to its original position
							if (score < bestScore)
							{
								bestScore = score;
                //if the score obtained is lesser than bestScore, since we are minimizing, it is now the new bestScore
							}
						}
					}
				}
				return bestScore;
			}
		}
		else
		{
      //none of the above conditions, just return 0
			return 0;
		}
	}
  return 0;
}

// Function to calculate best move
int bestMove(char board[][3], int moveIndex)
{
	int x = -1, y = -1;
	int score = 0, bestScore = -100;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j <3; j++)
		{
      //iterate through every position in the board
			if (board[i][j] == ' ')
			{
        //if a board is empty we place the AI Move, and then call the minimax with the intention to minimize
				board[i][j] = AIMOVE;
				score = minimax(board, moveIndex+1, false);
				board[i][j] = ' ';
				if(score > bestScore)
				{
          //if the obtained score is greater than bestScore that particular score is now the bestScore and x and y take the values of i and j, that is x and y now represent which move position is the best, or which moveindex is best
					bestScore = score;
					x = i;
					y = j;
				}
			}
		}
	}
  //because in our representation we have the board indiced as 
  /*
  Indices of Tic Tac Toe Board for your reference
  [0][0] | [0][1] | [0][2]
  ------------------------
  [1][0] | [1][1] | [1][2]
  ------------------------
  [2][0] | [2][1] | [2][2]
*/
//and 0,0 represents 1st square, 0,1 represents 2nd square and so on, if we want to say that well 1,1 is your best moveIndex we should first translate it to 1,2,3 and so on...so if 1,1 is the best moveIndex then x=1 and y=1 and we are returning x*3+y, which means we are returning 4th position or 5th square.

	return x*3+y;
}

// A function to play Tic-Tac-Toe 
void playTicTacToe(int whoseTurn) 
{ 
	char board[3][3]; 
	int moveIndex = 0, x = 0, y = 0;

	initialise(board); //setting up the board to null characters
	showInstructions(); //print all the instructions 
	
	// Keep playing till the game is over or it is a draw 
	while (gameOver(board) == false && moveIndex != 9) 
	{ 
		int n;
		if (whoseTurn == AI) 
		{
			n = bestMove(board, moveIndex);
      //get the best move from minimax functions and best move functions
			x = n / 3; //get x index
			y = n % 3; //get y index
			board[x][y] = AIMOVE; //putting ai move in that index
			printf("AI has put a %c in cell %d\n\n", AIMOVE, n+1);
			showBoard(board); //printing board
			moveIndex ++; 
			whoseTurn = HUMAN; //setting the turn to now humans chance
		} 
		
		else if (whoseTurn == HUMAN) 
		{
			printf("You can insert in the following positions : ");
			for(int i=0; i<3; i++)
				for (int j = 0; j < 3; j++)
					if (board[i][j] == ' ')
						printf("%d ", (i * 3 + j) + 1);
			printf("\n\nEnter the position = ");
			scanf("%d",&n);
			n--;
			x = n /3;
			y = n % 3; 
			if(board[x][y] == ' ' && n<9 && n>=0)
			{
				board[x][y] = HUMANMOVE; 
				printf ("\nHUMAN has put a %c in cell %d\n\n", HUMANMOVE, n+1); 
				showBoard(board); 
				moveIndex ++; 
				whoseTurn = AI;
			}
			else if(board[x][y] != ' ' && n<9 && n>=0)
			{
				printf("\nPosition is occupied, select any one place from the available places\n\n");
			}
			else if(n<0 || n>8)
			{
				printf("Invalid position\n");
			}
		} 
	} 

	// If the game has drawn 
	if (gameOver(board) == false && moveIndex == 9) 
		printf("It's a draw\n"); 
	else
	{ 
		// Toggling the user to declare the actual winner 
		if (whoseTurn == AI) 
			whoseTurn = HUMAN; 
		else if (whoseTurn == HUMAN) 
			whoseTurn = AI; 
		
		declareWinner(whoseTurn); 
	} 
} 

int main() 
{ 
	printf("\n-------------------------------------------------------------------\n\n");
	cout<<"Lets play Tic Tac Toe!"<<endl;
	printf("\n-------------------------------------------------------------------\n\n");
	char cont='y';
	do {
		char choice;
	 	printf("So do you want to make the first move?(y/n) : \n");
	 	scanf(" %c", &choice);

		if(choice=='n')
    {
      cout<<"Alright then I'll play first!"<<endl;
			playTicTacToe(AI);
    }
		else if(choice=='y')
    {
      cout<<"Okay, you go ahead if you are so clever."<<endl;
			playTicTacToe(HUMAN);
    }
		else
			printf("Invalid choice\n"); 
        
		printf("\nHa! Hungry for more? I bet you won't win this time!(y/n):");
       		scanf(" %c", &cont);
	} while(cont=='n');
	return (0); 
} 