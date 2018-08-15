INCPATH = -I./. -IGameEngine -IGameEngine/Participants
CFLAGS = $(INCPATH) -O3
#CFLAGS+=-D USE_GLUT_DOUBLE_BUFFERS  # DESCOMENTE AQUI SE VOCE DESEJAR USAR DOUBLE BUFFER.

LIBS := -lm -lGL -lGLU -lglut -ljpeg

#Jogo Produzido por Lucas Mello para fins acadêmicos
#   UFES - Departamento de Informática
#   lucashsmello@gmail.com

OBJDIR = objs
OBJS = \
	Map.o PlayerParticipant.o RectPrisma.o Sphere.o maps.o \
	BasicRunner.o Runner.o Box.o MovParticipant.o Participant.o \
	ParticipantFactory.o Space.o image.o jpeg.o \
	Controller.o

OBJS := $(addprefix $(OBJDIR)/,$(OBJS))

$(OBJDIR): ; mkdir $(OBJDIR)

LucasTrabCG: $(OBJDIR) $(OBJS) $(OBJDIR)/main.o
	$(CXX) -o LucasTrabCG $(OBJDIR)/main.o $(OBJS) $(LIBS)


$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: */%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: */*/%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: */*/*/%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: ../*/*/%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@


clean:
	rm -rf objs
