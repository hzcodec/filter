#!/usr/bin/env python
from pylab import *

NUMBER_OF_FIELDS = 11
ALPHA_POS = 8
SAMPLING_TIME = 83.0 # us
Y_POS = 0.8 # position of text

font = {'family': 'monospace',
        'color':  'black',
        'weight': 'bold',
        'size': 12,
        }

data = []

lines1 = [line.rstrip('\n') for line in open('logfiles/square_samples.txt')]
num_lines = sum(1 for line in open('logfiles/square_samples.txt'))
lines2 = [line.rstrip('\n') for line in open('logfiles/filter.txt')]

t = arange(0, num_lines-NUMBER_OF_FIELDS, 1)

# calculate total time and convert to ms
totTime = (num_lines-NUMBER_OF_FIELDS) * SAMPLING_TIME / 1000.0

# just make a copy of the list except the header info
data = lines1[0:num_lines-NUMBER_OF_FIELDS]

plot(t, data)
plot(t, lines2)

# get input type string
inputType = lines1[num_lines-NUMBER_OF_FIELDS]

fig = gcf()
fig.canvas.set_window_title('Filter test')

plt.text(0.3*num_lines, Y_POS, inputType, fontdict=font)

xlabel('samples')
ylabel('i')

title(str(lines1[num_lines-ALPHA_POS])+',  Total time:'+str(totTime)+' ms')

grid(True)
show()

