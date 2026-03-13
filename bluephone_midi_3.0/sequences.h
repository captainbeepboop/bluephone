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


const char turing[] PROGMEM = "01|01 E %110 >10010 ^2 2(X X) >00000 0(*00 E A+) !";
const char slippery[] PROGMEM = "02|01 C >10011 ^1 C X F C F C >00000 F G C X F C F C G C X X 2(1(C X F C F C F G C X F C F C G C) 3(*01 C X F C F C F G C X F C F C G C) X X) 1(1(>10000 C X F C F C F G C X F C F C G C) 0(>00000 *01 C X F C F C F G C X F C F C G C) X X) !";
const char born_to_run[] PROGMEM = "02|01 Am >11111 < . . . . . . >01111 &12 . . >00001 ^1 2(&01 2(*16 < C . . . F . G .) ^2 2(< C . . . F . G .) < F . Em . Dm . Em . C . C A#+ < F . Em . Dm . Em . < C . Am . F . &12 G .) &01 2(*16 < C . . . F . G .) *17 2(< C . . . F . G .) < Am . Am ^1 G C . Gm- . ^2 2(< A# . . . D# . . . < F . . . G#- . &12 . . &01) &01 *18 < C# . C# . G#- . G#- . < C# .  C# . D . D . ^1 >10001 D . . . . . . . G- . . . $16 . $17 . $18 . $19 . >00000 ^2 2( < C . . . F . G .) < F . Em . Dm . Em . C . C A#+ < F . Em . Dm . Em . < C . Am . F . &12 G . &01 0(*16 < C . . . F . G .) !";
const char sandstorm[] PROGMEM = "16|01 Em  >10011 ^2 < . . . . . . . . . . . . . . . . >10100 0(< *03 Em . . Em . . Em . Em . . Em . . C . C . . C . . G . G . . G . . D . Em . . Em . . Em . Em . . Em . . Am . Em . . Em . . Em . Em . . Em . . D .)!";
const char callmemaybe[] PROGMEM = "01|01 G >00001 ^2 0(G Em C D) *02 2( G D C D G D C D) 0(G Em C D) *02 0( G D C D G D C D) 1(G Em C D) 0(*02 G D C D G D C D)!";
const char carol[] PROGMEM = "01|01 Em >00001 ^2 0(Em X Em X D X Em X) 2(A G Em Em) 0(Em X Em X D X Em X) 4(A G Em Em) 0(Em X Em X D X Em X) 2(A G Em Em) !";
const char life[] PROGMEM = "01|01 C %140 >11111 ^1 0(*04 C Am F G) !";
const char mushroom[] PROGMEM = "01|01 C >01101 ^0 0(*05 C . . . F . . .) !";
const char yourcall[] PROGMEM = "01|01 Cm >10001 ^1 0(Cm A# D# G#) X";
const char stepdad[] PROGMEM = "01|01 E >10001 ^2 0(E X G# X C#m X A X) A A B C#m A X B X E B A A E B A A E B C#m A E B E X 2(E X G# X C#m X A X) A A B C#m A X B X E B A A E B A A E B C#m A E B E X >10000 4(E X G# X C#m X A X) A A B C#m A X B X >00000 E B A X E B A X E B C#m A E B E X !";
const char numb[] PROGMEM = "01|01 C >00001 %120 Am Am F C G 0(*06 Am F C G) Am F C G ?10 !";
const char allthethings[] PROGMEM = "02|01 C >00001 0(F Em Am C) 2(Am X G X C X Em X) X X 4(F Em Am C) 2(Am X G X C X Em X) X X 3(F Em Am C) F Em Am C ?13 !";
const char sevennations[] PROGMEM = "02|01 Am >00001 7(A C F E) A C F E ?09 !";
const char sk8rboi[] PROGMEM = "01|01 C >00001 2(C G Am G#-) 2(C G Am G#- C G Am A#) D# A# G#- G D# A# G#- G ?08 !";
const char beautiful[] PROGMEM = "01|01 C >10001 0(G X F X Em X D# X) 2(C X Am X G F C X) Am X ?11 !";
const char ice[] PROGMEM = "04|01 C >10101 %130 0(*08 D X X X X X X G+) !";
const char survive[] PROGMEM = "01|01 Am >10111 ^1 < . 0(< *10 Am Dm G C < F B E E) !";
const char runaway[] PROGMEM = "04|01 F >00001 2(*11 F . F . F . F .) 4(F . Gm- A#) Dm . A# . Gm- . C . Dm . A# . Gm- . C A# *12 3(F Gm A# . ) F Gm A# C *11 F . F . F . F . 4(F . Gm- A#) Dm . A# . Gm- . C . Dm . A# . Gm- . C A# *12 3(F Gm A# . ) F Gm A# C *11 F . F . F . F . >10001 Dm . A# . Gm- . C . Dm . A# . Gm- . C A# >00001 *12 3(F Gm A# . ) F Gm A# C 0(*11 F . F . F . F . ) !";
const char catholic[] PROGMEM = "01|01 Cm >00001 ^2 X X X X 0(Cm . Fm Cm Gm Fm Cm . ) !";
const char hackers[] PROGMEM = "08|01 Fm >11111 ^2 %156 0(0($24 Fm X X Fm X X Fm X X Fm X X Fm X Fm X $25 Cm X X Cm X X Cm X X Cm X X Cm X Cm X $26 C# X X C# X X C# X X C# X X C# X C# X $27 G# X X G# X X G# X X G# X X G# X Gd X $28 Fm X X Fm X X Fm X X Fm X X Fm X Fm X $29 Cm X X Cm X X Cm X X Cm X X Cm X Cm X $30 C# X X C# X X C# X X C# X X C# X C# X >00000 G# X X G# X X G# X X G# X X G# X Gd X) ^0 >11101 0(*13 $31 C X X X X X X X C X X X X X X X $32 F X X X X X X X C# X X X X X X X $33 D# X X X X X X X G#- X X X G- X X X F- X X X X X X X X X X X X X X X)) !";
const char pendulum[] PROGMEM = "04|01 Am ^2 %190 >00111 0(*14 Am Am Am Am C C C C Am Am Am Am C C C C Am Am Am Am C C C C Em Em Em Em G G G G) !";
const char bopit[] PROGMEM = "02|01 C ^2 %147 >11111 0(0(G X C X G X D X) 0(G D C D)) !";
const char winner[] PROGMEM = "01|01 G ^2 >11111 0(0(*15 G X Em X Am X D X) 0(G X D X Am X D X)) !";
const char careless[] PROGMEM = "01|01 C >01101 %080 0(Am Dm F Em) !";
const char dreams[] PROGMEM = "01|01 C >01101 ^2 %121 0(F X G X) !";
const char pretty[] PROGMEM = "01|01 C >11111 ^2 %120 0(C G Am F) !";
const char time_machine[] PROGMEM = "04|01 Cm ^0 >01101 &06 0(*19 Cm . . . A#+ . . . Cm . . G# A#+ . . .) !";



uint8_t number_of_sequences = 28;
const char *sequence_pointers[] = {&turing[0], &slippery[0], &callmemaybe[0], &sandstorm[0], &carol[0], &mushroom[0], &life[0], &yourcall[0], &numb[0], &allthethings[0], &sevennations[0], &sk8rboi[0], &beautiful[0], &ice[0], &stepdad[0], &survive[0], &runaway[0], &catholic[0], &hackers[0], &pendulum[0], &bopit[0], &winner[0], &careless[0], &dreams[0], &pretty[0], &born_to_run[0], &time_machine[0]};


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
//16 - hacker 156-16-12-0
//17 - pendulum 190-17-07-0
//18 - bop_it 147-18-02-5
//19 - the winner takes it all 125-19-92-0
//1* - careless whisper - 080-1*-21-0 - The riff is 7,6,3,1 (x 2) 5, 4, 1 (x 2) 4, 3, 1, 6, 4 / 3, 4, 5, 6, 7, 1, 2, 3
//1# - dreams - 120 - 10 - 12 - 0   
//20 - pretty enough - 120-20-51-0  1...5653 1...5432 8...785 1...5434 4323 321
//21 - born to run 140-21-12-0
//22 - time machine - 140-22-63-4


// ELMO - 170-10-4*-0


// - mushroom
// - plan B
// - miracle of modern science


//riffs
const char born_to_run_riff[] PROGMEM = "08|01 C . . . . . . . . . E F . . E . A . . . . . . . C . . . D . . . !";
const char born_to_run_riff_2[] PROGMEM = "16|01 G . G . G . G G A+ . G . G . G G E . G . G . G G D . C . C . G G E . G . G . G G A+ . G . A+ . G . . . C+ . . . A+ . G . G . A+ . G . G . C+ . . . C+ . A+ . G . A+ . G . G D C . D C A . C . . . A . . . A . A G- A . C A C . D C D . E D E . G E G . A+ G A+ . . . B+ . . . C+ . . . . . . . . . . . . . . .  !";
const char born_to_run_riff_3[] PROGMEM = "08|01 F# . . F . . . F F# . . F . . D# C# D# . . . . . G# G# D# . G# D# . . . . F# . . F . . . F F# . . F . . C# F G . . F# . . . F# G . . F# . . D . G . . F# . . F . . E . . D# . D . C# C . B . A# . A . G#- . G#- . G#- . G#- G- . . . . . . . !";

const char time_machine_riff[] PROGMEM = "08|01 C . . G . D# G# . A#+ . . D# . . D . C . . G# . D# G# . A#+ . . . . . . . ";


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
const char hacker_chorus[] PROGMEM = "04|01 C . . G- C . . D# F . . . C# . . . D# . . F- G#- . G- . F- . . . . . . . !";
const char pendulum_riff[] PROGMEM = "08|01 A C A C A C A C E- A E- A E- A E- A A C A C A C A C E- A E- A E- A E- A A C A C A C A C E- A E- A E- A E- A C E C E C E C E E G E G E G E G !";
const char winner_riff[] PROGMEM = "08|01 G- D C+ D G- B+ D G- A+ D G- G D#- E F# D#- E- B A+ B E- G B E- F# B E- E G#- B D G#- A E D+ E A C+ E A B+ C A A+ C A E A D- A G A D- F# A D E A D- D X F#- A X !";




uint8_t number_of_riffs = 20;
const char *riff_pointers[] = {&turing_riff[0], &slippery_riff[0], &callmemaybe_riff[0], &sandstorm_riff[0], &life_riff[0], &mushroom_riff[0], &numb_riff[0], &sevennations_riff[0], &ice_riff[0], &stepdad_riff[0], &survive_riff[0], &runaway_riff[0], &runaway_chorus[0], &hacker_chorus[0], &pendulum_riff[0], &winner_riff[0], &born_to_run_riff[0], &born_to_run_riff_2[0], &born_to_run_riff_3[0], &time_machine_riff[0]};
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




//drums
uint8_t number_of_drums = 14;


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
const char snare_fill[] PROGMEM = "16|----------------|xxxxxxxxxxxxxxxx|O---O---O---O---";
const char kick_fill[] PROGMEM = "16|----------------|----------------|OoooOoooOoooOooo";


const char *drumbeat_pointers[] = {&beat_0[0], &beat_1[0], &beat_2[0], &beat_3[0], &beat_4[0], &beat_5[0], &beat_6[0], &beat_7[0], &beat_8[0], &beat_9[0], &beat_star[0], &beat_hash[0], &snare_fill[0], &kick_fill[0]};


uint16_t sample_lengths[] = {
192, //1 - life
96, // 2 - turing
384, // 3 - modem
0, // 4 - wash
192, // 5 bopit
0,
0,
0,
0,
0,
0,
};
