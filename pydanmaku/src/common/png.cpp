#include <FreeImage.h>
#include <cstdio>

BYTE* load_image(const char *fname, int* width, int* height) {
    static BYTE *data = NULL;
    // active only for static linking
#ifdef FREEIMAGE_LIB
    FreeImage_Initialise();
#endif

    FIBITMAP *bitmap;
    FREE_IMAGE_FORMAT fif =FreeImage_GetFileType(fname, 0);
    if(fif == FIF_UNKNOWN) {
        fif = FreeImage_GetFIFFromFilename(fname);
    }
    bitmap = FreeImage_Load(fif, fname);
    if (FreeImage_GetBPP(bitmap) != 32 ) {
        FIBITMAP* oldImage = bitmap;
        bitmap = FreeImage_ConvertTo32Bits(oldImage);
        FreeImage_Unload(oldImage);
    }
    if(bitmap) {
        unsigned int w = FreeImage_GetWidth(bitmap);
        unsigned int h = FreeImage_GetHeight(bitmap);
        printf("Loading %s %d %d\n", fname, w, h);
        *width = w; *height = h;
        data = (BYTE*)FreeImage_GetBits(bitmap);
    }
    FreeImage_Unload(bitmap);
    // active only for static linking
#ifdef FREEIMAGE_LIB
    FreeImage_DeInitialise();
#endif
    return data;
}