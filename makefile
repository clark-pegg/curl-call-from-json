default:
	gcc -Wall -g -c curl-call-from-json.c -o curl-call-from-json.o
	ar ruv libccfj.a curl-call-from-json.o

example:
	gcc example.c libccfj.a -lcurl -lcjson