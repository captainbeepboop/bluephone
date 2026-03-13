import pygame
import numpy as np
import os

# Initialize Pygame and mixer
pygame.init()
pygame.mixer.init(frequency=44100)

# Screen setup
screen_width = 80
screen_height = 60
screen = pygame.display.set_mode((screen_width, screen_height))
pygame.display.set_caption("Bluephone Emulator")

# Beat and sequence

bpm = 160
time_delay = 15000/bpm
step = 0
last_time = 0
number_of_steps = 16
mutes = [0,0,0,0,0]
last_button = 0
sequence_playing = True

kick_sound = pygame.mixer.Sound("/home/cris/beepboop/Bluephone/bluephone_wav/bluephone_drums_sd_card/002kick.wav")
snare_sound = pygame.mixer.Sound("/home/cris/beepboop/Bluephone/bluephone_wav/bluephone_drums_sd_card/020snare.wav")
hihat_sound = pygame.mixer.Sound("/home/cris/beepboop/Bluephone/bluephone_wav/bluephone_drums_sd_card/040hat.wav")
drum_sounds = [hihat_sound, snare_sound, kick_sound]

sequence = "01|01 C A E F#m D !"

drum_beat = "|x-x-x-x-x-x-x-x-|----O--o----O---|O-------O-o---o-"
riff = "08|01 G- D C+ D G- B+ D G- A+ D G- G D#- E F# D#- E- B A+ B E- G B E- F# B E- E G#- B D G#- A E D+ E A C+ E A B+ C A A+ C A E A D- A G A D- F# A D E A D- D X F#- A X !";


scale = [0, 2, 4, 5, 7, 9, 11, 12], [0, 2, 3, 5, 7, 8, 10, 12]

stack_repeats = []
stack_jump = []


def string_to_root(step):
    global sequence
    global sequence_step
    global sequence_playing
    vibe = 0
    root = 0
    while True:
        if ord(sequence[step]) > 64 and ord(sequence[step]) < 72:
            root = scale[1][(ord(sequence[step]) - 65)%7] + 45
        elif sequence[step] == '#':
            root += 1
        elif sequence[step] == '+':
            root += 12
        elif sequence[step] == '-':
            root -= 12
        elif sequence[step] == ' ':
            return root
        step += 1

sequence_timing = []
sequence_timing.append(16/int(sequence[0:2]))
sequence_timing.append(int(sequence[3:5]))
root = string_to_root(6)
vibe = 0
sequence_step = 7
if sequence[7] == 'm' or sequence[8] == 'm' or sequence[9] == 'm':
        vibe = 1

def play_sequence():
    global step
    global sequence
    global sequence_step
    global sequence_timing
    if step % sequence_timing[0] == 0:
        root = 0
        vibe = 0
        loop = True

        while loop:
            sequence_step += 1
            command = sequence[sequence_step]
            print(command)
            
            if command == '!':
               #loop = 0
               #sequence_playing = False
               sequence_step = 7
    
            elif ord(command) > 64 and ord(command) < 72:
                root = string_to_root(sequence_step)

            elif command == 'm':
                vibe = 1

            elif command == 'd':
                vibe == 2

           # elif command == 'X' or command == '.':
           #     loop = False;
            
            elif command == '*':
                Print("riff!") 
                sequence_step = sequence_step + 2

            elif command == '$':
                Print("sample!")
                sequence_step = sequence_step + 2

            elif command == '%':
                bpm = int(sequence[sequence_step+1:sequence_step+4])
                time_delay = 15000/bpm
                sequence_step = sequence_step + 3
            
            elif command == '^':
                print("change bass mode!")
                sequence_step = sequence_step + 1

            elif  command == '&':
                print("change drums!")
                sequence_step = sequence_step + 2
            
            elif command == '>':
                for i in range(5):
                    mutes[i] = int(sequence[sequence_step+i+1])
                sequence_step = sequence_step + 5

            elif command == '<':
                print("beep test lap!")

            elif ord(command) > 47 and ord(command) < 58:
                if command == '0':
                    stack_repeats.append(255)
                    stack_jump.append(sequence_step)
                elif sequence[sequence_step+1] == '(':
                    stack_repeats.append(ord(command)-48)
                    stack_jump.append(sequence_step)
                else:
                    stack_repeats.append(int(sequence[sequence_step:sequence_step+2]))
                    stack_jump.append(sequence_step+1)
                    sequence_step += 1

            elif command == ')':
                stack_repeats[-1] -= 1
                if stack_repeats[-1] == 0:
                    stack_repeats.pop()
                    stack_jump.pop()
                    sequence_step += 1
                else:
                    sequence_step = stack_jump[-1]

            
            if command == ' ' or command == ')':
                if root > 0:
                    play_chord(root, vibe)
                loop = False;
            
        
    if step % sequence_timing[0] == sequence_timing[1] and sequence[sequence_step+1] != '.':
        stop_chord()

# Note Stuff

saws = []
squares = []
i = 0
for entry_name in sorted(os.listdir("saw")):
    saws.append(pygame.mixer.Sound("saw/"+entry_name))
    saws[i].set_volume(0.4)
    i = i+1
i = 0
for entry_name in sorted(os.listdir("square")):
    squares.append(pygame.mixer.Sound("square/"+entry_name))
    squares[i].set_volume(0.4)
    i = i+1

chord1 = saws[0]
chord2 = saws[0]
chord3 = saws[0]
lead = squares[0]

chord_type = [0, 1, 1, 0, 0, 1, 2, 0],[1, 2, 0, 0, 1, 1, 0, 0]
mode = 2
chord_octave = 1
lead_octave = 2

# Functions

def play_chord(note, vibe):
    note = note-45 + 12*chord_octave
    global chord1
    global chord2
    global chord3
    chord1.stop()
    chord2.stop()
    chord3.stop()
    chord1 = saws[note]
    if vibe == 2:
        chord2 = saws[note + 3]
        chord3 = saws[note + 6]
    else:
        chord2 = saws[note+4-vibe]
        chord3 = saws[note+7]

    chord1.play(-1, 3000)
    chord2.play(-1, 3000)
    chord3.play(-1, 3000)

def stop_chord():
    global chord1
    global chord2
    global chord3
    chord1.fadeout(1000)
    chord2.fadeout(1000)
    chord3.fadeout(1000)

def play_lead(note):
    note = note - 45 + 12*lead_octave
    global lead
    lead.stop()
    lead = squares[note]
    lead.play(-1, 3000)

def stop_lead():
    global lead
    lead.fadeout(500)



def beat():
    global step
    for i in range(3):
        if drum_beat[i*17+step+1] != "-":
            drum_sounds[i].play()
    if sequence_playing:
        play_sequence()
    step += 1
    if step == number_of_steps:
        step = 0

    

# Main game loop
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        if event.type == pygame.KEYDOWN:
            if event.key > 48 and event.key < 57:
                last_button = event.key
                if mode == 2:
                    play_lead(scale[vibe][event.key-49]+root)
                elif mode == 3:
                    play_chord(scale[vibe][event.key - 49] + root, chord_type[vibe][event.key - 49])
            if event.key > 1073741912 and event.key < 1073741922:
                last_button = event.key
                number = event.key - 1073741913
                conversion = [6,7,0,3,4,5,0,1,2]
                number = conversion[number]
                if mode == 2:
                    play_lead(scale[vibe][number]+root)
                elif mode == 3:
                    play_chord(scale[vibe][number] + root, chord_type[vibe][number])

        if event.type == pygame.KEYUP:
            if (event.key > 48 and event.key < 57) or (event.key > 1073741912 and event.key < 1073741922):
                if mode == 2 and event.key == last_button:
                    stop_lead()
                elif mode == 3:
                    stop_chord()
    if pygame.time.get_ticks() - last_time  > time_delay:
        last_time = pygame.time.get_ticks()
        beat()
        
    # Drawing
    screen.fill((0, 0, 0)) # Black background
    # Draw grid, buttons, indicators
    pygame.display.flip()

pygame.quit()


