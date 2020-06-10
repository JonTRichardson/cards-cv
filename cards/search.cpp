// search.cpp.  
//  Seeks to match a set of patterns against an image to identify suit, rank of a playing card.
//         Version 2 will make a judgement from the list of patterns about the suit and face cards.
//         Version 3 : final functional version.
//         Version 3.5 : Cleanup.
//         (bypass version 4)
//         Version 5 : Add the n non-face patterns.
//////////////////////////////////////
 
#define JR_SEARCH_CPP_VERSION   "ver 5"

// TODO : Reenable these warnings and fix the code.
#pragma GCC diagnostic ignored "-Wwrite-strings"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using std::cout;
using std::endl;
using namespace cv;

/////////////////////////////////////////////////////////////
/// Global Variables
Mat img; Mat templ;   // legacy of original matchdemo.cpp

const int match_method =CV_TM_SQDIFF; 

/////////////////////////////////////////////////////////////
//
//  patterns
//    The following definitions are used to represent
//    and detect cards.
//

enum Suit
{
    UNKNOWN_SUIT,
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
};

void print_suit(Suit suit)
{
    switch (suit)
    {
        case CLUBS:      cout << "Clubs ";      break;
        case DIAMONDS:   cout << "Diamonds ";   break;
        case HEARTS:     cout << "Hearts ";     break;
        case SPADES:     cout << "Spades ";     break;
        default:         cout << "Unknown suit. ";
    }
}

enum Rank
{
    UNKNOWN_RANK=0,
    NONFACE,
    TWO,
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
    ACE
};

void print_rank(Rank rank)
{
    switch (rank)
    {
        case NONFACE:    cout << "Nonface ";    break;
        case TWO:        cout << "Two ";        break;
        case THREE:      cout << "Three ";      break;
        case FOUR:       cout << "Four ";       break;
        case FIVE:       cout << "Five ";       break;
        case SIX:        cout << "Six ";        break;
        case SEVEN:      cout << "Seven ";      break;
        case EIGHT:      cout << "Eight ";      break;
        case NINE:       cout << "Nine ";       break;
        case TEN:        cout << "Ten ";        break;
        case ACE:        cout << "Ace ";        break;
        case JACK:       cout << "Jack ";       break;
        case QUEEN:      cout << "Queen ";      break;
        case KING:       cout << "King ";       break;
        default:         cout << "Unknown rank. ";
    }
}

/////////////////////////////////////////////////////////
// CardInfo
// This is shared by both a candidate image and patterns.
struct CardInfo
{
    char * filename;
    Rank rank;
    double rank_ratio;
    Suit suit;
    double suit_ratio;
    void print_me() { cout << "CardInfo: "; print_rank(rank); cout << "of "; print_suit(suit); cout << endl; };
};

/////////////////////////////////////////////////////////
//  array of patterns to match against images:
CardInfo patterns[] =
{
    // these will find suit of all cards in the set:
    { "templates/patt-club-fr4-nicu.png",  UNKNOWN_RANK, 0.0, CLUBS,        0.0, },  
    { "templates/patt-diamond-nicub.png",  UNKNOWN_RANK, 0.0, DIAMONDS,     0.0, }, 
    { "templates/patt-heart-alt-nicu.png", UNKNOWN_RANK, 0.0, HEARTS,       0.0, },
    { "templates/patt-spade-nicu.png",     UNKNOWN_RANK, 0.0, SPADES,       0.0, },

    // these 6 will find rank of the 12 face cards:
    { "templates/patt-jb-nicu.png",        JACK,         0.0, UNKNOWN_SUIT, 0.0, },
    { "templates/patt-jr-alt-nicu.png",    JACK,         0.0, UNKNOWN_SUIT, 0.0, }, 
    { "templates/patt-qb-nicu.png",        QUEEN,        0.0, UNKNOWN_SUIT, 0.0, },
    { "templates/patt-qr-nicu.png",        QUEEN,        0.0, UNKNOWN_SUIT, 0.0, },
    { "templates/patt-kb-nicu.png",        KING,         0.0, UNKNOWN_SUIT, 0.0, },
    { "templates/patt-kr-nicu.png",        KING,         0.0, UNKNOWN_SUIT, 0.0, },

    // these 7 will find rank of 14 of the nonface cards:
    { "templates/patt-ab-nicu.png",        ACE,          0.0, UNKNOWN_SUIT, 0.0, },
    { "templates/patt-2r-nicu.png",        TWO,          0.0, UNKNOWN_SUIT, 0.0, },
    { "templates/patt-4b-nicu.png",        FOUR,         0.0, UNKNOWN_SUIT, 0.0, },
    { "templates/patt-4r-nicu.png",        FOUR,         0.0, UNKNOWN_SUIT, 0.0, },
    { "templates/patt-6b-nicu.png",        SIX,          0.0, UNKNOWN_SUIT, 0.0, },
    { "templates/patt-9b-nicu.png",        NINE,         0.0, UNKNOWN_SUIT, 0.0, },
    { "templates/patt-10b-nicu.png",       TEN,          0.0, UNKNOWN_SUIT, 0.0, }
};

////////////////////////////////////////////////////////
// Function Headers
void MatchingMethod( const CardInfo& pattern, CardInfo&, int, void* );


///////////////////////////////////////////////
//
//  main()
//    Argument: filename of card candidate. 
//
int main( int argc, char** argv )
{
    
    if (argc<2)
    {
	    cout << "Incorrect args. argc="<<argc<<endl;
	    exit(1);
    }

    // Image of card candidate:
    img = imread( argv[1], 1 );

    CardInfo card = { "", NONFACE, 1.0, UNKNOWN_SUIT, 1.0};

    int num_patterns = sizeof(patterns) / sizeof(patterns[0]);
  
    for (int ii=0; ii<num_patterns; ii++)
    {
        // Template:
        templ = imread( patterns[ii].filename, 1 );

        MatchingMethod( patterns[ii], card, 0, 0 );
    }

    card.print_me();
    if (card.rank == NONFACE && card.suit == UNKNOWN_SUIT)
    {
        cout << "Card not detected\n";
    }

    return 0;
}   // main()


///////////////////////////////////////////////////////////////////////////
/**
 * @function MatchingMethod
 * @brief 
 *     Args:
 *      
 */
void MatchingMethod( const CardInfo& pattern, CardInfo& card, int, void* )
{
    Mat result;

    /// Source image to display
    Mat img_display;
    img.copyTo( img_display );

    /// Create the result matrix
    int result_cols = img.cols - templ.cols + 1;
    int result_rows = img.rows - templ.rows + 1;

    result.create( result_rows, result_cols, CV_32FC1 );

    /// Do the Matching and Normalize

    matchTemplate( img, templ, result, match_method );
    //normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );

    /// Localizing the best match with minMaxLoc
    double minVal; double maxVal; Point minLoc; Point maxLoc;
    Point matchLoc;

    minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
    double ratio = minVal / maxVal;

    /////////////////////////////////////////////////////
    // Logic for judging the card based on the match quality and the pattern info

    // Arbitrary threshold to prevent false positives:
    if (ratio < 0.10)
    {
        //cout << pattern.filename << " " << ratio << endl;

        // if pattern is for suit, then see if its a better match than we've seen for suit.
        if (pattern.suit > UNKNOWN_SUIT) 
        {
            if ( ratio < card.suit_ratio)
            {
                card.suit = pattern.suit;
                card.suit_ratio = ratio;
                //print_suit(card.suit);
            }
        }
    
        // if pattern is for rank, then see if its a better match than we've seen for rank.
        if (pattern.rank > NONFACE)
        {
            if ( ratio < card.rank_ratio)
            {
                card.rank = pattern.rank;
                card.rank_ratio = ratio;
                // print_rank(card.rank);
            }
        }
    }

    return;
}   // MatchingMethod()

