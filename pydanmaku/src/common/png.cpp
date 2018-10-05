#include <FreeImage.h>
#include "../../include/common/png.h"

BYTE* load_image(const char *fname, int* width, int* height) {
    static BYTE *data = NULL;
    // active only for static linking
#ifdef FREEIMAGE_LIB
    FreeImage_Initialise();
#endif

    FIBITMAP *bitmap;
    // Get the format of the image file
    FREE_IMAGE_FORMAT fif =FreeImage_GetFileType(fname, 0);

    // If the format can't be determined, try to guess the format from the file name
    if(fif == FIF_UNKNOWN) {
        fif = FreeImage_GetFIFFromFilename(fname);
    }

    // Load the data in bitmap if possible
    if(fif != FIF_UNKNOWN && FreeImage_FIFSupportsReading(fif)) {
        bitmap = FreeImage_Load(fif, fname);
    }
    else {
        bitmap = NULL;
    }

    // PROCESS IMAGE if bitmap was successfully initialized
    if(bitmap) {
        unsigned int w = FreeImage_GetWidth(bitmap);
        unsigned int h = FreeImage_GetHeight(bitmap);
        *width = w; *height = h;

        // Get a pointer to the pixel data
        data = (BYTE*)FreeImage_GetBits(bitmap);
    }

    // Clean bitmap;
    FreeImage_Unload(bitmap);
    // active only for static linking
#ifdef FREEIMAGE_LIB
    FreeImage_DeInitialise();
#endif
    return data;
}