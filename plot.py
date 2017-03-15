#!/usr/bin/env python
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

lines1 = [line.rstrip('\n') for line in open('logfiles/ramp_samples.txt')]
num_lines = sum(1 for line in open('logfiles/ramp_samples.txt'))
lines2 = [line.rstrip('\n') for line in open('logfiles/filter.txt')]

t = arange(0, num_lines-NUMBER_OF_FIELDS, 1)

# calculate total time and convert to ms
totTime = (num_lines-NUMBER_OF_FIELDS) * SAMPLING_TIME / 1000.0

# just make a copy of the list except the header info
data = lines1[0:num_lines-NUMBER_OF_FIELDS]

# find max y value, used to place text
ypos = 0.8 * float(max(data))

plot(t, data)
plot(t, lines2)

# get input type string
inputType = lines1[num_lines-NUMBER_OF_FIELDS]

fig = gcf()
fig.canvas.set_window_title('Filter test')

plt.text(0.3*num_lines, ypos, inputType, fontdict=font)

xlabel('samples')
ylabel('i')

title(str(lines1[num_lines-ALPHA_POS])+',  Total time:'+str(totTime)+' ms')

grid(True)
show()

