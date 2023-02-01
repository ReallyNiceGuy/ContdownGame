CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -std=c++2a -O2
LDFLAGS=-g
LDLIBS=

SRCS=main.cpp
OBJS=$(subst .cc,.o,$(SRCS))

all: tool

tool: $(OBJS)
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -o main $(OBJS) $(LDLIBS)

tool.o: tool.cc support.hh

support.o: support.hh support.cc

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) main
