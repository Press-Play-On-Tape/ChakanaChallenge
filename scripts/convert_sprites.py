from PIL import Image
import os
from pathlib import Path

def get_shade(rgba, shades, shade):
    if rgba[0] == 252 and rgba[1] == 111 and rgba[2] == 207 and rgba[3] == 255: 
        return 0

    w = (254 + shades) // shades
    b = (shade + 1) * w
    return 1 if rgba[0] >= b else 0

def get_mask(rgba):

    if rgba[0] == 252 and rgba[1] == 111 and rgba[2] == 207 and rgba[3] == 255: 
        return 0
    return 1 if rgba[3] >= 128 else 0

def convert(fname, shades, sw = None, sh = None, num = None, maskImage = False):

    if not (shades >= 2 and shades <= 4):
        print('shades argument must be 2, 3, or 4')
        return None

    im = Image.open(fname).convert('RGBA')
    pixels = list(im.getdata())
    
    masked = maskImage
    q = 0
    for i in pixels:
        q = q + 1
        # print(i[0])
        # print(i[1])
        # print(i[2])
        # print(i[3])
        if i[0] == 252 and i[1] == 111 and i[2] == 207 and i[3] == 255: 
            masked = True
            break
        if i[3] < 255:
            # print('masked!!! ')
            # print(q)
            masked = True
            # exit()
            break

    print('{}, shades {}, masked {}'.format(fname, shades, masked))


    w = im.width
    h = im.height
    if sw is None: sw = w
    if sh is None: sh = h
    nw = w // sw
    nh = h // sh
    if num is None: num = nw * nh
    sp = (sh + 7) // 8
    
    if nw * nh <= 0:
        print('%s: Invalid sprite dimensions' % fname)
        return None
        
    bytes = bytearray([sw, sh])
    
    for n in range(num):
        bx = (n % nw) * sw
        by = (n // nw) * sh
        for shade in range(shades - 1):
            for p in range(sp):
                for ix in range(sw):
                    x = bx + ix
                    byte = 0
                    mask = 0
                    for iy in range(8):
                        y = p * 8 + iy
                        if y >= sh: break
                        y += by
                        i = y * w + x
                        rgba = pixels[i]
                        byte |= (get_shade(rgba, shades, shade) << iy)
                        mask |= (get_mask(rgba) << iy)
                    bytes += bytearray([byte])
                    if masked:
                        bytes += bytearray([mask])
    
    return bytes
    
def convert_header(fname, fout, sym, shades, sw = None, sh = None, num = None, maskImage = False):
    bytes = convert(fname, shades, sw, sh, num, maskImage)
    if bytes is None: return
    with open(fout, 'a') as f:
        # f.write('#pragma once\n\n#include <stdint.h>\n#include <avr/pgmspace.h>\n\n')
        # f.write('constexpr uint8_t %s[] PROGMEM =\n{\n' % sym)
        f.write('uint8_t %s[] = {\n  ' % sym)
        for n in range(len(bytes)):
            if n % 16 == 2:
                f.write('\n  ')
            f.write('%3d,' % bytes[n])
            # f.write(' ' if n % 16 != 15 else '\n')
            # f.write(' ' if n % 18 != 2 else '\n')
            f.write(' ')
        if len(bytes) % 16 != 2:
            f.write('\n')
        f.write('};\n\n')

def deleteFile(filename):
    if os.path.isfile(filename):
        os.remove(filename)

BASE = './images/'
IMAGES = '../images/'

deleteFile(BASE + 'Images.hpp')

convert_header(IMAGES + 'Titles/PPOT.png',                                                     BASE + 'Images.hpp', 'PPOT', 4, 128, 64)
convert_header(IMAGES + 'Titles/Sound_Volume_Grey.png',                                        BASE + 'Images.hpp', 'Sound_Volume_Grey', 4, 22, 16)
convert_header(IMAGES + 'Titles/Sound_Volume_White.png',                                       BASE + 'Images.hpp', 'Sound_Volume_White', 4, 22, 16)
convert_header(IMAGES + 'Titles/Sound_Checkbox.png',                                           BASE + 'Images.hpp', 'Sound_Checkbox', 4)
convert_header(IMAGES + 'Titles/Title.png',                                                    BASE + 'Images.hpp', 'Title', 4, 48, 40, maskImage=False)
convert_header(IMAGES + 'Titles/Title_Background.png',                                         BASE + 'Images.hpp', 'Title_Background', 4)
convert_header(IMAGES + 'Titles/Pause.png',                                                    BASE + 'Images.hpp', 'Pause', 4, 128, 64)

convert_header(IMAGES + 'HUD.png',                                                             BASE + 'Images.hpp', 'HUD', 4)
convert_header(IMAGES + 'ArrowUpDown.png',                                                     BASE + 'Images.hpp', 'ArrowUpDown', 4)

convert_header(IMAGES + 'Palm1.png',                                                            BASE + 'Images.hpp', 'Palm1', 4)
convert_header(IMAGES + 'Palm2.png',                                                            BASE + 'Images.hpp', 'Palm2', 4)
convert_header(IMAGES + 'Palm3.png',                                                            BASE + 'Images.hpp', 'Palm3', 4)
convert_header(IMAGES + 'Palm4.png',                                                            BASE + 'Images.hpp', 'Palm4', 4)
convert_header(IMAGES + 'Palm5.png',                                                            BASE + 'Images.hpp', 'Palm5', 4)
convert_header(IMAGES + 'Palm6.png',                                                            BASE + 'Images.hpp', 'Palm6', 4)

convert_header(IMAGES + 'Background.png',                                                            BASE + 'Images.hpp', 'Background', 4)
convert_header(IMAGES + 'Background_Above.png',                                                            BASE + 'Images.hpp', 'Background_Above', 4)
convert_header(IMAGES + 'Player.png',                                                            BASE + 'Images.hpp', 'Player', 4, 16, 16)
convert_header(IMAGES + 'Enemy.png',                                                            BASE + 'Images.hpp', 'Enemy', 4, 16, 16)
convert_header(IMAGES + 'Player_Bounce.png',                                                     BASE + 'Images.hpp', 'Player_Bounce', 4, 16, 24)
convert_header(IMAGES + 'Waves.png',                                                            BASE + 'Images.hpp', 'Waves', 4, 128, 8)
convert_header(IMAGES + 'Pulse.png',                                                            BASE + 'Images.hpp', 'Pulse', 4, 32, 32)
convert_header(IMAGES + 'Beach.png',                                                            BASE + 'Images.hpp', 'Beach', 4)
convert_header(IMAGES + 'Beach_LH.png',                                                            BASE + 'Images.hpp', 'Beach_LH', 4, 50, 32)
convert_header(IMAGES + 'Boat.png',                                                            BASE + 'Images.hpp', 'Boat', 4)
convert_header(IMAGES + 'Boat_Small.png',                                                            BASE + 'Images.hpp', 'Boat_Small', 4, 10, 16)
convert_header(IMAGES + 'Arrow.png',                                                            BASE + 'Images.hpp', 'Arrow', 4, 11, 8)

convert_header(IMAGES + 'InventoryPanel.png',                                                            BASE + 'Images.hpp', 'InventoryPanel', 4, 32, 64)
convert_header(IMAGES + 'Cursor_00.png',                                                            BASE + 'Images.hpp', 'Cursor_00', 4)
convert_header(IMAGES + 'Cursor_01.png',                                                            BASE + 'Images.hpp', 'Cursor_01', 4)

convert_header(IMAGES + 'Item_00.png',                                                            BASE + 'Images.hpp', 'Item_00', 4, 16, 16)
convert_header(IMAGES + 'Item_01.png',                                                            BASE + 'Images.hpp', 'Item_01', 4, 16, 16)
convert_header(IMAGES + 'Item_02.png',                                                            BASE + 'Images.hpp', 'Item_02', 4, 16, 16)
convert_header(IMAGES + 'Item_03.png',                                                            BASE + 'Images.hpp', 'Item_03', 4, 16, 16)
convert_header(IMAGES + 'Item_04.png',                                                            BASE + 'Images.hpp', 'Item_04', 4, 16, 16)
convert_header(IMAGES + 'Item_05.png',                                                            BASE + 'Images.hpp', 'Item_05', 4, 16, 16)
convert_header(IMAGES + 'Item_06.png',                                                            BASE + 'Images.hpp', 'Item_06', 4, 16, 16)
convert_header(IMAGES + 'Item_07.png',                                                            BASE + 'Images.hpp', 'Item_07', 4, 16, 16)
convert_header(IMAGES + 'Item_08.png',                                                            BASE + 'Images.hpp', 'Item_08', 4, 16, 16)
convert_header(IMAGES + 'Item_09.png',                                                            BASE + 'Images.hpp', 'Item_09', 4, 16, 16)
convert_header(IMAGES + 'Item_09a.png',                                                            BASE + 'Images.hpp', 'Item_09a', 4)
convert_header(IMAGES + 'Item_10.png',                                                            BASE + 'Images.hpp', 'Item_10', 4, 16, 16)
convert_header(IMAGES + 'Item_11.png',                                                            BASE + 'Images.hpp', 'Item_11', 4, 16, 16)
convert_header(IMAGES + 'Item_12.png',                                                            BASE + 'Images.hpp', 'Item_12', 4, 48, 32)
convert_header(IMAGES + 'Item_13.png',                                                            BASE + 'Images.hpp', 'Item_13', 4, 16, 16)
convert_header(IMAGES + 'Item_14.png',                                                            BASE + 'Images.hpp', 'Item_14', 4, 32, 32)
convert_header(IMAGES + 'Item_15.png',                                                            BASE + 'Images.hpp', 'Item_15', 4, 32, 32)
convert_header(IMAGES + 'Item_16.png',                                                            BASE + 'Images.hpp', 'Item_16', 4, 32, 16)
convert_header(IMAGES + 'Item_17.png',                                                            BASE + 'Images.hpp', 'Item_17', 4, 16, 16)
convert_header(IMAGES + 'Item_18.png',                                                            BASE + 'Images.hpp', 'Item_18', 4, 16, 16, maskImage=True)
convert_header(IMAGES + 'Item_19.png',                                                            BASE + 'Images.hpp', 'Item_19', 4, 16, 16, maskImage=True)
convert_header(IMAGES + 'Item_20.png',                                                            BASE + 'Images.hpp', 'Item_20', 4, 16, 16, maskImage=True)

convert_header(IMAGES + 'Map.png',                                                            BASE + 'Images.hpp', 'Map', 4, 128, 64)
convert_header(IMAGES + 'Scroll.png',                                                            BASE + 'Images.hpp', 'Scroll', 4, maskImage=True)
convert_header(IMAGES + 'Crate_00.png',                                                        BASE + 'Images.hpp', 'Crate_00', 4, maskImage=True)
convert_header(IMAGES + 'Crate_01.png',                                                        BASE + 'Images.hpp', 'Crate_01', 4, maskImage=True)
convert_header(IMAGES + 'Crate_02.png',                                                        BASE + 'Images.hpp', 'Crate_02', 4, maskImage=True)
convert_header(IMAGES + 'Crate_03.png',                                                        BASE + 'Images.hpp', 'Crate_03', 4, maskImage=True)
convert_header(IMAGES + 'Crate_04.png',                                                        BASE + 'Images.hpp', 'Crate_04', 4, maskImage=True)
convert_header(IMAGES + 'Crate_05.png',                                                        BASE + 'Images.hpp', 'Crate_05', 4, maskImage=True)
convert_header(IMAGES + 'Crate_06.png',                                                        BASE + 'Images.hpp', 'Crate_06', 4, maskImage=True)
convert_header(IMAGES + 'Crate_07.png',                                                        BASE + 'Images.hpp', 'Crate_07', 4, maskImage=True)
convert_header(IMAGES + 'Crate_08.png',                                                        BASE + 'Images.hpp', 'Crate_08', 4, maskImage=True)
convert_header(IMAGES + 'Crate_09.png',                                                        BASE + 'Images.hpp', 'Crate_09', 4, maskImage=True)
convert_header(IMAGES + 'Crate_10.png',                                                        BASE + 'Images.hpp', 'Crate_10', 4, maskImage=True)
convert_header(IMAGES + 'Crate_11.png',                                                        BASE + 'Images.hpp', 'Crate_11', 4, maskImage=True)
convert_header(IMAGES + 'Crate_11a.png',                                                        BASE + 'Images.hpp', 'Crate_11a', 4, maskImage=True)
convert_header(IMAGES + 'Crate_12.png',                                                        BASE + 'Images.hpp', 'Crate_12', 4, maskImage=True)
convert_header(IMAGES + 'Crate_13.png',                                                        BASE + 'Images.hpp', 'Crate_13', 4, maskImage=True)
convert_header(IMAGES + 'Crate_14.png',                                                        BASE + 'Images.hpp', 'Crate_14', 4, maskImage=True)
convert_header(IMAGES + 'Crate_15.png',                                                        BASE + 'Images.hpp', 'Crate_15', 4, maskImage=True)
convert_header(IMAGES + 'Crate_16.png',                                                        BASE + 'Images.hpp', 'Crate_16', 4, maskImage=True)
convert_header(IMAGES + 'Crate_17.png',                                                        BASE + 'Images.hpp', 'Crate_17', 4, maskImage=True)
convert_header(IMAGES + 'Crate_18.png',                                                        BASE + 'Images.hpp', 'Crate_18', 4, maskImage=True)
convert_header(IMAGES + 'Crate_19.png',                                                        BASE + 'Images.hpp', 'Crate_19', 4, maskImage=True)
convert_header(IMAGES + 'Crate_20.png',                                                        BASE + 'Images.hpp', 'Crate_20', 4, maskImage=True)
convert_header(IMAGES + 'Crate_21.png',                                                        BASE + 'Images.hpp', 'Crate_21', 4, maskImage=True)
convert_header(IMAGES + 'Crate_22.png',                                                        BASE + 'Images.hpp', 'Crate_22', 4, maskImage=True)
convert_header(IMAGES + 'Crate_23.png',                                                        BASE + 'Images.hpp', 'Crate_23', 4, maskImage=True)
convert_header(IMAGES + 'Crate_24.png',                                                        BASE + 'Images.hpp', 'Crate_24', 4, maskImage=True)
convert_header(IMAGES + 'Crate_25.png',                                                        BASE + 'Images.hpp', 'Crate_25', 4, maskImage=True)
convert_header(IMAGES + 'Crate_26.png',                                                        BASE + 'Images.hpp', 'Crate_26', 4, maskImage=True)
convert_header(IMAGES + 'Crate_27.png',                                                        BASE + 'Images.hpp', 'Crate_27', 4, maskImage=True)
convert_header(IMAGES + 'Crate_28.png',                                                        BASE + 'Images.hpp', 'Crate_28', 4, maskImage=True)
convert_header(IMAGES + 'Crate_29.png',                                                        BASE + 'Images.hpp', 'Crate_29', 4, maskImage=True)
convert_header(IMAGES + 'Crate_30.png',                                                        BASE + 'Images.hpp', 'Crate_30', 4, maskImage=True)
convert_header(IMAGES + 'Crate_31.png',                                                        BASE + 'Images.hpp', 'Crate_31', 4, maskImage=True)
convert_header(IMAGES + 'Crate_32.png',                                                        BASE + 'Images.hpp', 'Crate_32', 4, 16, 16, maskImage=True)
convert_header(IMAGES + 'Crate_33.png',                                                        BASE + 'Images.hpp', 'Crate_33', 4, 16, 16, maskImage=True)
convert_header(IMAGES + 'Crate_34.png',                                                        BASE + 'Images.hpp', 'Crate_34', 4, 16, 16, maskImage=True)
convert_header(IMAGES + 'Crate_35.png',                                                        BASE + 'Images.hpp', 'Crate_35', 4, 16, 16, maskImage=True)
convert_header(IMAGES + 'Crate_36.png',                                                        BASE + 'Images.hpp', 'Crate_36', 4, maskImage=True)
convert_header(IMAGES + 'Crate_37.png',                                                        BASE + 'Images.hpp', 'Crate_37', 4, maskImage=True)
convert_header(IMAGES + 'Crate_38.png',                                                        BASE + 'Images.hpp', 'Crate_38', 4, maskImage=True)
convert_header(IMAGES + 'Spikes.png',                                                          BASE + 'Images.hpp', 'Spikes', 4, maskImage=True)
convert_header(IMAGES + 'Trebochet_Ball.png',                                                   BASE + 'Images.hpp', 'Trebochet_Ball', 4, 16, 16, maskImage=True)



convert_header(IMAGES + 'Health.png',                                                          BASE + 'Images.hpp', 'Health', 4, 15, 8)
convert_header(IMAGES + 'Glint.png',                                                          BASE + 'Images.hpp', 'Glint', 4, 16, 16)
convert_header(IMAGES + 'Sword_Wound.png',                                                          BASE + 'Images.hpp', 'Sword_Wound', 4, 6, 16)

convert_header(IMAGES + 'BoatEnters/BoatEnters.png',                                                          BASE + 'Images.hpp', 'BoatEnters', 4, 128, 64)
convert_header(IMAGES + 'EndOfLevel.png',                                                          BASE + 'Images.hpp', 'EndOfLevel', 4, 56, 64)
