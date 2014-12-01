#include "common.h";
#include "encoder.h";
class Png
{
public:
	Png();
	~Png();

	bool init(void);
	bool png_free(void);

	void make_png_buffer(size_t w, size_t h, ui8 **dataRGB, ui8 *buffer);
	void make_png_buffer2(size_t w, size_t h, ui8 *data, ui8 *buffer);
	void write_png_gray(size_t w, size_t h, char *file_name, unsigned char **image);
	void write_png_rgb(size_t w, size_t h, char *file_name, unsigned char **image);
	void write_png_fp_to_memory(size_t w, size_t h, unsigned char **image);

	png_structp png_ptr;
	png_infop   info_ptr;
private:
	static void PngWriteCallback(png_structp  png_ptr, png_bytep data, png_size_t length);
	static void PngWriteCallback2(png_structp  png_ptr, png_bytep data, png_size_t length);
};

Png::Png()
{

}

Png::~Png()
{
	
}

bool Png::init(void){
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL){
		return false;
	}
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
		return false;
	}

	return true;
}

bool Png::png_free(){
	if (png_ptr != NULL && info_ptr != NULL){
		png_destroy_write_struct(&png_ptr, &info_ptr);
		return true;
	}

	return false;
}

void Png::PngWriteCallback(png_structp  png_ptr, png_bytep data, png_size_t length){
	//std::vector<ui8> *p = (std::vector<ui8>*)png_get_io_ptr(png_ptr);
	//p->insert(p->end(), data, data + length);

	ui8** _p = (ui8**)png_get_io_ptr(png_ptr);
	memcpy(data, *_p, length);
	*_p += length;
}

void Png::PngWriteCallback2(png_structp  png_ptr, png_bytep data, png_size_t length){

	PngEncoder *p = (PngEncoder *)png_get_io_ptr(png_ptr);
	
	if (!p->png) {
		p->png = (char *)malloc(sizeof(p->png) * 41); // from tests pngs are at least 41 bytes
		if (!p->png)
			throw "malloc failed in node-png (PngEncoder::png_chunk_producer)";
		p->mem_len = 41;
	}

	if (p->png_len + length > p->mem_len) {
		char *new_png = (char *)realloc(p->png, sizeof(char)*p->png_len + length);
		if (!new_png)
			throw "realloc failed in node-png (PngEncoder::png_chunk_producer).";
		p->png = new_png;
		p->mem_len += length;
	}
	memcpy(p->png + p->png_len, data, length);
	p->png_len += length;
}

void Png::make_png_buffer(size_t w, size_t h, ui8 **dataRGB, ui8 *buffer){
	//出力バッファ初期化
	//buffer->clear();
	//PNG設定
	png_set_IHDR(png_ptr, info_ptr, w, h, 8,
		PNG_COLOR_TYPE_RGB,
		PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_DEFAULT,
		PNG_FILTER_TYPE_DEFAULT);
	//PNGデータ
	//std::vector<ui8 *> rows(h);
	//for (size_t y = 0; y < h; ++y)
	//	rows[y] = (ui8*)dataRGB + y * w * 3;
	png_set_rows(png_ptr, info_ptr, (png_bytepp)dataRGB);
	buffer = new ui8(w*h*3);
	png_set_write_fn(png_ptr, buffer, PngWriteCallback, NULL);
	png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
}

void Png::make_png_buffer2(size_t w, size_t h, ui8 *data, ui8 *buffer){
	PngEncoder encoder(data,w,h);
	encoder.encode();

}

void Png::write_png_gray(size_t w, size_t h, char *file_name, unsigned char **image)
{
	FILE            *fp;
	png_structp     png_ptr;
	png_infop       info_ptr;

	

	fp = fopen(file_name, "wb");                            // まずファイルを開きます
	png_ptr = png_create_write_struct(                      // png_ptr構造体を確保・初期化します
		PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	info_ptr = png_create_info_struct(png_ptr);             // info_ptr構造体を確保・初期化します
	png_init_io(png_ptr, fp);                               // libpngにfpを知らせます
	png_set_IHDR(png_ptr, info_ptr, w, h,          // IHDRチャンク情報を設定します
		8, PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
	png_write_info(png_ptr, info_ptr);                      // PNGファイルのヘッダを書き込みます
	png_write_image(png_ptr, image);                        // 画像データを書き込みます
	png_write_end(png_ptr, info_ptr);                       // 残りの情報を書き込みます
	png_destroy_write_struct(&png_ptr, &info_ptr);          // ２つの構造体のメモリを解放します
	fclose(fp);                                             // ファイルを閉じます
	
	return;
}

void Png::write_png_rgb(size_t w, size_t h, char *file_name, unsigned char **image)
{
	FILE            *fp;
	png_structp     png_ptr;
	png_infop       info_ptr;



	fp = fopen(file_name, "wb");                            // まずファイルを開きます
	png_ptr = png_create_write_struct(                      // png_ptr構造体を確保・初期化します
		PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	info_ptr = png_create_info_struct(png_ptr);             // info_ptr構造体を確保・初期化します
	png_init_io(png_ptr, fp);                               // libpngにfpを知らせます
	png_set_IHDR(png_ptr, info_ptr, w, h,          // IHDRチャンク情報を設定します
		8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
	png_write_info(png_ptr, info_ptr);                      // PNGファイルのヘッダを書き込みます
	png_write_image(png_ptr, image);                        // 画像データを書き込みます
	png_write_end(png_ptr, info_ptr);                       // 残りの情報を書き込みます
	png_destroy_write_struct(&png_ptr, &info_ptr);          // ２つの構造体のメモリを解放します
	fclose(fp);                                             // ファイルを閉じます

	return;
}

void Png::write_png_fp_to_memory(size_t w, size_t h, unsigned char **image)
{
	FILE            *fp;
	png_structp     png_ptr;
	png_infop       info_ptr;



	fp = fopen("test.png", "wb");                            // まずファイルを開きます
	png_ptr = png_create_write_struct(                      // png_ptr構造体を確保・初期化します
		PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	info_ptr = png_create_info_struct(png_ptr);             // info_ptr構造体を確保・初期化します
	png_init_io(png_ptr, fp);                               // libpngにfpを知らせます
	png_set_IHDR(png_ptr, info_ptr, w, h,          // IHDRチャンク情報を設定します
		8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
	png_write_info(png_ptr, info_ptr);                      // PNGファイルのヘッダを書き込みます
	png_write_image(png_ptr, image);                        // 画像データを書き込みます
	png_write_end(png_ptr, info_ptr);                       // 残りの情報を書き込みます
	png_destroy_write_struct(&png_ptr, &info_ptr);          // ２つの構造体のメモリを解放します
	                                            // ファイルを閉じます
	
	char *buf = new char[w*h * 3];
	while (fgets(buf, sizeof buf, fp)) printf("%d\n", buf);
	fclose(fp);
	return;
}