output: WindowsAPI.o Start.o linked_list.o stack.o
	g++ WindowsAPI.o Start.o linked_list.o stack.o -o WindowOn

Start.o: Start.cpp
	g++ -c Start.cpp WindowsAPI.h

WindowsAPI.o: WindowsAPI.cpp
	g++ -c WindowsAPI.cpp WindowsAPI.h

linked_list.o: linked_list.cpp 
	g++ -c linked_list.cpp WindowsAPI.h

stack.o: stack.cpp
	g++ -c stack.cpp WindowsAPI.h