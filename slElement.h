//
//  slac
//
//  Vladislav Borisov
//  Copyright © 2020 na. All rights reserved.
//


#ifndef slElement_h
#define slElement_h

// <----- Sentential Logic Element Class ----->
class slElement
{
    private:
        char charVal;
        bool truthVal;

    public:
        slElement (char c, bool t)
        {
            charVal=c;
            truthVal=t;
        }
    
        slElement (char c)
        {   charVal = c;}
    
        char getChar()
        {   return charVal;}
    
        bool getTruthVal()
        {   return truthVal;}
    
        void setTruth(bool t)
        {   truthVal = t;}
};

#endif /* slElement_h */
