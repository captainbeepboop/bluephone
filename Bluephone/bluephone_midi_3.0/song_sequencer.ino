#include <MIDI.h>
#include "sequences.h"
MIDI_CREATE_DEFAULT_INSTANCE();

#define debug 0

//sample stuff
uint8_t sample_number = 0;
uint8_t sample_length = 0;

//hardware stuff
bool button_status[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
bool button_status_last[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned long debounce_time[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const uint8_t debounce_delay = 50;
const uint8_t rowPins[4] = {6, 7, 8, 9}; 
const uint8_t colPins[3] = {3, 4, 5}; 
#define followPin 10
#define solenoid_1 A2
#define solenoid_2 A0
#define coin_LED A1
#define coinPin 13

//control stuff

uint8_t mode = 2;
uint8_t phone_number_index = 0;
uint8_t phone_number[] = {0,0,0,0,0,0,0,0};
bool mutes[] = {1,0,0,0,0};

//beat stuff
uint8_t bpm = 120;
unsigned long bpm_delay_micros = 5000000/bpm;
unsigned long last_beat_micros = 0;
uint8_t beat_count = 0;

//sequence stuff
uint8_t sequence_number = 0;
int sequence_step = 0;
int sequence_stacks[2][8] = {{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}}; // 0 is repeats, 1 is jump
bool sequence_play = 0;
uint8_t sequence_timing[] = {0,0};
uint8_t bass_mode = 1;
uint8_t last_bass = 0;
uint8_t sequence_pending = 0;

//riff stuff
uint8_t riff_number = 0;
int riff_step = 0;
bool riff_play = 0;
uint8_t riff_timing[] = {0,0};
uint8_t last_note[] = {0,0}; 

//note stuff
#define a_note 33
const uint8_t scale[] = {0, 2, 3, 5, 7, 8, 10};
uint8_t last_chord[3] = {0,0,0}; //ROOT, TYPE OF CHORD, 0 for SEQUENCE, 1 FOR BUTTON
uint8_t key_centre = 45;
bool vibe = 0;
bool bass_octave = 1;
bool chord_octave = 1;
uint8_t lead_octave = 2;

//drum stuff
uint8_t drumbeat_number = 0;
uint8_t drum_timing = 4;
bool drum_play = 0;
uint8_t drum_presets[] = {1, 2};
bool drum_preset_select = 0;

//MIDI stuff
#define chord_channel 2
#define bass_channel 4
#define riff_channel 3
#define drum_channel 10

//beep test stuff
uint8_t beep_test_count[2] = {0,0};
bool beep_test_on = 0;
#define beep_test_number_of_levels 8
const uint8_t beep_test_laps_per_level[] = {1, 4, 4, 4, 4, 4, 4, 4, 4};
const uint8_t beep_test_bpm_per_level[] = {25, 80, 100, 120, 140, 160, 180, 200, 220};

unsigned long delayed_sample_times[] = {0,0,0};
uint8_t delayed_sample_numbers[] = {0,0,0};

void setup()
{

    #if (debug == 0)
    MIDI.begin(MIDI_CHANNEL_OMNI); 
    #else
    Serial.begin(115200);
    #endif

    MIDI.sendNoteOn(0,3,3);

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


     MIDI.sendControlChange(47, 127, bass_channel);

     //load_drum_sequence(1);
     load_drum_sequence(1);
     //load_sequence(3);   
}

void loop()
{
    //temporary beat maker
    if (micros() - last_beat_micros > bpm_delay_micros)
    {
        last_beat_micros = last_beat_micros + bpm_delay_micros;
        beat();
    }
    button_check();
}

void beat()
{    
    play_delayed_sample();
    
    if (sequence_pending == 2 && beat_count % 48 == 0)
    {
        beat_count = 96;
        #if (debug == 0)
        MIDI.sendNoteOn(0, 3, 3);
        #endif
        sequence_pending = 1;
    }
    else if (sequence_pending == 1)
    {
       if (beat_count == 120)
       {
            #if (debug == 0)
            MIDI.sendNoteOff(0, 3, 3);
            #endif
       }
       if (beat_count == 144)
       {
            #if (debug == 0)
            MIDI.sendNoteOn(0, 3, 3);
            #endif
       }
       if (beat_count == 168)
       {
            #if (debug == 0)
            MIDI.sendNoteOff(0, 3, 3);
            #endif
       }
    }
    
    if (beat_count == 192)
    {
        beat_count = 0;
        if (sequence_pending == 1)
        {
            sequence_pending = 0;
            #if (debut == 0)
            MIDI.sendNoteOff(0, 3, 3);
            #endif
        }
    }
    
    if (sequence_play == 1)
    {
        play_sequence();
    }

    if (mutes[3] == 0)
    {
        generate_bass();
    }

    if (riff_play == 1)
    {
        play_riff();
    }
    
    if (drum_play == 1)
    {
        play_drum_sequence();
    }

    beat_count++;
}


//--------------------BUTTON FUNCTIONS---------------------

void reset()
{
    mode = 4;
    MIDI.sendNoteOn(0,3,3);
    sequence_play = 0;
    drum_play = 0;
    riff_play = 0;
    phone_number_index = 0;
    for (int i = 0; i < 5; i++)
    {
        mutes[i] = 1;
    }
    beep_test_count[0] = 0;
    beep_test_count[1] = 0;
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
            button_status_last[0] = button_status[0];
            debounce_time[0] = millis();
            int value = button_status[0];

        }
    }

    //check coin
    button_status[13] = digitalRead(coinPin);
    if (button_status[13] != button_status_last[13])
    {
        if ((millis() - debounce_time[13]) > debounce_delay*2)
        {
            //coin update function
            button_status_last[13] = button_status[13];
            
        }
    }

}

void button_update(uint8_t button, bool state)
{
    if (button_status[0] == 1)
    {
        if (state == 1)
        {
            follow_on_button_update(button);
        }
    }
    else
    {
        switch(mode)
        {
            case 1:
                if(state == 1)
                {
                    drum_button_update(button, state);
                }
            break;
            case 2:
                chord_button_update(button, state);
            break;
            case 3:
                riff_button_update(button, state);
            break;
            case 4:
                dial_button_update(button, state);
            break;
            case 5:
                if(state == 1 && button < 10)
                play_sample(button+2);
            break;
        }
    }
}

void dial_button_update(uint8_t button, bool state)
{
   
    if (state == 1)
    {
        if (phone_number_index < 8)
        {
            if (button == 11)
            {
                phone_number[phone_number_index] = 0;
            }
            else if (button == 12)
            {
                phone_number[phone_number_index] = 11;
            }
            else
            {
                phone_number[phone_number_index] = button;
            }
            #if (debug == 0)
            MIDI.sendNoteOn(button, 3, 3);
            #endif
            phone_number_index++;
        }
    }
    else
    {
        if (phone_number_index > 0)
        {
            #if (debug == 0)
            MIDI.sendNoteOff(button, 3, 3);
            #endif
        }
        if (phone_number_index == 8)
        {
            phone_number_index = 0;
            decode_phone_number();
        }
    } 
}

void decode_phone_number()
{    
    // 0 is encoded as 0, * is 10, # is 11
    
    //digits 0-2 are bpm - 10, 11, 12 count as 0
    int counter = 0;
    for (int i = 0; i < 3; i++)
    {
        if (phone_number[i] < 10)
        {
            counter = counter + phone_number[i]*pow(10, 2-i);
        }
    }

    bpm = counter;
    if (bpm > 250)
    {
        bpm = 250;
    }
    if (bpm < 20)
    {
        bpm = 20;
    }
    bpm_delay_micros = 5000000/bpm;

    //digits 3-4 are the sequence is base 12. # is 11. All * are major. (120-131) All # are minor. (132-143)

    uint8_t sequence_number = 12*phone_number[3] + phone_number[4];

    if (sequence_number < number_of_sequences)
    {
        load_sequence(sequence_number);
    }
    else if (phone_number[3] == 10)
    {
        vibe = 0;
        key_centre = 45 + phone_number[4];
        for (int i = 0; i < 4; i++)
        {
            mutes[i] = 0;
        }
    }
    else if (phone_number[3] == 11)
    {
        vibe = 1;
        key_centre = 45 + phone_number[4];
        for (int i = 0; i < 4; i++)
        {
            mutes[i] = 0;
        }
    }

    //digits 5-6 are drum starters
    drum_presets[0] = phone_number[5];
    drum_presets[1] = phone_number[6];
    drum_preset_select = 0;
    load_drum_sequence(drum_presets[drum_preset_select]);
    mode = 2;

    load_sample(phone_number[7]);
    //digit 7 is sample

}

void follow_on_button_update(uint8_t button)
{
    switch(button)
    {
        case 1:
        case 2:
        case 3:
            mode = button;
        break;
        case 4:
        case 5:
        case 6:
            mutes[button-4] = !mutes[button-4];
        break;
        case 7:
            drum_preset_select = !drum_preset_select;
            load_drum_sequence(drum_presets[drum_preset_select]);
        break;
        case 8:
            stop_note(last_bass, bass_channel);
            mutes[3] = !mutes[3];
        break;
        case 9:
            sequence_stacks[0][0] = 1;
        break;
        case 10:
            if (sample_number > 0)
            {
                mutes[4] = !mutes[4];
                stop_sample();
            }
        break;
        case 11:
            mode = 5;
        break;  
        case 12:
            reset();
        break;
    }
}

void drum_button_update(uint8_t button, bool state)
{
    switch (button)
    {
        case 7:
            play_sample(sample_number);
        break;
        case 8:
            drumbeat_number++;
            if (drumbeat_number == number_of_drums)
            {
                drumbeat_number == 0;
            }
            load_drum_sequence(drumbeat_number);
        break;
        case 9:
            bpm++;
            bpm_delay_micros = 5000000/bpm;
        break;
        case 10:
            stop_sample();
        break;
        case 11:
            drumbeat_number--;
            if (drumbeat_number < 0)
            {
                drumbeat_number == number_of_drums;
            }
            load_drum_sequence(drumbeat_number);
        break;
        case 12:
            bpm--;
            bpm_delay_micros = 5000000/bpm;
        break;
    }
}

void chord_button_update(uint8_t button, bool state)
{
    switch (button)
    {
        case 9:
            if (state == 1)
            {
                stop_note(last_chord[0], chord_channel);
                chord_octave = !chord_octave;
            }
        break;
        case 10:
            if (state == 1)
            {
                stop_note(last_bass, bass_channel);
                bass_mode++;
                if (bass_mode > 2)
                {
                    bass_mode = 1;
                }
            }
        break;
        case 11:
            if (state == 1)
            {
                stop_note(last_bass, bass_channel);
                mutes[3] = !mutes[3];
            }
        break;
        case 12:
            if (state == 1)
            {
                stop_note(last_bass, bass_channel);
                bass_octave = !bass_octave;
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
            if (state == 1)
            {
                play_chord(button_to_note(button), button_to_chord_type(button));
                last_chord[2] = button;
            }
            else if (last_chord[2] == button)
            {
                stop_note(last_chord[0],chord_channel);
                last_chord[2] = 0;
            };
        break;
    }
}


void riff_button_update(uint8_t button, bool state)
{
    switch (button)
    {
        case 9:
            if (state == 1)
            {
                lead_octave++;
                if (lead_octave > 3)
                {
                    lead_octave = 3;
                }
            }
        break;
        case 12:
            if (state == 1)
            {
                if (lead_octave > 0)
                {
                    lead_octave--;
                }
            }
        break;
        default:
            if (state == 1)
            {
                play_note(button_to_note(button), riff_channel); 
                last_note[1] = button;
            }
            else if (last_note[1] == button)
            {
                stop_note(last_note[0],riff_channel);
                last_note[1] = 0;
            };
        break;
    }
}

uint8_t button_to_note(uint8_t button)
{
    uint8_t result = key_centre - 3*!vibe + scale[(button-1+2*!vibe)%7] + 12*((button-1+2*!vibe)/7);
    return result;
}

uint8_t button_to_chord_type(uint8_t button)
{
    uint8_t number = (button-1+2*!vibe)%7;
    switch (number)
    {
        case 2:
        case 5:
        case 6:
            return 1;
        break;

        case 0:
        case 3:
        case 4:
            return 2;
        break;

        case 1:
            return 3;
        break;
    }
}

//------------------BEEP TEST FUNCTIONS-------------------------

void beep_test_lap()
{
    if (beep_test_count[0] > beep_test_number_of_levels)
    {
        play_sample(13);
        beep_test_on = 0;
        mode = 4;
        MIDI.sendNoteOn(0,3,3);
        sequence_play = 0;
        riff_play = 0;
        return;
    }
    if (beep_test_count[0] == 0)
    {
        play_sample(12);
        bpm = beep_test_bpm_per_level[beep_test_count[0]];
        bpm_delay_micros = 5000000/bpm;
    }
    else if (beep_test_count[1] == 0)
    {
        play_sample(14);
        delay_sample(beep_test_count[0] + 15, 2000);
        delay_sample(beep_test_count[1] + 16, 3000);
        bpm = beep_test_bpm_per_level[beep_test_count[0]];
        bpm_delay_micros = 5000000/bpm;
    }
    else
    {
        play_sample(15);
        delay_sample(beep_test_count[0] + 15, 1500);
        delay_sample(beep_test_count[1] + 16, 2500);
    }

    beep_test_count[1]++;
    if (beep_test_count[1] == beep_test_laps_per_level[beep_test_count[0]])
    {
        beep_test_count[1] = 0;
        beep_test_count[0]++;
    }
}

void delay_sample(uint8_t number, unsigned long time)
{
    for (int i = 0; i < 3; i++)
    {
        if (delayed_sample_numbers[i] == 0)
        {
            delayed_sample_numbers[i] = number;
            delayed_sample_times[i] = millis()+time;
            return;
        }
    }
}

void play_delayed_sample()
{
    if (delayed_sample_numbers[0] > 0 && delayed_sample_times[0] < millis())
    {
        play_sample(delayed_sample_numbers[0]);
        delayed_sample_numbers[0] = delayed_sample_numbers[1]; 
        delayed_sample_numbers[1] = delayed_sample_numbers[2];
        delayed_sample_numbers[2] = 0;
        delayed_sample_times[0] = delayed_sample_times[1]; 
        delayed_sample_times[1] = delayed_sample_times[2];
        delayed_sample_times[2] = 0;
    }
}

//------------------SAMPLE FUNCTIONS-------------------------

void load_sample(uint8_t number)
{
    sample_number = number;
    sample_length = sample_lengths[number-1];
}

void stop_sample()
{
    #if (debug == 0)
    MIDI.sendNoteOn(0,4,drum_channel);
    #endif
}

void play_sample(uint8_t number)
{
    uint8_t first_half = ((number+64) >> 4)*8;
    uint8_t second_half = ((number+64) & B00001111)*8 + 4;
    #if (debug == 0)
    MIDI.sendNoteOn(first_half,second_half,drum_channel);
    #endif
}

void load_drum_sequence(uint8_t number)
{
    drumbeat_number = number;
    drum_timing = 48/string_to_int(drumbeat_pointers[drumbeat_number],0,2);
    drum_play = 1;
}

void play_drum_sequence()
{   
    if (beat_count % drum_timing == 0)
    {
        uint8_t drum_byte = 0;
        uint8_t drum_accent = 1;

        if (mutes[4] == 0 && sample_number > 0)
        {
            drum_byte = (sample_number >> 4)*8;
            drum_accent = (sample_number & B00001111)*8 + 1;

            if ((beat_count)%sample_length == 0)
            {
                bitSet(drum_accent, 2);
            }
        }

        for (int i = 0; i < 3; i++)
        {                                            
            uint8_t step = (beat_count/drum_timing) % (48/drum_timing) + 3 + i*(48/drum_timing+1); //FINDS THE BIT OF THE DRUM TAB TO READ
            if (pgm_read_byte(drumbeat_pointers[drumbeat_number]+ step) > 64 && mutes[0] == 0)
            {
                bitSet(drum_byte, 2-i);
                if (pgm_read_byte(drumbeat_pointers[drumbeat_number]+ step) < 91)
                {
                    bitSet(drum_accent, 1);
                }
            }
            else if ((mode == 1 && button_status[3-i] == 1)&&button_status[0] == 0)
            {
                bitSet(drum_byte, 2-i);
            }
            if ((mode == 1 && button_status[6-i] == 1)&&button_status[0] == 0)
            {
                bitClear(drum_byte, 2-i);
            }
        }
        
        if (drum_byte > 0 || drum_accent > 0)
        {
            play_drum(drum_byte, drum_accent);
        }
    }

}

void play_drum(uint8_t drum, uint8_t accent)
{
    #if (debug == 0)
    MIDI.sendNoteOn(drum, accent, drum_channel);
    #endif
}


//-------------------SEQUENCE FUNCTIONS-------------------
void load_sequence(uint8_t number)
{
    sequence_pending = 2;
    sequence_number = number;
    sequence_timing[0] = 48/string_to_int(sequence_pointers[sequence_number],0,2);
    sequence_timing[1] = string_to_int(sequence_pointers[sequence_number],3,2);
    key_centre = string_to_root(sequence_pointers[sequence_number], 6);
    vibe = 0;
    if (pgm_read_byte(sequence_pointers[sequence_number]+7) == 'm')
    {
        vibe = 1;
    }
    
    sequence_step = 7;
    sequence_play = 1;
}

void play_sequence()
{
    if ((beat_count % sequence_timing[0] == 0 && sequence_pending == 0))
    {
        uint8_t root = 0;
        uint8_t type = 0;

        for (bool loop = 1; loop == 1;)
        {
            sequence_step++;
            
            char command = pgm_read_byte(sequence_pointers[sequence_number]+sequence_step); 

            if (command == '!')
            {
               loop = 0;
               sequence_play = 0;
            }

            if (command > 64 && command < 72) // NOTE
            {
                root = string_to_root(sequence_pointers[sequence_number], sequence_step);
                type = string_to_chord_type(sequence_pointers[sequence_number], sequence_step);
            }

            if (command == 'X' || command == '.')
            {
                loop = 0;
            }

            if (command == '*')
            {
                load_riff(string_to_int(sequence_pointers[sequence_number], sequence_step+1, 2));
                sequence_step = sequence_step + 2;
            }

            if (command == '$')
            {
                play_sample(string_to_int(sequence_pointers[sequence_number], sequence_step+1, 2));
            }

            if (command == '?')
            {
                sequence_play = 0;
                riff_play = 0;
                loop = 0;
                load_sequence(string_to_int(sequence_pointers[sequence_number], sequence_step+1, 2));
            }

            if (command == '%')
            {
                bpm = string_to_int(sequence_pointers[sequence_number], sequence_step+1, 3);
                bpm_delay_micros = 5000000/bpm;
            }

            if (command == '^')
            {
                bass_mode = string_to_int(sequence_pointers[sequence_number], sequence_step+1, 1);
    
            }

            if (command == '&')
            {
                load_drum_sequence(string_to_int(sequence_pointers[sequence_number], sequence_step+1, 2));
            }

            if (command == '>')
            {
                for (uint8_t i = 0; i < 5; i++)
                {
                    mutes[i] = string_to_int(sequence_pointers[sequence_number], sequence_step+1+i, 1);
                }
            }

            if (command == '<')
            {
                beep_test_lap();
            }
            
            else if (command > 47 && command < 58) // SET UP REPEAT
            {
                if (command == '0')
                {
                    push_stack(255, sequence_step);
                }
                else if (pgm_read_byte(sequence_pointers[sequence_number]+sequence_step+1) == '(')
                {
                    push_stack(command-48, sequence_step);
                }
                else
                {
                    push_stack(10*(command-48)+pgm_read_byte(sequence_pointers[sequence_number]+sequence_step)-48, sequence_step);
                    sequence_step++;
                }
            }
            else if (command == ')') // END SECTION, REPEAT
            {
                repeat();
            }
            if ((command == ' ' || command == ')') && root > 0) //PLAY NOTE
            {
                if(last_chord[2]==0)
                {
                    if (mutes[1] == 0)
                    {
                        play_chord(root, type);
                    }
                }
                loop = 0;
            }
        }
}
    if ((beat_count % sequence_timing[0] == sequence_timing[1] && last_chord[2] == 0)&& pgm_read_byte(sequence_pointers[sequence_number]+sequence_step+1) != '.')
    {
        if (mutes[1] == 0)
        {
            stop_note(last_chord[0],chord_channel);
        }
    }
}

void repeat()
{
    sequence_stacks[0][0]--;
    if (sequence_stacks[0][0] == 0)
    {
        pull_stack();
    }
    else
    {
        sequence_step = sequence_stacks[1][0];
    }
    //Serial.print("jumped to ");
    //Serial.print(sequence_step);
    //Serial.println();
}

void play_chord(uint8_t root, uint8_t type)
{
    
    
    #if (debug == 0)
    MIDI.sendNoteOff(last_chord[0],0,chord_channel);
    #endif

    last_chord[0] = root;
    last_chord[1] = type;
    #if (debug == 0)
    MIDI.sendNoteOn(last_chord[0] + 12*chord_octave, type, chord_channel);
    if (bass_mode == 1)
    {
        play_note(root, bass_channel);
    }
    #endif
}

void push_stack(int repeats, int jump)
{
    for (uint8_t i = 7; i > 0; i--)
    {
        sequence_stacks[0][i] = sequence_stacks[0][i-1];
        sequence_stacks[1][i] = sequence_stacks[1][i-1];
    }
    sequence_stacks[0][0] = repeats;
    sequence_stacks[1][0] = jump;

    //Serial.print("push");
    //Serial.println();

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            //Serial.print(sequence_stacks[i][j]);
            //Serial.print("-");
        }
        //Serial.println();
    }
}

int pull_stack()
{
    for (uint8_t i = 0; i < 7; i++)
    {
        sequence_stacks[0][i] = sequence_stacks[0][i+1];
        sequence_stacks[1][i] = sequence_stacks[1][i+1];
    }
    sequence_stacks[0][7] = 0;
    sequence_stacks[1][7] = 0;

    //Serial.print("pull");
    //Serial.println();

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            //Serial.print(sequence_stacks[i][j]);
            //Serial.print("-");
        }
        //Serial.println();
    }
}

void generate_bass()
{
    uint8_t arp = last_chord[0];
    switch(bass_mode)
    {
        case 2:
            if (beat_count % drum_timing == 0)
            {
                if (beat_count/drum_timing % 2 == 0)
                {
                    play_note(last_chord[0], bass_channel);
                }
                if (beat_count/drum_timing % 2 == 1)
                {
                    stop_note(last_chord[0], bass_channel);
                }
            }
        
        break;
        
        case 3:
            if (beat_count % drum_timing == 0)
            {
                play_note(last_chord[0], bass_channel);
            }
        break;

        case 4:
            if (beat_count % (2*drum_timing) == 0)
            {
                if (beat_count/drum_timing % 8 == 2 || beat_count % 8 == 4)
                {
                    arp = arp + 3;
                    if(last_chord[1] == 0)
                    {
                        arp = arp + 1;
                    }
                }
                else if (beat_count/drum_timing % 8 == 4)
                {
                    arp = arp + 7;
                    if(last_chord[1] == 2)
                    {
                        arp = arp - 1;
                    }
                }
                play_note(arp, bass_channel);
            }
        break;

        case 5:
            if (beat_count % drum_timing == 0)
            {
                if (beat_count/drum_timing % 4 == 1 || beat_count % 4 == 3)
                {
                    arp = arp + 3;
                    if(last_chord[1] == 0)
                    {
                        arp = arp + 1;
                    }
                }
                else if (beat_count/drum_timing % 4 == 2)
                {
                    arp = arp + 7;
                    if(last_chord[1] == 2)
                    {
                        arp = arp - 1;
                    }
                }
                play_note(arp, bass_channel);
            }
        break;
    }
}

//----------------RIFF FUNCTIONS----------------------------------

void load_riff(uint8_t number)
{
   riff_number = number;
    riff_timing[0] = 48/string_to_int(riff_pointers[riff_number],0,2);
    riff_timing[1] = string_to_int(riff_pointers[riff_number],3,2);
    riff_step = 5;
    riff_play = 1;
}

void play_riff()
{
    if (beat_count % riff_timing[0] == 0)
    {
        uint8_t note = 0;
        
        for (bool loop = 1; loop == 1;)
        {            
            riff_step++;
            
            char command = pgm_read_byte(riff_pointers[riff_number]+riff_step);
            
            if (command == '!')
            {
                loop = 0;
                riff_play = 0;
            }

            if (command > 64 && command < 72) // NOTE
            {
                note = string_to_root(riff_pointers[riff_number], riff_step);
            }

            if (command == 'X' || command == '.')
            {
                riff_step++;
                loop = 0;
            }

            if (command == ' ' && note > 0) //PLAY NOTE
            {
                if(last_note[1] == 0)
                {
                    if (mutes[2] == 0)
                    {
                        play_note(note, riff_channel);
                    }
                }
                loop = 0;
            }
        }
    }
    if ((beat_count % riff_timing[0] == riff_timing[1] && last_note[1] == 0)&& pgm_read_byte(riff_pointers[riff_number]+riff_step+1) != '.')
    {
        if (mutes[2] == 0)
        {
            stop_note(last_note[0],riff_channel);
        }
    }
}

void play_note(uint8_t note, uint8_t channel)
{
    if (channel == riff_channel)
    {
        
        uint8_t velocity = 1;
        if (mode == 4)
        {
            velocity = 3;
        }
        last_note[0] = note;
        #if (debug == 0)
        MIDI.sendNoteOn(last_note[0] + 12*lead_octave, velocity, channel);
        #endif
    }
    if (channel == bass_channel)
    {
        stop_note(last_bass, bass_channel);
        last_bass = note;
        #if (debug == 0)
        MIDI.sendNoteOn(last_bass+12*bass_octave-12, 127, bass_channel);
        #endif
    }
}

void stop_note(uint8_t note, uint8_t channel)
{
    #if (debug == 0)

    if (channel == chord_channel)
    {
        MIDI.sendNoteOff(note+12*chord_octave, 0, channel);
        //MIDI.sendNoteOff(note+12*bass_octave-12, 0, bass_channel);
    }
    else if (channel == bass_channel)
    {
        MIDI.sendControlChange(123, 0, bass_channel);
        //MIDI.sendNoteOff(note+12*bass_octave-12, 0, bass_channel);
    }
    else if (channel == riff_channel)
    {
        MIDI.sendNoteOff(note+12*lead_octave, 0, riff_channel);
    }

    #endif
}


//---------------STRING CONVERSION FUNCTIONS---------------------

uint8_t string_to_int(const char *pointer, int start, uint8_t length)
{
    uint8_t value = 0;
    int power = 1;
    for (int i = 0; i < length - 1; i++)
    {
        power = power * 10;
    }
    for (int i = start; i < length + start; i++)
    {
        value = value + (pgm_read_byte(pointer+i)-48)*power;
        power = power/10;
    }
    return value;
}

uint8_t string_to_root(const char *pointer, int step)
{
    uint8_t root = 0;
    for (int i = step; i < step + 5; i++)
    {
        char command = pgm_read_byte(pointer+i);
        if (command > 64 && command < 72) // NOTE
        {
            root = scale[(command - 65)%7] + a_note;
        }
        if (command == '#') //SHARP
        {
            root++;
        }
        if (command == '+') // UP OR DOWN AN OCTAVE
        {
            root = root+12;
        }
        if (command == '-') // UP OR DOWN AN OCTAVE
        {
            root = root-12;
        }
        if (command == ' ' || command == ')')
        {
            return root;
        }
    }
}

uint8_t string_to_chord_type(const char *pointer, int step)
{
    uint8_t type = 1;
    for (int i = step; i < step + 5; i++)
    {
        char command = pgm_read_byte(pointer+i);
        if (command == 'm') // Major is 1, minor is 2, diminished is 3
        {
            type = 2;
        }
        else if (command == 'd') 
        {
            type = 3;
        }
        else if (command == '5')
        {
            type = 4;
        }
        else if (command == ' ' || command == ')')
        {
            return type;
        }
    }
}