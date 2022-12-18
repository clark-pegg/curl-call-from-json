run: 
	gcc -Wall -o curl-call-from-json curl-call-from-json.c -lcurl -lcjson
	./curl-call-from-json

debug: 
	gcc -g -Wall -o curl-call-from-json curl-call-from-json.c -lcurl -lcjson
	valgrind -s --vgdb=no --track-origins=yes --leak-check=full --show-leak-kinds=all ./curl-call-from-json