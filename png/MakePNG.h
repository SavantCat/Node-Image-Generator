#include <png.h>
#include <iostream>
#include <vector>

typedef unsigned char ui8;

class Png
{
public:
	Png();
	~Png();

	bool init(void);
	bool png_free(void);

	void make_png_buffer(size_t w, size_t h, ui8 *dataRGBA, std::vector<ui8> *buffer);
	void write_png_gray(size_t w, size_t h, char *file_name, unsigned char **image);
	void write_png_rgba(size_t w, size_t h, char *file_name, unsigned char **image);

	png_structp png_ptr;
	png_infop   info_ptr;
private:
	static void PngWriteCallback(png_structp  png_ptr, png_bytep data, png_size_t length);
};

Png::Png()
{

}

Png::~Png()
{
	png_free();
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
	std::vector<ui8> *p = (std::vector<ui8>*)png_get_io_ptr(png_ptr);
	p->insert(p->end(), data, data + length);
}

void Png::make_png_buffer(size_t w, size_t h, ui8 *dataRGBA, std::vector<ui8> *buffer){
	//PNG�\���̏�����



	if (init() == false){

	}

	buffer->clear();
	//PNG�ݒ�
	png_set_IHDR(png_ptr, info_ptr, w, h, 8,
		PNG_COLOR_TYPE_RGBA,
		PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_DEFAULT,
		PNG_FILTER_TYPE_DEFAULT);
	//PNG�f�[�^
	std::vector<ui8 *> rows(h);
	for (size_t y = 0; y < h; ++y)
		rows[y] = (ui8*)dataRGBA + y * w * 4;
	png_set_rows(png_ptr, info_ptr, &rows[0]);
	png_set_write_fn(png_ptr, buffer, PngWriteCallback, NULL);
	png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

	if (png_free() == false){

	}
}

void Png::write_png_gray(size_t w, size_t h, char *file_name, unsigned char **image)
{
	FILE            *fp;
	png_structp     png_ptr;
	png_infop       info_ptr;

	

	fp = fopen(file_name, "wb");                            // �܂��t�@�C�����J���܂�
	png_ptr = png_create_write_struct(                      // png_ptr�\���̂��m�ہE���������܂�
		PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	info_ptr = png_create_info_struct(png_ptr);             // info_ptr�\���̂��m�ہE���������܂�
	png_init_io(png_ptr, fp);                               // libpng��fp��m�点�܂�
	png_set_IHDR(png_ptr, info_ptr, w, h,          // IHDR�`�����N����ݒ肵�܂�
		8, PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
	png_write_info(png_ptr, info_ptr);                      // PNG�t�@�C���̃w�b�_���������݂܂�
	png_write_image(png_ptr, image);                        // �摜�f�[�^���������݂܂�
	png_write_end(png_ptr, info_ptr);                       // �c��̏����������݂܂�
	png_destroy_write_struct(&png_ptr, &info_ptr);          // �Q�̍\���̂̃�������������܂�
	fclose(fp);                                             // �t�@�C������܂�
	
	return;
}

void Png::write_png_rgba(size_t w, size_t h, char *file_name, unsigned char **image)
{
	FILE            *fp;
	png_structp     png_ptr;
	png_infop       info_ptr;



	fp = fopen(file_name, "wb");                            // �܂��t�@�C�����J���܂�
	png_ptr = png_create_write_struct(                      // png_ptr�\���̂��m�ہE���������܂�
		PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	info_ptr = png_create_info_struct(png_ptr);             // info_ptr�\���̂��m�ہE���������܂�
	png_init_io(png_ptr, fp);                               // libpng��fp��m�点�܂�
	png_set_IHDR(png_ptr, info_ptr, w, h,          // IHDR�`�����N����ݒ肵�܂�
		8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
	png_write_info(png_ptr, info_ptr);                      // PNG�t�@�C���̃w�b�_���������݂܂�
	png_write_image(png_ptr, image);                        // �摜�f�[�^���������݂܂�
	png_write_end(png_ptr, info_ptr);                       // �c��̏����������݂܂�
	png_destroy_write_struct(&png_ptr, &info_ptr);          // �Q�̍\���̂̃�������������܂�
	fclose(fp);                                             // �t�@�C������܂�

	return;
}