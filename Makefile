CDFLAGS = -DUNICODE 
LDFLAGS = -municode -fno-exceptions -fno-rtti

output:
	if not exist bin \
		mkdir bin

	g++ src/main.cpp $(CDFLAG) -o bin/engine.exe $(LDFLAGS) 
