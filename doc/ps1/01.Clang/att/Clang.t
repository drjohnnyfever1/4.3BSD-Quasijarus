.so cmac1
.nr Cl 2
.CH 2 "C LANGUAGE"
.H 1 "C LANGUAGE"
.H 2 "LEXICAL CONVENTIONS"
.P
There are six classes of tokens\ -\ 
identifiers, keywords, constants, strings, operators, and other separators.
Blanks, tabs, new\(hylines,
and comments (collectively, ``white space'') as described below
are ignored except as they serve to separate
tokens.
Some white space is required to separate
otherwise adjacent identifiers,
keywords, and constants.
.P
If the input stream has been parsed into tokens
up to a given character, the next token is taken
to include the longest string of characters
which could possibly constitute a token.
.H 3 "Comments"
.P
The characters
.B
/*
.R
introduce a comment which terminates
with the characters
\fB*/\fR.
Comments do not nest.
.H 3 "Identifiers (Names)"
.P
An identifier is a sequence of letters and digits.
The first character must be a letter.
The underscore
(\fB_\fR)
counts as a letter.
Uppercase and lowercase letters
are different.
Although there is no limit on the length of a name,
only initial characters are significant: at least
eight characters of a non-external name, and perhaps
fewer for external names.
Moreover, some implementations may collapse case
distinctions for external names.
The external name sizes include:
.DS I
.ft C
.nf
.ss 0
PDP-11               7 characters, 2 cases
VAX-11            >100 characters, 2 cases
AT&T 3B 20        >100 characters, 2 cases
.ss 12
.ft R
.fi
.DE
.H 3 "Keywords"
.P
The following identifiers are reserved for use
as keywords and may not be used otherwise:
.DS I
.ta 0.8i 1.6i 2.4i 3.2i 4.0i
\fBauto	do	for	return	typedef
break	double	goto	short	union
case	else	if	sizeof	unsigned
char	enum	int	static	void
continue	external	long	struct	while
default	float	register	switch\fR
.ta 0.5i
.DE
.P 0
Some implementations also reserve the words
.B
fortran
.R
and
.B asm\fR.
.H 3 "Constants"
.P
There are several kinds
of constants.
Each has a type; an introduction to types is given in ``NAMES.''
Hardware characteristics that affect sizes are summarized in
``Hardware Characteristics'' under ``LEXICAL CONVENTIONS.''
.H 4 "Integer Constants"
.br
.P
An integer constant consisting of a sequence of digits
is taken
to be octal if it begins with
.B
0
.R
(digit zero).
An octal constant consists of the digits \fB0\fR through \fB7\fR only.
A sequence of digits preceded by
.B
0x
.R
or
.B
0X
.R
(digit zero) is taken to be a hexadecimal integer.
The hexadecimal digits include
.B
a
.R
or
.B
A
.R
through
.B
f
.R
or
.B
F
.R
with values 10 through 15.
Otherwise, the integer constant is taken to be decimal.
A decimal constant whose value exceeds the largest
signed machine integer is taken to be
\fBlong\fR;
an octal or hex constant which exceeds the largest unsigned machine integer
is likewise taken to be
.B
long\fR.
.R
Otherwise, integer constants are \fBint\fR.
.H 4 "Explicit Long Constants"
.br
.P
A decimal, octal, or hexadecimal integer constant immediately followed
by
.B
l
.R
(letter ell)
or
.B
L
.R
is a long constant.
As discussed below,
on some machines
integer and long values may be considered identical.
.H 4 "Character Constants"
.br
.P
A character constant is a character enclosed in single quotes,
as in \'\fBx\fR'.
The value of a character constant is the numerical value of the
character in the machine's character set.
.P
Certain nongraphic characters,
the single quote
(\fB'\fR)
and the backslash
(\fB\e\fR),
may be represented according to the following table
of escape sequences:
.DS I
.ft C
.ss 0
new\(hyline            NL (LF)      \en
horizontal tab      HT           \et
vertical tab        VT           \ev
backspace           BS           \eb
carriage return     CR           \er
form feed           FF           \ef
backslash           \e            \e\e
single quote        '            \e'
bit pattern         \f(COddd\fC          \e\f(COddd\fC
.ss 12
.ft R
.DE
.P 0
The escape
\e\fIddd\fR
consists of the backslash followed by 1, 2, or 3 octal digits
which are taken to specify the value of the
desired character.
A special case of this construction is
.B
\e0
.R
(not followed
by a digit), which indicates the character
.B
NUL\fR.
.R
If the character following a backslash is not one
of those specified, the
behavior is undefined.
A new-line character is illegal in a character constant.
The type of a character constant is \fBint\fR.
.H 4 "Floating Constants"
.br
.P
A floating constant consists of
an integer part, a decimal point, a fraction part,
an
.B
e
.R
or
\fBE\fR,
and an optionally signed integer exponent.
The integer and fraction parts both consist of a sequence
of digits.
Either the integer part or the fraction
part (not both) may be missing.
Either the decimal point or
the
.B
e
.R
and the exponent (not both) may be missing.
Every floating constant has type \fBdouble\fR.
.H 4 "Enumeration Constants"
.br
.P
Names declared as enumerators
(see ``Structure, Union, and Enumeration Declarations'' under
``DECLARATIONS'')
have type \fBint\fR.
.H 3 "Strings"
.P
A string is a sequence of characters surrounded by
double quotes,
as in
\fB"..."\fR.
A string has type
``array of \fBchar\fR'' and storage class
\fBstatic\fR
(see ``NAMES'')
and is initialized with
the given characters.
The compiler places
a null byte
(\fB\e0\fR)
at the end of each string so that programs
which scan the string can
find its end.
In a string, the double quote character
(\fB"\fR)
must be preceded by
a
\fB\e\fR;
in addition, the same escapes as described for character
constants may be used.
.P
A
.B
\e
.R
and
the immediately following new\(hyline are ignored.
All strings, even when written identically, are distinct.
.H 3 "Hardware Characteristics"
.P
The following figures summarize
certain hardware properties that vary from machine to machine.
.DS
.TS
center box;
c s s
c s s
l | l1 lp8.
\fBDEC PDP-11\fR
(ASCII)
.sp
_
char	8 bits
int	16
short	16
long	32
float	32
double	64
float range	   \(+-10	\(+-38
\^	\^
double range	   \(+-10	\(+-38
\^	\^
.TE
.FG 4 4 1 "DEC PDP-11 HARDWARE CHARACTERISTICS"
.DE
.DS
.TS
center box;
c s s
c s s
l | l1 lp8.
\fBDEC VAX-11\fR
(ASCII)
.sp
_
char	8 bits
int	32
short	16
long	32
float	32
double	64
float range	   \(+-10	\(+-38
\^	\^
double range	   \(+-10	\(+-38
\^	\^
.TE
.FG 4 4 1 "DEC VAX-11 HARDWARE CHARACTERISTICS"
.DE
.DS
.TS
center box;
c s s
c s s
l | l1 lp8.
\fBAT&T 3B\fR
(ASCII)
.sp
_
char	8 bits
int	32
short	16
long	32
float	32
double	64
float range	   \(+-10	\(+-38
\^	\^
double range	   \(+-10	\(+-308
\^	\^
.TE
.FG 4 4 1 "AT&T 3B HARDWARE CHARACTERISTICS"
.DE
.P
.H 2 "SYNTAX NOTATION"
Syntactic categories are indicated by
.I
italic
.R
type
and literal words and characters
in
\fBbold\fR
type.
Alternative categories are listed on separate lines.
An optional terminal or nonterminal symbol is
indicated by the subscript ``opt,'' so that
.DS I
{ \fIexpression\v'0.5'opt\v'-0.5'\fR }
.DE
.P 0
indicates an optional expression enclosed in braces.
The syntax is summarized in ``SYNTAX SUMMARY''.
.H 2 "NAMES"
.P
The C language bases the interpretation of an
identifier upon two attributes of the identifier - its
.I
storage class
.R
and its
.I
type\fR.
The storage class determines the location and lifetime
of the storage associated with an identifier;
the type determines
the meaning of the values
found in the identifier's storage.
.H 3 "Storage Class"
.P
There are four declarable storage classes:
.BL 6 1
.LI
Automatic
.LI
Static
.LI
External
.LI
Register.
.LE
.P 0
Automatic variables are local to each invocation of
a block (see ``Compound Statement or Block'' in 
``STATEMENTS'') and are discarded upon exit from the block.
Static variables are local to a block but retain
their values upon reentry to a block even after control
has left the block.
External variables exist and retain their values throughout
the execution of the entire program and
may be used for communication between
functions, even separately compiled functions.
Register variables are (if possible) stored in the fast registers
of the machine; like automatic
variables, they are local to each block and disappear on exit from the block.
.H 3 "Type"
.P
The C language supports several
fundamental
types of objects.
Objects declared as characters
(\fBchar\fR)
are large enough to store any member of the implementation's
character set.
If a genuine character from that character set is
stored in a \fBchar\fR variable,
its value is equivalent to the integer code for that character.
Other quantities may be stored into character variables, but
the implementation is machine dependent.
In particular, \fBchar\fR may be signed or unsigned by default.
.P
Up to three sizes of integer, declared
.B
short
.R
\fBint\fR,
\fBint\fR,
and
.B
long
.R
\fBint\fR,
are available.
Longer integers provide no less storage than shorter ones,
but the implementation may make either short integers or long integers,
or both, equivalent to plain integers.
``Plain'' integers have the natural size suggested
by the host machine architecture.
The other sizes are provided to meet special needs.
.P
The properties of \fBenum\fR types (see ``Structure, Union, and Enumeration Declarations''
under ``DECLARATIONS'')
are identical to those of
some integer types.
The implementation may use the range of values to
determine how to allot storage.
.P
Unsigned
integers, declared
.B
unsigned,
.R
obey the laws of arithmetic modulo
2\v'-0.5'\fIn\fR\v'0.5'
where \fIn\fR is the number of bits in the representation.
(On the
PDP-11,
unsigned long quantities are not supported.)
.P
Single-precision floating point
(\fBfloat\fR)
and double precision floating point
(\fBdouble\fR)
may be synonymous in some implementations.
.P
Because objects of the foregoing types can usefully be interpreted
as numbers, they will be referred to as
.I
arithmetic
.R
types.
\fBChar\fR,
.B
int
.R
of all sizes whether \fBunsigned\fR or not, and
.B
enum
.R
will collectively be called
.I
integral
.R
types.
The
.B
float
.R
and
.B
double
.R
types will collectively be called
.I
floating
.R
types.
.P
The
.B
void
.R
type
specifies an empty set of values.
It is used as the type returned by functions that
generate no value.
.P
Besides the fundamental arithmetic types, there is a
conceptually infinite class of derived types constructed
from the fundamental types in the following ways:
.BL 6 1
.LI
\fIArrays\fR
of objects of most types
.LI
\fIFunctions\fR
which return objects of a given type
.LI
\fIPointers\fR
to objects of a given type
.LI
\fIStructures\fR
containing a sequence of objects of various types
.LI
\fIUnions\fR
capable of containing any one of several objects of various types.
.LE
.P 0
In general these methods
of constructing objects can
be applied recursively.
.H 2 "OBJECTS AND LVALUES"
.P
An
.I
object
.R
is a manipulatable region of storage.
An
.I
lvalue
.R
is an expression referring to an object.
An obvious example of an lvalue
expression is an identifier.
There are operators which yield lvalues:
for example,
if
.B
E
.R
is an expression of pointer type, then
.B
*E
.R
is an lvalue
expression referring to the object to which
.B
E
.R
points.
The name ``lvalue'' comes from the assignment expression
.B
E1\ =\ E2
.R
in which the left operand
.B
E1
.R
must be
an lvalue expression.
The discussion of each operator
below indicates whether it expects lvalue operands and whether it
yields an lvalue.
.H 2 "CONVERSIONS"
.P
A number of operators may, depending on their operands,
cause conversion of the value of an operand from one type to another.
This part explains the result to be expected from such
conversions.
The conversions demanded by most ordinary operators are summarized under
``Arithmetic Conversions.''
The summary will be supplemented
as required by the discussion
of each operator.
.H 3 "Characters and Integers"
.P
A character or a short integer may be used wherever an
integer may be used.
In all cases
the value is converted to an integer.
Conversion of a shorter integer
to a longer preserves sign.
Whether or not sign-extension occurs for characters is machine
dependent, but it is guaranteed that a member of the
standard character set is non-negative.
Of the machines treated here,
only the
PDP-11
and
VAX-11
sign-extend.
On these machines,
.B
char
.R
variables range in value from
\-128 to 127.
The more explicit type
.B
unsigned
.R
.B
char
.R
forces the values to range from 0 to 255.
.P
On machines that treat characters as signed,
the characters of the
ASCII
set are all non-negative.
However, a character constant specified
with an octal escape suffers sign extension
and may appear negative;
for example,
\fB\'\e377\'\fR
\fRhas the value
.B
-1\fR.
.P
When a longer integer is converted to a shorter
integer
or to a
.B
char,
.R
it is truncated on the left.
Excess bits are simply discarded.
.H 3 "Float and Double"
.P
All floating arithmetic in C is carried out in double precision.
Whenever a
.B
float
.R
appears in an expression it is lengthened to
.B
double
.R
by zero padding its fraction.
When a
.B
double
.R
must be
converted to
\fBfloat\fR,
for example by an assignment,
the
.B
double
.R
is rounded before
truncation to
.B
float
.R
length.
This result is undefined if it cannot be represented as a float.
.H 3 "Floating and Integral"
.P
Conversions of floating values to integral type
are rather machine dependent.
In particular, the direction of truncation of negative numbers
varies.
The result is undefined if
it will not fit in the space provided.
.P
Conversions of integral values to floating type
are well behaved.
Some loss of accuracy occurs
if the destination lacks sufficient bits.
.H 3 "Pointers and Integers"
.P
An expression of integral type may be added to or subtracted from
a pointer; in such a case,
the first is converted as
specified in the discussion of the addition operator.
Two pointers to objects of the same type may be subtracted;
in this case, the result is converted to an integer
as specified in the discussion of the subtraction
operator.
.H 3 "Unsigned"
.P
Whenever an unsigned integer and a plain integer
are combined, the plain integer is converted to unsigned
and the result is unsigned.
The value
is the least unsigned integer congruent to the signed
integer (modulo 2\v'-0.3'\s-2wordsize\s+2\v'0.3').
In a 2's complement representation,
this conversion is conceptual; and there is no actual change in the
bit pattern.
.P
When an unsigned \fBshort\fR integer is converted to
\fBlong\fR,
the value of the result is the same numerically as that of the
unsigned integer.
Thus the conversion amounts to padding with zeros on the left.
.H 3 "Arithmetic Conversions"
.P
A great many operators cause conversions
and yield result types in a similar way.
This pattern will be called the ``usual arithmetic conversions.''
.AL 1 6 
.LI
First, any operands of type
.B
char
.R
or
.B
short
.R
are converted to
\fBint\fR,
and any operands of type \fBunsigned char\fR
or \fBunsigned short\fR are converted
to \fBunsigned int\fR.
.LI
Then, if either operand is
.B
double,
.R
the other is converted to
.B
double
.R
and that is the type of the result.
.LI
Otherwise, if either operand is \fBunsigned long\fR,
the other is converted to \fBunsigned long\fR and that
is the type of the result.
.LI
Otherwise, if either operand is
\fBlong\fR,
the other is converted to
.B
long
.R
and that is the type of the result.
.LI
Otherwise, if one operand is \fBlong\fR, and
the other is \fBunsigned int\fR, they are both
converted to \fBunsigned long\fR and that is
the type of the result.
.LI
Otherwise, if either operand is
.B
unsigned,
.R
the other is converted to
.B
unsigned
.R
and that is the type of the result.
.LI
Otherwise, both operands must be
\fBint\fR,
and that is the type of the result.
.LE
.H 3 "Void"
.P
The (nonexistent) value of a
.B
void
.R
object may not be used in any way,
and neither explicit nor implicit conversion may be applied.
Because a void expression denotes a nonexistent value,
such an expression may be used only
as an expression statement
(see ``Expression Statement'' under ``STATEMENTS'')
or as the left operand
of a comma expression (see ``Comma Operator'' under ``EXPRESSIONS'').
.P
An expression may be converted to
type
.B
void
.R
by use of a cast.
For example, this makes explicit the discarding of the value
of a function call used as an expression statement.
.H 2 "EXPRESSIONS"
.P
The precedence of expression operators is the same
as the order of the major
subsections of this section, highest precedence first.
Thus, for example, the expressions referred to as the operands of
.B
+
.R
(see ``Additive Operators'')
are those expressions defined under ``Primary Expressions'',
``Unary Operators'', and ``Multiplicative Operators''.
Within each subpart, the operators have the same
precedence.
Left- or right-associativity is specified
in each subsection for the operators
discussed therein.
The precedence and associativity of all the expression
operators are summarized in the
grammar of ``SYNTAX SUMMARY''.
.P
Otherwise, the order of evaluation of expressions
is undefined.  In particular, the compiler
considers itself free to
compute subexpressions in the order it believes
most efficient
even if the subexpressions
involve side effects.
The order in which subexpression evaluation takes place is unspecified.
Expressions involving a commutative and associative
operator
(\fB*,\fR
\fB+\fR,
\fB&\fR,
\fB|\fR,
\fB^\fR)
may be rearranged arbitrarily even in the presence
of parentheses;
to force a particular order of evaluation,
an explicit temporary must be used.
.P
The handling of overflow and divide check
in expression evaluation
is undefined.
Most existing implementations of C ignore integer overflows;
treatment of
division by 0 and all floating-point exceptions
varies between machines and is usually
adjustable by a library function.
.H 3 "Primary Expressions"
.P
Primary expressions
involving \fB\.\fR,
\fB->\fR,
subscripting, and function calls
group left to right.
.DS I
\fIprimary-expression:
        identifier
        constant
        string
        ( expression )
        primary-expression [ expression ]
        primary-expression ( expression-list\v'0.5'opt\v'-0.5' )
        primary-expression . identifier
        primary-expression -> identifier\fR
.DE
.DS I
\fIexpression-list:
        expression
        expression-list , expression\fR
.DE
.P 0
An identifier is a primary expression provided it has been
suitably declared as discussed below.
Its type is specified by its declaration.
If the type of the identifier is ``array of .\|.\|.'',
then the value of the identifier expression
is a pointer
to the first object in the array; and the
type of the expression is
``pointer to .\|.\|.''.
Moreover, an array identifier is not an lvalue
expression.
Likewise, an identifier which is declared
``function returning .\|.\|.'',
when used except in the function-name position
of a call, is converted to ``pointer to function returning .\|.\|.''.
.P
A
constant is a primary expression.
Its type may be
\fBint\fR,
\fBlong\fR,
or
.B
double
.R
depending on its form.
Character constants have type
.B
int 
.R
and floating constants have type
.B
double\fR.
.R
.P
A string is a primary expression.
Its type is originally ``array of
\fBchar\fR'',
but following
the same rule given above for identifiers,
this is modified to ``pointer to
\fBchar\fR'' and
the
result is a pointer to the first character
in the string.
(There is an exception in certain initializers;
see ``Initialization'' under ``DECLARATIONS.'')
.P
A parenthesized expression is a primary expression
whose type and value are identical
to those of the unadorned expression.
The presence of parentheses does
not affect whether the expression is an
lvalue.
.P
A primary expression followed by an expression in square
brackets is a primary expression.
The intuitive meaning is that of a subscript.
Usually, the primary expression has type ``pointer to .\|.\|.'',
the subscript expression is
\fBint\fR,
and the type of the result is ``\|.\|.\|.\|''.
The expression
.B
E1[E2]
.R
is
identical (by definition) to
.B
*((E1)+(E2))\fR.
All the clues
needed to understand
this notation are contained in this subpart together
with the discussions
in ``Unary Operators'' and ``Additive Operators'' on identifiers,
.B
* 
.R
and
.B
+,
.R
respectively.
The implications are summarized under ``Arrays, Pointers, and Subscripting''
under ``TYPES REVISITED.''
.P
A function call is a primary expression followed by parentheses
containing a possibly
empty, comma-separated list of expressions
which constitute the actual arguments to the
function.
The primary expression must be of type ``function returning .\|.\|.,''
and the result of the function call is of type ``\|.\|.\|.\|''.
As indicated
below, a hitherto unseen identifier followed
immediately by a left parenthesis
is contextually declared
to represent a function returning
an integer;
thus in the most common case, integer-valued functions
need not be declared.
.P
Any actual arguments of type
.B
float
.R
are
converted to
.B
double
.R
before the call.
Any of type
.B
char
.R
or
.B
short
.R
are converted to
.B
int\fR.
.R
Array names are converted to pointers.
No other conversions are performed automatically;
in particular, the compiler does not compare
the types of actual arguments with those of formal
arguments.
If conversion is needed, use a cast;
see ``Unary Operators'' and ``Type Names'' under
``DECLARATIONS.''
.P
In preparing for the call to a function,
a copy is made of each actual parameter.
Thus, all argument passing in C is strictly by value.
A function may
change the values of its formal parameters, but
these changes cannot affect the values
of the actual parameters.
It is possible
to pass a pointer on the understanding
that the function may change the value
of the object to which the pointer points.
An array name is a pointer expression.
The order of evaluation of arguments is undefined by the language;
take note that the various compilers differ.
Recursive calls to any
function are permitted.
.P
A primary expression followed by a dot followed by an identifier
is an expression.
The first expression must be a structure or a union, and the identifier
must name a member of the structure or union.
The value is the named member of the structure or union, and it is
an lvalue if the first expression is an lvalue.
.P
A primary expression followed by an arrow (built from
.B
-
.R
and
.B
>
.R
)
followed by an identifier
is an expression.
The first expression must be a pointer to a structure or a union
and the identifier must name a member of that structure or union.
The result is an lvalue referring to the named member
of the structure or union
to which the pointer expression points.
Thus the expression
.B
E1->MOS
.R
is the same as
.B
(*E1).MOS\fR.
.R
Structures and unions are discussed in
``Structure, Union, and Enumeration Declarations'' under
``DECLARATIONS.''
.H 3 "Unary Operators"
.P
Expressions with unary operators
group right to left.
.tr ~~
.DS I
\fIunary-expression:
        * expression
        & lvalue
        - expression
        ! expression
        ~ expression
        ++ lvalue
        --lvalue
        lvalue ++
        lvalue --
        ( type-name ) expression\fR
        sizeof\fI expression\fR
        sizeof\fI ( type-name )\fR
.DE
.P 0
The unary
.B
*
.R
operator
means
.I
indirection
.R
;
the expression must be a pointer, and the result
is an lvalue referring to the object to
which the expression points.
If the type of the expression is ``pointer to .\|.\|.,''
the type of the result is ``\|.\|.\|.\|''.
.P
The result of the unary
.B
&
.R
operator is a pointer
to the object referred to by the
lvalue.
If the type of the lvalue is ``\|.\|.\|.\|'',
the type of the result is ``pointer to .\|.\|.''.
.P
The result
of the unary
.B
-
.R
operator
is the negative of its operand.
The usual arithmetic conversions are performed.
The negative of an unsigned quantity is computed by
subtracting its value from
2\v'-0.5'\fIn\fR\^\v'0.5' where \fIn\fR\^ is the number of bits in
the corresponding signed type.
.sp
.tr ~~
There is no unary
.B
+
.R
operator.
.P
The result of the logical negation operator
.B
!
.R
is one if the value of its operand is zero, zero if the value of its
operand is nonzero.
The type of the result is
.B
int\fR.
.R
It is applicable to any arithmetic type
or to pointers.
.P
The
.B
~
.R
operator yields the one's complement of its operand.
The usual arithmetic conversions are performed.
The type of the operand must be integral.
.P
The object referred to by the lvalue operand of prefix
.B
++
.R
is incremented.
The value is the new value of the operand
but is not an lvalue.
The expression
.B
++x
.R
is equivalent to
\fBx=x+1\fR.
See the discussions ``Additive Operators'' and ``Assignment
Operators'' for information on conversions.
.P
The lvalue operand of prefix
.B
--
.R
is decremented
analogously to the
prefix
.B
++
.R
operator.
.P
When postfix
.B
++
.R
is applied to an lvalue,
the result is the value of the object referred to by the lvalue.
After the result is noted, the object
is incremented in the same
manner as for the prefix
.B
++
.R
operator.
The type of the result is the same as the type of the lvalue expression.
.P
When postfix
.B
--
.R
is applied to an lvalue,
the result is the value of the object referred to by the lvalue.
After the result is noted, the object
is decremented in the manner as for the prefix
.B
--
.R
operator.
The type of the result is the same as the type of the lvalue
expression.
.P
An expression preceded by the parenthesized name of a data type
causes conversion of the value of the expression to the named type.
This construction is called a
.I
cast\fR.
.R
Type names are described in ``Type Names'' under ``Declarations.''
.P
The
.B
sizeof
.R
operator yields the size
in bytes of its operand.
(A
.I
byte
.R
is undefined by the language
except in terms of the value of
.B
sizeof\fR.
.R
However, in all existing implementations,
a byte is the space required to hold a
\fBchar.\fR)
When applied to an array, the result is the total
number of bytes in the array.
The size is determined from
the declarations of
the objects in the expression.
This expression is semantically an
.B
unsigned
.R
constant and may
be used anywhere a constant is required.
Its major use is in communication with routines
like storage allocators and I/O systems.
.P
The
.B
sizeof
.R
operator
may also be applied to a parenthesized type name.
In that case it yields the size in bytes of an object
of the indicated type.
.P
The construction
\fBsizeof(\fItype\|\fR\^)\fR\^
is taken to be a unit,
so the expression
\fBsizeof(\fItype\|\fB)-2\fR
is the same as
\fB(sizeof(\fItype\|\fB))-2\fR.
.H 3 "Multiplicative Operators"
.P
The multiplicative operators
\fB*\fR,
\fB/\fR,
and
.B
%
.R
group left to right.
The usual arithmetic conversions are performed.
.DS I
\fImultiplicative expression:
        expression * expression
        expression / expression
        expression % expression\fR
.DE
.P
The binary
.B
*
.R
operator indicates multiplication.
The
.B
*
.R
operator is associative,
and expressions with several multiplications at the same
level may be rearranged by the compiler.
The binary
.B
/
.R
operator indicates division.
.P
The binary
.B
%
.R
operator yields the remainder
from the division of the first expression by the second.
The operands must be integral.
.P
When positive integers are divided, truncation is toward 0;
but the form of truncation is machine-dependent
if either operand is negative.
On all machines covered by this manual,
the remainder has the same sign as the dividend.
It is always true that
.B
(a/b)*b\ +\ a%b
.R
is equal to
.B
a
.R
(if
.B
b
.R
is not 0).
.H 3 "Additive Operators"
.P
The additive operators
.B
+
.R
and
.B
-
.R
group left to right.
The usual arithmetic conversions are performed.
There are some additional type possibilities for each operator.
.DS I
\fIadditive-expression:
        expression + expression
        expression - expression\fR
.DE
.P 0
The result of the
.B
+
.R
operator is the sum of the operands.
A pointer to an object in an array and
a value of any integral type
may be added.
The latter is in all cases converted to
an address offset
by multiplying it
by the length of the object to which the
pointer points.
The result is a pointer
of the same type as the original pointer
which points to another object in the same array,
appropriately offset from the original object.
Thus if
.B
P
.R
is a pointer
to an object in an array, the expression
.B
P+1
.R
is a pointer
to the next object in the array.
No further type combinations are allowed for pointers.
.P
The
.B
+
.R
operator is associative,
and expressions with several additions at the same level may
be rearranged by the compiler.
.P
The result of the
.B
-
.R
operator is the difference of the operands.
The usual arithmetic conversions are performed.
Additionally,
a value of any integral type
may be subtracted from a pointer,
and then the same conversions for addition apply.
.P
If two pointers to objects of the same type are subtracted,
the result is converted
(by division by the length of the object)
to an
.B
int
.R
representing the number of
objects separating
the pointed-to objects.
This conversion will in general give unexpected
results unless the pointers point
to objects in the same array, since pointers, even
to objects of the same type, do not necessarily differ
by a multiple of the object length.
.H 3 "Shift Operators"
.P
The shift operators
.B
<<
.R
and
.B
>>
.R
group left to right.
Both perform the usual arithmetic conversions on their operands,
each of which must be integral.
Then the right operand is converted to
\fBint\fR;
the type of the result is that of the left operand.
The result is undefined if the right operand is negative
or greater than or equal to the length of the object in bits.
.DS I
\fIshift-expression:
        expression << expression
        expression >> expression\fR
.DE
.P 0
The value of
.B
E1<<E2
.R
is
.B
E1
.R
(interpreted as a bit
pattern) left-shifted
.B
E2
.R
bits.
Vacated bits are 0 filled.
The value of
.B
E1>>E2
.R
is
.B
E1
.R
right-shifted
.B
E2
.R
bit positions.
The right shift is guaranteed to be logical
(0 fill)
if
.B
E1
.R
is
\fBunsigned\fR;
otherwise, it may be
arithmetic.
.H 3 "Relational Operators"
.P
The relational operators group left to right. 
.DS I
\fIrelational-expression:
        expression < expression
        expression > expression
        expression <= expression
        expression >= expression\fR
.DE
.P 0
The operators
.B
<
.R
(less than),
.B
>
.R
(greater than), \fB<=\fR
(less than
or equal to), and
.B
>=
.R
(greater than or equal to)
all yield 0 if the specified relation is false
and 1 if it is true.
The type of the result is
.B
int\fR.
The usual arithmetic conversions are performed.
Two pointers may be compared;
the result depends on the relative locations in the address space
of the pointed-to objects.
Pointer comparison is portable only when the pointers point to objects
in the same array.
.H 3 "Equality Operators"
.P
.DS I
\fIequality-expression:
        expression == expression
        expression != expression\fR
.DE
.P
The
.B
==
.R
(equal to) and the
.B
!=
.R
(not equal to) operators
are exactly analogous to the relational
operators except for their lower
precedence.
(Thus
.B
a<b\ ==\ c<d
.R
is 1 whenever
.B
a<b
.R
and
.B
c<d
.R
have the same truth value).
.P
A pointer may be compared to an integer
only if the
integer is the constant 0.
A pointer to which 0 has been assigned is guaranteed
not to point to any object
and will appear to be equal to 0.
In conventional usage, such a pointer is considered to be null.
.H 3 "Bitwise \s-1AND\s0 Operator"
.P
.DS I
\fIand-expression:
        expression & expression\fR
.DE
.P
The
.B
&
.R
operator is associative,
and expressions involving
.B
&
.R
may be rearranged.
The usual arithmetic conversions are performed.
The result is the bitwise
AND
function of the operands.
The operator applies only to integral
operands.
.H 3 "Bitwise Exclusive \s-1OR\s0 Operator"
.DS I
\fIexclusive-or-expression:
        expression ^ expression\fR
.DE
.P
The
.B
^
.R
operator is associative,
and expressions involving
.B
^
.R
may be rearranged.
The usual arithmetic conversions are performed;
the result is
the bitwise exclusive
OR
function of
the operands.
The operator applies only to integral
operands.
.H 3 "Bitwise Inclusive \s-1OR\s0 Operator"
.DS I
\fIinclusive-or-expression:
        expression | expression\fR
.DE
.P
The
.B
|
.R
operator is associative,
and expressions involving
.B
|
.R
may be rearranged.
The usual arithmetic conversions are performed;
the result is the bitwise inclusive
OR
function of its operands.
The operator applies only to integral
operands.
.H 3 "Logical \s-1AND\s0 Operator"
.DS I
\fIlogical-and-expression:
        expression && expression\fR
.DE
.P
The
.B
&&
.R
operator groups left to right.
It returns 1 if both its operands
evaluate to nonzero, 0 otherwise.
Unlike
\fB&\fR,
.B
&&
.R
guarantees left to right
evaluation; moreover, the second operand is not evaluated
if the first operand is 0.
.P
The operands need not have the same type, but each
must have one of the fundamental
types or be a pointer.
The result is always
.B
int\fR.
.R
.H 3 "Logical \s-1OR\s0 Operator"
.DS I
\fIlogical-or-expression:
        expression || expression\fR
.DE
.P
The
.B
||
.R
operator groups left to right.
It returns 1 if either of its operands
evaluates to nonzero, 0 otherwise.
Unlike
\fB|\fR,
.B
||
.R
guarantees left to right evaluation; moreover,
the second operand is not evaluated
if the value of the first operand is nonzero.
.P
The operands need not have the same type, but each
must
have one of the fundamental types
or be a pointer.
The result is always
.B
int\fR.
.R
.H 3 "Conditional Operator"
.DS I
\fIconditional-expression:
        expression ? expression : expression\fR
.DE
.P
Conditional expressions group right to left.
The first expression is evaluated;
and if it is nonzero, the result is the value of the
second expression, otherwise that of third expression.
If possible, the usual arithmetic conversions are performed
to bring the second and third expressions to a common type.
If both are structures or unions of the same type,
the result has the type of the structure or union.
If both pointers are of the same type,
the result has the common type.
Otherwise, one must be a pointer and the other the constant 0,
and the result has the type of the pointer.
Only one of the second and third
expressions is evaluated.
.H 3 "Assignment Operators"
.P
There are a number of assignment operators,
all of which group right to left.
All require an lvalue as their left operand,
and the type of an assignment expression is that
of its left operand.
The value is the value stored in the
left operand after the assignment has taken place.
The two parts of a compound assignment operator are separate
tokens.
.DS I
\fIassignment-expression:
        lvalue = expression
        lvalue += expression
        lvalue -= expression
        lvalue *= expression
        lvalue /= expression
        lvalue %= expression
        lvalue >>= expression
        lvalue <<= expression
        lvalue &= expression
        lvalue ^= expression
        lvalue |= expression\fR
.DE
.P
In the simple assignment with
\fB=\fR,
the value of the expression replaces that of the object
referred
to by the lvalue.
If both operands have arithmetic type,
the right operand is converted to the type of the left
preparatory to the assignment.
Second, both operands may be structures or unions of the same type.
Finally, if the left operand is a pointer, the right operand must in general be a pointer
of the same type.
However, the constant 0 may be assigned to a pointer;
it is guaranteed that this value will produce a null
pointer distinguishable from a pointer to any object.
.P
The behavior of an expression
of the form
\fBE1\fR\^ \fIop\fR\^ = \fBE2\fR\^
may be inferred by
taking it as equivalent to
\fBE1 = E1 \fIop\fR\^ (\fBE2\fR\^);
however,
.B
E1
.R
is evaluated only once.
In
.B
+=
.R
and
\fB-=\fR,
the left operand may be a pointer; in which case, the (integral) right
operand is converted as explained
in ``Additive Operators.''
All right operands and all nonpointer left operands must
have arithmetic type.
.H 3 "Comma Operator"
.DS I
\fIcomma-expression:
        expression , expression\fR
.DE
.P
A pair of expressions separated by a comma is evaluated
left to right, and the value of the left expression is
discarded.
The type and value of the result are the
type and value of the right operand.
This operator groups left to right.
In contexts where comma is given a special meaning,
e.g., in lists of actual arguments
to functions (see ``Primary Expressions'') and lists
of initializers (see ``Initialization'' under ``DECLARATIONS''),
the comma operator as described in this subpart
can only appear in parentheses. For example,
.DS I
\fBf(a, (t=3, t+2), c)\fR
.DE
.P 0
has three arguments, the second of which has the value 5.
.H 2 "DECLARATIONS"
.P
Declarations are used to specify the interpretation
which C gives to each identifier; they do not necessarily
reserve storage associated with the identifier.
Declarations have the form
.DS I
\fIdeclaration:
        decl-specifiers declarator-list\v'0.5'opt\v'-0.5' ;\fR
.DE
.P 0
The declarators in the declarator-list
contain the identifiers being declared.
The decl-specifiers
consist of a sequence of type and storage class specifiers.
.DS I
\fIdecl-specifiers:
        type-specifier decl-specifiers\v'0.5'opt\v'-0.5'
        sc-specifier decl-specifiers\v'0.5'opt\v'-0.5'\fR
.DE
.P 0
The list must be self-consistent in a way described below.
.H 3 "Storage Class Specifiers"
.P
The sc-specifiers are:
.DS I
\fIsc-specifier:\fB
        auto
        static
        extern
        register
        typedef\fR
.DE
.P 0
The
.B
typedef
.R
specifier does not reserve storage
and is called a ``storage class specifier'' only for syntactic convenience.
See ``Typedef'' for more information.
The meanings of the various storage classes were discussed in ``Names.''
.P
The
\fBauto\fR,
\fBstatic\fR,
and
.B
register
.R
declarations also serve as definitions
in that they cause an appropriate amount of storage to be reserved.
In the
.B
extern
.R
case,
there must be an external definition (see ``External Definitions'')
for the given identifiers
somewhere outside the function in which they are declared.
.P
A
.B
register
.R
declaration is best thought of as an
.B
auto
.R
declaration, together with a hint to the compiler
that the variables declared will be heavily used.
Only the first few
such declarations in each function are effective.
Moreover, only variables of certain types will be stored in registers;
on the
PDP-11,
they are
.B
int
.R
or pointer.
One other restriction applies to register variables:
the address-of operator
.B
&
.R
cannot be applied to them.
Smaller, faster programs can be expected if register declarations
are used appropriately,
but future improvements in code generation
may render them unnecessary.
.P
At most, one sc-specifier may be given in a declaration.
If the sc-specifier is missing from a declaration, it
is taken to be
.B
auto
.R
inside a function,
.B
extern
.R
outside.
Exception:
functions are never
automatic.
.H 3 "Type Specifiers"
.P
The type-specifiers are
.DS I
\fItype-specifier:
        struct-or-union-specifier
        typedef-name
        enum-specifier
basic-type-specifier:
        basic-type
        basic-type basic-type-specifiers
basic-type:\fB
        char
        short
        int
        long
        unsigned
        float
        double
        void\fR
.DE
.P 0
At most one of the words \fBlong\fR or \fBshort\fR
may be specified in conjunction with \fBint\fR;
the meaning is the same as if \fBint\fR were not mentioned.
The word \fBlong\fR may be specified in conjunction with
\fBfloat\fR;
the meaning is the same as \fBdouble\fR.
The word \fBunsigned\fR may be specified alone, or
in conjunction with \fBint\fR or any of its short
or long varieties, or with \fBchar\fR.
.P
Otherwise, at most on type-specifier may be
given in a declaration.
In particular, adjectival use of \fBlong\fR,
\fBshort\fR, or \fBunsigned\fR is not permitted
with \fBtypedef\fR names.
If the type-specifier is missing from a declaration,
it is taken to be \fBint\fR.
.P
Specifiers for structures, unions, and enumerations are discussed in
``Structure, Union, and Enumeration Declarations.''
Declarations with
.B
typedef
.R
names are discussed in ``Typedef.''
.H 3 "Declarators"
.P
The declarator-list appearing in a declaration
is a comma-separated sequence of declarators,
each of which may have an initializer.
.DS I
\fIdeclarator-list:
        init-declarator
        init-declarator , declarator-list
.DE
.DS I
\fIinit-declarator:
        declarator initializer\v'0.5'opt\v'-0.5'\fR
.DE
.P 0
Initializers are discussed in ``Initialization''.
The specifiers in the declaration
indicate the type and storage class of the objects to which the
declarators refer.
Declarators have the syntax:
.DS I
\fIdeclarator:
        identifier
        ( declarator )
        * declarator
        declarator ()
        declarator [ constant-expression\v'0.5'opt\v'-0.5' ]\fR
.DE
.P 0
The grouping is
the same as in expressions.
.H 3 "Meaning of Declarators"
.P
Each declarator is taken to be
an assertion that when a construction of
the same form as the declarator appears in an expression,
it yields an object of the indicated
type and storage class.
.P
Each declarator contains exactly one identifier; it is this identifier that
is declared.
If an unadorned identifier appears
as a declarator, then it has the type
indicated by the specifier heading the declaration.
.P
A declarator in parentheses is identical to the unadorned declarator,
but the binding of complex declarators may be altered by parentheses.
See the examples below.
.P
Now imagine a declaration
.DS I
\fBT D1\fR
.DE
.P 0
where
.B
T
.R
is a type-specifier (like
\fBint\fR,
etc.)
and
.B
D1
.R
is a declarator.
Suppose this declaration makes the identifier have type
``\|.\|.\|.\|
.B
T
.R
,''
where the ``\|.\|.\|.\|'' is empty if
.B
D1
.R
is just a plain identifier
(so that the type of
.B
x
.R
in
\fB`int x''\fR
is just
\fBint\fR).
Then if
.B
D1
.R
has the form
.DS I
\fB*D\fR
.DE
.P 0
the type of the contained identifier is
``\|.\|.\|.\| pointer to
.B
T
.R
\&.''
.P
If
.B
D1
.R
has the form
.DS I
\fBD()\fR
.DE
.P 0
then the contained identifier has the type
``\|.\|.\|. function returning
\fBT\fR.''
.P
If
.B
D1
.R
has the form
.DS I
\fBD[\fIconstant-expression\fB]\fR
.DE
.P 0
or
.DS I
\fBD[]\fR
.DE
.P 0
then the contained identifier has type
``\|.\|.\|.\| array of
\fBT\fR.''
In the first case, the constant
expression
is an expression
whose value is determinable at compile time
, whose type is
.B
int\fR,
and whose value is positive.
(Constant expressions are defined precisely in ``Constant Expressions.'')
When several ``array of'' specifications are adjacent, a multidimensional
array is created;
the constant expressions which specify the bounds
of the arrays may be missing only for the first member of the sequence.
This elision is useful when the array is external
and the actual definition, which allocates storage,
is given elsewhere.
The first constant expression may also be omitted
when the declarator is followed by initialization.
In this case the size is calculated from the number
of initial elements supplied.
.P
An array may be constructed from one of the basic types, from a pointer,
from a structure or union,
or from another array (to generate a multidimensional array).
.P
Not all the possibilities
allowed by the syntax above are actually
permitted.
The restrictions are as follows:
functions may not return
arrays or functions
although they may return pointers;
there are no arrays of functions although
there may be arrays of pointers to functions.
Likewise, a structure or union may not contain a function;
but it may contain a pointer to a function.
.P
As an example, the declaration
.DS I
\fBint i, *ip, f(), *fip(), (*pfi)();\fR
.DE
.P 0
declares an integer
\fBi\fR,
a pointer
.B
ip
.R
to an integer,
a function
.B
f
.R
returning an integer,
a function
.B
fip
.R
returning a pointer to an integer,
and a pointer
.B
pfi
.R
to a function which
returns an integer.
It is especially useful to compare the last two.
The binding of
.B
*fip()
.R
is
.B
*(fip())\fR.
.R
The declaration suggests,
and the same construction in an expression
requires, the calling of a function
.B
fip\fR.
.R
Using indirection through the (pointer) result
to yield an integer.
In the declarator
\fB(*pfi)()\fR,
the extra parentheses are necessary, as they are also
in an expression, to indicate that indirection through
a pointer to a function yields a function, which is then called;
it returns an integer.
.P
As another example,
.DS I
\fBfloat fa[17], *afp[17];\fR
.DE
.P 0
declares an array of
.B
float
.R
numbers and an array of
pointers to
.B
float
.R
numbers.
Finally,
.DS I
\fBstatic int x3d[3][5][7];\fR
.DE
.P 0
declares a static 3-dimensional array of integers,
with rank 3\(mu5\(mu7.
In complete detail,
.B
x3d
.R
is an array of three items;
each item is an array of five arrays;
each of the latter arrays is an array of seven
integers.
Any of the expressions
\fBx3d\fR,
\fBx3d[i]\fR,
\fBx3d[i][j]\fR,
.B
x3d[i][j][k]
.R
may reasonably appear in an expression.
The first three have type ``array''
and the last has type
.B
int\fR.
.R
.H 3 "Structure and Union Declarations"
.P
A structure
is an object consisting of a sequence of named members.
Each member may have any type.
A union is an object which may, at a given time, contain any one
of several members.
Structure and union specifiers have the same form.
.DS I
\fIstruct-or-union-specifier:
        struct-or-union { struct-decl-list }
        struct-or-union identifier { struct-decl-list }
        struct-or-union identifier
.DE
.DS I
\fIstruct-or-union:\fB
        struct
        union\fR
.DE
.P 0
The
struct-decl-list
.ne 4
is a sequence of declarations for the members of the structure or union:
.DS I
\fIstruct-decl-list:
        struct-declaration
        struct-declaration struct-decl-list
.DE
.DS I
\fIstruct-declaration:
        type-specifier struct-declarator-list ;
.DE
.DS I
\fIstruct-declarator-list:
        struct-declarator
        struct-declarator , struct-declarator-list\fR
.DE
.P 0
In the usual case, a struct-declarator is just a declarator
for a member of a structure or union.
A structure member may also consist of a specified number of bits.
Such a member is also called a
.I
field ;
.R
its length,
a non-negative constant expression,
is set off from the field name by a colon.
.DS I
\fIstruct-declarator:
        declarator
        declarator : constant-expression
        : constant-expression\fR
.DE
.P 0
Within a structure, the objects declared
have addresses which increase as the declarations
are read left to right.
Each nonfield member of a structure
begins on an addressing boundary appropriate
to its type;
therefore, there may
be unnamed holes in a structure.
Field members are packed into machine integers;
they do not straddle words.
A field which does not fit into the space remaining in a word
is put into the next word.
No field may be wider than a word.
.P
Fields are assigned right to left
on the
PDP-11
and
VAX-11,
left to right on the 3B 20.
.P
A struct-declarator with no declarator, only a colon and a width,
indicates an unnamed field useful for padding to conform
to externally-imposed layouts.
As a special case, a field with a width of 0
specifies alignment of the next field at an implementation dependant boundary.
.P
The language does not restrict the types of things that
are declared as fields,
but implementations are not required to support any but
integer fields.
Moreover,
even
.B
int
.R
fields may be considered to be unsigned.
On the
PDP-11,
fields are not signed and have only integer values;
on the
VAX-11,
fields declared with
.B
int
.R
are treated as containing a sign.
For these reasons,
it is strongly recommended that fields be declared as
.B
unsigned\fR.
.R
In all implementations,
there are no arrays of fields,
and the address-of operator
.B
&
.R
may not be applied to them, so that there are no pointers to
fields.
.P
A union may be thought of as a structure all of whose members
begin at offset 0 and whose size is sufficient to contain
any of its members.
At most, one of the members can be stored in a union
at any time.
.P
A structure or union specifier of the second form, that is, one of
.DS I
        \fBstruct \fIidentifier { struct-decl-list \fR}
        \fBunion \fIidentifier { struct-decl-list \fR}
.DE
.P 0
declares the identifier to be the
.I
structure tag
.R
(or union tag)
of the structure specified by the list.
A subsequent declaration may then use
the third form of specifier, one of
.DS I
        \fBstruct \fIidentifier\fR
        \fBunion \fIidentifier\fR
.DE
.P 0
Structure tags allow definition of self-referential
structures. Structure tags also
permit the long part of the declaration to be
given once and used several times.
It is illegal to declare a structure or union
which contains an instance of
itself, but a structure or union may contain a pointer to an instance of itself.
.P
The third form of a structure or union specifier may be
used prior to a declaration which gives the complete specification
of the structure or union in situations in which the size
of the structure or union is unnecessary.
The size is unnecessary in two situations: when a
pointer to a structure or union is being declared and
when a \fBtypedef\fR name is declared to be a synonym
for a structure or union.
This, for example, allows the declaration of a pair
of structures which contain pointers to each other.
.P
The names of members and tags do not conflict
with each other or with ordinary variables.
A particular name may not be used twice
in the same structure,
but the same name may be used in several different structures in the same scope.
.P
A simple but important example of a structure declaration is
the following binary tree structure:
.DS I
\fBstruct tnode 
{
        char tword[20];
        int count;
        struct tnode *left;
        struct tnode *right;
};\fR
.DE
.P 0
which contains an array of 20 characters, an integer, and two pointers
to similar structures.
Once this declaration has been given, the
declaration
.DS I
\fBstruct tnode s, *sp;\fR
.DE
.P 0
declares
.B
s
.R
to be a structure of the given sort
and
.B
sp
.R
to be a pointer to a structure
of the given sort.
With these declarations, the expression
.DS I
\fBsp->count\fR
.DE
.P 0
refers to the
.B
count
.R
field of the structure to which
.B
sp
.R
points;
.DS I
\fBs.left\fR
.DE
.P 0
refers to the left subtree pointer
of the structure
\fBs\fR;
and
.DS I
\fBs.right->tword[0]\fR
.DE
.P 0
refers to the first character of the
.B
tword
.R
member of the right subtree of
.B
s\fR.
.R
.P
.H 3 "Enumeration Declarations"
.P
Enumeration variables and constants have integral type.
.DS I
\fIenum-specifier:\fB
        enum\fI { enum-list \fR}\fB
        enum \fIidentifier { enum-list \fR}\fB
        enum \fIidentifier
.sp
enum-list:
        enumerator
        enum-list , enumerator
.sp
enumerator:
        identifier
        identifier = constant-expression\fR
.DE
.P 0
The identifiers in an enum-list are declared as constants
and may appear wherever constants are required.
If no enumerators with
.B
=
.R
appear, then the values of the
corresponding constants begin at 0 and increase by 1 as the declaration is
read from left to right.
An enumerator with
.B
=
.R
gives the associated identifier the value
indicated; subsequent identifiers continue the progression from the assigned value.
.P
The names of enumerators in the same scope must all be distinct
from each other and from those of ordinary variables.
.P
The role of the identifier in the enum-specifier
is entirely analogous to that of the structure tag
in a struct-specifier; it names a particular enumeration.
For example,
.DS L 
\fBenum color { chartreuse, burgundy, claret=20, winedark };
\&...
enum color \(**cp, col;
\&...
col = claret;
cp = &col;
\&...
if (\(**cp == burgundy) ...\fR
.DE
.P 0
makes
.B
color
.R
the enumeration-tag of a type describing various colors,
and then declares
.B
cp
.R
as a pointer to an object of that type,
and
.B
col
.R
as an object of that type.
The possible values are drawn from the set {0,1,20,21}.
.H 3 "Initialization"
.P
A declarator may specify an initial value for the
identifier being declared.
The initializer is preceded by
.B
= 
.R
and
consists of an expression or a list of values nested in braces.
.DS I
\fIinitializer:
        = expression
        = { initializer-list }
        = { initializer-list , }
.DE
.DS I
\fIinitializer-list:
        expression
        initializer-list , initializer-list\fR
        { \fIinitializer-list \fR}
        { \fIinitializer-list\fR , }
.DE
.P
All the expressions in an initializer
for a static or external variable must be constant
expressions, which are described in ``CONSTANT EXPRESSIONS'',
or expressions which reduce to the address of a previously
declared variable, possibly offset by a constant expression.
Automatic or register variables may be initialized by arbitrary
expressions involving constants and previously declared variables and functions.
.P
Static and external variables that are not initialized are
guaranteed to start off as zero.
Automatic and register variables that are not initialized
are guaranteed to start off as garbage.
.P
When an initializer applies to a
.I
scalar
.R
(a pointer or an object of arithmetic type),
it consists of a single expression, perhaps in braces.
The initial value of the object is taken from
the expression; the same conversions as for assignment are performed.
.P
When the declared variable is an
.I
aggregate
.R
(a structure or array),
the initializer consists of a brace-enclosed, comma-separated list of
initializers for the members of the aggregate
written in increasing subscript or member order.
If the aggregate contains subaggregates, this rule
applies recursively to the members of the aggregate.
If there are fewer initializers in the list than there are members of the aggregate,
then the aggregate is padded with zeros.
It is not permitted to initialize unions or automatic aggregates.
.P
Braces may in some cases be omitted.
If the initializer begins with a left brace, then
the succeeding comma-separated list of initializers initializes
the members of the aggregate;
it is erroneous for there to be more initializers than members.
If, however, the initializer does not begin with a left brace,
then only enough elements from the list are taken to account
for the members of the aggregate; any remaining members
are left to initialize the next member of the aggregate of which
the current aggregate is a part.
.P
A final abbreviation allows a
.B
char
.R
array to be initialized by a string.
In this case successive characters of the string
initialize the members of the array.
.P
For example,
.DS I
\fBint x[] = { 1, 3, 5 };\fR
.DE
.P 0
declares and initializes
.B
x
.R
as a one-dimensional array which has three members, since no size was specified
and there are three initializers.
.DS I
\fBfloat y[4][3] = 
{
        { 1, 3, 5 },
        { 2, 4, 6 },
        { 3, 5, 7 },
};\fR
.DE
.P 0
is a completely-bracketed initialization:
1, 3, and 5 initialize the first row of
the array
\fBy[0]\fR,
namely
\fBy[0][0]\fR,
\fBy[0][1]\fR,
and
.B
y[0][2]\fR.
.R
Likewise, the next two lines initialize
.B
y[1]
.R
and
.B
y[2]\fR.
.R
The initializer ends early and therefore
.B
y[3]
.R
is initialized with 0.
Precisely, the same effect could have been achieved by
.DS I
\fBfloat y[4][3] = 
{
        1, 3, 5, 2, 4, 6, 3, 5, 7
};\fR
.DE
.P 0
The initializer for
.B
y
.R
begins with a left brace but that for
.B
y[0]
.R
does not;
therefore, three elements from the list are used.
Likewise, the next three are taken successively for
.B
y[1]
.R
and
.B
y[2]\fR.
.R
Also,
.DS I
\fBfloat y[4][3] = 
{
        { 1 }, { 2 }, { 3 }, { 4 }
};\fR
.DE
.P 0
initializes the first column of
.B
y
.R
(regarded as a two-dimensional array)
and leaves the rest 0.
.P
Finally,
.DS I
\fBchar msg[] = "Syntax error on line %s\en";\fR
.DE
.P 0
shows a character array whose members are initialized
with a string.
.H 3 "Type Names"
.P
In two contexts (to specify type conversions explicitly
by means of a cast
and as an argument of
\fBsizeof\fR),
it is desired to supply the name of a data type.
This is accomplished using a ``type name'', which in essence
is a declaration for an object of that type which omits the name of
the object.
.DS I
\fItype-name:
        type-specifier abstract-declarator
.DE
.DS I
\fIabstract-declarator:
        empty
        ( abstract-declarator )
        * abstract-declarator
        abstract-declarator ()
        abstract-declarator\fR\^ [ \fIconstant-expression\v'0.5'opt\v'-0.5' \fR\^]
.DE
.P 0
To avoid ambiguity,
in the construction
.DS I
        \fI( abstract-declarator \fR)
.DE
.P 0
the
abstract-declarator
is required to be nonempty.
Under this restriction,
it is possible to identify uniquely the location in the abstract-declarator
where the identifier would appear if the construction were a declarator
in a declaration.
The named type is then the same as the type of the
hypothetical identifier.
For example,
.DS I
\fBint
int *
int *[3]
int (*)[3]
int *()
int (*)()
int (*[3])()\fR
.DE
.P 0
name respectively the types ``integer,'' ``pointer to integer,''
``array of three pointers to integers,''
``pointer to an array of three integers,''
``function returning pointer to integer,''
``pointer to function returning an integer,''
and ``array of three pointers to functions returning an integer.''
.H 3 "Typedef"
.P
Declarations whose ``storage class'' is
.B
typedef
.R
do not define storage but instead
define identifiers which can be used later
as if they were type keywords naming fundamental
or derived types.
.DS I
\fItypedef-name:\fR
        \fIidentifier\fR
.DE
.P 0
Within the scope of a declaration involving
\fBtypedef\fR,
each identifier appearing as part of
any declarator therein becomes syntactically
equivalent to the type keyword
naming the type
associated with the identifier
in the way described in ``Meaning of Declarators.''
For example,
after
.DS I
\fBtypedef int MILES, *KLICKSP;
typedef struct { double re, im; } complex;\fR
.DE
.P 0
the constructions
.DS I
\fBMILES distance;
extern KLICKSP metricp;
complex z, *zp;\fR
.DE
.P 0
are all legal declarations; the type of
.B
distance
.R
is
\fBint\fR,
that of
.B
metricp
.R
is ``pointer to \fBint\fR, ''
and that of
.B
z
.R
is the specified structure.
The
.B
zp
.R
is a pointer to such a structure.
.P
The
.B
typedef
.R
does not introduce brand-new types, only synonyms for
types which could be specified in another way.
Thus
in the example above
.B
distance
.R
is considered to have exactly the same type as
any other
.B
int
.R
object.
.H 2 "STATEMENTS"
.P
Except as indicated, statements are executed in sequence.
.H 3 "Expression Statement"
.P
Most statements are expression statements, which have
the form
.DS I
\fIexpression \fR;
.DE
.P 0
Usually expression statements are assignments or function
calls.
.H 3 "Compound Statement or Block"
.P
So that several statements can be used where one is expected,
the compound statement (also, and equivalently, called ``block'') is provided:
.DS I
\fIcompound-statement:
        { declaration-list\v'0.5'opt\v'-0.5' statement-list\v'0.5'opt\v'-0.5' }
.DE
.DS I
\fIdeclaration-list:
        declaration
        declaration declaration-list
.DE
.DS I
\fIstatement-list:
        statement
        statement statement-list\fR
.DE
.P 0
If any of the identifiers
in the declaration-list were previously declared,
the outer declaration is pushed down for the duration of the block,
after which it resumes its force.
.P
Any initializations of
.B
auto
.R
or
.B
register
.R
variables are performed each time the block is entered at the top.
It is currently possible
(but a bad practice)
to transfer into a block;
in that case the initializations are not performed.
Initializations of
.B
static
.R
variables are performed only once when the program
begins execution.
Inside a block,
.B
extern
.R
declarations do not reserve storage
so initialization is not permitted.
.H 3 "Conditional Statement"
.P
The two forms of the conditional statement are
.DS I
\fBif\fR\^ ( \fIexpression\fR\^ ) \fIstatement\fR\^
\fBif\fR\^ ( \fIexpression\fR\^ ) \fIstatement \fBelse \fIstatement\fR\^
.DE
.P 0
In both cases, the expression is evaluated;
and if it is nonzero, the first substatement
is executed.
In the second case, the second substatement is executed
if the expression is 0.
The ``else'' ambiguity is resolved by connecting
an
.B
else
.R
with the last encountered
\fBelse\fR-less
.B
if\fR.
.R
.H 3 "While Statement"
.P
The
.B
while
.R
statement has the form
.DS I
\fBwhile\fR\^ ( \fIexpression\fR\^ ) \fIstatement\fR\^
.DE
.P 0
The substatement is executed repeatedly
so long as the value of the
expression remains nonzero.
The test takes place before each execution of the
statement.
.H 3 "Do Statement"
.P
The
.B
do
.R
statement has the form
.DS I
\fBdo \fIstatement  \fBwhile\fR\^ ( \fIexpression \fR\^) ;
.DE
.P 0
The substatement is executed repeatedly until
the value of the expression becomes 0.
The test takes place after each execution of the
statement.
.H 3 "For Statement"
.P
The
.B
for
.R
statement has the form:
.DS I 
\fBfor\fI ( exp-1\v'0.5'opt\v'-0.5' ; exp-2\v'0.5'opt\v'-0.5' ; exp-3\v'0.5'opt\v'-0.5' ) statement\fR
.DE
.P 0
.sp
Except for the behavior of \fBcontinue\fR,
this statement is equivalent to
.DS I
\fIexp-1 \fR;
\fBwhile\fR\^ ( \fIexp-2\ ) \fR\^
{
        \fIstatement
        exp-3 ;
}\fR
.DE
.P 0
Thus the first expression specifies initialization
for the loop; the second specifies
a test, made before each iteration, such
that the loop is exited when the expression becomes
0.
The third expression often specifies an incrementing
that is performed after each iteration.
.P
Any or all of the expressions may be dropped.
A missing
.I
exp-2
.R
makes the
implied
.B
while
.R
clause equivalent to
\fBwhile(1)\fR;
other missing expressions are simply
dropped from the expansion above.
.H 3 "Switch Statement"
.P
The
.B
switch
.R
statement causes control to be transferred
to one of several statements depending on
the value of an expression.
It has the form
.DS I
\fBswitch\fR\^ ( \fIexpression\fR\^ ) \fIstatement\fR\^
.DE
.P 0
The usual arithmetic conversion is performed on the
expression, but the result must be
.B
int\fR.
.R
The statement is typically compound.
Any statement within the statement
may be labeled with one or more case prefixes
as follows:
.DS I
\fBcase \fIconstant-expression \fR:
.DE
.P 0
where the constant
expression
must be
.B
int\fR.
.R
No two of the case constants in the same switch
may have the same value.
Constant expressions are precisely defined in ``CONSTANT EXPRESSIONS.''
.P
There may also be at most one statement prefix of the
form
.DS I
\fBdefault :\fR
.DE
.P 0
When the
.B
switch
.R
statement is executed, its expression
is evaluated and compared with each case constant.
If one of the case constants is
equal to the value of the expression,
control is passed to the statement
following the matched case prefix.
If no case constant matches the expression
and if there is a
\fBdefault\fR,
prefix, control
passes to the prefixed
statement.
If no case matches and if there is no
\fBdefault\fR,
then
none of the statements in the
switch is executed.
.P
The prefixes
.B
case
.R
and
.B
default
.R
do not alter the flow of control,
which continues unimpeded across such prefixes.
To exit from a switch, see
``Break Statement.''
.P
Usually, the statement that is the subject of a switch is compound.
Declarations may appear at the head of this
statement,
but
initializations of automatic or register variables
are ineffective.
.H 3 "Break Statement"
.P
The statement
.DS I
\fBbreak ;\fR
.DE
.P 0
causes termination of the smallest enclosing
\fBwhile\fR,
\fBdo\fR,
\fBfor\fR,
or
\fBswitch\fR
statement;
control passes to the
statement following the terminated statement.
.H 3 "Continue Statement"
.P
The statement
.DS I
\fBcontinue ;\fR
.DE
.P 0
causes control to pass to the loop-continuation portion of the
smallest enclosing
\fBwhile\fR,
\fBdo\fR,
or
\fBfor\fR
statement; that is to the end of the loop.
More precisely, in each of the statements
.DS I
\fBwhile (...)        do                  for (...) 
{                  {                   {
      ...                ...                 ...
contin: ;          contin: ;           contin: ;
}                  } while (...);      }\fR
.DE
.P 0
a
.B
continue
.R
is equivalent to
.B
goto\ contin\fR.
.R
(Following the
.B
contin:
.R
is a null statement, see ``Null Statement''.)
.H 3 "Return Statement"
.P
A function returns to its caller by means of
the
.B
return
.R
statement which has one of the
forms
.DS I
\fBreturn ;
return \fIexpression \fR;
.DE
.P 0
In the first case, the returned value is undefined.
In the second case, the value of the expression
is returned to the caller
of the function.
If required, the expression is converted,
as if by assignment, to the type of
function in which it appears.
Flowing off the end of a function is
equivalent to a return with no returned value.
The expression may be parenthesized.
.H 3 "Goto Statement"
.P
Control may be transferred unconditionally by means of
the statement
.DS I
\fBgoto \fIidentifier \fR;
.DE
.P 0
The identifier must be a label
(see ``Labeled Statement'')
located in the current function.
.H 3 "Labeled Statement"
.P
Any statement may be preceded by
label prefixes of the form
.DS I
\fIidentifier \fR:
.DE
.P 0
which serve to declare the identifier
as a label.
The only use of a label is as a target of a
.B
goto\fR.
.R
The scope of a label is the current function,
excluding any subblocks in which the same identifier has been redeclared.
See ``SCOPE RULES.''
.H 3 "Null Statement"
.P
The null statement has the form
.DS I
\fB;\fR
.DE
.P 0
A null statement is useful to carry a label just before the
.B
}
.R
of a compound statement or to supply a null
body to a looping statement such as
.B
while\fR.
.R
.H 2 "EXTERNAL DEFINITIONS"
.P
A C program consists of a sequence of external definitions.
An external definition declares an identifier to
have storage class
.B
extern
.R
(by default)
or perhaps
\fBstatic\fR,
and
a specified type.
The type-specifier (see ``Type Specifiers'' in
``DECLARATIONS'') may also be empty, in which
case the type is taken to be
.B
int\fR.
.R
The scope of external definitions persists to the end
of the file in which they are declared just as the effect
of declarations persists to the end of a block.
The syntax of external definitions is the same
as that of all declarations except that
only at this level may the code for functions be given.
.H 3 "External Function Definitions"
.P
Function definitions have the form
.DS
\fIfunction-definition:
        decl-specifiers\v'0.5'opt\v'-0.5' function-declarator function-body\fR
.DE
.P 0
The only sc-specifiers
allowed
among the decl-specifiers
are
.B
extern
.R
or
\fBstatic\fR;
see ``Scope of Externals'' in 
``SCOPE RULES'' for the distinction between them.
A function declarator is similar to a declarator
for a ``function returning .\|.\|.\|'' except that
it lists the formal parameters of
the function being defined.
.DS I
\fIfunction-declarator:
        declarator ( parameter-list\v'0.5'opt\v'-0.5' )
.DE
.DS I
\fIparameter-list:
        identifier
        identifier , parameter-list\fR
.DE
.P 0
The function-body
has the form
.DS I
\fIfunction-body:
        declaration-list\v'0.5'opt\v'-0.5' compound-statement\fR
.DE
.P 0
The identifiers in the parameter list, and only those identifiers,
may be declared in the declaration list.
Any identifiers whose type is not given are taken to be
.B
int\fR.
.R
The only storage class which may be specified is
\fBregister\fR;
if it is specified, the corresponding actual parameter
will be copied, if possible, into a register
at the outset of the function.
.P
A simple example of a complete function definition is
.DS I
\fBint max(a, b, c)
        int a, b, c;
{
        int m;
.sp
        m = (a > b) ? a : b;
        return((m > c) ? m : c);
}\fR
.DE
.P 0
Here
.B
int
.R
is the type-specifier;
.B
max(a,\ b,\ c)
.R
is the function-declarator;
.B
int\ a,\ b,\ c;
.R
is the declaration-list for
the formal
parameters;
\fB{\ ...\ }\fR
is the
block giving the code for the statement.
.P
The C program converts all
.B
float
.R
actual parameters
to
\fBdouble\fR,
so formal parameters declared
.B
float
.R
have their declaration adjusted to read
.B
double\fR.
.R
All \fBchar\fR and \fBshort\fR formal parameter
declarations are similarly adjusted
to read \fBint\fR.
Also, since a reference to an array in any context
(in particular as an actual parameter)
is taken to mean
a pointer to the first element of the array,
declarations of formal parameters declared ``array of .\|.\|.\|''
are adjusted to read ``pointer to .\|.\|.\|.''
.H 3 "External Data Definitions"
.P
An external data definition has the form
.DS I
\fIdata-definition:
        declaration\fR
.DE
.P 0
The storage class of such data may be
.B
extern
.R
(which is the default)
or
.B
static 
.R
but not
.B
auto
.R
or
\fBregister\fR.
.H 2 "SCOPE RULES"
.P
A C program need not all
be compiled at the same time. The source text of the
program
may be kept in several files, and precompiled
routines may be loaded from
libraries.
Communication among the functions of a program
may be carried out both through explicit calls
and through manipulation of external data.
.P
Therefore, there are two kinds of scopes to consider:
first, what may be called the
.UL lexical
.UL scope
of an identifier, which is essentially the
region of a program during which it may
be used without drawing ``undefined identifier''
diagnostics;
and second, the scope
associated with external identifiers,
which is characterized by the rule
that references to the same external
identifier are references to the same object.
.H 3 "Lexical Scope"
.P
The lexical scope of identifiers declared in external definitions
persists from the definition through
the end of the source file
in which they appear.
The lexical scope of identifiers which are formal parameters
persists through the function with which they are
associated.
The lexical scope of identifiers declared at the head of a block
persists until the end of the block.
The lexical scope of labels is the whole of the
function in which they appear.
.P
In all cases, however,
if an identifier is explicitly declared at the head of a block,
including the block constituting a function,
any declaration of that identifier outside the block
is suspended until the end of the block.
.P
Remember also (see ``Structure, Union, and Enumeration Declarations'' in
``DECLARATIONS'') that tags, identifiers associated with
ordinary variables,
and identities associated with structure and union members
form three disjoint classes
which do not conflict.
Members and tags follow the same scope rules
as other identifiers.
The \fBenum\fR constants are in the same
class as ordinary variables and follow the same scope rules.
The
.B
typedef
.R
names are in the same class as ordinary identifiers.
They may be redeclared in inner blocks, but an explicit
type must be given in the inner declaration:
.DS I
\fBtypedef float distance;
\&...
{
     auto int distance;
     ...\fR
.DE
.P 0
The
.B
int
.R
must be present in the second declaration,
or it would be taken to be
a declaration with no declarators and type
.B
distance\fR.
.R
.H 3 "Scope of Externals"
.P
If a function refers to an identifier declared to be
\fBextern\fR,
then somewhere among the files or libraries
constituting the complete program
there must be at least one external definition
for the identifier.
All functions in a given program which refer to the same
external identifier refer to the same object,
so care must be taken that the type and size
specified in the definition
are compatible with those specified
by each function which references the data.
.P
It is illegal to explicitly initialize any external
identifier more than once in the set of files and libraries
comprising a multi-file program.
It is legal to have more than one data definition
for any external non-function identifier;
explicit use of \fBextern\fR does not
change the meaning of an external declaration.
.P
In restricted environments, the use of the \fBextern\fR
storage class takes on an additional meaning.
In these environments, the explicit appearance of the
\fBextern\fR keyword in external data declarations of
identities without initialization indicates that
the storage for the identifiers is allocated elsewhere,
either in this file or another file.
It is required that there be exactly one definition of
each external identifier (without \fBextern\fR)
in the set of files and libraries
comprising a mult-file program.
.P
Identifiers declared
.B
static
.R
at the top level in external definitions
are not visible in other files.
Functions may be declared
.B
static\fR.
.R
.nr Hu 1
.H 2 "COMPILER CONTROL LINES"
.P
The C compiler contains a preprocessor capable
of macro substitution, conditional compilation,
and inclusion of named files.
Lines beginning with
.B
#
.R
communicate
with this preprocessor.
There may be any number of blanks and horizontal tabs
between the \fB#\fR and the directive.
These lines have syntax independent of the rest of the language;
they may appear anywhere and have effect which lasts (independent of
scope) until the end of the source program file.
.nr Hu 1
.H 3 "Token Replacement"
.P
A compiler-control line of the form
.DS I
\fB#define \fIidentifier token-string\v'0.5'opt\v'-0.5'\fR
.DE
.P 0
causes the preprocessor to replace subsequent instances
of the identifier with the given string of tokens.
Semicolons in or at the end of the token-string are part of that string.
A line of the form
.DS
\fB#define \fIidentifier(identifier, ... )token-string\v'0.5'opt\v'-0.5'\fR
.DE
.P 0
where there is no space between the first identifier
and the
\fB(\fR,
is a macro definition with arguments.
There may be zero or more formal parameters.
Subsequent instances of the first identifier followed
by a
\fB(\fR,
a sequence of tokens delimited by commas, and a
\fB)\fR
are replaced
by the token string in the definition.
Each occurrence of an identifier mentioned in the formal parameter list
of the definition is replaced by the corresponding token string from the call.
The actual arguments in the call are token strings separated by commas;
however, commas in quoted strings or protected by
parentheses do not separate arguments.
The number of formal and actual parameters must be the same.
Strings and character constants in the token-string are scanned
for formal parameters, but
strings and character constants in the rest of the program are
not scanned for defined identifiers
to replacement.
.P
In both forms the replacement string is rescanned for more
defined identifiers.
In both forms
a long definition may be continued on another line
by writing
.B
\e
.R
at the end of the line to be continued.
.P
This facility is most valuable for definition of ``manifest constants,''
as in
.DS I
\fB#define TABSIZE 100
.sp
int table[TABSIZE];\fR
.DE
.P 0
A control line of the form
.DS I
\fB#undef \fIidentifier\fR
.DE
.P 0
causes the
identifier's preprocessor definition (if any) to be forgotten.
.P
If a \fB#define\fRd identifier is the subject of a subsequent
\fB#define\fR with no intervening \fB#undef\fR, then
the two token-strings are compared textually.
If the two token-strings are not identical
(all white space is considered as equivalent), then
the identifier is considered to be redefined.
.nr Hu 1
.H 3 "File Inclusion"
.P
A compiler control line of
the form
.DS I
\fB#include\fI "filename\|\fR"
.DE
.P 0
causes the replacement of that
line by the entire contents of the file
.I
filename\fR.
.R
The named file is searched for first in the directory
of the file containing the \fB#include\fR,
and then in a sequence of specified or standard places.
Alternatively, a control line of the form
.DS I
\fB#include\fI <filename\|\fR>
.DE
.P 0
searches only the specified or standard places
and not the directory of the \fB#include\fR.
(How the places are specified is not part of the language.)
.P
\fB#include\fRs
may be nested.
.nr Hu 1
.H 3 "Conditional Compilation"
.P
A compiler control line of the form
.DS I
\fB#if \fIrestricted-constant-expression\fR
.DE
.P 0
checks whether the restricted-constant expression evaluates to nonzero.
(Constant expressions are discussed in ``CONSTANT EXPRESSIONS'';
the following additional restrictions apply here:
the constant expression may not contain
.B
sizeof
.R
casts, or an enumeration constant.)
.P
A restricted constant expression may also contain the
additional unary expression
.DS I
\fBdefined \fIidentifier\fR
or
\fBdefined( \fIidentifier\fR
.DE
which evaluates to one if the identifier is currently
defined in the preprocessor and zero if it is not.
.P
All currently defined identifiers in restricted-constant-expressions
are replaced by their token-strings (except those identifiers
modified by \fBdefined\fR) just as in normal text.
The restricted constant expression will be evaluated only
after all expressions have finished.
During this evaluation, all undefined (to the procedure)
identifiers evaluate to zero.
.P
A control line of the form
.DS I
\fB#ifdef \fIidentifier\fR
.DE
.P 0
checks whether the identifier is currently defined
in the preprocessor; i.e., whether it has been the
subject of a
.B
#define
.R
control line.
It is equivalent to \fB#ifdef(\fIidentifier\fB)\fR.
A control line of the form
.DS I
\fB#ifndef \fIidentifier\fR
.DE
.P 0
checks whether the identifier is currently undefined
in the preprocessor.
It is equivalent to \fB#if!defined(\fIidentifier\fB)\fR.
.P
All three forms are followed by an arbitrary number of lines,
possibly containing a control line
.DS I
\fB#else\fR
.DE
.P 0
and then by a control line
.DS I
\fB#endif\fR
.DE
.P 0
If the checked condition is true,
then any lines
between
.B
#else
.R
and
.B
#endif
.R
are ignored.
If the checked condition is false, then any lines between
the test and a
.B
#else
.R
or, lacking a
\fB#else\fR,
the
.B
#endif 
.R
are ignored.
.P
These constructions may be nested.
.nr Hu 1
.H 3 "Line Control"
.P
For the benefit of other preprocessors which generate C programs,
a line of the form
.DS I
\fB#line \fIconstant "filename\fR"
.DE
.P 0
causes the compiler to believe, for purposes of error
diagnostics,
that the line number of the next source line is given by the constant and the current input
file is named by "\fIfilename\fR".
If "\fIfilename\fR" is absent, the remembered file name does not change.
.nr Hu 1
.H 2 "IMPLICIT DECLARATIONS"
.P
It is not always necessary to specify
both the storage class and the type
of identifiers in a declaration.
The storage class is supplied by
the context in external definitions
and in declarations of formal parameters
and structure members.
In a declaration inside a function,
if a storage class but no type
is given, the identifier is assumed
to be
\fBint\fR;
if a type but no storage class is indicated,
the identifier is assumed to
be
.B
auto\fR.
.R
An exception to the latter rule is made for
functions because
.B
auto
.R
functions do not exist.
If the type of an identifier is ``function returning .\|.\|.\|,''
it is implicitly declared to be
.B
extern\fR.
.R
.P
In an expression, an identifier
followed by
.B
(
.R
and not already declared
is contextually
declared to be ``function returning
.B
int\fR.\'\'
.nr Hu 1
.H 2 "TYPES REVISITED"
.P
This part summarizes the operations
which can be performed on objects of certain types.
.nr Hu 1
.H 3 "Structures and Unions"
.P
Structures and unions may be assigned, passed as arguments to functions,
and returned by functions.
Other plausible operators, such as equality comparison
and structure casts,
are not implemented.
.P
In a reference
to a structure or union member, the
name on the right
of the \fB->\fR or the \fB.\fR
must specify a member of the aggregate
named or pointed to by the expression
on the left.
In general, a member of a union may not be inspected
unless the value of the union has been assigned using that same member.
However, one special guarantee is made by the language in order
to simplify the use of unions:
if a union contains several structures that share a common initial sequence
and if the union currently contains one of these structures,
it is permitted to inspect the common initial part of any of
the contained structures.
For example, the following is a legal fragment:
.DS I
\fBunion 
{
        struct 
        {
                int        type;
        } n;
        struct 
        {
                int        type;
                int        intnode;
        } ni;
        struct 
        {
                int        type;
                float      floatnode;
        } nf;
} u;
\&...
u.nf.type = FLOAT;
u.nf.floatnode = 3.14;
\&...
if (u.n.type == FLOAT)
        ... sin(u.nf.floatnode) ...\fR
.DE
.P 0
.nr Hu 1
.H 3 "Functions"
.P
There are only two things that
can be done with a function \*em 
call it or take its address.
If the name of a function appears in an
expression not in the function-name position of a call,
a pointer to the function is generated.
Thus, to pass one function to another, one
might say
.DS I
\fBint f();
\&...
g(f);\fR
.DE
.P 0
.ne 8
Then the definition of
.B
g
.R
might read
.DS I
\fBg(funcp)
        int (*funcp)();
{
        ...
        (*funcp)();
        ...
}\fR
.DE
.P 0
Notice that
.B
f
.R
must be declared
explicitly in the calling routine since its appearance
in
.B
g(f)
.R
was not followed by
.B
(.
.R
.nr Hu 1
.H 3 "Arrays, Pointers, and Subscripting"
.P
Every time an identifier of array type appears
in an expression, it is converted into a pointer
to the first member of the array.
Because of this conversion, arrays are not
lvalues.
By definition, the subscript operator
.B
[]
.R
is interpreted
in such a way that
.B
E1[E2]
.R
is identical to
.B
*((E1)+(E2))\fR.
.R
Because of the conversion rules
which apply to
\fB+\fR,
if
.B
E1
.R
is an array and
.B
E2
.R
an integer,
then
.B
E1[E2]
.R
refers to the
.B
E2 -th
.R
member of
.B
E1\fR.
.R
Therefore,
despite its asymmetric
appearance, subscripting is a commutative operation.
.P
A consistent rule is followed in the case of
multidimensional arrays.
If
.B
E
.R
is an
\fIn\fR-dimensional
array
of rank
i\(muj\(mu...\(muk,
then
.B
E
.R
appearing in an expression is converted to
a pointer to an (n-1)-dimensional
array with rank
j\(mu...\(muk.
If the
.B
*
.R
operator, either explicitly
or implicitly as a result of subscripting,
is applied to this pointer,
the result is the pointed-to (n-1)-dimensional array,
which itself is immediately converted into a pointer.
.P
For example, consider
.DS I
\fBint x[3][5];\fR
.DE
.P 0
Here
.B
x
.R
is a 3\(mu5 array of integers.
When
.B
x
.R
appears in an expression, it is converted
to a pointer to (the first of three) 5-membered arrays of integers.
In the expression
\fBx[i]\fR,
which is equivalent to
\fB*(x+i)\fR,
.B
x
.R
is first converted to a pointer as described;
then
.B
i
.R
is converted to the type of
\fBx\fR,
which involves multiplying
.B
i
.R
by the
length the object to which the pointer points,
namely 5-integer objects.
The results are added and indirection applied to
yield an array (of five integers) which in turn is converted to
a pointer to the first of the integers.
If there is another subscript, the same argument applies
again; this time the result is an integer.
.P
Arrays in C are stored
row-wise (last subscript varies fastest)
and the first subscript in the declaration helps determine
the amount of storage consumed by an array.
Arrays play no other part in subscript calculations.
.nr Hu 1
.H 3 "Explicit Pointer Conversions"
.P
Certain conversions involving pointers are permitted
but have implementation-dependent aspects.
They are all specified by means of an explicit type-conversion
operator, see ``Unary Operators'' under``EXPRESSIONS'' and
``Type Names''under ``DECLARATIONS.''
.P
A pointer may be converted to any of the integral types large
enough to hold it.
Whether an
.B
int
.R
or
.B
long
.R
is required is machine dependent.
The mapping function is also machine dependent but is intended
to be unsurprising to those who know the addressing structure
of the machine.
Details for some particular machines are given below.
.P
An object of integral type may be explicitly converted to a pointer.
The mapping always carries an integer converted from a pointer back to the same pointer
but is otherwise machine dependent.
.P
A pointer to one type may be converted to a pointer to another type.
The resulting pointer may cause addressing exceptions
upon use if
the subject pointer does not refer to an object suitably aligned in storage.
It is guaranteed that
a pointer to an object of a given size may be converted to a pointer to an object
of a smaller size
and back again without change.
.P
For example,
a storage-allocation routine
might accept a size (in bytes)
of an object to allocate, and return a
.B
char
.R
pointer;
it might be used in this way.
.DS I
\fBextern char *alloc();
double *dp;
.sp
dp = (double *) alloc(sizeof(double));
*dp = 22.0 / 7.0;\fR
.DE
.P 0
The
.B
alloc
.R
must ensure (in a machine-dependent way)
that its return value is suitable for conversion to a pointer to
\fBdouble\fR;
then the
.I
use
.R
of the function is portable.
.P
The pointer
representation on the
PDP-11
corresponds to a 16-bit integer and
measures bytes.
The
.B
char\fR's
have no alignment requirements; everything else must have an even address.
.P
On the
VAX-11,
pointers are 32 bits long and measure bytes.
Elementary objects are aligned on a boundary equal to their
length, except that
.B
double
.R
quantities need be aligned only on even 4-byte boundaries.
Aggregates are aligned on the strictest boundary required by
any of their constituents.
.P
The 3B 20 computer has 24-bit pointers placed into 32-bit quantities.
Most objects are
aligned on 4-byte boundaries. \fBShort\fRs are aligned in all cases on
2-byte boundaries. Arrays of characters, all structures,
\fBint\fR\^s, \fBlong\fR\^s, \fBfloat\fR\^s, and \fBdouble\fR\^s are aligned on 4-byte
boundries; but structure members may be packed tighter.
.nr Hu 1
.H 2 "CONSTANT EXPRESSIONS"
.P
In several places C requires expressions that evaluate to
a constant:
after
\fBcase\fR,
as array bounds, and in initializers.
In the first two cases, the expression can
involve only integer constants, character constants,
casts to integral types,
enumeration constants,
and
.B
sizeof
.R
expressions, possibly
connected by the binary operators
.ne 10
.DS I
+ - * / % & | ^ << >> == != < > <= >= && ||
.DE
.P 0
or by the unary operators
.DS I
-  ~
.DE
.P 0
or by the ternary operator
.DS I
?:
.DE
.P 0
Parentheses can be used for grouping
but not for function calls.
.P
More latitude is permitted for initializers;
besides constant expressions as discussed above,
one can also use floating constants
and arbitrary casts and
can also apply the unary
.B
&
.R
operator to external or static objects
and to external or static arrays subscripted
with a constant expression.
The unary
.B
&
.R
can also
be applied implicitly
by appearance of unsubscripted arrays and functions.
The basic rule is that initializers must
evaluate either to a constant or to the address
of a previously declared external or static object plus or minus a constant.
.nr Hu 1
.H 2 "PORTABILITY CONSIDERATIONS"
.P
Certain parts of C are inherently machine dependent.
The following list of potential trouble spots
is not meant to be all-inclusive
but to point out the main ones.
.P
Purely hardware issues like
word size and the properties of floating point arithmetic and integer division
have proven in practice to be not much of a problem.
Other facets of the hardware are reflected
in differing implementations.
Some of these,
particularly sign extension
(converting a negative character into a negative integer)
and the order in which bytes are placed in a word,
are nuisances that must be carefully watched.
Most of the others are only minor problems.
.P
The number of
.B
register
.R
variables that can actually be placed in registers
varies from machine to machine
as does the set of valid types.
Nonetheless, the compilers all do things properly for their own machine;
excess or invalid
.B
register
.R
declarations are ignored.
.P
Some difficulties arise only when
dubious coding practices are used.
It is exceedingly unwise to write programs
that depend
on any of these properties.
.P
The order of evaluation of function arguments
is not specified by the language.
The order in which side effects take place
is also unspecified.
.P
Since character constants are really objects of type
\fBint\fR,
multicharacter character constants may be permitted.
The specific implementation
is very machine dependent
because the order in which characters
are assigned to a word
varies from one machine to another.
.P
Fields are assigned to words and characters to integers right to left
on some machines
and left to right on other machines.
These differences are invisible to isolated programs
that do not indulge in type punning (e.g.,
by converting an
.B
int
.R
pointer to a
.B
char
.R
pointer and inspecting the pointed-to storage)
but must be accounted for when conforming to externally-imposed
storage layouts.
.nr Hu 1
.H 2 "SYNTAX SUMMARY"
.P
This summary of C syntax is intended more for aiding comprehension
than as an exact statement of the language.
.nr Hu 1
.ne 18
.H 3 "Expressions"
.P
The basic expressions are:
.tr ~~
.DS I
\fIexpression:
        primary
        * expression\fR
        &\fIlvalue
        - expression
        ! expression
        ~ expression
        ++ lvalue
        --lvalue
        lvalue ++
        lvalue --
        \fBsizeof\fI expression
        \fBsizeof (\fItype-name\fB)\fI
        ( type-name ) expression
        expression binop expression
        expression ? expression : expression
        lvalue asgnop expression
        expression , expression
.DE
.DS I
\fIprimary:
        identifier
        constant
        string
        ( expression )
        primary ( expression-list\v'0.5'opt\v'-0.5' )
        primary [ expression ]
        primary . identifier
        primary -> identifier
.DE
.DS I
\fIlvalue:
        identifier
        primary [ expression ]
        lvalue . identifier
        primary -> identifier
        * expression
        ( lvalue )\fR
.DE
.P 0
.P
The primary-expression operators
.DS I
()  []  .  ->
.tr ~~
.DE
.P 0
have highest priority and group left to right.
The unary operators
.DS I
*  &  -  !  ~  ++ -- \fBsizeof\fI   ( type-name \fR)
.DE
.P 0
have priority below the primary operators
but higher than any binary operator
and group right to left.
Binary operators
group left to right; they have priority
decreasing
as indicated below.
.DS I
\fIbinop:\fR
        *    /    %
        +    -
        >>   <<
        <    >    <=    >=
        ==   !=
        &
        ^
        |
        &&
        ||
.DE
The conditional operator groups right to left.
.P
Assignment operators all have the same
priority and all group right to left.
.DS I
\fIasgnop:\fR
        =  +=  -=  *=  /=  %=  >>=  <<=  &=  ^=  |=
.DE
.P 0
The comma operator has the lowest priority and groups left to right.
.nr Hu 1
.H 3 "Declarations"
.P
.DS I
\fIdeclaration:
        decl-specifiers init-declarator-list\v'0.5'opt\v'-0.5' ;
.DE
.DS I
\fIdecl-specifiers:
        type-specifier decl-specifiers\v'0.5'opt\v'-0.5'
        sc-specifier decl-specifiers\v'0.5'opt\v'-0.5'
.DE
.DS I
\fIsc-specifier:\fB
        auto
        static
        extern
        register
        typedef
.DE
.DS I
\fItype-specifier:
        struct-or-union-specifier
        typedef-name
        enum-specifier
basic-type-specifier:
        basic-type
        basic-type basic-type-specifiers
basic-type:\fB
        char
        short
        int
        long
        unsigned
        float
        double
        void\fR
.DE
.DS I
\fIenum-specifier:\fB
        enum\fI { enum-list }\fB
        enum \fIidentifier { enum-list }\fB
        enum \fIidentifier
.DE
.DS I
\fIenum-list:
        enumerator
        enum-list , enumerator
.DE
.DS I
\fIenumerator:
        identifier
        identifier = constant-expression
.DE
.DS I
\fIinit-declarator-list:
        init-declarator
        init-declarator , init-declarator-list
.DE
.DS I
\fIinit-declarator:
        declarator initializer\v'0.5'opt\v'-0.5'
.DE
.DS I
\fIdeclarator:
        identifier
        ( declarator )
        * declarator
        declarator ()
        declarator [ constant-expression\v'0.5'opt\v'-0.5' ]
.DE
.DS I
\fIstruct-or-union-specifier:\fB
        struct\fI { struct-decl-list }\fB
        struct \fIidentifier { struct-decl-list }\fB
        struct \fIidentifier\fB
        union { \fIstruct-decl-list }\fB
        union \fIidentifier { struct-decl-list }\fB
        union \fIidentifier
.DE
.DS I
\fIstruct-decl-list:
        struct-declaration
        struct-declaration struct-decl-list
.DE
.DS I
\fIstruct-declaration:
        type-specifier struct-declarator-list ;
.DE
.DS I
\fIstruct-declarator-list:
        struct-declarator
        struct-declarator , struct-declarator-list
.DE
.DS I
\fIstruct-declarator:
        declarator
        declarator : constant-expression
        : constant-expression
.DE
.DS I
\fIinitializer:
        = expression
        = { initializer-list }
        = { initializer-list , }
.DE
.DS I
\fIinitializer-list:
        expression
        initializer-list , initializer-list
        { initializer-list }
        { initializer-list , }
.DE
.DS I
\fItype-name:
        type-specifier abstract-declarator
.DE
.DS I
\fIabstract-declarator:
        empty
        ( abstract-declarator )
        * abstract-declarator
        abstract-declarator ()
        abstract-declarator [ constant-expression\v'0.5'opt\v'-0.5' ]
.DE
.DS I
\fItypedef-name:
        identifier
.nr Hu 1
.DE
.H 3 "Statements"
.P
.DS I
\fIcompound-statement:
        { declaration-list\v'0.5'opt\v'-0.5' statement-list\v'0.5'opt\v'-0.5' }
.DE
.DS I
\fIdeclaration-list:
        declaration
        declaration declaration-list
.DE
.DS I
\fIstatement-list:
        statement
        statement statement-list
.DE
.DS I 
\fIstatement:
        compound-statement
        expression ;
        \fBif\fI ( expression ) statement
        \fBif\fI ( expression ) statement  \fBelse\fI statement
        \fBwhile\fI ( expression ) statement
        \fBdo\fI statement  \fBwhile\fI ( expression ) ;
        \fBfor\fI (exp\v'0.3'opt\v'-0.3'\fB;\fIexp\v'0.3'opt\v'-0.3'\fB;\fIexp\v'0.3'opt\v'-0.3'\fI) statement
        \fBswitch\fI ( expression ) statement
        \fBcase\fI constant-expression :  statement
        \fBdefault\fI : statement
        \fBbreak ;
        continue ;
        return ;
        return\fI expression ;
        \fBgoto\fI identifier ;
        identifier : statement
        ;\fR
.nr Hu 1
.DE
.H 3 "External definitions"
.P
.DS
\fIprogram:
        external-definition
        external-definition program
.DE
.DS
\fIexternal-definition:
        function-definition
        data-definition
.DE
.DS
\fIfunction-definition:
        decl-specifier\v'0.5'opt\v'-0.5' function-declarator function-body
.DE
.DS
\fIfunction-declarator:
        declarator ( parameter-list\v'0.5'opt\v'-0.5' )
.DE
.DS
\fIparameter-list:
        identifier
        identifier , parameter-list
.DE
.DS
\fIfunction-body:
        declaration-list\v'0.5'opt\v'-0.5' compound-statement
.DE
.DS
\fIdata-definition:
        \fBextern\fI declaration\fB ;
        \fBstatic\fI declaration\fB ;
.DE
.H 3 "Preprocessor"
.DS
        \fB#define\fI identifier token-string\v'0.3'opt\v'-0.3'\fB
        \fB#define\fI identifier\fB(\fIidentifier\fB,...)\fItoken-string\v'0.5'opt\v'-0.5'\fB
        \fB#undef\fI identifier\fB
        \fB#include "\fIfilename\|\fB"
        #include <\fIfilename\|\fB>
        \fB#if\fI restricted-constant-expression\fB
        \fB#ifdef\fI identifier\fB
        \fB#ifndef\fI identifier\fB
        \fB#else
        \fB#endif
        \fB#line\fI constant \fB"\fIfilename\|\fB"
.sp 5
.DE
.TC 2 1 3 0
