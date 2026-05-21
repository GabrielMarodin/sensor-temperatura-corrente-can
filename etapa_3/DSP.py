"""
Definitions of classes and functions for Digital Signal Processing

Author: Emanuel S Araldi
"""

from matplotlib import rcParams
from matplotlib.figure import Figure
from matplotlib import patches
import matplotlib.pyplot as plt
import numpy as np
import scipy as sp

"""
@brief: Takes two signals with different 'n' vectors, and equalizes 'n'

@param: sig1        - First signal
@param: sig2        - Second signal
@ret:   sig1, sig2  - Resulting signals, with the same 'n' vector
"""


def equal_n(sig1, sig2):
    try:  # Signal is a numpy array of (n, x) form
        n1 = sig1[1]
        x1 = sig1[0].copy()
        n2 = sig2[1]
        x2 = sig2[0].copy()
    except:  # Part of class "Signal"
        n1 = sig1.n
        x1 = sig1.val.copy()
        n2 = sig2.n
        x2 = sig2.val.copy()
    # Normalizes
    nmin = min(n1[0], n2[0])        # => n1 and n2 are ascending
    nmax = max(n1[-1], n2[-1])+1
    n = np.arange(nmin, nmax, 1)

    y1 = np.zeros(len(n))
    y2 = y1.copy()

    # Adapted from professor's sigadd
    y1[np.nonzero(np.logical_and((n >= n1[0]),
                                 (n <= n1[-1])) == 1)] = x1
    y2[np.nonzero(np.logical_and((n >= n2[0]),
                                 (n <= n2[-1])) == 1)] = x2

    return [y1, y2], n


def Four_Plot_Same(F, dB=False, title="Transformada de Fourier",
                   y1='|H(ω)|', y2='Phase'):
    fig = plt.figure()
    ax = fig.add_subplot(1, 1, 1)
    ax2 = ax.twinx()  # instantiate a second axes that shares the same x-axis
    # Plot
    if dB:
        y1 = str(y1) + " - dB"
        ax.plot(F[1], 20*np.log10(np.abs(F[0])))
    else:
        ax.plot(F[1], np.abs(F[0]))
    ax2.plot(F[1], np.angle(F[0], deg=True), 'r--')
    # Titles and labels
    ax.set_title(title)
    ax.set_xlabel('f (Hz)')
    ax.set_ylabel(y1)
    # we already handled the x-label with ax
    ax2.set_ylabel(y2)
    ax2.tick_params(axis='y')
    fig.tight_layout()  # otherwise the right y-label is slightly clipped
    # Add legend
    ax.legend("Magnitude")
    ax2.legend("Phase")
    plt.grid(True, 'both')
    return


def Four_Plot_Sep_Sub(F, dB=False, title="Transformada de Fourier",
                      y1='|H(ω)|', y2='Phase'):
    fig = plt.figure()
    ax1 = fig.add_subplot(2, 1, 1)
    ax2 = fig.add_subplot(2, 1, 2)
    # Plot
    if dB:
        y1 = str(y1) + " - dB"
        ax1.plot(F[1], 20*np.log10(np.abs(F[0])))
    else:
        ax1.plot(F[1], np.abs(F[0]))
    ax2.plot(F[1], np.angle(F[0], deg=True), 'r--')
    # Titles and labels
    plt.title(title)
    ax1.set_xlabel('f (Hz)')
    ax1.set_ylabel(y1)
    ax2.set_xlabel('f (Hz)')
    ax2.set_ylabel(y2)
    # Add legend
    ax1.legend("Magnitude")
    ax2.legend("Phase")
    plt.grid(True, 'both')
    return


def Four_Plot_Sep(F, dB=False, title="Transformada de Fourier",
                  y1='|H(ω)|', y2='Phase'):
    fig = plt.figure()
    # First plot
    Four_Plot_Mag(F, dB, title, y1)
    # Second plot
    fig = plt.figure()
    ax2 = fig.add_subplot(1, 1, 1)
    # Titles and labels
    plt.title(title)

    ax2.set_xlabel('f (Hz)')
    ax2.set_ylabel(y2)
    # Plot
    ax2.plot(F[1], np.angle(F[0], deg=True), 'r--')
    # Add legend
    ax2.legend("Phase")
    plt.grid(True, 'both')
    return


def Four_Plot_Mag(F, dB=False, title="Transformada de Fourier",
                  y1='|H(ω)|', y2=None):
    fig = plt.figure()
    # First plot
    ax1 = fig.add_subplot(1, 1, 1)
    if dB:
        y1 = str(y1) + " - dB"
        ax1.plot(F[1], 20*np.log10(np.abs(F[0])))
    else:
        ax1.plot(F[1], np.abs(F[0]))
    # Titles and labels
    ax1.set_xlabel('f (Hz)')
    ax1.set_ylabel(y1)
    ax1.legend("Magnitude")
    plt.title(title)
    plt.grid(True, 'both')
    return


"""
@brief: Defines a signal (x[n]) and the operations to be performed on it

@var: n - numpy array containing the number of the samples
@var: val - numpy array containg the values mapped to the 'n' vector
@var: title - title used for plotting
"""


class Signal:
    # Basic Methods
    def __init__(self, lower_bound, upper_bound, title=None):
        self.n = np.arange(lower_bound, upper_bound + 1, 1)
        self.val = np.zeros(self.n.shape)
        if (title != None):
            self.title = title
        else:
            self.title = "Signal"

    def __mul__(self, s):
        [y1, y2], n = equal_n(self, s)
        ret = Signal(n[0], n[-1])
        ret.set_sig(np.multiply(y1, y2))
        return ret

    def __imul__(self, s):
        [y1, y2], n = equal_n(self, s)

        self.val = np.multiply(y1, y2)
        self.n = n
        return self

    def __add__(self, s):
        [y1, y2], n = equal_n(self, s)
        ret = Signal(n[0], n[-1])
        ret.set_sig(y1 + y2)
        return ret

    def __iadd__(self, s):
        [y1, y2], n = equal_n(self, s)

        self.val = y1 + y2
        self.n = n

        return self

    def __sub__(self, s):
        [y1, y2], n = equal_n(self, s)
        ret = Signal(n[0], n[-1])
        ret.set_sig(y1 - y2)
        return ret

    def __isub__(self, s):
        [y1, y2], n = equal_n(self, s)

        self.val = y1 - y2
        self.n = n
        return self

    def __irshift__(self, num):
        self.n += num
        return self

    def __ilshift__(self, num):
        self.n -= num
        return self

    def __rshift__(self, num):
        r = self.n + num
        return r

    def __lshift__(self, num):
        r = self.n - num
        print(r)
        return r

    # Modified Convolution, from professor's DSP
    def __xor__(self, s):
        nyb = self.n[0]+s.n[0]
        nye = self.n[len(self.val)-1] + s.n[len(s.val)-1]
        ny = np.arange(nyb, nye+1)
        y = np.convolve(self.val, s.val)
        return [y, ny]

    def __ixor__(self, s):
        nyb = self.n[0]+s.n[0]
        nye = self.n[len(self.val)-1] + s.n[len(s.val)-1]
        self.n = np.arange(nyb, nye+1)
        self.val = np.convolve(self.val, s.val)

    # Class Methods
    # Impulse signal
    def impulse(self, n, A=1):
        temp = np.where(self.n == n)
        if (not temp[0].size):
            print("Invalid 'n'")
            return
        ret = Signal(0, 0)
        ret.n = self.n
        ret.val[temp] += A
        return ret

    # Exponential Signal
    def exp(self, k, A=1, off=0):
        ret = Signal(0, 0)
        ret.n = self.n
        ret.val = A*np.exp(k*(ret.n - off))
        return ret

    # Sine Signal
    def sin(self, w, A=1, fi=0):
        fi = fi*np.pi/180  # Degree -> rad
        ret = Signal(0, 0)
        ret.n = self.n
        ret.val = A*np.sin(w*ret.n + fi)
        return ret

    # Cosine Signal
    def cos(self, w, A=1, fi=0):
        ret = Signal(0, 0)
        ret.n = self.n
        fi = fi*np.pi/180  # Degree -> rad
        ret.val = A*np.cos(w*ret.n + fi)
        return ret

    def heaviside(self, n0=0, A=1):
        self.val = A*np.heaviside(self.n - n0, 1)
        return

    def moving_avg(self, samples=2):
        final_size = len(self.n)-samples+1
        s = Signal(self.n[0], final_size + self.n[0] - 1)
        i = 0
        while i < final_size:
            window = self.val[i: i+samples]
            s.val[i] = np.sum(window)/samples
            i += 1
        return s

    def filter(self, wc, order=2, type="lowpass"):
        filtered = Signal(self.n[0], self.n[-1])
        sos = sp.signal.butter(N=order, Wn=wc/(np.pi),
                               btype=type, output='sos')
        filtered.val = sp.signal.sosfilt(sos, self.val)

        return filtered

    def add_noise(self, var=1, mean=0):
        self.val += np.random.normal(mean, var/100, self.val.shape)
        return

    def fourier(self, points=500, half=False):
        i = 0
        j = complex(0, 1)
        if (not half):
            W = np.linspace(0, 2*np.pi, points)
        else:
            W = np.linspace(0, np.pi, points)
        F = np.zeros(len(W)) * j
        for w in W:
            F[i] = np.sum(self.val*np.exp(-j*w*self.n))
            i += 1
        if (half):
            F = 2*F

        return [F, W, self.n]

    def get_sig(self):
        return self.val

    def set_sig(self, new_val):
        try:
            self.val = new_val
        except:
            print("Error setting signal")

    # Plot Signal
    def plot(self, xl='n', yl='y[n]', title=None):
        fig = plt.figure()
        ax = fig.add_subplot(1, 1, 1)
        # Titles and labels
        if (title == None):
            ax.set_title(self.title)
        else:
            ax.set_title(title)
        ax.set_xlabel(xl)
        ax.set_ylabel(yl)
        # Plot
        plt.stem(self.n, self.val)
        return

# Plot de Conveniência


def plot(signal, title="Signal", xl='n', yl='y[n]', grid=True):
    fig = plt.figure()
    ax = fig.add_subplot(1, 1, 1)
    # Titles and labels
    ax.set_title(title)
    ax.set_xlabel(xl)
    ax.set_ylabel(yl)
    # Grids
    ax.grid(grid, 'both', 'both')
    # Plot
    plt.stem(signal[1], signal[0])

# Plot de conveniência para transformada de Fourier


def Plot_Fourier(F, type="Mag_Only", dB=False,
                 title="Transformada de Fourier",
                 y1='|H(ω)|', y2='Phase'):

    Four_Plot_Funcs[type](F, dB, title, y1, y2)
    return


"""
@brief: Inverse Fourier Transform

@var:   F - np array on form (X[w], w, n)
@ret:   s - Signal reconstructed from F

@obs:   The params n0 and nf are fail-safes
"""


def inv_four(F, n0=-10, nf=10):
    i = 0
    j = complex(0, 1)
    X = F[0]  # => X(w)
    try:
        N = F[2]
    except:
        N = np.arange(n0, nf+1)
    s = Signal(0, 0)
    s.n = N
    x = np.zeros(len(N))

    for n in N:
        # np.real prevents cast warning
        x[i] += np.real(np.trapz(X*np.exp(j*F[1]*n), F[1]))
        i += 1

    s.val = x/(2*np.pi)

    return s


def cos(start, end, w=1):
    n = np.arange(start, end+1, 1)
    return np.cos(w*n), n


def sin(start, end, w=1):
    n = np.arange(start, end+1, 1)
    return np.sin(w*n), n


def echo(sig, aten, T, fs=1):
    sig_echo = aten * sig  # Atenua sinal
    sig_echo = np.append(np.zeros(int(T*fs)), sig_echo)  # Adiciona delay
    sig_echo[0:len(sig)] = sig_echo[0:len(sig)] + sig
    return sig_echo


def halfsp(x):
    x_ret = np.zeros(len(x)//2)
    for i in range(len(x)//2):
        x_ret[i] = x[2*i]
    return x_ret


def doublesp(x):
    x_ret = np.zeros(2*len(x))
    for i in np.arange(0, 2*len(x)):
        if (i % 2):                     # True for odd numbers
            x_ret[i] = x[i//2]        # 1+i//2 = ceil(i/2)
            continue
        else:                           # True for even numbers
            x_ret[i] = (x[i//2]+x[i//2-1])/2
            continue
    return x_ret


def normalize(x, A=1.0):
    return A*x.astype(float)/np.max(np.abs(x.astype(float)))

# fDSP do professor


def impseq(n0, n1, n2):

    #      Generates x(n) = delta(n-n0); n1 <= n <= n2
    #      ----------------------------------------------
    #      [x,n] = impseq(n0,n1,n2)
    #

    n = np.array(range(n1, n2+1))
    # Shift by n0
    x = n-n0
    for i in range(len(x)):
        # Only x[n0] == 0
        if x[i] != 0:
            x[i] = 0
        else:
            x[i] = 1
    # x = (n-n0) == 0
    return [x, n]


def stepseq(n0, n1, n2):
    #     Generates x(n) = u(n-n0); n1 <= n <= n2
    #     ------------------------------------------
    #     [x,n] = stepseq(n0,n1,n2)
    #
    n = np.arange(n1, n2+1)
    x = n-n0
    for i in range(len(x)):
        if x[i] < 0:
            x[i] = 0
        else:
            x[i] = 1
    # x = [(n-n0) >= 0]
    return [x, n]


def sigadd(x1, n1, x2, n2):
    # % implements y(n) = x1(n)+x2(n)
    # % -----------------------------
    # % [y,n] = sigadd(x1,n1,x2,n2)
    # % y = sum sequence over n, which includes n1 and n2
    # % x1 = first sequence over n1
    # % x2 = second sequence over n2 (n2 can be different from n1)
    # %
    n = np.arange(min(n1.min(0), n2.min(0)), max(
        n1.max(0), n2.max(0))+1)  # duration of y(n)
    y1 = np.zeros((1, len(n)))  # initialization
    y1 = y1[0, :]
    y2 = y1.copy()
    y1[np.nonzero(np.logical_and((n >= n1.min(0)),
                  (n <= n1.max(0))) == 1)] = x1.copy()
    y2[np.nonzero(np.logical_and((n >= n2.min(0)),
                  (n <= n2.max(0))) == 1)] = x2.copy()
    y = y1+y2
    return [y, n]


def sigmult(x1, n1, x2, n2):
    # % implements y(n) = x1(n)*x2(n)
    # % -----------------------------
    # % [y,n] = sigmult(x1,n1,x2,n2)
    # % y = product sequence over n, which includes n1 and n2
    # % x1 = first sequence over n1
    # %
    n = np.arange(min(n1.min(0), n2.min(0)), max(
        n1.max(0), n2.max(0))+1)  # duration of y(n)
    y1 = np.zeros((1, len(n)))  # initialization
    y1 = y1[0, :]
    y2 = y1.copy()
    y1[np.nonzero(np.logical_and((n >= n1.min(0)),
                  (n <= n1.max(0))) == 1)] = x1.copy()
    y2[np.nonzero(np.logical_and((n >= n2.min(0)),
                  (n <= n2.max(0))) == 1)] = x2.copy()
    y = y1*y2
    return [y, n]


def sigshift(x, m, k):
    # % implements y(n) = x(n-k)
    # % -------------------------
    # % [y,n] = sigshift(x,m,k)
    # %
    n = m+k
    y = x.copy()
    return [y, n]


def sigfold(x, n):
    # % implements y(n) = x(-n)
    # % -----------------------
    # % [y,n] = sigfold(x,n)
    # %
    y = np.flip(x)
    n = -np.flip(n)
    return [y, n]


def conv_m(x, nx, h, nh):
    # Modified convolution routine for signal processing
    # --------------------------------------------------
    # [y,ny] = conv_m(x,nx,h,nh)
    # [y,ny] = convolution result
    # [x,nx] = first signal
    # [h,nh] = second signal
    #
    nyb = nx[0]+nh[0]
    nye = nx[len(x)-1] + nh[len(h)-1]
    ny = np.arange(nyb, nye+1)
    y = np.convolve(x, h)
    return [y, ny]

# Adicionais


def print_Hz(b, a):
    num = "       "
    equ = "H(z) = "
    den = "       "
    i = 0
    for bi in b:
        if np.abs(bi) > 1e-6:
            if i == 0:
                num = num + str(round(bi, 3))
            else:
                num = num + " + " + str(round(bi, 3)) + "z^-" + str(i)
        i = i+1
    i = 0

    for ai in a:
        if np.abs(ai) > 1e-6:
            if i == 0:
                den = den + str(round(ai, 3))
            else:
                den = den + " + " + str(round(ai, 3)) + "z^-" + str(i)
        i = i+1

    equ = equ + "-"*(max(len(num), len(den))-7)

    print(num)
    print(equ)
    print(den)
    return


def print_diff_eq(b, a):
    b_str = ""
    a_str = ""
    i = 0
    for bi in b:
        if np.abs(bi) > 1e-6:
            if i == 0:
                b_str = str(round(bi, 3)) + "*x[n]"
            else:
                b_str = b_str + " + " + \
                    str(round(bi, 3)) + "*x[n-" + str(i) + "]"
        i = i+1

    i = 0
    for ai in a:
        if np.abs(ai) > 1e-6:
            if i == 0:
                a_str = str(round(ai, 3)) + "*y[n]"
            else:
                a_str = a_str + " + " + \
                    str(round(ai, 3)) + "*y[n-" + str(i) + "]"
        i = i+1

    print(a_str, " = ", b_str)
    return


def print_Hz_diff_eq(b, a, Separate=False):
    separator = ""
    if Separate:
        separator = "----" + "-----------"*(len(b)-1)
        print(separator)
    print_Hz(b, a)
    print(separator)
    print_diff_eq(b, a)
    print(separator)
    return


def get_FFT(y, T=1, N=None):
    if not N:
        N = len(y)
    N = len(y)
    H = (2.0/N) * (sp.fft.fft(y)[0:N//2])
    w = sp.fft.fftfreq(N, T)[:N//2]
    F = [H, w]
    return F


def plot_FFT(y, type="Mag_Only", T=1.0, dB=False, title=None, y1="H|ω|", y2="Phase"):
    F = get_FFT(y, T)
    Plot_Fourier(F, type, dB, title, y1, y2)


def plot_group_delay(b, a, fs=1, title="Delay de Grupo"):
    w, gd = sp.signal.group_delay((b, a), fs=fs)
    plot([gd, w], title=title, xl="$\omega$", yl="nº amostras")


def read_wav(file):
    return (sp.io.wavfile.read(file))


def write_wav(file, rate, data):
    return sp.io.wavfile.write(file, rate, data)

#
# Copyright (c) 2011 Christopher Felton
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

# The following is derived from the slides presented by
# Alexander Kain for CS506/606 "Special Topics: Speech Signal Processing"
# CSLU / OHSU, Spring Term 2011.


def zplane(b, a, title="plano z do filtro", filename=None):
    """Plot the complex z-plane given a transfer function.
    """

    # get a figure/plot
    ax = plt.subplot(111)

    # create the unit circle
    uc = patches.Circle((0, 0), radius=1, fill=False,
                        color='black', ls='dashed')
    ax.add_patch(uc)

    # Get the poles and zeros
    p = np.roots(a)
    z = np.roots(b)

    # Plot the zeros and set marker properties
    t1 = plt.plot(z.real, z.imag, 'go', ms=10)
    plt.setp(t1, markersize=10.0, markeredgewidth=1.0,
             markeredgecolor='k', markerfacecolor='g')

    # Plot the poles and set marker properties
    t2 = plt.plot(p.real, p.imag, 'rx', ms=10)
    plt.setp(t2, markersize=12.0, markeredgewidth=3.0,
             markeredgecolor='r', markerfacecolor='r')

    ax.spines['left'].set_position('center')
    ax.spines['bottom'].set_position('center')
    ax.spines['right'].set_visible(False)
    ax.spines['top'].set_visible(False)

    # set the ticks
    r = 1.5
    plt.axis('scaled')
    plt.axis([-r, r, -r, r])
    ticks = [-1, -.5, .5, 1]
    plt.xticks(ticks)
    plt.yticks(ticks)

    plt.title(title)

    if filename is None:
        plt.show()
    else:
        plt.savefig(filename)

    return z, p


def QCoeff(x, N):
    #  [y,L,B] = QCoeff(x,N)
    #  Coefficient Quantization using N=1+L+B bit Representation
    #  with Rounding operation
    #  y: quantized array (same dim as x)
    #  L: number of integer bits
    #  B: number of fractional bits
    #  x: a scalar, vector, or matrix
    #  N: total number of bits
    xm = np.abs(x)
    eps = np.spacing(1)
    L = np.max(np.maximum(0, np.fix(np.log2(xm[:]+eps)+1)))   # Integer bits
    if L > N:
        print("errmsg = *** N deve ser pelo menos ", int(L))
    B = N-L   # Fractional bits
    y = xm/(2**L)
    y = np.round(y*(2**N))   # Rounding to N bits
    y = np.sign(x)*y*(2**(-B))   # L+B+1 bit representation
    return y, L, B


# Function Dictionary For Fourier Plotting
Four_Plot_Funcs = {
    "Same": Four_Plot_Same,
    "Separate_Sub": Four_Plot_Sep_Sub,
    "Separate": Four_Plot_Sep,
    "Mag_Only": Four_Plot_Mag
}
