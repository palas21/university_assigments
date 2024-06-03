"""
Author: Şafak Özkan Pala 150210016
Date: 07.05.2024
Description: This code is written to decrypt the hidden message in the given audio file and simulate the system with the decrypted message.
"""

import librosa
import numpy as np
import soundfile as sf
import scipy.signal as signal

def simulate_system(audio_file, sr=22050):
    """
    We simulate the system with the given input signal using given formula and save the output signal to the data folder.

    Args:
        audio_file (string): Input signal path
        sr (int, optional): Sample rate of the input signal. Defaults to 22050.
    """
    input_signal, _ = librosa.load(audio_file)
    
    output_signal = signal.lfilter([8, -14, -4], [8, 2, -1], input_signal)
    
    sf.write("data/part2.wav", output_signal, sr)

def decrypte_file(audio_file):
    """
    We decrypt the given audio file and save the output to the data folder. 

    Args:
        audio_file (string): Path of the audio file

    """

    audio_data, sample_rate = librosa.load(audio_file) # Read the audio file

    segment_length = sample_rate

    num_segments = len(audio_data) // segment_length 
    segments = np.array_split(audio_data, num_segments) # We split the audio data into segments for every second

    hidden_message = [] # We will store the hidden message in this list
    for segment in segments:

        spectrum = np.fft.fft(segment) # We take the fourier transform of the segment

        message_half = spectrum[len(spectrum)//2:] # We take the second half of the spectrum

        recovered_segment = np.fft.irfft(message_half) # We take the inverse fourier transform of the second half
        
        hidden_message.append(recovered_segment) # We append the recovered segment to the hidden message list

    hidden_message_audio = np.concatenate(hidden_message)
    output_file = "data/part1.wav"
    sf.write(output_file, hidden_message_audio, sample_rate)
    
def main():
    decrypte_file("data/bayrakfm.wav")
    simulate_system("data/part1.wav")
    print("You can listen to the output files in the data folder.")
    
if __name__ == "__main__":
    main()