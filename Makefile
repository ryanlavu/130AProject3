
project3: GraphOperator.o GraphGenerator.o main.o
	gcc -o project3 GraphOperator.o GraphGenerator.o main.o -lstdc++ -lm -ldl

clean:
	$(RM) project3 GraphOperator.o GraphGenerator.o main.o
