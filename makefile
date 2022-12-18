default:
	gcc -Wall -g -c curl-call-from-json.c -o curl-call-from-json.o
	ar ruv lib-curl-call-from-json.a curl-call-from-json.o

example:
	gcc example.c lib-curl-call-from-json.a -lcurl -lcjson