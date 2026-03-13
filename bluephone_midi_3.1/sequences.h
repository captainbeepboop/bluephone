//sequences
/*
+ = up an octave
- = down an octave
# = sharp
m = minor
d = diminished
5 = 5th
( ) = repeated section
! = end sequence
* = play riff (2 digits)
$ = play single sample (2 digits)
% change bpm (3 digits)
^ adjust bass mode (0)
& change drums (00)
< beep test lap
> adjust mutes (00000) (drums, chord, lead, bass, sample)
? new sequence
b play bass line
*/
const char dammit[] PROGMEM = "02|01 G >00000 %107 2(^1 &07 0(G D Em C) ^2 &01 2(G . D . Em . C .)) ^1 &07 0(G D Em C) >10000 $45 G . D . Em . C . >00000 ^02 $45 G . D . Em . C . $44 G . D . &00 Em . C . C . C . &07 $47 8(G D Em C) 0($45 G D Em C G D Em C)!";

const char idol[] PROGMEM = "04|01 C >00000 ^1 2(&00 C >10000 . . . >00000 Cm >10000 . >00000 Cm Cm &07 0(C . . . Cm . Cm Cm) 4(C . G . Dm . . . )) 4(C . G . Dm . . . ) !";
const char nlatob[] PROGMEM = "01|01 G >00000 0(^2 %176 &07 0(G B C Cm) %132 &06 ^1 G G C Cm &07 ^4 G G C Cm ) !";
const char stepdad[] PROGMEM = "01|01 E >10001 ^2 0(E X C#m X B X A X) 1(A A B C#m A X B X) 1(E B A E E B A A E B C#m A E B E X) 2(E X C#m X B X A X) 1(A A B C#m A X B X) 1(E B A E E B A A E B C#m A E B E X) >10000 4(E X C#m X B X A X) 1(A A B C#m A X B X) >00000 1(E B A E E B A A E B C#m A E B E X) !";
//const char stepdad[] PROGMEM = "01|01 E >10001 ^2 0(E X G# X C#m X A X) A A B C#m A X B X E B A A E B A A E B C#m A E B E X 2(E X G# X C#m X A X) A A B C#m A X B X E B A A E B A A E B C#m A E B E X >10000 4(E X G# X C#m X A X) A A B C#m A X B X >00000 E B A X E B A X E B C#m A E B E X !";
const char mates[] PROGMEM = "08|01 C >10101 &00 ^2 %135 0(Dm  . . . . . . . .  . . . . . . . A . . . . . . . . . . . . . . . )  >00101 b34 E . . . . . . . %130 b34 . . . . . . . . %125 b34 E . . . . . . . %120 b34 &00 . . . . . . . . %115 b34 E . . . . . . . %110 b34 X . . . . . . . %105 b34 E . . . . . . . %100 b34 X . . . . . . . %095 b34 X . . . . . . . %090 >11101 b34 X . . . . . . . %085 b34 X . . . . . . . 2(b33 %115 . . . . . . . . . . . . . . . .) >01101 6(b33 . . . . . . . . . . . . . . . .) &06 8(b33 . . . . . . . . . . . . . . . .) >00101 8(b33 Em . . . . . . . Dm . . . F . . . b33 Em . . . . . . . . . . . . . . . ) >00100 4(b33 Em . . . . . . . Dm . . . F . . . b33 Em . . . . . . . . . . . . . . . ) >01100 &00 2(b33 Em . . . . . . . Dm . . . F . . . b33 Em . . . . . . . . . . . . . . . ) >00100 &06 0(b33 Em . . . . . . . Dm . . . F . . . b33 Em . . . . . . . . . . . . . . . ) !";      
const char deerpark[] PROGMEM = "01|01 C >11111 < . >00000 &15 0(< C . E .  < F . Fm . ) !";

const char turing[] PROGMEM = "01|01 C %110 >10010 ^2 2(X X) >00000 0(*00 E A+)!";
const char slippery[] PROGMEM = "02|01 C >10011 ^1 C X F C F C >00000 F G C X F C F C G C X X 2(1(C X F C F C F G C X F C F C G C) 3(*01 C X F C F C F G C X F C F C G C) X X) 1(1(>10000 C X F C F C F G C X F C F C G C) 0(>00000 *01 C X F C F C F G C X F C F C G C) X X) !";
const char born_to_run[] PROGMEM = "02|01 Am >11111 < . . . . . . >01111 &12 . . >00001 ^1 2(&01 2(*16 < C . . . F . G .) ^2 2(< C . . . F . G .) < F . Em . Dm . Em . C . C A#+ < F . Em . Dm . Em . < C . Am . F . &12 G .) &01 2(*16 < C . . . F . G .) *17 2(< C . . . F . G .) < Am . Am ^1 G C . Gm- . ^2 2(< A# . . . D# . . . < F . . . G#- . &12 . . &01) &01 *18 < C# . C# . G#- . G#- . < C# .  C# . D . D . ^1 >10001 D . . . . . . . G- . . . $16 . $17 . $18 . $19 . >00000 ^2 2( < C . . . F . G .) < F . Em . Dm . Em . C . C A#+ < F . Em . Dm . Em . < C . Am . F . &12 G . &01 0(*16 < C . . . F . G .) !";
const char sandstorm[] PROGMEM = "16|01 Em  >10011 ^2 < . . . . . . . . . . . . . . . . >10100 0(4(*27 < Em . . Em . . Em . Em . . Em . . C . C . . C . . G . G . . G . . D . *27 Em . . Em . . Em . Em . . Em . . Am . Em . . Em . . Em . Em . . Em . . D . ) *27 < Em . . Em . . Em . Em . . Em . . C . *27 Em . . Em . . Em . Em . . Em . . C . *27 Em . . Em . . Em . *27 Em . . Em . . Em . 8(*27 Em . ) 4(*03 < Em . . Em . . Em . Em . . Em . . C . C . . C . . G . G . . G . . D . Em . . Em . . Em . Em . . Em . . Am . Em . . Em . . Em . Em . . Em . . D .)  < 2(*28 Em . . Em . . Em . Em . . Em . . D . ) 4(*28 Em . *29 . .) 8(*28 Em .) )!";
//const char callmemaybe[] PROGMEM = "01|01 G >00001 ^2 0(G Em C D) *02 2( G D C D G D C D) 0(G Em C D) *02 0( G D C D G D C D) 1(G Em C D) 0(*02 G D C D G D C D)!";
const char callmemaybe[] PROGMEM = "16|01 G >00001 &15 ^1 8(X . . . . . . . . . . . . . . . X . . . . . . . . . . . . . . .) 4(&14 G X X X G X X X &15 . . . . . . . . . . . . . . . . . . . . . . . . ) ^2 &02 0(0(G X X X X X X X X X X X X X X X Em X X X X X X X X X X X X X X X C X X X X X X X X X X X X X X X D X X X X X X X X X X X X X X X) *02 2(G X X X X X X X X X X X X X X X D X X X X X X X X X X X X X X X C X X X X X X X X X X X X X X X D X X X X X X X X X X X X X X X G X X X X X X X X X X X X X X X D X X X X X X X X X X X X X X X C X X X X X X X X X X X X X X X D X X X X X X X X X X X X X X X))!";
const char carol[] PROGMEM = "01|01 Em >00001 ^2 0(Em X Em X D X Em X) 2(A G Em Em) 0(Em X Em X D X Em X) 4(A G Em Em) 0(Em X Em X D X Em X) 2(A G Em Em) !";
const char life[] PROGMEM = "01|01 C %140 >11111 ^1 0(*04 C Am F G) !";
const char mushroom[] PROGMEM = "01|01 C >01101 ^0 0(*05 C . . . F . . .) !";
const char yourcall[] PROGMEM = "01|01 Dm >10001 ^1 1(Dm B# E# A#) >00001 1(*41 Dm B# E# A#) 4(Dm B# E# A#) >00000 2(*41 Dm B# E# A#) >00001 4(Dm B# E# A#) &07 ^3 >00000 0(*42 Dm B# E# A#) X";
const char numb[] PROGMEM = "01|01 C >00001 %120 Am Am F C G 0(*06 Am F C G) Am F C G ?10 !";
const char allthethings[] PROGMEM = "02|01 C >00001 0(F Em Am C) 2(Am X G X C X Em X) X X 4(F Em Am C) 2(Am X G X C X Em X) X X 3(F Em Am C) F Em Am C ?13 !";
const char sevennations[] PROGMEM = "02|01 Am >00001 7(A C F E) A C F E ?09 !";
const char sk8rboi[] PROGMEM = "01|01 C >00001 2(C G Am G#-) 2(C G Am G#- C G Am A#) D# A# G#- G D# A# G#- G ?08 !";
const char beautiful[] PROGMEM = "01|01 C >10001 0(G X F X Em X D# X) 2(C X Am X G F C X) Am X ?11 !";
const char ice[] PROGMEM = "04|01 C >10101 %130 0(*08 D X X X X X X G+) !";
const char survive[] PROGMEM = "01|01 Am >10111 ^1 < . 1(< *10 Am Dm G C < F B E E) >00101 0(< b43 *10 Am Dm G C < F B E E) !";
const char runaway[] PROGMEM = "04|01 F >00001 2(*11 F . F . F . F .) 4(F . Gm- A#) Dm . A# . Gm- . C . Dm . A# . Gm- . C A# *12 3(F Gm A# . ) F Gm A# C *11 F . F . F . F . 4(F . Gm- A#) Dm . A# . Gm- . C . Dm . A# . Gm- . C A# *12 3(F Gm A# . ) F Gm A# C *11 F . F . F . F . >10001 Dm . A# . Gm- . C . Dm . A# . Gm- . C A# >00001 *12 3(F Gm A# . ) F Gm A# C 0(*11 F . F . F . F . ) !";
const char catholic[] PROGMEM = "01|01 Cm >00001 ^2 X X X X 0(Cm . Fm Cm Gm Fm Cm . ) ^1 >10001 Cm . . . !";
const char hackers[] PROGMEM = "08|01 Fm >11111 ^2 %156 0(0($24 Fm X X Fm X X Fm X X Fm X X Fm X Fm X $25 Cm X X Cm X X Cm X X Cm X X Cm X Cm X $26 C# X X C# X X C# X X C# X X C# X C# X $27 G# X X G# X X G# X X G# X X G# X Gd X $28 Fm X X Fm X X Fm X X Fm X X Fm X Fm X $29 Cm X X Cm X X Cm X X Cm X X Cm X Cm X $30 C# X X C# X X C# X X C# X X C# X C# X >00000 G# X X G# X X G# X X G# X X G# X Gd X) ^0 >11101 0(*13 $31 C X X X X X X X C X X X X X X X $32 F X X X X X X X C# X X X X X X X $33 D# X X X X X X X G#- X X X G- X X X F- X X X X X X X X X X X X X X X)) !";
const char pendulum[] PROGMEM = "04|01 Am ^2 %190 >00111 0(*14 Am Am Am Am C C C C Am Am Am Am C C C C Am Am Am Am C C C C Em Em Em Em G G G G) !";
const char bopit[] PROGMEM = "02|01 C ^2 %147 >11111 0(0(G X C X G X D X) 0(G D C D)) !";
const char winner[] PROGMEM = "01|01 G ^2 >11111 0(0(*15 G X Em X Am X D X) 0(G X D X Am X D X)) !";
const char careless[] PROGMEM = "01|01 C >01101 %080 0(Am Dm F Em) !";
const char dreams[] PROGMEM = "01|01 C >01101 ^2 %121 0(F X G X) !";
const char pretty[] PROGMEM = "01|01 C >11111 ^2 %120 0(C G Am F) !";
const char time_machine[] PROGMEM = "04|01 Bm ^0 >10001 &00 0(b19 X X X X X X X X X X X X X X X X) &06 2(b19 *19 Bm . . . A+ . . . Bm . . G A+ . . .) 6(0(>00101 b19 Bm X X X X X X X X X X X X X X X) 0(b19 *19 >00001 Bm . . . A+ . . . Bm . . G A+ . . .)) b26 *26 X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X 0(b19 *19 Bm . . . A+ . . . Bm . . G A+ . . .) b19 *19 Bm . . . A+ . . . Bm . . G &00 A+ >10001 . . . . . . . . . . . . . . . . . . . . . . !";
const char staying_alive[] PROGMEM = "08|01 Cm : >01111 0(^0 *20 Fm . . . . . . . Fm . . . . . . . ) 2(^1 *21 A# . . . . . . .) 2(&06 ^0 *20 Fm . . . . . . . . . . . . . . . ^1 2(*20 Fm . . . . . . . D#- . . . . . . .) ^2 4(*21 A# . . . . . . .) &02 *22 4(Fm . . . . . . .) 2(Fm X Fm X Fm X Fm X Fm . . . . . . .) &06 D# . . . . . . . Fm . . . . . . . Cm . . . . . . . ^0 *20 Fm . . . . . . . Fm . . . . . . . ) ^1 &02 G#- . . . . . . . G#- . . . . . . . A# . . . . . . . *20 &06 ^0 Fm . . . . . . . Fm . . . . . . . ^1 &02 A# . . . . . . . A# . . . . . . . 2(*20 &06 ^0 Fm . . . . . . . Fm . . . . . . .) ^1 2(*20 Fm . . . . . . . D#- . . . . . . .) ^2 4(*21 A# . . . . . . .) &02 *22 4(Fm . . . . . . .) 2(Fm X Fm X Fm X Fm X Fm . . . . . . .) &06 D# . . . . . . . Fm . . . . . . . Cm . . . . . . . ^0 *20 Fm . . . . . . . Fm . . . . . . . 0(^1 &02 G#- . . . . . . . G#- . . . . . . . A# . . . . . . . *20 &06 ^0 Fm . . . . . . . Fm . . . . . . . ^1 &02 A# . . . . . . . A# . . . &12 . . . . *20 &06 ^0 Fm . . . . . . . Fm . . . . . . .) !";
const char solidarity[] PROGMEM = "02|01 C >00001 ^2 *24 G . G . C . G D G . B Em Am D G . 0(&02 G . G . C . G D G . B Em Am D G . *24 G . G . C . G D G . B Em Am D G .) !";
const char thunderstruck[] PROGMEM = "16|01 B >00000 &15 ^1 8(X . . . . . . . . . . . . . . . X . . . . . . . . . . . . . . .) 4(*25 X . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .) 8(*25 &14 Bf X X X Bf X X X &15 . . . . . . . . . . . . . . . . . . . . . . . .) ^2 &02 4(*25 Bf . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . *25 Bf . . . . . . . . . . . . . . . &14 ^1 Bf . . . Bf . . . &02 ^2 . . . . . . . .) ^1 4(Bf . . . . . . . Af Ef- . . . . . . . . Af . . . Af . Ef- . . . . . . . ) &13 Ef- . . . . . . . . . . . . . . . &12 4(X . . .) ^2 &02 4(*25 Bf . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .) 4(*25 Bf . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . *25 Bf . . . . . . . . . . . . . . . &14 ^1 Bf . . . Bf . . . &02 ^2 . . . . . . . .) ^1 3(Bf . . . Af . . . Ef- . . . X . . . X . . . X . . . X . . . Af . . .) Bf . . . Af . . . Ef- . . . &00 X . . . &13 X . . . X . . . X . . . &12 X . . . &02 ^2 4(*25 Bf . . . . . Af . . . . . Df- . Ef- . Af . . . . . Ef- . . . . . . . . .) 8(*25 X . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .) 3(*25 &14 Bf X X X Bf X X X &15 . . . . . . . . . . . . . . . . . . . . . . . .) *25 &14 Bf X X X Bf X X X &15 . . . . . . . . . . . . &12 . . . . . . . . . . . . &2 4(*25 Bf . . . . . Af . . . . . Df- . Ef- . Af . . . . . Ef- . . . . . . . . .) >10000 ^1 Bf . . . . . . . . . . . . . . . . !";
const char treatmegood[] PROGMEM = "01|01 C#m >00000 0(A F#m E Bm) *30 2(C#m F#m Bm E) 2(A F#m E Bm) *30 2(C#m F#m Bm E) D G F#m E D G F# G 2(F#m C#m G D) *30 2(A F#m E Bm) 2(C#m F#m Bm E) 4(Em Am Dm G) !";
const char orange[] PROGMEM = "08|01 F#m >00001 3(0(b31 C#f- C#f- X X C#f- C#f- X X C#f- C#f- X X C#f- C#f- X X C#f- C#f- X X C#f- C#f- X X C#f- C#f- X X C#f- C#f- X X C#f- C#f- X X C#f- C#f- X X C#f- C#f- X X C#f- C#f- X X C#f- C#f- X X C#f- C#f- X X C#f- C#f- X X C#f- C#f- X X D D X X D D X X D D X X D D X X D D X X D D X X D D X X D D X X D D X X D D X X D D X X D D X X D D X X D D X X D D X X D D X X ) 4(>00001 *32 b32 C#f C#f C#f C#f C#f C#f C#f C#f C#f C#f C#f C#f C#f C#f C#f C#f C#f C#f C#f C#f C#f C#f C#f C#f C#f C#f C#f C#f C#f C#f C#f C#f >00101 Df Df Df Df Df Df Df Df Df Df Df Df Df Df Df Df Df Df Df Df Df Df Df Df Df Df Df Df Df Df Df Df)) b31 C#f- C#f- X X C#f- C#f- X X C#f- C#f- X X C#f- C#f- X X C#f- >11111 !";
const char love[] PROGMEM = "08|01 C >11101 2(b33 . . . . . . . . . . . . . . . .) >01101 6(b33 . . . . . . . . . . . . . . . .) &06 8(b33 . . . . . . . . . . . . . . . .) >00101 8(b33 Em . . . . . . . Dm . . . F . . . b33 Em . . . . . . . . . . . . . . . ) >00100 4(b33 Em . . . . . . . Dm . . . F . . . b33 Em . . . . . . . . . . . . . . . ) >01100 &00 2(b33 Em . . . . . . . Dm . . . F . . . b33 Em . . . . . . . . . . . . . . . ) >00100 &06 0(b33 Em . . . . . . . Dm . . . F . . . b33 Em . . . . . . . . . . . . . . . ) !";
const char scifi[] PROGMEM = "08|01 A 2(>00001 &16 0($09 b39  A . . . . . . D A . . . . . . D) ^2 $09 E . . . . . . . $09 E . . . . . . . $09 E . . . . . . . $09 2(*38 b40 D . . . . . . . *38 E . . . . . . . *38 C#m . . . . . . . *38 D . . . . . . . )) &00 0(^2 D . D . D . D . E . E . E . E . C#m . C#m . C#m . C#m . D . D . D . D . &01) &16 $09 2(*38 b40 D . . . . . . . *38 E . . . . . . . *38 C#m . . . . . . . *38 D . . . . . . . ) ^1 &00 D >10001 . . . . . . . !";

uint8_t number_of_sequences = 39;
const char *sequence_pointers[] = {&turing[0], &slippery[0], &callmemaybe[0], &sandstorm[0], &carol[0], &mushroom[0], &life[0], &yourcall[0], &numb[0], &allthethings[0], &sevennations[0], &sk8rboi[0], &beautiful[0], &ice[0], &stepdad[0], &survive[0], &runaway[0], &catholic[0], &hackers[0], &pendulum[0], &bopit[0], &winner[0], &careless[0], &dreams[0], &pretty[0], &born_to_run[0], &time_machine[0], &staying_alive[0], &solidarity[0], &thunderstruck[0], &treatmegood[0], &orange[0], &love[0], &scifi[0], &mates[0], &dammit[0], &nlatob[0], &idol[0], &deerpark[0]};


//00 - turing - 110-00-3*-2
//01 - slippery -080-01-21-0
//02 - call me maybe -130-02-96-0
//03 - sand storm beep test - 090-03-26-0
//04 - carol -140-04-92-0
//05 - mushroom - 120-05-52-0
//06 - life is mysterous -140-06-60-1
//07 - your call is important - 080-07-#7-0
//08 - numb - FIGURE OUT RIFF
//09 - all the things
//0* - seven nations army - KEY IN RIFF THEN PLAY HIGHER
//0# - sk8r boi - 140 - FIGURE OUT RIFF
//10 - beautiful - 140
//11 - ice - KEY IN RIFF
//12 - stepdad
//13 - survive 120-13-16-0
//14 - runaway - 050-14-*#-0
//15 - catholi0c boys school 090-15-70-0
//16 - hacker 156-16-12-0
//17 - pendulum 190-17-07-0
//18 - bop_it 147-18-02-5
//19 - the winner takes it all 125-19-92-0
//1* - careless whisper - 080-1*-21-0 - The riff is 7,6,3,1 (x 2) 5, 4, 1 (x 2) 4, 3, 1, 6, 4 / 3, 4, 5, 6, 7, 1, 2, 3
//1# - dreams - 120 - 10 - 12 - 0   
//20 - pretty enough - 120-20-51-0  1...5653 1...5432 8...785 1...5434 4323 321
//21 - born to run 140-21-12-0
//22 - time machine - 140-22-63-4
//23 - staying alive - 140-23-62-0
//24 - solidarity 4ever 160-24-27-0&00
//25 - thunderstruck 120-25-00-0
//26 - treat me good - 090-26-21-0
//27 - orange - 200-27-12-8
//28 - love - 115-28-06-7
//29 sci-fi 120-29-00-9
// ELMO - 170-10-4*-0

//12 - stepdad - 140-12-12-0
//2* - mates - 115-2*-06-0
//2# - dammit 100-2#-76-0
//30 - nlatob 176-30-12-0
//31 - idol 125-31-12-0
//32 - deer park test 120-32-79-0


// - mushroom
// - plan B
// - miracle of modern science


//riffs
const char born_to_run_riff[] PROGMEM = "08|01 C . . . . . . . . . E F . . E . A . . . . . . . C . . . D . . . !";
const char born_to_run_riff_2[] PROGMEM = "16|01 G . G . G . G G A+ . G . G . G G E . G . G . G G D . C . C . G G E . G . G . G G A+ . G . A+ . G . . . C+ . . . A+ . G . G . A+ . G . G . C+ . . . C+ . A+ . G . A+ . G . G D C . D C A . C . . . A . . . A . A G- A . C A C . D C D . E D E . G E G . A+ G A+ . . . B+ . . . C+ . . . . . . . . . . . . . . .  !";
const char born_to_run_riff_3[] PROGMEM = "08|01 F# . . F . . . F F# . . F . . D# C# D# . . . . . G# G# D# . G# D# . . . . F# . . F . . . F F# . . F . . C# F G . . F# . . . F# G . . F# . . D . G . . F# . . F . . E . . D# . D . C# C . B . A# . A . G#- . G#- . G#- . G#- G- . . . . . . . !";

const char time_machine_riff[] PROGMEM = "08|01 B . . F# . D G . A+ . . D . . C# . B . . G . D G . A+ . . . . . . . !";

const char sandstorm_riff[] PROGMEM = "16|01 B B B B B . B B B B B B B . E E E E E E E . D D D D D D D . A A B B B B B . B B B B B B B . E E B B B B B . B B B B B B B . E E !";
const char sandstorm_riff_a[] PROGMEM = "16|01 B B B B B  !";
const char sandstorm_riff_b[] PROGMEM = "16|01 B B B B B . B B B B B . D . D . !";
const char sandstorm_riff_c[] PROGMEM = "16|01 D . D . !";
const char callmemaybe_riff[] PROGMEM = "08|01 . . D . A B D A . . . A A B F# D . . . D F# G+ F# D . . . D F# E E D . .  D . A B D B . . . . A B F# F# . D . D F# G+ F# D . . . D F# E E D !";
const char turing_riff[] PROGMEM = "16|01 E X X F X X G X E X X F X X G X E X X F X X G X E X X D X X C X !";
const char slippery_riff[] PROGMEM = "08|01 C C C C C C C C F F F F C C C C F F F F C C C C F F F F G G G G C C C C C C C C F F F F C C C C F F F F C C C C G G G G C C C C X X X X X X X X !";
const char life_riff[] PROGMEM = "08|01 C X E G X X X C+ B+ X G E X X X X F X A X C+ X A X G X B X D+ X X X X";
const char mushroom_riff[] PROGMEM = "04|01 C E G E C E G E C E G E C E G E F A C A F A C A F A C A F A C A !";
const char numb_riff[] PROGMEM = "08|01 A X X C X X B X X X X X X E- G- E- C X X B X X G- X X X X X X E- G- E- !";
const char sevennations_riff[] PROGMEM = "24|01 5 X X X X X X X X 5 X X 7 X X X 5 X X X 4 X X X 3 X X X X X X X X X X X 2 X X X X X X X X X X X 5 X X X X X X X X 5 X X 7 X X X 5 X X X 4 X X X 3 X X X 4 X X X 3 X X X 2 X X X X X X X X X X X !";
const char ice_riff[] PROGMEM = "16|01 D X D X D X D D D X A X X X X X D X D X D X D D D X A X X X X X !";
const char stepdad_riff[] PROGMEM = "01|01 A A B C#m A X B X E B A . E B A . E B C#m A E B E- X !";
const char survive_riff[] PROGMEM = "16|01 D+ . . . C+ . . . C+ . A+ . C+ . G+ . F+ . . . . . E+ . D+ E+ C+ . B+ C+ A+ . G . . . . . . . . . G+ . . . E+ F+ E+ . D+ E+ D+ . C+ D+ C+ . B+ C+ B+ . A+ B+ A+ . . . . . . . E+ . . . F+ . . . D+ C+ B+ A+ G F E D C B A G- F- E- . D- E . . . . . . . . . . . . . . . !";
const char runaway_riff[] PROGMEM = "24|01 A . C C C A A# A G- F- . . F- . . E- F- . . E- F- E- F- G- A . C . . A A# A G- F- . . . . . . D . C . . C A# A !";
const char runaway_chorus[] PROGMEM = "24|01 C . . . . A A# A . G- . F- . . . X X F- A# . A G- . . F- . G- F- . G- F- . . . . . . . . X X X F- E- D- C- . . . . C . . A A# A . G- . F- . . . X X F- A# A . G- . F- . . A  . . . G- . F- . E- F- . . . . . X E- . . . . .   !";
const char hacker_chorus[] PROGMEM = "04|01 C . . G- C . . D# F . . . C# . . . D# . . F- G#- . G- . F- . . . . . . . !";
const char pendulum_riff[] PROGMEM = "08|01 A C A C A C A C E- A E- A E- A E- A A C A C A C A C E- A E- A E- A E- A A C A C A C A C E- A E- A E- A E- A C E C E C E C E E G E G E G E G !";
const char winner_riff[] PROGMEM = "08|01 G- D C+ D G- B+ D G- A+ D G- G D#- E F# D#- E- B A+ B E- G B E- F# B E- E G#- B D G#- A E D+ E A C+ E A B+ C A A+ C A E A D- A G A D- F# A D E A D- D X F#- A X !";
const char staying_alive_riff_1[] PROGMEM = "16|01 D F X G X X D X X X C X A C D X A C X D X D A X C X D X F X G X !";
const char staying_alive_riff_2[] PROGMEM = "16|01 X X X X X X X G# X G# X F G# . F X !";
const char staying_alive_chorus[] PROGMEM = "16|01 C C C C C A# A# A# A# G#- G#- G#- G#- G- G- G- G- G#- G#- G#- X X X X G- G#- G#- G#- X X X X C C C C C A# A# A# A# G#- G#- G#- G#- G- G- G- G- G#- G#- G#- X X X X G- G#- G#- G#- X X X X C X X X A# X X X G#- X X X G- X X X G- G#- G#- G#- X X X X G- G#- G#- G#- X X X X C X X X A# X X X G#- X X X G- X X X G#- G#- G#- C . . . . . . . . . . . . A# . . . . . . . . . . . . . C A# G#- . . . . . . . . . . . . . . . G- . . . . . . . . . C . . !";
const char solidarity_verse[] PROGMEM = "08|01 D D D C B D G A+ B+ B+ B+ A+ G X G F E E E F G F G E D E D B D X D D D D D C B D G A+ B+ B+ B+ A+ G X G X A+ X A+ X G X X X G X X X !";
const char solidarity_chorus[] PROGMEM = "08|01 D . . C B D G A+ B+ . . . G . . . E . . F G F G E D . . . B . . . D . . C B D G A+ B+ . . . G . G . A+ . A+ . G . . . G . . . . . . . !";
const char thunderstruck_riff[] PROGMEM = "16|01 B+ B A+ B G# B A+ B G# B F# B G# B E B F# B D# B E B D# B E B D# B E B D# B !";
const char happy_birthday[] PROGMEM = "08|01 X . . . . . F# F# G# . . F# . . B+ . A#+ . . . . . F# F# G# . . F# . . C#+ . B+ . . . . . F# F# F#+ . . D+# . . B+ . A#+ . G# . . . E E D# . . B+ . . C#+ .f !";
const char treatmegood_riff[] PROGMEM = "16|01 E X X E X X E X X X X X X X B A B X X C# X X C# X X X X X X X X X E X E X E X F# X X X B X X X A X A X B X C# X A X B X A X B X C# X E X X E X X E X X X X X X X B A B X X C# X X B X X X A X X X X X X X X X B X C# . . . . X B X A X B X A X B . . . X X X X X X X X !"; //
const char orange_verse[] PROGMEM = "08|01 C#- C#- X C#- C#- C#- X C#- C#- C#- X C#- C#- C#- X C#- C#- C#- X C#- C#- C#- X C#- C#- C#- X C#- C#- C#- X C#- C#- C#- X C#- C#- C#- X C#- C#- C#- X C#- C#- C#- X C#- C#- C#- X C#- C#- C#- X C#- C#- C#- X C#- C#- C#- X C#- D D X D D D X D D D X D D D X D D D X D D D X D D D X D D D X D D D X D D D D X F# A C# C#- E G# E F# D D X D D D D X F# A C# C#- E G# E F# !"; //FFED for little care
const char orange_chorus[] PROGMEM = "08|01 C# X G# G# C# X G# X C# X G# G# C# X G# X C# C# G# X C# X G# X C# C# G# X C# X F# X D D X D D D D X F# A C# C#- E G# E F# D D X D D D D X F# A C# C#- E G# E F# !";
const char toggles_riff_a[] PROGMEM = "16|01 E- X X E- X X E- X X E- X X E- X X E- X X E- X X E- X X E- X X E- X X F- X !";
const char toggles_riff_b[] PROGMEM = "16|01 E- X E- X E- X E- X E- X E- X E- X E- X!";
const char toggles_riff_c[] PROGMEM = "16|01 F F F F F F F F F F F F F F F X F F F F F F F F F F F F F F F X !";
const char toggles_lead_a[] PROGMEM = "16|01 D X X E X X E X D X X E X X E X D X X E X X E X D X X E X X F X !";
const char toggles_lead_b[] PROGMEM = "16|01 F X X F X X F X F X X F X X F X F F X F F X F X F F X F F X F X !";
const char sci_fi_lead[] PROGMEM = "04|01 D A+ G# D !";
const char sci_fi_note[] PROGMEM = "08|01 A A X A+ X E X C# A A X A+ X E X A+ !";
const char sci_fi_bass[] PROGMEM = "08|01 D A+ D A+ D A+ D A+ E B+ E B+ E B+ E B+ C# G# C# G# C# G# C# G# D A+ D A+ D A+ D A+ !";
const char your_call_riff[] PROGMEM = "12|01 X X X D- E- F- G- . . . . . . X X D- E- F- G- . A A# . . C . . A# . A G- . . E#- . . A# . . . . . . . . . . . !";
const char your_call_riff_straight[] PROGMEM = "16|01 X X X X D- E- F- X G- . . . . . . . X X X X D- E- F- X G- . . A A# . . . C . . . A# . A . G . . . E#- . . . A# . . . . . . . . . . . . . . . !";
const char survive_bass[] PROGMEM = "16|01 A X A X X A X X A X X X X X C X D X D X X D X X D X E X F X F# X G X G X X G X X G- X G- X X X G- X C X C X X C X X C X X X X X C X F- X F- X X F- X X F- X X X X X F- X B X B X X B X X B X X X X X B X E- X E- X X E- X X E- X X X X X B X E X E X X B X X E- X X E- E X E- X !";





uint8_t number_of_riffs = 44;
const char *riff_pointers[] = {&turing_riff[0], &slippery_riff[0], &callmemaybe_riff[0], &sandstorm_riff[0], &life_riff[0], &mushroom_riff[0], &numb_riff[0], &sevennations_riff[0], &ice_riff[0], &stepdad_riff[0], &survive_riff[0], &runaway_riff[0], &runaway_chorus[0], &hacker_chorus[0], &pendulum_riff[0], &winner_riff[0], &born_to_run_riff[0], &born_to_run_riff_2[0], &born_to_run_riff_3[0], &time_machine_riff[0], &staying_alive_riff_1[0], &staying_alive_riff_2[0], &staying_alive_chorus[0], &solidarity_verse[0], &solidarity_chorus[0], &thunderstruck_riff[0], &happy_birthday[0], &sandstorm_riff_a[0], &sandstorm_riff_b[0], &sandstorm_riff_c[0], &treatmegood_riff[0], &orange_verse[0], &orange_chorus[0], &toggles_riff_a[0], &toggles_riff_b[0], &toggles_riff_c[0], &toggles_lead_a[0], &toggles_lead_b[0], &sci_fi_lead[0], &sci_fi_note[0], &sci_fi_bass[0],&your_call_riff[0],&your_call_riff_straight[0],&survive_bass[0]};
//00 - turing
//01 - slippery
//02 - call me maybe
//03 - sand storm beep test
//04 - life is mysterous
//05 - mushroom
//06 - numb
//07 - seven nations army
//08 - ice, ice, baby
//09 - stepdad
//10 - survive
//11 - runaway
//12 - runaway chorus
//13 - hacker chorus
//14 - pendulum riff
//15 - winner riff
//16 - born to run main riff
//17 - born to run 2
//18 - born to run 3
//19 - time machine riff
//20 - staying alive riff 1
//21 - staying alive riff 2
//22 - staying alive chorus
//23 - solidarity verse
//24 - solidarity chorus
//25 - thunderstruck riff
//26 birthday
//27 sandstorm a
//28 sandstorm b
//29 sandstorm c
//30 treatmegood
//31 orange verse
//32 orange chorus
//33 toggle a
//34 toggle b
//35 toggle c
//36 toggles lead a
//37 toggles lead b
//38 scifi lead
//39 scifi note
//40 scifi bass
//41 your call bass

//drums
uint8_t number_of_drums = 17;


const char beat_0[] PROGMEM = "16|----------------|----------------|O---O---O---O---"; //0 - FOUR BASS
const char beat_1[] PROGMEM = "16|x-x-x-x-x-x-x-x-|----O--o----O---|O-------O-o---o-"; //1 - ROCK BEAT
const char beat_2[] PROGMEM = "16|xxxxxxxxxxxxxxxx|----O-------O---|O---O---O---O---"; //2 - DISCO BEAT
const char beat_3[] PROGMEM = "16|x-xxx-x-x-xxx-x-|----O-------O---|Oo-o----Oo-o----"; //3 - TURING BEAT
const char beat_4[] PROGMEM = "16|x-x-x-x-x-x-x-x-|----O--O----O---|O---------o---o-"; //4 - SURF ROCK
const char beat_5[] PROGMEM = "16|----------------|------------O---|O-----O-O-------"; //5 -BE MY BABY
const char beat_6[] PROGMEM = "16|--x---x---x---x-|----O-------O---|O---O---O---O---"; //6 - FOUR TO THE FLOOR
const char beat_7[] PROGMEM = "16|X-X-X-X-X-X-X-X-|--O---O---O---O-|O--o-o--O--o-o--"; //7 - PUNK BEAT
const char beat_8[] PROGMEM = "16|X-X-X-X-X-X-X-X-|----O-------O---|O-oo-o-oO-oo-o-o"; //8 - IMMIGRANT SONG
const char beat_9[] PROGMEM = "16|x-x-x-x-x-x-x-x-|----O-------O---|O-------O-------"; //9 - BASIC
const char beat_star[] PROGMEM = "24|x-xxx-x-x-x-xxx-x-xxx-x-|------O-----------O-----|O-----------Oo-o------"; //* - WALTZ
const char beat_hash[] PROGMEM = "24|x-x-x-x-x-x-x-x-x-x-x-x-|------O------o-o--O-----|Oo-o--------O-o-----o-"; //# - MORE WALTZ
const char snare_fill[] PROGMEM = "16|----------------|xxxxxxxxxxxxxxxx|O---O---O---O---";
const char kick_fill[] PROGMEM = "16|----------------|----------------|OoooOoooOoooOoo-";
const char thunder[] PROGMEM = "16|X---X-----------|X---X-----------|X---X-----------";
const char allhats[] PROGMEM = "16|XxxxXxxxXxxxXxxx|----------------|X---X---X---X ---";
const char scifi_beat[] PROGMEM = "16|xXxXxXxXxXxXxXxX|--O---O---O---O-|Oo--O---Oo--Oo--";


const char *drumbeat_pointers[] = {&beat_0[0], &beat_1[0], &beat_2[0], &beat_3[0], &beat_4[0], &beat_5[0], &beat_6[0], &beat_7[0], &beat_8[0], &beat_9[0], &beat_star[0], &beat_hash[0], &snare_fill[0], &kick_fill[0], &thunder[0], &allhats[0], &scifi_beat[0]};


uint16_t sample_lengths[] = {
192, //1 - life
96, // 2 - turing
384, // 3 - modem
0, // 4 - wash
192, // 5 bopit
96, // 6 
96, // 7 - love
0, // 8 - monkeys
96, // 9 what is the point?
0,
};
