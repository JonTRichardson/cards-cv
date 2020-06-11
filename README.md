# cards-cv
A prototype / demo of card image recognition using OpenCV

This reads card images and identifies the card, i.e. rank and suit.

This was a hasty project I did as part of a job application for a position which involved image recognition.


KNOWN PROBLEMS

 - There is a card that is not correctly identified (possibly more than one).
 - The card identification is very fragile : it looks for an exact match for
   a portion of the card.  It does abstract suit and rank however.
 - I've only built and run this on this one configuration of raspberryPi so
   it wouldn't surprise me if results are wildly different elsewhere.
   g++ -V reports "gcc version 4.9.2 (Raspbian 4.9.2-10)" 
 - This repository has a hacked build approach to the openCV library and
   includes the built objects from the openCV distribution.  It was taking too
   much time to get CMake to work, so to save time, I created my own Makefile.
 - There are compiler warnings.
 - There may be license issues, e.g. a conflict between this project and
   the openCV distribution. (I'm using MIT.  They are using 3-BSD.)

