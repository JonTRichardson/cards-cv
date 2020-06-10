// search.cpp.  
//     Derived from jmatch, which matched a single pattern against an image.
//         This program will do a comparison versus a list of patterns.
//         Version 2 will make a judgement from the list of patterns about the suit and face cards.
//////////////////////////////////////

#define JR_SEARCH_CPP_VERSION   "ver 2"

// TODO : Reenable these warnings and fix the code.
#pragma GCC diagnostic ignored "-Wwrite-strings"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

#include "jutils.hpp"

using std::cout;
using std::endl;
using namespace cv;

////////////////////////////////////////
/// Global Variables (legacy)
Mat img; Mat templ;

const int match_method =CV_TM_SQDIFF; 

////////////////////////////////////////////////
//
//  patterns
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
        case JACK:       cout << "Jack ";       break;
        case QUEEN:      cout << "Queen ";      break;
        case KING:       cout << "King ";       break;
        default:         cout << "Unknown rank. ";
    }
}


struct CardInfo
{
    char * filename;
    Rank rank;
    double rank_ratio;
    Suit suit;
    double suit_ratio;
    void print_me() { cout << "CardInfo: "; print_rank(rank); cout << "of "; print_suit(suit); cout << endl; };
};

CardInfo patterns[] =
{
    { "templates/patt-club-fr4-nicu.png",  UNKNOWN_RANK, 0.0, CLUBS,        0.0, },  
    { "templates/patt-diamond-nicub.png",  UNKNOWN_RANK, 0.0, DIAMONDS,     0.0, }, 
    { "templates/patt-heart-fr4-nicu.png", UNKNOWN_RANK, 0.0, HEARTS,       0.0, },
    { "templates/patt-spade-nicu.png",     UNKNOWN_RANK, 0.0, SPADES,       0.0, },
    { "templates/patt-jb-nicu.png",        JACK,         0.0, UNKNOWN_SUIT, 0.0, },
    { "templates/patt-jr-nicu.png",        JACK,         0.0, UNKNOWN_SUIT, 0.0, }, 
    { "templates/patt-qb-nicu.png",        QUEEN,        0.0, UNKNOWN_SUIT, 0.0, }
};


/// Function Headers
void MatchingMethod( const CardInfo& pattern, CardInfo&, int, void* );

///////////////////////////////////////////////
//
//  main()
//
int main( int argc, char** argv )
{
    cout << JR_SEARCH_CPP_VERSION << endl;
    
    if (argc!=2)
    {
	    cout << "Incorrect args. argc="<<argc<<endl;
	    exit(1);
    }

    // Image:
    cout << "Image file (argv[1]) : " << argv[1] << endl; 
    img = imread( argv[1], 1 );

    CardInfo card = { "", NONFACE, 1.0, UNKNOWN_SUIT, 1.0};
    //card.print_me();

    int num_patterns = sizeof(patterns) / sizeof(patterns[0]);
    cout << "num_paterns=" << num_patterns << endl;
  
    for (int ii=0; ii<num_patterns; ii++)
    {
        // Template:
        cout << "file: " << patterns[ii].filename << endl; 
        templ = imread( patterns[ii].filename, 1 );

        MatchingMethod( patterns[ii], card, 0, 0 );
    }

    card.print_me();

    return 0;
} // main()


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
    int result_cols =  img.cols - templ.cols + 1;
    int result_rows = img.rows - templ.rows + 1;

    result.create( result_rows, result_cols, CV_32FC1 );

    /// Do the Matching and Normalize

    matchTemplate( img, templ, result, match_method );
    //normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );

    /// Localizing the best match with minMaxLoc
    double minVal; double maxVal; Point minLoc; Point maxLoc;
    Point matchLoc;

    minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
    //cout << "minVal=" << minVal << endl;
    //cout << "maxVal=" << maxVal << endl;
    double ratio = minVal / maxVal;
    cout << "ratio=" << ratio << endl;

    /////////////////////////////////////////////////////
    // Logic for judging the card based on the match quality and the pattern info

    // Arbitrary thresholds:
    card.suit_ratio = 0.12;
    card.rank_ratio = 0.12;

    // if pattern is for suit, then see if its a better match than we've seen for suit.
    if (pattern.suit > UNKNOWN_SUIT) 
    {
        if (ratio < card.suit_ratio)
        {
            card.suit = pattern.suit;
            card.suit_ratio = ratio;
            print_suit(card.suit);
            cout << card.suit_ratio << endl;
        }
    }

    // if pattern is for rank, then see if its a better match than we've seen for rank.
    if (pattern.rank > NONFACE)
    {
        if (ratio < card.rank_ratio)
        {
            card.rank = pattern.rank;
            card.rank_ratio = ratio;
            print_rank(card.rank);
            cout << card.rank_ratio << endl;
        }
    }

    return;
} // MatchingMethod()

