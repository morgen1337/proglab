integctrl: integctrl.c
	gcc integctrl.c -lcrypto -o integctrl

save: integctrl
	./integctrl -s loc database

check: integctrl
	./integctrl -c loc database