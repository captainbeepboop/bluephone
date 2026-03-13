import numpy as np
from scipy.io import wavfile

def midi_to_hz(note):
    a = 440 #frequency of A (coomon value is 440Hz)
    return (a / 32) * (2 ** ((note - 9) / 12))


for i in range(45,81):

    sample_rate = 44100  # samples per second
    duration = 1        # seconds
    frequency = midi_to_hz(i)     # Hz (for a sine wave example)

    # Generate a time array
    t = np.linspace(0, duration, int(sample_rate * duration), endpoint=False)
    amplitude = 0.8
    waveform =amplitude * np.sign(np.sin(2 * np.pi * frequency * t))
    #waveform = amplitude * np.sin(2 * np.pi * frequency * t)
    scaled_waveform = (waveform * 32767).astype(np.int16)

    # Write the waveform to a WAV file
    output_filename = 'sq'+str(i)+'.wav'
    wavfile.write(output_filename, sample_rate, scaled_waveform)

    print(f"WAV file '{output_filename}' created successfully.")