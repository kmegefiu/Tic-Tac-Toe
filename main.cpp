#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct userType
{
    string username;
    int score;
};


void readUsers(userType users[], int NUMUSERS);
void writeUsers(userType users[], int NUMUSERS);
void sortUsers(userType users[], int NUMUSERS);
void displayUsers(userType users[], int NUMUSERS);
void initUsers(userType users[], int NUMUSERS);
void printMenu();
void printGameInstruction(int NUMUSERS);
void initBoard(char board[][3]);
void printBoard(char board[][3]);
void printLocationOnBoard();
int getSelectedMenuChoice();
string getPlayerName(int player);
bool isScoreBoardFull(userType users[], int NUMUSERS);
char isGameOver(char board[][3]);
bool isGameTied(char board[][3]);
void startNewGame(userType users[], int NUMUSERS, char board[][3]);
void saveScore(userType users[], int NUMUSERS, string player, int score);


int main()
{
    const int NUMUSERS = 10;
    userType myGamers[NUMUSERS];
    char board[3][3];
    bool quitGame = false;
    int menu = -1;
    
    // Program
    initBoard(board);
    initUsers(myGamers, NUMUSERS);
    printGameInstruction(NUMUSERS);
    do {
        printMenu();
        menu = getSelectedMenuChoice();

        // Make decision based on menu options selected by user
        switch (menu) {
            case 0: // Exiting Game
                quitGame = true;
                break;

            case 1: // New Game
                cout << "New Game ..." << endl;
                startNewGame(myGamers, NUMUSERS, board);
                break;

            case 2: // Display all users of the game
                displayUsers(myGamers, NUMUSERS);
                break;

            case 3: // Load users in their respective score
                readUsers(myGamers, NUMUSERS);
                break;

            case 4: // Sort Users
                cout << "Sorting users" << endl;
                sortUsers(myGamers, NUMUSERS);
                break;

            case 5: // Save game
                writeUsers(myGamers, NUMUSERS);
                break;

            default:
                cout << "This Menu option is not yet supported" << endl;
                break;
        }

        cout << endl;   // For formatting purposes
    } while(!quitGame);

    cout << "Succeffully exited the game" << endl;
    system("Pause");
    return 0;
    
}

void startNewGame(userType users[], int NUMUSERS, char board[][3]) {
    cout << "--------------------------------------------------" << endl;
    string p1Name = getPlayerName(1);
    string p2Name = getPlayerName(2);
    
    cout << "\nGame Started ..." << endl;
    string winner = "";
    string player = p1Name;
    char playerIndicator = 'X';
    int pEntry = 0;
    bool gameOver = false;
    
    
    do {
        // Show board instruction
        printLocationOnBoard();
        cout << endl;
        // Show current game board
        printBoard(board);
        
        cout << player << "'s turn." << endl;
        cout << "Enter your play location: ";
        cin >> pEntry;
        cout << endl;   // Formatting
        
        switch (pEntry) {
            case 1:
                board[0][0] = playerIndicator;
                break;
            case 2:
                board[0][1] = playerIndicator;
                break;
            case 3:
                board[0][2] = playerIndicator;
                break;
            case 4:
                board[1][0] = playerIndicator;
                break;
            case 5:
                board[1][1] = playerIndicator;
                break;
            case 6:
                board[1][2] = playerIndicator;
                break;
            case 7:
                board[2][0] = playerIndicator;
                break;
            case 8:
                board[2][1] = playerIndicator;
                break;
            case 9:
                board[2][2] = playerIndicator;
                break;
            default:
                break;
        }
        
        // Check if the game is Over
        if(isGameTied(board) == true) {
            gameOver = true;
            printBoard(board);
            cout << "Game tied!" << endl;
        } else if(isGameOver(board) == 'X') {
            gameOver = true;
            printBoard(board);
            cout << p1Name << " won!" << endl;
            saveScore(users, NUMUSERS, p1Name, 10);     // Call Save function
        } else if(isGameOver(board) == 'O') {
            gameOver = true;
            printBoard(board);
            cout << p2Name << " won!" << endl;
            saveScore(users, NUMUSERS, p2Name, 10);     // Call Save function
        }
        
        
        // Switch player's turn, if game is not over
        if(gameOver == false) {
            if(player == p1Name) {
                player = p2Name;
                playerIndicator = 'O';
            } else {
                player = p1Name;
                playerIndicator = 'X';
            }
        }
        
    } while(!gameOver);
}

void printMenu() {
    cout << "**************************************************" << endl;
    cout << "*                   MAIN MENU                    *" << endl;
    cout << "**************************************************" << endl;
    cout << "1. New Game" << endl;
    cout << "2. Display Users" << endl;
    cout << "3. Load Users" << endl;
    cout << "4. Sort Users" << endl;
    cout << "5. Write Score to file" << endl;
    cout << "0. Exit game" << endl;
    cout << "--------------------------------------------------\n" << endl;
}


int getSelectedMenuChoice() {
    int menuChoice = 0;
    cout << "Please enter a selection: ";
    cin >> menuChoice;
    cout << endl;       // Added for formatting
    while(menuChoice < 0 || menuChoice > 5) {
        cout << "ERROR! Invalid Input. (Only numbers 0 - 5 are accepted" << endl;
        cout << "Please enter a selection: ";
        cin >> menuChoice;
        cout << endl;       // Added for formatting
    }
    return menuChoice;
}

bool isScoreBoardFull(userType users[], int NUMUSERS) {
    // Check is there is space in scoreboard
    for(int i=0; i < NUMUSERS; i++) {
        if(users[i].score == -1) {
            return false;
        }
    }
    return true;
}

void saveScore(userType users[], int NUMUSERS, string player, int score) {
    char save = ' ';
    cout << player << ", would you like to save your score? (Y/N): ";
    cin >> save;
    cout << endl;   // For formatting
    
    // User request to save score
    if(save == 'y' || save == 'Y') {
        displayUsers(users, NUMUSERS);
        cout << endl;           // For formatting
        
        int tmp = -1;
        bool foundSpot = false;
        // If there is space in the Scoreboard, add score
        if(isScoreBoardFull(users, NUMUSERS) == false) {
            // Look for a spot, and add score
            for(int i=0; i < NUMUSERS; i++) {
                if(foundSpot == false && users[i].score == -1) {
                    tmp = i;
                    foundSpot = true;
                }
            }
            
            // Add new score
            users[tmp].username = player;
            users[tmp].score = score;
        } else {
            // Prompt user to replace score
            do {
                cout << "Enter a score to replace/delete (1-10): ";
                cin >> tmp;
            } while(tmp < 1 || tmp > 10);
            
            // Replace score from scoreboard
            users[tmp].username = player;
            users[tmp].score = score;
        }
        
        // Redisplay list of scores to show user updates
        // then write new scores to files
        displayUsers(users, NUMUSERS);
        writeUsers(users, NUMUSERS);
    }
}

void initBoard(char board[][3]) {
    for(int i= 0; i < 3; i++) {
        for(int j= 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

string getPlayerName(int player) {
    string name = "";
    cout << "Enter Payer " << player << "'s name: ";
    cin >> name;
    return name;
}

bool isGameTied(char board[][3]) {
    for(int i= 0; i < 3; i++) {
        for(int j= 0; j < 3; j++) {
            if(board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

// Check if one of the player wins,
// if a player wins return the player character (X or O)
// If no player wins, return ''
char isGameOver(char board[][3]) {
    // Horizontal possibilities
    for(int i = 0; i < 3; i++) {
        if(board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return board[i][0];
        }
    }
    
    // Vertical possibilities
    for(int i = 0; i < 3; i++) {
        if(board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return board[0][i];
        }
    }
    
    // Diagonal possibilities
    if((board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) ||
       (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])) {
        return board[1][1];
    }
    return ' ';
}

void printLocationOnBoard() {
    cout << "Location on board. Use the following number\nwhen you wish to make a move" << endl;
    cout << "  1  |  2  |  3  " << endl;
    cout << "-----|-----|-----" << endl;
    cout << "  4  |  5  |  6  " << endl;
    cout << "-----|-----|-----" << endl;
    cout << "  7  |  8  |  9  " << endl;
}

void printBoard(char board[][3]) {
    cout << "  " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << "  " << endl;
    cout << "-----|-----|-----" << endl;
    cout << "  " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << "  " << endl;
    cout << "-----|-----|-----" << endl;
    cout << "  " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << "  " << endl;
}

void printGameInstruction(int NUMUSERS) {
    cout << "WELCOME MESSAGE" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "Welcome to the Tic Tac Toe Game. This game suports" << endl;
    cout << "a maximum of 2 players. The game allows you to see" << endl;
    cout << "the list scores of past users (" << NUMUSERS <<"), load" << endl;
    cout << "a previously saved game, save a game for later on" << endl;
    cout << "and play the game of course" << endl << endl;
}

void readUsers(userType users[], int NUMUSERS)
{
    int index = 0;
    ifstream indata;
    indata.open("Text.txt");
    
    while (!indata.eof() && index < NUMUSERS)
    {
        indata >> users[index].username >> users[index].score;
        index++;
    } //end of while
    indata.close();
    
    
    
}
void writeUsers(userType users[], int NUMUSERS)
{
    ofstream outdata;
    outdata.open("Text.txt");
    
    for (int i = 0; i < NUMUSERS; i++)
    {
        if (users[i].score != -1)
            outdata << users[i].username << " " << users[i].score << endl;
    }
    outdata.close();
}
void sortUsers(userType users[], int NUMUSERS)
{
    
    
    
}

void displayUsers(userType users[], int NUMUSERS)
{
    for (int i = 0; i<NUMUSERS; i++)
        cout << users[i].username << " " << users[i].score << endl;
    
    
}
void initUsers(userType users[], int NUMUSERS)
{
    for (int i = 0; i<NUMUSERS; i++)
    {
        users[i].username = "noName";
        users[i].score = -1;
    }
    
}


