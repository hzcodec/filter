#!/usr/bin/env python
import os
import sys
from pylab import *

NUMBER_OF_FIELDS = 11
ALPHA_POS = 3
SAMPLING_TIME = 83.0 # us

font = {'family': 'monospace',
        'color':  'black',
        'weight': 'bold',
        'size': 12,
        }

data = []
lines1 = []
num_lines = 0
select = -1

f = []
for (dirpath, dirnames, filenames) in os.walk('logfiles'):
    f.extend(filenames)

print '-'*25
print 'Current logfiles:'
for i in range(1,len(filenames)):
    print ' ', filenames[i]
print ' '

print '[0] Quit application'
print '[1] Sinus samples read'
print '[2] Square samples read'
print '[3] Ramp samples read'
print '[4] Slope samples read'
print '[5] Filter read'
print '[6] Counter read'
print '[7] Power of 2 read'
print ' '

select = input("Select file to be read: ")
print 'select ->', select

if (select == 1):
    print 'Sinus samples read\n'
    lines1 = [line.rstrip('\n') for line in open('logfiles/sinus_samples.txt')]
    num_lines = sum(1 for line in open('logfiles/sinus_samples.txt'))

elif (select == 2):
    print 'Square samples read\n'
    lines1 = [line.rstrip('\n') for line in open('logfiles/square_samples.txt')]
    num_lines = sum(1 for line in open('logfiles/square_samples.txt'))

elif (select == 3):
    print 'Ramp samples read\n'
    lines1 = [line.rstrip('\n') for line in open('logfiles/ramp_samples.txt')]
    num_lines = sum(1 for line in open('logfiles/ramp_samples.txt'))

elif (select == 4):
    print 'Slope samples read\n'
    lines1 = [line.rstrip('\n') for line in open('logfiles/slope.txt')]
    num_lines = sum(1 for line in open('logfiles/slope.txt'))

elif (select == 5):
    print 'Filter read\n'
    lines1 = [line.rstrip('\n') for line in open('logfiles/filter.txt')]
    num_lines = sum(1 for line in open('logfiles/filter.txt'))

elif (select == 6):
    print 'Counter read\n'
    lines1 = [line.rstrip('\n') for line in open('logfiles/counter_samples.txt')]
    num_lines = sum(1 for line in open('logfiles/counter_samples.txt'))

elif (select == 7):
    print 'Power of 2 read\n'
    lines1 = [line.rstrip('\n') for line in open('logfiles/power2_samples.txt')]
    num_lines = sum(1 for line in open('logfiles/power2_samples.txt'))

elif (select == 0):
    print 'Quit application'
    sys.exit()

t = arange(0, num_lines-NUMBER_OF_FIELDS, 1)

# calculate total time and convert to ms
totTime = (num_lines-NUMBER_OF_FIELDS) * SAMPLING_TIME / 1000.0

# just make a copy of the list except the header info
data = lines1[11:num_lines]

# find max y value, used to place text
ypos = 0.3 * float(max(data))

# get input type string
inputType = lines1[0]

#plot(t, data, marker='o', linestyle='-.', color='b')
plot(t, data)

fig = gcf()
fig.canvas.set_window_title('Filter test')

plt.text(0.3*num_lines, ypos, inputType, fontdict=font)

xlabel('samples')
ylabel('i')

title(str(lines1[ALPHA_POS])+',  Total time:'+str(totTime)+' ms')

grid(True)
show()

