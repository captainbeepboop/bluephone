
#define max_beats 128
#define drum_length 16

int chord_preset = 0;
int drum_preset1 = 0;
int drum_preset2 = 0;

bool drum_mute = 0;
bool chord_mute = 0;
bool lead_mute = 1;

int sample1 = 0;
int sample_start1 = 0;
int sample_duration1 = 0;

int sample2 = 0;
int sample_start2 = 0;
int sample_duration2 = 0;

#define number_of_preset_settings 9

/////////////////////////////////////////PRESET SETTING//////////////////////////////////////////////

const int preset_settings[10][number_of_preset_settings] PROGMEM = 
{
    // drum mute / chord mute / lead mute / lead continuous / sample 1 / start beat 1 / duration 1 / sample 2 / start beat 2 / duration 2
    // sample options (1 - life is mysterious, 2 - alan turing)

    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    //1 - LIFE IS MYSTERIOUS AND AMAZING/CALL ME MAYBE
    {1, 1, 1, 1, 0, 64, 1, 0, 16},
    //2 - TURING
    {1, 1, 1, 2, 0, 32, 2, 0, 8},
    //3 - HEAVEN
    {1, 0, 1, 0, 0, 0, 0, 0, 0},
    //4 - KIDS and MUSHROOM
    {1, 1, 0, 0, 0, 0, 0, 0, 0},
    //5 - BELIEVE
    {1, 0, 0, 0, 0, 0, 0, 0, 0},
    //6 - ANIME
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    //7 -PLAN B
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    //8 - 
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    //9 - 
    {0, 0, 0, 0, 0, 0, 0, 0, 0}
};

/////////////////////////////////////////PRESETS//////////////////////////////////////////////////

const uint8_t blank[] PROGMEM = {128, 0, 255};

// LIFE IS MYSTERIOUS
const uint8_t c_life[] PROGMEM = {8, 1, 0, 6, 0, 4, 0, 5, 0, 255};
const uint8_t l_life[] PROGMEM = {2, 1, 1, 3, 5, 5, 5, 5, 8, 7, 7, 5, 3, 3, 3, 3, 3, 4, 4, 6, 0, 8, 0, 6, 0, 5, 5, 7, 9, 9, 9, 9, 9, 255};

// CALL ME MAYBE CHORUS
const uint8_t c_callmemaybe[] PROGMEM = {8, 1, 0, 5, 0, 4, 0, 5, 0, 255};
const uint8_t l_callmemaybe[] PROGMEM = {2, 0, 0, 5, 5, 2, 3, 5, 2, 0, 0, 0, 2, 2, 3, 7, 5, 0, 0, 0, 5, 7, 8, 7, 5, 0, 0, 0, 5, 7, 6, 6, 5, 0, 0, 5, 5, 2, 3, 5, 3, 0, 0, 0, 0, 2, 3, 7, 7, 7, 5, 0, 5, 7, 8, 7, 5, 0, 0, 0, 5, 7, 6, 6, 5, 255};

// TURING
const uint8_t c_turing[] PROGMEM = {8, 1, 0, 4, 0, 255};

// KIDS
const uint8_t c_kids[] PROGMEM = {8, 6, 0, 4, 0, 1, 0, 5, 0, 255};
const uint8_t l_kids[] PROGMEM = {2, 1, 1, 2, 2, 3, 3, 5, 5, 6, 6, 7, 6, 6, 5, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 3, 3, 5, 5, 6, 6, 7, 6, 6, 5, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 255};

// MUSHROOM
const uint8_t c_mushroom[] PROGMEM = {16, 1, 1, 1, 0, 4, 4, 4, 0, 255};
const uint8_t l_mushroom[] PROGMEM = {4, 1, 3, 5, 3, 1, 3, 5, 3, 1, 3, 5, 3, 1, 3, 5, 3, 4, 6, 8, 6, 4, 6, 8, 6, 4, 6, 8, 6, 4, 6, 8, 5, 255};

// BELIEVE
const uint8_t c_believe_v[] PROGMEM = {16, 1, 0, 3, 0, 4, 0, 5, 0, 255};
const uint8_t c_believe_c[] PROGMEM = {8, 1, 0, 5, 0, 2, 0, 4, 0, 1, 0, 5, 0, 2, 0, 6, 0, 255};

//HEAVEN
const uint8_t c_heaven_c[] PROGMEM = {4, 4, 0, 5, 0, 6, 6, 6, 0, 1, 1, 1, 0, 4, 4, 4, 0, 4, 0, 5, 0, 6, 6, 6, 0, 5, 5, 5, 5, 5, 5, 5, 0, 255};
const uint8_t c_heaven_v[] PROGMEM = {8, 1, 0, 6, 0, 5, 5, 5, 0, 2, 0, 6, 0, 2, 0, 5, 0, 255};
const uint8_t l_heaven_c[] PROGMEM = {1, 6, 6, 0, 0, 6, 6, 0, 0, 7, 7, 0, 7, 7, 0, 7, 0, 8, 8, 0, 0, 8, 8, 8, 0, 8, 8, 0, 8, 8, 0, 9, 0, 10, 10, 0, 0, 10, 10, 0, 0, 12, 12, 0, 12, 12, 0, 10, 0, 6, 6, 0, 0, 6, 6, 0, 0, 6, 6, 0, 6, 6, 0, 7, 0, 6, 6, 0, 0, 6, 6, 0, 0, 7, 7, 0, 7, 7, 0, 7, 0, 8, 8, 0, 0, 8, 8, 0, 0, 8, 8, 0, 8, 8, 0, 8, 0, 7, 7, 0, 0, 7, 7, 0, 0, 7, 7, 0, 7, 7, 0, 7, 0, 8, 8, 0, 0, 8, 8, 0, 0, 8, 8, 0, 8, 8, 0, 9, 0, 255};

// PLAN B
const uint8_t c_planb[] PROGMEM = {8, 1, 0, 1, 0, 4, 0, 1, 0, 5, 0, 4, 0, 1, 0, 1, 0, 255};

//MUSHROOM

/////////////////////////////////////////PRESET POINTERS//////////////////////////////////////////////

const uint8_t *preset_pointers[][4] =
{
    //1 - LIFE/CALL ME MAYBE
    {&c_life[0], &c_callmemaybe[0], &l_life[0], &l_callmemaybe[0]},
    //2 - TURING
    {&c_turing[0], &blank[0], &blank[0], &blank[0]},
    //3 - HEAVEN
    {&c_heaven_c[0], &c_heaven_v[0], &l_heaven_c[0], &blank[0]},
    //4 - KIDS and MUSHROOM
    {&c_mushroom[0], &c_kids[0], &l_mushroom[0], &l_kids[0]},
    //5 - BELIEVE
    {&c_believe_v[0], &c_believe_c[0], &blank[0], &blank[0]},
    //6 - PLAN B
    {&c_planb[0], &blank[0], &blank[0], &blank[0]},
   
    // FREE SPOTS
    {&blank[0], &blank[0], &blank[0], &blank[0]},
    {&blank[0], &blank[0], &blank[0], &blank[0]},
    {&blank[0], &blank[0], &blank[0], &blank[0]},
};

/////////////////////////////////////////DRUM PRESETS//////////////////////////////////////////////

const bool drum_presets[9][3][drum_length] PROGMEM =
{
    //preset 1 - basic
    {
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},       
    },
    
    //preset 2 - double speed
    {
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
        {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0},       
    },

    //preset 3 - break beat
    {
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0},       
    },

    //preset 4 - be my baby
    {
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0},        
    },

    //preset 5 - disco
    {
        {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0},       
    },

    //preset 6 - offbeats
    {
        {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},       
    },
    
    //preset 7 - immigrant song
    {
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1},       
    },

    //preset 8 - snare and kick on each beat
    {
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
        {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
        {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},       
    },

    //preset 9 - half time
    {
        {1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},       
    },
    

};

/////////////////////////////////////////FUNCTIONS//////////////////////////////////////////////

void load_preset(int preset_number)
{
  if (preset_number > 0)
      {
      for (int n = 0; n < 2; n++)
      {
          int j = 0;
          int note_length = pgm_read_byte(preset_pointers[preset_number-1][n]);
          for(int i = 0; i < max_beats; i++)
          {
            if (i%note_length == 0)
            {
              j++;
            }
            if (pgm_read_byte(preset_pointers[preset_number-1][n]+j) == 255)
            {
              j = 1;
            }
            chords[n][i] = pgm_read_byte(preset_pointers[preset_number-1][n]+j);
          }
      }

      for (int n = 0; n < 2; n++)
      {
          int j = 0;
          int note_length = pgm_read_byte(preset_pointers[preset_number-1][n+2]);
          for(int i = 0; i < max_beats; i++)
          {
            if (i%note_length == 0)
            {
              j++;
            }
            if (pgm_read_byte(preset_pointers[preset_number-1][n+2]+j) == 255)
            {
              j = 1;
            }
            leads[n][i] = pgm_read_byte(preset_pointers[preset_number-1][n+2]+j);
          }
      }
  }
}

void load_drums(int preset1, int preset2)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < drum_length; j++)
        {
            if (preset1 > 0)
            {
              drums[0][i][j] = pgm_read_byte(&drum_presets[preset1-1][i][j]);
            }
            if (preset2 > 0)
            {
              drums[1][i][j] = pgm_read_byte(&drum_presets[preset2-1][i][j]);
            }
        }
    }
}



