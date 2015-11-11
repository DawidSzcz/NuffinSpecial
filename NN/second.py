import numpy as np
import matplotlib.pyplot as plt
import operator
import collections
import random

from sklearn import datasets


## K-nearest algoritm
def calcDistance(a, b):
	a = np.array(a)
	b = np.array(b)
	return ((a-b).dot((a-b).transpose()))**(.5)

def kNearest(pts, types, ids, point_id, k):
	d = collections.OrderedDict()
	t = dict.fromkeys(set(types), 0)
	x = pts[point_id]
	for i in ids:
		dist = calcDistance(x, pts[i])
		if(sum(t.values()) < k):
			d[dist] = types[i]
			t[types[i]]+=1 
			maxx = max(d.keys())
		elif (dist < maxx):
			#print(d)			
			t[d[maxx]]-=1
			del d[maxx]
			d[dist] = types[i]
			t[types[i]]+=1
			maxx = max(d.keys())
	maxXx = 0 
	for i in t:
		if t[i] >= maxXx:
			maxXx = t[i]
			key = i

	return key

## end of k-nearest algoritm


## solution for task 3
iris =  datasets.load_iris()

pts = np.array([i[:2] for i in iris.data])
types = iris.target
fig = plt.figure()

errors =dict.fromkeys(range(1,21), 0)
for l in range(0,500):
	print(l)
	for k in range(1,21):
		samples = random.sample(range(150), 100)
		test = [i for i in range(150) if i not in samples]
		for i in test:
			if(kNearest(pts, types, samples, i, k) != iris.target[i]):
				errors[k]+=1
	print(errors)
ax = fig.add_axes([0.1, 0.1, 0.8, 0.8])
ax.grid(True)
ax.plot([i for i in errors.keys()], [i/500 for i in errors.values()], color='blue', lw=2)
plt.show()
	

	
	
	
