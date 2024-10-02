

#include "SerialMP3Player.h"
#include <MIDI.h>
#define TX 11
#define RX 10
#define channelpin 2
#define mutepin 3
long last_time = 0;
int debounce_time = 10;

SerialMP3Player mp3(RX,TX);

MIDI_CREATE_DEFAULT_INSTANCE();

bool channel_select = 0;
bool mute = 1;

void setup() {
  	mp3.begin(9600);
	MIDI.setHandleNoteOn(HandleNoteOn);  // Put only the name of the function
	MIDI.begin(9);
	pinMode(channelpin, INPUT_PULLUP);
	pinMode(mutepin, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(mutepin), change_mute, FALLING);

}

void change_mute()
{
	if (millis() - last_time > debounce_time)
	{
		mute = !mute;
		mp3.stop();
	}
	last_time = millis();
}

void HandleNoteOn(byte channel, byte note, byte velocity) {
	
	if ((velocity == 1 && mute == 0)&&channel_select == 0)
	{
		mp3.play(note*2 - 1);
	}
	if (velocity == 2 && channel_select == 1)
	{
		mp3.play(note*2 - 1);
	}

}

void loop() {
	MIDI.read();
	channel_select = !digitalRead(channelpin);
}