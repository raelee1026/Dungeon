CC = g++
CFLAGS = -std=c++11 -Wall
SRCDIR = .
INCDIR = .
BUILDDIR = .
TARGET = main

SRCS = $(wildcard $(SRCDIR)/*.cpp)
TXTS = $(wildcard $(SRCDIR)/*.txt)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -c -o $@ $^

txtfiles: $(TXTS)
	@mkdir -p $(BUILDDIR)
	cp $^ $(BUILDDIR)

clean:
	rm -rf $(BUILDDIR)/*.o $(TARGET)

.PHONY: txtfiles  
