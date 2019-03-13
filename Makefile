UNAME    = $(shell uname)
EXE      = BsAnalysis
 
VPATH  = .:./interface
vpath %.h ./interface

CSUF   = cc
HSUF   = h
DICTC  = Dict.$(CSUF)
DICTH  = $(patsubst %.$(CSUF),%.h,$(DICTC))
DICTO  = $(patsubst %.$(CSUF),%.o,$(DICTC))

SRCS   = src/AnalObjects.cc src/AnaUtil.cc src/BsAnalysis.cc
OBJS   = $(patsubst %.$(CSUF), %.o, $(SRCS))

CXX       = g++
LDFLAGS  = -g
SOFLAGS  = -shared 
CXXFLAGS = -I./interface -I./ -g -Wall -Wno-deprecated -std=c++11
LIBS = 

# Add names of the header files which you do not want to create dictionary of
HDRS_DICT = interface/AnalObjects.h interface/LinkDef.h

bin: $(EXE) 
cling: $(DICTC)
all: 
	gmake cling
	gmake bin 
 
$(DICTC): $(HDRS_DICT)
	echo "Generating dictionary $(DICTC)"
	rootcling -f $@ -rmf interface/SLHCUpgradeSimulationsTTAnalysis_xr.rootmap -c $(CXXFLAGS) $^
	mv $(DICTC) src/ 
	cp Dict_rdict.pcm src/

$(EXE): $(OBJS) src/$(DICTO)
	$(CXX) $(LDFLAGS) $^ -o $@ $(LIBS) `root-config --libs`
 
# Create object files
%.o : %.$(CSUF)
	$(CXX) $(CXXFLAGS) -std=c++11 `root-config --cflags` -o $@ -c $<

# makedepend
depend: $(SRCS:.$(CSUF)=.$(CSUF).dep)
	@cat $(notdir $^) > Makefile.dep
	@-rm -f $(notdir $^) $(patsubst %,%.bak,$(notdir $^))
%.dep:
	@touch $(notdir $@)
	rmkdepend -f$(notdir $@) -- $(CXXFLAGS) `root-config --cflags` -- $*
include Makefile.dep

# Clean 
.PHONY   : clean 
clean : 
	@-rm $(OBJS) $(EXE) src/$(DICTC) src/$(DICTO)
