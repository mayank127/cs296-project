.SUFFIXES: .cpp .hpp

# Programs
SHELL 	= bash
CC     	= g++
LD	= ld
RM 	= rm
ECHO	= /bin/echo
CAT	= cat
PRINTF	= printf
SED	= sed
DOXYGEN = doxygen
######################################
# Project Name (generate executable with this name)
TARGET = cs296_base

# Project Paths
PROJECT_ROOT=.
EXTERNAL_ROOT=$(PROJECT_ROOT)/external
SRCDIR = $(PROJECT_ROOT)/src
OBJDIR = $(PROJECT_ROOT)/obj
BINDIR = $(PROJECT_ROOT)/bin
DOCDIR = $(PROJECT_ROOT)/doc

# Library Paths
BOX2D_ROOT=$(EXTERNAL_ROOT)
GLUI_ROOT=/usr
GL_ROOT=/usr

#Libraries
LIBS = -lBox2D -lglui -lglut -lGLU -lGL

# Compiler and Linker flags
CPPFLAGS =-g -O3 -Wall 
CPPFLAGS+=-I $(BOX2D_ROOT)/include -I $(GLUI_ROOT)/include
LDFLAGS+=-L $(BOX2D_ROOT)/lib -L $(GLUI_ROOT)/lib

######################################

NO_COLOR=\e[0m
OK_COLOR=\e[1;32m
ERR_COLOR=\e[1;31m
WARN_COLOR=\e[1;33m
MESG_COLOR=\e[1;34m
FILE_COLOR=\e[1;37m

OK_STRING="[OK]"
ERR_STRING="[ERRORS]"
WARN_STRING="[WARNINGS]"
OK_FMT="${OK_COLOR}%30s\n${NO_COLOR}"
ERR_FMT="${ERR_COLOR}%30s\n${NO_COLOR}"
WARN_FMT="${WARN_COLOR}%30s\n${NO_COLOR}"
######################################

SRCS := $(wildcard $(SRCDIR)/*.cpp)
INCS := $(wildcard $(SRCDIR)/*.hpp)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)


.PHONY: all setup doc clean Box2D report exe dist install

all: setup exe

setup:
	@$(ECHO) "Setting up compilation..."
	@mkdir -p obj
	@mkdir -p bin

-include $(OBJS:.o=.d)

$(BINDIR)/$(TARGET): box2D $(OBJS) 
	@$(PRINTF) "$(MESG_COLOR)Building executable:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "$(notdir $@)"
	@$(CC) -o $@ $(LDFLAGS) $(OBJS) $(LIBS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.err



$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(PRINTF) "$(MESG_COLOR)Compiling: $(NO_COLOR) $(FILE_COLOR) %25s$(NO_COLOR)" "$(notdir $<)"
	@$(CC) $(CPPFLAGS) -c $< -o $@ -MD 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else printf "${OK_COLOR}%30s\n${NO_COLOR}" "[OK]"; \
	fi;
	@$(RM) -f temp.log temp.err

box2D: 
	@$(PRINTF) "$Compiling Box2D"
	@$ cd $(EXTERNAL_ROOT)/src/ ; tar -zxvf Box2D.tgz ; cd Box2D ; mkdir build296 ; cd build296 ; cmake ../ ; make ; make install ; cd ../../../../


exe: clean setup $(BINDIR)/$(TARGET)
	@$(PRINTF) "Executable Made in bin folder"

install: exe report
	@$ rm -rf ../install
	@$ mkdir ../install
	@$ mkdir ../install/doc
	@$ cp -r bin/ ../install/
	@$ cp ./doc/profiling_report.html ./doc/g11_prof_report.pdf ../install/doc/

dist: clean
	@$ rm ../cs296_project_code/ -rf
	@$ mkdir ../cs296_project_code
	@$ cp -r * ../cs296_project_code/
	@$ tar -zcvf ../cs296_g11_project.tar.gz ../cs296_project_code
	@$ rm ../cs296_project_code/ -rf
	

doc:
	@$(ECHO) -n "Generating Doxygen Documentation ...  "
	@$(RM) -rf doc/html
	@$(DOXYGEN) $(DOCDIR)/Doxyfile 2 > /dev/null
	@$(ECHO) "Done"

report: 
	@$(ECHO) -n "Generating Latex Documentation ...  "
	@$(RM) -rf $(DOCDIR)/*.aux $(DOCDIR)/*.bbl $(DOCDIR)/*.blg $(DOCDIR)/*.log $(DOCDIR)/*.pdf
	@$ cd $(DOCDIR); latex g11_prof_report; bibtex g11_prof_report; latex g11_prof_report; latex g11_prof_report; dvips g11_prof_report.dvi; ps2pdf g11_prof_report.ps

clean:
	@$(ECHO) -n "Cleaning up..."
	@$(RM) -rf $(OBJDIR) *~ $(DEPS) $(SRCDIR)/*~ $(DOCDIR)/*.aux $(DOCDIR)/*.log $(DOCDIR)/*.dvi $(DOCDIR)/*.pdf $(DOCDIR)/html $(DOCDIR)/*.ps $(DOCDIR)/*.bbl $(DOCDIR)/*.blg $(BINDIR) $(EXTERNAL_ROOT)/include $(EXTERNAL_ROOT)/lib $(EXTERNAL_ROOT)/src/Box2D
	@$(ECHO) "Done"