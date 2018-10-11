src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)
dep = $(obj:.o=.d)  # one dependency file for each source

LDFLAGS = -lGL -lglut -lGLU -lXxf86vm -lalut -lfreenect -lopenal \
		  -lopencv_highgui -lopencv_core -lopencv_imgcodecs \
		  -lopencv_imgproc -lopencv_videoio -lboost_thread \
		  -lboost_system -lpthread

ViMusPd: $(obj)
	mkdir -p ../bin
	$(CXX) -o ../bin/$@ $^ $(LDFLAGS)

-include $(dep)   # include all dep files in the makefile

# rule to generate a dep file by using the C preprocessor
# (see man cpp for details on the -MM and -MT options)
%.d: %.c
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@

.PHONY: clean
clean:
	rm -f $(obj) ../bin/ViMusPd

.PHONY: cleandep
cleandep:
	rm -f $(dep)
