#!/usr/bin/env python
from pylab import *

NUMBER_OF_FIELDS = 10
ALPHA_POS = 8
data = []

lines1 = [line.rstrip('\n') for line in open('logfiles/square_samples.txt')]
num_lines = sum(1 for line in open('logfiles/square_samples.txt'))
lines2 = [line.rstrip('\n') for line in open('logfiles/filter.txt')]

t = arange(0, num_lines-NUMBER_OF_FIELDS, 1)

totTime = (num_lines-NUMBER_OF_FIELDS) * 83.0 / 1000.0
print num_lines
print totTime

# just make a copy of the list
data = lines1[0:num_lines-NUMBER_OF_FIELDS]

plot(t, data)
plot(t, lines2)

fig = gcf()
fig.canvas.set_window_title('Filter test')

xlabel('samples')
ylabel('i')
title(str(lines1[num_lines-ALPHA_POS])+',  Total time:'+str(totTime)+' ms')

grid(True)
show()

