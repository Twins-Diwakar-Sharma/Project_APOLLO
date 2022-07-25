#program name
prog =Apollo

#directories
srcDir =source
incDir =include
bldDir =build
binDir =binary

cc =g++
incl = -I$(incDir)
lib =-lpthread
flag =-pthread

classes =$(shell find $(srcDir) -name "*.cpp")
objects =$(patsubst $(srcDir)/%, $(bldDir)/%, $(classes:.cpp=.o))

all:	directories $(prog)

directories:
	@mkdir -p $(binDir)
	@mkdir -p $(bldDir)

$(prog): $(objects)
	@echo " ____|-----|____"
	@echo " |:: | ::: | :: | "
	@echo " |:: | ::: | :: |"
	@echo " |   |     |    |"
	@echo "     BUILDING "

	$(cc) -o $(binDir)/$@ $^ $(lib)

$(bldDir)/%.o:	$(srcDir)/%.cpp
	$(cc) -o $@ -c $< $(flag) $(incl)

clean:
	@rm -rf $(bldDir)

purge:	clean
	@rm -rf $(binDir)
	@echo "This is SPARTA !!!!!!!!"
	@echo "KICK"
	
