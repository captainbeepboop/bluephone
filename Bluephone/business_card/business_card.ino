#include <MIDI.h>
#include <MozziGuts.h>
#include <Oscil.h> 
#include <tables/triangle_analogue512_int8.h>
#include <tables/square_analogue512_int8.h>
#include <tables/sin512_int8.h> // sine table for oscillator
#include <tables/saw_analogue512_int8.h>
#include <tables/whitenoise8192_int8.h>
#include <mozzi_midi.h>
#include <ADSR.h>

#define CONTROL_RATE 256 

MIDI_CREATE_DEFAULT_INSTANCE();

#define board 1 //1 = BASS, 2 = CHORDS, 3 = LEAD
const byte midi_channels[3] = {4, 2, 3};

//SET UP OSCILLATORS
Oscil <SAW_ANALOGUE512_NUM_CELLS, AUDIO_RATE> aOsc1(SAW_ANALOGUE512_DATA);
Oscil <SAW_ANALOGUE512_NUM_CELLS, AUDIO_RATE> aOsc2(SAW_ANALOGUE512_DATA);
Oscil <WHITENOISE8192_NUM_CELLS, AUDIO_RATE> Noise(WHITENOISE8192_DATA);

#if board == 2
    #define oscillators 4
    Oscil <SAW_ANALOGUE512_NUM_CELLS, AUDIO_RATE> aOsc3(SAW_ANALOGUE512_DATA);
    Oscil <SAW_ANALOGUE512_NUM_CELLS, AUDIO_RATE> aOsc4(SAW_ANALOGUE512_DATA);
#else
    #define oscillators 2
#endif


//SET UP ENVELOPES
ADSR <CONTROL_RATE, CONTROL_RATE> envelope;
Oscil <SIN512_NUM_CELLS, AUDIO_RATE> LFO(SIN512_DATA);
#define envelope_pin 5

int attack_ms = 0;
int release_ms = 500;
float lfo_speed = 1;

byte max_env_gain = 255;
int max_lfo_gain = 0;
float min_lfo_speed = 0.1;
float max_lfo_speed = 20;

#define min_gain 75
#define max_gain 255
#define max_attack 1000
#define max_release 2000

//SET UP NOTE MODS
byte note = 40;
#define max_vibrato 40
byte vibrato_depth = 0;
#define max_detune 2
float detune = 0;
float noise_depth = 0;

//SET UP KNOBS
#if board == 2
    #define env_attack_knob A0
    #define env_release_knob A1
    #define env_depth_knob A2
    #define lfo_speed_knob A3
    #define lfo_depth_knob A4
    #define wave_switch 6
#else
    #define env_release_knob A0
    #define env_depth_knob A1
    #define lfo_speed_knob A2
    #define noise_knob A2
    #define rotary1 3
    #define rotary2 4
    #define rotary_button 2

    long last_rotary = 0;
    int rotary_debounce = 50;
    int rotary_count = 0;
#endif

byte mode = 0;
#define number_of_modes 3

void update_envelope()
{
    envelope.update();
    byte env_gain = map(envelope.next(), 0, 255, 0, max_env_gain);

    int lfo_gain = map(LFO.next(), -116, 115, 0, max_lfo_gain);
    int adjusted_gain = map(lfo_gain + env_gain, 0, 512, min_gain, max_gain);
    int pitch_shift = map(LFO.next(), -116, 115, -vibrato_depth, vibrato_depth);
    
    if (adjusted_gain > 255)
    {
        adjusted_gain = 255;
    }
    analogWrite(envelope_pin, adjusted_gain);
    #if board != 2
        aOsc1.setFreq(mtof(note)+pitch_shift);
        aOsc2.setFreq((mtof(note)+pitch_shift)*detune);
    #endif
}

void update_knobs()
{
    #if board == 2
        attack_ms = map(mozziAnalogRead(env_attack_knob),0,1024,0,max_attack);
        release_ms = map(mozziAnalogRead(env_release_knob),0,1024,0,max_release);
        lfo_speed = (float) map(mozziAnalogRead(lfo_speed_knob),0,1024,1,400);
        max_env_gain = map(mozziAnalogRead(env_depth_knob), 0, 1024, 0, 255);
        max_lfo_gain = map(mozziAnalogRead(lfo_depth_knob), 0, 1024, 0, 255);
    #else
        release_ms = map(mozziAnalogRead(env_release_knob),0,1024,0,max_release);
        max_env_gain = map(mozziAnalogRead(env_depth_knob), 0, 1024, 0, 255);

        switch (mode)
        {
            case 0:
            case 1:
                lfo_speed = (float) map(mozziAnalogRead(lfo_speed_knob),0,1024,1,400);
            break;

            case 2:
                noise_depth = (float) map(mozziAnalogRead(noise_knob),0,1024,1,100)/100;
            break;
        }
    #endif

    LFO.setFreq(lfo_speed);
    envelope.setTimes(attack_ms,0,10000,release_ms);
}

void setup()
{
    MIDI.setHandleNoteOn(note_on);
    MIDI.setHandleNoteOff(note_off);
    MIDI.begin(midi_channels[board-1]);
    
    Noise.setFreq(100);
    
    aOsc1.setFreq(mtof(float(note)));
    #if board == 2
        aOsc2.setFreq(mtof(float(note+12)));
        aOsc3.setFreq(mtof(float(note+16)));
        aOsc4.setFreq(mtof(float(note+19)));
    #else
        aOsc1.setFreq(mtof(float(note)));
        aOsc2.setFreq(mtof(float(note)));
    #endif

    LFO.setFreq(lfo_speed);
    envelope.setTimes(attack_ms,0,10000,release_ms);
    envelope.setADLevels(255,255);

    startMozzi(CONTROL_RATE);

    pinMode(envelope_pin, OUTPUT);
    #if board == 2
        pinMode(wave_switch, INPUT_PULLUP);
    #else
        pinMode(rotary1, INPUT_PULLUP);
        pinMode(rotary2, INPUT_PULLUP);
        pinMode(rotary_button, INPUT_PULLUP);
        attachInterrupt(digitalPinToInterrupt(rotary1), rotary_turn, CHANGE);
        attachInterrupt(digitalPinToInterrupt(rotary_button), rotary_press, FALLING);
    #endif
}

void rotary_turn()
{
  #if board != 2
    if (millis() - last_rotary > rotary_debounce)
    {
        if (digitalRead(rotary1) == digitalRead(rotary2))
        {
            switch (mode)
            {
                case 0:
                    if (max_lfo_gain > 0)
                    {
                        max_lfo_gain = max_lfo_gain - 5;
                    }
                break;
                case 1:
                    if (vibrato_depth > 0)
                    {
                        vibrato_depth--;
                    }
                break;
                case 2:
                    if (detune > 0)
                    {
                        detune = detune - 0.05;
                    }
                break;
            }
        }
        else
        {
            switch (mode)
            {
                case 0:
                    if (max_lfo_gain < 255)
                    {
                        max_lfo_gain = max_lfo_gain + 5;
                    }
                break;
                case 1:
                    if (vibrato_depth < max_vibrato)
                    {
                        vibrato_depth++;
                    }
                break;
                case 2:
                    if (detune < max_detune)
                    {
                        detune = detune + 0.05;
                    }
                break;
            }
        }
        last_rotary = millis();
    }
  #endif
}

void rotary_press()
{
    #if board != 2
        if (millis() - last_rotary > rotary_debounce)
        {
            mode++;
            if (mode == number_of_modes)
            {
                mode = 0;
            }
            switch (mode)
            {
                case 0:
                    max_lfo_gain = 100;
                    vibrato_depth = 0;
                    detune = 0;
                    noise_depth = 0;
                    aOsc1.setTable(SAW_ANALOGUE512_DATA);
                    aOsc2.setTable(SAW_ANALOGUE512_DATA);

                break;
                case 1:
                    max_lfo_gain = 0;
                    vibrato_depth = 20;
                    detune = 0;
                    noise_depth = 0;
                    aOsc1.setTable(SQUARE_ANALOGUE512_DATA);
                    aOsc2.setTable(SQUARE_ANALOGUE512_DATA);

                break;
                case 2:
                    max_lfo_gain = 0;
                    vibrato_depth = 0;
                    detune = 1.1;
                    aOsc1.setTable(SAW_ANALOGUE512_DATA);
                    aOsc2.setTable(SAW_ANALOGUE512_DATA);
                break;
            }
            last_rotary = millis();
        }
    #endif
}


void updateControl()
{
    MIDI.read();
    update_knobs();
    update_envelope();
}

void note_on(byte midi_channel, byte midi_note, byte velocity)
{
    envelope.noteOn();
    note = midi_note;

    #if board == 1
        envelope.noteOff();
    #endif

    #if board == 2
        aOsc1.setFreq(mtof(float(note)));
        aOsc2.setFreq(mtof(float(note+12)));
        switch(velocity)
        {
            
            case 1:
                aOsc3.setFreq(mtof(float(note+16)));
                aOsc4.setFreq(mtof(float(note+19)));
            break;

            case 2:
                aOsc3.setFreq(mtof(float(note+15)));
                aOsc4.setFreq(mtof(float(note+19)));
            break;

            case 3:
                aOsc3.setFreq(mtof(float(note+15)));
                aOsc4.setFreq(mtof(float(note+18)));
            break;

            case 4: 
                aOsc3.setFreq(mtof(float(note+24)));
                aOsc4.setFreq(mtof(float(note+19)));
            break; 
        }
    #endif
}

void note_off()
{
    envelope.noteOff();
}



void loop() {
  audioHook(); 
}

int updateAudio(){
#if board == 2
    return (aOsc1.next()+aOsc2.next()+aOsc3.next()+aOsc4.next())/4;
#else
    return (aOsc1.next()+aOsc2.next())/2; 
#endif
}
