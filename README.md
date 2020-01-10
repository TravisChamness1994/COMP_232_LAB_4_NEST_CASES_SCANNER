# COMP 232 Lab 4 - Nested Cases Scanner

### tokens and lexing intro

In this lab, you will implement a scanner (lexer) for the following simple grammar:

```
<program> ::= <statement> <EOF> | <statement> <program>

<statement> ::= <assignStmt> | <printStmt> | <repeatStmt>
<assignStmt> ::= <id> = <expr> ;
<printStmt> ::= print <expr> ;
<repeatStmt> ::= repeat ( <expr> ) <statement>

<expr> ::= <term> | <expr> <addOp> <term>
<term> ::= <factor> | <term> <multOp> <factor>
<factor> ::= <id> | <number> | - <factor> | ( <expr> )

<id> ::= <letter> | <id> <letter> | <id> <digit>

<number> ::= <integer> | <float>

<integer> ::= <digit> | <integer> <digit>
<float> ::= <digit> . | <digit> <float> | <float> <digit>

<letter> ::= a-z, A-Z
<digit> ::= 0-9
```

Your first task is to decide what the tokens should be in the grammar above. You have likely encountered a more formal definition for tokens and lexing in the lecture section. Here we will think of the tokens in a simpler way: tokens are to statements as words and punctuation are to sentences.

For example, if we were to tokenize the following english sentence:

`Nick, that is not a sentence.`

would be lexed into:

```
< NOUN Nick >
< PUNCUTATION , >
< PRONOUN that >
< VERB is >
< ADVERB not >
< ARTICLE a >
< NOUN sentence >
< PUNCTUATION . >
```

Note that lexing is disjoint from syntax; a sequence of random words which make absolutely no sense as a sentence could still be lexed correctly, but they could not be parsed to create any coherent meaning.

Look through the grammar above and decide what the tokens are. When you think you have them, ask me to check your answers. Once I've approved your list of token types, you're ready to move on.

(HINT: There are 12 of them).

### state machine

Now that you've identified all of the types of tokens, you can create a finite state machine for tokenization.

The machine should have a single starting state. The machine's transitions depend on the value of the next character, and whenever a character is read for which there is no transition out of the current state, the implication is that this character is the start of the next token, so the current token (whose type is determined by the state the machine is in) is complete.

Draw a state machine to construct all of the tokens as described in the grammar. When you think your state machine is complete, ask to have it checked. Once your machine has been approved, you're ready to move on.

### lexer implementation

You've now finished the theoretical foundation of the lexer to be implemented. Using [this project](./lab_4_scanner.zip) as a starting point to complete a lexer for the provided grammar.

Open `scanner.h`. Read through the `TOKEN_TYPE` enum, ensuring that all of your token types (as well as `INVALID_TOKEN` and `NO_TOKEN_TYPE`) are there.

Read the `TOKEN_VALUE` union. Decide what member of this union (if any) a token of each `TOKEN_TYPE` will need to populate. Note that `TOKEN_TYPES` for which the type conveys all necessary information about the token do not need to store any `TOKEN_VALUE`.

Read the `STATE` enum. Notice that many `TOKEN_TYPE`s don't have a dedicated state in the finite state machine. Why is the state machine so small? What qualities can you identify about the `TOKEN_TYPE`s which don't have a corresponding state in the state machine? How will tokens of these types be lexed?

Once you are comfortable with the code in `scanner.h`, move on to `main.c`. This main is relatively simple; it essentially lexes in a loop until the resulting token is an `EOF` token, printing and freeing each token in the process.

Note the first line in the `main` function:

```c
freopen(argv[1], "r", stdin);
```

By now we should be familiar with `freopen`; we know this line is overwriting the `stdin` so input can be more easily gathered from elsewhere. `argv[1]` is the string value of the first program argument; it should be the name of the file we wish to use as input.

We have a provided input file, `input.txt`. We need `argv[1]` to be the path to `input.txt` in order for the input from `input.txt` to be used.

CLion allows us to provide program arguments in the Run Configurations; open the `Run` menu, select `Edit Configurations`, select the `scanner` executable and in the `Program arguments` box enter `../input.txt`.

Once you are comfortable with both `scanner.h` and `main.c`, you're ready to work on your lexer!

Open `scanner.c`. There are four `TODO`s in the file.

The intended functionality for `freeToken` and `printToken` should be intuitive, and we will not discuss them further here.

The `scanner` function should emulate your state machine to tokenize inputs, character by character, to create and return a single token. It will do so by reading 1 new character in each iteration of a while loop. It must use these characters (along with the current state of the finite state machine) to determine what state transitions to take, and to determine when to assign value to the token being constructed.

When a token is composed of multiple characters, you'll generally know it's "done" when you encounter a character that is not part of the token being composed (for instance, if your state machine is in the `INTEGER_STATE` and you encounter a letter, that letter is clearly not part of the integer, so it must be part of the **next** token.

When this happens, you'll want to put the unused character back on the input stream so it can be reconsidered as the beginning of the following token. Check out the manual entry for `ungetc`.

The following is a successful sample run for the provided [`input.txt`](./lab_4_scanner/input.txt):

```
<IDENT, firstvar>
<ASSIGN>
<INT, 123>
<SEMICOLON>
<IDENT, secondVar>
<ASSIGN>
<FLOAT, 21.000000>
<SEMICOLON>
<IDENT, var3>
<ASSIGN>
<FLOAT, 1.500000>
<SEMICOLON>
<KEYWORD, repeat>
<LPAREN>
<INT, 10>
<RPAREN>
<IDENT, var3>
<ASSIGN>
<INT, 2>
<MULT_OP, *>
<LPAREN>
<IDENT, firstvar>
<ADD_OP, +>
<IDENT, secondvar>
<RPAREN>
<MULT_OP, />
<LPAREN>
<IDENT, firstvar>
<ADD_OP, +>
<INT, 2>
<RPAREN>
<SEMICOLON>
<KEYWORD, repeat>
<LPAREN>
<IDENT, firstvar>
<ADD_OP, +>
<INT, 2>
<MULT_OP, *>
<IDENT, secondvar>
<RPAREN>
<KEYWORD, print>
<IDENT, firstvar>
<SEMICOLON>
<EOF>


Process finished with exit code 0

```

Don't forget to test your program with Valgrind and remove any memory errors!

Don't forget to include documentation with sample runs in your submission! You likely want to expand `input.txt` to more rigorously test your lexer.