/*
? Postfix = an empty string 
& an empty operator stack

^ Infix 4 * 2 +3 + 8 / 4


? POSTFIX -> 4
^ if * is greater priority then stack push if less or equal push into postfix 
! paraenthesis never has parenthesis

^ compare star to hand if greater prio
& * -> 
&  + -> 
? 4 -> 2 -> * -> 3 ->
? 4 -> 2 - * -> 3 + -> 8
? 4 -> 2 - * -> 3 + -> 8 -> 4 / -> +
 
*/

