#!/usr/bin/env python

from pylab import *

lines1 = [line.rstrip('\n') for line in open('logfiles/square_samples.txt')]
num_lines = sum(1 for line in open('logfiles/square_samples.txt'))

lines2 = [line.rstrip('\n') for line in open('logfiles/filter.txt')]
#lines3 = [line.rstrip('\n') for line in open('logfiles/filter.txt')]
#lines4 = [line.rstrip('\n') for line in open('logfiles/filter2.txt')]
t = arange(0, num_lines, 1)

totTime = num_lines * 83.0 / 1000.0

plot(t, lines1)
plot(t, lines2)
#plot(t, lines3)
#plot(t, lines4)

fig = gcf()
fig.canvas.set_window_title('Filter test')

xlabel('samples')
ylabel('i')
title('alpha = 0.00005, tot time:'+str(totTime)+'ms')

grid(True)
show()

