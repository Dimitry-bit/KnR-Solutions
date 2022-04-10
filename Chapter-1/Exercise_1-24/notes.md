## Check For:
  - rudimentary syntax errors like;
    - [ ]
    - ( )
    - { }
    - " "
    - ' '

  - Escape sequences:
    - \a 	Bell (alert)
    - \b 	Backspace
    - \f 	Form feed
    - \n  New line
    - \r 	Carriage return
    - \t 	Horizontal tab
    - \v 	Vertical tab
    - \' 	Single quotation mark
    - \" 	Double quotation mark
    - \\ 	Backslash
    
  - Comments:
    - /* */
    - //

---

# LOG Errors

error: expected statement before ‘)’ token
   90 |         if (!is_string_literal))

error: expected ‘)’ before ‘{’ token
   90 |         if ((!is_string_literal)
      |            ~                    ^
      |                                 )
   91 |         {

error: expected declaration or statement at end of input
  208 | }
      | ^

error: stray ‘\’ in program
   94 |         \\
      |         ^~

warning: unknown escape sequence: '\s'
   69 |         if (current_char == '\s' && !is_in_comment && is_string_literal)
      |                             ^~~~

warning: missing terminating ' character
   89 | '
      | ^

warning: missing terminating " character
   89 | "
      | ^
