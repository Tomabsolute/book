CXX = g++
CXXFLAGS = -std=c++11 -lncurses 

TARGET = conway
DOXYGEN = doxygen
DOXYFILE = Doxyfile

SRCS = main.cpp Conway.cpp
DOCS = html/index.html

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

doc:
	$(DOXYGEN) $(DOXYFILE)

clean:
	rm -f $(TARGET) *.bmp
	rm -rf html latex 

