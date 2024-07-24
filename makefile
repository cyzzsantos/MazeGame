all: clean jogoUI motor

jogoUI: jogoUI.c
	gcc jogoUI.c -o jogoUI -lncurses

backend: motor.c
	gcc motor.c -o motor

clean:
	rm -f jogoUI motor
	rm -f tmp/*
