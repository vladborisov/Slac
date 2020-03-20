2020 Slac Rework 
Essentially a re-implementation of the original Slac
Better commented, more efficient, & overall just more clean


--



VERSION 1.1 UPDATES
------- --- -------
+  In the Slac 1.0 release version, users had to manually specify and assign truth-values for each atomic component/sentence. Slac 1.1 replaces this with an automatic scan/prompt system. This is a bit more time & memory-intensive, but serves for a much better user experience.
+  Added support for sentences with brackets as well as parentheses.
+  Controls for input and minor bug fixes.

=============================================

Ahah! My first project.

Minoring in Logic, I quickly realized that sentential and propositional systems rely on a mostly mechanical method of evaluation. Hence, Slac was born! You'll find it here.

 

Slac is designed to be readable and complete. I built it from scratch during my breaks between classes over the course of a week, and it occupies just over 400 lines of C++ at the current moment.

 

Starting from a basic user-input string expression and the truth-value assignment of its atomic components, Slac
  cleans the string up for internal use
  converts the proposition to reverse-Polish (postfix) notation
  tokenizes the proposition and converts it into a vector of custom class objects
  allows the user to define the assigned truth-values of individual sentences
  evaluates the proposition
  
Slac allows for sentences of infinite length and complexity, allowing for parentheses as needed.

 

As time permits, I’d like to add some more robust error handling. The nature of the program requires lots of user input of a specific form, and that needs to be controlled for undefined behavior. Some closing recaps of atomic component values might be useful, too.

In the long run, I’d love to add some kind of truth-tree generating feature. The backbone for something like that is quite different from what we have here, though, and a GUI might be necessary. Regardless, the ability to construct and display full truth-tables for any given expression without defined truth-value assignments would be very interesting.

- Vladislav Borisov -
