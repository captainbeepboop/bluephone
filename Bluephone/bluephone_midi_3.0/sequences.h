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

*/

const char turing[] PROGMEM = "01|01 E %110 >10000 2(X X) >00000 0(*00 E A+) !";
const char slippery[] PROGMEM = "02|01 C >10011 C X F C F C >00000 F G C X F C F C G C X X 0(1(C X F C F C F G C X F C F C G C) 3(*01 C X F C F C F G C X F C F C G C) X X) !";
const char born_to_run[] PROGMEM = "02|01 C >00001 2(0(*00 C . . . F X G X) F X C X Dm X C X C X C A#+ F X C X Dm X C X C X Am X F X G X) 2(A# X A# X D# X D# X F X F X G X G X ) !";
const char sandstorm[] PROGMEM = "16|01 Em  >10011 < . . . . . . . . . . . . . . . . >10100 0(< *03 Em . . Em . . Em . Em . . Em . . C . C . . C . . G . G . . G . . D . Em . . Em . . Em . Em . . Em . . Am . Em . . Em . . Em . Em . . Em . . D .)!";
const char callmemaybe[] PROGMEM = "01|01 G >00001 0(G Em C D) *02 2( G D C D G D C D) 0(G Em C D) *02 0( G D C D G D C D) 1(G Em C D) 0(*02 G D C D G D C D)!";
const char carol[] PROGMEM = "01|01 Em >00001 0(Em X Em X D X Em X) 2(A G Em Em) 0(Em X Em X D X Em X) 4(A G Em Em) 0(Em X Em X D X Em X) 2(A G Em Em) !";
const char life[] PROGMEM = "01|01 C %140 >11110 0(*04 C Am F G) !";
const char mushroom[] PROGMEM = "01|01 C >01101 0(*05 C . . . F . . .) !";
const char yourcall[] PROGMEM = "01|01 Cm >10001 0(Cm A# D# G#) X";
const char stepdad[] PROGMEM = "01|01 E >10000 0(E X G# X C#m X A X) A A B C#m A X B X E B A A E B A A E B C#m A E B E X 2(E X G# X C#m X A X) A A B C#m A X B X E B A A E B A A E B C#m A E B E X >10000 4(E X G# X C#m X A X) A A B C#m A X B X >00000 E B A X E B A X E B C#m A E B E X !";
const char numb[] PROGMEM = "01|01 C >00000 %120 Am Am F C G 0(*06 Am F C G) Am F C G ?10 !";
const char allthethings[] PROGMEM = "02|01 C >00000 0(F Em Am C) 2(Am X G X C X Em X) X X 4(F Em Am C) 2(Am X G X C X Em X) X X 3(F Em Am C) F Em Am C ?13 !";
const char sevennations[] PROGMEM = "02|01 Am >00000 7(A C F E) A C F E ?09 !";
const char sk8rboi[] PROGMEM = "01|01 C >00000 2(C G Am G#-) 2(C G Am G#- C G Am A#) D# A# G#- G D# A# G#- G ?08 !";
const char beautiful[] PROGMEM = "01|01 C >10000 0(G X F X Em X D# X) 2(C X Am X G F C X) Am X ?11 !";
const char ice[] PROGMEM = "04|01 C >10100 %130 0(*08 D X X X X X X G+) !";
const char survive[] PROGMEM = "01|01 Am >10110 < . 0(< *10 Am Dm G C < F B E E) !";
const char runaway[] PROGMEM = "04|01 F >00001 2(*11 F . F . F . F .) 4(F . Gm- A#) Dm . A# . Gm- . C . Dm . A# . Gm- . C A# *12 3(F Gm A# . ) F Gm A# C *11 F . F . F . F . 4(F . Gm- A#) Dm . A# . Gm- . C . Dm . A# . Gm- . C A# *12 3(F Gm A# . ) F Gm A# C *11 F . F . F . F . >10001 Dm . A# . Gm- . C . Dm . A# . Gm- . C A# >00001 *12 3(F Gm A# . ) F Gm A# C 0(*11 F . F . F . F . ) !";
const char catholic[] PROGMEM = "01|01 Cm >00000 X X X X 0(Cm . Fm Cm Gm Fm Cm . ) !";

uint8_t number_of_sequences = 18;
const char *sequence_pointers[] = {&turing[0], &slippery[0], &callmemaybe[0], &sandstorm[0], &carol[0], &mushroom[0], &life[0], &yourcall[0], &numb[0], &allthethings[0], &sevennations[0], &sk8rboi[0], &beautiful[0], &ice[0], &stepdad[0], &survive[0], &runaway[0], &catholic[0]};

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
//15 - catholic boys school 090-15-70-0
// ELMO - 170-10-4*-0

// - mushroom
// - plan B
// - miracle of modern science

//riffs
const char born_to_run_riff[] PROGMEM = "08|01 C . . . . . . . . . E F . . E . A . . . . . . . C . . . D . . . !";
const char sandstorm_riff[] PROGMEM = "16|01 B B B B B . B B B B B B B . E E E E E E E . D D D D D D D . A A B B B B B . B B B B B B B . E E B B B B B . B B B B B B B . E E !";
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


uint8_t number_of_riffs = 13;
const char *riff_pointers[] = {&turing_riff[0], &slippery_riff[0], &callmemaybe_riff[0], &sandstorm_riff[0], &life_riff[0], &mushroom_riff[0], &numb_riff[0], &sevennations_riff[0], &ice_riff[0], &stepdad_riff[0], &survive_riff[0], &runaway_riff[0], &runaway_chorus[0]};
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


//drums
uint8_t number_of_drums = 12;

const char beat_0[] PROGMEM = "16|----------------|----------------|O---O---O---O---"; //0 - FOUR BASS
const char beat_1[] PROGMEM = "16|x-x-x-x-x-x-x-x-|----O--o----O---|O-------O-o---o-"; //1 - ROCK BEAT
const char beat_2[] PROGMEM = "16|xxxxxxxxxxxxxxxx|----O-------O---|O-------Oo------"; //2 - DISCO BEAT
const char beat_3[] PROGMEM = "16|x-xxx-x-x-xxx-x-|----O-------O---|Oo-o----Oo-o----"; //3 - TURING BEAT
const char beat_4[] PROGMEM = "16|x-x-x-x-x-x-x-x-|----O--O----O---|O---------o---o-"; //4 - SURF ROCK
const char beat_5[] PROGMEM = "16|----------------|------------O---|O-----O-O-------"; //5 -BE MY BABY
const char beat_6[] PROGMEM = "16|--x---x---x---x-|----O-------O---|O---O---O---O---"; //6 - FOUR TO THE FLOOR
const char beat_7[] PROGMEM = "16|X-X-X-X-X-X-X-X-|--O---O---O---O-|O--o-o--O--o-o--"; //7 - PUNK BEAT
const char beat_8[] PROGMEM = "16|X-X-X-X-X-X-X-X-|----O-------O---|O-oo-o-oO-oo-o-o"; //8 - IMMIGRANT SONG
const char beat_9[] PROGMEM = "16|x-x-x-x-x-x-x-x-|----O-------O---|O-------O-------"; //9 - BASIC
const char beat_star[] PROGMEM = "24|x-xxx-x-x-x-xxx-x-xxx-x-|------O-----------O-----|O-----------Oo-o------"; //* - WALTZ
const char beat_hash[] PROGMEM = "24|x-x-x-x-x-x-x-x-x-x-x-x-|------O------o-o--O-----|Oo-o--------O-o-----o-"; //# - MORE WALTZ

const char *drumbeat_pointers[] = {&beat_0[0], &beat_1[0], &beat_2[0], &beat_3[0], &beat_4[0], &beat_5[0], &beat_6[0], &beat_7[0], &beat_8[0], &beat_9[0], &beat_star[0], &beat_hash[0]};

uint8_t sample_lengths[] = {
192, //1 - life
96, // 2 - turing
0,
0,
0,
0,
0,
0,
0,
0,
0,
};
