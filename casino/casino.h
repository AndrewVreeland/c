// Menu Macros
#define BLACKJACK 1
#define KENO 2
#define POKER 3
#define ROULETTE 4 // MUST be the last game type
#define QUIT 0

// macro to hold count of playable games for main menu
#define NUM_PLAYABLE_GAMES ROULETTE // always points at last item in list this holds last number

// MISC MACROS
#define TRUE 1
#define FALSE 0

// roulette macros
#define ROULETTE_SIZE 37
#define STRAIGHT 1
#define ODD_EVEN 2
#define LOW_HIGH 3                          // MUST be the last game type
#define NUM_OF_ROULETTE_GAME_TYPES LOW_HIGH // always points at last bet type

// keno macros
#define ROWS 8
#define COLS 10
#define KENO_NUMS 10
#define KENO_SELECT 20
#define KENO_MAX 80
#define KENO_BET 20.00

// blackjack Macros
#define DECK_SIZE 52
#define MAX_HAND 10
#define MIN_HIT 16
#define HIT 1
#define STAND 0
#define BUST 21
#define BLACKJACK_BET 50.00
#define BLACKJACK_WIN 100.00

// poker Macros
#define CARDS 5
#define POKER_BET 25.00
#define FACES 13
# define HANDTYPE_COUNT 8

// poker enums
typedef enum
{
    STRAIGHT_FL,
    FOUR_KIND,
    FULL_HOUSE,
    FLUSH,
    STRGHT,
    THREE_KIND,
    TWO_PAIRS,
    ONE_PAIR
}Poker;

// blackjack enums
typedef enum
{
    HEARTS,
    DIAMONDS,
    CLUBS,
    SPADES,
    NUM_SUITS
} Suit;

typedef enum
{
    TWO = 2,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE,
    NUM_FACES
} Face;

// blackjack structs
typedef struct
{
    Suit suit;
    Face face;
} Card;

// menu constants
char BLACKJACK_STR[] = "Black Jack";
char KENO_STR[] = "Keno";
char POKER_STR[] = "Video Poker";
char ROULETTE_STR[] = "Roulette";
char QUIT_STR[] = "Quit";

// roulette constants
char STRAIGHT_STR[] = "Straight Up: Bet on a single number (35:1)";
char ODD_EVEN_STR[] = "Odd or Even: Bet on odd or even numbers (1:1)";
char LOW_HIGH_STR[] = "Low or High: Bet on 0-18 or 19-36 (1-1)";

// function prototypes
void logo();
void sampleCards();
void printStatements();
void play();
int gameMenu();

// roulette function prototypes
double playRoulette();
void printRoulette();
int straight();
int oddEven();
int lowHigh();
int rouletteSpin();
double rouletteWinCheck();
bool chipPlacementComparison();

// keno function prototypes
double playKeno();
void populateKenoCard();
void displayKenoCard();
void getKenoCard();
void getKenoNumbers();
int contains();
void displayKenoNumbers();
void selectKenoNumbers();
double kenoWinCheck();
int comp();

// blackjack function prototypes
double playBlackJack();
void initializeDeck();
void shuffleDeck();
const char convertface();
void displayHand();
Card dealCard();
int scoreHand();
double blackJackWinCheck();

// poker function prototypes
double playVideoPoker();
double videoPokerWinCheck();
int isStraightFlush();
int isFourKind();
int isThreeKind();
int isFullHouse();
int isFlush();
int isStraight();
int isTwoPair();
int isOnePair();
int compareCards();
void faceCount();
