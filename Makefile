main.exe:main.cpp
	g++ -o $@ $^
clean:
	rm -rf *.exe *.o