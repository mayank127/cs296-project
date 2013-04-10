
import numpy
import matplotlib.pyplot as plt
data = numpy.genfromtxt('./data/lab09_g11_data.csv', delimiter=',',names=['rerun','iteration','step','collision','velocity','position','loop'])

# Graph 1
print("Generating Plot 1")
plt.clf()
stepAvgs = []
loopAvgs = []
for i in range(100):
	step = [x[2] for x in data if x[1]==i+1]
	loop = [x[6] for x in data if x[1]==i+1]
	stepAvgs.append(numpy.average(step))
	loopAvgs.append(numpy.average(loop))

plt.plot(range(1,101),stepAvgs,'r.',label="Step Time Averaged")
plt.plot(range(1,101),loopAvgs,'g.',label="Loop Time Averaged")
plt.title("g11_plot01")
plt.xlabel("Iteration Value ")
plt.ylabel("Average Time Values (ms)")
lgd=plt.legend(loc='upper center', bbox_to_anchor=(0.5,-0.1),ncol=2)
plt.savefig("./plot_gen/g11_lab09_plot01.png" , bbox_extra_artists=(lgd,), bbox_inches='tight')


# Graph 2
print("Generating Plot 2")
plt.clf()
collisionAvgs =[]
velocityAvgs = []
positionAvgs = []
for i in range(100):
	colli = [x[3] for x in data if x[1]==i+1] 
	velo = [x[4] for x in data if x[1]==i+1]
	posi = [x[5] for x in data if x[1]==i+1]
	collisionAvgs.append(numpy.average(colli))
	velocityAvgs.append(numpy.average(velo))
	positionAvgs.append(numpy.average(posi))

plt.plot(range(1,101),stepAvgs,'r.',label="Step Time Averaged")
plt.plot(range(1,101),collisionAvgs,'g.',label="Collision Time Averaged")
plt.plot(range(1,101),velocityAvgs,'b.',label="Velocity Time Averaged")
plt.plot(range(1,101),positionAvgs,'y.',label="Position Time Averaged")
plt.title("g11_plot02")
plt.xlabel("Iteration Value ")
plt.ylabel("Average Time Values (ms)")
lgd=plt.legend(loc='upper center', bbox_to_anchor=(0.5,-0.1),ncol=2)
plt.savefig("./plot_gen/g11_lab09_plot02.png" , bbox_extra_artists=(lgd,), bbox_inches='tight')

# Graph 3
print("Generating Plot 3")
plt.clf()
stepAvgs = []
loopAvgs = []
for i in range(100):
	step = [x[2] for x in data if x[0]==i+1]
	loop = [x[6] for x in data if x[0]==i+1]
	stepAvgs.append(numpy.average(step))
	loopAvgs.append(numpy.average(loop))

plt.plot(range(1,101),stepAvgs,'r.',label="Step Time Averaged")
plt.plot(range(1,101),loopAvgs,'g.',label="Loop Time Averaged")
plt.title("g11_plot03")
plt.xlabel("Rerun Value ")
plt.ylabel("Average Time Values (ms)")
lgd=plt.legend(loc='upper center', bbox_to_anchor=(0.5,-0.1),ncol=2)
plt.savefig("./plot_gen/g11_lab09_plot03.png" , bbox_extra_artists=(lgd,), bbox_inches='tight')

# Graph 4
print("Generating Plot 4")
plt.clf()
collisionAvgs =[]
velocityAvgs = []
positionAvgs = []
for i in range(100):
	colli = [x[3] for x in data if x[0]==i+1] 
	velo = [x[4] for x in data if x[0]==i+1]
	posi = [x[5] for x in data if x[0]==i+1]
	collisionAvgs.append(numpy.average(colli))
	velocityAvgs.append(numpy.average(velo))
	positionAvgs.append(numpy.average(posi))

plt.plot(range(1,101),stepAvgs,'r.',label="Step Time Averaged")
plt.plot(range(1,101),collisionAvgs,'g.',label="Collision Time Averaged")
plt.plot(range(1,101),velocityAvgs,'b.',label="Velocity Time Averaged")
plt.plot(range(1,101),positionAvgs,'y.',label="Position Time Averaged")
plt.title("g11_plot04")
plt.xlabel("Rerun Value ")
plt.ylabel("Average Time Values (ms)")
lgd=plt.legend(loc='upper center', bbox_to_anchor=(0.5,-0.1),ncol=2)
plt.savefig("./plot_gen/g11_lab09_plot04.png" , bbox_extra_artists=(lgd,), bbox_inches='tight')



# Graph 5
print("Generating Plot 5")
plt.clf()
stepAvgs = []
# stepErrMax = []
# stepErrMin = []
stepStdDev = []
for i in range(100):
	step = [x[2] for x in data if x[1]==i+1]
	stepAvgs.append(numpy.average(step))
	# stepErrMax.append(numpy.amax(step))
	# stepErrMin.append(numpy.amin(step))
	stepStdDev.append(numpy.std(step))

# plt.errorbar(range(1,101),stepAvgs,yerr=[stepErrMin,stepErrMax],fmt='.',label="Y Error Bars")
plt.errorbar(range(1,101),stepAvgs,yerr=stepStdDev,fmt='.r',label="Y Error Bars")
plt.title("g11_plot05")
plt.xlabel("Iteration Value")
plt.ylabel("Step Time Values (ms) with Errorbars")
lgd=plt.legend(loc='upper center', bbox_to_anchor=(0.5,-0.1),ncol=2)
plt.savefig("./plot_gen/g11_lab09_plot05.png" , bbox_extra_artists=(lgd,), bbox_inches='tight')


# Graph 6
print("Generating Plot 6")
plt.clf()
vals =[x[2] for x in data if x[1]==12]
fig = plt.figure()
ax = fig.add_subplot(111)
ax.hist(vals,bins=100, label="Frequency")
ax2=ax.twinx()
ax2.hist(vals, bins=100, cumulative=True,histtype='step',color='r',label="Cumulative Frequency")
plt.title("g11_plot06")
ax.set_xlabel("Step Time (ms)")
ax.set_ylabel("Number of Reruns")
ax2.set_ylabel("Cumulative Reruns")
lgd=ax.legend(loc='upper center', bbox_to_anchor=(0.1,-0.1),ncol=2)
lgd2=ax2.legend(loc='upper center', bbox_to_anchor=(0.8,-0.1),ncol=2)
plt.savefig("./plot_gen/g11_lab09_plot06.png" , bbox_extra_artists=(lgd,lgd2), bbox_inches='tight')
