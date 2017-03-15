#!/usr/bin/env python
from pylab import *

NUMBER_OF_FIELDS = 10
ALPHA_POS = 8
SAMPLING_TIME = 83.0 # us
INPUT_TYPE = 'Ramp input signal'
Y_POS = 9 # position of text

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

# just make a copy of the list
data = lines1[0:num_lines-NUMBER_OF_FIELDS]

plot(t, data)
plot(t, lines2)

fig = gcf()
fig.canvas.set_window_title('Filter test')

plt.text(0.3*num_lines, Y_POS, INPUT_TYPE, fontdict=font)

xlabel('samples')
ylabel('i')

title(str(lines1[num_lines-ALPHA_POS])+',  Total time:'+str(totTime)+' ms')

grid(True)
show()

