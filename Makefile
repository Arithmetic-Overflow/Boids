GPP = g++
OBJ = boidsim.o Boid.o math.o

main : $(OBJ)
	g++ $(OBJ) -o boidsim -lsfml-graphics -lsfml-window -lsfml-system

%.o : %.cpp
	g++ -c $<

exportDisplay:
	export DISPLAY=:0

clean:
	rm -fv *.o boidsim