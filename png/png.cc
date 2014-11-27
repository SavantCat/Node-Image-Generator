#include <node.h>

using namespace v8;

Handle<Value> png(const Arguments& args) {
	HandleScope scope;



	return scope.Close(Undefined());
}

void init(Handle<Object> exports) {
	exports->Set(String::NewSymbol("png"),
		FunctionTemplate::New(png)->GetFunction());
}

NODE_MODULE(png, init)