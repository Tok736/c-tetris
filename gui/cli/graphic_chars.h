#ifndef GRAPHIC_CHARS_H
#define GRAPHIC_CHARS_H

#define CH_EMPTY             ' '

#define CH_MENU_LEFT_ARROW   '<'
#define CH_MENU_RIGHT_ARROW  '>'
#define CH_BLOCK1            ACS_CKBOARD, ACS_CKBOARD
#define CH_BLOCK2            ((char)0x2588), ((char)0x2588)
#define CH_BLOCK3            (ACS_CKBOARD | A_REVERSE), (ACS_CKBOARD | A_REVERSE)
#define CH_BLOCK4            (ACS_BSSS | A_REVERSE), (ACS_SSBS | A_REVERSE)
#define CH_MISSING_BLOCK     ('#'), ('#')

#endif  // GRAPHIC_CHARS_H