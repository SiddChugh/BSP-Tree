#flags passed to the g++ compiler
CXXFLAGS += -g -std=c++17
SOURCE_FILE = BVTreeQuestion.cpp
TEST_OBJECT = BVTreeTest
TEST_FILES = BVTreeQuestionTest.cpp

all:
	$(CXX) $(CXXFLAGS) -c $(SOURCE_FILE)

test:
	$(CXX) $(CXXFLAGS) -o $(TEST_OBJECT) $(TEST_FILES) $(SOURCE_FILE) 	

clean:
	rm $(TEST_OBJECT)