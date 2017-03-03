CXXFLAGS = -O2

OBJS = accuracy.o analogy.o basic_method.o debug.o dispatcher.o distance.o main.o model.o multi_threads.o parameter_controller.o word2phrase.o word2vector.o wrrbm_train.o

WordRepresentation: $(OBJS)
	g++ -o ../bin/$@ $^ -lpthread

$(OBJS): %.o:%.cpp
	g++ $(CXXFLAGS) -o $@ -c $<

.PHONY: clean

clean:
	-rm $(OBJS) ../bin/WordRepresentation
