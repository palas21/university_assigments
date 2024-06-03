"""
Author: Şafak Özkan Pala 150210016
Date: 07.05.2024
Description: This code is written to play a maze game automatically. You can reach the game in using the following link: https://web.itu.edu.tr/sahinyu/mine_project_web/
             If you encounter a problem with the code please restart the game and run the code again. It works perfectly in the second run.
"""
import soundcard as sc
import pyautogui as pg
import time
import numpy as np

mic = sc.all_microphones(include_loopback=True)[3] # Get the default output device

def mic_check(): # Check if the microphone is working
    rate = 16000
    with mic.recorder(samplerate=rate) as rec:
        data = rec.record(numframes= rate * 0.001)[:,1]
    
    if data is not None:
        print('Microphone is working!')

def listen():
    """
    Listen the heartbeat sound and return True if there is not any mine
    otherwise return False.
    
    Used sample rate: 16000 Hz for the best results 
    Take the first 0.001 seconds of the sound and analyze it
    If the mean is between 0.50 and 0.52, there is a mine otherwise there is not.
    
    Returns:
        bool: True if there is not any mine, False otherwise
    
    """
    print('Listening...')
    
    rate = 16000
    with mic.recorder(samplerate=rate) as rec:
        data = rec.record(numframes= rate * 0.001)[:,1]
        
    maks = np.max(data)
    mini = np.min(data)
    norm = (data - mini) / (maks - mini) * 2 - 1
    
    mean = np.mean(norm)
    
    if mean < 0.52 and mean > 0.50:
        return False
    else:
        return True

def check(direction, coordinates):
    """
    This functions checks the given direction and returns True if there is not any mine

    Args:
        direction (int): 0 for right, 1 for up, 2 for down, 3 for left  
        coordinates (list): Current coordinates of the player [x, y]

    Returns:
        res (bool): True if there is not any mine, False otherwise
    """
    
    res = False
    if direction == 'right':
        print('Checking right...')
        pg.keyDown('d')
        time.sleep(0.6)
        pg.keyUp('d')
        time.sleep(0.4)
    
        res = listen()
        
        pg.keyDown('a')
        time.sleep(0.6)
        pg.keyUp('a')
        time.sleep(0.4)
    
    elif direction == 'up':
        if coordinates[1] < 4:
            print('Checking up...')
            pg.keyDown('w')
            time.sleep(0.6)
            pg.keyUp('w')
            time.sleep(0.4)
            
            res = listen()
            
            pg.keyDown('s')
            time.sleep(0.6)
            pg.keyUp('s')
            time.sleep(0.4)
        
    elif direction == 'left':
        print('Checking left...')
        pg.keyDown('a')
        time.sleep(0.6)
        pg.keyUp('a')
        time.sleep(0.4)
        
        res = listen()
        
        pg.keyDown('d')
        time.sleep(0.6)
        pg.keyUp('d')
        time.sleep(0.4)
        
    elif direction == 'down':
        if coordinates[1] > 2:
            print('Checking down...')
            pg.keyDown('s')
            time.sleep(0.6)
            pg.keyUp('s')
            time.sleep(0.4)
            
            res = listen()
            
            pg.keyDown('w')
            time.sleep(0.6)
            pg.keyUp('w')
            time.sleep(0.4) 
            
    return res

def move(direction, coordinates):
    """
    This function moves the player to the given direction and updates the coordinates

    Args:
        direction (int): 0 for right, 1 for up, 2 for down, 3 for left
        coordinates (list): Current coordinates of the player [x, y]
    """
    if direction == 'right':
        print('Moving right...')
        pg.keyDown('d')
        time.sleep(1.89)
        pg.keyUp('d')
        time.sleep(0.4)
        coordinates[0] += 1
        
    elif direction == 'up':
        print('Moving up...')
        pg.keyDown('w')
        time.sleep(1.89)
        pg.keyUp('w')
        time.sleep(0.4)
        coordinates[1] += 1
    
    elif direction == 'down':
        print('Moving down...')
        pg.keyDown('s')
        time.sleep(1.89)
        pg.keyUp('s')
        time.sleep(0.4)
        coordinates[1] -= 1
    
    elif direction == 'left':
        print('Moving left...')
        pg.keyDown('a')
        time.sleep(1.89)
        pg.keyUp('a')
        time.sleep(0.4)
        coordinates[0] -= 1

def make_decision(prev, coordinates):
    """
    This function makes the decision based on the previous direction and current coordinates

    Args:
        prev (int): 0 for right, 1 for up, 2 for down, 3 for left
        coordinates (list): list of current coordinates [x, y]

    Returns:
        prev or new_prev (int): Updated previous direction
        coordinates (list): Updated coordinates
    """
    print('Making decision...')
    print('Previous:', prev)

    if prev != 3:
        if check('right', coordinates):
            move('right', coordinates)
            return 0, coordinates
    if prev != 2:
        if check('up', coordinates):
            move('up', coordinates)
            return 1, coordinates
    if prev != 1:
        if check('down', coordinates):
            move('down', coordinates)
            return 2, coordinates
    if prev != 0: 
        if check('left', coordinates):
            move('left', coordinates)
            return 3, coordinates
    
    return prev, coordinates

def simulate():
    """
    This functions simulates the player in the maze.

    The player starts from the coordinates [0, 0] and tries to reach the end of the maze [7, X]
    
    """
    mic_check()
    print('Simulation started...')
    current = 2
    coordinates = [0, 0]
    while True:
        current, coordinates = make_decision(current, coordinates)
        print('Coordinates:', coordinates)
        if coordinates[0] == 7:
            break
    
    print('Congratulations! You have reached the end of the maze!')

def main():
    simulate()

if __name__ == '__main__':
    main()