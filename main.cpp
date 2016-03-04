//
//  SLAC: A Sentential Logic Algebra Calculator
//  Created by Vladislav Borisov on 2/29/16.
//  Copyright © 2016 na. All rights reserved.
//
//
//
//
//       _____ _               _____
//      / ____| |        /\   / ____|
//     | (___ | |       /  \ | |
//      \___ \| |      / /\ \| |
//      ____) | |____ / ____ \ |____
//     |_____/|______/_/    \_\_____|
//
// = ========== ===== ======= ==========
// A Sentential Logic Algebra Calculator
// = ========== ===== ======= ==========
//
//           Vladislav Borisov
//
//


#include <iostream>
#include <iomanip>
#include <stack>
#include <queue>
#include <string>
#include <sstream>
#include <stdlib.h>
using namespace std;


// OPERATORS
/*
 
// EXTERNAL OPERATORS
// +++++++++
// CONJUNCTION      &
// DISJUNCTION      v
// NEGATION         ~
// CONDITIONAL      ->
// BICONDITIONAL    <->

// INTERNAL OPERATORS
// +++++++++
// CONJUNCTION      &
// DISJUNCTION      v
// NEGATION         ~
// CONDITIONAL      >
// BICONDITIONAL    =
 
*/

// Intro & Info
void introtext ()
{
    cout << "       _____ _               _____      " << endl;
    cout << "      / ____| |        /\\   / ____|     " << endl;
    cout << "     | (___ | |       /  \\ | |          " << endl;
    cout << "      \\___ \\| |      / /\\ \\| |          " << endl;
    cout << "      ____) | |____ / ____ \\ |____      " << endl;
    cout << "     |_____/|______/_/    \\_\\_____|     " << endl << endl;
    cout << " = ========== ===== ======= ==========  " << endl;
    cout << " A Sentential Logic Algebra Calculator  " << endl;
    cout << " = ========== ===== ======= ==========  " << endl << endl;
    cout << "           Vladislav Borisov            " << endl << endl << endl;
    
    cout << "Slac evaluates the truth-value for any given proposition!" << endl;
    cout << "Slac uses the system of symbolic logic known as Sentential or Propositional Logic." << endl << endl;
    
    cout << "Please use left  \"(\"  and right  \")\"  parentheses when necessary." << endl;
    cout << "Please note that Slac uses the following standard logical operator symbols: " << endl;
    cout << "CONJUNCTION      &" << endl;
    cout << "DISJUNCTION      v" << endl;
    cout << "NEGATION         ~" << endl;
    cout << "CONDITIONAL      >  OR  ->"  << endl;
    cout << "BICONDITIONAL    =  OR  <->" << endl << endl << endl;
}

// Controls user interaction for primary loop in main
bool cont ()
{
    string contresp;
    cout << "Would you like to evaluate another proposition?  ( Y / N )" << endl;
    
    cin >> contresp;
    cout << endl << endl;
    
    if (contresp == "Y" || contresp == "y" || contresp == "YES" || contresp == "yes" || contresp == "Yes")
        return true;
    else if (contresp == "N" || contresp == "n" || contresp == "NO" || contresp == "no" || contresp == "No")
        cout << "Thank you for using Slac!" << endl << "Exiting with normal conditions now." << endl;
        return false;
    return false;
}

// Logical Symbol Class
//    char for symbol or placeholder
//    bool for assigned or evaluated truth-value
class slElem
{
    private:
        char cval;
        bool tval;
    public:
        slElem(char c, bool t)
        {
            cval = c;
            tval = t;
        }
        slElem (char c)
        {
            cval = c;
        }
        char gets()
        {
            return cval;
        }
        bool gett()
        {
            return tval;
        }
        void sett(bool t)
        {
            tval = t;
        }
};

// ACCEPTS char token
// RETURNS true if operator, false if not
bool isoperator (char tok)
{
    if ((tok == '&') || (tok == 'v') || (tok == '~') || (tok == '>') || (tok == '='))
        return true;
    else
        return false;
}

// ACCEPTS left element, right element, operator element
// RETURNS operator element w/ truth value of local expression
slElem evaltv (slElem left, slElem right, slElem  oper)
{
    slElem result('$');
    
    if (oper.gets() == '&')
    {
        if ( (left.gett() == true) && (right.gett() == true) )
        {
            result.sett(true);
            return result;
        }
        result.sett(false);
        return result;
    }
    
    if (oper.gets() == 'v')
    {
        if ( (left.gett() == true) ||  (right.gett() == true) )
        {
            result.sett(true);
            return result;
        }
        result.sett(false);
        return result;
    }
    
    if (oper.gets() == '>')
    {
        if ( (left.gett() == true) && (right.gett() == false) )
        {
            result.sett(false);
            return result;
        }
        result.sett(true);
        return result;
    }
    
    if (oper.gets() == '=')
    {
        if ( ( (left.gett() == true) && (right.gett() == true) ) || ( (left.gett() == false) && (right.gett() == false) ) )
        {
            result.sett(true);
            return result;
        }
        result.sett(false);
        return result;
    }

    return result;
}

// ACCEPTS input infix string
// RETURNS cleaned infix string
string cleaner (string expr)
{
    while (true)
    {
        size_t found = expr.find("<->");
        if (found!=string::npos)
        {
            expr.erase(found, 3);
            expr.insert(found, "=");
        }
        else
            break;
    }
    while (true)
    {
        size_t found = expr.find("->");
        if (found!=string::npos)
        {
            expr.erase(found, 2);
            expr.insert(found, ">");
        }
        else
            break;
    }
    return expr;
}

// ACCEPTS cleaned infix string
// RETURNS cleaned postfix string
string postfixer (string expr)
{
    char token;
    stack<char> mys;
    queue<char> myq;
    stringstream in = stringstream(expr);
    in >> token;
    while (in)
    {
        if ( (!(isoperator(token))) && (token != '(') && (token != ')') )
        {
            myq.push(token);
        }
        else if ( isoperator(token) )
        {
            while ( (!mys.empty()) && (isoperator(mys.top())) )
            {
                myq.push( mys.top() );
                mys.pop();
            }
            mys.push(token);
        }
        else if (token == '(')
        {
            mys.push(token);
        }
        else if (token == ')')
        {
            while ( (!mys.empty()) && (mys.top() != '(' ) )
            {
                myq.push( mys.top() );
                mys.pop();
            }
            mys.pop();
        }
        in >> token;
    }
    while (!mys.empty())
    {
        myq.push( mys.top() );
        mys.pop();
    }
    string newS;
    while(!myq.empty())
    {
        newS = newS + (myq.front());
        myq.pop();
    }
    return newS;
}

// ACCEPTS cleaned postfix string
// RETURNS cleaned postfix element vector
vector<slElem> elementer (string expr)
{
    vector<slElem> elemented;
    
    for (int i=0; i<expr.size(); i++)
    {
        elemented.push_back(slElem (expr[i]) );
    }
    return elemented;
}

// ACCEPTS input infix string
// RETURNS cleaned postfix element vector
vector<slElem> preparer (string expr)
{
    expr = cleaner(expr);
    expr = postfixer(expr);
    vector<slElem> ready (elementer(expr));
    return ready;
}

// ACCEPTS cleaned postfix element vector
// RETURNS cleaned postfix element vector w/ truth-value assignments
vector<slElem> assigner (vector<slElem> myElems)
{
    bool go = true;
    string gos;
    while (go)
    {
        char current;
        char tvac;
        bool tvab;
        cout << "Please enter an atomic component of your proposition:  ";
        cin >> current; //cout << endl;
        cout << "Enter the truth-value assignment for sentence \" " << current << " \" :  ";
        cin >> tvac; //cout << endl << endl;
        
        if (tvac == 'T' || tvac == 't' || tvac == '1')
            tvab = true;
        else
            tvab = false;
        
        for (int i=0; i<myElems.size(); i++)
        {
            if ( (myElems[i].gets()) == current)
                myElems[i].sett(tvab);
        }
        
        cout << "Do you have another truth-value to set?  ( Y / N ):  ";
        cin >> gos;
        
        if (gos == "Y" || gos == "y" || gos == "YES" || gos == "yes" || gos == "Yes")
            go = true;
        else if (gos == "N" || gos == "n" || gos == "NO" || gos == "no" || gos == "No")
            go = false;
    }
    return myElems;
}

// ACCEPTS cleaned postfix elemen vector w/ truth-value assignments
// RETURNS boolean truth-value of expression
bool evalbase (vector<slElem> myElems)
{
    stack<slElem> mys;
    for (int i = 0; i<myElems.size(); i++)
    {
        if(!(isoperator(myElems[i].gets())))
            mys.push(myElems[i]);
        if (isoperator(myElems[i].gets()))
        {
            if ( myElems[i].gets() == '~' )
            {
                mys.top().sett( !( mys.top().gett() ) );
            }
            else
            {
                slElem right( (mys.top().gets()), (mys.top().gett()) );
                mys.pop();
                slElem left ( (mys.top().gets()), (mys.top().gett()) );
                mys.pop();
                
                slElem oper( (myElems[i].gets()), (myElems[i].gett()) );
                
                mys.push( evaltv(left, right, oper) );
            }
        }
    }
    return mys.top().gett();
    
}

// Provides intro, gets input string expr, prepares for eval, and calls all necessary functions
// Controls play loop w/ call to cont
int main(int argc, const char * argv[])
{
    introtext();
    
    bool play = true;
    string myexpr;
    
    while (play)
    {
        bool result;
        cout << "------ ----- ---- ------------" << endl;
        cout << "------ ----- ---- ------------" << endl;
        cout << "Please enter your proposition:" << endl;
        cin >> myexpr;
        
        vector<slElem> ready (preparer(myexpr));
        
        ready = assigner(ready);
        
        result = evalbase(ready);
        
        cout << endl << endl << "                     ";
        for(int i=0; i<myexpr.size(); i++)
            cout << "-";
        cout << endl << "Your expression      " << myexpr << endl;
        cout << "has a truth value of ";
        
        if (result)
        {
            cout << "TRUE" << endl;
            cout << "                     ----" << endl;
        }
        else
        {
            cout << "FALSE" << endl;
            cout << "                     -----" << endl;
        }
        
        cout << endl << endl;
        
        play = cont();
    }
    
    
    cout << endl;
    return 0;
}
