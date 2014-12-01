#include "common.h";
#include "MakePNG.h"

using namespace v8;

Handle<Value> png_to_memory(const Arguments& args) {
	HandleScope scope;
	Png png;
	int w, h, i, j;
	ui8   **raw,*out;

	w = args[0]->Int32Value();
	h = args[1]->Int32Value();

	raw = new ui8*[h];
	for (i = 0; i < h; i++){
		raw[i] = new ui8[w * 3];
	}
	printf("A");
	Local<Array> data = Local<Array>::Cast(args[2]);
	for (i = 0; i < h; i++) {                           // 以下５行は単純なテストパターンを作ります
		for (j = 0; j<w * 3; j += 3) {
			raw[i][j    ] = (ui8)(data->Get(j + (w * 3 * i))->Int32Value());
			raw[i][j + 1] = (ui8)(data->Get(j + 1 + (w * 3 * i))->Int32Value());
			raw[i][j + 2] = (ui8)(data->Get(j + 2 + (w * 3 * i))->Int32Value());
		}
	}
	printf("B");
	

	png.init();
	//png.write_png_rgb(w, h, *file, raw);
	png.make_png_buffer(w, h, raw, out);
	printf("%s",out);
	//png.write_png_fp_to_memory(w,h,raw);
	png.png_free();
	

	return scope.Close(Undefined());








	/*
	int w, h, i, j;
	int len;
	ui8   *raw;
	std::vector<ui8> *out;
	out->clear();

	w = args[0]->Int32Value();
	h = args[1]->Int32Value();

	//raw = new ui8[w*h*3];

	Local<Array> data = Local<Array>::Cast(args[2]);
		
	

	for (i = 0; i < w*h*3; i++) {                           // 以下５行は単純なテストパターンを作ります
	raw[i] = (ui8)(data->Get(i)->Int32Value());
	}
	*/

	//printf("A\n");
	//png.make_png_buffer(w, h, raw, out);
	//printf("C\n");
	//len = out->size();
//	printf("%d\n",len);

	//Local<Array> image = Array::New(len);
	
	//printf("%d\n", v8::Number::New(out->at(i)));
	/*
	
	for (i = 0; i < image->Length(); ++i ) {
		image->Set(i, Int32::New(i));
	}
	*/
	//out->clear();

	
	//node::Buffer *image = node::Buffer::New(len);
	/*
	printf("D\n");
	memcpy(node::Buffer::Data(image), out, len);
	printf("E\n");
	Local<Object> globalObj = Context::GetCurrent()->Global();
	Local<Function> bufferConstructor = Local<Function>::Cast(globalObj->Get(String::New("Buffer")));
	Handle<Value> constructorArgs[3] = { image->handle_, v8::Integer::New(len), v8::Integer::New(0) };
	Local<Object> actualBuffer = bufferConstructor->NewInstance(3, constructorArgs);
	*/

	
	
	//printf("F\n");

	//return scope.Close(Undefined());
}

Handle<Value> write_png_gray(const Arguments& args) {
	HandleScope scope;
	Png png;
	int w, h, i, j;
	unsigned char   **raw;

	w = args[0]->Int32Value();
	h = args[1]->Int32Value();
	String::Utf8Value file(args[2]->ToString());

	printf("W:%d,H:%d,F:%s\n",w,h,*file);
	
	raw = new ui8*[h];
	for (i = 0; i < h; i++){
		raw[i] = new ui8[w];
	}

	std::cout << "start" << std::endl;

	Local<Array> data = Local<Array>::Cast(args[3]);
	for (i = 0; i < h; i++) {                           // 以下５行は単純なテストパターンを作ります
		for (j = 0; j < w; j++) {
			raw[i][j] = (ui8)(data->Get(j + (w*i))->Int32Value());
		}
	}

	png.init();
	png.write_png_gray(w, h,*file,raw);

	std::cout << "end" << std::endl;

	return scope.Close(Undefined());
}

Handle<Value> write_png_rgb(const Arguments& args) {
	HandleScope scope;
	Png png;
	int w, h, i, j;
	unsigned char   **raw;

	w = args[0]->Int32Value();
	h = args[1]->Int32Value();
	String::Utf8Value file(args[2]->ToString());

	printf("W:%d,H:%d,F:%s\n", w, h, *file);

	raw = new ui8*[h];
	for (i = 0; i < h; i++){
		raw[i] = new ui8[w*3];
	}

	std::cout << "start" << std::endl;

	Local<Array> data = Local<Array>::Cast(args[3]);
	for (i = 0; i < h; i++) {                           // 以下５行は単純なテストパターンを作ります
		for (j = 0;j<w*3;j+=3) {
			raw[i][j  ] = (ui8)(data->Get(j   + (w*3*i))->Int32Value());
			raw[i][j+1] = (ui8)(data->Get(j+1 + (w*3*i))->Int32Value());
			raw[i][j+2] = (ui8)(data->Get(j+2 + (w*3*i))->Int32Value());
		}
	}
	
	png.init();
	png.write_png_rgb(w, h, *file, raw);
	png.png_free();
	


	std::cout << "end" << std::endl;

	return scope.Close(Undefined());
}

void init(Handle<Object> exports) {
	exports->Set(String::NewSymbol("write_png_to_memory"), FunctionTemplate::New(png_to_memory)->GetFunction());
	exports->Set(String::NewSymbol("write_png_gray"), FunctionTemplate::New(write_png_gray)->GetFunction());
	exports->Set(String::NewSymbol("write_png_rgb"), FunctionTemplate::New(write_png_rgb)->GetFunction());
}

NODE_MODULE(png, init)