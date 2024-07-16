#ifndef _FUNC
#define _FUNC


int IsBinding(Texture2D _tex)
{
    int width = 0, height = 0;
    _tex.GetDimensions(width, height);
    
    if (width == 0 || height == 0)
        return false;
    
    return true;

}


#endif