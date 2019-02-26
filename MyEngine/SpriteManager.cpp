#include "SpriteManager.h"


#define png_infopp_NULL (png_infopp)NULL
#define int_p_NULL (int*)NULL
#define png_voidp_NULL (png_voidp)NULL
#define png_error_ptr_NULL (png_error_ptr)NULL

std::unordered_map<std::string, Sprite*> SpriteManager::imageMap;

SpriteManager::SpriteManager()
{
}


SpriteManager::~SpriteManager()
{
}


void SpriteManager::ImageLoading()
{
	LoadBmp("./Graphics/test.bmp", "TestImg");
	LoadBmp("./Graphics/uvTest.bmp", "UvTest");
	//LoadBmp("./Graphics/Player.bmp", "PlayerImg");
	//LoadBmp("./Graphics/PlayerBullet.bmp", "PlayerBulletImg");

	LoadPng("./Graphics/Player.png", "PlayerImg");
	LoadPng("./Graphics/PlayerBullet.png", "PlayerBulletImg");
	LoadPng("./Graphics/Jako_0.png", "JakoIdleImg_0");
	LoadPng("./Graphics/Jako_1.png", "JakoIdleImg_1");
	LoadPng("./Graphics/Goei_0.png", "GoeiIdleImg_0");
	LoadPng("./Graphics/Goei_1.png", "GoeiIdleImg_1");
	LoadPng("./Graphics/Boss1_0.png", "Boss1IdleImg_0");
	LoadPng("./Graphics/Boss1_1.png", "Boss1IdleImg_1");
	LoadPng("./Graphics/Boss2_0.png", "Boss2IdleImg_0");
	LoadPng("./Graphics/Boss2_1.png", "Boss2IdleImg_1");
	LoadPng("./Graphics/EnemyDie_0.png", "EnemyDie_0");
	LoadPng("./Graphics/EnemyDie_1.png", "EnemyDie_1");
	LoadPng("./Graphics/EnemyDie_2.png", "EnemyDie_2");
	LoadPng("./Graphics/EnemyDie_3.png", "EnemyDie_3");
	LoadPng("./Graphics/EnemyDie_4.png", "EnemyDie_4");

	LoadPng("./Graphics/Number/0.png", "Font_0");
	LoadPng("./Graphics/Number/1.png", "Font_1");
	LoadPng("./Graphics/Number/2.png", "Font_2");
	LoadPng("./Graphics/Number/3.png", "Font_3");
	LoadPng("./Graphics/Number/4.png", "Font_4");
	LoadPng("./Graphics/Number/5.png", "Font_5");
	LoadPng("./Graphics/Number/6.png", "Font_6");
	LoadPng("./Graphics/Number/7.png", "Font_7");
	LoadPng("./Graphics/Number/8.png", "Font_8");
	LoadPng("./Graphics/Number/9.png", "Font_9");

	LoadPng("./Graphics/1Up.png", "Score");
	LoadPng("./Graphics/HighScore.png", "HighScore");
	LoadPng("./Graphics/StageTxtImage.png", "Stage");

	LoadPng("./Graphics/PlayerHitted_0.png", "PalyerDie_0");
	LoadPng("./Graphics/PlayerHitted_1.png", "PalyerDie_1");
	LoadPng("./Graphics/PlayerHitted_2.png", "PalyerDie_2");
	LoadPng("./Graphics/PlayerHitted_3.png", "PalyerDie_3");

	LoadPng("./Graphics/Ready.png", "Ready");
	LoadPng("./Graphics/GameOver.png", "GameOver");
	LoadPng("./Graphics/Star.png", "Star");

	LoadPng("./Graphics/TitleScene/Title.png", "Title");
	LoadPng("./Graphics/TitleScene/PlayerTxt.png", "PlayerTxt");
	LoadPng("./Graphics/TitleScene/PlayerSelected.png", "PlayerSelected");

	LoadPng("./Graphics/MinerOfGun/Character.png", "Miner_Player");
	LoadPng("./Graphics/MinerOfGun/Character2.png", "Miner_Player2");
	LoadPng("./Graphics/MinerOfGun/100_100_Image.png", "100*100");
	LoadPng("./Graphics/MinerOfGun/AlphaTest.png", "AlphaTest");
	LoadPng("./Graphics/MinerOfGun/point.png", "Point");
	LoadPng("./Graphics/MinerOfGun/InventoryFrame.png", "InventoryFrame");
	LoadPng("./Graphics/MinerOfGun/Inventory_Space.png", "InventorySlot");
	LoadPng("./Graphics/MinerOfGun/Cursor.png", "Cursor");
	LoadPng("./Graphics/MinerOfGun/InfiniteIcon.png", "Infinite");
	LoadPng("./Graphics/MinerOfGun/GameOver.png", "M_GameOver");
	LoadPng("./Graphics/MinerOfGun/Trap_Mark.png", "TrapMark");

	LoadPng("./Graphics/MinerOfGun/Block_Ground.png",			"GroundBlock");
	LoadPng("./Graphics/MinerOfGun/Block_Default.png",			"DefaultBlock");
	LoadPng("./Graphics/MinerOfGun/Block_Explosion.png",		"ExplosionBlock");
	LoadPng("./Graphics/MinerOfGun/Block_Invincibility.png",	"InvincibilityBlock");
	LoadPng("./Graphics/MinerOfGun/Block_Start.png",			"StartBlock");
	LoadPng("./Graphics/MinerOfGun/ItemBlock_Range.png",		"RangeItemBlock");
	LoadPng("./Graphics/MinerOfGun/ItemBlock_Attack.png",		"AttackItemBlock");
	LoadPng("./Graphics/MinerOfGun/ItemBlock_Speed.png",		"SpeedItemBlock");
	LoadPng("./Graphics/MinerOfGun/Block_Laser_1.png",			"LaserBlock_1");
	LoadPng("./Graphics/MinerOfGun/Block_Laser_2.png",			"LaserBlock_2");
	LoadPng("./Graphics/MinerOfGun/Block_Laser_4.png",			"LaserBlock_4");
	LoadPng("./Graphics/MinerOfGun/ItemBlock_Range_Txt.png",	"RangeItemBlockTxt");
	LoadPng("./Graphics/MinerOfGun/ItemBlock_Attack_Txt.png",	"AttackItemBlockTxt");
	LoadPng("./Graphics/MinerOfGun/ItemBlock_Range_Txt.png",	"SpeedItemBlockTxt");

	LoadPng("./Graphics/MinerOfGun/Skin_Heroes.png", "HeroesSkin");
	LoadPng("./Graphics/MinerOfGun/Skin_Cat.png", "CatSkin");
	LoadPng("./Graphics/MinerOfGun/Skin_Charater.png", "CharacterSkin");
	LoadPng("./Graphics/MinerOfGun/Skin_MeatBoy.png", "MeatBoySkin");


	LoadPng("./Graphics/MinerOfGun/Gun_Pistol.png", "PistolGun");
	LoadPng("./Graphics/MinerOfGun/Gun_Default.png", "DefaultGun");
	LoadPng("./Graphics/MinerOfGun/Gun_Rifle.png", "Rifle");
	LoadPng("./Graphics/MinerOfGun/Gun_Sniper.png", "Sniper");

	LoadPng("./Graphics/MinerOfGun/GradientEffect.png", "GradientEffect");
	LoadPng("./Graphics/MinerOfGun/Meter.png", "Meter");

}


void SpriteManager::Release()
{
	for (std::unordered_map<std::string, Sprite*>::iterator it = imageMap.begin(); it != imageMap.end();)
	{
		delete it->second;
		it = imageMap.erase(it);
	}
}


Sprite* SpriteManager::GetImagePtr(const char* imageKey)
{
	return imageMap[imageKey];
}


bool SpriteManager::LoadBmp(const char* imagepath, std::string imageKey)
{
	Sprite* nowImage = new Sprite();
	imageMap.insert(std::pair<std::string, Sprite*>(imageKey, nowImage));

	// Data read from the header of the BMP file
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int imageSize;   // = width*height*3
							  // Actual RGB data
	unsigned char * data;

	FILE* file = fopen(imagepath, "rb");
	if (!file)
	{
		printf("Image could not be opened\n");
		return 0;
	}

	if (fread(header, 1, 54, file) != 54)
	{
		printf("Not a correct BMP file\n");
		return false;
	}

	if (header[0] != 'B' || header[1] != 'M')
	{
		printf("Not a correct BMP file\n");
		return 0;
	}

	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	nowImage->m_width = *(int*)&(header[0x12]);
	nowImage->m_height = *(int*)&(header[0x16]);

	if (imageSize == 0)
		imageSize = nowImage->m_width * nowImage->m_height * 3;
	if (dataPos == 0)
		dataPos = 54;

	data = new unsigned char[imageSize];

	fread(data, 1, imageSize, file);
	fclose(file);


	glGenTextures(1, &nowImage->imageId);

	glBindTexture(GL_TEXTURE_2D, nowImage->imageId);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, nowImage->m_width, nowImage->m_height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	glGenerateMipmap(GL_TEXTURE_2D);

	return true;
}


bool SpriteManager::LoadPng(const char* imagepath, std::string imageKey)
{
	Sprite* nowImage = new Sprite();
	imageMap.insert(std::pair<std::string, Sprite*>(imageKey, nowImage));
	GLubyte		   *ImageData;
	GLubyte		   **data = &ImageData;


	png_structp png_ptr;
	png_infop info_ptr;
	unsigned int sig_read = 0;
	int color_type, interlace_type;
	FILE *fp;

	if ((fp = fopen(imagepath, "rb")) == NULL)
		return false;

	/* Create and initialize the png_struct
	* with the desired error handler
	* functions.  If you want to use the
	* default stderr and longjump method,
	* you can supply NULL for the last
	* three parameters.  We also supply the
	* the compiler header file version, so
	* that we know if the application
	* was compiled with a compatible version
	* of the library.  REQUIRED
	*/

	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL) {
		fclose(fp);

		return false;
	}

	/* Allocate/initialize the memory
	* for image information.  REQUIRED. */

	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		fclose(fp);
		png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL);

		return false;
	}

	/* Set error handling if you are
	* using the setjmp/longjmp method
	* (this is the normal method of
	* doing things with libpng).
	* REQUIRED unless you  set up
	* your own error handlers in
	* the png_create_read_struct()
	* earlier.
	*/

	if (setjmp(png_jmpbuf(png_ptr))) {
		/* Free all of the memory associated
		* with the png_ptr and info_ptr */

		png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
		fclose(fp);

		/* If we get here, we had a
		* problem reading the file */

		return false;
	}

	/* Set up the output control if
	* you are using standard C streams */
	png_init_io(png_ptr, fp);

	/* If we have already
	* read some of the signature */

	png_set_sig_bytes(png_ptr, sig_read);

	/*
	* If you have enough memory to read
	* in the entire image at once, and
	* you need to specify only
	* transforms that can be controlled
	* with one of the PNG_TRANSFORM_*
	* bits (this presently excludes
	* dithering, filling, setting
	* background, and doing gamma
	* adjustment), then you can read the
	* entire image (including pixels)
	* into the info structure with this
	* call
	*

	* PNG_TRANSFORM_STRIP_16 |
	* PNG_TRANSFORM_PACKING  forces 8 bit
	* PNG_TRANSFORM_EXPAND forces to
	*  expand a palette into RGB
	*/

	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, png_voidp_NULL);
	nowImage->m_width = info_ptr->width;
	nowImage->m_height = info_ptr->height;

	switch (info_ptr->color_type) {
	case PNG_COLOR_TYPE_RGBA:
		nowImage->m_hasAlpha = true;
		break;

	case PNG_COLOR_TYPE_RGB:
		nowImage->m_hasAlpha = false;
		break;

	default:
		std::cout << "Color type " << info_ptr->color_type << " not supported" << std::endl;
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		fclose(fp);

		return false;
	}

	unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
	*data = (unsigned char*)malloc(row_bytes * nowImage->m_height);

	png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

	for (int i = 0; i < nowImage->m_height; i++) {
		// note that png is ordered top to  
		// bottom, but OpenGL expect it bottom to top  
		// so the order or swapped  

		//memcpy(*outData+(row_bytes * (outHeight-1-i)), row_pointers[i], row_bytes);  
		memcpy(*data + (row_bytes * i), row_pointers[i], row_bytes);
	}

	/* Clean up after the read,
	* and free any memory allocated */

	png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);

	/* Close the file */
	fclose(fp);


	/* That's it */
	// GL Setting
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &nowImage->imageId);

	glBindTexture(GL_TEXTURE_2D, nowImage->imageId);

	glTexImage2D(
		GL_TEXTURE_2D, 0, 
		nowImage->m_hasAlpha ? GL_RGBA : GL_RGB,
		nowImage->m_width, nowImage->m_height,
		0, 
		nowImage->m_hasAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE,
		ImageData
	);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	free(ImageData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	glGenerateMipmap(GL_TEXTURE_2D);
}