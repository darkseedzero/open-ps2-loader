#ifndef __FNTSYS_H
#define __FNTSYS_H

#include <gsToolkit.h>

/// default (built-in) font id
#define FNT_DEFAULT (0)

/** Initializes the font subsystem */
void fntInit(void);

/** Terminates the font subsystem */
void fntEnd(void);

/** Loads a font
  * @param buffer The memory buffer containing the font
  * @param bufferSize Size of the buffer
  * @return font slot id */
int fntLoad(void* buffer, int bufferSize);

/** Replaces the given font slot with the defined font */
void fntReplace(int id, void* buffer, int bufferSize);

/** Reloads the default font into the given font slot */
void fntSetDefault(int id);

/** Releases a font slot */
void fntRelease(int id);

/** Sets a new aspect ratio
* @note Invalidates the whole glyph cache for all fonts! */
void fntSetAspectRatio(float aw, float ah);

/** Renders a string
* @return Width of the string rendered */
int fntRenderString(int font, int x, int y, short aligned, const unsigned char* string, u64 colour);

/** Calculates the dimensions of the given text string
@param str The string to calculate dimensions for
@param w the resulting width of the string
@param h the resulting height of the string
*/
void fntCalcDimensions(int font, const unsigned char* str, int *w, int *h);

#endif
