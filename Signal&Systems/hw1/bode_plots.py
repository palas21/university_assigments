"""
Author: Şafak Özkan Pala 150210016
Date: 07.05.2024
Description: This code is written to plot the Bode plots of the transfer functions H1, H2 and the cascade system H_c = H1 * H2.
"""

from matplotlib import pyplot as plt
import numpy as np
import scipy.signal as signal

H1 = signal.TransferFunction([10, 10] , [1 / 100, 1 / 5, 1]) # H1 = 10s + 10 / 0.01s^2 + 0.2s + 1
H2 = signal.TransferFunction([1], [1 / 10, 1]) # H2 = 1 / 0.1s + 1
H_c = signal.TransferFunction(np.convolve([10, 10] , [1]), np.convolve([1 / 100, 1 / 5, 1] , [1 / 10, 1])) # H_c = H1 * H2

w1, mg1, phs1 = signal.bode(H1) # Bode plot of H1
w2, mg2, phs2 = signal.bode(H2) # Bode plot of H2
w_c, mg_c, phs_c = signal.bode(H_c) # Bode plot of H_c

plt.figure()
plt.semilogx(w1, mg1, label="H1(jω)")
plt.semilogx(w2, mg2, label="H2(jω)")
plt.semilogx(w_c, mg_c, label="Cascade")
plt.xlabel("Frequency [rad/s]")
plt.ylabel("Magnitude [dB]")
plt.title("Bode Plots")
plt.legend()
plt.grid() 

plt.figure()
plt.semilogx(w1, phs1, label="H1(jω)")
plt.semilogx(w2, phs2, label="H2(jω)")
plt.semilogx(w_c, phs_c, label="Cascade")
plt.xlabel("Frequency [rad/s]")
plt.ylabel("Phase [degrees]")
plt.title("Bode Plots")
plt.legend()
plt.grid()
plt.show()

"""
In this part of the code, we have created a cascade system by multiplying two transfer functions H1 and H2. First we get H1 and H2 transfer functions by using signal.TransferFunction() function. 
Then we get the Bode plots of H1, H2 and the cascade system H_c by using signal.bode() function. 
Finally, we plot the magnitude and phase of H1, H2 and H_c in two separate figures.
We used plt.semilogx() function to plot the magnitude and phase of the transfer functions in logarithmic scale instead of plt.plot() function.

In the graph of H1 we can see that it has 2 poles and 1 zero.
In the graph of H2 we can see that it has 1 pole and 0 zero. 
In the graph of the cascade system H_c we can see that it has 3 poles and 1 zero. 
"""