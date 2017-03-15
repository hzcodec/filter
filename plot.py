#!/usr/bin/env python
import sys
from pylab import *

NUMBER_OF_FIELDS = 11
ALPHA_POS = 8
SAMPLING_TIME = 83.0 # us

font = {'family': 'monospace',
        'color':  'black',
        'weight': 'bold',
        'size': 12,
        }

data = []
skip = 0


try:
    sel = sys.argv[1]
except IndexError:
    print 'Error! ./plot [1|2]'
    sys.exit()

if (sel == '1'):
    lines1 = [line.rstrip('\n') for line in open('logfiles/square_samples.txt')]
    num_lines = sum(1 for line in open('logfiles/square_samples.txt'))

elif (sel == '2'):
    lines1 = [line.rstrip('\n') for line in open('logfiles/ramp_samples.txt')]
    num_lines = sum(1 for line in open('logfiles/ramp_samples.txt'))

elif (sel == '3'):
    lines1 = [line.rstrip('\n') for line in open('logfiles/slope.txt')]
    num_lines = sum(1 for line in open('logfiles/slope.txt'))


try:
    lines2 = [line.rstrip('\n') for line in open('logfiles/filter.txt')]
except IOError:
    print 'filter.txt not read'
    skip = 1


t = arange(0, num_lines-NUMBER_OF_FIELDS, 1)

# calculate total time and convert to ms
totTime = (num_lines-NUMBER_OF_FIELDS) * SAMPLING_TIME / 1000.0

# just make a copy of the list except the header info
data = lines1[0:num_lines-NUMBER_OF_FIELDS]

# find max y value, used to place text
ypos = 0.2 * float(max(data))

# get input type string
inputType = lines1[num_lines-NUMBER_OF_FIELDS]

plot(t, data)

if (skip == 0):
    plot(t, lines2)

fig = gcf()
fig.canvas.set_window_title('Filter test')

plt.text(0.3*num_lines, ypos, inputType, fontdict=font)

xlabel('samples')
ylabel('i')

title(str(lines1[num_lines-ALPHA_POS])+',  Total time:'+str(totTime)+' ms')

grid(True)
show()

