#!/usr/bin/python

zoo = ('wolf', 'elephant', 'penguin')
print 'Number of animals in the zoo is', len(zoo)

new_zoo = ('monkey', 'dolphin', zoo)
print 'Number of animals in the new zoo is', len(new_zoo)
print 'All animals in the new zoo is', new_zoo
print 'Animals brought from the old zoo are', new_zoo[2]
print 'Last animals brought from the old zoo are', new_zoo[2][2]
