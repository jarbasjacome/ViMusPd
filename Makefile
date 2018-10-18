SRCDIR = src
OBJDIR = obj
BINDIR = bin
EXEC =  $(BINDIR)/ViMusPd

src = $(wildcard $(SRCDIR)/*.cpp)
obj = $(src:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
dep = $(obj:$(OBJDIR)/%.o=$(OBJDIR)/%.d)

LDFLAGS = -lGL -lglut -lGLU -lXxf86vm -lalut -lfreenect -lopenal \
		  -lopencv_highgui -lopencv_core -lopencv_imgcodecs \
		  -lopencv_imgproc -lopencv_videoio -lboost_thread \
		  -lboost_system -lpthread

all : $(OBJDIR) $(EXEC)

$(EXEC): $(obj)
	test -d $(BINDIR) || mkdir -p $(BINDIR)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) -c $< -o $@ 

-include $(dep)   # inclui todas as dependências no Makefile

# regra para gerar dependências
$(OBJDIR)/%.d: $(SRCDIR)/%.cpp
	$(CPP) $< -MM -MT '$(OBJDIR)/$*.o $(OBJDIR)/$*.d ' >$@

$(OBJDIR):
	test -d $(OBJDIR) || mkdir -p $(OBJDIR)

.PHONY: clean
clean:
	rm -f $(EXEC) $(OBJDIR)/*.o $(OBJDIR)/*.d
