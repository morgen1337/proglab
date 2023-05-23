integctrl: integctrl.c
	gcc integctrl.c -Wall -lcrypto -o integctrl

save: integctrl
	./integctrl -s -r -f database loc

check: integctrl
	./integctrl -c -f database loc

error1: integctrl
	./integctrl -c -s -f
error2: integctrl
	./integctrl -c database loc
error3: integctrl
	./integctrl -s -f database
error4: integctrl
	./integctrl -c -f wow
	