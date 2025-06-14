#include <MIDI.h>
#include <MozziGuts.h>
#include <Oscil.h> 
#include <tables/triangle_analogue512_int8.h>
#include <tables/sin512_int8.h> // sine table for oscillator
#include <tables/saw_analogue512_int8.h>
#include <tables/whitenoise8192_int8.h>
#include <mozzi_midi.h>
#include <ADSR.h>

MIDI_CREATE_DEFAULT_INSTANCE();

#define CONTROL_RATE 256 

//oscillators
Oscil <TRIANGLE_ANALOGUE512_NUM_CELLS, AUDIO_RATE> aOsc(TRIANGLE_ANALOGUE512_DATA);
Oscil <TRIANGLE_ANALOGUE512_NUM_CELLS, AUDIO_RATE> aOsc1(TRIANGLE_ANALOGUE512_DATA);
Oscil <TRIANGLE_ANALOGUE512_NUM_CELLS, AUDIO_RATE> aOsc2(TRIANGLE_ANALOGUE512_DATA);
Oscil <TRIANGLE_ANALOGUE512_NUM_CELLS, AUDIO_RATE> aOsc3(TRIANGLE_ANALOGUE512_DATA);
Oscil <WHITENOISE8192_NUM_CELLS, AUDIO_RATE> Noise(WHITENOISE8192_DATA);

Oscil <SIN512_NUM_CELLS, CONTROL_RATE*400> aSin(SIN512_DATA);

#define waveSwitch 12
#define noiseSwitch 8
bool last_wave_switch = 1;
bool wave_type = 0;
bool noise_on = 0;

//envelopes/LFO

#define envelopePin 11
#define lfoPin 3
#define attackPot A0
#define decayPot A1
#define lfoPot A2

int lfo = 0;
int lfo_print = 0;
int lfo_frequency = 1;
double attack = 0;
double decay = 0;
double envelope = 0;
int envelope_print = 0;

bool envelope_stage = 0;
int envelope_note = 48;


void HandleNoteOn(byte channel, byte note, byte velocity) {

  aOsc.setFreq(mtof(float(note)));
  aOsc1.setFreq(mtof(float(note+12)));
  switch(velocity)
  {
    
    case 1:
        aOsc2.setFreq(mtof(float(note+16)));
        aOsc3.setFreq(mtof(float(note+19)));
    break;

    case 2:
        aOsc2.setFreq(mtof(float(note+15)));
        aOsc3.setFreq(mtof(float(note+19)));
    break;

    case 3:
        aOsc2.setFreq(mtof(float(note+15)));
        aOsc3.setFreq(mtof(float(note+18)));
    break;

    case 4: 
        aOsc2.setFreq(mtof(float(note+24)));
        aOsc3.setFreq(mtof(float(note+19)));
    break; 
  }
  envelope = 0;
  envelope_note = note;
  envelope_stage = 1;

}


void HandleNoteOff(byte channel, byte note, byte velocity) {

  if(envelope_note == note)
  {
    envelope_stage = 0;
  }

}

void setup() {

  MIDI.setHandleNoteOn(HandleNoteOn);  // Put only the name of the function
  MIDI.setHandleNoteOff(HandleNoteOff);  // Put only the name of the function
  MIDI.begin(2);

  Noise.setFreq(100);
  aOsc.setFreq(mtof(float(50)));
  aOsc1.setFreq(mtof(float(50+12)));
  aOsc2.setFreq(mtof(float(50+16)));
  aOsc3.setFreq(mtof(float(50+19)));

  aSin.setFreq(2);

  pinMode(envelopePin, OUTPUT);
  pinMode(lfoPin, OUTPUT);
  pinMode(waveSwitch, INPUT_PULLUP);
  pinMode(noiseSwitch, INPUT_PULLUP);


  startMozzi(CONTROL_RATE);

  aOsc.setTable(SAW_ANALOGUE512_DATA);
  aOsc1.setTable(SAW_ANALOGUE512_DATA);
  aOsc2.setTable(SAW_ANALOGUE512_DATA);
  aOsc3.setTable(SAW_ANALOGUE512_DATA);
}

void updateControl(){

  lfo_frequency = map(analogRead(lfoPot), 0, 1023, 10, 1500);
  aSin.setFreq(lfo_frequency);
  lfo = (int) (aSin.next());
  lfo_print = map(lfo, -116, 115, 0, 255);

  analogWrite(lfoPin, lfo_print);

  ////END EXPERIMENTAL STUFF

  if (digitalRead(noiseSwitch) == noise_on)
  {
    noise_on = !noise_on;
  }
  
  if(last_wave_switch != digitalRead(waveSwitch))
  {
    last_wave_switch = digitalRead(waveSwitch);
    if (last_wave_switch == 0)
    {
        wave_type = !wave_type;
    }
    if (wave_type == 1)
    {
      aOsc.setTable(TRIANGLE_ANALOGUE512_DATA);
      aOsc1.setTable(TRIANGLE_ANALOGUE512_DATA);
      aOsc2.setTable(TRIANGLE_ANALOGUE512_DATA);
      aOsc3.setTable(TRIANGLE_ANALOGUE512_DATA);

    }
    else
    {
      aOsc.setTable(SAW_ANALOGUE512_DATA);
      aOsc1.setTable(SAW_ANALOGUE512_DATA);
      aOsc2.setTable(SAW_ANALOGUE512_DATA);
      aOsc3.setTable(SAW_ANALOGUE512_DATA);
    }

  }
  
  
  switch(envelope_stage) {
    
    case 0:
        decay = 2048/(analogRead(decayPot)+1);
        envelope = envelope - decay;
        if(envelope < 0)
        {
            envelope = 0;
        }
    break;
    
    case 1:
        attack = 2048/(analogRead(attackPot)+1);
        envelope = envelope + attack;
        if(envelope > 1024)
        {
            envelope = 1024;
        }
    break;

  }

  envelope_print = map(envelope, 0, 1024, 0, 255);
  MIDI.read();
  analogWrite(envelopePin, envelope_print);
}

int updateAudio(){
  
    return (int) (
    (aOsc.next()/4
    +aOsc1.next()/4
    +aOsc2.next()/4
    +aOsc3.next()/4
    +noise_on*Noise.next()/4)
  );

}


void loop() {
  audioHook(); // required here
}