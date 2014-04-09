roadImageExtract: main.cpp utility.o logger.o readConfig.o json_reader.o json_value.o json_writer.o
	g++ -o roadImageExtract main.cpp utility.o logger.o readConfig.o json_reader.o json_value.o json_writer.o \
	    `pkg-config opencv --libs` `pkg-config log4cplus --libs`
	rm *.o
utility.o: utility.h utility.cpp
	g++ -o utility.o -c utility.cpp `pkg-config opencv --cflags`
readConfig.o: readConfig.h readConfig.cpp
	g++ -o readConfig.o -c readConfig.cpp
logger.o: logger.h logger.cpp
	g++ -o logger.o -c logger.cpp
json_reader.o: ./json/json_reader.cpp
	g++ -o json_reader.o -c ./json/json_reader.cpp
json_value.o: ./json/json_value.cpp
	g++ -o json_value.o -c ./json/json_value.cpp
json_writer.o: ./json/json_writer.cpp
	g++ -o json_writer.o -c ./json/json_writer.cpp
clean:
	rm roadImageExtract
