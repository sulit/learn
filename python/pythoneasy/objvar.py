#!/usr/bin/python
#遗留问题__del__的执行过程尚不明白，做了测试还是不明了

class Person:
	'''Represents a person'''
	population = 0

	def __init__(self,name):
		'''Initializes the person's data.'''
		self.name = name
		print '(Initializing %s)'% self.name

		Person.population += 1

	def __del__(self):
		'''I am dying.'''
		print '%s says bye.'% self.name

		Person.population -= 1

		if Person.population == 0:
			print 'I am the last one.'
		else:
			print 'There are still %d people left.'% Person.population

	def say_hi(self):
		'''Greeting by the person.
		Really,that's all it does.'''
		print 'Hi, my name is %s'% self.name

	def  how_many(self):
		'''Print the current population.'''
		if Person.population == 1:
			print 'I am the only person here.'
		else:
			print 'We have %d persons here.'% Person.population


sulit = Person('sulit')
sulit.say_hi()
sulit.how_many()

mengyi = Person('mengyi')
mengyi.say_hi()
mengyi.how_many()


sulit.say_hi()
sulit.how_many()
