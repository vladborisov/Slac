//
//  slac
//
//  Vladislav Borisov
//  Copyright © 2020 na. All rights reserved.
//


// <----- INCLUDES ----->
#include "slElement.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <stack>
#include <queue>
#include <sstream>
#include <stdlib.h>
using namespace std;


// <----- FUNCTION DECLARATIONS ----->
void introText();
string cleaner(string);
string postfixer(string);
bool isOperator (char);
vector<slElement> slElementer (string);
vector<slElement> assigner (vector <slElement>);
bool evalBase (vector<slElement>);
slElement eval (slElement, slElement, slElement);
bool cont ();


// <----- DRIVER ----->
int main(int argc, const char * argv[])
{
    introText();
    
    bool play = true;
    string myExpr;
    
    while (play)
    {
        bool result;
        cout << "Please enter your proposition:" << endl;
        cout << "------ ----- ---- ------------" << endl << endl;

        
        cin >> myExpr;                                              // Original Expression
        cout << endl;
        string originalExpr = myExpr;
        
        myExpr = cleaner(myExpr);                                   // Cleaned for Uniform/Single-Character Parsing
        
        myExpr = postfixer(myExpr);                                 // Postfixed
        
        
        vector<slElement> myExprElemented = slElementer(myExpr);    // Parsed to slElements Vector
        
        myExprElemented = assigner (myExprElemented);               // with Truth Values
        
        result = evalBase(myExprElemented);
        
        cout << endl << endl << "                         ";
        for(int i  =0; i < originalExpr.size(); i++)
            cout << "-";
        cout << endl << "Your expression          " << originalExpr << endl;
        cout << "has a truth value of     ";
        
        if (result)
        {
            cout << "TRUE" << endl;
            cout << "                         ----" << endl;
        }
        else
        {
            cout << "FALSE" << endl;
            cout << "                         -----" << endl;
        }
        
        cout << endl << endl;
        
        play = cont();
    }
    
    return 0;
}


// <----- Introductory Text ----->
// <----- ACCEPTS: n/a ----->
// <----- RETURNS: n/a ----->
void introText()
{
    cout << "            _____ _               _____      " << endl;
    cout << "           / ____| |        /\\   / ____|     " << endl;
    cout << "          | (___ | |       /  \\ | |          " << endl;
    cout << "           \\___ \\| |      / /\\ \\| |          " << endl;
    cout << "           ____) | |____ / ____ \\ |____      " << endl;
    cout << "          |_____/|______/_/    \\_\\_____|     " << endl << endl;
    cout << "      = ========== ===== ======= ==========  " << endl;
    cout << "      A Sentential Logic Algebra Calculator  " << endl;
    cout << "      = ========== ===== ======= ==========  " << endl << endl;
    cout << "                Vladislav Borisov            " << endl << endl << endl << endl;
    
    
    
    cout << "Slac evaluates the truth-value for any given proposition!" << endl << endl;
    
    cout << "Slac uses the system of symbolic logic known as Sentential or Propositional Logic." << endl << endl << endl << endl;
    
    

    cout << "Please use parentheses  (  )  or brackets  [  ]  when necessary," << endl;
    cout << " including to group usage of the unary negation symbol ~ ." << endl << endl;
    cout << "   IE              A v ~B        |           A v ~(B&C)" << endl;
    cout << "              as   A v (~B)      |      as   A v (~(B&C))" << endl << endl << endl << endl;
    
    
    
    cout << "Please note that Slac uses the following standard logical operator symbols: " << endl << endl;
    
    cout << "CONJUNCTION      &" << endl;
    cout << "DISJUNCTION      v" << endl;
    cout << "NEGATION         ~" << endl;
    cout << "CONDITIONAL      >  OR  ->"  << endl;
    cout << "BICONDITIONAL    =  OR  <->" << endl << endl << endl << endl;
}


// <----- Cleans Expression to Ensure Single-Character Operators & Parenthetical Grouping ----->
// <----- ACCEPTS: original infix string ----->
// <----- RETURNS: cleaned infix string ----->
string cleaner(string expr)
{
    while (true)                                // cleans <-> into =
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
    
    while (true)                                // cleans -> into >
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
    
    while (true)                                // cleans [ into (
    {
        size_t found = expr.find("[");
        if (found!=string::npos)
        {
            expr.erase(found, 1);
            expr.insert(found, "(");
        }
        else
            break;
    }
    
    while (true)                                // cleans ] into )
    {
        size_t found = expr.find("]");
        if (found!=string::npos)
        {
            expr.erase(found, 1);
            expr.insert(found, ")");
        }
        else
            break;
    }
    
    return expr;
}


// <----- Converts Expression to Postfix (Reverse-Polish) Notation ----->
// <----- ACCEPTS: cleaned infix string ----->
// <----- RETURNS: cleaned postfix string ----->
string postfixer (string expr)
{
    char curToken;
    char peekToken;
    stack <char> operatorStack;
    queue <char> myQueue;
    stringstream in = stringstream(expr);
    string outExpr;

    while (in)
    {
        in >> curToken;
        if (!in.good())     // necessary to ensure no double-counting at eof character
            break;
        else if (  ( !isOperator(curToken) ) && (( curToken!='(' ) && ( curToken!=')' ))  )      // if token is operand
            outExpr += curToken;
        else if ( curToken == '(' )                                                         // if token is (
            operatorStack.push(curToken);
        else if ( curToken == ')' )                                                         // if token is )
        {
            peekToken = operatorStack.top();
            operatorStack.pop();
            while ( peekToken != '(' && !operatorStack.empty() )
            {
                outExpr += peekToken;
                peekToken = operatorStack.top();
                operatorStack.pop();
            }
            if (peekToken != '(' )
                outExpr += peekToken;
        }
        else if ( isOperator(curToken) )                                                    // if token is operator
        {
            while ( !operatorStack.empty() && operatorStack.top()!= '(' )
            {
                outExpr += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(curToken);
        }
    }
    while ( !operatorStack.empty() )
    {
        peekToken = operatorStack.top();
        operatorStack.pop();
        outExpr += peekToken;
    }
    
    return outExpr;
}


// <----- Checks if Token is an Operator ----->
// <----- ACCEPTS: character token ----->
// <----- RETURNS: boolean ----->
bool isOperator (char c)
{
    if ((c == '&') || (c == 'v') || (c == '~') || (c == '>') || (c == '='))
        return true;
    else
        return false;
}


// <----- Converts Expression from String to Vector of slElement Objects ----->
// <----- ACCEPTS: cleaned postfix string ----->
// <----- RETURNS: cleaned postfix slElement vector ----->
vector<slElement> slElementer (string expr)
{
    vector<slElement> elemented;
    
    for (int i = 0; i < expr.size(); i++)
        elemented.push_back( slElement (expr[i]) );
    
    return elemented;
}


// <----- Assigns Truth-Values to Atomic Components of Expression ----->
// <----- ACCEPTS: cleaned postfix slElement vector ----->
// <----- RETURNS: cleaned postfix slElement vector w/truth value assignments ----->
vector<slElement> assigner (vector <slElement> elems)
{
    string componentsInExpr;
    
    for (int i = 0; i <= elems.size(); i++)
        if ( !isOperator(elems[i].getChar()) )
            componentsInExpr += elems[i].getChar();
    
    sort( begin(componentsInExpr),end(componentsInExpr) );
    auto last = unique( begin(componentsInExpr), end(componentsInExpr) );
    componentsInExpr.erase( last, end(componentsInExpr) );
    
    int numUniqueComp = int(componentsInExpr.length() - 1);
    
    char uniqueComponents [numUniqueComp];
    
    strcpy(uniqueComponents, componentsInExpr.substr(1, componentsInExpr.length()).c_str());
    
    string truthValResponse;
    bool truthValBool;
    for (int i = 0; i < numUniqueComp; i++)
    {
        cout << "Please enter the truth-value assignment for atomic component " << uniqueComponents[i] << " :  ";
        cin >> truthValResponse;
        
        if (truthValResponse == "T" || truthValResponse == "t" || truthValResponse == "1" || truthValResponse == "TRUE" || truthValResponse == "True" || truthValResponse == "true" || truthValResponse == "YES" || truthValResponse == "Yes" || truthValResponse == "yes" || truthValResponse == "Y" || truthValResponse == "y")
            truthValBool = true;
        else
            truthValBool = false;
        
        for (int j = 0; j < elems.size(); j++)
            if ( (elems[j].getChar()) == uniqueComponents[i])
                elems[j].setTruth(truthValBool);
    }
    
    return elems;
}


// <----- Evaluates Expression (Base) ----->
// <----- ACCEPTS: cleaned postfix slElement vector w/truth value assignments ----->
// <----- RETURNS: boolean truth-value of expression ----->
bool evalBase (vector<slElement> elems)
{
    stack<slElement> evalStack;
    
    for (int i = 0; i < elems.size(); i++)
    {
        if ( !isOperator(elems[i].getChar()) )      // If Operand
            evalStack.push(elems[i]);                   // push to stack
    
        else                                        // If Operator
        {
            if ( elems[i].getChar() == '~' )            // If unary operator ~
            {                                               // evaluate (negate)
                evalStack.top().setTruth( !(evalStack.top().getTruthVal()) );
            }
            else                                        // If binary operator
            {                                               // perform binary eval (pass to eval func)
                slElement right( evalStack.top().getChar(), evalStack.top().getTruthVal() );
                evalStack.pop();
                slElement left( evalStack.top().getChar(), evalStack.top().getTruthVal() );
                evalStack.pop();
                slElement oper( elems[i].getChar(), elems[i].getTruthVal() );
                
                evalStack.push ( eval(left, right, oper) );
            }
        }
    }
    return evalStack.top().getTruthVal();
}


// <----- Performs Binary Operator Evaluation ----->
// <----- ACCEPTS: left slElement, right slElement, operator slElement ----->
// <----- RETURNS: operator element w/truth value of local expression ----->
slElement  eval (slElement left, slElement right, slElement oper)
{
    slElement result( '$' );    // Resulting slElement uses '$' charVal to flag as non-operator in further eval
    
    if ( oper.getChar() == '&' )                        // If Conjunction &
    {
        if ( (left.getTruthVal() == true) && (right.getTruthVal() == true) )
        {
            result.setTruth(true);
            return result;
        }
        else
        {
            result.setTruth(false);
            return result;
        }
    }
    
    else if ( oper.getChar() == 'v' )                   // If Disjunction v
    {
        if ( (left.getTruthVal() == true) || (right.getTruthVal() == true) )
        {
            result.setTruth(true);
            return result;
        }
        else
        {
            result.setTruth(false);
            return result;
        }
    }
    
    else if ( oper.getChar() == '>' )                   // If Conditional >
    {
        if ( (left.getTruthVal() == true) && (right.getTruthVal() == false) )
        {
            result.setTruth(false);
            return result;
        }
        else
        {
            result.setTruth(true);
            return result;
        }
    }
    
    else if ( oper.getChar() == '=' )                   // If Biconditional =
    {
        if ( left.getTruthVal() == right.getTruthVal() )
        {
            result.setTruth(true);
            return result;
        }
        else
        {
            result.setTruth(false);
            return result;
        }
    }
    
    return result;
}


// <----- Controls User Interaction for Primary Functionality ----->
// <----- ACCEPTS: n/a ----->
// <----- RETURNS: boolean ----->
bool cont()
{
    string contresp;
    cout << endl << endl;
    cout << "Would you like to evaluate another proposition?  ( Y / N ) " << endl;
    cout << "----- --- ---- -- -------- ------- ------------" << endl;
    
    cin >> contresp;
    cout << endl << endl;
    
    if (contresp == "Y" || contresp == "y" || contresp == "YES" || contresp == "yes" || contresp == "Yes")
        return true;
    else if (contresp == "N" || contresp == "n" || contresp == "NO" || contresp == "no" || contresp == "No")
        cout << "Thank you for using Slac!" << endl << "Exiting with normal conditions now." << endl;
    return false;
}
