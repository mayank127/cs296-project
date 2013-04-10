import re
import os
file1 = open("./data/lab09_g11_data.csv","w")
for i in range (1,101):
	for j in range (1,101):
		p=os.popen("./bin/cs296_base %s" %j)
		text=p.read()
		values=re.findall(r"(?<= is )([0-9\.]+)(?= ms)",text)
		file1.write(str(i)+","+str(j)+","+values[0]+","+values[1]+","+values[2]+","+values[3]+","+values[4]+"\n")
file1.close()
