#include <MIDI.h>

#define kick_knob A0
#define snare_knob A1
#define hihat_knob A2
#define sample_knob A3
#define pitch_knob A4
#define radio_pin 2
#define switch_pin 3

bool radio_gain = 0;
uint8_t sample_counter = 0;
uint8_t sample_frequency = 32;
uint8_t frequencies[] = {64, 16, 8, 4, 2, 1};
uint8_t current_sample = 0;

MIDI_CREATE_DEFAULT_INSTANCE();

uint8_t drum_numbers[] = {1, 1, 1};
int16_t pitch_shift = 0;
bool pitch_shifted = 0;

int i = 1;

void setup() {
  
    Serial.begin(9600);
    Serial.write(0xf0);
    Serial.write(0xaa); //start of message

    Serial.write(0x07); //length of message

    Serial.write(0x0c);
    Serial.write(0x5a);
    Serial.write(0x1f);

    Serial.write(0x55); //end of message

    MIDI.setHandleNoteOn(HandleNoteOn);  // Put only the name of the function
    MIDI.begin(10);

    pinMode(radio_pin, OUTPUT);
    pinMode(switch_pin, INPUT_PULLUP);
    digitalWrite(radio_pin, radio_gain);

    play_drum(1,1);
  
}

void loop() {

    MIDI.read();

}

void check_knobs() {

    drum_numbers[0] = map(analogRead(kick_knob), 0, 1024, 1, 9);
    drum_numbers[1] = map(analogRead(snare_knob), 0, 1024, 1, 9);
    drum_numbers[2] = map(analogRead(hihat_knob), 0, 1024, 1, 9);
    sample_frequency = frequencies[map(analogRead(sample_knob),0,1024,0,6)];
    pitch_shift = map(analogRead(pitch_knob), 0, 1024, -32767, 32767);

}

void HandleNoteOn(byte channel, byte note, byte velocity) {

    check_knobs();
    adjust_speed_or_volume();
    
    for(uint8_t i = 0; i < 3; i++)
    {
        if (bitRead(note, i) == 1)
        {
            play_drum(i, velocity & 0b11);
        }
    }
    if (bitRead(note, 1) != radio_gain)
    {
        radio_gain = bitRead(note, 1);
        digitalWrite(radio_pin, radio_gain);
    }
    uint8_t sample_number = 16*(note >> 3) + (velocity >> 3);
    if (sample_number > 0)
    {
        play_sample(sample_number, bitRead(velocity, 2));
    }
    else if (bitRead(velocity, 2) == 1)
    {
        //stop sample
        Serial.write(0xf0);
        Serial.write(0xaa); //start of message

        Serial.write(0x09); //length of message

        Serial.write(0x0d); //control track
        Serial.write(0x04); //play poly=
        Serial.write(current_sample); //track number (lower byte)
        Serial.write(0x00); //track number (higher byte)
        Serial.write(0x00); //lock - prevents voice from being stolen

        Serial.write(0x55); //end of message

    }
}

void play_sample(uint8_t sample, bool start)
{
    current_sample = sample;
    if (current_sample > 64)
    {
        Serial.write(0xf0);
        Serial.write(0xaa); //start of message

        Serial.write(0x09); //length of message

        Serial.write(0x0d); //control track
        Serial.write(0x01); //play poly
        Serial.write(sample); //track number (lower byte)
        Serial.write(0x00); //track number (higher byte)
        Serial.write(0x01); //lock - prevents voice from being stolen

        Serial.write(0x55); //end of message
    }
    else
    {
        current_sample = current_sample + 64;
        if (start == 1)
        {
            sample_counter = 0;
        }
        else
        {
            sample_counter++;
        }
        
        if (sample_counter % sample_frequency == 0)
        {
            //stop sample
            Serial.write(0xf0);
            Serial.write(0xaa); //start of message

            Serial.write(0x09); //length of message

            Serial.write(0x0d); //control track
            Serial.write(0x04); //stop track
            Serial.write(current_sample); //track number (lower byte)
            Serial.write(0x00); //track number (higher byte)
            Serial.write(0x00); //lock - prevents voice from being stolen

            Serial.write(0x55); //end of message
            
            //play sample
            Serial.write(0xf0);
            Serial.write(0xaa); //start of message

            Serial.write(0x09); //length of message

            Serial.write(0x0d); //control track
            Serial.write(0x01); //play poly
            Serial.write(current_sample); //track number (lower byte)
            Serial.write(0x00); //track number (higher byte)
            Serial.write(0x01); //lock - prevents voice from being stolen

            Serial.write(0x55); //end of message
        }
    }
}

void play_drum(uint8_t drum, uint8_t accent)

{    
    int16_t gain = 0;
    if (accent == 1)
    {gain = -5;}

    //adjust volume
    Serial.write(0xf0);
    Serial.write(0xaa); //start of message

    Serial.write(0x09); //length of message

    Serial.write(0x08); //control volume
    Serial.write(16*drum+drum_numbers[drum]); //track number (lower byte)
    Serial.write(0x00); //track number (higher byte)
    Serial.write(gain & 0xff);
    Serial.write(gain >> 8);

    Serial.write(0x55); //end of message

    // stop drums
    Serial.write(0xf0);
    Serial.write(0xaa); //start of message

    Serial.write(0x09); //length of message

    Serial.write(0x0d); //control track
    Serial.write(0x04); //stop track
    Serial.write(16*drum+drum_numbers[drum]); //track number (lower byte)
    Serial.write(0x00); //track number (higher byte)
    Serial.write(0x00); //lock - prevents voice from being stolen

    Serial.write(0x55); //end of message
    
    //play drum
    Serial.write(0xf0);
    Serial.write(0xaa); //start of message

    Serial.write(0x09); //length of message

    Serial.write(0x0d); //control track
    Serial.write(0x01); //play poly
    Serial.write(16*drum+drum_numbers[drum]); //track number (lower byte)
    Serial.write(0x00); //track number (higher byte)
    Serial.write(0x01); //lock - prevents voice from being stolen

    Serial.write(0x55); //end of message
}

void adjust_speed_or_volume()
{
    if (digitalRead(switch_pin) == 0)
    {
        Serial.write(0xf0);
        Serial.write(0xaa); //start of message

        Serial.write(0x07); //length of message
        Serial.write(0x0c); //control speed
        Serial.write(pitch_shift & 0xff);
        Serial.write(pitch_shift >> 8);

        Serial.write(0x55); //end of message
        pitch_shifted = 1;
    }
    else
    {
        if (pitch_shifted == 1)
        {
            Serial.write(0xf0);
            Serial.write(0xaa); //start of message

            Serial.write(0x07); //length of message
            Serial.write(0x0c); //control speed
            Serial.write(0x00);
            Serial.write(0x00);

            Serial.write(0x55); //end of message
            pitch_shifted = 0;
        }
    }
}