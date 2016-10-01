TARGET=/root/ecgusbethernet
LIBS=-lncurses -lpthread -lm

all: $(TARGET)

$(TARGET): main.c udp_send_thread.c 
	gcc main.c -o $(TARGET) $(LIBS) -g

clean:
	rm -rf *.o $(TARGET)
