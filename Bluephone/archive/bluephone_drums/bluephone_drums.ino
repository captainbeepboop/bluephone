
#include <MIDI.h>
#include <MozziGuts.h>
#include <Oscil.h> // oscillator template
#include <tables/sin512_int8.h> // sine table for oscillator
#include <samples/hat1.h>
#include <samples/hat2.h>
#include <samples/hat3.h>
#include <samples/hat4.h>
#include <samples/clap.h>
#include <tables/whitenoise2048_int8.h>
#include <ADSR.h>
#include <Sample.h> // Sample template

#define kick_tone_knob A0
#define kick_decay_knob A1
#define snare_decay_knob A3
#define snare_tone_knob A2
#define hihat_knob A4

#define CONTROL_RATE 1024

MIDI_CREATE_DEFAULT_INSTANCE();

Oscil <SIN512_NUM_CELLS, AUDIO_RATE> kick_oscil(SIN512_DATA);
Oscil <SIN512_NUM_CELLS, AUDIO_RATE> snare_oscil(SIN512_DATA);
Oscil <WHITENOISE2048_NUM_CELLS, AUDIO_RATE> snare_noise(WHITENOISE2048_DATA);

ADSR <CONTROL_RATE, CONTROL_RATE> kick_envelope;
ADSR <CONTROL_RATE, CONTROL_RATE> snare_envelope;

ADSR <CONTROL_RATE, CONTROL_RATE> kick_tone_envelope;
ADSR <CONTROL_RATE, CONTROL_RATE> snare_tone_envelope;


Sample <hat1_NUM_CELLS, AUDIO_RATE> hh1sample(hat1_DATA);
Sample <hat2_NUM_CELLS, AUDIO_RATE> hh2sample(hat2_DATA);
Sample <hat3_NUM_CELLS, AUDIO_RATE> hh3sample(hat3_DATA);
Sample <hat4_NUM_CELLS, AUDIO_RATE> hh4sample(hat4_DATA);
Sample <clap_NUM_CELLS, AUDIO_RATE> clapsample(clap_DATA);

//drum values

byte kick_gain = 0;
byte snare_gain = 0;

unsigned int kick_tone = 100;
unsigned int snare_tone = 300;
int kick_tone_mod = 0;
int snare_tone_mod = 0;
unsigned int snare_attack = 10;
unsigned int snare_decay = 50;
unsigned int kick_attack = 15;
unsigned int kick_decay = 50;

unsigned int min_decay = 50;
unsigned int max_decay = 500;
unsigned int min_tone = 20;
unsigned int max_tone = 400;

unsigned int hihat_index = 0;
unsigned int snare_index = 0;

int hatvolume;
int snarevolume;
int kickvolume;

void update_envelopes()

{

    hihat_index = map(mozziAnalogRead(hihat_knob), 0, 1000, 0, 3);

    kick_tone = map(mozziAnalogRead(kick_tone_knob), 0, 1024, min_tone, max_tone);
    kick_decay = map(mozziAnalogRead(kick_decay_knob), 0, 1024, min_decay, max_decay);
    snare_tone = map(mozziAnalogRead(snare_tone_knob), 0, 1024, min_tone, max_tone);
    snare_decay = map(mozziAnalogRead(snare_decay_knob), 0, 1024, min_decay, max_decay);


    kick_envelope.setTimes(kick_attack, kick_decay, 0, 0);
    kick_tone_envelope.setTimes(kick_attack, kick_decay, 0, 0);
    snare_envelope.setTimes(snare_attack, snare_decay, 0, 0);
    snare_tone_envelope.setTimes(snare_attack, snare_decay, 0, 0);
}


void setup() {
  
    startMozzi(CONTROL_RATE);
  
    kick_envelope.setADLevels(250, 0);
    snare_envelope.setADLevels(250, 0);
    
    kick_tone_envelope.setADLevels(900, 0);
    snare_tone_envelope.setADLevels(900, 0);

    snare_noise.setFreq((float)AUDIO_RATE/WHITENOISE2048_SAMPLERATE);

    hh1sample.setFreq((float) hat1_SAMPLERATE / (float) hat1_NUM_CELLS);
    hh2sample.setFreq((float) hat2_SAMPLERATE / (float) hat2_NUM_CELLS);
   hh3sample.setFreq((float) hat3_SAMPLERATE / (float) hat3_NUM_CELLS);
   hh4sample.setFreq((float) hat4_SAMPLERATE / (float) hat4_NUM_CELLS);
   clapsample.setFreq((float) clap_SAMPLERATE / (float) clap_NUM_CELLS);

    update_envelopes();

    MIDI.setHandleNoteOn(HandleNoteOn);  // Put only the name of the function
    MIDI.begin(10);

}

void updateControl() {

    kick_envelope.update();
    kick_tone_envelope.update();
    kick_gain = kick_envelope.next();
    kick_tone_mod = kick_tone + kick_tone_envelope.next();
    
    snare_envelope.update();
    snare_tone_envelope.update();
    snare_gain = snare_envelope.next();
    snare_tone_mod = snare_tone + snare_tone_envelope.next();

    kick_oscil.setFreq(kick_tone_mod);
    snare_oscil.setFreq(snare_tone_mod);

    MIDI.read();
}

void play_drum(int drum, int volume) {

    switch (drum) {
        //for each drum, change a variable for that drum's volume based on the volume coming in
        case 0:
        kick_envelope.noteOn();
        kick_tone_envelope.noteOn();
        kickvolume = volume;
        break;
    
        case 1:
        if (snare_tone < 100)
        {
            clapsample.start();
        }
        else
        {
            snare_envelope.noteOn();
            snare_tone_envelope.noteOn();
        }
        snarevolume = volume;
        break;
    
        case 2:
        switch(hihat_index)
        {

            case 0:
                hh1sample.start();
            break;
            case 1:
                hh2sample.start();
            break;
            case 2:
                hh3sample.start();
            break;
            case 3:
                hh4sample.start();
            break;
        }
        hatvolume = volume;
        break;
    }
}

void HandleNoteOn(byte channel, byte note, byte velocity) {

        update_envelopes();

        for (int i = 0; i < 3; i++)
        {
            if (bitRead(note, i) == 1)
            {
                play_drum(i, 1);
            }
        }

}


int updateAudio(){
    return MonoOutput::from8Bit(
        (kick_gain * kick_oscil.next() >> 10)
        +((snare_gain * snare_oscil.next() >> 11)
        +(snare_gain * snare_noise.next() >> 12))
        +((hh1sample.next())/5
        +(hh2sample.next())/4
        +(hh3sample.next())/4
        +(hh4sample.next())/4
        +(clapsample.next())/4)
    ); 
}


void loop(){
  audioHook(); // required here
}



