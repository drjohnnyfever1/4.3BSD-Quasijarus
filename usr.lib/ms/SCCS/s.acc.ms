h37002
s 00018/00002/00078
d D 1.4 04/10/28 02:10:28 msokolov 4 3
c pstroff:	use non-ascii circumflex and tilde
c for those chars that are now in ISO Latin-1, define the strings to the latter
c more work is needed
e
s 00001/00000/00079
d D 1.3 90/06/02 17:47:34 karels 3 2
c reorg; insert keyworks
e
s 00000/00000/00079
d D 1.2 90/06/02 17:35:44 karels 2 1
c version distributed with 4.3BSD, dated Jun 23, 1983
e
s 00079/00000/00000
d D 1.1 90/06/02 17:25:55 karels 1 0
c ancillary file for tmac.s, extracted from there;
c version distributed with 4.2BSD, named "s.*", dated Jun 23, 1983
e
u
U
t
T
I 3
.\" %W% (Berkeley) %G%
E 3
I 1
.	\" AM - accent mark definitions
.bd S B 3
.	\" fudge factors for nroff and troff
.if n \{\
.	ds #H 0
.	ds #V .8m
.	ds #F .3m
.	ds #[ \f1
.	ds #] \fP
.\}
.if t \{\
.	ds #H ((1u-(\\\\n(.fu%2u))*.13m)
.	ds #V .6m
.	ds #F 0
.	ds #[ \&
.	ds #] \&
.\}
.	\" simple accents for nroff and troff
.if n \{\
.	ds ' \h'-1'\'
.	ds ` \h'-1'\`
.	ds ^ \h'-1'^
.	ds , \h'-1',
.	ds ~ \h'-1'~
.	ds ? ?
.	ds ! !
.	ds / \h'-1'\(sl
.	ds q o\h'-1',
.\}
.if t \{\
.	ds ' \\k:\h'-(\\n(.wu*8/10-\*(#H)'\'\h"|\\n:u"
.	ds ` \\k:\h'-(\\n(.wu*8/10-\*(#H)'\`\h'|\\n:u'
D 4
.	ds ^ \\k:\h'-(\\n(.wu*10/11-\*(#H)'^\h'|\\n:u'
E 4
I 4
.	if \n(.C .ds ^ \\k:\h'-(\\n(.wu*10/11-\*(#H)'\X93\h'|\\n:u'
.	el .ds ^ \\k:\h'-(\\n(.wu*10/11-\*(#H)'^\h'|\\n:u'
E 4
.	ds , \\k:\h'-(\\n(.wu*8/10)',\h'|\\n:u'
D 4
.	ds ~ \\k:\h'-(\\n(.wu-\*(#H-.1m)'~\h'|\\n:u'
E 4
I 4
.	if \n(.C .ds ~ \\k:\h'-(\\n(.wu-\*(#H-.1m)'\X94\h'|\\n:u'
.	el .ds ~ \\k:\h'-(\\n(.wu-\*(#H-.1m)'~\h'|\\n:u'
E 4
.	ds ? \s-2c\h'-\w'c'u*7/10'\u\h'\*(#H'\zi\d\s+2\h'\w'c'u*8/10'
.	ds ! \s-2\(or\s+2\h'-\w'\(or'u'\v'-.8m'.\v'.8m'
.	ds / \\k:\h'-(\\n(.wu*8/10-\*(#H)'\z\(sl\h'|\\n:u'
.	ds q o\h'-\w'o'u*8/10'\s-4\v'.4m'\z\(*i\v'-.4m'\s+4\h'\w'o'u*8/10'
.\}
.	\" troff and (daisy-wheel) nroff accents
.ds : \\k:\h'-(\\n(.wu*8/10-\*(#H+.1m+\*(#F)'\v'-\*(#V'\z.\h'.2m+\*(#F'.\h'|\\n:u'\v'\*(#V'
.ds 8 \h'\*(#H'\(*b\h'-\*(#H'
.ds v \\k:\h'-(\\n(.wu*9/10-\*(#H)'\v'-\*(#V'\*(#[\s-4v\s0\v'\*(#V'\h'|\\n:u'\*(#]
.ds _ \\k:\h'-(\\n(.wu*9/10-\*(#H+(\*(#F*2/3))'\v'-.4m'\z\(hy\v'.4m'\h'|\\n:u'
.ds . \\k:\h'-(\\n(.wu*8/10)'\v'\*(#V*4/10'\z.\v'-\*(#V*4/10'\h'|\\n:u'
.ds 3 \*(#[\v'.2m'\s-2\&3\s0\v'-.2m'\*(#]
.ds o \\k:\h'-(\\n(.wu+\w'\(de'u-\*(#H)/2u'\v'-.3n'\*(#[\z\(de\v'.3n'\h'|\\n:u'\*(#]
.ds d- \h'\*(#H'\(pd\h'-\w'~'u'\v'-.25m'\f2\(hy\fP\v'.25m'\h'-\*(#H'
.ds D- D\\k:\h'-\w'D'u'\v'-.11m'\z\(hy\v'.11m'\h'|\\n:u'
.ds th \*(#[\v'.3m'\s+1I\s-1\v'-.3m'\h'-(\w'I'u*2/3)'\s-1o\s+1\*(#]
.ds Th \*(#[\s+2I\s-2\h'-\w'I'u*3/5'\v'-.3m'o\v'.3m'\*(#]
.ds ae a\h'-(\w'a'u*4/10)'e
.ds Ae A\h'-(\w'A'u*4/10)'E
.ds oe o\h'-(\w'o'u*4/10)'e
.ds Oe O\h'-(\w'O'u*4/10)'E
.	\" corrections for vroff
.if v .ds ~ \\k:\h'-(\\n(.wu*9/10-\*(#H)'\s-2\u~\d\s+2\h'|\\n:u'
.if v .ds ^ \\k:\h'-(\\n(.wu*10/11-\*(#H)'\v'-.4m'^\v'.4m'\h'|\\n:u'
.	\" for low resolution devices (crt and lpr)
.if \n(.H>23 .if \n(.V>19 \
\{\
.	ds : \h'-1'"
.	ds 8 B
.	ds v \h'-1'\o'\(aa\(ga'
.	ds _ \h'-1'^
.	ds . \h'-1'.
.	ds 3 3
.	ds o a
.	ds d- d\h'-1'\(ga
.	ds D- D\h'-1'\(hy
.	ds th \o'bp'
.	ds Th \o'LP'
.	ds ae ae
.	ds Ae AE
.	ds oe oe
.	ds Oe OE
I 4
.\}
.	\" some of them are now ISO Latin-1 characters
.if \n(.C \{\
.	ds ! \(!!
.	ds ? \(??
.	ds ae \(ae
.	ds AE \(AE
.	ds oe \(oe
.	ds OE \(OE
.	ds d- \(d-
.	ds D- \(D-
.	ds th \(th
.	ds Th \(TH
.	ds 8 \(ss
E 4
.\}
.rm #[ #] #H #V #F C
E 1
