import re
HTML = '<html><head><title> '

lines = []
f  = open("./doc/g11_prof_report.tex","r")
for line in f:
    line = line.rstrip("\n")
    lines.append(line)

f.close()
text = "".join(lines)

sections = text.split("begin{section}*")
HTML += (re.findall("(?<=title{)(?:[ :,.a-zA-Z0-9]*)",sections[0])[0])
HTML +='</title><style type="text/css">'
CSS = 'h1{text-align:center;} img{display:block;margin: 0 auto;height:500px;}'
HTML+=CSS
HTML +='</style></head><body>'



subsections = sections[1].split("begin{subsection}*")
HTML += '<h1>Introduction</h1><p>'
HTML += (re.findall("(?<={Introduction})(?:[- :.,a-zA-Z0-9]*)",subsections[0])[0])
HTML += '</p>'

for i in range (1,7):
	HTML += '<h1>Graph ' + i.__str__() + '</h1><img src="../plots/g11_lab09_plot0'+i.__str__()+'.png"/><p>'
	str = subsections[i].split("eps}")[2]
	str = str.split("end{subsection}")[0]
	str = str.replace("\\\\", "<br>")
	str = str.replace("\\", "<br>")
	HTML += str
	HTML += '</p>'


HTML += '</body></html>'

f = open ("./doc/g1_lab09_report.html","w")
f.write(HTML)
f.close()
