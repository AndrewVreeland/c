#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "casino.h"

// main function
int main()
{
    srand(time(NULL));
    // function calls
    logo();
    sampleCards();
    play();

    // utilizing getchar as system pause was casuing me errors with ubuntu. (I have vscode installed through ubuntu)
    printStatements();

    // int return
    return 0;
}
// logo dunction
void logo()
{
    // asci art
    printf("   /$$$$$$     /$$$$$$     /$$$$$$    /$$$$$$   /$$   /$$     /$$$$$$$$    \n");
    printf("  /$$    $$   /$$    $$   /$$__  $$  |_  $$-/  | $$$ | $$    /$$___   $$       \n");
    printf("  /$$__  $$  /$$__  $$   |$$   \\__/    | $$    | $$$$| $$   | $$   \\  $$      \n");
    printf(" | $$  \\__/  |$$   \\ $$  | $$$$$$      | $$    | $$ $$ $$   | $$    | $$           \n");
    printf(" | $$        | $$$$$$$$  \\____  $$     | $$    | $$  $$$$   | $$    | $$          \n");
    printf(" | $$   /$$  | $$__  $$  /$$  \\ $$     | $$    | $$ \\ $$$   | $$    | $$              \n");
    printf(" |  $$$$$$/  | $$  | $$  | $$$$$$/    /$$$$$$  | $$  \\ $$   | $$$$$$$$/             \n");
    printf("  \\______/   |__/  |__/  \\______/   |_______/   __/  \\__/    \\_______/                            \n");
}
// sampleCards function
void sampleCards()
{
    printf("\n\n");
    // cards asci art
    printf(" .----------.    .----------.     .----------.     .----------.    \n");
    printf(" |A .----.  |    |A .----.  |     |A .----.  |     |A .----.  |\n");
    printf(" |  :    :  |    |  :    :  |     |  :    :  |     |  :    :  |\n");
    printf(" |  : /\\ :  |    |   (\\/)   |     |  : () :  |     |  : /\\ :  |\n");
    printf(" |  : \\/ :  |    |  : \\/ :  |     |  ()  ()  |     |  ( /\\ )  |\n");
    printf(" |  :    :  |    |  :    :  |     |  :    :  |     |  :    :  |\n");
    printf(" |  '----' A|    |  '----'A |     |  '----'A |     |  '----' A|\n");
    printf(" `----------'    `----------'     `----------'     `----------'\n");
    printf("   Diamonds         Hearts            Clubs           Spades \n\n");
}

// general game flow
void play()
{
    char playerName[30];
    double bank = 0.0;
    int gameSelection = 0;

    printf("Please enter your first name...\n");
    scanf("%s", playerName); // saves user input to player name

    while (TRUE) // loop that exits on correct input, prevents negative numbers and characters
    {
        printf("Please enter total cash, (e.g. 100.25)...\n");
        int playerInputCheck = scanf("%lf", &bank); // returns 1 if true and 0 if false also saves user input to bank

        // checks player input to see if value is a number and if bank is > than 0
        if (playerInputCheck == TRUE && bank > 0)
        {
            // if this fails then it will start the while loop over
            break;
        }
        // clears input

        printf("Invalid input. Please input a value larger than zero.\n");
    }

    printf("Value accepted: %.2f\n", bank);

    printf("Hello %s, what game would you like to play?\n", playerName);
    gameSelection = 1;
    while (gameSelection != QUIT)
    {
        gameSelection = gameMenu();
        // Switch statement handling game selection.
        switch (gameSelection)
        {
        case 0:
            printf("Thanks for coming %s, have a good day!\n\n", playerName);
            break;
        case 1:
            printf("%s, get ready to play %s!\n\n", playerName, BLACKJACK_STR);
            bank = playBlackJack(playerName, bank);
            printf("%s your bank total is $%lf\n", playerName, bank);
            break;

        case 2:
            printf("%s, get ready to play %s!\n\n", playerName, KENO_STR);
            bank = playKeno(playerName, bank);
            printf("%s your bank total is $%lf\n", playerName, bank);
            break;

        case 3:
            printf("%s, get ready to play %s!\n\n", playerName, POKER_STR);
            bank = playVideoPoker(playerName, bank);
            printf("%s your bank total is now $%lf\n", playerName, bank);
            break;

        case 4:
            printf("%s, get ready to play %s!\n\n", playerName, ROULETTE_STR);
            bank = playRoulette(playerName, bank);
            printf("%s your bank total is now $%lf\n", playerName, bank);
            break;

        default:
            printf("%s, Invalid selection, Exiting.\n", playerName);
        }
    }
}

// game selection menu
int gameMenu()
{
    int gameSelection = 0;
    int numOfGames = 0;

    // player game selection options
    printf("%d. %s\n", QUIT, QUIT_STR);
    printf("%d. %s\n", BLACKJACK, BLACKJACK_STR);
    printf("%d. %s\n", KENO, KENO_STR);
    printf("%d. %s\n", POKER, POKER_STR);
    printf("%d. %s\n", ROULETTE, ROULETTE_STR);

    // saves user input for game selection

    while (TRUE)
    {
        int playerInputCheck = scanf("%d", &gameSelection); // assigns 1 to playerInputCheck if true and zero if false. assigns input value to game.

        if (playerInputCheck == TRUE && gameSelection >= QUIT && gameSelection <= NUM_PLAYABLE_GAMES) // checks if player input is a number and if that number is in the range from 0 to 5
        {
            break; // if true this breaks us from the loop
        }

        while (getchar() != '\n')
            ;                                             // clears user input
        printf("please input a number from the list.\n"); // prompts user to input a correct value.
    }

    // returns needed game selection number IE 1-5
    return gameSelection;
}

double playRoulette(char player[30], double bank)
{

    char wheel[ROULETTE_SIZE];
    int gameChoice = 0;
    double bet = 0.0;
    int chip = 0;
    int number = 0;
    double winnings = 0;

    for (int i = 0; i < ROULETTE_SIZE; i++) // sets roulette wheel array data
    {
        wheel[i] = i;
    }
    printf("%s, your bank contains $%lf, please place your bet\n", player, bank);

    while (TRUE)
    {                                                            // infinte loop that is broken by player input
        int playerInputScheck = scanf("%lf", &bet);              // returns 1 if true or 0 if false
        if (playerInputScheck == TRUE && bet <= bank && bet > 0) // while player bet is true and bet is lees or equal to bank then continue
        {
            bank -= bet; // subtract bet
            break;       // break while loop
        }

        while (getchar() != '\n')
            ;
        printf("%s, please place a proper bet you currently have $%lf in your bank\n", player, bank); // prompts user for proper input
    }

    printf("%s, please choose your game\n", player);
    // menu items for roulette
    printf("%d. %s\n", STRAIGHT, STRAIGHT_STR);
    printf("%d. %s\n", ODD_EVEN, ODD_EVEN_STR);
    printf("%d. %s\n", LOW_HIGH, LOW_HIGH_STR);
    printf("%d. %s\n", QUIT, QUIT_STR);

    while (TRUE)
    {                                                    // infitie loop that is broken by player input
        int playerInputCheck = scanf("%d", &gameChoice); // makes sure user input is a digit returns 1 if true and 0 if false
        if (playerInputCheck == TRUE && gameChoice >= QUIT && gameChoice <= NUM_OF_ROULETTE_GAME_TYPES)
        {
            break;
        }
        while (getchar() != '\n')
            ;
        printf("%s, please input a number from the list \n", player); // prompts user for proper input
    }

    switch (gameChoice) // switch statement for quitting and bet options
    {
    case 0:
        bank += bet;
        bet = 0;
        printf("Now returning to main menu \n\n");
        return bank;
    case 1:
        printRoulette(wheel); // prints numbers of roulette table
        chip = straight(player);
        break;
    case 2:
        chip = oddEven(player);
        break;
    case 3:
        chip = lowHigh(player);
        break;

        return bank;
    }

    number = rouletteSpin(wheel); // spins the table and generates random number
    printf("%s, the ball landed on %d\n", player, number);

    winnings = rouletteWinCheck(gameChoice, number, chip, bet); // collects winnings and assings the return value to winngins
    bank += winnings;                                           // adds winnings to bank

    if (winnings > 1)
    { // prompts user based on whether they won or not
        printf("Congrats %s! Your winnings are %lf$\n", player, winnings);
    }
    else
    {
        printf("Sorry %s, your bank value is at $%lf. No winnings this time!\n", player, bank);
    }
    return bank;
}

// manual statement due to System("pause"); not working with my setup
void printStatements()
{
    // clears cache, guarentees we don't skip the pause below.
    while ((getchar()) != '\n')
        ;

    printf(" \nPlease press enter to continue.....");
    getchar();
}

void printRoulette(char wheel[37]) // method to print roulette table
{
    for (int i = 0; i < ROULETTE_SIZE; i++)
    {
        printf("%d ", wheel[i]);
    }
    printf("\n");
}

int straight(char player[30]) // rule set for picking 1 number
{
    int chipPlacement = 0;
    printf("%s what is your chip placement? 0 - 36\n", player);

    while (TRUE) // infitie loop till the user ends it via input
    {
        int playerInputCheck = scanf("%d", &chipPlacement);                                  // will return 0 if thrue or 1 if false. guartees propper input
        if (playerInputCheck == TRUE && chipPlacement > 0 && chipPlacement <= ROULETTE_SIZE) // checks input to make sure it's within parameters
        {
            break; // if so break loop
        }
        while (getchar() != '\n')
            ;                                                                 // clear text
        printf("%s please place chips on proper locaitons 0 - 36\n", player); // prompts user to try new input
    }

    return chipPlacement; // returns the users chip placement
}

int lowHigh(char player[30]) // rule set for low or high value sets
{
    int chipPlacement = 0;
    printf("%s please place your chips, 0 for Low (0-18) or 1 for High(19-36)\n", player);

    while (TRUE) // similar while loops as before. refer to straight method for code comparison
    {
        int playerInputCheck = scanf("%d", &chipPlacement);
        if (playerInputCheck == TRUE && chipPlacement == TRUE || chipPlacement == FALSE)
        {
            break;
        }

        while (getchar() != '\n')
            ;
        printf("%s, please place your chips in the proper locations 1 or 0\n", player);
    }
    return chipPlacement;
}

int oddEven(char player[30]) // rule set for odd or even bet placements
{
    int chipPlacement = 0;
    printf("%s, please choose your placement, 0 for Even, 1 for Odd\n", player);
    while (TRUE) // similar while loops as before. refer to straight method for code comparison
    {
        int playerInputCheck = scanf("%d", &chipPlacement);
        if (playerInputCheck == TRUE && chipPlacement == 0 || chipPlacement == 1)
        {
            break;
        }

        while (getchar() != '\n')
            ;
        printf("%s, please place your chips in the proper locations 1 or 0\n", player);
    }
    return chipPlacement;
}

int rouletteSpin(int wheel[37]) // returns random number within the size restriction of the rouletter board
{
    int number = 0;
    return number = (rand() % (ROULETTE_SIZE));
}

double rouletteWinCheck(int choice, double bet, int number, int chipPlacement) // checks if user wins or looses
{
    double winnings = 0;

    switch (choice)
    {
    case 1:
        if (number == chipPlacement) // if placement and landed value are the same then calculate winnings
        {
            bet *= 35;
            winnings += bet;
        }
        break;
    case 2:
        if (chipPlacement % 2 == 0 && number % 2 == 0) // if placement and landed value are even then calculate winnings
        {
            bet *= 2;
            winnings += bet;
        }
        else if (chipPlacement % 2 == 1 && number % 2 == 1) // same as above but for odd
        {
            bet *= 2;
            winnings += bet;
        }
        break;
    case 3:
        if (chipPlacement == 0 && number >= 1 && number <= 18) // low to high rule set if numbers are low then reward
        {
            bet *= 2;
            winnings += bet;
        }
        else if (chipPlacement == 1 && number >= 19 && number <= 36) // if numbers are high then reward
        {
            bet *= 2;
            winnings += bet;
        }
        break;

    default:
        break;
    }

    return winnings;
}

// Keno Methods
double playKeno(char playerName[30], double bank)
{
    // initilizing arrays
    int kenoCard[ROWS][COLS];
    int kenoNumbers[KENO_NUMS];
    int kenoSelect[KENO_SELECT];
    double winnings = 0.0; // total winnings return variable

    memset(kenoNumbers, 0, sizeof(kenoNumbers));
    memset(kenoSelect, 0, sizeof(kenoSelect));
    populateKenoCard(kenoCard);
    printf("hello %2s, the bet for playing Keno is %lf.\n", playerName, KENO_BET);

    if (bank < KENO_BET)
    { // leaves game is player doesnt have enough for bet
        printf("Sorry %s, the bet for playing keno is $20.00\n", playerName);
        return bank;
    }
    bank -= KENO_BET; // subtracts $20 for bet

    printf("%s, your keno is card is being displayed.\n", playerName);
    displayKenoCard(kenoCard); // dispalying keno cards
    printf("%s, please select your keno numbers. \n", playerName);

    getKenoNumbers(playerName, kenoNumbers);                     // keno number selection
    qsort(kenoNumbers, KENO_NUMS, sizeof(kenoNumbers[0]), comp); // sorting numbers in order

    printf("%s, you selected the following numbers \n", playerName);
    displayKenoNumbers(kenoNumbers, KENO_NUMS); // display player number selection

    selectKenoNumbers(kenoSelect, playerName); // selects winning number
    qsort(kenoSelect, KENO_SELECT, sizeof(kenoSelect[0]), comp);

    displayKenoNumbers(kenoSelect, KENO_SELECT);
    winnings = kenoWinCheck(playerName, kenoNumbers, kenoSelect);

    bank += winnings;
    return bank;
}
void populateKenoCard(int kenoCard[ROWS][COLS]) // populates keno card array with numbers 1-80
{
    int currentNumber = 1;
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            kenoCard[row][col] = currentNumber;
            currentNumber++;
        }
    }
}

void displayKenoCard(int kenoCard[ROWS][COLS])
{
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            if (row == 0 && col == 9)
            {
                printf("| %d   | ", kenoCard[row][col]);
            }
            else if (row == 0)
            {
                printf("| %d    | ", kenoCard[row][col]);
            }
            else
            {
                printf("| %d   | ", kenoCard[row][col]);
            }
        }
        printf("\n");
    }
}

void displayKenoNumbers(int kenoNumbers[KENO_NUMS], int size)
{
    for (int i = 0; i < KENO_NUMS; i++)
    {
        printf("| %d |   ", kenoNumbers[i]);
    }
    printf("\n");
}

void getKenoNumbers(char playerName[30], int kenoNumbers[KENO_NUMS])
{
    int count = 0;
    int number = 0;
    for (int i = 0; i < KENO_NUMS; i++)
    {
        printf("%s, please enter in a number between 1 and 80, number %d\n", playerName, count + 1);
        while (TRUE) // infinite loop to validate user input
        {
            int playerInputCheck = scanf("%d", &number); // returns 1 if true and 0 if false
            if (playerInputCheck == TRUE && number > 0 && number <= KENO_MAX && contains(kenoNumbers, count, number) == FALSE)
            {
                kenoNumbers[i] = number;
                count++;
                break;
            }
            printf("%s, please choose a number greater than 0 and less than 81. Also make sure to select a number you have not previoulsy selected. \n", playerName);
        }
    }
}

int contains(int kenoNumbers[], int arrSize, int numberToFind)
{
    for (int i = 0; i < arrSize; i++)
    {
        if (kenoNumbers[i] == numberToFind)
        {
            return TRUE;
        }
    }
    return FALSE;
}

void selectKenoNumbers(int kenoSelect[KENO_SELECT], char playerName[30])
{
    int count = 0;
    int number = 0;

    printf("%s the %d winning numbers are being selected!\n", playerName, KENO_SELECT);
    for (int i = 0; i < KENO_SELECT; i++)
    {
        while (TRUE) // infinite loop for data validation
        {
            number = (rand() % KENO_MAX) + 1;
            if (contains(kenoSelect, count, number) == false)
            { // checks to make sure the winning number isnt chosen twice.
                kenoSelect[i] = number;
                count++;
                break;
            }
        }
    }
}

double kenoWinCheck(char playerName[30], int kenoNumbers[KENO_NUMS], int kenoSelected[KENO_SELECT])
{
    double winnings = 0.0;
    int matches = 0;
    const int PAYOUTS[11] =
        {
            0,
            4,
            10,
            30,
            100,
            500,
            2500,
            10000,
            50000,
            250000,
            1000000};

    for (int i = 0; i < KENO_SELECT; i++)
    {
        if (contains(kenoNumbers, KENO_NUMS, kenoSelected[i]))
        {
            matches++;
        }
    }

    printf("%s, you have %d matches!\n", playerName, matches);
    if (matches > 0)
    {
        winnings = (double)PAYOUTS[matches];
    }
    return winnings;
}

int comp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

// blackjack methods
double playBlackJack(char playerName[30], double bank)
{
    int playerchoice = -1;
    int playerScore = 0;
    int dealerScore = 0;
    int playerCards = 2;
    int dealerCards = 2;
    int dealt[DECK_SIZE];
    double winnings = 0.00;
    Card playerHand[MAX_HAND];
    Card dealerHand[MAX_HAND];
    Card deck[DECK_SIZE];

    memset(dealt, 0, sizeof(dealt));
    initializeDeck(deck);
    shuffleDeck(deck, DECK_SIZE);

    printf("BLACK JACK TABLE RULES \n\n");
    printf("ACE is always 11 points \n");
    printf("Dealer must HIT if their score is 16 or less \n");
    printf("Dealer must STAND if their score is 17 or higher \n");
    printf("If the player wins the hand, they win $100 \n");
    printf("If the dealer wins the hand the player loses their $50 bet \n");
    printf("If it is a PUSH the player keeps their $50 bet \n\n");
    printf("Hello %s, the bet to play blackjack is %lf\n", playerName, BLACKJACK_BET);

    if (bank < BLACKJACK_BET)
    {
        printf("Sorry %s, You lack the funds to play\n", playerName);
        return bank;
    }
    bank -= BLACKJACK_BET;

    playerHand[0] = dealCard(deck, dealt, playerName);
    playerHand[1] = dealCard(deck, dealt, playerName);
    dealerHand[0] = dealCard(deck, dealt, playerName);
    dealerHand[1] = dealCard(deck, dealt, playerName);

    // player logic

    playerScore = scoreHand(playerHand, playerCards);
    printf("%s your current score is %d. \n", playerName, playerScore);

    printf("%s, please press %d to stand or %d to hit \n", playerName, STAND, HIT);
    while (TRUE)
    {
        playerScore = scoreHand(playerHand, playerCards);
        printf("Hello %s your hand is, \n", playerName);
        displayHand(playerHand, playerCards);
        printf("Your current score is %d.\n", playerScore);

        if (playerScore >= BUST)
        {
            break; // Skip to outcome logic
        }

        printf("%s, please press %d to Stand or %d to Hit: \n", playerName, STAND, HIT);

        int playerInputCheck = scanf("%d", &playerchoice);

        if (playerInputCheck == 1 && (playerchoice == STAND || playerchoice == HIT))
        {
            if (playerchoice == STAND)
            {
                printf("%s stands with %d.\n", playerName, playerScore);
                break; // Exit loop to start dealer's turn
            }
            else // playerchoice == HIT
            {
                printf("%s hits.\n", playerName);
                playerHand[playerCards] = dealCard(deck, dealt, playerName);
                playerCards++;
            }
        }
        else
        {
            printf("Invalid input. Please press %d or %d.\n", STAND, HIT);
            while (getchar() != '\n')
                ; // Clear stdin buffer to prevent infinite loop
        }
    }
    if (playerScore >= BUST)
    {
        printf("%s BUSTS with %d! Dealer wins.\n", playerName, playerScore);
        return bank;
    }
    printf("\nDealer's turn.\nDealer's hand is: \n");
    displayHand(dealerHand, dealerCards);
    dealerScore = scoreHand(dealerHand, dealerCards);
    printf("Dealer's score is %d.\n", dealerScore);

    while (dealerScore < MIN_HIT)
    {
        printf("Dealer hits.\n");
        dealerHand[dealerCards] = dealCard(deck, dealt, playerName);
        dealerCards++;
        dealerScore = scoreHand(dealerHand, dealerCards);

        printf("Dealer's new hand: ");
        displayHand(dealerHand, dealerCards);
        printf("Dealer's new score: %d.\n", dealerScore);
    }
    winnings = blackJackWinCheck(playerName, playerScore, dealerScore);
    return bank += winnings;
}

void initializeDeck(Card deck[])
{
    int c = 0;
    for (int s = HEARTS; s < NUM_SUITS; s++)
    {
        for (int f = TWO; f < NUM_FACES; f++)
        {
            deck[c].suit = (Suit)s;
            deck[c].face = (Face)f;
            c++;
        }
    }
}

void shuffleDeck(Card deck[], int deckSize)
{
    for (int c = 0; c < deckSize; c++)
    {
        int r = rand() % (c + 1);
        Card card = deck[c];
        deck[c] = deck[r];
        deck[r] = card;
    }
}

const char convertFace(Face face)
{
    switch (face)
    {
    case TWO:
        return '2';
    case THREE:
        return '3';
    case FOUR:
        return '4';
    case FIVE:
        return '5';
    case SIX:
        return '6';
    case SEVEN:
        return '7';
    case EIGHT:
        return '8';
    case NINE:
        return '9';
    case TEN:
        return 'T';
    case JACK:
        return 'J';
    case QUEEN:
        return 'Q';
    case KING:
        return 'K';
    case ACE:
        return 'A';
    }
}

Card dealCard(Card deck[DECK_SIZE], int dealt[DECK_SIZE], char playerName[30])
{
    int used = FALSE;
    int cardNum = 0;
    Card card;
    static int cardsDealt = 0;
    while (used == FALSE)
    {
        cardNum = rand() % DECK_SIZE;
        if (dealt[cardNum] == FALSE)
        {
            used = TRUE;
            dealt[cardNum] = TRUE;
            card = deck[cardNum];
            cardsDealt++;
        }
    }
    if (cardsDealt == 52)
    {
        printf("%s all cards have been dealt, now shuffling.\n", playerName);
        cardsDealt = 0;
        memset(dealt, 0, DECK_SIZE);
    }
    return card;
}

void displayHand(Card hand[], int handSize)
{
    for (int i = 0; i < handSize; i++)
    {
        char face = convertFace(hand[i].face);
        switch (hand[i].suit)
        {
        case 0:
            printf(".----------.     \n");
            printf("|%c .----.  |     \n", face);
            printf("|  :    :  |     \n");
            printf("|   (\\/)   |     \n");
            printf("|  : \\/ :  |     \n");
            printf("|  :    :  |     \n");
            printf("|  '----'%c |     \n", face);
            printf("`----------'     \n");
            printf("   Hearts\n\n");
            break;
        case 1:
            printf(" .----------.\n");
            printf(" |%c .----.  |\n", face);
            printf(" |  :    :  |\n");
            printf(" |  : /\\ :  |\n");
            printf(" |  : \\/ :  |\n");
            printf(" |  :    :  |\n");
            printf(" |  '----' %c|\n", face);
            printf(" `----------'\n");
            printf("   Diamonds\n\n");
            break;
        case 2:
            printf(".----------.\n");
            printf("|%c .----.  |\n", face);
            printf("|  :    :  |\n");
            printf("|  : () :  |\n");
            printf("|  ()  ()  |\n");
            printf("|  :    :  |\n");
            printf("|  '----'%c |\n", face);
            printf("`----------'\n");
            printf("   Clubs\n\n");
            break;
        case 3:
            printf(".----------.    \n");
            printf("|%c .----.  |\n", face);
            printf("|  :    :  |\n");
            printf("|  : /\\ :  |\n");
            printf("|  ( /\\ )  |\n");
            printf("|  :    :  |\n");
            printf("|  '----' %c|\n", face);
            printf("`----------'\n");
            printf("   Spades \n\n");
            break;
        }
    }
}

int scoreHand(Card hand[], int handSize)
{
    int score = 0;
    for (int i = 0; i < handSize; i++)
    {
        switch (hand[i].face)
        {
        case TWO:
            score += 2;
            break;
        case THREE:
            score += 3;
            break;
        case FOUR:
            score += 4;
            break;
        case FIVE:
            score += 5;
            break;
        case SIX:
            score += 6;
            break;
        case SEVEN:
            score += 7;
            break;
        case EIGHT:
            score += 8;
            break;
        case NINE:
            score += 9;
            break;
        case TEN:
            score += 10;
            break;
        case JACK:
            score += 10;
            break;
        case QUEEN:
            score += 10;
            break;
        case KING:
            score += 10;
            break;
        case ACE:
            score += 11;
            break;
        default:
            break;
        }
    }
    return score;
}

double blackJackWinCheck(char playerName[30], int playerScore, int dealerScore)
{
    double WIN = 100.00;
    double PUSH = 50.00;
    double LOSE = 0.00;

    if (playerScore > BUST)
    {
        printf("SORRY %s, you LOST you BUSTED \n", playerName);
        return LOSE;
    }
    else if (dealerScore > BUST)
    {
        printf(" %s, you WON the dealer BUSTED \n", playerName);
        return WIN;
    }
    else if (playerScore == dealerScore)
    {
        printf(" %s, you tied the dealer PUSHHHHHH \n", playerName);
        return PUSH;
    }
    else if (playerScore > dealerScore)
    {
        printf(" %s, you WON\n", playerName);
        return WIN;
    }
    else if (playerScore < dealerScore)
    {
        printf(" %s, you LOST, dealer won\n", playerName);
        return LOSE;
    }
}
// poker functions

double playVideoPoker(char playerName[30], double bank)
{
    Card deck[DECK_SIZE];
    int dealt[DECK_SIZE];
    Card hand[CARDS];
    double winnings = 0.0;

    memset(dealt, 0, sizeof(dealt)); // sets every value of the arry in dealt with the size of dealt to 0
    printf("%s, the bet to play is $25.00\n", playerName);

    if (bank < 25.00)
    {
        printf("%s you do not have enough to play, you need $25.00 to continue\n", playerName);
        return bank;
    }

    bank -= POKER_BET;
    printf("%s, you bank is now %lf\n", playerName, bank);
    initializeDeck(deck);
    shuffleDeck(deck, DECK_SIZE);

    for (int i = 0; i < CARDS; i++)
    {
        hand[i] = dealCard(deck, dealt, playerName);
    }

    qsort(hand, CARDS, sizeof(hand[0]), compareCards);

    printf("%s hand has been sorted.\n", playerName);

    displayHand(hand, CARDS);
    winnings = videoPokerWinCheck(playerName, hand);
    bank += winnings;
    printf("%s, your winnings are %lf.\n", playerName, winnings);
    return bank;
}

double videoPokerWinCheck(char playerName[30], Card hand[CARDS])
{
    // test cases
// straight flush (hand is sorted by the time it gets here)
// hand[0].face = SEVEN;
// hand[0].suit = CLUBS;
// hand[1].face = EIGHT;
// hand[1].suit = CLUBS;
// hand[2].face = NINE;
// hand[2].suit = CLUBS;
// hand[3].face = TEN;
// hand[3].suit = CLUBS;
// hand[4].face = JACK;
// hand[4].suit = CLUBS;
// four of a kind
hand[0].face = NINE;
hand[0].suit = SPADES;
for(int c = 1; c < CARDS; c++)
{
hand[c].face = TEN;
hand[c].suit = HEARTS;
}
// full house
// hand[0].face = NINE;
// hand[0].suit = SPADES;
// hand[1].face = NINE;
// hand[1].suit = HEARTS;
// for(int c = 2; c < CARDS; c++)
// {
// hand[c].face = ACE;
// hand[c].suit = HEARTS;
// }
// flush
// for(int c = 0; c < CARDS; c++)
// {
// hand[c].face = TEN;
// hand[c].suit = HEARTS;
// }
// straight (hand is sorted by the time it gets here)
// hand[0].face = SEVEN;
// hand[0].suit = SPADES;
// hand[1].face = EIGHT;
// hand[1].suit = HEARTS;
// hand[2].face = NINE;
// hand[2].suit = SPADES;
// hand[3].face = TEN;
// hand[3].suit = DIAMONDS;
// hand[4].face = JACK;
// hand[4].suit = CLUBS;
// three of a kind
// hand[0].face = NINE;
// hand[0].suit = SPADES;
// hand[1].face = KING;
// hand[1].suit = SPADES;
// for(int c = 2; c < CARDS; c++)
// {
// hand[c].face = ACE;
// hand[c].suit = HEARTS;
// }
// two pair
// hand[0].face = NINE;
// hand[0].suit = SPADES;
// hand[1].face = NINE;
// hand[1].suit = HEARTS;
// hand[2].face = TEN;
// hand[2].suit = SPADES;
// hand[3].face = TEN;
// hand[3].suit = HEARTS;
// hand[4].face = ACE;
// hand[4].suit = HEARTS;
// one pair
// hand[0].face = NINE;
// hand[0].suit = SPADES;
// hand[1].face = NINE;
// hand[1].suit = HEARTS;
// hand[2].face = ACE;
// hand[2].suit = SPADES;
// hand[3].face = TEN;
// hand[3].suit = DIAMONDS;
// hand[4].face = KING;
// hand[4].suit = CLUBS;
    double winnings = 0.0;
    int payoutMultiplier[HANDTYPE_COUNT] =
        {
            [STRAIGHT_FL] = 50,
            [FOUR_KIND] = 25,
            [FULL_HOUSE] = 9,
            [FLUSH] = 6,
            [STRGHT] = 4,
            [THREE_KIND] = 3,
            [TWO_PAIRS] = 2,
            [ONE_PAIR] = 1};
    for (int i = 0; i < HANDTYPE_COUNT; i++)
    {
        switch (i)
        {
        case 0:
            if (isStraightFlush(hand) == TRUE)
            {
                printf("%s you have a straight flush!\n", playerName);
                winnings = 25.00 * payoutMultiplier[i];
                return winnings;
            }
            break;

        case 1:
            if (isFourKind(hand) == TRUE)
            {
                printf("%s you have a four of a kind!\n", playerName);
                winnings = 25.00 * payoutMultiplier[i];
                return winnings;
            }
            break;
        case 2:
            if (isFullHouse(hand) == TRUE)
            {
                printf("%s you have a full house!\n", playerName);
                winnings = 25.00 * payoutMultiplier[i];
                return winnings;
            }
            break;
        case 3:
            if (isFlush(hand) == TRUE)
            {
                printf("%s you have a flush!\n", playerName);
                winnings = 25.00 * payoutMultiplier[i];
                return winnings;
            }
            break;
        case 4:
            if (isStraight(hand) == TRUE)
            {
                printf("%s you have a straight!\n", playerName);
                winnings = 25.00 * payoutMultiplier[i];
                return winnings;
            }
            break;
        case 5:
            if (isThreeKind(hand) == TRUE)
            {
                printf("%s you have three of a kind!\n", playerName);
                winnings = 25.00 * payoutMultiplier[i];
                return winnings;
            }
            break;
        case 6:
            if (isTwoPair(hand) == TRUE)
            {
                printf("%s you have two pairs!\n", playerName);
                winnings = 25.00 * payoutMultiplier[i];
                return winnings;
            }
            break;
        case 7:
            if (isOnePair(hand) == TRUE)
            {
                printf("%s you have one pair!\n", playerName);
                winnings = 25.00 * payoutMultiplier[i];
                return winnings;
            }
            break;
        }
    }
}

// hand checks

int isStraightFlush(Card hand[CARDS])
{
    int win = FALSE;
    int count[FACES];

    memset(count, 0, sizeof(count));
    faceCount(count, hand);

    if (isFlush(hand) && isStraight(hand))
    {
        win = TRUE;
    }
    return win;
}

int isThreeKind(Card hand[CARDS])
{
    int win = FALSE;
    int count[FACES];

    memset(count, 0, sizeof(count));
    faceCount(count, hand);

    for (int i = 0; i < FACES; i++)
    {
        if (count[i] == 3)
        {
            win = TRUE;
        }
    }
    return win;
}

int isFullHouse(Card hand[CARDS])
{
    int win = FALSE;
    int count[FACES];

    memset(count, 0, sizeof(count));
    faceCount(count, hand);

    if (isThreeKind(hand) && isOnePair(hand))
    {
        win = TRUE;
    }

    return win;
}

int isFlush(Card hand[CARDS])
{
    int win = TRUE;

    for (int i = 0; i < CARDS; i++)
    {
        if (hand[i].suit != hand[0].suit)
        {
            win = FALSE;
        }
    }
    return win;
}

int isStraight(Card hand[CARDS])
{
    int win = TRUE;

    for (int i = 0; i < CARDS - 1; i++)
    {
        if (hand[i].face + 1 != hand[i + 1].face)
        {
            win = FALSE;
        }
    }
    return win;
}

int isTwoPair(Card hand[CARDS])
{
    int pairs = 0;
    int count[FACES];
    memset(count, 0, sizeof(count));
    faceCount(count, hand);

    for (int i = 0; i < FACES; i++)
    {
        if (count[i] == 2)
        {
            pairs++;
        }
    }

    return (pairs == 2) ? TRUE : FALSE;
}

int isOnePair(Card hand[CARDS])
{
    int win = FALSE;
    int pairs = 0;
    int count[FACES];

    memset(count, 0, sizeof(count));
    faceCount(count, hand);

    for (int i = 0; i < FACES; i++)
    {
        if (count[i] == 2)
        {
            pairs++;
        }
    }
    if (pairs == 1)
    {
        win = TRUE;
    }
    return win;
}
int isFourKind(Card hand[CARDS])
{
    int win = FALSE;
    int count[FACES];
    memset(count, 0, sizeof(count));
    faceCount(count, hand);
    for (int i = 0; i < FACES; i++)
    {
        if (count[i] == 4)
        {
            win = TRUE;
        }
    }
    return win;
}

void faceCount(int count[FACES], Card hand[CARDS])
{
    for (int i = 0; i < CARDS; i++)
    {
        Face currentFace = hand[i].face;
        int index = currentFace - 2;
        count[index]++;
    }
}

int compareCards(const void *c1, const void *c2)
{
    const Card *card1 = (const Card *)c1;
    const Card *card2 = (const Card *)c2;

    return card1->face - card2->face;
}