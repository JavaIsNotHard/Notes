
## Context free grammar 

## Top down parser 
- starts at the root of the syntax tree or the start symbol of the grammar 
- this continues until 
	- the parse tree only contains terminal symbols 
	- there is a mismatch between the fringe of the tree and the input source
- if the parser selection a wrong production rule for a given non terminal symbol then it has be backtrack and consider another production rule.

- we can also make the top down parser backtracking free which includes recursive descent parsers and LL(1) parsers.
- backtracking algorithm is good when the parser always selects the right choice but when it chooses the wrong there is a cost associated with the backtracking to previous state

- there is also the problem of infinite left recursion which needs to be eliminated
- also eliminate any indirect left recursive production
- backtrack free grammar using lookahead symbol to determine which production rule to expand
- we remove backtracking by left-factoring method

- there are two types of backtrack-free parser which includes
	- [[top down recursive descent parser]]
	- [[LL(1) parser]]

