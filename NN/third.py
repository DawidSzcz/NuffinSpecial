%pylab inline

size = 30
x = numpy.random.uniform(-numpy.pi/2, numpy.pi/2, size)
x.sort()
test = numpy.random.uniform(-numpy.pi/2, numpy.pi/2, siz)
D = 0.5
a = [[exp(-abs(test[i] - y))/D for y in x] for i in range(test.size)]
print a
y = numpy.random.normal(sin(x), 0.1, len(x))
plt.scatter(x, y)
