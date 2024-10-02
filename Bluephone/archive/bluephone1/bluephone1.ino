#define debug 0

// display stuff
#define IIC_SCL 12
#define IIC_SDA 11


const bool numbers[4][5][3] PROGMEM =
{
  {{0,1,0},
  {0,1,0},
  {0,1,0},
  {0,1,0},
  {0,1,0}},

  {{1,1,1},
  {0,0,1},
  {1,1,1},
  {1,0,0},
  {1,1,1}},

  {{1,1,1},
  {0,0,1},
  {1,1,1},
  {0,0,1},
  {1,1,1}},
  
  {{1,0,1},
  {1,0,1},
  {1,1,1},
  {0,0,1},
  {0,0,1}},
};

const bool coin_message[5][42] PROGMEM =
{
    {0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0},
    {0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0},
    {0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0},
    {0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0},
    {0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0},
};

bool table[7][16] = 
{
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

//keypad stuff
bool button_status[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
bool button_status_last[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned long debounce_time[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const uint8_t debounce_delay = 10;
const uint8_t rowPins[4] = {9, 7, 8, 6}; 
const uint8_t colPins[3] = {5, 3, 4}; 
#define followPin 10
uint8_t last_button = 0;

//coin stuff
#define solenoid_1 A2
#define solenoid_2 A0
#define coin_LED A1
#define coinPin 13
bool coin_status = 0;

//MIDI stuff
#if (debug == 0)
#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();
#endif

//note stuff
int octave1 = 0;
int octave2 = 0;
const int scale[2][12] = {{0, 2, 4, 5, 7, 9, 11, 12, 14, 16, 17, 19},{0, 2, 3, 5, 7, 8, 10, 12, 14, 15, 17, 19}};
bool vibe = 0;
int key = 0;
uint8_t note1 = 48;
uint8_t note2 = 48;
uint8_t note3 = 48;
uint8_t note4 = 48;
uint8_t note5 = 0;
uint8_t note6 = 0;

bool lead_follows = 0;

//beat stuff
#define max_beats 128
int count_in = 0;
bool on_or_off = 0;

bool drums[2][3][16] = {
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    },
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    }
};

uint8_t chords[2][max_beats] =
{
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

uint8_t leads[2][max_beats] =
{
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

#include "presets.h"

uint8_t bpm = 120;
unsigned long bpm_delay = 7500000/bpm;
unsigned long last_beat = 0;
uint8_t beat_count = 0;

bool beat_display[8] = {0,0,0,0,0,0,0,0};

int min_bpm = 40;
int max_bpm = 250;

//mode stuff

int phone_number[8] = {0,0,0,0,0,0,0,0};
int phone_number_index = 0;
int mode = 0;
bool chord_track = 0;
bool lead_track = 0;
bool drum_track = 0;
int mode_shift = 0;

void reset()
{
    mode = 0;
    chord_track = 0;
    lead_track = 0;
    drum_track = 0;
    bpm = 120;
    phone_number_index = 0;
    
    chord_track = 0;
    lead_track = 0;
    drum_track = 0;
    mode_shift = 0;   

    drum_mute = 0;
    chord_mute = 0;
    lead_mute = 1;
    on_or_off = 0;
    
    //clear chords
    for (int i = 0; i < max_beats; i++)
    {
        chords[0][i] = 0;
        chords[1][i] = 0;
        leads[0][i] = 0;
        leads[1][i] = 0;
    }
    
    //clear drums
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < drum_length; j++)
        {
            drums[0][i][j] = 0;
            drums[1][i][j] = 0;
        }
    }
    clear_table();

    delay(500);
    digitalWrite(solenoid_1, 0);
}

void setup()
{
    //display stuff
    pinMode(IIC_SCL, OUTPUT);
    pinMode(IIC_SDA, OUTPUT);
    digitalWrite(IIC_SCL, LOW);
    digitalWrite(IIC_SDA, LOW);

    //keypad stuff
    pinMode(colPins[0], OUTPUT);
    pinMode(colPins[1], OUTPUT);
    pinMode(colPins[2], OUTPUT);
    pinMode(rowPins[0], INPUT);
    pinMode(rowPins[1], INPUT);
    pinMode(rowPins[2], INPUT);
    pinMode(rowPins[3], INPUT);
    pinMode(solenoid_1, OUTPUT);
    pinMode(solenoid_2, OUTPUT);
    pinMode(coin_LED, OUTPUT);
    pinMode(followPin, INPUT);
    pinMode(coinPin, INPUT_PULLUP);

    //coin stuff
    digitalWrite(solenoid_1, LOW);
    digitalWrite(solenoid_2, HIGH);
    digitalWrite(coin_LED, HIGH);

    #if (debug == 0)
    MIDI.begin(MIDI_CHANNEL_OMNI);   
    #endif

    #if (debug == 1)
    Serial.begin(9600);
    #endif

}

void loop()
{

//check the beat
if (micros() - last_beat > bpm_delay)
{   
    last_beat = micros() - (micros() - last_beat - bpm_delay); //see if this causes it to catch up or makes it too stuttery???
    update_table();
    on_or_off = !on_or_off;
    if (on_or_off == 1)
    {
        the_beat();
    }
    else
    {
        the_off_beat();
    }
}

//check buttons
button_check();

// records onto the previous beat every moment after the beat
// - hello, could do something like this, where late notes go forward and early notes go back
if (micros() - last_beat < (bpm_delay/2))
{
    check_record();
}

}

void clear_table()
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            table[j][i] = 0;
        }
    }

}

void update_table()
{
    switch (mode)
    {
        case 0: //displays the "insert coin message"
            for (int i = 0; i < 16; i++)
            {
                for (int j = 1; j < 6; j++)
                {
                    if((beat_count + i)%64 < 42)
                    {
                      table[j][i] = pgm_read_byte(&coin_message[j-1][(beat_count + i)%64]);
                      //table[j][i] = coin_message[j-1][(beat_count + i)%64];
                    }
                    else
                    {
                      table[j][i] = 0;
                    }
                }
            }

        break;
        case 1:
            //phone number appears as it's being typed
        break;
        case 2:
        case 3:
        case 4:

            //displays the beat
            for (int i = 0; i < 4; i++)
            {
                if (beat_count % 4 == i)
                {
                    table[1][11+i] = 1;
                }
                else
                {
                    table[1][11+i] = 0;
                }            
            
                if ((beat_count%16)/4 == i)
                {
                    table[2][11+i] = 1;
                }
                else
                {
                    table[2][11+i] = 0;
                } 
                if ((beat_count/16)%4 == i)
                {
                    table[3][11+i] = 1;
                }
                else
                {
                    table[3][11+i] = 0;
                }            
            }

        break;
        case 5:
            //control centre display
        break;
    }
    //every time the table updates, the screen updates
    update_screen();
}

void the_off_beat()
{
    if(mode > 1)
    {
        for (int i = 2; i < 5; i++)
        {
          table[i][9] = 0;
        }
    }
}

void the_beat()
{       
    switch(mode)
    {
        case 1: // if phone number is entered, count in
            if(phone_number_index == 8)
            {
                table[0][count_in] = 1;
                table[6][16-count_in] = 1;
              
                if(count_in % 4 == 0)
                {
                    for(int i = 0; i<16; i++)
                    {
                        for(int j = 1; j<6; j++)
                        {
                            table[j][i] = 0;
                        }           
                    }

                    if(count_in == 0)
                    { 
                        for(int i = 0; i<3; i++)
                        {
                            for(int j = 0; j<5; j++)
                            {
                                table[j+1][i+1] = pgm_read_byte(&numbers[0][j][i]);
                                //table[j+1][i+1] = numbers[0][j][i];
                            }           
                        }
                    }
                    else
                    {
                        for(int i = 0; i<3; i++)
                        {
                            for(int j = 0; j<5; j++)
                            {
                                table[j+1][i+count_in] = pgm_read_byte(&numbers[count_in/4][j][i]);
                                //table[j+1][i+count_in] = numbers[count_in/4][j][i];
                            }           
                        }                    
                    } 
                }

                /*if(count_in == 4)
                {
                    MIDI.sendNoteOff(note5, 0, 6);
                }*/
                
                if(count_in == 16)
                {
                    phone_number_index = 0;
                    beat_count = max_beats-1;
                    mode = 2;
                    drum_track = 0;
                    clear_table();
                    table[4][12] = 1; 
                    table[4][13] = 1; 
                    table[5][11] = 1; 
                    table[5][13] = 1; 
                    count_in = 0;
                }
                else
                {
                    count_in++;
                }
            }
        break;
        
        
        case 2:
        case 3:
        case 4:
        case 5:
        #if (debug == 0)
            
            //play chord sequence if no other chord is playing
             
            if ((last_button == 0 && button_status[11] == 0) || mode != 2)
            {
                if (48 + scale[vibe + chords[chord_track][beat_count] - 1] + octave1*12 + key != note1 && chord_mute == 0)
                {
                    MIDI.sendNoteOff(note1, 0, 2);
                    chord_visualisation(chords[chord_track][beat_count], 1);

                    note1 = 48 + scale[vibe][chords[chord_track][beat_count] - 1] + octave1*12 + key;
                    note2 = 48 + scale[vibe][chords[chord_track][beat_count] + 1] + octave1*12 + key;
                    note3 = 48 + scale[vibe][chords[chord_track][beat_count] + 3] + octave1*12 + key;

                }
            }

            if ((last_button == 0 && button_status[11] == 0) || (mode != 3 && lead_follows == 0))
            {
                if (48 + scale[vibe][leads[lead_track][beat_count] - 1] + octave2*12 + key != note4)
                { 
                    MIDI.sendNoteOff(note4, 0, 5);

                    note4 = 48 + scale[vibe][leads[lead_track][beat_count] - 1] + octave2*12 + key;
                }
            }
            
            
            //play drums
            for(int i = 0; i < 3; i++)
            {
                if (mode == 4 && button_status[i+1] == 1)
                {
                    table[4-i][9] = 1;
                    table[4-i][9] = 1;
                        if (beat_count % 4 == 0)
                        {
                            MIDI.sendNoteOn(i, 4, 10);
                        }
                        else
                        {
                            MIDI.sendNoteOn(i, 1, 10);
                        }
                }
                else if (mode != 4 || button_status[4 + i] == 0)
                { 
                    if (drums[drum_track][2-i][beat_count%drum_length] == 1 && drum_mute == 0)
                    {
                        table[4-i][9] = 1;
                        if (beat_count % 2 == 0)
                        {
                            MIDI.sendNoteOn(i, 4, 10);
                        }
                        else
                        {
                            MIDI.sendNoteOn(i, 1, 10);
                        }
                
                    }
                }
            }

            // play sample
            if (sample_duration1 > 0)
            {
                if (beat_count%sample_duration1 == sample_start1)
                {
                  MIDI.sendNoteOn(sample1, 127, 7);
                }
                if (beat_count % sample_duration2 == sample_start2)
                {
                  MIDI.sendNoteOn(sample2, 127, 8);
                }
            }

            //play notes
              if (chords[chord_track][beat_count] > 0 && chord_mute == 0)
                    {
                        MIDI.sendNoteOn(note1, 127, 2);
                        MIDI.sendNoteOn(note2, 127, 3);
                        MIDI.sendNoteOn(note3, 127, 4);
                    }
            //play leads
              if (leads[lead_track][beat_count] > 0 && lead_mute == 0)
                    {
                        MIDI.sendNoteOn(note4, 127, 5);
                    }
              
        #endif
        break;
    }
  
    beat_count++;
    if (beat_count == max_beats)
    {
        beat_count = 0;
    }
}

void button_check()
{
    //check keypad
    for(int i = 0; i < 3; i++)
    {
        digitalWrite(colPins[i], LOW);
        for(int j = 0; j < 4; j++)
        {
            button_status[3*j + i + 1] = !digitalRead(rowPins[j]);
            if (button_status[3*j + i + 1] != button_status_last[3*j + i + 1])
            {
                if ((millis() - debounce_time[3*j + i + 1]) > debounce_delay)
                {
                    button_update(3*j + i + 1, button_status[3*j + i + 1]);
                    button_status_last[3*j + i + 1] = button_status[3*j + i + 1];
                    debounce_time[3*j + i + 1] = millis();
                }
            }
        }
        digitalWrite(colPins[i], HIGH);
    }
    
    //check follow-on
    button_status[0] = !digitalRead(followPin);
    if (button_status[0] != button_status_last[0])
    {
        if ((millis() - debounce_time[0]) > debounce_delay)
        {
            button_update(0, button_status[0]);
            button_status_last[0] = button_status[0];
            debounce_time[0] = millis();
        }
    }

    //check coin
    button_status[13] = digitalRead(coinPin);
    if (button_status[13] != button_status_last[13])
    {
        if ((millis() - debounce_time[13]) > debounce_delay*2)
        {
            button_update(13, button_status[13]);
            button_status_last[13] = button_status[13];
        }
    }
}

void check_record()
{
    int record_beat = beat_count - 1;
    if (record_beat == -1)
    {
        record_beat = 63;
    }
    
    switch (mode)
    {
        case 2:
            if(button_status[11] == 1)
            {
                chords[chord_track][record_beat] = last_button;
            }
        break;

        case 3:
            if(button_status[11] == 1)
            {
                leads[lead_track][record_beat] = last_button;
            }
        break;

        case 4:
            for (int i = 1; i < 4; i++)
            {
                if(button_status[11] == 1 && button_status[i] == 1)
                {
                    drums[drum_track][3-i][record_beat%drum_length] = 1;              
                }    
                else if (button_status[11] == 1 && button_status[3+i] == 1) 
                {
                    drums[drum_track][3-i][record_beat%drum_length] = 0;
                }
            }

    }
}


void phone_number_check()
{
    bpm = 100*phone_number[0] +  10*phone_number[1] +  phone_number[2];
    
    if (bpm > max_bpm)
    {
        bpm = max_bpm;
    } 
    if (bpm < min_bpm)
    {
        bpm = min_bpm;
    } 
    bpm_delay = 7500000/bpm;

    key = phone_number[3];
    if (key > 7)
    {
        key = 7;
    } 

    if (phone_number[4] == 0)
    {
        vibe = 0; 
    }
    else
    {
        vibe = 1;
    }

    drum_preset1 = phone_number[6];    
    drum_preset2 = phone_number[7];    
    chord_preset = phone_number[5];

    load_preset(chord_preset);
    load_drums(drum_preset1, drum_preset2);

    sample1 = pgm_read_word(&preset_settings[chord_preset][3]);
    sample_start1 = pgm_read_word(&preset_settings[chord_preset][4]);
    sample_duration1 = pgm_read_word(&preset_settings[chord_preset][5]);
    
    sample2 = pgm_read_word(&preset_settings[chord_preset][6]);
    sample_start2 = pgm_read_word(&preset_settings[chord_preset][7]);
    sample_duration2 = pgm_read_word(&preset_settings[chord_preset][8]);

    drum_mute = pgm_read_word(&preset_settings[chord_preset][0]);
    chord_mute = pgm_read_word(&preset_settings[chord_preset][1]);
    lead_mute = pgm_read_word(&preset_settings[chord_preset][2]);

}

/*void load_preset(int in, int pr, int tr)
{ // in is the instrument (0 for drums, 1 for chords), pr is the preset (1-9 or 0 for nothing, tr is the track (0 or 1).
    if (pr > 0)
    {
        if (in == 0)
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < drum_length; j++)
                {
                    drums[tr][i][j] = pgm_read_byte(&drum_presets[pr-1][i][j]);
                }
            }
        }

        if (in == 1)
        {
            for (int i = 0; i < max_beats; i++)
            {
                chords[0][i] = pgm_read_word(&chord_presets[pr-1][0][i/2]);
                chords[1][i] = pgm_read_word(&chord_presets[pr-1][1][i/2]);
                
                leads[0][i] = pgm_read_word(&lead_presets[pr-1][0][i/2]);
                leads[1][i] = pgm_read_word(&lead_presets[pr-1][1][i/2]);
            }
        }
    }
}
*/

void button_update(int button, bool state)
{  
    
    if(button_status[0] == 1 && state == 1)
    {
        if(button == 1)
        {
            mode = 4;
            table[4][11] = 1;
            table[4][12] = 0;
        }
        if(button == 2)
        {
            mode = 2;
            table[4][11] = 0;
            table[4][12] = 1;
        }
        if(button == 3)
        {   
            mode = 3;
            table[4][11] = 1;
            table[4][12] = 1;
        }
        if(button == 4)
        {
            drum_mute = !drum_mute;
        }
        if(button == 5)
        {
            chord_mute = !chord_mute;
        }
        if(button == 6)
        {
            lead_mute = !lead_mute;
        }
        if(button == 7)
        {
            drum_track = !drum_track;
            table[4][13] = !drum_track;
            table[4][14] = drum_track;
        }
        if(button == 8)
        {
            chord_track = !chord_track;
            table[5][11] = !chord_track;
            table[5][12] = chord_track;
        }
        if(button == 9)
        {
            lead_track = !lead_track;
            table[5][13] = !lead_track;
            table[5][14] = lead_track;
        }
        if(button == 10)
        {
            key--;
        }
        if(button == 11)
        {
            key++;
        }
        if(button == 12)
        {
            digitalWrite(solenoid_1, state);
            reset();
        }

        mode_shift = button;
    }
    else
    {       
        switch (mode) {
            case 0: //if coin detected, move to mode 1
                if (state == 1 && button == 13)
                {
                    mode = 1;
                    #if (debug == 0)
                    MIDI.sendNoteOn(0, 127, 6);
                    clear_table();
                    #endif
                }
            break;
            
            case 1: //waits for the phone number to be keyes in
                if ((state == 1 && phone_number_index < 8)&&(button > 0 && button < 13))
                {
                    phone_number[phone_number_index] = button;
                    if (phone_number[phone_number_index] == 11)
                    {
                        phone_number[phone_number_index] = 0;
                    }
                    table[3][phone_number_index + 4] = 1;
                    update_table();
                    phone_number_index++;
                    if (phone_number_index == 8)
                    {
                        clear_table();
                        phone_number_check();
                    }

                note5 = button;
                #if (debug == 0)
                MIDI.sendNoteOn(note5, 127, 6);
                #endif
                }
                else
                {
                #if (debug == 0)
                MIDI.sendNoteOff(note5, 0, 6);
                #endif
                }


            break;

            case 2: //buttons for the 2 synth modes
            case 3:
                switch (button) {
                    case 9:
                        if (button_status[11] == 0)
                        {
                            if (mode == 2 && state == 1)
                            {
                                octave1++;
                                if (octave1 > 2)
                                {
                                    octave1 = 2;
                                }
                            }
                            
                            if (mode == 3 && state == 1)
                            {
                                octave2++;
                                if (octave2 > 2)
                                {
                                    octave2 = 2;
                                }
                            }
                        }
                    break;
            
                    case 10:
                        if (button_status[button] == 1 && button_status[11] == 0)
                        {
                            if (mode == 2)
                            {
                                lead_follows = !lead_follows;
                            }
                            else if (chord_mute == 1)
                            {
                                #if (debug == 0)
                                MIDI.sendNoteOn(note1, 127, 2);
                                MIDI.sendNoteOn(note2, 127, 3);
                                MIDI.sendNoteOn(note3, 127, 4);
                                chord_visualisation(last_button, 1);
                                #endif
                            }
                        }
                      if (button_status[button] == 0 && button_status[11] == 0)
                      {
                          if (mode == 3 && chord_mute == 1)
                          {
                                #if (debug == 0)
                                MIDI.sendNoteOff(note1, 0, 2);
                                chord_visualisation(last_button, 0);
                                #endif
                          }
                      }
                    break;

                    case 12:
                        if (button_status[11] == 0)
                        {
                            if (mode == 2 && state == 1)
                            {
                                octave1--;
                                if (octave1 < -2)
                                {
                                    octave1 = -2;
                                }
                            }
                            
                            if (mode == 3 && state == 1)
                            {
                                octave2--;
                                if (octave2 < -2)
                                {
                                    octave2 = -2;
                                }
                            }
                        }
                    break;
            
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:

                        if (mode == 2)
                        {
                            chord_visualisation(button, state);
                        }
                        else
                        {
                            note_visualisation(button, state);
                        }

                        if (state == 1)
                        {
                            
                            #if (debug == 0)
                            if (mode == 2)
                            {
                                note1 = 48 + scale[vibe][button - 1] + octave1*12 + key;
                                note2 = 48 + scale[vibe][button + 1] + octave1*12 + key;
                                note3 = 48 + scale[vibe][button + 3] + octave1*12 + key;
                                MIDI.sendNoteOn(note1, 127, 2);
                                MIDI.sendNoteOn(note2, 127, 3);
                                MIDI.sendNoteOn(note3, 127, 4);

                                if (lead_follows == 1)
                                {
                                note4 = 48 + scale[vibe][button - 1] + octave2*12 + key;
                                MIDI.sendNoteOn(note4, 127, 5);
                                }
                            }
                            
                            if (mode == 3)
                            {
                                note1 = 48 + scale[vibe][button - 1] + octave1*12 + key;
                                note2 = 48 + scale[vibe][button + 1] + octave1*12 + key;
                                note3 = 48 + scale[vibe][button + 3] + octave1*12 + key;
                                note4 = 48 + scale[vibe][button - 1] + octave2*12 + key;
                                MIDI.sendNoteOn(note4, 127, 5);
                            }
                            #endif

                            last_button = button;
                        }
                        else
                        {
                            if (button == last_button)
                            {
                                #if (debug == 0)
                                if (mode == 2)
                                {
                                    MIDI.sendNoteOff(note1, 0, 2);
                                    //MIDI.sendNoteOff(note2, 0, 3);
                                    //MIDI.sendNoteOff(note3, 0, 4);
                                }
                                else
                                {
                                    MIDI.sendNoteOff(note4, 0, 5);
                                }
                                #endif

                                last_button = 0;
                            }
                        }

                    break;
                }
            break;

            case 4:
                switch (button) {
                    case 7:
                        if (button_status[0] == 0 && state == 1) 
                        {
                            if (drum_track == 0)
                            {
                                drum_preset1--;
                                if (drum_preset1 < 1)
                                {drum_preset1 = 9;}
                            }
                            else
                            {
                                drum_preset2--;
                                if (drum_preset2 < 1)
                                {drum_preset2 = 9;}
                            }
                            load_drums(drum_preset1, drum_preset2);
                        }
                    break;

                    case 8:
                        if (button_status[0] == 0 && state == 1) 
                        {
                            if (drum_track == 0)
                            {
                                drum_preset1++;
                                if (drum_preset1 > 9)
                                {drum_preset1 = 1;}
                            }
                            else
                            {
                                drum_preset2++;
                                if (drum_preset2 > 9)
                                {drum_preset2 = 1;}
                            }
                            load_drums(drum_preset1, drum_preset2);
                        }
                    break;

                    case 9:
                        if (state == 1)
                        {
                            bpm++;
                            bpm_delay = 7500000/bpm;
                        }
                    break;

                    case 10:
                        if (state == 1)
                        {
                            last_beat = micros();
                            beat_count = 0;
                            on_or_off = 0;
                        }
                    break;

                    case 12:
                        if (state == 1)
                        {
                            bpm--;
                            bpm_delay = 7500000/bpm;
                        }
                    break;

                }
            break;
        
    }
  }
}

void update_screen()
{
    IIC_start();
    IIC_send(0x40);// set the address plus 1 automatically
    IIC_end();
    IIC_start();
    IIC_send(0xc0);// set the initial address as 0
    for (int i = 15; i > -1; i--)
    {
        IIC_send(table[6][i]+2*table[5][i]+4*table[4][i]+8*table[3][i]+16*table[2][i]+32*table[1][i]+64*table[0][i]);
    }
    IIC_end();

    IIC_start();
    IIC_send(0x8A);// set the brightness display
    IIC_end();
}

void IIC_start()
{
    digitalWrite(IIC_SCL, LOW);
    delayMicroseconds(3);
    digitalWrite(IIC_SDA, HIGH);
    delayMicroseconds(3);
    digitalWrite(IIC_SCL, HIGH);
    delayMicroseconds(3);
    digitalWrite(IIC_SDA, LOW);
    delayMicroseconds(3);
}

void IIC_send(unsigned char send_data)
{
    for (char i = 0; i < 8; i++) 
    {
        digitalWrite(IIC_SCL, LOW);
        delayMicroseconds(3);
        if (send_data & 0x01)
        {
            digitalWrite(IIC_SDA, HIGH);
        }
        else
        {
            digitalWrite(IIC_SDA, LOW);
        }
        delayMicroseconds(3);
        digitalWrite(IIC_SCL, HIGH);
        delayMicroseconds(3);
        send_data = send_data >> 1;
    }
}

void IIC_end()
{
    digitalWrite(IIC_SCL, LOW);
    delayMicroseconds(3);
    digitalWrite(IIC_SDA, LOW);
    delayMicroseconds(3);
    digitalWrite(IIC_SCL, HIGH);
    delayMicroseconds(3);
    digitalWrite(IIC_SDA, HIGH);
    delayMicroseconds(3);
}

void note_visualisation(int note, bool state)
{
    if (mode > 1)
    {
        table[3][note] = state;
    }
}

void chord_visualisation(int note, bool state)
{
    if (mode > 1)
    {
        if (state == 1)
        {
            for(int i = 1; i < 6; i++)
            {
              for (int j = 1; j < 8; j++)
              {
                  if (i != 3)
                  table[i][j] = 0;
              }
            }
        
        }
        if (note > 0)
        {
        // visualisation of the root note being played
            for(int i = 1; i < 6; i++)
            {
              if (i != 3)
              {
                  table[i][note] = state;
              }
            }

            // visualisation of the other notes being played
            for(int i = 2; i < 5; i++)
            {
              int t = note + 2;
              if (t > 7)
              {
                t = t - 7;
              }

              int f = note + 4;
              if (f > 7)
              {
                f = f - 7;
              }
              
              if (i != 3)
              {
                  table[i][t] = state;
                  table[i][f] = state;
              }
            }
        }
    }
}

